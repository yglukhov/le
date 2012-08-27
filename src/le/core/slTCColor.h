#pragma once

#include "base/slTCColorBase.h"

// TODO: remove this
#ifndef NULL
#define NULL 0
#endif

namespace sokira
{
	namespace le
	{

template <typename TComponent = UInt8>
class TCColor : public sokira::le::base::CColorBase
{
	public:
		typedef TComponent TComponentType;

		inline TCColor() :
			mR(), mG(), mB(), mA()
		{

		}

		inline TCColor(TComponent red, TComponent green = 0, TComponent blue = 0, TComponent alpha = _max<TComponent>::max()) :
			mR(red),
			mG(green),
			mB(blue),
			mA(alpha)
		{

		}

		template <typename T>
		inline TCColor(T red, T green = 0, T blue = 0, T alpha = _max<T>::max()) :
			mR(toComponent(red)),
			mG(toComponent(green)),
			mB(toComponent(blue)),
			mA(toComponent(alpha))
		{

		}

		inline TCColor(const TCColor<TComponent>& copy) :
			mR(copy.mR),
			mG(copy.mG),
			mB(copy.mB),
			mA(copy.mA)
		{

		}

		template <typename T>
		inline TCColor(const TCColor<T>& copy) :
			mR(copy.template redAs<TComponent>()),
			mG(copy.template greenAs<TComponent>()),
			mB(copy.template blueAs<TComponent>()),
			mA(copy.template alphaAs<TComponent>())
		{

		}


		inline TComponent red() const
		{
			return mR;
		}

		inline TComponent green() const
		{
			return mG;
		}

		inline TComponent blue() const
		{
			return mB;
		}

		inline TComponent alpha() const
		{
			return mA;
		}

		template <typename T>
		inline T redAs() const
		{
			return fromComponent<T>(mR);
		}

		template <typename T>
		inline T greenAs() const
		{
			return fromComponent<T>(mG);
		}

		template <typename T>
		inline T blueAs() const
		{
			return fromComponent<T>(mB);
		}

		template <typename T>
		inline T alphaAs() const
		{
			return fromComponent<T>(mA);
		}

		template <typename T>
		inline void setRed(T r)
		{
			mR = toComponent<T>(r);
		}

		template <typename T>
		inline void setGreen(T g)
		{
			mG = toComponent<T>(g);
		}

		template <typename T>
		inline void setBlue(T b)
		{
			mB = toComponent<T>(b);
		}

		template <typename T>
		inline void setAlpha(T a)
		{
			mA = toComponent<T>(a);
		}

		template <typename T>
		inline void setComponents(T r, T g, T b, T a)
		{
			mR = toComponent(r);
			mG = toComponent(g);
			mB = toComponent(b);
			mA = toComponent(a);
		}

		template <typename T>
		inline void getComponents(T* r, T* g = NULL, T* b = NULL, T* a = NULL) const
		{
			if (r)
				*r = fromComponent<T>(mR);
			if (g)
				*g = fromComponent<T>(mG);
			if (b)
				*b = fromComponent<T>(mB);
			if (a)
				*a = fromComponent<T>(mA);
		}

		inline const TCColor<TComponent>& operator = (const TCColor<TComponent>& copy)
		{
			return operator = <TComponent>(copy);
		}

		template <typename T>
		const TCColor<TComponent>& operator = (const TCColor<T>& copy)
		{
			mR = copy.template redAs<TComponent>();
			mG = copy.template greenAs<TComponent>();
			mB = copy.template blueAs<TComponent>();
			mA = copy.template alphaAs<TComponent>();
			return *this;
		}

		inline bool operator == (const TCColor<TComponent>& color)
		{
			return operator == <TComponent>(color);
		}

		template <typename T>
		bool operator == (const TCColor<T>& color)
		{
			return ((mR == color.template redAs<TComponent>()) &&
					  (mG == color.template greenAs<TComponent>()) &&
					  (mB == color.template blueAs<TComponent>()) &&
					  (mA == color.template alphaAs<TComponent>()));
		}

		inline bool operator != (const TCColor<TComponent>& color)
		{
			return operator != <TComponent>(color);
		}

		template <typename T>
		bool operator != (const TCColor<T>& color)
		{
			return ((mR != color.template redAs<TComponent>()) ||
					  (mG != color.template greenAs<TComponent>()) ||
					  (mB != color.template blueAs<TComponent>()) ||
					  (mA != color.template alphaAs<TComponent>()));
		}

	private:

		template <typename From>
		inline TComponent toComponent(From component) const
		{
			enum
			{
				toTypeIsFloat = TSOr<TSTypesEqual<TComponent, Float32>, TSTypesEqual<TComponent, Float64> >::value,
				fromTypeIsFloat = TSOr<TSTypesEqual<From, Float32>, TSTypesEqual<From, Float64> >::value
			};
			return _convert<toTypeIsFloat, fromTypeIsFloat, TComponent, From>::convert(component);
		}

		template <typename To>
		inline To fromComponent(TComponent component) const
		{
			enum
			{
				toTypeIsFloat = TSOr<TSTypesEqual<To, Float32>, TSTypesEqual<To, Float64> >::value,
				fromTypeIsFloat = TSOr<TSTypesEqual<TComponent, Float32>, TSTypesEqual<TComponent, Float64> >::value
			};
			return _convert<toTypeIsFloat, fromTypeIsFloat, To, TComponent>::convert(component);
		}

		TComponent mR, mG, mB, mA; // conponents
};

	} // namespace le
} // namespace sokira
