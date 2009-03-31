#if !defined SL_LE_core_io_slCDataStream_h
#define SL_LE_core_io_slCDataStream_h

#include <iostream>

namespace utl
{

template
<
  typename elemT,
  typename traitsT,
  typename allocT
>
class basic_membuf
  : public std::basic_streambuf<elemT, traitsT>,
    public allocT
{
  private:
    enum { opt_shared_buffer = 1 };
  public:
    typedef elemT                           char_type;
    typedef traitsT                         traits_type;
    typedef typename traits_type::int_type  int_type;
    typedef typename traits_type::pos_type  pos_type;
    typedef typename traits_type::off_type  off_type;

    typedef std::basic_streambuf<elemT, traitsT>  sbuf_type;
    typedef allocT                          allocator_type;
    typedef typename allocT::pointer        pointer;
    typedef typename allocT::const_pointer  const_pointer;
    typedef typename allocT::size_type      size_type;
  public:  // CTOR/DTOR
    // output (extensible buffer)
    basic_membuf(size_type initial_size = 0)
    {
      pointer ptr = 0;
      if(initial_size > 0)
      {
        ptr = allocator_type::allocate(initial_size);
      }
      init(0, ptr, initial_size);
    }
    // input (fixed length buffer)
    basic_membuf(pointer ptr, size_type n)
    {
      init(opt_shared_buffer, ptr, n);
    }
    virtual ~basic_membuf()
    {
      fini();
    }
  public:
    // return pointer to the beginning of the buffer
    const_pointer c_data() const
    {
      return this->pbase();
    }
    // return whole buffer size
    size_type size() const
    {
      return (this->epptr() - this->pbase());
    }

    // output buffer acceptors
    // return pointer to hte beginning of output buffer
    const_pointer c_odata() const
    {
      return this->pbase();
    }
    // return elements count already writen to the output buffer
    size_type osize() const
    {
      return (this->pptr() - this->pbase());
    }

    // input buffer acceptors
    // return pointer to the current element in the input buffer
    const_pointer c_idata() const
    {
      return this->gptr();
    }
    // return elements count available in the input buffer
    size_type isize() const
    {
      const_cast<basic_membuf*>(this)->adjust_egptr();
      return (this->egptr() - this->gptr());
    }
  protected:
    virtual int_type overflow(int_type c = traits_type::eof())
    {
      int gpos = int(this->gptr() - this->eback());
      if(extend())
      {
        *(this->pptr()) = c, this->pbump(1);
        // adjust get area pointers
        this->setg(this->pbase(), this->pbase() + gpos, this->pptr());
        return traits_type::not_eof(c);
      }
      return traits_type::eof();
    }
    int_type underflow()
    {
      if(this->gptr() < this->egptr()) return *(this->gptr());
      return (adjust_egptr()?traits_type::not_eof(*(this->gptr())):traits_type::eof());
    }
    pos_type seekoff(off_type off, std::ios_base::seekdir way, std::ios_base::openmode which)
    {
      adjust_egptr();
      pos_type pos(off);
      switch(way)
      {
        case std::ios_base::beg:
          break;
        case std::ios_base::cur:
          if((which & std::ios_base::in && which & std::ios_base::out) ||
            which & std::ios_base::out)
          {
            pos += int_type(this->pptr() - this->pbase());
          }
          else
          if(which & std::ios_base::in)
          {
            pos += int_type(this->gptr() - this->eback());
          }
          else
          {
            return pos_type(off_type(-1));
          }
          break;
        case std::ios_base::end:
          if((which & std::ios_base::in && which & std::ios_base::out) ||
            which & std::ios_base::out)
          {  
            pos = int_type(this->egptr() - this->pbase()) + pos;
          }
          else
          if(which & std::ios_base::in)
          {
            pos = int_type(this->egptr() - this->eback()) + pos;
          }
          else
          {
            return pos_type(off_type(-1));
          }
          break;
        default:
          return pos_type(off_type(-1));
      }
      return seekpos(pos, which);
    }
    pos_type seekpos(pos_type pos, std::ios_base::openmode which)
    {
      adjust_egptr();
      off_type offset = off_type(pos);
      if(which & std::ios_base::in)
      {
        if(offset < 0 || offset > this->egptr() - this->eback())
        {
          return pos_type(off_type(-1));
        }
        this->setg(this->eback(), this->eback() + offset, this->egptr());
      }
      if(which & std::ios_base::out)
      {
        if(offset < 0 || offset > this->egptr() - this->pbase())
        {
          return pos_type(off_type(-1));
        }
        this->setp(this->pbase(), this->epptr());
        this->pbump(offset);
      }
      return pos;
    }
  private:
    void init(int opts, pointer ptr, size_type n)
    {
      opts_ = opts;
      this->setp(ptr, ptr + n);
      this->setg(ptr, ptr, ptr + n);
    }
    void fini()
    {
      if(!(opts_ & opt_shared_buffer))
      {
        allocator_type::deallocate
        (
          this->pbase(),
          this->epptr() - this->pbase()
        );
        this->setp(0, 0);
        this->setg(0, 0, 0);
      }
    }
    bool adjust_egptr()
    {
      if(this->egptr() < this->pptr())
      {
        this->setg(this->eback(), this->gptr(), this->pptr());
        return true;
      }
      return false;
    }
    bool extend()
    {
      enum { min_extent_size = 32 };
      if(opts_ & opt_shared_buffer)
      {
        return false;
      }
      size_type old_size = size();
      int offset = int(this->pptr() - this->pbase());
      // realloc memory
      // grow buffer by 50%
      size_type inc = (old_size/2 < min_extent_size ? min_extent_size : old_size/2);
      while(inc > 0 && INT_MAX - inc < old_size)
      {  // halve increment in case of numeric overflow
        inc /= 2;
      }
      pointer ptr = 0;
      if(inc > 0)
      {  // allocate new buffer
        ptr = allocator_type::allocate(old_size + inc);
        if(!ptr)
        {
          return false;
        }
      }
      if(old_size > 0)
      {  // copy all data from old buffer if needed
        traits_type::copy(ptr, this->pbase(), old_size);
        // deallocate old buffer
        allocator_type::deallocate(this->pbase(), old_size);
      }
      // reset pointers
      this->setp(ptr, ptr + old_size + inc);
      this->pbump(offset);
      return true;
    }
  private:
    int opts_;
}; // class <basic_membuf>

template
<
  typename elemT,
  typename traitsT,
  typename allocT
>
class buf_holder
{
  public:
    typedef allocT allocator_type;
    typedef basic_membuf<elemT, traitsT, allocator_type> buffer_type;
  public:
    buf_holder(typename allocT::size_type n = 0)
      :  buf_(n)
    {}
    buf_holder(typename allocT::pointer ptr,
                typename allocT::size_type n)
      :  buf_(ptr, n)
    {}
    buffer_type* bufptr()
    {
      return &buf_;
    }
    buffer_type const* bufptr() const
    {
      return &buf_;
    }
  private:
    buffer_type buf_;
};

template
<
  typename elemT,
  typename traitsT = std::char_traits<elemT>,
  typename allocT = std::allocator<elemT>
>
class basic_imemstream
  : public buf_holder<elemT, traitsT, allocT >,
    public std::basic_istream<elemT, traitsT>
{
  public:
    typedef buf_holder<elemT, traitsT, allocT>  holder_type;
    typedef std::basic_istream<elemT, traitsT>  stream_type;
  public:
    basic_imemstream(typename allocT::const_pointer ptr,
                      typename allocT::size_type n)
      : holder_type(const_cast<typename allocT::pointer>(ptr), n),
        stream_type(holder_type::bufptr())
    {}
    typename allocT::const_pointer c_data() const
    {
      return this->bufptr()->c_idata();
    }
    typename allocT::size_type size() const
    {
      return this->bufptr()->isize();
    }
};

template
<
  typename elemT,
  typename traitsT = std::char_traits<elemT>,
  typename allocT = std::allocator<elemT>
>
class basic_omemstream
  : public buf_holder<elemT, traitsT, std::allocator<elemT> >,
    public std::basic_ostream<elemT, traitsT>
{
  public:
    typedef buf_holder<elemT, traitsT, allocT>  holder_type;
    typedef std::basic_ostream<elemT, traitsT>  stream_type;
  public:
    basic_omemstream(typename allocT::size_type initial_size = 0)
      : holder_type(initial_size),
        stream_type(holder_type::bufptr())
    {}
    typename allocT::const_pointer c_data() const
    {
      return this->bufptr()->c_odata();
    }
    typename allocT::size_type size() const
    {
      return this->bufptr()->osize();
    }
};

typedef basic_imemstream<char>  imemstream;
typedef basic_omemstream<char>  omemstream;

}; // namespace <utl>


namespace sokira
{
	namespace le
	{

typedef ::utl::omemstream CDataStream;
//
//class CDataStream : 
//{
//	public:
//	//	virtual void addFunction(const CString& signature, function);
//		virtual void addClass(const CClass& theClass);
//	//	virtual void addInstance(const CString& name, instance);
//		virtual void runFromStream(std::istream& stream);
//};

	} // namespace le
} // namespace sokira


#endif // not defined SL_LE_core_io_slCDataStream_h
