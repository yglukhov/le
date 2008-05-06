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

template <typename TComponent = Float32>
class TCColor : public _TCColorBase
{
	public:

		inline TCColor() :
			mR(), mG(), mB(), mA()
		{

		}

		inline TCColor(UInt8 red, UInt8 green = 0, UInt8 blue = 0, UInt8 alpha = 0) :
			mR(toComponent(red)),
			mG(toComponent(green)),
			mB(toComponent(blue)),
			mA(toComponent(alpha))
		{

		}

		inline TCColor(Float32 red, Float32 green = 0.0f, Float32 blue = 0.0f, Float32 alpha = 0.0f) :
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
			mR(copy.redAs<TComponent>()),
			mG(copy.greenAs<TComponent>()),
			mB(copy.blueAs<TComponent>()),
			mA(copy.alphaAs<TComponent>())
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
		inline void rgba(T r, T g, T b, T a)
		{
			mR = toComponent(r);
			mG = toComponent(g);
			mB = toComponent(b);
			mA = toComponent(a);
		}

		template <typename T>
		inline void rgba(T* r, T* g = NULL, T* b = NULL, T* a = NULL) const
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
			mR = copy.redAs<TComponent>();
			mG = copy.greenAs<TComponent>();
			mB = copy.blueAs<TComponent>();
			mA = copy.alphaAs<TComponent>();
			return *this;
		}

		inline bool operator == (const TCColor<TComponent>& color)
		{
			return operator == <TComponent>(color);
		}

		template <typename T> 
		bool operator == (const TCColor<T>& color)
		{
			return ((mR == color.redAs<TComponent>()) &&
					  (mG == color.greenAs<TComponent>()) &&
					  (mB == color.blueAs<TComponent>()) &&
					  (mA == color.alphaAs<TComponent>()));
		}

		inline bool operator != (const TCColor<TComponent>& color)
		{
			return operator != <TComponent>(color);
		}

		template <typename T>
		bool operator != (const TCColor<T>& color)
		{
			return ((mR != color.redAs<TComponent>()) ||
					  (mG != color.greenAs<TComponent>()) ||
					  (mB != color.blueAs<TComponent>()) ||
					  (mA != color.alphaAs<TComponent>()));
		}

	private:

		template <typename From>
		inline TComponent toComponent(From component) const
		{
			return _convert<TComponent, From>::convert(component);
		}

		template <typename To>
		inline To fromComponent(TComponent component) const
		{
			return _convert<To, TComponent>::convert(component);
		}

	private:
		TComponent mR, mG, mB, mA; // conponents
};

	} // namespace le
} // namespace sokira
