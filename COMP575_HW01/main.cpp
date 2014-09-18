//
//  main.cpp
//  Test02
//
//  Created by Golden Compass on 9/17/14.
//  Copyright (c) 2014 Golden Compass. All rights reserved.
//

#include <iostream>
#include "Config.h"

using namespace std;

void changeSize(int w, int h) {
    
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;
    
	float ratio =  w * 1.0 / h;
    
	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);
    
	// Reset Matrix
	glLoadIdentity();
    
	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);
    
	// Set the correct perspective.
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);
    
	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);
}

void traceImage(void){

    RayTracer tracer;
    pixels = tracer.traceImage();
    
    
    
}

void renderScene(void) {
	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Reset transformations
	glLoadIdentity();
    
	// Set the camera
	gluLookAt(	0.0f, 0.0f, 10.0f,  // Eye
              0.0f, 0.0f,  0.0f,    // Center
              0.0f, 1.0f,  0.0f);   // Up
//    glRasterPos2i(0,0);
    glDrawPixels(WINDOW_WIDTH, WINDOW_HEIGHT, GL_RGBA, GL_FLOAT, pixels);
    
	glutSwapBuffers();
}

void keyboard (unsigned char key, int x, int y)
{
	switch ( key )
	{
		case 'q':
			exit(EXIT_SUCCESS);
			break;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv) {
    
	// init GLUT and create window
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	glutCreateWindow("Lighthouse3D- GLUT Tutorial");
    
    cout << "Start tracing image...\n";
    traceImage();
    
	// register callbacks
	glutDisplayFunc(renderScene);
	glutReshapeFunc(changeSize);
	glutIdleFunc(renderScene);
    glutKeyboardFunc(keyboard);
    
	// enter GLUT event processing cycle
	glutMainLoop();
    
	return 0;
}

