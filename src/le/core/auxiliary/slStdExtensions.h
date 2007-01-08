#pragma once

#include <le/core/config/slPrefix.h>
namespace sokira
{
	namespace le
	{

template<typename TContainer>
void clearPointerContainer(TContainer& container)
{
	typename TContainer::iterator end = container.end();
	for(typename TContainer::iterator it = container.begin(); it != end; ++it)
		delete (*it);
	container.clear();
}

	} // namespace le
} // namespace sokira
