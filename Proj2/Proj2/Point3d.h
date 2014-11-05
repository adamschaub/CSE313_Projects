#pragma once 

#include "Vector3d.h"

class Point3d {
public:
	double x, y, z;
public:
	Point3d() : x(0), y(0), z(0) {}
	Point3d(double xx, double yy, double zz) {x=xx; y=yy; z=zz;}
	~Point3d() {}

	Point3d& operator=(const Point3d& p){
		x = p.x;
		y = p.y;
		z = p.z;
		return * this;
	}
	
	void set(double cx, double cy, double cz) {x=cx; y=cy; z=cz;}
	void add(Vector3d v){
		x += v.x;
		y += v.y;
		z += v.z;
	}

	double distance(Point3d p){
		return sqrt((x-p.x)*(x-p.x)+(y-p.y)*(y-p.y)+(z-p.z)*(z-p.z));
	}
}; 