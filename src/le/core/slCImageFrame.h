#if !defined SL_LE_core_slCImageFrame_hp
#define SL_LE_core_slCImageFrame_hp

#include <le/core/geometry/slTCSize2D.h>

namespace sokira
{
	namespace le
	{

enum EPixelFormat
{
	ePixelFormatGrayscale = 8,
	ePixelFormatRGB = 24,
	ePixelFormatRGBA = 32
};

class CImageFrameImpl;

class CImageFrame
{
	public:
		CImageFrame();
		CImageFrame(const CImageFrame& frame);
		~CImageFrame();

		EPixelFormat pixelFormat() const;
		const UInt8* pixelData() const;
		CSize2D size() const;
		UInt32 duration() const; // Duration of a frame in milliseconds;

		const CImageFrame& operator = (const CImageFrame&);

	// private:
		CImageFrame(CImageFrameImpl* impl);

	private:
		CImageFrameImpl* mImpl;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_core_slCImageFrame_hp
