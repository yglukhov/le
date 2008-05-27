#include <le/core/debug/slDebug.h>
#include <le/core/template/function/slTCFunction.h>
#include <le/core/template/function/slTCBind.h>
#include <le/core/slCString.h>

#include <le/core/preprocessor/slPPand.h>
#include <le/core/preprocessor/slPPor.h>
#include <le/core/preprocessor/slPPnot.h>
#include <le/core/preprocessor/slPPif.h>
#include <le/core/preprocessor/slPPfor.h>
#include <le/core/preprocessor/slPPequal.h>
#include <le/core/preprocessor/slPPnot_equal.h>

#include "slCGeneralTestSuite.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CGeneralTestSuite);

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void CGeneralTestSuite::testTypeTraits()
{
	LE_ENTER_LOG;
	typedef TSIntSelect<0, TSFalse, TSTrue>::result comp1;
	typedef TSIntSelect<1, TSTrue, TSFalse>::result comp2;
	typedef TSTypesEqual<comp2, comp1> comp3;
	typedef TSTypesEqual<int, SInt> comp4;
	typedef TSSelect<comp4, TSTrue, TSFalse>::result comp5;

	LE_ASSERT(comp1::value);
	LE_ASSERT(comp2::value);
	LE_ASSERT(comp3::value);
	LE_ASSERT(comp4::value);
	LE_ASSERT((TSCastAvailable<comp4, TSTrue>::value));
	LE_ASSERT(comp5::value);
	LE_ASSERT(TSNot<TSBoolTypeFromType<TSNot<comp5> > >::value);
	LE_ASSERT(TSNot<TSNot<TSTrue> >::value);
	LE_ASSERT((TSOr<TSFalse, comp5>::value));
	LE_ASSERT((TSNot<TSOr<TSFalse, TSNot<TSBoolTypeFromInt<comp5::value> > > >::value));
	LE_ASSERT((TSAnd<comp5, TSTrue>::value));
	LE_ASSERT((TSNot<TSAnd<comp5, TSNot<TSTrue> > >::value));

	// Type-is-pointer test
	LE_ASSERT(TSPointerPower<int>::value == 0);
	LE_ASSERT(TSPointerPower<int *>::value == 1);
	LE_ASSERT(TSPointerPower<int **>::value == 2);
	LE_ASSERT(TSPointerPower<int ***>::value == 3);
	LE_ASSERT(TSPointerPower<int ****>::value == 4);

	LE_ASSERT(!TSIsPointer<float>::value);
	LE_ASSERT(TSIsPointer<float *>::value);
	LE_ASSERT(TSIsPointer<float **>::value);

	LE_ASSERT((TSTypesEqual<TSResetPointerPower<float>::result, float>::value));
	LE_ASSERT((TSTypesEqual<TSResetPointerPower<float*>::result, float>::value));
	LE_ASSERT((TSTypesEqual<TSResetPointerPower<float**>::result, float>::value));

	LE_ASSERT((TSTypesEqual<TSResetPointerPower<float, 2>::result, float**>::value));
	LE_ASSERT((TSTypesEqual<TSResetPointerPower<float*, 4>::result, float****>::value));
	LE_ASSERT((TSTypesEqual<TSResetPointerPower<float**, 2>::result, float**>::value));
	LE_ASSERT((TSTypesEqual<TSResetPointerPower<float***, 1>::result, float*>::value));

	// Some rtti tests
	LE_ASSERT((TSTypesEqual<leFirstParent, leFirstParent>::value));
	LE_ASSERT((TSTypesEqual<leFirstParent, CTestSuite>::value));
	LE_ASSERT((TSTypesEqual<leFirstPublicParent, CTestSuite>::value));
	LE_ASSERT((TSTypesEqual<leFirstPrivateParent, _SNullType>::value));
	LE_ASSERT((TSTypesEqual<leSelf, CGeneralTestSuite>::value));
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
template <int i>
struct i2t
{
	enum { value = i };
};

template <typename T1, typename T2>
struct TSSortTestPredicate
{

};

template <int i, int j>
struct TSSortTestPredicate <i2t<i>, i2t<j> >
{
	enum { value = (i < j)?(-1):((i > j)?(1):(0)) };
};

template <typename T>
struct TCollectorPredicate
{

};

template <int I>
struct TCollectorPredicate<i2t<I> >
{
	enum { value = (I > 2 && I < 5) };
	typedef i2t<I + 5> result;
};

void CGeneralTestSuite::testTypeList()
{
	LE_ENTER_LOG;
	typedef TSTypeList<i2t<5>, i2t<4>, i2t<3>, i2t<2>, i2t<1>, i2t<0>, i2t<7>,
						i2t<-2>, i2t<0>, i2t<1>, i2t<2>, i2t<3>, i2t<4>, i2t<5>,
						i2t<-1>, i2t<10>, i2t<-3> > unsortedList;
	typedef unsortedList::SortDes<TSSortTestPredicate> sortedList;

	LE_ASSERT(sortedList::TypeAt<0>::result::value == 10);
	LE_ASSERT(sortedList::TypeAt<1>::result::value == 7);
	LE_ASSERT(sortedList::TypeAt<2>::result::value == 5);
	LE_ASSERT(sortedList::TypeAt<3>::result::value == 5);
	LE_ASSERT(sortedList::TypeAt<4>::result::value == 4);
	LE_ASSERT(sortedList::TypeAt<5>::result::value == 4);
	LE_ASSERT(sortedList::TypeAt<6>::result::value == 3);
	LE_ASSERT(sortedList::TypeAt<7>::result::value == 3);
	LE_ASSERT(sortedList::TypeAt<8>::result::value == 2);
	LE_ASSERT(sortedList::TypeAt<9>::result::value == 2);
	LE_ASSERT(sortedList::TypeAt<10>::result::value == 1);
	LE_ASSERT(sortedList::TypeAt<11>::result::value == 1);
	LE_ASSERT(sortedList::TypeAt<12>::result::value == 0);
	LE_ASSERT(sortedList::TypeAt<13>::result::value == 0);
	LE_ASSERT(sortedList::TypeAt<14>::result::value == -1);
	LE_ASSERT(sortedList::TypeAt<15>::result::value == -2);
	LE_ASSERT(sortedList::TypeAt<16>::result::value == -3);

	typedef unsortedList::CollectIf<TCollectorPredicate> collection;
	LE_ASSERT(collection::TypeAt<0>::result::value == 4);
	LE_ASSERT(collection::TypeAt<1>::result::value == 3);
	LE_ASSERT(collection::TypeAt<2>::result::value == 3);
	LE_ASSERT(collection::TypeAt<3>::result::value == 4);

	typedef unsortedList::CollectMutantsIf<TCollectorPredicate> mutatedCollection;
	LE_ASSERT(mutatedCollection::TypeAt<0>::result::value == 9);
	LE_ASSERT(mutatedCollection::TypeAt<1>::result::value == 8);
	LE_ASSERT(mutatedCollection::TypeAt<2>::result::value == 8);
	LE_ASSERT(mutatedCollection::TypeAt<3>::result::value == 9);

	typedef TSTypeList<int, float, int> TypeList1;
	typedef TSTypeList<int, float>::PushBack<int> TypeList2;

	LE_ASSERT((TSTypesEqual<TypeList1::TypeAt<0>::result,
							TypeList2::TypeAt<0>::result>::value));
	LE_ASSERT((TSTypesEqual<TypeList1::TypeAt<1>::result,
							TypeList2::TypeAt<1>::result>::value));
	LE_ASSERT((TSTypesEqual<TypeList1::TypeAt<2>::result,
							TypeList2::TypeAt<2>::result>::value));
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void CGeneralTestSuite::testBasicTypes()
{
	LE_ENTER_LOG;
	LE_ASSERT(sizeof(SInt8) == 1);
	LE_ASSERT(sizeof(UInt8) == 1);
	LE_ASSERT(sizeof(SInt16) == 2);
	LE_ASSERT(sizeof(UInt16) == 2);
	LE_ASSERT(sizeof(SInt32) == 4);
	LE_ASSERT(sizeof(UInt32) == 4);
	LE_ASSERT(sizeof(SInt64) == 8);
	LE_ASSERT(sizeof(UInt64) == 8);

	LE_ASSERT(sizeof(Float32) == 4);
	LE_ASSERT(sizeof(Float64) == 8);
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
static int testFunc(int a, int b)
{
	return (a < b)?(b):(a);
}

class A
{
	public:
		int memberOfA(int a)
		{
			return mFunctor(a);
		}

		TCFunction<int, TSTypeList<int> > mFunctor;
};

void CGeneralTestSuite::testBinds()
{
	LE_ENTER_LOG;
	A objA;

	objA.mFunctor = bind(testFunc, 10, bindTo(0));

	TCFunction<int, TSTypeList<A*, int> > func = bind(&A::memberOfA, bindTo(0), bindTo(1));
	LE_ASSERT(func(&objA, 5) == 10);

	TCFunction<int, TSTypeList<A*, int> > func2 = func;
	LE_ASSERT(func2(&objA, 12) == 12);

	TCFunction<int> func3 = bind(func2, &objA, 8);
	LE_ASSERT(func3() == 10);

	objA.mFunctor = bind(testFunc, 5, bindTo(0));
	LE_ASSERT(func3() == 8);
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void CGeneralTestSuite::testTuples()
{
	LE_ENTER_LOG;
	TCTuple<TSTypeList<int, float, int> > tuple;
	tuple.setValue<0>(5);
	tuple.setValue<2>(6);
	tuple.setValue<1>(3.1f);
	LE_ASSERT(tuple.value<0>() == 5);
	LE_ASSERT(tuple.value<1>() > 3.0f && tuple.value<1>() < 3.2f);
	LE_ASSERT(tuple.value<2>() == 6);
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void CGeneralTestSuite::testStrings()
{
	LE_ENTER_LOG;

	int a = 5;
	CString str = CString::createWithFormat(CString("%d"), a);
	LE_ASSERT(str == "5");

	a = 10;
	str = CString::createWithFormat("%d", a);
	LE_ASSERT(str == "10");
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void CGeneralTestSuite::testFunctionTraits()
{
//	typedef TSFunctionTraits<testFunc> TestFuncTraits;
//	LE_ASSERT((TSTypesEqual<TestFuncTraits::RetType, int>::value));
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void CGeneralTestSuite::testPreprocessor()
{
	LE_ASSERT(LE_PP_OR(2, 3));
	LE_ASSERT(LE_PP_OR(3, 0));
	LE_ASSERT(LE_PP_NOT(LE_PP_OR(0, 0)));
	LE_ASSERT(LE_PP_IF(5, 1, error));
	LE_ASSERT(LE_PP_IF(LE_PP_AND(3, 6), 1, error));

	LE_ASSERT(LE_PP_EQUAL(5, 5));
	LE_ASSERT(LE_PP_NOT_EQUAL(5, 6));


#define LE_TEST_FOR_PREDICATE(current) LE_PP_NOT_EQUAL(current, 2)
#define LE_TEST_FOR_ACTION(current) current

// TODO: Rework LE_PP_FOR to compile on MSVC without "macros nested too deeply" error
//		and to allow "," (comma) in expressions.
//	std::cout << LE_PP_FOR(1, LE_TEST_FOR_PREDICATE, LE_TEST_FOR_ACTION) << std::endl;
//	LE_ASSERT(CString(1234) == LE_STR(LE_PP_FOR(1, LE_TEST_FOR_PREDICATE, LE_TEST_FOR_ACTION)));

#undef LE_TEST_FOR_PREDICATE
#undef LE_TEST_FOR_ACTION

}

	} // namespace le
} // namespace sokira
