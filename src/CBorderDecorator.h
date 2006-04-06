#pragma once

#include "CDecorator.h"

class CBorderDecorator : public CDecorator
{
	public:
		CBorderDecorator(CControl* child, float borderWidth = 0.0);
	
	private:
		float mBorderWidth;
};