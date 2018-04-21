#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include "LevelManager.h"

using namespace std;

//refreshsyncvert

int main(int argc, char **argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_ALPHA | GLUT_DEPTH);
	glutCreateWindow("Open Portal");
    glutFullScreen();

    LevelManager::init();
    glutMainLoop();
}
