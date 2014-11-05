========================================================================
    CONSOLE APPLICATION : AdamSchaub_Project2 Project Overview
========================================================================

RUNNING
=======
Included is a full Visual Studio project folder. All source files are the
same as in the "skeleton" project. It can be opened in run in Visual Studio.
See OVERVIEW for a description of the added funtionality.

OVERVIEW
========
The project has been completed using the "skeleton" project provided 
online. The files that have been modified are documented here. This
implementation has accomplished the following:

	1. Complete TreePart constructor to recursively generate tree parts.
	2. Updated call to CScene::build()
		-Multiple trees made at one time
		-Placed trees in a uniformly random position with no collisions
	3. Updated Rand.h to set seed for random number generator

Items marked with an 'x' are extra credit implementations.

MODIFIED FILES
==============
TreePart(.h/.cpp):
	-Added some constants for recursively generating TreeParts
	-Completed default constructor

Scene(.h/.cpp):
	-Changed default numObstacles to 4
	-updated isFreeSpot to check for NULL obstacles in pObstacles because
		previous implementation caused a segmentation fault

Tree(.h/.cpp):
	-Added constants for tree generation

Rand.h:
	-Added setSeed function to set seed of random number generator