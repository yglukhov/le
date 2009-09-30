#if !defined SL_LE_gui_slCTexture_h
#define SL_LE_gui_slCTexture_h

namespace sokira
{
	namespace le
	{

class CImage;
class CImageImpl;
class CTextureImpl;

class CTexture
{
	public:
		CTexture();
		CTexture(const CTexture& image);
		CTexture(const CImage& image);
		~CTexture();

		void setImage(const CImage& image);
		CSize2D size() const;

	private:
		friend class CRenderingContext;
		void disposeData();

		mutable CImageImpl* mImageImpl;
		mutable CTextureImpl* mImpl;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCTexture_h
