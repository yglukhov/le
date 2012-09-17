#include <le/core/debug/slDebug.h>
#include <le/core/template/function/slTCFunction.h>
#include <le/core/template/function/slTCBind.h>
#include <le/core/slCAny.h>
#include <le/core/auxiliary/slCBundle.h>

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

template <class TEnumerationContext>
struct EnumerateTypeList
{
	static void f()
	{
		std::cout << "type " << TEnumerationContext::I << ": " << typeid(typename TEnumerationContext::T).name() << std::endl;
		TEnumerationContext::Next::f();
	}
};

template <>
struct EnumerateTypeList<_SNullType>
{
	static void f()
	{
		std::cout << "type ZZZZZ" << std::endl;
	}
};

void CGeneralTestSuite::testTypeList()
{
	LE_ENTER_LOG;

	typedef TSTypeList<i2t<5>, i2t<4>, i2t<3>, i2t<2>, i2t<1>, i2t<0>, i2t<7>,
						i2t<-2>, i2t<0>, i2t<1>, i2t<2>, i2t<3>, i2t<4>, i2t<5>,
						i2t<-1>, i2t<10>, i2t<-3> > unsortedList;
	typedef unsortedList::SortDes<TSSortTestPredicate>::result sortedList;

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

	typedef unsortedList::CollectIf<TCollectorPredicate>::result collection;
	LE_ASSERT(collection::TypeAt<0>::result::value == 4);
	LE_ASSERT(collection::TypeAt<1>::result::value == 3);
	LE_ASSERT(collection::TypeAt<2>::result::value == 3);
	LE_ASSERT(collection::TypeAt<3>::result::value == 4);

	typedef unsortedList::CollectMutantsIf<TCollectorPredicate>::result mutatedCollection;
	LE_ASSERT(mutatedCollection::TypeAt<0>::result::value == 9);
	LE_ASSERT(mutatedCollection::TypeAt<1>::result::value == 8);
	LE_ASSERT(mutatedCollection::TypeAt<2>::result::value == 8);
	LE_ASSERT(mutatedCollection::TypeAt<3>::result::value == 9);

	typedef TSTypeList<>::PushBack<i2t<0> >::result pushBackedTypeList1;
	LE_ASSERT(pushBackedTypeList1::length == 1);

	typedef pushBackedTypeList1::PushBack<i2t<1> >::result pushBackedTypeList2;
	LE_ASSERT(pushBackedTypeList2::length == 2);

	typedef pushBackedTypeList2::PushBack<i2t<2> >::result pushBackedTypeList3;
	LE_ASSERT(pushBackedTypeList3::length == 3);

	typedef pushBackedTypeList3::PushBack<i2t<3> >::result pushBackedTypeList4;
	LE_ASSERT(pushBackedTypeList4::length == 4);

	typedef TSTypeList<int, float, int> TypeList1;
	typedef TSTypeList<int, float>::PushBack<int>::result TypeList2;

	LE_ASSERT((TSTypesEqual<TypeList1::TypeAt<0>::result,
							TypeList2::TypeAt<0>::result>::value));
	LE_ASSERT((TSTypesEqual<TypeList1::TypeAt<1>::result,
							TypeList2::TypeAt<1>::result>::value));
	LE_ASSERT((TSTypesEqual<TypeList1::TypeAt<2>::result,
							TypeList2::TypeAt<2>::result>::value));

	typedef TypeList2::PopFront::PushBack<float>::result TypeList3;

	LE_ASSERT(!(TSTypesEqual<TypeList1::TypeAt<0>::result,
			   TypeList3::TypeAt<0>::result>::value));
	LE_ASSERT(!(TSTypesEqual<TypeList1::TypeAt<1>::result,
			   TypeList3::TypeAt<1>::result>::value));
	LE_ASSERT(!(TSTypesEqual<TypeList1::TypeAt<2>::result,
			   TypeList3::TypeAt<2>::result>::value));


	typedef TSTypeList<float, int, float> TypeList4;
	LE_ASSERT((TSTypesEqual<TypeList3::TypeAt<0>::result,
			   TypeList4::TypeAt<0>::result>::value));
	LE_ASSERT((TSTypesEqual<TypeList3::TypeAt<1>::result,
			   TypeList4::TypeAt<1>::result>::value));
	LE_ASSERT((TSTypesEqual<TypeList3::TypeAt<2>::result,
			   TypeList4::TypeAt<2>::result>::value));

	typedef TypeList4::Insert<1, double>::result TypeList5;
	LE_ASSERT((TSTypesEqual<TypeList5::TypeAt<0>::result, float>::value));
	LE_ASSERT((TSTypesEqual<TypeList5::TypeAt<1>::result, double>::value));
	LE_ASSERT((TSTypesEqual<TypeList5::TypeAt<2>::result, int>::value));
	LE_ASSERT((TSTypesEqual<TypeList5::TypeAt<3>::result, float>::value));

	LE_ASSERT(TypeList5::Find<double>::result == 1);
	LE_ASSERT(TypeList5::Find<int>::result == 2);


//	TypeList4::Enumerate<EnumerateTypeList>::f();
//	TSTypeList<>::Enumerate<EnumerateTypeList>::f();
//	mutatedCollection::Enumerate<EnumerateTypeList>::f();
//	TSEnumerateTypeList<TypeList4, EnumerateTypeList>::f();
//	LE_ASSERT((TSTypesEqual<TSTypeList<>, TSTypeList<>::EraseAt<0> >::value));
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

		void voidFunc()
		{
			mTestValue = 5;
		}
	
		void someConstFunc(int a) const
		{
			mMutableTestValue = a;
		}

		TCFunction<int, TSTypeList<int> > mFunctor;
		UInt32 mTestValue;
		mutable int mMutableTestValue;
};

void CGeneralTestSuite::testBinds()
{
	LE_ENTER_LOG;
	A objA;

	objA.mFunctor = bind(testFunc, 10, bindTo(0));
	LE_ASSERT(objA.mFunctor(5) == 10);

	TCFunction<int, TSTypeList<A*, int> > func = bind(&A::memberOfA, bindTo(0), bindTo(1));
	LE_ASSERT(func(&objA, 5) == 10);

	TCFunction<int, TSTypeList<A*, int> > func2 = func;
	LE_ASSERT(func2(&objA, 12) == 12);

	TCFunction<int> func3 = bind(func2, &objA, 8);
	LE_ASSERT(func3() == 10);

	objA.mFunctor = bind(testFunc, 5, bindTo(0));
	LE_ASSERT(func3() == 8);

	objA.mTestValue = 0;
	TCFunction<> func4 = bind(&A::voidFunc, &objA);
	func4();
	LE_ASSERT(objA.mTestValue == 5);

	TCFunction<void, TSTypeList<int> > func5 = bind(&A::someConstFunc, &objA, bindTo(0));
	func5(15);
	LE_ASSERT(objA.mMutableTestValue == 15);
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void CGeneralTestSuite::testTuples()
{
	LE_ENTER_LOG;

	{
		TCTuple<TSTypeList<int, float, int> > tuple;
		tuple.setValue<0>(5);
		tuple.setValue<2>(6);
		tuple.setValue<1>(3.1f);
		LE_ASSERT(tuple.value<0>() == 5);
		LE_ASSERT(tuple.value<1>() > 3.0f && tuple.value<1>() < 3.2f);
		LE_ASSERT(tuple.value<2>() == 6);
	}

	{
		// Reference tuple
		CString str = "Hello";
		TCTuple<TSTypeList<CString&> > refTuple;
		refTuple.setValue<0>(str);
		refTuple.value<0>().append(LESTR(", world!"));
		LE_ASSERT(str == "Hello, world!");
	}

	{
		int a = 123;
		void* somePtr = &a;
		TCTuple<TSTypeList<void*> > tuple;
		tuple.setValue<0>(somePtr);
		TCTuple<TSTypeList<void*> > otherTuple;
		otherTuple.setValue<0>(tuple.value<0>());
		LE_ASSERT(*((int*)otherTuple.value<0>()) == 123);
	}
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

	str = CString::createWithFormat("%f", (double) 1.0);
	LE_ASSERT(str == "1.000000");

	str = "\t\n  test";
	str.trimWhitespace();
	LE_ASSERT(str == "test");

	str = "test    ";
	str.trimWhitespace();
	LE_ASSERT(str == "test");

	str = "\n  test s  ";
	str.trimWhitespace();
	LE_ASSERT(str == "test s");

	str.trimWhitespace();
	LE_ASSERT(str == "test s");

	str.clear();
	str.trimWhitespace();
	LE_ASSERT(str.isEmpty());

	str = "Bar Hi Foo Hi";
	CString pattern = "Hi";
	LE_ASSERT(str.find(pattern) == 4);
	LE_ASSERT(str.findLast(pattern) == 11);
	pattern = "Hi not found!";
	LE_ASSERT(str.find(pattern) == -1);
	LE_ASSERT(str.findLast(pattern) == -1);
	pattern = "Bar";
	LE_ASSERT(str.find(pattern) == 0);
	LE_ASSERT(str.findLast(pattern) == 0);

	LE_ASSERT(str.subString(0, 3) == "Bar");
	LE_ASSERT(str.subString(4, 2) == "Hi");
	LE_ASSERT(str.subString(11, 2) == "Hi");
	LE_ASSERT(str.subString(7, 0) == "Foo Hi");
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void CGeneralTestSuite::testUrls()
{
	CURL url("/Applications/iTunes.app/Contents/MacOS/iTunes");
	LE_ASSERT(url.lastPathComponent() == "iTunes");
	url = CURL("/Applications/iTunes.app/Contents/MacOS/iTunes/");
	LE_ASSERT(url.lastPathComponent().isEmpty());
	url = CURL("asdf");
	LE_ASSERT(url.lastPathComponent() == "asdf");

	url = CURL("/Applications/iTunes.app/Contents/MacOS/iTunes");
	url.removeLastPathComponent();
	LE_ASSERT(url.path() == "/Applications/iTunes.app/Contents/MacOS");

	url = CURL("/Applications/iTunes.app/Contents/MacOS/iTunes");
	url.removeLastPathComponents(3);
	LE_ASSERT(url.path() == "/Applications/iTunes.app");

	url = CURL("/Applications/iTunes.app/Contents/MacOS/iTunes");
	url.removeLastPathComponents(15);
//	std::cout << "URL: " << url.path() << std::endl;
	LE_ASSERT(url.path() == "");

	url = CURL("/Applications/iTunes.app/Contents/MacOS/iTunes");
	url.removeLastPathComponents(4);
//	std::cout << "URL: " << url.path() << std::endl;
	LE_ASSERT(url.path() == "/Applications");

	url = CURL("/Applications/iTunes.app/Contents/MacOS/iTunes");
	url.removeLastPathComponents(5);
//	std::cout << "URL: " << url.path() << std::endl;
	LE_ASSERT(url.path() == "");

	url = CURL("/");
	url.removeLastPathComponent();
//	std::cout << "URL: " << url.path() << std::endl;
	LE_ASSERT(url.path() == "");

	CBundle bundle(CURL("/Applications/iTunes.app/Contents/MacOS/iTunes"));
//	LE_ASSERT(bundle.resourcesUrl() == CURL("/Applications/iTunes.app/Contents/Resources"));
	//LE_ASSERT(bundle.infoPlistUrl() == CURL("/Applications/iTunes.app/Contents/Info.plist"));
	//LE_ASSERT(bundle.contentsUrl() == CURL("/Applications/iTunes.app/Contents"));
}

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void CGeneralTestSuite::testFunctionTraits()
{
//	typedef Traits<MyTestFunc> TestFuncTraits;
//	LE_ASSERT(TestFuncTraits::value);
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

////////////////////////////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////////////////////////////
void CGeneralTestSuite::testAny()
{
	int i = 2;
	CAny any = i;

	LE_ASSERT(any.value<int>() == i);
	LE_ASSERT(any.value<int &>() == i);

	any.value<int&>() = 6;

	LE_ASSERT(any.value<int>() == 6);

	any = CAny::ref(i);
	LE_ASSERT(any.value<int&>() == i);

	i = 123;
	LE_ASSERT(any.value<int>() == i);

	any.value<int&>() = 321;
	LE_ASSERT(any.value<int>() == i);

	const int j = 123;
	any = j;

	LE_ASSERT(any.value<int>() == j);
	LE_ASSERT(any.value<int &>() == j);

	any.value<int &>() = 321;
	LE_ASSERT(any.value<const int>() == 321);

	any = CAny::constRef(j);
	LE_ASSERT(any.value<int>() == j);

	LE_ASSERT(any.value<int &>() == j);
	any.value<int &>() = 321;

	const CString str = "hi!";
	any = CAny::constRef(str);

	any.value<CString&>() = "qwer";
//
//	std::cout << any.value<CString&>() << std::endl;
//	std::cout << str << std::endl;
}

	} // namespace le
} // namespace sokira
