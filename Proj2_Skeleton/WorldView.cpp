
// WorldView.cpp: implementation of the CWorldView class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WorldView.h" 
#include "Scene.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CWorldView::CWorldView(int w, int h)
{

	width = w;
	height = h;

	pScene = new CScene();

}


CWorldView::~CWorldView()
{

	delete pScene;

}

void CWorldView::projection()
{

	// ... change and add in code here and elsewhere to implemenet antialiasing using A-buffer
	// refer to Red book chapter 10 and example 10-2.

	// set up world camera viewing projection (perspective)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glFrustum(-1, 1, -1, 1, 1, 40);
} 

void CWorldView::draw()  
{

	float lt_posit[4] = {-20.0f, -20.0f, 30.0f, 1.0f};

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	worldCameraTransformation();

	// position light
	glLightfv(GL_LIGHT0, GL_POSITION, lt_posit);
	glEnable(GL_LIGHTING);

	glPushMatrix();
	pScene->setLightPosition(lt_posit);
	pScene->sceneTransformation();
	pScene->draw();
	glPopMatrix();
	
}


void CWorldView::worldCameraTransformation()
{
	// move camera back so that the scene is visible
	glTranslated(0, 0, -15);

	// rotate by alt/azim
	glRotated(-60, 1, 0, 0);
//	glRotated(15, 0, 1, 0);
//	glRotated(0, 0, 0, 1);


}

