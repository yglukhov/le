#pragma once
#include <common/types/slCString.h>

#include <map>

LE_NAMESPACE_START

class CControl;
class CPoint;
class CControlBasicController;

class CTheme : public CObject
{
	DECLARE_RUNTIME_CLASS(CTheme);

	public:
		CTheme();

		static CTheme* instance();

		void drawControl(const CControl* control) const;
		bool hitTest(const CControl* control, const CPoint& point) const;

		static void currentTheme(const char* themeClass);
		static CString currentTheme();

		const CControlBasicController* controllerForControl(CString controlClass) const;

	private:
		void init();

		typedef std::map<CString, TCPointer<CControlBasicController> > CControllerMap;
		CControllerMap mControllerMap;
};

LE_NAMESPACE_END
