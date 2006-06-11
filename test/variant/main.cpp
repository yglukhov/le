
#include <iostream>
#include <common/types/slCVariant.h>
#include <common/types/slCNumber.h>

int main(int argc, char * const argv[])
{
	SInt1 SInt1Value = 5;
	CVariant varUInt1 = SInt1Value;

	Float4 fVal= 0.6f;

	varUInt1 = fVal;

	CNumber number = varUInt1.value<CNumber>();

	std::cout << number.valueAsUInt8() << std::endl;
	return 0;
}
