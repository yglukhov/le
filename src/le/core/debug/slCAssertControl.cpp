/*
 *  slCAssertControl.cpp
 *  le
 *
 *  Created by Yuriy Glukhov on 1/26/08.
 *  Copyright 2008 __MyCompanyName__. All rights reserved.
 *
 */

#include "slCAssertControl.h"
#include "slCAssertionPolicy.h"

namespace sokira
{
	namespace le
	{


CAssertControl::CAssertControl() :
	mPolicy(new CAssertionPolicy())
{

}

CAssertControl::~CAssertControl()
{
	delete mPolicy;
}


CAssertionPolicy *CAssertControl::assertionPolicy() const
{
	return mPolicy;
}

void CAssertControl::setAssertionPolicy(CAssertionPolicy *policy)
{
	delete mPolicy;
	mPolicy = policy;
}

	} // namespace le
} // namespace sokira
