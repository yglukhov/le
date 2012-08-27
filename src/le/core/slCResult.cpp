//
//  slCResult.cpp
//  le
//
//  Created by Yuriy Glukhov on 8/31/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "slCResult.h"


namespace sokira
{
	namespace le
	{
		
CResult::CResult(Bool success) :
	mSuccess(success)
{

}

CResult::CResult(const CString& errorDescription) :
	mSuccess(false),
	mErrorDescription(errorDescription)
{

}

CResult::operator Bool() const
{
	return mSuccess;
}

CString CResult::errorDescription() const
{
	return mErrorDescription;
}

	} // namespace le
} // namespace sokira
