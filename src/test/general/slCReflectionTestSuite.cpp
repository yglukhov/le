
#include <typeinfo>
#include <le/core/slCString.h>
#include "slCReflectionTestSuite.h"
#include <le/core/slCDictionary.h>

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
		LE_RTTI_SELECTOR_WITH_TYPE(testFunc, int, (int))
		LE_RTTI_SELECTOR_WITH_TYPE_NAME(testFunc, voidTestFunc, void, (void))
	LE_RTTI_END

	public:
		void testFunc();
		int testFunc(int);
		void testFunc2() const;
		void testFunc3(int);

		virtual void serialize(CDictionary& dict) const
		{
			dict.setValueForKey(LESTR("SomeKey"), CString(LESTR("SomeValue")));
		}
};

LE_IMPLEMENT_RUNTIME_CLASS(TestClass);

void TestClass::testFunc()
{
	std::cout << "hi(void)" << std::endl;
}

int TestClass::testFunc(int a)
{
	std::cout << "hi: " << a << std::endl;
	return a + 5;
}

void TestClass::testFunc2() const
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
	
	CDictionary dict;
	testObj.selector("serialize")(dict);
	LE_ASSERT(dict.valueAsStringForKey("SomeKey") == "SomeValue");

	std::cout << "WILL CALL test func!!" << std::endl;

//	std::cout << "Result: " <<
	testObj.selector("testFunc2")(5);
	testObj.selector("testFunc3")(5);

	std::cout << "DID CALL test func!!" << std::endl;


	CClass testClass = TestClass2::staticClass();
	std::set<ISelector*> selectors = testClass.selectors();

	std::cout << "Selectors: " << std::endl;
	for (std::set<ISelector*>::iterator it = selectors.begin(); it != selectors.end(); ++it)
	{
		std::cout << "Selector: " << (*it)->name() << std::endl;
	}

	std::vector<CClass> parents = testClass.parents();
	for (std::vector<CClass>::iterator it = parents.begin(); it != parents.end(); ++it)
	{
		std::cout << "parent: " << it->name() << std::endl;
	}

	LE_ASSERT(testObj.selector("voidTestFunc").isVoid());
	LE_ASSERT(!testObj.selector("testFunc").isVoid());
	
	LE_ASSERT(testObj.respondsToSelector("testFunc"));
	LE_ASSERT(testObj.respondsToSelector("voidTestFunc"));
	LE_ASSERT(testObj.respondsToSelector("testFunc2"));
	LE_ASSERT(testObj.respondsToSelector("testFunc3"));
	LE_ASSERT(!testObj.respondsToSelector("someNonexistentFunc"));

//	class AbraCadabra;
//
//	std::cout << "Typeof int: " << typeid(AbraCadabra).name() << std::endl;
//	std::cout << "Typeof int&: " << typeid(const int&).name() << std::endl;
}

static std::set<CString> classNamesFromClasses(const std::vector<CClass>& classes)
{
	std::set<CString> result;
	for (std::vector<CClass>::const_iterator it = classes.begin(); it != classes.end(); ++it)
	{
		result.insert(it->name());
	}
	return result;
}

void CReflectionTestSuite::testInheritance()
{
	std::set<CString> parents = classNamesFromClasses(TestClass::staticClass().parents());

	std::set<CString> validValue;
	validValue.insert("CObject");

	LE_ASSERT(validValue == parents);


	parents = classNamesFromClasses(TestClass2::staticClass().parents());

	validValue.clear();
	validValue.insert("TestClass");
	LE_ASSERT(validValue == parents);

	LE_ASSERT(TestClass2::staticClass().isChildOfStdClass(typeid(TestClass)));
	LE_ASSERT(TestClass2::staticClass().isChildOfStdClass(typeid(CObject)));
	LE_ASSERT(TestClass::staticClass().isChildOfStdClass(typeid(CObject)));
	LE_ASSERT(!TestClass::staticClass().isChildOfStdClass(typeid(TestClass2)));
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
