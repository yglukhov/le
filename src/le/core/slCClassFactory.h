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
		TCPointer<THierarchyRoot> create(const CBasicString& className)
		{
			LE_ENTER_LOG;

			base::IClassImpl* classImpl = _classWithName(className);
			if (classImpl)
				return CClass(classImpl).create<THierarchyRoot>();

			return NULL;
		}

		bool isClassRegistered(const CBasicString& className);
		CClass classWithName(const CBasicString& className)
		{
			return CClass(_classWithName(className));
		}

		class iterator// : public std::set<IClassImpl*>::iterator
		{
				typedef std::set<base::IClassImpl*>::iterator parent;
			public:
				class IPredicate
				{
					public:
						virtual bool operator () (base::IClassImpl*) const
						{
							return true;
						}
						virtual ~IPredicate() {}
				};

				iterator(parent it, parent begin, parent end, IPredicate* pred) :
					mIt(it),
					mBegin(begin),
					mEnd(end),
					mClass(NULL),
					mPredicate(pred)
				{
					while (mIt != mEnd)
					{
						if ((*mPredicate)(*mIt))
						{
							mClass = CClass(*mIt);
							break;
						}
						++mIt;
					}
				}

				const CClass& operator* () const
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

						if ((*mPredicate)(*mIt))
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
					++(*this);
					return tmp;
				}

				iterator& operator--()
				{
					bool matched = false;
					while (mIt != mBegin)
					{
						--mIt;
						if ((*mPredicate)(*mIt))
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
					--(*this);
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
				std::set<base::IClassImpl*>::iterator mIt;
				std::set<base::IClassImpl*>::iterator mBegin;
				std::set<base::IClassImpl*>::iterator mEnd;
				CClass mClass;
				TCPointer<IPredicate> mPredicate;
		};

		iterator begin();
		template <class T>
		inline iterator beginForChildsOf()
		{
			return _beginForChildsOfStd(typeid(T));
		}

		iterator beginForChildsOf(const CBasicString& name);
		iterator beginForChildsOf(const CClass& theClass)
		{
			return _beginForChildsOfStd(theClass.stdType());
		}

		iterator end();


		void registerClass(base::IClassImpl* theClass);
	private:
		typedef std::set<base::IClassImpl*> CClassSet;
		CClassSet mClassSet;
		base::IClassImpl* _classWithName(const CBasicString& name);
		iterator _beginForChildsOfStd(const std::type_info& name);
};

	} // namespace le
} // namespace sokira
