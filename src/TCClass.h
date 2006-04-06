#pragma once

#include "IClass.h"
#include <string>

template <typename T>
class TCClass : public IClass
{
	public:
		virtual CObject::Ptr create() const;

	private:
		const char* name() const;
		const std::string mName;

	public:
		TCClass(const char*);
};

template <typename T>
TCClass<T>::TCClass(const char* name) :
	mName(name)
{
	void _register_class(const std::string&, IClass*);
	_register_class(mName, this);
}

template <typename T>
CObject::Ptr TCClass<T>::create() const
{
	return CObject::Ptr(dynamic_cast<CObject*>(new T()));
}

template <typename T>
const char* TCClass<T>::name() const
{
	return mName.c_str();
}