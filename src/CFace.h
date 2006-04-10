#pragma once

#include <vector>
#include <list>

#include "Types.h"

class CWindow;
class CControl;
class CBox;

class CFace
{
 public:	
	typedef std::vector<std::vector<CPoint3D> > Point3DMatrix;
	typedef std::list<CControl*> ControlList;
//	typedef float[16] TransformationMatrix;
	
//	CFace(const CBox& box);
	CFace(Point3DMatrix pointList);
	CFace();
	
	void setDimension(unsigned width, unsigned height);
	Point3DMatrix& getPointMatrix(); 
	
	void rotate(float angle = 0.0, float x = 0.0, float y = 0.0, float z = 1.0);
	void translate(float x = 0.0, float y = 0.0, float z = 0.0);
	void scale(float x = 1.0, float y = 1.0, float z = 1.0);
	
	bool pivotPoint(unsigned x = 0, unsigned y = 0);
	void pivotPoint(CPoint3D point);
	CPoint3D pivotPoint() const;
	
	void draw();
	void addChild(CControl* child);
	
 private:
	void matrix(float& matrix);
	void multiplyMatrix(float& matrix);
	void eraseMatrix();

	ControlList mChilds;
	Point3DMatrix mPointMatrix;
	float mMatrix[16];//glLoadMatrixf
	CPoint3D mPivotPoint;
};