#include "slCTheme.h"
#include <le/core/debug/slDebug.h>
#include "slCControl.h"
#include <le/core/slCClassFactory.h>
#include "slBasicGraphicControllers.h"
#include <list>

LE_LINK_MODULE_DEPENDENCY(_le_slBasicGraphicControllers);

namespace sokira
{
	namespace le
	{

LE_IMPLEMENT_RUNTIME_CLASS(CTheme);

//static CTheme::Ptr _currentTheme;

typedef std::map<CString /*theme*/,
					  std::list<std::pair<CString /*controller*/,
												 CString /*control*/> > > CGeneralControllerMap;

static inline CGeneralControllerMap& controllerMap()
{
	static CGeneralControllerMap map;
	return map;
}

CTheme::CTheme()
{
	init();
}

void CTheme::init()
{
	CGeneralControllerMap &theMap = controllerMap();
	CGeneralControllerMap::iterator foundIt;
	foundIt = theMap.find(objectClass().name());
	if (foundIt == controllerMap().end())
	{
		return;
	}

	// collecting appropriate controllers to graphic controller map.
	std::list<std::pair<CString, CString> >& controllerList = foundIt->second;

	std::list<std::pair<CString, CString> >::iterator end = controllerList.end();
	for (std::list<std::pair<CString, CString> >::iterator it = controllerList.begin();
			it != end; ++it)
	{
		TCPointer<CControlBasicController> controller =
				CClassFactory::defaultInstance()->create<CControlBasicController>(it->first);

		if(controller)
		{
			mControllerMap.insert(CControllerMap::value_type(it->second, controller));
		}
	}
}

const CControlBasicController* CTheme::controllerForControl(CString controlClass) const
{
	LE_ENTER_LOG;

	CControllerMap::const_iterator it = mControllerMap.find(CString(controlClass));
	if(it == mControllerMap.end())
	{
		LE_IF_LOG(log << "WARNING: Graphic controller for " << controlClass
					<< " not found." << std::endl);
		// TODO: search for controller from default theme.
		return NULL;
	}

	return it->second;
}

void CTheme::drawControl(const CControl* control, CRenderingContext* context) const
{
	const CControlBasicController* controller = controllerForControl(control->objectClass().name());
	if (controller)
	{
		controller->draw(control, this, context);
	}
}

Bool CTheme::onMouse(EMouseButton button, EButtonState state, const CPoint& point, CControl* control) const
{
	const CControlBasicController* controller = controllerForControl(control->objectClass().name());
	if (controller)
	{
		return controller->onMouse(button, state, point, control, this);
	}

	return false;
}

	} // namespace le
} // namespace sokira


void _le_register_graphic_controller(const char* controllerClass,
									 const char* themeClass,
									 const char* controlClass)
{
	// TODO: check for existance of this controller.
	LE_ENTER_LOG_SILENT;
	LE_IF_LOG(log << "Registering graphic controller \"" << controllerClass << "\" for control \""
		<< controlClass << "\" for theme \"" << themeClass << "\"" << std::endl);

	::sokira::le::controllerMap()[themeClass].push_back(
		std::pair<sokira::le::CString, ::sokira::le::CString>(
			controllerClass, controlClass));
}
