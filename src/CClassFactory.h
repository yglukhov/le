#pragma once

#include "TCPointer.h"

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