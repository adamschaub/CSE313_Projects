// TreePart.h: interface for the CTreePart class.
//
//////////////////////////////////////////////////////////////////////
 
#pragma once

#include "stdafx.h"
#include "Rand.h"
#include <vector>

class CTreePart  
{
public:
	CTreePart(CRand rgen, int depth, int numBranch, double partLen, double partWid,  double partTz, double partRx, double partRz);
	virtual ~CTreePart();

public:
	
	static const int MIN_X_ROT = 30.0;
	static const int MAX_X_ROT = 70.0;
	static const int DIF_Z_ROT = 50;  //maximum difference in z rotation for branches
	// transformation for this branch/leaf
	double Tz, Rx, Rz;

	// leaf or trunk
	boolean leaf;

	// size of part
	double length, width;

	// children
	std::vector<CTreePart *> parts;

	void draw(int cylDisplayList, bool setColor);

};
