#ifndef FACE_H
#define FACE_H
 
#include "VertexID.h"
#include "Vector3d.h"
#include "Normal.h"
 
 
#include <vector>
using namespace std;


#define NULL 0
class Face{
    public:
	int nVerts; // number of vertices in this face
	Normal faceNorm;		// face normal vector

	vector <VertexID> vert;   // the list of vertex and normal indices
	Face( ){nVerts = 0; } // constructor
	
	~Face( ){ nVerts = 0;} // destructor
};

#endif