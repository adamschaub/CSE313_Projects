// WorldView.h: interface for the CWorldView class.
//
//////////////////////////////////////////////////////////////////////
 
#pragma once

#include "stdafx.h"
#include "Vector3d.h"
#include "Scene.h"

class CWorldView  
{
private:
	int width;
	int height;

	CScene* pScene;

public:
	CWorldView(int w, int h);
	virtual ~CWorldView();

public: 


	CScene & getScene()  {return (*pScene);}

	void projection();
	void draw();  

	void worldCameraTransformation();  // apply world camera transformation

};


