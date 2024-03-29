#pragma once

#include "slCView.h"

namespace sokira
{
	namespace le
	{

class CTitleBar;

class CDialog: public CView
{
	LE_DECLARE_RUNTIME_CLASS(CDialog);

	public:
		CDialog();
		CDialog(const CRectangle& rect);

		virtual void addChild(CControl* child);
		virtual void removeChild(CControl* child);

		void title(const char* titleString);

	protected:
		CView* mWorkWindow;
		CTitleBar* mTitleBar;
};

	} // namespace le
} // namespace sokira
