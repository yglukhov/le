#include "CBorderDecorator.h"

CBorderDecorator::CBorderDecorator(CControl* child, float borderWidth) :
	CDecorator(child), mBorderWidth(borderWidth)
{
	if(child)
	{
		mRect.width(mRect.width() + 2*mBorderWidth);
		mRect.width(mRect.width() + 2*mBorderWidth);
	}
}