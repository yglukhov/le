#pragma once

#include "CObject.h"

class IClass
{
	public:
		virtual const char* name() const = 0;
		virtual CObject::Ptr create() const = 0;
};