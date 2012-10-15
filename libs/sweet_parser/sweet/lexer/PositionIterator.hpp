//
// PositionIterator.hpp
// Copyright (c) 2009 - 2011 Charles Baker.  All rights reserved.
//    
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented; you must not
//    claim that you wrote the original software. If you use this software
//    in a product, an acknowledgment in the product documentation would be
//    appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
//    misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source
//    distribution.
//

#ifndef SWEET_LEXER_POSITIONITERATOR_HPP_INCLUDED
#define SWEET_LEXER_POSITIONITERATOR_HPP_INCLUDED

#include <iterator>

namespace sweet
{

namespace lexer
{

/**
// An iterator wrapper that adds line number tracking to iterators or 
// pointers.
*/
template <class Iterator>
class PositionIterator
{
    public:
        typedef std::forward_iterator_tag iterator_category; ///< The type of this iterator (always forward regardless of the underlying iterator).
        typedef typename std::iterator_traits<Iterator>::difference_type difference_type; ///< The type to represent the difference between two iterators.
        typedef typename std::iterator_traits<Iterator>::value_type value_type; ///< The type of the element the iterator can point to.
        typedef typename std::iterator_traits<Iterator>::pointer pointer; ///< The type of a pointer to an element the iterator can point to.
        typedef typename std::iterator_traits<Iterator>::reference reference; ///< Type to represent a reference to an element pointed by the iterator.

    private:
        Iterator position_; ///< The current position of this iterator.
        Iterator end_; ///< One past the last position of the input sequence for this iterator.
        bool ended_; ///< True if this iterator has reached its end.
        int line_; ///< The current line number of this iterator.
    
    public:
        PositionIterator()
        : position_(),
          end_(),
          ended_( true ),
          line_( 1 )
        {
        }
    
        PositionIterator( Iterator begin, Iterator end )
        : position_( begin ),
          end_( end ),
          ended_( begin == end ),
          line_( 1 )
        {
        }
        
        
        PositionIterator( const PositionIterator& iterator )
        : position_( iterator.position_ ),
          end_( iterator.end_ ),
          ended_( iterator.ended_ ),
          line_( iterator.line_ )
        {
        }
        
        
        PositionIterator& operator=( const PositionIterator& iterator )
        {
            if ( this != &iterator )
            {
                position_ = iterator.position_;
                end_ = iterator.end_;
                ended_ = iterator.ended_;
                line_ = iterator.line_;
            }
            
            return *this;
        }
        
        
        PositionIterator& operator++()
        {
            int character = *position_;
            ++position_;
            if ( character == '\n' || character == '\r' && (position_ == end_ || *position_ != '\n') )
            {
                ++line_;
            }
            
            ended_ = position_ == end_;
            return *this;
        }
        
        
        value_type operator*() const
        {
            return *position_;
        }
        
        
        int line() const
        {
            return line_;
        }
        
        
        bool operator!=( const PositionIterator& iterator ) const
        {
            return ended_ || iterator.ended_ ? ended_ != iterator.ended_ : position_ != iterator.position_;
        }
        
        
        bool operator==( const PositionIterator& iterator ) const
        {
            return ended_ || iterator.ended_ ? ended_ == iterator.ended_ : position_ == iterator.position_;
        }
};

}

}

#endif
