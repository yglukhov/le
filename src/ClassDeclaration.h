#pragma once
class IClass;

////////////////////////////////////////////////////////////////////////////////
// This macro must be used in class declaration section.
// The class must be inherited from CObject.

#define DECLARE_RUNTIME_CLASS(Class)		\
template <typename T> friend class TCClass;\
public:												\
	static IClass* staticClass();				\
	virtual IClass* objectClass() const;	\
														\
	typedef TCPointer<Class> Ptr;				\
private:
