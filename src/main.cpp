#include "ofMain.h"
#include "ofApp.h"

//========================================================================
int main( ){

	ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context

	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());

	/*
		Ideas
		* Make a button selection screen for different algorithms
		*    - Recursive
		*    - DFS
		*    - BFS 
		Make each maze algorithm a class that contains a method to generate the maze
		*    This method populates a vector with all the points in the maze that were visited
		*        This way, we can "step through" the maze solving process
		* 
	*/

}
