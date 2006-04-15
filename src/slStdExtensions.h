#pragma once

#include <config/slPrefix.h>
LE_NAMESPACE_START

template<typename TContainer>
void clearPointerContainer(TContainer& container)
{
	typename TContainer::iterator end = container.end();
	for(typename TContainer::iterator it = container.begin(); it != end; ++it)
		delete (*it);
	container.clear();
}

LE_NAMESPACE_END
