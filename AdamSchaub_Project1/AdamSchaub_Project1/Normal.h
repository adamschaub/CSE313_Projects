// Normal.h: interface for the Normal class.
//
//////////////////////////////////////////////////////////////////////
   
#ifndef  NORMAL_H
#define NORMAL_H 

#include "Vector3d.h"

class Normal  
{
public:
	Normal();
	virtual ~Normal();

	//added = operator for easy normal copying
	Normal& operator=(const Normal& rhs){
		norm = rhs.norm;
		pt = rhs.pt;
		return * this;
	}
	

	Vector3d norm;
	Vector3d pt;

};

#endif 
