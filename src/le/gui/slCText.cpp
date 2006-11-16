#include "slCText.h"
#include "slTypes.h"
#include <glut/slGlut.h>

LE_NAMESPACE_START

CText::CText() :
	mFormat(0)
{

}

CText::CText(const std::string& string, unsigned format) :
	mString(string), mFormat(format)
{

}

CText::CText(const char* string, unsigned format) :
	mString(string), mFormat(format)
{

}

void CText::draw(const CPoint& position) const
{
	glRasterPos2f(position.x(), position.y() + 7);

	for(const char* c = mString.c_str(); *c; ++c)
	{
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
	}
}

void CText::format(unsigned Format)
{
	mFormat = Format;
}

void CText::text(const char* textString)
{
	mString = textString;
}


LE_NAMESPACE_END
