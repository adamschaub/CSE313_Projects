#include "Mesh.h"
 
#include <windows.h>
#include <gl/Gl.h>
#include <gl/Glu.h>
#include <gl/glut.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
  
using namespace std;


Mesh::Mesh()
{
	shape = new Shape();

}


Mesh::Mesh(Shape *shape2)
{
	shape = shape2;
}



Mesh::~Mesh()
{

}



// Make the mesh: vertex list, face list, normal list.
void Mesh::makeSurfaceMesh()
{

	// ...  Extra Credits:
	// instead of reading an object file, make a tesselated mesh surface (e.g. cylinder, cone) 
	// by yourself using tesselation here.
	//start with octahedron of desired size
	pt.resize(0);
	face.resize(0);
	norm.resize(0);

	Vector3d v;
	VertexID vid;
	Face f;
	for(int i = 0; i < 4; i++) {
		v.set(tetrahedronPts[i][0], tetrahedronPts[i][1], tetrahedronPts[i][2]);
		pt.push_back(v);
		
		for(int j = 0; j < 3; j++) {
			vid.normIndex = vid.vertIndex = tetrahedronInd[i][j] - 1;
			f.vert.push_back(vid);
		}	
		f.nVerts = f.vert.size();
		face.push_back(f);
		f.vert.resize(0);
	}

	tessalateCone(1.0, 2.0, 2);

	norm.resize(pt.size());

	numVerts = pt.size();
	numFaces = face.size();
	numNorms = norm.size();

	calcNewell();
	calcGourand();
}



void Mesh::draw() // use openGL to draw this mesh
{
	for(unsigned int f = 0;f <face.size();f++) // for each face
	{
		glColor3f(1,1,1);

		if(!shape->getWire())  // draw in wireframe or solid mode?
		{
			glEnable(GL_LIGHTING);
			glEnable(GL_LIGHT0);
			glBegin(GL_POLYGON);
		}
		else
		{
			glDisable(GL_LIGHTING);
			glBegin(GL_LINE_LOOP);
		}
		for(int v=0;v<face[f].nVerts;v++) // for each vertex in this face
		{	
			int in = face[f].vert[v].normIndex; // index of this normal
			int iv = face[f].vert[v].vertIndex; // index of this vertex
			if(shape->getSmooth())
				glNormal3f(norm[in].norm.x, norm[in].norm.y, norm[in].norm.z);
			else
				glNormal3f(face[f].faceNorm.norm.x, face[f].faceNorm.norm.y, face[f].faceNorm.norm.z);

			glVertex3f(pt[iv].x, pt[iv].y, pt[iv].z);
		
		}
		glEnd();

	}


	if(shape->getNormals())  // drawing normal is enabled
	{
		glDisable(GL_LIGHTING);
		glColor3f(0, 1, 0);
		double NORM_SCALE = 0.1;
		glBegin(GL_LINES);
		if(shape->getSmooth()) {
			// .... If smooth shading, draw each vertex normal using a short line originating from the vertex
			for(auto normIter = norm.begin(), end = norm.end(); normIter != end; normIter++) {
				glVertex3d(normIter->pt.x, normIter->pt.y, normIter->pt.z);
				glVertex3d(normIter->pt.x + normIter->norm.x*NORM_SCALE, normIter->pt.y + normIter->norm.y*NORM_SCALE, normIter->pt.z + normIter->norm.z*NORM_SCALE);
			}
		}
		else {
			// .... If flat shading, draw each face normal using a short line originating from center of the face
			for(auto faceIter = face.begin(), end = face.end(); faceIter != end; faceIter++) {			
				glVertex3d(faceIter->faceNorm.pt.x, faceIter->faceNorm.pt.y, faceIter->faceNorm.pt.z);
				glVertex3d(faceIter->faceNorm.pt.x + faceIter->faceNorm.norm.x*NORM_SCALE, faceIter->faceNorm.pt.y + faceIter->faceNorm.norm.y*NORM_SCALE, faceIter->faceNorm.pt.z + faceIter->faceNorm.norm.z*NORM_SCALE);
			}
		}
		glEnd();	
	}
	

}


// Calculate Newell Face Normal 
void Mesh::calcNewell()
{
	for(auto faceIter = face.begin(), end = face.end(); faceIter != end; faceIter++) {
		//for each point and the next point in this face, get the sum for the face normal. Stop when last point is reached.
		//use indices here so we can mod vertex positions
		Normal ptNorm;  //initialized to (0,0,0)
		for(int ptIter = 0, len = faceIter->nVerts; ptIter < len; ptIter++) {
			Vector3d thisVert, nextVert;
			thisVert = pt[faceIter->vert[ptIter].vertIndex];
			nextVert = pt[faceIter->vert[(ptIter+1)%len].vertIndex]; 

			ptNorm.norm.x += (thisVert.y - nextVert.y)*(thisVert.z + nextVert.z);
			ptNorm.norm.y += (thisVert.z - nextVert.z)*(thisVert.x + nextVert.x);
			ptNorm.norm.z += (thisVert.x - nextVert.x)*(thisVert.y + nextVert.y);

			ptNorm.pt.x += thisVert.x/len;
			ptNorm.pt.y += thisVert.y/len;
			ptNorm.pt.z += thisVert.z/len;
		}
		ptNorm.norm.normalize();
		faceIter->faceNorm = ptNorm;
	}
}


//Calculate Normal at Vertices
void Mesh::calcGourand()
{
	for(int ptIter = 0, len = pt.size(); ptIter < len; ptIter++) {
		int numFaces = 0;
		Normal ptNorm;
		ptNorm.pt = pt[ptIter];
		for(auto faceIter = face.begin(), end = face.end(); faceIter != end; faceIter++) {
			for(int iter = 0, len = faceIter->nVerts; iter < len; iter++) {
				if(faceIter->vert[iter].vertIndex == ptIter) {
					ptNorm.norm.add(faceIter->faceNorm.norm);
					numFaces++;
				}
			}
		}
		ptNorm.norm.set(ptNorm.norm.x/numFaces, ptNorm.norm.y/numFaces, ptNorm.norm.z/numFaces);
		ptNorm.norm.normalize();
		norm[ptIter] = ptNorm;
	}
}

//tessalates a cone from a tetrahedron
void Mesh::tessalateCone(double radius, double height, int detail) {
	Vector3d top(0.0, 0.0, height);
	pt[0] = top;
	//get midpoint of all neighbors
	for(int ptIter = 1, len = pt.size(); ptIter < len; ptIter++) {
		Vector3d curr, next, n;
		curr = pt[ptIter];
		int nextInd = (ptIter+1)%len;
		if(nextInd == 0) nextInd++;
		next = pt[nextInd];
		curr.add(next);
		n = curr;
		n.normalize();
		n.set(n.x*radius, n.y*radius, n.z*radius);
		pt.insert(pt.begin()+ptIter+1, n); //inserts to the right of curr
		ptIter++;
		len++;
	}

	//get faces from the newly added points
	//point 0 is the top, the rest circle the base ccw
	face.resize(0);
	Face f;
	VertexID vid;
	for(int ptIter = 1, len = pt.size(); ptIter < len; ptIter++) {
		f.vert.resize(0);
		vid.normIndex = vid.vertIndex = 0;
		f.vert.push_back(vid);
		int nextIndex = (ptIter+1)%len;
		if(nextIndex == 0) nextIndex = 1;
		vid.normIndex = vid.vertIndex = nextIndex;
		f.vert.push_back(vid);
		vid.normIndex = vid.vertIndex = ptIter;
		f.vert.push_back(vid);
		f.nVerts = f.vert.size();
		face.push_back(f);
	}

	f.vert.resize(0);
	for(int ptIter = 1, len = pt.size(); ptIter < len; ptIter++) {
		vid.normIndex = vid.vertIndex = ptIter;
		f.vert.push_back(vid);
		f.nVerts = f.vert.size();
	}
	face.push_back(f);

	if(detail > 0) tessalateCone(radius, height, --detail);
}

void Mesh::readfile(string filename)
{
	// read a mesh from a Wavefront OBJ object model file.
	// fill in the content of the three lists

	ifstream in(filename.c_str());
	string s;
	double x,y,z;
	int vindex;

	Vector3d v;
	Face f;
	VertexID vid;

	norm.resize(0);
	face.resize(0);
	pt.resize(0);

	in >> s;
	while(1)
	{
		if(s=="v")
		{
			in >> x >> y >> z;
			v.set(x,y,z);
			pt.push_back(v);
			if(!(in >> s))
				break;

		}
		else if(s=="f")
		{

			while((in >> s) && s[0]>='0' && s[0]<='9')
			{
	
				vindex = atoi(s.c_str());
	
				vid.vertIndex = vid.normIndex = vindex-1;
				f.vert.push_back(vid);
				f.nVerts=f.vert.size();
			}
			face.push_back(f);
			f.vert.resize(0);
		}
		else
		{
			getline(in,s);
			if(!(in>>s))
				break;
		}
	} 

	norm.resize(pt.size());

	numVerts = pt.size();
	numFaces = face.size();
	numNorms = norm.size();

	calcNewell();
	calcGourand();

	in.close();
}

void Mesh::writefile(string filename)
{
	ofstream out(filename.c_str());
	out << std::setprecision(6) << std::fixed;
	for(auto ptIter = pt.begin(), end = pt.end(); ptIter != end; ptIter++) {
		out << "v " << ptIter->x << " " << ptIter->y << " " << ptIter->z << std::endl; 
	}

	for(auto faceIter = face.begin(), end = face.end(); faceIter != end; faceIter++) {
		out << "f ";
		for(int ptIter = 0, len = faceIter->nVerts; ptIter < len; ptIter++) {
			out << faceIter->vert[ptIter].vertIndex + 1 << " ";
		}
		out << std::endl;
	}
	
	out.close();
}
