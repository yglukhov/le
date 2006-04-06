#include "CTheme.h"
#include "Debug.h"
#include "IClass.h"
#include "CControl.h"
#include "CClassFactory.h"
#include "ClassImplementation.h"
#include "BasicGraphicControllers.h"
#include <list>


IMPLEMENT_RUNTIME_CLASS(CTheme);

static CTheme::Ptr _currentTheme;

typedef std::map<std::string /*theme*/,
					  std::list<std::pair<std::string /*controller*/,
												 std::string /*control*/> > > CGeneralControllerMap;

static inline CGeneralControllerMap& controllerMap()
{
	static CGeneralControllerMap map;
	return map;
}

void _register_graphic_controller(const char* controllerClass, 
										const char* themeClass, const char* controlClass)
{
	// TODO: check for existance of this controller.
	ENTER_LOG;
	IF_LOG(log << "Registering graphic controller \"" << controllerClass << "\" for control \""
		<< controlClass << "\" for theme \"" << themeClass << "\"" << std::endl);

	controllerMap()[std::string(themeClass)].push_back(std::pair<std::string, std::string>(std::string(controllerClass), std::string(controlClass)));
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
	CGeneralControllerMap::iterator foundIt = controllerMap().find(std::string(objectClass()->name()));
	if(foundIt == controllerMap().end())
	{
		return;
	}

	// collecting appropriate controllers to graphic controller map.
	std::list<std::pair<std::string, std::string> >& controllerList = foundIt->second;

	std::list<std::pair<std::string, std::string> >::iterator end = controllerList.end();
	for(std::list<std::pair<std::string, std::string> >::iterator it = controllerList.begin();
			it != end; ++it)
	{
		TCPointer<CControlBasicController> controller =
						CClassFactory::create<CControlBasicController>(it->first.c_str());

		if(controller)
		{
			mControllerMap.insert(CControllerMap::value_type(it->second, controller));
		}
	}
}

const CControlBasicController* CTheme::controllerForControl(const char* controlClass) const
{
	ENTER_LOG;

	CControllerMap::const_iterator it = mControllerMap.find(std::string(controlClass));
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
	ENTER_LOG;

	delete _currentTheme;
	_currentTheme = CClassFactory::create<CTheme>(themeClass);

	if(_currentTheme)
	{
		_currentTheme->init();
	}
}

const char* CTheme::currentTheme()
{
	return instance()->objectClass()->name();
}