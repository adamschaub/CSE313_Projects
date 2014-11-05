#include "stdafx.h"
#include "WorldView.h"

//######################## GLOBALS #################################
int screenWidth = 640, screenHeight = 640;
 
// variables attached to the world view
CWorldView wv(screenWidth, screenHeight);
bool pan = true;  // pan if true; rotate if false;
int x_win1, y_win1;  // mouse coordinates in window 1 (world view)
char rotateAxis ='z'; // initial setting to rotate around z axis

double dt = 1.0/30.0;  // in seconds, that is, 30 frames per second, so call display() once every 1/30 seconds
double clockSpeed =1.0;  // initialize clock speed; larger value leads to faster animation.

//<<<<<<<<<<<<<<<<<<<<<<<<<<<<< display for world view >>>>>>>>>>>>>>>>>>>>>>
void display(void)
{
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	wv.projection();  
	wv.draw();
 
	glFlush();
	glutSwapBuffers(); // swap buffers for smooth animation

}
//<<<<<<<<<<<<<<<<<<<<<<< myKeys >>>>>>>>>>>>>>>>>>>>>>>>
void myKeys(unsigned char key, int x, int y)
{

	CScene & scene = wv.getScene();

	switch(key)  
	{
		case 'q':	// Quit
			exit(0);
		case 'r':	// Mouse move to change rotation
			pan=false;
			printf("Mouse move to rotate object around Z axis...\n");
			break;
		case 't':	// Mouse move to change translation
			pan =true;
			printf("Mouse move to translate object...\n");
			break;
		case 'x':	// Change rotation axis to x
			rotateAxis = 'x';
			printf("Mouse move to rotate object around X axis...\n");
			break;
		case 'y':	// Change rotation axis to y
			rotateAxis = 'y';
	        printf("Mouse move to rotate object around Y axis...\n");
			break;
		case 'z':	// Change rotation axis to z
			rotateAxis = 'z';
			printf("Mouse move to rotate object around Z axis...\n");
			break;
		case '+':	// Scaling up object
			scene.setScale(scene.getScale()+0.1);
			printf("zooming in...\n");
			break;
		case '-':	// Scaling down ojbect
			scene.setScale(scene.getScale()-0.1);
			printf("zooming out\n");
			break;
		case 'f':  // faster animation
			clockSpeed +=0.1;
			printf("faster animation\n");
			break;
		case 'l':  // slower animation
			clockSpeed -=0.1;
			printf("slower animation\n");
			break;
		default: break;
	}

	// Update world camera view
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

	CScene & scene = wv.getScene();

	double dx = (double)x-x_win1;
	double dy = (double) y-y_win1;


	if(pan){	// change translation
		

		scene.setTx(scene.getTx()+dx/50);
		scene.setTy(scene.getTy()-dy/50);
	

	}else { // change rotation, only use the x distance 

		switch(rotateAxis){
			case 'x':
				scene.setRx(scene.getRx()+dx/5);
				break;
			case 'y':
				scene.setRy(scene.getRy()+dx/5);
				break;
			case 'z':
				scene.setRz(scene.getRz()+dx/5);
				break;
			default:
				break;
		}

	}

	x_win1=x;
	y_win1=y;
	
	// Update world camera view
	glutPostRedisplay();
	
}


//<<<<<<<<<<<<<<<<<<<<<<<<<<< timer >>>>>>>>>>>>>>>
void timer(int) // the timer callback function
{
		CScene & scene = wv.getScene();

		// time elapsed is (dt) seconds, controlled by clockSpeed
		double elapsed = dt*clockSpeed;

		// time updated, need to process the scene (update acceleration, velocity, position, etc.)
		scene.process(elapsed);

		display();
		glutTimerFunc((int)(dt*1000), timer,1); // reset timer

}

//<<<<<<<<<<<<<<<<<<<<< myInit >>>>>>>>>>>>>>>>>>
void myInit()
{

	
	glClearColor(0.58f,0.74f,0.98f,0.0f);  // background is sky blue
	glViewport(0, 0, screenWidth, screenHeight);

	// enable openGL depth test
	glEnable(GL_DEPTH_TEST);

	// Set the polygon mode to fill
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Set the shading model
	//glShadeModel(GL_SMOOTH);

	
	// Define material and light
	float lt_diff[4] = {1.0f, 1.0f, 1.0f, 1.0f};
	float mat_ambi[4] = {0.1f, 0.3f, 0.3f, 1.0f};
	float mat_diff[4] = {0.4f, 0.6f, 0.6f, 1.0f};
	float mat_spec[4] = {0.5f, 0.5f, 0.5f, 1.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambi);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diff);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_diff);
	glMaterialf(GL_FRONT, GL_SHININESS, 5);

	glLightfv(GL_LIGHT0, GL_DIFFUSE, lt_diff);
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);

	glColorMaterial(GL_FRONT, GL_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);
}

//<<<<<<<<<<<<<<<<<<<<<< main >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(screenWidth, screenHeight);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("World View");
	glutDisplayFunc(display);
	glutKeyboardFunc(myKeys);
	glutMouseFunc (MouseButton);
	glutMotionFunc(MouseMotion);

	myInit();
	glutTimerFunc((int)(dt*1000), timer,1);


	glutMainLoop();
}
