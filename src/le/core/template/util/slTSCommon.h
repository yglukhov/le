#pragma once

#include <le/core/config/slPrefix.h>

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
		typedef TSBoolTypeFromInt<sizeof(t1) == sizeof(_f(0, static_cast<TFrom*>(NULL)))> _result;
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
struct TSConstRef
{
	typedef typename TSIntSelect<(sizeof(T) > sizeof(const T&)), const T&, const T>::result result;
};

	} // namespace le
} // namespace sokira
