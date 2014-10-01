// Camera.cpp: implementation of the CCamera class.
 
//////////////////////////////////////////////////////////////////////
 
#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include "Camera.h"

using namespace std;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCamera::CCamera()
{

}

CCamera::~CCamera()
{

}

void CCamera::init()
{

	  tx = 0;
	  ty = 0;
	  tz = -4;  // camera at (0, 0, 4)
	  xRoll = 0;
	  yRoll = 0;
	  zRoll = 0;

	  right = 1.0;
	  left = -1.0;
	  top = 1.0;
	  bottom = -1.0;
	  nearVal = 1;  
	  farVal = 40;   


}
void CCamera::setCurrentView(double l, double r, double b, double t)
{
	left = l;
	right = r;
	bottom = b;
	top = t;
}

void CCamera::reset()
{
	init();
}
