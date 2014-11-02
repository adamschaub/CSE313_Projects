// Tree.cpp: implementation of the CTree class.
//
//////////////////////////////////////////////////////////////////////

#include "Tree.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTree::CTree(CRand rgen, int level, int branching, double trunkLen, double trunkDiam, double xposition, double yposition)
{

	// set tree position
	xpos = xposition;
	ypos = yposition;

	cylDisplayList = -1;

	// construct tree
	tree = new CTreePart(rgen, level, branching, trunkLen, trunkDiam, 0, 0, 0);

}

CTree::~CTree()
{

	delete tree;
}

void CTree::draw(bool setColor)
{
	initialize(false);
	glPushMatrix();
	glTranslated(xpos, ypos, 0);
	tree->draw(cylDisplayList, setColor);
	glPopMatrix();
	uninitialize();
}

void CTree::initialize(bool detail)
{
	int res = detail ? 15 : 5;

	// make display list for cylinder
	cylDisplayList = glGenLists(1);

	GLUquadric * qobj = gluNewQuadric();

	// create a cylinder centered on z-axis from z = 0...1 (height 1),
	// that has a diameter of 1
	gluQuadricDrawStyle(qobj, GLU_FILL);
	gluQuadricNormals(qobj, GLU_SMOOTH);
	glNewList(cylDisplayList, GL_COMPILE);
	gluCylinder(qobj, 0.5, 0.50, 1.0, res, 1);
	glEndList();

	gluDeleteQuadric(qobj);

}

void CTree::uninitialize()
{
	glDeleteLists(cylDisplayList,1);
}
