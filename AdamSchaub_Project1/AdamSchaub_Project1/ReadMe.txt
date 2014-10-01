========================================================================
    CONSOLE APPLICATION : AdamSchaub_Project1 Project Overview
========================================================================

RUNNING
=======
Included is a full Visual Studio project folder. All source files are the
same as in the "skeleton" project. It can be opened in run in Visual Studio.
See OVERVIEW for a description of the added funtionality.

Some object files are included:
	-bones.obj
	-bunny.obj
	-cow.obj
	-cube.obj
	-para.obj
	-cone.obj (an object file generated using this project, see below)

OVERVIEW
========
The project has been completed using the "skeleton" project provided 
online. The files that have been modified are documented here. This
implementation has accomplished the following:

	1. Sets up a fulstrum-perspective projection for objects.
	2. Implemented camera and object transformations (rotation,
		translation, and scaling)
	2. On loading a .obj file, calculates the normals used for lighting
		2a. Implements Newell's Method for calculating face normals
		2b. Implements Gourand's Method for calculating vertex normals
	3. Drawing face/vertex normals
	4x. Tessalation of a cone (using triangles to approximate). This
		is the set default when the program loads. 
	5x. You can write the current object to a file by entering capital 'O'
		on the keyboard. This will prompt the user for the name of a file
		to write to. The file is saved in the working directory

Items marked with an 'x' are extra credit implementations.

MODIFIED FILES
==============
Normal.h:
	-Added overloaded '=' opeartor to enable easier normal copying.

Mesh(.h/.cpp):
	-Implemented calcNewell
	-Implemented calcGourand
	-Implemented makeSurfaceMesh
		->Default creates a full cone using tessalateCone
	-Implemented tessalateCone
		->Turns the current mesh into a cone. Starts with a primitive
			tetrahedron. Vertices and faces are stored as constant arrays
			in Mesh.h
	-Implemented writefile
		->Write the currently viewed object to a specified file using .obj
			format
	-Implemented draw
		->Draws all faces/vertices and applies lighting using smooth or flat
			shading methods.
		->Optionally displays the normals of all verticies/faces used for lighting

CameraView(.h/.cpp):
	-Implemented projection method to set up fulstrum projection matrix
	-Implemented shapeTransformation to apply rotation/translation/scaling to shape
	-Implemented cameraTransformation to apply rotation/translation to camera

AdamSchaub_Project1.cpp:
	-Removed default loading of "cube.obj". Shape objects by default use the makeSurfaceMesh
		method to instantiate the surface mesh (see makeSurfaceMesh above)