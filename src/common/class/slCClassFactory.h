#pragma once

#include <common/config/slPrefix.h>
#include <common/pointer/slTCPointer.h>
#include <common/types/slCString.h>

LE_NAMESPACE_START

class CObject;

class CClassFactory
{
	public:
		static TCPointer<CObject> create(CString className);

		template <class TCastTo>
		static TCPointer<TCastTo> create(CString className);
};

template <class TCastTo>
TCPointer<TCastTo> CClassFactory::create(CString className)
{
	return TCPointer<TCastTo>(dynamic_cast<TCastTo*>(create(className).get()));
}

LE_NAMESPACE_END
