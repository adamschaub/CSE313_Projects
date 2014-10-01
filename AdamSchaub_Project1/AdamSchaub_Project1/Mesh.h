#ifndef MESH_H
#define MESH_H

#include "Face.h"
#include "Vector3d.h"
#include <vector>


class Shape;

#include "Shape.h"
#include "Normal.h"

using namespace std;

#define PI 3.1415

/**Basic information for constructing a tetrahedron**/
//Vertices for the tetrahedron
static double tetrahedronPts [4][3] = {
	{0.0, 0.0, 3.0}, 
	{1, 0.0, 0.0}, 
	{ -0.5, -0.86602, 0.0}, 
	{ -0.5, 0.86602, 0.0} 
};
//Faces for the tetrahedron
static int tetrahedronInd [4][3] = {
	{1, 3, 2},
	{1, 4, 3},
	{1, 2, 4},
	{2, 3, 4}
};

// ############### Mesh ######################
class Mesh{
   private:
	int numVerts;		// number of vertices in the mesh
	int numNorms;		// number of normal vertices for the mesh
	int numFaces;		// number of faces in the mesh

	vector <Vector3d> pt;      // list of 3D vertices
	vector <Normal> norm;    // list of normals
	vector <Face> face;		// list of faces

	Shape *shape;

   public:
	Mesh();			// constructor
	Mesh(Shape *shape); // constructor
	~Mesh();			// destructor
	void draw();
	void makeSurfaceMesh();
	void calcNewell();
	void calcGourand();

	void readfile(string filename);
	void writefile(string filename);
	void tessalateCone(double radius, double height, int detail);
};

#endif