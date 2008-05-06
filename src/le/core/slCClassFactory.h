#pragma once

#include <set>
#include "slCClass.h"
#include <le/core/debug/slDebug.h>

namespace sokira
{
	namespace le
	{

class CClassFactory
{
	public:
		static CClassFactory *defaultInstance();

		template <class THierarchyRoot>
		static TCPointer<THierarchyRoot> create(const CBasicString& className)
		{
			LE_ENTER_LOG;

			IClassImpl* classImpl = _classWithName(className);
			if (classImpl)
				return CClass(classImpl).create<THierarchyRoot>();

			return NULL;
		}

		static bool isClassRegistered(const CBasicString& className);
		static CClass classWithName(const CBasicString& className)
		{
			return CClass(_classWithName(className));
		}

		class iterator// : public std::set<IClassImpl*>::iterator
		{
				typedef std::set<IClassImpl*>::iterator parent;
			public:
				class IPredicate
				{
					public:
						virtual bool match(IClassImpl*) const
						{
							return true;
						}
						virtual ~IPredicate() {}
				};

				iterator(parent it, parent begin, parent end, IPredicate* pred) :
					mIt(it),
					mBegin(begin),
					mEnd(end),
					mClass(*it),
					mPredicate(pred)
				{
					while (mIt != mEnd)
					{
						if (mPredicate->match(*mIt))
						{
							mClass = CClass(*mIt);
							break;
						}
						++mIt;
					}
					
					if (mIt == mEnd)
					{
						mClass = CClass(*mIt);
					}
				}

				~iterator()
				{
					delete mPredicate;
				}

				CClass operator* () const
				{
					return mClass;
				}

				const CClass* operator->() const
				{
					return &mClass;
				}

				iterator& operator++()
				{
					while (mIt != mEnd)
					{
						++mIt;
						if (mIt == mEnd)
						{
							mClass = CClass(NULL);
							break;
						}
						else if (mPredicate->match(*mIt))
						{
							mClass = CClass(*mIt);
							break;
						}
					}
					return *this;
				}

				iterator operator++(int)
				{
					iterator tmp = *this;
					while (mIt != mEnd)
					{
						++mIt;
						if (mIt == mEnd)
						{
							mClass = CClass(NULL);
							break;
						}
						else if (mPredicate->match(*mIt))
						{
							mClass = CClass(*mIt);
							break;
						}
					}
					return tmp;
				}

				iterator& operator--()
				{
					bool matched = false;
					while (mIt != mBegin)
					{
						--mIt;
						if (mPredicate->match(*mIt))
						{
							mClass = CClass(*mIt);
							matched = true;
							break;
						}
					}
					if (mIt == mBegin && !matched)
					{
						mClass = CClass(NULL);
					}
					return *this;
				}

				iterator operator--(int)
				{
					iterator tmp = *this;
					bool matched = false;
					while (mIt != mBegin)
					{
						--mIt;
						if (mPredicate->match(*mIt))
						{
							mClass = CClass(*mIt);
							matched = true;
							break;
						}
					}
					if (mIt == mBegin && !matched)
					{
						mClass = CClass(NULL);
					}
					return tmp;
				}

				bool operator == (const iterator& rhs) const
				{
					return mIt == rhs.mIt;
				}
				bool operator != (const iterator& rhs) const
				{
					return mIt != rhs.mIt;
				}

			private:
				std::set<IClassImpl*>::iterator mIt;
				std::set<IClassImpl*>::iterator mBegin;
				std::set<IClassImpl*>::iterator mEnd;
				CClass mClass;
				IPredicate* mPredicate;
		};

		static iterator begin();
		template <class T>
		static inline iterator beginForChildsOf()
		{
			return _beginForChildsOfStd(typeid(T).name());
		}

		static iterator beginForChildsOf(const CBasicString& name);
		static iterator beginForChildsOf(const CClass& theClass)
		{
			return _beginForChildsOfStd(theClass.stdName());
		}

		static iterator end();

	private:
		typedef std::set<IClassImpl*> CClassSet;
		CClassSet mClasses;
		static IClassImpl* _classWithName(const CBasicString& name);
		static iterator _beginForChildsOfStd(const char* name);
};

	} // namespace le
} // namespace sokira
