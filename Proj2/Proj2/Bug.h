// Bug.h: interface for the CBug class.
//

#pragma once

#include "Critter.h"
#include "stdafx.h"
#include "Vector3d.h"

class CBug : public CCritter
{
public:
	CBug(double bugScale, double bugPx, double bugPy, double bugVx, double bugVy);
	virtual ~CBug();

	int legNum, pNum;

	// Key frame parameters
	double keyFrames[5][12];
	
	// Time stamps for keyframes, in [0,1]
	double keyT[5];

	
	int numParams;	
	int numKeyT;
	double stride;

	double* param;
	double scale;
 
	int cylDisplayList;
	int conDisplayList;
	int sphDisplayList;

	double bugHeading();
	void transform();
	void inverseTransform();
	void initialize(bool detail);
	void uninitialize();

public:
	
	void draw(bool setColor, Vector3d color);
	void keyframe(double distanceTraveled); // the rate at which a bug's legs move should depend on the speed the bug is traveling and the bug's size

};