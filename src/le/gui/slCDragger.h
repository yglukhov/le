#pragma once

#include <le/core/geometry/slTCPoint2D.h>
#include "slTypes.h"

namespace sokira
{
	namespace le
	{

class CControl;

class CDragger
{
	public:
		CDragger(CControl* controlToDrag, CControl* dragHandler);

		void startDrag(const CPoint& point);
		void drag(const CPoint& point);
		void endDrag();

		CControl* handler();

		static CDragger* currentDragger();

	protected:
		CControl* mControl;
		CControl* mHandler;
		CPoint mDragPoint;
};

	} // namespace le
} // namespace sokira
