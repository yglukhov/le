#pragma once

#include "slCView.h"
#include "slCDragger.h"
#include "slCControlDelegate.h"
#include "slCText.h"

namespace sokira
{
	namespace le
	{

class CButton;

class CTitleBar: public CView, private CDragger, public CControlDelegate
{
	LE_DECLARE_RUNTIME_CLASS(CTitleBar);

	public:
		CTitleBar();
		CTitleBar(CView* parent);

		virtual bool onMouseLeftDown(const CPoint& point, CControl* sender);
		virtual bool onMouseLeftUp(const CPoint& point, CControl* sender);

		void caption(const char* captionString);

		const CText& captionText() const;

	protected:
		CButton*	mCloseButton;
		CText mCaption;
};

	} // namespace le
} // namespace sokira
