#include "slCReflectionTestSuite.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CReflectionTestSuite);

#define _LE_PP_NOTHING

class TestClass: public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(TestClass)
		LE_RTTI_SINGLE_PUBLIC_PARENT
		LE_RTTI_SELECTOR(testFunc)
//		LE_RTTI_SELECTOR_WITH_TYPE(testFunc, testFunc, void, (int))
//		LE_RTTI_SELECTOR_WITH_TYPE(testFunc, void, (void))
	LE_RTTI_END

	public:
		void testFunc();
//		void testFunc(int);
};

LE_IMPLEMENT_RUNTIME_CLASS(TestClass);

void TestClass::testFunc()
{
	std::cout << "hi" << std::endl;
}

//void TestClass::testFunc(int a)
//{
//	std::cout << "hi" << std::endl;
//}

void CReflectionTestSuite::testSelectors()
{
	TestClass testObj;
	testObj.testFunc();
//	testObj.selector("testFunc")();
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
