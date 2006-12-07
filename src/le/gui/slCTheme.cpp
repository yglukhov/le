#include "slCTheme.h"
#include <le/core/debug/slDebug.h>
#include "slCControl.h"
#include <le/core/slTCClassFactory.h>
#include "slBasicGraphicControllers.h"
#include <list>

LE_NAMESPACE_START

LE_LINK_MODULE_DEPENDENCY(slBasicGraphicControllers);

IMPLEMENT_RUNTIME_CLASS(CTheme);

static CTheme::Ptr _currentTheme;

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

}

CTheme* CTheme::instance()
{
	if(!_currentTheme)
	{
		currentTheme("CTheme");
	}

	return _currentTheme.get();
}

void CTheme::init()
{
	CGeneralControllerMap::iterator foundIt = controllerMap().find(objectClass()->name());
	if(foundIt == controllerMap().end())
	{
		return;
	}

	// collecting appropriate controllers to graphic controller map.
	std::list<std::pair<CString, CString> >& controllerList = foundIt->second;

	std::list<std::pair<CString, CString> >::iterator end = controllerList.end();
	for(std::list<std::pair<CString, CString> >::iterator it = controllerList.begin();
			it != end; ++it)
	{
		TCPointer<CControlBasicController> controller =
				TCClassFactory<CObject>::create<CControlBasicController>(it->first);

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
		IF_LOG(log << "WARNING: Graphic controller for " << controlClass
					<< " and theme " << currentTheme() << " not found." << std::endl);
		// TODO: search for controller from default theme.
		return NULL;
	}

	return it->second;
}

void CTheme::drawControl(const CControl* control) const
{
	const CControlBasicController* controller = controllerForControl(control->objectClass()->name());
	if(controller)
	{
		controller->draw(control);
	}
}

bool CTheme::hitTest(const CControl* control, const CPoint& point) const
{
	const CControlBasicController* controller = controllerForControl(control->objectClass()->name());
	if(controller)
	{
		return controller->hitTest(control, point);
	}

	return false;
}

void CTheme::currentTheme(const char* themeClass)
{
	LE_ENTER_LOG;

	delete _currentTheme;
	_currentTheme = TCClassFactory<CObject>::create<CTheme>(themeClass);

	if(_currentTheme)
	{
		_currentTheme->init();
	}
}

CString CTheme::currentTheme()
{
	return instance()->objectClass()->name();
}


LE_NAMESPACE_END


void _le_register_graphic_controller(const CBasicString& controllerClass, 
										const CBasicString& themeClass, const CBasicString& controlClass)
{
	// TODO: check for existance of this controller.
	LE_ENTER_LOG_SILENT;
	IF_LOG(log << "Registering graphic controller \"" << controllerClass << "\" for control \""
		<< controlClass << "\" for theme \"" << themeClass << "\"" << std::endl);

	LE_NESTED_NAMESPACE controllerMap()[themeClass].push_back(
		std::pair<CString, CString>(controllerClass, controlClass));
}
