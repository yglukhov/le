#if !defined SL_LE_gui_slCTheme_h
#define SL_LE_gui_slCTheme_h

#include <le/core/slCString.h>
#include <le/gui/slBasicGraphicControllers.h>
#include <le/gui/slConstants.h>

#include <map>

namespace sokira
{
	namespace le
	{

class CControl;
class CPoint;
class CControlBasicController;
class CRenderingContext;

class CTheme
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CTheme)
	LE_RTTI_END

	public:
		CTheme();

//		static CTheme* instance();

		void drawControl(const CControl* control, CRenderingContext* context) const;
//		Bool hitTest(const CControl* control, const CPoint& point) const;

		Bool onMouse(EMouseButton button, EButtonState state, const CPoint& point, CControl* control) const;
//		Bool mouseButtonPressed(EMouseButton button, const CPoint& point, CControl* control) const;
//		Bool mouseButtonReleased(EMouseButton button, const CPoint& point, CControl* control) const;
//		Bool mouseHovered(const CPoint& point, CControl* control) const;

//		static void currentTheme(const char* themeClass);
//		static CString currentTheme();

	private:
		const CControlBasicController* controllerForControl(CString controlClass) const;

		void init();

		typedef std::map<CString, TCPointer<CControlBasicController> > CControllerMap;
		CControllerMap mControllerMap;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCTheme_h
