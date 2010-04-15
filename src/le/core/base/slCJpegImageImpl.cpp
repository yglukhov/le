
//#include <iostream>
#include <le/core/slCImage.h>
//#include <le/core/slCNumber.h>
#include "slCJpegImageImpl.hp"

#include "slCImageImpl.hp"
#include "slCImageFrameImpl.hp"

#include <jpeg/include/jpeglib.h>


namespace sokira
{
	namespace le
	{

static void onJpegError (j_common_ptr cinfo)
{
	throw cinfo;
}

void CJpegImageImpl::loadFromFileToImageImpl(FILE* file, CImageImpl* image)
{
	fseek(file, 0, SEEK_SET);

	jpeg_decompress_struct info;  //the jpeg decompress info
	jpeg_error_mgr jerr; // the error handler

	info.err = jpeg_std_error(&jerr);
	jerr.error_exit = onJpegError;

	try
	{
		jpeg_create_decompress(&info);       //sets info to all the default stuff

		jpeg_stdio_src(&info, file);    //tell the jpeg lib the file we'er reading

		jpeg_read_header(&info, TRUE);   //tell it to start reading it

		//if it wants to be read fast or not
	#if 1 // Fast decompression
		info.do_fancy_upsampling = FALSE;
	#endif

		jpeg_start_decompress(&info);    //decompress the file

		//set the x and y
		CSize2D size(info.output_width, info.output_height);

		EPixelFormat type = (info.num_components == 4)?ePixelFormatRGBA:ePixelFormatRGB;

		// read turn the uncompressed data into something ogl can read
		UInt8* pixelData = new UInt8[(UInt32)size.area() * info.num_components];

		UInt8* p1 = pixelData;
		UInt8** p2 = &p1;
		int numlines = 0;

		while (info.output_scanline < info.output_height)
		{
			numlines = jpeg_read_scanlines(&info, (JSAMPLE**)p2, 1);
			*p2 += numlines * 3 * info.output_width;
		}

		jpeg_finish_decompress(&info);   //finish decompressing this file

		image->insertFrame(0, CImageFrame(new CImageFrameImpl(size, type, pixelData, 0)));
	}
	catch (j_common_ptr cinfo)
	{
		std::cerr << "JPEG Error: ";
		(*cinfo->err->output_message) (cinfo);
	}
}

	} // namespace le
} // namespace sokira
