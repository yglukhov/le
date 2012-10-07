#pragma once

#include <le/core/slTypes.h>

namespace sokira
{
	namespace le
	{

////////////////////////////////////////////////////////////////////////////////
struct TSTrue
{
	enum { value = true };
};

struct TSFalse
{
	enum { value = false };
};

////////////////////////////////////////////////////////////////////////////////
template <int TVal>
struct TSBoolTypeFromInt : public TSTrue
{};

template <>
struct TSBoolTypeFromInt<0> : public TSFalse
{};

////////////////////////////////////////////////////////////////////////////////
template <int TVal, typename TTrue, typename TFalse>
struct TSIntSelect
{
	typedef TTrue result;
};

template <typename TTrue, typename TFalse>
struct TSIntSelect<0, TTrue, TFalse>
{
	typedef TFalse result;
};

////////////////////////////////////////////////////////////////////////////////
template <typename TFrom, typename TTo>
struct _TSStrictCastAvailable
{
	private:
		typedef char t1;
		typedef struct { t1 t[2]; } t2;
		static t1 _f(int, const TTo*);
		static t2 _f(int, ...);
	public:
		typedef TSBoolTypeFromInt<sizeof(t1) == sizeof(_f(0, static_cast<TFrom*>(0)))> _result;
};

////////////////////////////////////////////////////////////////////////////////
template <typename TFrom, typename TTo>
struct TSStrictCastAvailable : public _TSStrictCastAvailable<TFrom, TTo>::_result
{};

////////////////////////////////////////////////////////////////////////////////
template <typename T1, typename T2>
struct TSTypesEqual : public TSFalse
{};

template <typename T>
struct TSTypesEqual<T, T> : public TSTrue
{};

////////////////////////////////////////////////////////////////////////////////
template <typename TFrom, typename TTo>
struct TSCastAvailable : public TSBoolTypeFromInt<
			TSStrictCastAvailable<TFrom, TTo>::value ||
			TSTypesEqual<TFrom, TTo>::value>
{};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct TSBoolTypeFromType : public TSBoolTypeFromInt<!TSCastAvailable<T, TSFalse>::value>
{};

////////////////////////////////////////////////////////////////////////////////
template <class T, typename TTrue, typename TFalse>
struct TSSelect : public TSIntSelect<TSBoolTypeFromType<T>::value, TTrue, TFalse>
{};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct TSNot : public TSBoolTypeFromInt<!TSBoolTypeFromType<T>::value>
{};

////////////////////////////////////////////////////////////////////////////////
template <typename T1, typename T2>
struct TSAnd : public TSBoolTypeFromInt<TSBoolTypeFromType<T1>::value && TSBoolTypeFromType<T2>::value>
{};

////////////////////////////////////////////////////////////////////////////////
template <typename T1, typename T2>
struct TSOr : public TSBoolTypeFromInt<TSBoolTypeFromType<T1>::value || TSBoolTypeFromType<T2>::value>
{};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct TSPointerPower
{
	enum { value = 0 };
};

template <typename T>
struct TSPointerPower<T*>
{
	enum { value = TSPointerPower<T>::value + 1 };
};

////////////////////////////////////////////////////////////////////////////////
template <typename T, UInt Value>
struct TSIncreasePointerPower
{
	typedef typename TSIncreasePointerPower<T*, Value - 1>::result result;
};

template <typename T>
struct TSIncreasePointerPower<T, 0>
{
	typedef T result;
};

////////////////////////////////////////////////////////////////////////////////
template <typename T, UInt Value>
struct TSDecreasePointerPower
{
	typedef T result;
};

template <typename T, UInt Value>
struct TSDecreasePointerPower<T*, Value>
{
	typedef typename TSDecreasePointerPower<T, Value - 1>::result result;
};

template <typename T>
struct TSDecreasePointerPower<T, 0>
{
	typedef T result;
};

////////////////////////////////////////////////////////////////////////////////
template <typename T, UInt ToValue = 0>
struct TSResetPointerPower
{
	typedef typename TSIncreasePointerPower
		<
			typename TSDecreasePointerPower
			<
				T,
				TSPointerPower<T>::value
			>::result,
			ToValue
		>::result result;
};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct TSIsPointer : public TSBoolTypeFromInt<TSPointerPower<T>::value>
{};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct TSIsConst : public TSFalse
{};

template <typename T>
struct TSIsConst<const T> : public TSTrue
{};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct TSIsMutable : public TSNot<TSIsConst<T> >
{};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct TSIsRef : public TSFalse
{};

template <typename T>
struct TSIsRef<T&> : public TSTrue
{};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct TSIsConstRef : public TSAnd<TSIsRef<T>, TSIsConst<T> >
{};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct TSIsMutableRef : public TSAnd<TSIsRef<T>, TSIsMutable<T> >
{};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct TSRemoveConst
{
	typedef T result;
};

template <typename T>
struct TSRemoveConst<const T>
{
	typedef T result;
};

template <typename T>
struct TSRemoveConst<const T&>
{
	typedef T& result;
};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct TSRemoveRef
{
	typedef T result;
};

template <typename T>
struct TSRemoveRef<T&>
{
	typedef T result;
};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct TSConstRef
{
	typedef const T& result;
//	private:
//		typedef typename TSRemoveRef<T>::result _unref;
//	public:
//		typedef typename TSIntSelect<
//			(sizeof(_unref) > sizeof(_unref&)),
//			const _unref&,
//			const _unref>::result result;
};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
		struct TSRef
{
	typedef T const& result;
//	typedef typename TSSelect<TSIsConst<T>,
//		typename TSConstRef<T>::result,
//		typename TSRemoveRef<T>::result&>::result result;
};

template <typename T>
struct TSRef<const T*>
{
	typedef const T* result;
	//	typedef typename TSSelect<TSIsConst<T>,
	//		typename TSConstRef<T>::result,
	//		typename TSRemoveRef<T>::result&>::result result;
};

template <typename T>
struct TSRef<const T * const>
{
	typedef const T* const result;
	//	typedef typename TSSelect<TSIsConst<T>,
	//		typename TSConstRef<T>::result,
	//		typename TSRemoveRef<T>::result&>::result result;
};

template <typename T>
struct TSRef<T&>
{
	typedef T& result;
};

template <typename T>
struct TSRef<const T>
{
	typedef T const& result;
};


#define LE_DECLARE_MEMBER_FUNCTION_CHECKER(func, name)						\
	template<typename TTypeOfClassThatHasMemberFunction, typename TMemberFunctionType>	\
	struct __##name##__ {															\
		typedef char yes[1];												\
		typedef char no [2];												\
		template <typename U, U> struct type_check;							\
		template <typename _1> static yes &chk(type_check<TMemberFunctionType, &_1::func> *); \
		template <typename   > static no  &chk(...);						\
		typedef TSBoolTypeFromInt<sizeof(chk<TTypeOfClassThatHasMemberFunction>(0)) == sizeof(yes)> result; \
	}; \
	template<typename TTypeOfClassThatHasMemberFunction, typename TMemberFunctionType>	\
	struct name : public __##name##__<TTypeOfClassThatHasMemberFunction, TMemberFunctionType>::result \
	{ }



////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct _TSTypeHasDefaultConstructor
{
	public:
//	template<int x>
//	class receive_size{};

	static int sfinae( int a )
	{
		T t;
		return 0;
	}

	static char sfinae( ... )
	{
		return 0;
	}
	public:
		typedef TSBoolTypeFromInt<sizeof(sfinae(0)) == sizeof(int)> _result;
};

////////////////////////////////////////////////////////////////////////////////
template <typename T>
struct TSTypeHasDefaultConstructor : public _TSTypeHasDefaultConstructor<T>::_result
{ };

	} // namespace le
} // namespace sokira
