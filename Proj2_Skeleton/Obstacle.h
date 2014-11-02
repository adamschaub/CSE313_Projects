// Obstacle.h: interface for the CObstacle class.
//
//////////////////////////////////////////////////////////////////////
 
#pragma once

#include "Point3d.h"

class CObstacle  
{
public: 
	CObstacle();
	virtual ~CObstacle();

public:
	virtual Point3d getLocation()
	{
		Point3d p;
		return p;

	};
	virtual void draw(bool){};
};

