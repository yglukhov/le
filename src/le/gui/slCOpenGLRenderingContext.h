#if !defined SL_LE_gui_slCOpenGLRenderingContext_h
#define SL_LE_gui_slCOpenGLRenderingContext_h

#include "slCRenderingContext.h"
#include "slCFont.h"

namespace sokira
{
	namespace le
	{

class COpenGLRenderingContext : public CRenderingContext
{
	LE_RTTI_BEGIN
		LE_RTTI_SELF(COpenGLRenderingContext)
		LE_RTTI_SINGLE_PUBLIC_PARENT
	LE_RTTI_END

	public:
		COpenGLRenderingContext();
		~COpenGLRenderingContext();

		virtual void beginDrawing();
		virtual void endDrawing();

		virtual void setLineWidth(Float32 width);

		virtual void unsetTexture();

		virtual void pushClippingRect(const CRectangle& rect);
		virtual void popClippingRect();

		// Geometry
		virtual void drawText(const CString& text, const CPoint2D& position);
		virtual void drawBox(const CBox& box);
		virtual void drawWireBox(const CBox& box);

		virtual SVertex* sharedVertexBufferOfSize(UInt32 count);
		virtual SColoredVertex* sharedColorVertexBufferOfSize(UInt32 count);

		virtual void drawVertexesInSharedBuffer(UInt32 count, EPrimitiveType primitive);
		virtual void drawColoredVertexesInSharedBuffer(UInt32 count, EPrimitiveType primitive);

		// Stencil routines
		virtual void beginStencil();
		virtual void endStencil();
		virtual void disableStencil();

		virtual Float32 levelOfDetail() const;

		virtual void setFillMethod(const CFillMethod* fillMethod);

		Bool isExtensionSupported(const char* extensionName) const;

	protected:
		virtual CTextureImpl* createTextureImpl(const CTexture* texture, const CImageImpl* imageImpl);
		virtual void setTextureImpl(const CTextureImpl* textureImpl);

	private:
		void* sharedBufferOfSize(UInt32 size);
		//void drawRectWithGLMode(const CRectangle& rect, int mode);

		void* mSharedBuffer;
		UInt32 mSharedBufferSize;

		CFont mFont;
};

	} // namespace le
} // namespace sokira

#endif // not defined SL_LE_gui_slCOpenGLRenderingContext_h
