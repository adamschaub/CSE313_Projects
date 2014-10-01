// CameraView.cpp: implementation of the CCameraView class.
 
//////////////////////////////////////////////////////////////////////
  

#include "CameraView.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCameraView::CCameraView(int w, int h)
{

	width = w;
	height = h;

	cam.init();

}


CCameraView::~CCameraView()
{
	delete shape;
}

void CCameraView::projection()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(cam.getLeft(), cam.getRight(), cam.getBottom(), cam.getTop(), cam.getNear(), cam.getFar());
}

void CCameraView::draw()  
{
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// viewing transformations
	cameraTransformation();

	glPushMatrix();
		// modeling transformations
		shapeTransformation();
		shape->draw();
	glPopMatrix();

}


void CCameraView::cameraTransformation()
{
	glTranslated(cam.getTx(), cam.getTy(), cam.getTz()); 
	glRotated(cam.getXRoll(), 1, 0, 0); //rotate about x-axis (horizontal)
	glRotated(cam.getYRoll(), 0, 1, 0); //rotate about y-axis (vertical)
	glRotated(cam.getZRoll(), 0, 0, 1); //rotate about z-axis (perpendicular to screen)
}


void CCameraView::shapeTransformation()
{
	glTranslated(shape->getTx(), shape->getTy(), shape->getTz()); 
	glScaled(shape->getScale(), shape->getScale(), shape->getScale());
	glRotated(shape->getRx(), 1, 0, 0); //rotate about x-axis (horizontal)
	glRotated(shape->getRy(), 0, 1, 0); //rotate about y-axis (vertical)
	glRotated(shape->getRz(), 0, 0, 1); //rotate about z-axis (perpendicular to screen)
}



