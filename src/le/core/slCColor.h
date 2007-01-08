#pragma once

#include <le/core/slCObject.h>
#include "slTCColor.h"


namespace sokira
{
	namespace le
	{

class CColor : public CObject, public TCColor<>
{
	LE_DECLARE_RUNTIME_CLASS(CColor);

	public:
		inline CColor() {};

		inline CColor(UInt8 red, UInt8 green = 0, UInt8 blue = 0, UInt8 alpha = 0) :
			TCColor<>(red, green, blue, alpha)
		{

		}

		inline CColor(Float32 red, Float32 green = 0.0f, Float32 blue = 0.0f, Float32 alpha = 0.0f) :
			TCColor<>(red, green, blue, alpha)
		{

		}

		virtual void serialize(CDictionary& toDictionary) const;
		virtual void deserialize(const CDictionary& fromDictionary);
};

	} // namespace le
} // namespace sokira
