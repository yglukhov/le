#include "slCGeneralTestSuite.h"

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CGeneralTestSuite);

bool CGeneralTestSuite::runTest()
{
	std::cout << "runTest() called" << std::endl;
	return true;
}

	} // namespace le
} // namespace sokira
