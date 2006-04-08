
#define FUNCTORS_TESTING 1

#if FUNCTORS_TESTING

#include <function/TCFunction.h>
#include <function/TCBind.h>
#include <iostream>

void f(int a)
{
	std::cout << "f(" << a << ");" << std::endl;
}

int main(int argc, char * const argv[])
{
	TCFunction<void, TSTypeList<int> > func1 = f;
	func1(5);

	TCFunction<void, TSTypeList<int, float, int> > func2 = bind(f, bindTo(2));
	func2(4, 5.0f, 7);

	TCFunction<void, TSTypeList<int> > func3 = bind(func2, 1, 5.0f, bindTo(0));
	func3(9);

	return 1;
}

#else // FUNCTORS_TESTING

#include "CApplication.h"

int main(int argc, char * const argv[])
{
	CApplication theApplication;
	return theApplication.run(argc, argv);
}

#endif // not FUNCTORS_TESTING
