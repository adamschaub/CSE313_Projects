// Critter.h: interface for the CCritter class.
//
//////////////////////////////////////////////////////////////////////
 
#pragma once

#include "Point3d.h"
#include "Vector3d.h"
#include "stdafx.h"
#include "Rand.h"

// this abstract class implements methods for keeping track of the position, velocity and acceleration
// of a critter (such as a bug), for integrating these quantities over time, and for computing accelerations
// that give the bug wandering behavior
class CCritter  
{
public:
	// position, velocity and acceleration
	Point3d pos;
	Vector3d vel, acc;

	// total distance traveled (used for keyframing)
	double dist;

	// last time and direction of wandering
	double lastWander;
	Point3d pWander;



public:
	CCritter();
	virtual ~CCritter();

//	virtual void draw(bool setColor);
//	virtual void keyframe(double t);


	CRand rgen; 

	Point3d getLocation() {return pos;}
	double distTraveled() {return dist;}

	// method to integrate acc to get updated vel and pos.
	// also, compute the distance traveled
	// assume acc has already been computed
	void integrate(double dt);
	
	
	// reset acceleration to zero
	void accelReset(){ acc.set(0,0,0);}

	void accelCap(double max){
		double mag = acc.magnitude();
		if(mag > max){
			acc.normalize();
			acc.scale(max);
		}
	}

	void velCap(double max){
		double mag = vel.magnitude();
		if( mag > max){
			vel.normalize();
			vel.scale(max);
		}
	}

	// add in viscous drag (assume mass of 1): a+=-k*v (k>0)
	void accelDrag(double k);
	
	// add in attraction acceleration: a += direction*(k*dist^exp)
	// (negative value of k produce repulsion; positive k produce attraction; exp should be negative.)
	void accelAttract(Point3d p, double k, double exp);

	// add in acceleration towards a temporary goal, which changes regularly
	void accelWander(double k, double t, double often);

};


