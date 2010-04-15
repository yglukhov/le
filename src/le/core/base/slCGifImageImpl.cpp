#include <iostream>
#include <le/core/slCImage.h>
#include <le/core/slCNumber.h>
#include "slCImageFrameImpl.hp"

#include "slCGifImageImpl.hp"
#include "slCImageImpl.hp"

#include <gif/include/gif_lib.h>


namespace sokira
{
	namespace le
	{

static int le_gif_input_func(GifFileType *gifFile, GifByteType * data, int byteCount)
{
	return fread(data, 1, byteCount, (FILE*)gifFile->UserData);
}

static inline UInt8* graphicControlExtension(const SavedImage& image)
{
	for (int i = 0; i < image.ExtensionBlockCount; ++i)
	{
		if (image.ExtensionBlocks[i].Function == 0xf9) // our function
		{
			return (UInt8*)image.ExtensionBlocks[i].Bytes;
		}
	}
	return 0;
}

static inline Bool imageIsTransparent(UInt8* graphicControlExtension)
{
	return *graphicControlExtension & 1;
}

static inline UInt16 frameDuration(UInt8* graphicControlExtension)
{
	return CNumber::littleEndianToHost(*(UInt16*)(graphicControlExtension + 1)); // CNumber::bigEndianToHost(d.duration);
}

static inline UInt8 transparentColor(UInt8* graphicControlExtension)
{
	return *(graphicControlExtension + 3);
}

void CGifImageImpl::loadFromFileToImageImpl(FILE* file, CImageImpl* image)
{
	fseek(file, 0, SEEK_SET);
	GifFileType *gifFile = DGifOpen(file, le_gif_input_func);
	if (gifFile)
	{
		if (DGifSlurp(gifFile) != GIF_OK)
		{
			std::cout << "Failed opening file!" << std::endl;
		}

		for (UInt32 i = 0; i < (UInt32)gifFile->ImageCount; ++i)
		{
			ColorMapObject *colorMap = gifFile->SavedImages[i].ImageDesc.ColorMap;
			if (!colorMap) colorMap = gifFile->SColorMap;
			if (!colorMap)
			{
				std::cout << "No colormap for frame " << i << std::endl;
				continue;
			}

			UInt8* gce = graphicControlExtension(gifFile->SavedImages[i]);

			Bool imageTransparent = imageIsTransparent(gce);
			EPixelFormat format = (imageTransparent)?(ePixelFormatRGBA):(ePixelFormatRGB);
			UInt8 transparentColorIndex = transparentColor(gce);

			CSize2D size(gifFile->SavedImages[i].ImageDesc.Width, gifFile->SavedImages[i].ImageDesc.Height);
			UInt8* pixelData = new UInt8[(UInt32)size.area() * format / 8];
			UInt8* iP = pixelData;
			for (UInt32 j = 0; j < size.area(); ++j)
			{
				GifColorType &colorMapEntry = colorMap->Colors[gifFile->SavedImages[i].RasterBits[j]];
				*iP = colorMapEntry.Red;
				++iP;
				*iP = colorMapEntry.Green;
				++iP;
				*iP = colorMapEntry.Blue;
				++iP;
				if (imageTransparent)
				{
					*iP = (gifFile->SavedImages[i].RasterBits[j] == transparentColorIndex)?(0):(0xff);
					++iP;
				}
			}
//			std::cout << "IMAGE " << i << " duration: " << frameDuration(gce) << std::endl;
			image->insertFrame(i, CImageFrame(new CImageFrameImpl(size, format, pixelData, frameDuration(gce))));
		}

		DGifCloseFile(gifFile);
	}
	else
	{
//		PrintGifError();
		std::cout << "Error opening gif file" << std::endl;
	}

}

	} // namespace le
} // namespace sokira
