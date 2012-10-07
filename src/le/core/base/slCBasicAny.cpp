//
//  slCBasicAny.cpp
//  le
//
//  Created by Yuriy Glukhov on 9/5/12.
//
//

#include <iostream>
#include "slCBasicAny.h"

namespace sokira
{
	namespace le
	{
	
CBasicAny::CBasicAny() :
	mValue(NULL)
{
//	std::cout << "default constructor\n";
}

CBasicAny::CBasicAny(const CBasicAny& copy) :
	mValue(copy.mValue ? copy.mValue->copy() : NULL)
{
//	std::cout << "copy constructor\n";
}

CBasicAny::CBasicAny(IAnyContainer* container) :
	mValue(container)
{

}

const CBasicAny& CBasicAny::operator = (const CBasicAny& copy)
{
//	std::cout << "copy =\n";
	mValue = copy.mValue->copy();
	return *this;
}


	} // namespace le
} // namespace sokira
