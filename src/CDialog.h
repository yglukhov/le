#pragma once

#include "CWindow.h"

class CTitleBar;

class CDialog: public CWindow
{
	DECLARE_RUNTIME_CLASS(CDialog);

	public:
		CDialog();
		CDialog(const CRectangle& rect);

		virtual void addChild(CControl* child); 		
		virtual void removeChild(CControl* child);

		void title(const char* titleString);

	protected:
		CWindow* mWorkWindow;
		CTitleBar* mTitleBar;
};