/* 
	Author: Adam Schaub
	Course: CSE 313
	Assignment: Homework 1

	Program description:
		Draw a five-leaf rose polar plot which varies with time. The plot is a line with
		a gradient from the leading point being traced back to the tail. Drawing is done
		using timesteps gained from GetTickCount, so don't let this run for more than 49.7 days.
 */

#include "stdafx.h"   // Necessary for a project you created in VS
#include <windows.h>
#include <iostream>
#include <stdlib.h>
#include <math.h>   // Needed for sin, cos, etc.
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>

using namespace std;

/*CONSTANTS*/
const int screenWidth = 480, screenHeight = 480;
const float PI = 3.14159265;			// We need to define PI to do polar plots
const float INTERVAL = PI - PI/24;			//the size of the interval to be drawn for the rose
const float ANGLE_SPEED = PI/10;			//the angle to advance the interval, measured in rad/s
const int NUM_INTERVAL_POINTS = 256;	//controls the number of points drawn in the interval
const float THETA_STEP = INTERVAL/(float)NUM_INTERVAL_POINTS; //the angle difference between each drawn point

/*INSTANCE VARIABLES*/
float theta;		//marks the beginning of the interval to be drawn, measured in radians
DWORD lastUpdate;	//the system time of the last update measured in ms
bool withColorize;	//false if greyscale, true if we should add hue

void updateColors(GLdouble &r, GLdouble &g, GLdouble &b) {
	GLdouble colorStep = 1.0/NUM_INTERVAL_POINTS; //how much the color changes between points	
	if(!withColorize) {
		r += colorStep;
		b += colorStep;
		g += colorStep;
	}
	//logic for incrementing rgb over the purble spectrum
	else {
		//increment blue to max first, then red, then green
		colorStep *= 3;
		if(b > 1.0)  {
			if(r > 1.0) {
				g += colorStep/1.5;	//green is increased less to keep the tail from getting very white near the front
			}
			else {
				r += colorStep;
			}
		}
		else {
			b += colorStep;
		}
	}
}

void FiveLeafRose()
{
	/* Starting at theta
		->set the initial color attribute
		->draw NUM_INTERVAL_POINTS from theta to (theta + INTERVAL)
	*/
	GLdouble r, g, b;
	r = 0.0;
	g = 0.0;
	b = 0.0;

	float startTheta = theta;
	float endTheta = theta + INTERVAL;
	glBegin(GL_LINE_STRIP);
	while(startTheta < endTheta) {
		GLdouble x, y, radius;
		radius = cos(5*startTheta);
		x = radius*cos(startTheta);
		y = radius*sin(startTheta);
		
		glColor3f(r, g, b);
		glVertex2d(x, y);

		startTheta += THETA_STEP;
		updateColors(r, g, b);
	}
	glEnd();
	glFlush();
}

void display(void)
{
	// Clear the screen
	glClear(GL_COLOR_BUFFER_BIT); 
	// Load the identity matrix to undo any rotations from the previous frame
	glLoadIdentity();

	// Call our custom drawing function
	FiveLeafRose();

	// Swap buffers to display the completed buffer (double-buffering)
	glutSwapBuffers();
}

void myKeys(unsigned char key, int x, int y)
{
	switch(key)  
	{
		// Quit
		case 'q':	exit(0); // quit
					break;
		case 'h':	printf("Changing hue\n");
					withColorize = withColorize ? false : true;	//reverse hue
					break;
		default:	printf("Don't have an option for that key...\n");
	    //... Add other keyboard controls for any extra credit features.

	}
	// Call the display function to reflect our changes
	display();
}

/* This is the idle function. */
void spinner(void) // the idle function
{
	/* Use system ticks to get time since last update, and change theta accordingly. Idle func update rate isn't dependable. */
	DWORD now = GetTickCount();
	DWORD elapsed = now - lastUpdate;
	
	theta += ANGLE_SPEED * elapsed/1000; //divided elapsed time by 1000 to convert to seconds
	if(theta > PI) theta -= PI;	//so theta doesn't grow indefinitely
	lastUpdate = now;

	// Redraw to reflect the changes
	display();
}

// Do some basic OpenGL initialization to set up 2D graphics.
void myInit(int argc, char **argv)
{
	/* INITIALIZE INSTANCE VARIABLES */
	theta = 0;	//starts drawing the rose at angle 0
	lastUpdate = GetTickCount();	//System ticks since last update
	withColorize = false;	//draw black and white by default

	// Set background color to black
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	// Initialize the projection matrix with the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// Initialize the modelview matrix with the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	/* Set up a coordinate system so we don't have
	 * to convert to screen coordinates manually */
	gluOrtho2D(-1.1, 1.1,-1.1,1.1);
	// Set our OpenGL viewport to be the size of the glut window
	glViewport(0,0,screenWidth,screenHeight); //the default

}

// Our main function
void main(int argc, char **argv)
{
	// Initialize glut
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	// Set some parameters for our OpenGL window before creating it
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);

	// Create a window with a title
	glutCreateWindow("Adam Schaub Homework 01");

	// Register callbacks for glut
	glutKeyboardFunc(myKeys);
	glutDisplayFunc(display);
	glutIdleFunc(spinner);


	// Initialize our OpenGL window
	myInit(argc, argv);
	
	// Start the glut loop to begin drawing, etc.
	glutMainLoop();
}