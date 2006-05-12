#pragma once

#include <common/config/slPrefix.h>
#include <common/pointer/slTCPointer.h>

LE_NAMESPACE_START

class CObject;

class CClassFactory
{
	public:
		static TCPointer<CObject> create(const char* className);

		template <class TCastTo>
		static TCPointer<TCastTo> create(const char* className);
};

template <class TCastTo>
TCPointer<TCastTo> CClassFactory::create(const char* className)
{
	return TCPointer<TCastTo>(dynamic_cast<TCastTo*>(create(className).get()));
}

LE_NAMESPACE_END
