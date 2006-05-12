#pragma once

#include <common/config/slPrefix.h>
#include "slCWindow.h"

LE_NAMESPACE_START

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

LE_NAMESPACE_END
