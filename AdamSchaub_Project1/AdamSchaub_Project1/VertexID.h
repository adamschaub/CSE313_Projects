#ifndef VERTEXID_H
#define VERTEXID_H
  
 
// ############### Vertex ID ######################
class VertexID{
   public:
	int vertIndex; // index of this vertex in the vertex list
	int normIndex; // index of this vertex’s normal
	VertexID(){vertIndex = 0; normIndex = 0;}
};

#endif