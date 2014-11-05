// Tree.h: interface for the CTree class.
//
//////////////////////////////////////////////////////////////////////
 
#pragma once

#include "Obstacle.h"
#include "TreePart.h"
#include "Point3d.h"
#include "Rand.h"
 
const double NORM_TREE_HEIGHT = 4.0;
const double MIN_TREE_HEIGHT = 4.0;

class CTree  : public CObstacle
{
public:
	CTree(CRand rgen, int level, int branching, double trunkLen, double trunkDiam, double xposition, double yposition);
	virtual ~CTree();

public:
	double xpos, ypos;

	// base of tree
	CTreePart * tree;

	// display list id for cylinder
	int cylDisplayList;

	Point3d getLocation()
	{
		Point3d p;
		p.set(xpos, ypos,0);
		return p;
	}

	void draw(bool setColor);

	void initialize(bool detail);
	void uninitialize();

};

