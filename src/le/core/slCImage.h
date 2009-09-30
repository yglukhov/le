#if !defined SL_LE_core_slCImage_h
#define SL_LE_core_slCImage_h

#include <le/core/geometry/slTCSize2D.h>
#include "slCString.h"


namespace sokira
{
	namespace le
	{

class CImageImpl;
class CURL;

class CImage : public CObject
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(CImage)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		CImage();
		CImage(const CImage& image);
		CImage(const CURL& url);
		~CImage();

		Bool loadFromURL(const CURL& url);
		
		const UInt8* pixelData() const;
		CSize2D size() const;

		CImageImpl* _impl() const;

	private:
		CImageImpl* mImpl;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCImage_h
