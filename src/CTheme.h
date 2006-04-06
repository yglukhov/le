#pragma once

#include "CObject.h"

#include <string>
#include <map>

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
		static const char* currentTheme();

		const CControlBasicController* controllerForControl(const char* controlClass) const;

	private:
		void init();

		typedef std::map<std::string, TCPointer<CControlBasicController> > CControllerMap;
		CControllerMap mControllerMap;
};