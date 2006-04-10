
#include "CFace.h"
#include "CControl.h"
#include "CTheme.h"
#include "CScreen.h"

#include <glut/le_glut.h>
///////////////////////////////////////////////////////////////////////////////
void initMatrixWithZero(float* matrix)
{
	for (int i = 0; i < 16; ++i)
	{
		if (i%4 == (int)(i/4))
		{
			matrix[i] = 1;
		}
		else
		{
			matrix[i] = 0;
		}
	}
/*
	glPushMatrix();
	glMultMatrixf(matrix);
	glGetFloatv(GL_PROJECTION_MATRIX, matrix);
	glPopMatrix();*/
}

CFace::CFace(Point3DMatrix pointList) :
	mPointMatrix(pointList)
{
	//initMatrixWithZero(mMatrix);
	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix);
}

CFace::CFace()
{
	glGetFloatv(GL_MODELVIEW_MATRIX, mMatrix);
	//initMatrixWithZero(mMatrix);
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
		glMultMatrixf(mMatrix);
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

		child->parent(CScreen::instance());
		child->face(this);
	}
}

bool CFace::onMouse(EMouseButton button, EButtonState state, const CPoint& point)
{
	ENTER_LOG;

	//rotate(0.5, 1,0,0);
//	mMatrix[0] += 0.1;
	//scale(2.2,2.1,1.3);
	rotate(0.01,1,1,1);
	ControlList::iterator end = mChilds.end();
	for (ControlList::iterator it = mChilds.begin(); it != end; ++it)
	{
		if (CTheme::instance()->hitTest(*it, point) && (*it)->onMouse(button, state, point))
			return true;
	}

	return false;
}

bool CFace::hitTest(const CPoint& point) const
{
	ControlList::const_iterator end = mChilds.end();
	for (ControlList::const_iterator it = mChilds.begin(); it != end; ++it)
	{
		if (CTheme::instance()->hitTest(*it, point))
			return true;
	}
	return false;
}
///////////////////////////////////////////////////////////////////////////////
void CFace::multiplyMatrix(float& matrix)
{
	glPushMatrix();
	glLoadMatrixf(mMatrix);
	glMultMatrixf(&matrix);
	glGetFloatv(GL_PROJECTION_MATRIX, mMatrix);
	glPopMatrix();
}

void CFace::eraseMatrix()
{
	initMatrixWithZero(mMatrix);
}