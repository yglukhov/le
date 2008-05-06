#pragma comment(lib, "leCore")
#pragma comment(lib, "leGui")

#include <iostream>
#include <le/gui/slCApplication.h>

int main(int argc, char * const argv[])
{
	::sokira::le::CApplication theApplication;
	theApplication.run(argc, argv);
	std::cout << "EXITING" << std::endl;
	return 0;
}
