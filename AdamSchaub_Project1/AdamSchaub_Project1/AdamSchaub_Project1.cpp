#include "stdafx.h"
#include <iostream>
#include <windows.h>
#include <vector>
#include <cmath>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <string>
 
#include "CameraView.h"
#include "Face.h"
 
using namespace std;

#define PI 3.1415
#define NULL 0

//######################## GLOBALS #################################
int screenWidth = 480, screenHeight = 480;
int window1; // window1 for showing camera view
int window2; // window2 for showing world

// variables attached to the camera view window
CCameraView viewWindow(screenWidth, screenHeight);
bool pan_win1 = true;  // pan if true; rotate if false;
int x_win1, y_win1;  // mouse coordinates in window 1 
char rotateAxis_win1 ='z'; // initial setting to rotate around z axis


// initialize the shape 
Shape* shape = new Shape();

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< display for camera view >>>>>>>>>>>>>>>>>>>>>>
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  // clear screen and depth buffer

	// Define material and light
     float lt_posit[4] = {  5.0f,  5.0f,  30.0f, 0.0f };
     float lt_ambi[4]  = {   0.5f,   0.5f,   0.5f, 1.0f };
     float lt_diff[4]  = {   1.0f,   1.0f,   1.0f, 1.0f };
     float mat_ambi[4] = {   0.1f,   0.3f,   0.3f, 1.0f };
     float mat_diff[4] = {   0.4f,   0.6f,   0.6f, 1.0f };
     float mat_spec[4] = {   0.3f,   0.3f,   0.3f, 1.0f };

     glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambi);
     glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diff);
     glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_spec);
     glMaterialf( GL_FRONT, GL_SHININESS, 10);

     glLightfv(GL_LIGHT0, GL_AMBIENT, lt_ambi);
     glLightfv(GL_LIGHT0, GL_DIFFUSE, lt_diff);
     glEnable(GL_LIGHT0);

     glLightfv(GL_LIGHT0, GL_POSITION, lt_posit);

	 // Call functions to perform OpenGL projection, viewing, modeling and object drawing
	 viewWindow.setShape(*shape);
	 viewWindow.projection();
	 viewWindow.draw();
		
	 glFlush();
	 glutSwapBuffers(); // swap buffers for smooth animation

}
//<<<<<<<<<<<<<<<<<<<<<<< myKeys >>>>>>>>>>>>>>>>>>>>>>>>
void myKeys(unsigned char key, int x, int y)
{
	string filename;

	switch(key)  
	{
		case 'q':
			exit(0); // quit
		case 'o':
			printf("Enter an object file to be read: ");
			cin >> filename;
			shape->readfile(filename);
			break;
		case 'O':
			printf("Enter file name to write object to: ");
			cin >> filename;
			shape->writefile(filename);
			break;
		case 'C':
			// reset shape to the default cube
			shape->readfile("cube.obj");
			printf("Drawing Cube\n");
			break;
		case 'r':
			pan_win1=false; // mouse move to change rotation
			printf("Rotation enabled.\n");
			break;
		case 't':
			pan_win1 =true;
			printf("Translation Enabled.\n");
			break;	// mouse move to change translation
		case 'x':		// change rotation axis to x
			rotateAxis_win1 = 'x';
			printf("X Axis Rotate Enabled\n");
			break;
		case 'y':		// change rotation axis to y
			rotateAxis_win1 = 'y';
	        printf("Y Axis Rotate Enabled.\n");
			break;
		case 'z':		// change rotation axis to z
			rotateAxis_win1 = 'z';
			printf("Z Axis Rotate Enabled.\n");
			break;
		case '+':	// scaling up object
			shape->setScale(shape->getScale()+0.1);
			printf("Scale Factor Increased.\n");
			break;
		case '-':
			shape->setScale(shape->getScale()-0.1);
			printf("Scale Factor Decreased.\n");
			break;
		case 's':
			glShadeModel(GL_SMOOTH);
			shape->setSmooth(true);
			printf("Smooth Shading Enabled.\n");
			break;
		case 'f':
			glShadeModel(GL_FLAT);
			shape->setSmooth(false);
			printf("Flat Shading Enabled.\n");
			break;
		case 'n':
			shape->setNormals(true);
			printf("Normal Display Enabled.\n");
			break;
		case 'N':
			shape->setNormals(false);
			printf("Normal Display Disabled.\n");
			break;
		case 'p':
			shape->setWire(false);
			printf("Polygon Mode Enabled.\n");
			break;
		case 'w':
			shape->setWire(true);
			printf("Wireframe Mode Enabled.\n");
			break;
		default: break;
	}

	// update camera view
	display();

}

// mouse down, record current mouse coordinates
void MouseButton(int button, int state, int x, int y)
{
  // Respond to mouse button presses.
  // If button1 pressed, mark this state so we know in motion function.
  if (button == GLUT_LEFT_BUTTON)
  {
          x_win1 = x;
	  y_win1 = y;
  }
}

void MouseMotion(int x, int y)
{

	// this will change object parameters

	double dx = (double)x-x_win1;
	double dy = (double)y-y_win1;


	if(pan_win1){	// change translation
		

		shape->setTx(shape->getTx()+dx/50);
		shape->setTy(shape->getTy()-dy/50);
	

	}else { // change rotation, only use the x distance 

		switch(rotateAxis_win1){
			case 'x':
				shape->setRx(shape->getRx()+dx/5);
				break;
			case 'y':
				shape->setRy(shape->getRy()+dx/5);
				break;
			case 'z':
				shape->setRz(shape->getRz()+dx/5);
				break;
			default:
				break;
		}

	}

	x_win1=x;
	y_win1=y;
	
	// update camera view
	display();

}



//<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>
void myInit(int window_id)
{
	glutSetWindow(window_id);
	glClearColor(0.0f,0.0f,0.0f,0.0f);  // background is black
	glViewport(0, 0, screenWidth, screenHeight);

	// enable openGL depth test
	glEnable(GL_DEPTH_TEST);

	// Set the shading model
	
	glShadeModel(GL_SMOOTH);

	glEnable(GL_NORMALIZE);


	// Set the polygon mode to fill
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	window1 = glutCreateWindow("Camera View");
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeys);
	glutMouseFunc (MouseButton);
	glutMotionFunc(MouseMotion);

	myInit(window1);

	//window2 = glutCreateWindow("World View");

	glutMainLoop();
}
