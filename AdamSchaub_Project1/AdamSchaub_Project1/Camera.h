// Camera.h: interface for the CCamera class.
  
//////////////////////////////////////////////////////////////////////
#ifndef CAMERA_H
#define CAMERA_H
  
// class for camera
class CCamera  
{
public:
	CCamera();
	virtual ~CCamera();

private:
	double tx, ty, tz, xRoll, yRoll, zRoll;
	double left, right, bottom, top, nearVal, farVal;
	


public:
	void init();
	void setCurrentView(double l, double r, double b, double t);
	void reset();

	double getTx() {return tx;}
	double getTy() {return ty;}
	double getTz() {return tz;}
	double getXRoll() {return xRoll;}
	double getYRoll() {return yRoll;}
	double getZRoll() {return zRoll;}

	double getNear() {return nearVal;}
	double getFar() {return farVal;}

	double getLeft(){return left;}
	double getRight() {return right;}
	double getBottom() {return bottom;}
	double getTop() {return top;}
	bool isPerspective() {return true;}

	void setNear(double n) {nearVal=n;}
	void setFar(double f) {farVal=f;}

	void setTx(double x) {tx=x;}
	void setTy(double y) {ty=y;}
	void setTz(double z) {tz=z;}
	void setXRoll(double xR) {xRoll = xR;}
	void setYRoll(double yR) {yRoll = yR;}
	void setZRoll(double zR) {zRoll = zR;}


};

#endif 
