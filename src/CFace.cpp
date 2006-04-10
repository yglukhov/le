
#include "CFace.h"
#include "CControl.h"

#include <glut/le_glut.h>
///////////////////////////////////////////////////////////////////////////////
void initMatrixWithZero(float* matrix)
{
	for (int i = 0; i < 16; ++i)
	{
		matrix[i] = 0;
	}
}

CFace::CFace(Point3DMatrix pointList) :
	mPointMatrix(pointList)
{
	initMatrixWithZero(mMatrix);
}

CFace::CFace()
{
	initMatrixWithZero(mMatrix);
}


///////////////////////////////////////////////////////////////////////////////
void CFace::setDimension(unsigned width, unsigned height)
{
	mPointMatrix.resize(width);
	for (unsigned i = 0; i < width; ++i)
	{
		mPointMatrix[i].resize(height);
	}
}

CFace::Point3DMatrix& CFace::getPointMatrix()
{
	return mPointMatrix;
} 

///////////////////////////////////////////////////////////////////////////////
void CFace::rotate(float angle, float x, float y, float z)
{
	glPushMatrix();
	glLoadMatrixf(mMatrix);
	glRotatef(angle, x, y, z);
	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix);
	glPopMatrix();
}

void CFace::translate(float x, float y, float z)
{
	glPushMatrix();
	glLoadMatrixf(mMatrix);
	glTranslatef(x, y, z);
	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix);
	glPopMatrix();
}

void CFace::scale(float x, float y, float z)
{
	glPushMatrix();
	glLoadMatrixf(mMatrix);
	glScalef(x, y, z);
	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix);
	glPopMatrix();
}


///////////////////////////////////////////////////////////////////////////////
bool CFace::pivotPoint(unsigned x, unsigned y)
{
	bool returnValue = false;

	if ((mPointMatrix.size() > x) && (mPointMatrix[x].size() > y))
	{
		mPivotPoint = mPointMatrix[x][y];
		returnValue = true;
	}

	return returnValue;
}

void CFace::pivotPoint(CPoint3D point)
{
	mPivotPoint = point;
}

CPoint3D CFace::pivotPoint() const
{
	return mPivotPoint;
}


///////////////////////////////////////////////////////////////////////////////
void CFace::draw()
{
	ControlList::const_iterator end = mChilds.end();
	for(ControlList::const_iterator it = mChilds.begin(); it != end; ++it)
	{
		glPushMatrix();
		glLoadMatrixf(mMatrix);
		(*it)->draw();
		glPopMatrix();
	}
}

void CFace::addChild(CControl* child)
{
	ENTER_LOG;

	if(child)
	{
		mChilds.push_back(child);

		child->parent(NULL);
		child->face(this);
	}
}
///////////////////////////////////////////////////////////////////////////////
void CFace::multiplyMatrix(float& matrix)
{
	glPushMatrix();
	glLoadMatrixf(mMatrix);
	glMultMatrixf(mMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix);
	glPopMatrix();
}

void CFace::eraseMatrix()
{
	initMatrixWithZero(mMatrix);
}