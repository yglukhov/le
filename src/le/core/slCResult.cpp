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
	mErrorCode(!success)
{
}

CResult::CResult(SInt32 code) :
	mErrorCode(code)
{
}

CResult::CResult(const CString& errorDescription, SInt32 errorCode) :
	mErrorDescription(errorDescription),
	mErrorCode(errorCode)
{
}

CResult::CResult(const NChar* errorDescription, SInt32 errorCode) :
	mErrorDescription(errorDescription),
	mErrorCode(errorCode)
{
}

CResult::CResult(const WChar* errorDescription, SInt32 errorCode) :
	mErrorDescription(errorDescription),
	mErrorCode(errorCode)
{
}

CResult::CResult(const CResult& copy) :
	mErrorDescription(copy.mErrorDescription),
	mErrorCode(copy.mErrorCode)
{
}

const CResult& CResult::operator=(const CResult& copy)
{
	mErrorCode = copy.mErrorCode;
	mErrorDescription = copy.mErrorDescription;
	return *this;
}

CResult::operator Bool() const
{
	return !mErrorCode;
}

CString CResult::description() const
{
	return mErrorDescription;
}

SInt32 CResult::errorCode() const
{
	return mErrorCode;
}

void CResult::throwIfFailure() const
{
	if (!*this)
	{
		throw *this;
	}
}

	} // namespace le
} // namespace sokira
