#include <math.h>
#include <GL/glut.h>
#include <iostream>
#include "include/LevelManager.h"

using namespace std;

//refreshsyncvert

int main(int argc, char **argv){
    int width=800, height=600;
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(200, 100);
	glutCreateWindow("Open Portal");
	glEnable(GL_CULL_FACE);
    glEnable(GL_ALPHA);

    LevelManager::init(width,height);

	glutMainLoop();
}
