#include "slCReflectionTestSuite.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CReflectionTestSuite);

class TestClass: public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(TestClass)
		LE_RTTI_SINGLE_PUBLIC_PARENT
//		LE_RTTI_SELECTOR(testFunc)
		LE_RTTI_SELECTOR(testFunc2)
		LE_RTTI_SELECTOR(testFunc3)
		LE_RTTI_SELECTOR_WITH_TYPE(testFunc, void, (int))
		LE_RTTI_SELECTOR_WITH_TYPE_NAME(testFunc, voidTestFunc, void, (void))
	LE_RTTI_END

	public:
		void testFunc();
		void testFunc(int);
		void testFunc2();
		void testFunc3(int);
};

LE_IMPLEMENT_RUNTIME_CLASS(TestClass);

void TestClass::testFunc()
{
	std::cout << "hi" << std::endl;
}

void TestClass::testFunc(int)
{
	std::cout << "hi" << std::endl;
}

void TestClass::testFunc2()
{
	std::cout << "hi2" << std::endl;
}

void TestClass::testFunc3(int a)
{
	std::cout << "hi" << a << std::endl;
}

class TestClass2: public TestClass
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(TestClass2)
		LE_RTTI_SINGLE_PUBLIC_PARENT
		LE_RTTI_SELECTOR(test2Func)
		LE_RTTI_SELECTOR(test2Func2)
		LE_RTTI_SELECTOR(test2Func3)
//		LE_RTTI_SELECTOR_WITH_TYPE(testFunc, testFunc, void, (int))
//		LE_RTTI_SELECTOR_WITH_TYPE(testFunc, void, (void))
	LE_RTTI_END

	public:
		void test2Func();
		void test2Func2();
		void test2Func3(int);
};

LE_IMPLEMENT_RUNTIME_CLASS(TestClass2);

void TestClass2::test2Func()
{
	std::cout << "hi" << std::endl;
}

void TestClass2::test2Func2()
{
	std::cout << "hi2" << std::endl;
}

void TestClass2::test2Func3(int a)
{
	std::cout << "hi" << a << std::endl;
}


void CReflectionTestSuite::testSelectors()
{
	TestClass testObj;
	testObj.testFunc();
//	testObj.selector("testFunc")();

	CClass testClass = TestClass2::staticClass();
	std::set<ISelector*> selectors = testClass.selectors();

	for (std::set<ISelector*>::iterator it = selectors.begin(); it != selectors.end(); ++it)
	{
		std::cout << "Selector: " << (*it)->name() << std::endl;
	}

	std::vector<CClass> parents = testClass.parents();
	for (std::vector<CClass>::iterator it = parents.begin(); it != parents.end(); ++it)
	{
		std::cout << "parent: " << it->name() << std::endl;
	}
	
}

class CAnimation
{
	void setBlocking(bool);
	void setProgressBounds(float start, float end);
	void setAnimationCurve(int);
	void setNumberOfLoops(int);
	void setDuration(float seconds);
//	void setAnimationCallback(TCFunction<void, TSTypeList<CAnimation*> >& function);
	void start();
};

	} // namespace le
} // namespace sokira
