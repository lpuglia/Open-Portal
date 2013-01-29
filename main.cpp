#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include "include/LevelManager.h"

using namespace std;

//refreshsyncvert

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA | GLUT_DEPTH);
	//glutInitWindowSize(width, height);
	//glutInitWindowPosition(200, 100);
	glutCreateWindow("Open Portal");
    glutFullScreen();

    LevelManager::init();
    glutMainLoop();
}
