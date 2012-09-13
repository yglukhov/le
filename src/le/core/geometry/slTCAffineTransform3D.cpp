//
//  File.cpp
//  le
//
//  Created by Yuriy Glukhov on 8/23/12.
//
//

#include <le/core/slCAny.h>
#include <le/core/template/function/slTCFunction.h>
#include <le/core/template/function/slTCBind.h>
#include <le/core/template/function/slTCVariadicFunction.h>

#include "slTCAffineTransform3D.h"

using namespace ::sokira::le;

void f(int i)
{
	std::cout << "f: " << i << std::endl;
}

void ff()
{
	std::cout << "f" << std::endl;
}

template <class TTypeList>
struct SMyVariadicFunctionResult
{
	typedef void result;
};

struct SMyAnotherVariadicFunction
{
	template <class TTypeList>
	struct TResult
	{
		typedef void result;
	};

	template <class TTypeList>
	typename TResult<TTypeList>::result operator()(const TCTuple<TTypeList>& tuple)
	{
		std::cout << "Args count: " << TTypeList::length << std::endl;
	}
};

struct SMyVariadicFunction : public TCVariadicFunctionMixin<SMyVariadicFunction, SMyVariadicFunctionResult, true>
{
	using TVariadic::operator();
//	template <class TTypeList>
//	struct TResult
//	{
//		typedef void result;
//	};

	template <class TTypeList>
	typename SMyVariadicFunctionResult<TTypeList>::result operator()(const TCTuple<TTypeList>& tuple) const
	{
		std::cout << "Args count: " << TTypeList::length << std::endl;
	}
};

struct SMyAnyVariadicFunction
{
	template <class TTypeList>
	struct TResult
	{
		typedef void result;
	};

	void operator()(const std::vector<CAny>& arguments)
	{
		std::cout << "Arg count: " << arguments.size() << std::endl;
		for (std::vector<CAny>::const_iterator it = arguments.begin(); it != arguments.end(); ++it)
		{
			std::cout << "Arg: " << it->value<int>() << std::endl;
		}
	}
};


//static TCVariadicFunction<SMyVariadicFunction> myVariadicFunction;
static TCAnyVariadicFunction<SMyAnyVariadicFunction, std::vector<CAny> > myAnyVariadicFunction;

static SMyVariadicFunction myVariadicFunction;
static TCVariadicFunction<SMyAnotherVariadicFunction> myAnotherVariadicFunction;

struct B
{
	private:
	B()
	{
		std::cout << "B::private called" << std::endl;
	}
};

struct A
{
	void fillMatrix(float* m)
	{
		for (int i = 0; i < 16; ++i)
		{
			m[i] = rand() % 10;
		}
	}

	void testFunc(int a)
	{
		std::cout << "tetFunc(" << a << ")" << std::endl;
	}

	void testFunc2()
	{
		std::cout << "tetFunc()" << std::endl;
	}

	A()
	{
	//	TResult<SMyVariadicFunction, TSTypeList<> >::result t;
//		myVariadicFunction();
//		myVariadicFunction(2);
//		myAnotherVariadicFunction(2);
//		std::cout << "A constructible: " << TSTypeHasDefaultConstructor<A>::value << std::endl;
//		std::cout << "B constructible: " << TSTypeHasDefaultConstructor<B>::value << std::endl;
//		_TSTypeHasDefaultConstructor<B>::sfinae(0);
//		TCFreeFunction<void(*)()> tet(ff);
//		tet();
//		TCFunction<void, TSTypeList<int> > tet(f);
//		tet(3);
//		TCFunction<void, TSTypeList<int> > f = bind(&A::testFunc, this, bindTo(0));
//		f(7);

//		TCTuple<TSTypeList<> > tuple;
		
//		CAny any(5);
//		CAny any2 = any;
//		std::cout << any.value<int>() << std::endl;
//		
//		myAnyVariadicFunction(5, 5, 3, 2, 8);
//
//
//		Float32 m[16];
//		fillMatrix(m);
//		CAffineTransform3D trans1;
//		trans1.setIdentity();
//		std::cout << "identity: " << std::endl;
//		std::cout << trans1;
//
//		
////		memcpy(&trans, m, sizeof(trans));
//		trans1.rotate(2.0f, 3.0f, 4.0f);
//		CAffineTransform3D trans2;
//		trans2.setIdentity();
////		memcpy(&trans2, m, sizeof(trans));
////		trans2.translate(2.0f, 3.0f, 4.0f);
//
//		CAffineTransform3D translation;
//		translation.setRotation(2.0f, 3.0f, 4.0f);
//
//
//		trans2 *= translation;
//
//		std::cout << "trans1: " << std::endl;
//		std::cout << trans1;
//
//		std::cout << "trans2: " << std::endl;
//		std::cout << trans2;
//
//		std::cout << "Equal: " << !memcmp(&trans1, &trans2, sizeof(trans1)) << std::endl;
	}

} a;
