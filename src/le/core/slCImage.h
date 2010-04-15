#if !defined SL_LE_core_slCImage_h
#define SL_LE_core_slCImage_h

#include <le/core/geometry/slTCSize2D.h>
#include "slCString.h"
//#include "slCImageFrame.h"


namespace sokira
{
	namespace le
	{

class CImageImpl;
class CImageFrame;
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

		UInt32 frameCount() const;
		CImageFrame frameAtIndex(UInt32 index) const;
		void insertFrame(UInt32 position, const CImageFrame& frame);

//		UInt32 currentFrame() const;
//		void setCurrentFrame(UInt32 frame);
//
//		// Current frame info
//		EPixelFormat pixelFormat() const;
//		const UInt8* pixelData() const;
//		CSize2D size() const;
//		UInt32 duration(); // duration of a frame in milliseconds

		CImageImpl* _impl() const;

	private:
		CImageImpl* mImpl;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCImage_h
