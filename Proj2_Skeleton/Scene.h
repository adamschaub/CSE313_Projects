// Scene.h: interface for the CScene class. 
//
//////////////////////////////////////////////////////////////////////

#pragma once

#include "Bug.h"
#include "Point3d.h"
#include "stdafx.h"
#include "Obstacle.h"
#include "Tree.h"
#include "Rand.h"

#define numCritters 3 // number of follower critters, not counting the main bug
#define numObstacles 1 // number of obstacles

class CScene  
{
private:
	double tx, ty, tz, rx, ry, rz,scale;

	Point3d freeSpotGaussian(float minDist, float sigma);
	Point3d freeSpotUniform(float minDist, float rad);
	bool isFreeSpot(Point3d p, float minDist);

public:
	CScene();
	virtual ~CScene();

	double getTx() {return tx;}
	double getTy() {return ty;}
	double getTz() {return tz;}
	double getRx() {return rx;}
	double getRy() {return ry;}
	double getRz() {return rz;}
	double getScale() {return scale;}

	void setTx(double x) {tx=x;}
	void setTy(double y) {ty=y;}
	void setTz(double z) {tz=z;}
	void setRx(double x) {rx=x;}
	void setRy(double y) {ry=y;}
	void setRz(double z) {rz=z;}
	void setScale(double s)  {scale =s;}

	void sceneTransformation();

	CRand rgen;  // random number generator
	
	CBug * pMainBug;

	CBug * pCritters[numCritters];   // small follower critters

	CObstacle *pObstacles[numObstacles];

	// current clock reading for the scene
	double clock;

	//center of the world
	Point3d origin;

	float light_position[4];


	// things related to clock
private:
	int frameNumber;

public:

	int getFrameNumber() {return frameNumber;}
	void incrementFrameNumber() {frameNumber++;}
	void resetClock() {
		clock = 0;
		frameNumber = 0;
	}
	void setLightPosition(float pos[4]){

		light_position[0] = pos[0];
		light_position[1] = pos[1];
		light_position[2] = pos[2];
		light_position[3] = pos[3];
	}
	
	void shadowProject();   // projection matrix 

	void build();   // build the scene (create critters, trees, obstacles, etc. in the scene)
	void process(double elapsed);   // update the scene (animate) after "elapsed" seconds

	void draw();



};


 