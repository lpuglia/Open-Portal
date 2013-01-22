#include "../include/LevelManager.h"

Character* LevelManager::he;
EntityList LevelManager::entList;
int LevelManager::width;
int LevelManager::height;

void LevelManager::init(int width, int height){
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0, 0.0, 0.0, 1.0);

    glutDisplayFunc(display);
	glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouseMotion);
    glutSpecialFunc(specialKeyboard);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);

    LevelManager::width=width;
    LevelManager::height=height;

    he = new ViewManager(vector3(1.0,0.0,5.0), 1.80, width, height, &entList);
    entList.push_back(he);

    ///TODO "LOAD LEVEL ELEMENTS"
    entList.push_back(new Cube(vector3(3.0,10.0,3.0),vector3(0.0,0.0,1.0),&entList));
    /*entList.push_back(new Cube(vector3(3.0,10.0,-3.0),vector3(1.0,0.0,1.0),&entList));
    entList.push_back(new Cube(vector3(-3.0,10.0,-3.0),vector3(1.0,0.0,0.0),&entList));
    entList.push_back(new Cube(vector3(-3.0,10.0,3.0),vector3(2.0,0.0,1.0),&entList));
    entList.push_back(new Cube(vector3(6.0,10.0,3.0),vector3(4.0,0.0,1.0),&entList));
    entList.push_back(new Cube(vector3(6.0,10.0,-3.0),vector3(1.0,0.0,4.0),&entList));
    entList.push_back(new Cube(vector3(-6.0,10.0,-3.0),vector3(2.0,0.0,5.0),&entList));
    entList.push_back(new Cube(vector3(-6.0,10.0,3.0),vector3(4.0,0.0,5.0),&entList));
    entList.push_back(new Cube(vector3(3.0,10.0,6.0),vector3(0.0,0.0,1.0),&entList));
    entList.push_back(new Cube(vector3(3.0,10.0,-6.0),vector3(0.0,0.0,6.0),&entList));
    entList.push_back(new Cube(vector3(-3.0,10.0,-6.0),vector3(6.0,0.0,1.0),&entList));
    entList.push_back(new Cube(vector3(-3.0,10.0,6.0),vector3(7.0,0.0,1.0),&entList));
    entList.push_back(new Cube(vector3(6.0,10.0,6.0),vector3(8.0,0.0,5.0),&entList));
    entList.push_back(new Cube(vector3(6.0,10.0,-6.0),vector3(6.0,0.0,1.0),&entList));
    entList.push_back(new Cube(vector3(-6.0,10.0,-6.0),vector3(4.0,0.0,3.0),&entList));
    entList.push_back(new Cube(vector3(-6.0,10.0,6.0),vector3(10.0,0.0,7.0),&entList));*/

    entList.push_back(new Bound());

    /*Cube Level */
    entList.push_back(new Wall(vector3(0.0,0.0,10.0),vector3(0.0,0.0,-1.0),vector3(-10.0,0.0,0.0),vector3(10.0,0.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),vector3(1.0,0.0,0.0)));
    entList.push_back(new Wall(vector3(0.0,0.0,-10.0),vector3(0.0,0.0,1.0),vector3(-10.0,0.0,0.0),vector3(10.0,0.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),vector3(1.0,1.0,0.0)));
    entList.push_back(new Wall(vector3(10.0,0.0,0.0),vector3(-1.0,0.0,0.0),vector3(-10.0,0.0,0.0),vector3(10.0,0.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),vector3(0.0,1.0,1.0)));
    entList.push_back(new Wall(vector3(-10.0,0.0,-15.0),vector3(-1.0,0.0,0.0),vector3(-5.0,0.0,0.0),vector3(5.0,0.0,0.0),vector3(5.0,10.0,0.0),vector3(-5.0,10.0,0.0),vector3(1.0,0.5,0.0)));
    entList.push_back(new Wall(vector3(-10.0,0.0,15.0),vector3(-1.0,0.0,0.0),vector3(-5.0,0.0,0.0),vector3(5.0,0.0,0.0),vector3(5.0,10.0,0.0),vector3(-5.0,10.0,0.0),vector3(0.0,0.5,1.0)));
    entList.push_back(new Wall(vector3(-20.0,0.0,20.0),vector3(0.0,0.0,-1.0),vector3(-10.0,0.0,0.0),vector3(10.0,0.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),vector3(1.0,0.0,0.5)));
    entList.push_back(new Wall(vector3(-20.0,0.0,-20.0),vector3(0.0,0.0,1.0),vector3(-10.0,0.0,0.0),vector3(10.0,0.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),vector3(1.0,0.0,1.0)));
    entList.push_back(new Wall(vector3(-30.0,0.0,0.0),vector3(1.0,0.0,0.0),vector3(-20.0,0.0,0.0),vector3(20.0,0.0,0.0),vector3(20.0,10.0,0.0),vector3(-20.0,10.0,0.0),vector3(0.0,0.0,1.0)));
    entList.push_back(new Wall(vector3(-10.0,-10.0,0.0),vector3(-1.0,0.0,0.0),vector3(-10.0,0.0,0.0),vector3(10.0,0.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),vector3(0.5,0.6,1.0)));
    //entList.push_back(new LevelDelimiter(vector3(0.0,10.0,0.0),vector3(0.0,-1.0,0.0),vector3(1.0,0.0,0.0),vector3(-10.0,-10.0,0.0),vector3(10.0,-10.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),vector3(1.0,1.0,1.0)));
    entList.push_back(new Floor(vector3(0.0,0.0,0.0),vector3(0.0,1.0,0.0),vector3(1.0,0.0,0.0),vector3(-10.0,-10.0,0.0),vector3(10.0,-10.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),vector3(0.0,1.0,0.0)));
    entList.push_back(new Floor(vector3(-20.0,-5.0,0.0),vector3(0.0,1.0,0.5),vector3(1.0,0.0,0.0),vector3(-10.0,-10.0,0.0),vector3(10.0,-10.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),vector3(0.5,1.0,0.5)));
    //entList.push_back(new Floor(vector3(-20.0,-15.0,5.0),vector3(0.0,1.0,-0.5),vector3(1.0,0.0,0.0),vector3(-10.0,-10.0,0.0),vector3(10.0,-10.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),vector3(0.7,0.9,0.5)));

    //<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    he->init();
}

void LevelManager::reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.5, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void LevelManager::idle(void){
    list<Entity*>::iterator p;
    Bound* bound = new Bound();
    for (p = entList.begin(); p!=entList.end(); p++){
        if (typeid(**p) != typeid(*(bound)))
            ((Item*)(*p))->movement();
        else break;
    }
    glutPostRedisplay();
}

void LevelManager::mouse(int button, int state, int x, int y){
    he->mouse(button,state,x,y);
}

void LevelManager::mouseMotion(int x, int y){
    he->mouseMotion(x,y);
}

void LevelManager::keyboard(unsigned char key, int x, int y){
    he->keyboard(key);
}

void LevelManager::keyboardUp(unsigned char key, int x, int y){
    he->keyboardUp(key);
}

void LevelManager::specialKeyboard(int key, int x, int y){
    he->specialKeyboard(key);
}

void LevelManager::display(){
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

    list<Entity*>::iterator p = entList.begin();
    (*p)->drawEntity();

    for (p++; p!=entList.end(); p++){
        glPushMatrix();
        (*p)->drawEntity();
        glPopMatrix();
    }
	glutSwapBuffers();
}
