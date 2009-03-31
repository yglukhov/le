#if !defined SL_LE_gui_slCScene_h
#define SL_LE_gui_slCScene_h

#include <le/gui/slConstants.h>
#include <le/gui/slTypes.h>

namespace sokira
{
	namespace le
	{

class CRenderingContext;

class CScene
{
	public:
		CScene();

		// Mouse events
		virtual Bool onMouse(EMouseButton button, EButtonState state, const CPoint& point);
//		virtual Bool mouseButtonPressed(EMouseButton button, const CPoint& point);
//		virtual Bool mouseButtonReleased(EMouseButton button, const CPoint& point);
//		virtual Bool mouseHovered(const CPoint& point);
		virtual Bool mouseEntered(const CPoint& point);
		virtual Bool mouseExited(const CPoint& point);

		virtual void draw(CRenderingContext* context);

		virtual void setNeedsRedraw();

	private:
		friend class CScreen;
		void setScreen(CScreen* screen);
		CScreen* mScreen;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCScene_h
