
#include <iostream>
#include <template/typelist/slTSTypeList.h>

template <class T> class TSProtectedInheriter {};

template <class T>
struct TSInheritTraits
{
	typedef T toInheritType;
	typedef T theType;
	enum { public_inheritance = 1 };
};

template <class T>
struct TSInheritTraits<TSProtectedInheriter<T> >
{
	class toInheritType : protected T
	{
	
	};
	typedef T theType;
	enum { public_inheritance = 0 };
};

template <class T>
struct TSToInheritTraitsMutator
{
	typedef TSInheritTraits<T> result;
};


template <class T>
struct TSCollectIfPublicInheritance
{
	// Here we receive only TSInheritTraits<x> as T
	enum { result = T::public_inheritance };
};

template <class T>
struct TSCollectIfProtectedInheritance
{
	// Here we receive only TSInheritTraits<x> as T
	enum { result = !(T::public_inheritance) };
};

template <class T>
struct TSUnpackClassFromInheritTraits
{
	// Here we receive only TSInheritTraits<x> as T
	typedef typename T::theType result;
};

template <class TInherits, unsigned len>
class TCPublicInheriter;

template <class TInherits>
class TCPublicInheriter<TInherits, 0>
{

};

template <class TInherits>
class TCPublicInheriter<TInherits, 1> :
	public TInherits::template TypeAt<0>::result
{

};

template <class TInherits>
class TCPublicInheriter<TInherits, 2> :
	public TInherits::template TypeAt<0>::result,
	public TInherits::template TypeAt<1>::result
{

};


template <class TInherits, int indexOf>
struct TSFirstParentDefiner
{
	typedef typename TSInheritTraits<typename TInherits::template TypeAt<indexOf>::result>::theType firstParent;
};

template <class TInherits>
struct TSFirstParentDefiner<TInherits, -1>
{

};

template <class TInherits, int indexOf>
struct TSFirstPublicParentDefiner
{
	typedef typename TSInheritTraits<typename TInherits::template TypeAt<indexOf>::result>::theType firstPublicParent;
};

template <class TInherits>
struct TSFirstPublicParentDefiner<TInherits, -1>
{

};

template <class TInherits, int indexOf>
struct TSFirstProtectedParentDefiner
{
	typedef typename TSInheritTraits<typename TInherits::template TypeAt<indexOf>::result>::theType firstProtectedParent;
};

template <class TInherits>
struct TSFirstProtectedParentDefiner<TInherits, -1>
{

};

template <class T>
struct TSIsPublicInheritance
{
	enum { result = TSInheritTraits<T>::public_inheritance };
};

template <class T>
struct TSIsProtectedInheritance
{
	enum { result = !(TSInheritTraits<T>::public_inheritance) };
};

template <class T>
struct TSMutateToTypeToInherit
{
	typedef typename TSInheritTraits<T>::toInheritType result;
};

template <class TInherits>
class TCInheriterImpl :
	public TCPublicInheriter<typename TInherits::template Mutate<TSMutateToTypeToInherit>::result, TInherits::length>,
	public TSFirstParentDefiner<TInherits, (TInherits::length)?(0):(-1)>,
	public TSFirstPublicParentDefiner<TInherits, TInherits::template FindIf<TSIsPublicInheritance>::result>,
	public TSFirstProtectedParentDefiner<TInherits, TInherits::template FindIf<TSIsProtectedInheritance>::result>
{
	typedef typename TInherits::template Mutate<TSToInheritTraitsMutator>::result
																			inheritTraitsList;
	typedef typename inheritTraitsList::template CollectIf<TSCollectIfPublicInheritance>::result
																			publicInheritTraitsList;
	typedef typename inheritTraitsList::template CollectIf<TSCollectIfProtectedInheritance>::result
																			protectedInheritTraitsList;
	public:
	typedef typename inheritTraitsList::template Mutate<TSUnpackClassFromInheritTraits>::result allParents;
	typedef typename publicInheritTraitsList::template Mutate<TSUnpackClassFromInheritTraits>::result allPublicParents;
	typedef typename protectedInheritTraitsList::template Mutate<TSUnpackClassFromInheritTraits>::result allProtectedParents;
};

template <class T1 = _SNullType, class T2 = _SNullType , class T3 = _SNullType>
class TCInheriter :
	public TCInheriterImpl<TSTypeList<T1, T2, T3> >
{

};

template <class T>
struct TSDummyDef
{
	typedef T result;
};

#define Public(x) TSDummyDef<x >::result
#define Protected(x) TSDummyDef<TSProtectedInheriter<x> >::result
#define inherits public TCInheriter

class A
{
	public:
		void f()
		{
			std::cout << "A::f()\n";
		}
};

class B
{
	public:
		void f()
		{
			std::cout << "B::f()\n";
		}
};

class C : public A, inherits<Public(A), Public(B)>
{
	public:
		void f()
		{
			std::cout << "C::f()\n{\n";
			firstParent::f();
			firstProtectedParent::f();
			std::cout << "}\n";
		}
};

int main (int argc, char * const argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    A a;
	 B b;
	 C c;
	 
	 std::cout << "Calling A::f ...\n";
	 a.f();

	 std::cout << "Calling B::f ...\n";
	 b.f();

	 std::cout << "Calling C::f ...\n";
	 c.f();
	 
	 return 0;
}
