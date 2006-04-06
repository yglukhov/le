#pragma once

#include "CWindow.h"
#include "CDragger.h"
#include "CControlDelegate.h"
#include "CText.h"


class CButton;

class CTitleBar: public CWindow, private CDragger, public CControlDelegate
{
	DECLARE_RUNTIME_CLASS(CTitleBar);

	public:
		CTitleBar();
		CTitleBar(CWindow* parent);

		virtual bool onMouseLeftDown(const CPoint& point, CControl* sender);
		virtual bool onMouseLeftUp(const CPoint& point, CControl* sender);

		void caption(const char* captionString);

		const CText& captionText() const;

	protected:
		CButton*	mCloseButton;
		CText mCaption;
};
