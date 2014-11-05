#pragma once

#include <math.h>
 
class Vector3d
{
public:
	double x;
	double y;
	double z;

public:
	Vector3d():x(0),y(0),z(0) {}
	Vector3d(double xx, double yy, double zz) {x=xx;y=yy;z=zz;}
	~Vector3d() {}

	Vector3d& operator=(const Vector3d& rhs){
		x = rhs.x;
		y = rhs.y;
		z = rhs.z;
		return * this;
	}
	
	void negate() {x = -x; y=-y; z=-z;}

	void set(double cx, double cy, double cz) {x=cx; y=cy; z=cz;}
	void setVec(double v[3]) {x = v[0]; y=v[1]; z=v[2];}

	void add(Vector3d u)  {x += u.x; y += u.y; z += u.z;}
	void sub(Vector3d u)  {x -= u.x; y -= u.y; z -= u.z;}
	void cross(Vector3d u){	
		 
		 double nx = y*u.z - z*u.y;
		 double ny = z*u.x - x*u.z;
		 double nz = x*u.y - y*u.x;

		 x = nx; y = ny; z = nz;
	}

	double magnitude() {return sqrt(x*x+y*y+z*z);}

	void normalize()  {
		double mag = magnitude();
		x /= mag;
		y /= mag;
		z /= mag;
	}

	double dot(Vector3d u) {return (x*u.x+y*u.y+z*u.z);}

	void scale(double s) {
		x *=s;
		y *=s;
		z *=s;
	}

	void scaleAdd(double s, Vector3d vs, Vector3d vo){

		Vector3d c;
		c.add(vs);
		c.scale(s);
		c.add(vo);
		x =c.x;
		y =c.y;
		z =c.z;
	}
};