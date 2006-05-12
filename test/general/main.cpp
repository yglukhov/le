
#define FUNCTORS_TESTING 1

#pragma comment(lib, "leCommon")
#pragma comment(lib, "leGui")

#if FUNCTORS_TESTING

#include <template/function/slTCFunction.h>
#include <template/function/slTCBind.h>
#include <iostream>

void f(int a)
{
	std::cout << "f(" << a << ");" << std::endl;
}

template <int i>
struct i2t
{
	static void f()
	{
		std::cout << i << std::endl;
	}
};

template <typename T1, typename T2>
struct Predicate
{

};

template <int i, int j>
struct Predicate <i2t<i>, i2t<j> >
{
	enum { result = (i < j)?(-1):((i > j)?(1):(0)) };
};

class A
{
	public:
		void memberOfA(int a)
		{
			std::cout << "memberOfA(" << a << ")" << std::endl;
		}
};

int main(int argc, char * const argv[])
{
//	using namespace le;

	std::cout << "Typelist sorting" << std::endl;
	
	typedef TSTypeList<i2t<5>, i2t<4>, i2t<3>, i2t<2>, i2t<1>, i2t<0>, i2t<-1>, i2t<-2>,
						i2t<5>, i2t<4>, i2t<3>, i2t<2>, i2t<1>, i2t<0>, i2t<-1>, i2t<-2>, i2t<-3> > unsortedList;
	typedef unsortedList::SortDes<Predicate>::result sortedList;

	unsortedList::TypeAt<0>::result::f();
	unsortedList::TypeAt<1>::result::f();
	unsortedList::TypeAt<2>::result::f();
	unsortedList::TypeAt<3>::result::f();
	unsortedList::TypeAt<4>::result::f();
	unsortedList::TypeAt<5>::result::f();
	unsortedList::TypeAt<6>::result::f();
	unsortedList::TypeAt<7>::result::f();
	unsortedList::TypeAt<8>::result::f();
	unsortedList::TypeAt<9>::result::f();
	unsortedList::TypeAt<10>::result::f();
	unsortedList::TypeAt<11>::result::f();
	unsortedList::TypeAt<12>::result::f();
	unsortedList::TypeAt<13>::result::f();
	unsortedList::TypeAt<14>::result::f();
	unsortedList::TypeAt<15>::result::f();
	unsortedList::TypeAt<16>::result::f();

	std::cout << "---------" << std::endl;

	sortedList::TypeAt<0>::result::f();
	sortedList::TypeAt<1>::result::f();
	sortedList::TypeAt<2>::result::f();
	sortedList::TypeAt<3>::result::f();
	sortedList::TypeAt<4>::result::f();
	sortedList::TypeAt<5>::result::f();
	sortedList::TypeAt<6>::result::f();
	sortedList::TypeAt<7>::result::f();
	sortedList::TypeAt<8>::result::f();
	sortedList::TypeAt<9>::result::f();
	sortedList::TypeAt<10>::result::f();
	sortedList::TypeAt<11>::result::f();
	sortedList::TypeAt<12>::result::f();
	sortedList::TypeAt<13>::result::f();
	sortedList::TypeAt<14>::result::f();
	sortedList::TypeAt<15>::result::f();
	sortedList::TypeAt<16>::result::f();

	std::cout << std::endl << "Member bind testing" << std::endl;

	A objA;

	TCFunction<void, TSTypeList<A*, int> > func = bind(&A::memberOfA, bindTo(0), bindTo(1));

	func(&objA, 5);
	
	/*TCFunction<void, TSTypeList<A*> > func2 = func;
	
	func(&objA);
	func2(&objA);

	TCFunction<> func3 = bind(func2, &objA);
	func3();*/

	return 1;
}

#else // FUNCTORS_TESTING

#pragma comment(lib, "leGui")
#pragma comment(lib, "leCommon")
#pragma comment(lib, "leAux")
#pragma comment(lib, "leFile")
#pragma comment(lib, "leThread")

#include <gui/slCApplication.h>


int main(int argc, char * const argv[])
{
	LE_NESTED_NAMESPACE CApplication theApplication;
	return theApplication.run(argc, argv);
}

#endif // not FUNCTORS_TESTING
