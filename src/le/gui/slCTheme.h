#pragma once
#include <le/core/slCString.h>

#include <map>

namespace sokira
{
	namespace le
	{

class CControl;
class CPoint;
class CControlBasicController;

class CTheme
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CTheme)
	LE_RTTI_END

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

	} // namespace le
} // namespace sokira
