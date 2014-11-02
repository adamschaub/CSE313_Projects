// Bug.cpp: implementation of the CBug class.
//
//////////////////////////////////////////////////////////////////////

#include "Bug.h" 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBug::CBug(double bugScale, double bugPx, double bugPy, double bugVx, double bugVy)
{

	legNum=6;
	pNum = 2;
	numParams=12;
	numKeyT=5;
	stride = 1.3;

	pos.set(bugPx, bugPy, 0);
	vel.set(bugVx, bugVy, 0);
	scale = bugScale;

	param = new double[numParams];

	cylDisplayList = -1;
	conDisplayList = -1;
	sphDisplayList = -1;

	// initialize keyframe parameters
	keyFrames[0][0] = 30;
	keyFrames[0][1] = 10;
	keyFrames[0][2] = 30;
	keyFrames[0][3] = 30;
	keyFrames[0][4] = 0;
	keyFrames[0][5] = 30;
	keyFrames[0][6] = 0;
	keyFrames[0][7] = 10;
	keyFrames[0][8] = -30;
	keyFrames[0][9] = 10;
	keyFrames[0][10] = -30;
	keyFrames[0][11] = 30;

	keyFrames[1][0] = 20;
	keyFrames[1][1] = 10;
	keyFrames[1][2] = 40;
	keyFrames[1][3] = 30;
	keyFrames[1][4] = 10;
	keyFrames[1][5] = 30;
	keyFrames[1][6] = -10;
	keyFrames[1][7] = 10;
	keyFrames[1][8] = -40;
	keyFrames[1][9] = 10;
	keyFrames[1][10] = -20;
	keyFrames[1][11] = 30;

	keyFrames[2][0] = 30;
	keyFrames[2][1] = 30;
	keyFrames[2][2] = 30;
	keyFrames[2][3] = 10;
	keyFrames[2][4] = 0;
	keyFrames[2][5] = 10;
	keyFrames[2][6] = 0;
	keyFrames[2][7] = 30;
	keyFrames[2][8] = -30;
	keyFrames[2][9] = 30;
	keyFrames[2][10] = -30;
	keyFrames[2][11] = 10;
	
	keyFrames[3][0] = 40;
	keyFrames[3][1] = 30;
	keyFrames[3][2] = 20;
	keyFrames[3][3] = 10;
	keyFrames[3][4] = -10;
	keyFrames[3][5] = 10;
	keyFrames[3][6] = 10;
	keyFrames[3][7] = 30;
	keyFrames[3][8] = -20;
	keyFrames[3][9] = 30;
	keyFrames[3][10] = -40;
	keyFrames[3][11] = 10;


	keyFrames[4][0] = 30;
	keyFrames[4][1] = 10;
	keyFrames[4][2] = 30;
	keyFrames[4][3] = 30;
	keyFrames[4][4] = 0;
	keyFrames[4][5] = 30;
	keyFrames[4][6] = 0;
	keyFrames[4][7] = 10;
	keyFrames[4][8] = -30;
	keyFrames[4][9] = 10;
	keyFrames[4][10] = -30;
	keyFrames[4][11] = 30;

	// time at each key frame, keyT between [0,1]
	keyT[0] = 0.0;
	keyT[1] = 0.25;
	keyT[2] = 0.5;
	keyT[3] = 0.75;
	keyT[4] = 1.0;


	keyframe(0);

}

CBug::~CBug()
{

}


void CBug::keyframe(double distanceTraveled)
{
	// convert t to T (to cyclic time in [0,1], scaled by bug step size

	// scale to match keyframe speed
	double T= distanceTraveled/(scale*stride);

	// find [0,1] component of time
	T -= (int) T;

	// the following two line are place holder for the initial main bug
	for (int i=0; i<numParams; i++)
		param[i] = keyFrames[0][i];

	// ... add in code here
	// find two nearest keyframes
	// interpolate keyframes (linearly) to compute current keyframe parameters and save in "param"

}


void CBug::draw(bool setColor, Vector3d color)
{
	
	initialize(true);

	glPushMatrix();
	transform();

	// Body
	glPushMatrix();
	{
		glTranslated(0, 0, 0.75);
		if (setColor){
			//glColor3d(0.4, 0.5, 0.65);
			glColor3d(color.x, color.y, color.z);
		}

		glPushMatrix();
		{
			glScaled(1.2, 1, 1);
			glCallList(sphDisplayList);
		}
		glPopMatrix();

		// Head (relative to body)
		glPushMatrix();
		glTranslated(0.7, 0.0, 0.0);
		glScaled(0.5, 0.5, 0.5);
		if(setColor){
			//glColor3d(0.45, 0.35, 0.55);
			glColor3d(color.x, color.y, color.z);
		}
		glCallList(sphDisplayList);
		glPopMatrix();

		// Legs (relative to body)
		double legThick = 0.15;
		if(setColor){
			//glColor3d(0.3, 0.3, 0.3);
			glColor3d(max(0, color.x-0.5),max(0, color.y-0.2), max(0, color.z-0.2));
		}

		for (int i=0; i < legNum/2; i++){
			// left legs
			glPushMatrix();
			{
			glRotated(param[2*i*pNum], 0, 0, 1);
			glRotated(90-param[2*i*pNum+1], 1, 0, 0);

			glPushMatrix();
			{
				glScaled(legThick, legThick, 1.0);
				glCallList(cylDisplayList);
			}
			glPopMatrix();

			glTranslated(0, 0, 1);
			glRotated(90, 1, 0, 0);
			glScaled(legThick, legThick, 1.0);
			glCallList(conDisplayList);
			}
			glPopMatrix();

			// right legs
			glPushMatrix();
			{
				glRotated(-param[(2*i+1)*pNum], 0, 0, 1);
				glRotated(-90+param[(2*i+1)*pNum+1], 1, 0, 0);

				glPushMatrix();
				{
					glScaled(legThick, legThick, 1.0);
					glCallList(cylDisplayList);
				}
				glPopMatrix();

				glTranslated(0, 0, 1);
				glRotated(-90, 1, 0, 0);
				glScaled(legThick, legThick, 1.0);
				glCallList(conDisplayList);
			}
			glPopMatrix();
		}
	}

	// body
	glPopMatrix();

	// bug
	glPopMatrix();

	uninitialize();

}
  

// compute bug heading (rotation around z-axis) using bug velocity
double CBug::bugHeading()
{
	double theta;

	// the following line is place holder 
	theta =-90; 

	// ... add in code here to compute bug heading based on velocity
	// Hint: you may need to use the atan2() function
	// if velocity is zero, use acceleration direction to compute heading

	return theta;
}

void CBug::transform()
{

	double theta = bugHeading();   // rotation around z axis

	glTranslated(pos.x, pos.y, pos.z);
	glRotated(theta*180/PI, 0, 0, 1);
	glScaled(scale, scale, scale);

}

void CBug::inverseTransform(){
	double theta = bugHeading();

	glScaled(1.0/scale, 1.0/scale, 1.0/scale);
	glRotated(-theta*180/PI, 0, 0, 1);
	glTranslated(-pos.x, -pos.y, -pos.z);

}


void CBug::initialize(bool detail){

	int res = detail ? 20 : 6;

	// make display list for cylinder
	cylDisplayList = glGenLists(3);
	conDisplayList = cylDisplayList +1;
	sphDisplayList = cylDisplayList +2;

	GLUquadric * qobj = gluNewQuadric();

	// create a cylinder centered on z-axis from z = 0...1 (height 1),
	// that has a diameter of 1
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	glNewList(cylDisplayList, GL_COMPILE);
	gluCylinder(qobj, 0.5, 0.50, 1.0, res, 1);
	glEndList();

	// create a cone centered on z-axis from z = 0...1 (height 1) with top at 
	// z=1, that has a diameter of 1 at bottom
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	glNewList(conDisplayList, GL_COMPILE);
	gluCylinder(qobj, 0.5, 0.0, 1.0, res, 1);
	glEndList();


	// create a sphere at the origin with diameter 1
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	glNewList(sphDisplayList, GL_COMPILE);
	gluSphere(qobj, 0.5, res, res);
	glEndList();

	gluDeleteQuadric(qobj);


}

void CBug::uninitialize(){

	glDeleteLists(cylDisplayList,1);
	glDeleteLists(conDisplayList,1);
	glDeleteLists(sphDisplayList,1);
}
