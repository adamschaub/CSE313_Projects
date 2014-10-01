#include "Shape.h"

 
 
Shape::Shape()
{
	
	tx = 0.0;
	ty = 0.0;
	tz = -0.5;
	rx = 0.0;
	ry = 0.0;
	rz = 0.0;
	scale = 1.0;
	smooth = false;  // true    // smooth shading or not
	normals = false;  // true   // draw normal or not
	wire =  true;	
	//wire = false;
	
	
	mesh = new Mesh(this);
	mesh->makeSurfaceMesh();  // read in a mesh, make a tesselated mesh, etc.
}


Shape::~Shape(){

	delete mesh;
}

Shape& Shape::operator=(const Shape& rhs)
{
	tx = rhs.tx;
	ty = rhs.ty;
	tz = rhs.tz;
	rx = rhs.rx;
	ry = rhs.ry;
	rz = rhs.rz;
	scale = rhs.scale;
	smooth = rhs.smooth;
	normals = rhs.normals;
	wire = rhs.wire;
	return * this;
}


void Shape::draw()
{
	mesh->draw();
}

void Shape::readfile(string filename)
{
	mesh->readfile(filename);
}

void Shape::writefile(string filename)
{
	mesh->writefile(filename);
}