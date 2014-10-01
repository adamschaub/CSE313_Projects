// CameraView.h: interface for the CCameraView class.

//////////////////////////////////////////////////////////////////////
  
#ifndef CAMERAVIEW_H
#define CAMERAVIEW_H

#include "Camera.h"
#include "Vector3d.h"
#include "Shape.h"

#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>

using namespace std;

class CCameraView  
{
private:
	int width;
	int height;

	Shape *shape;
	CCamera cam;  // camera

public:
	CCameraView(int w, int h);
	virtual ~CCameraView();
	Shape& getShape()  {return *shape;}

public:

	void setShape(Shape& shape2) {shape = &shape2;}

	void projection();  // always perspective projection for camera
	void draw();  

	void cameraTransformation();  // apply camera's viewing transformation
	void shapeTransformation();  // apply object transformation


};

#endif 

