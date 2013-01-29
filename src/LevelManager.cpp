#include "../include/LevelManager.h"

Character* LevelManager::he;
Portal* LevelManager::blue;
Portal* LevelManager::orange;
EntityList LevelManager::entList;
int LevelManager::frameCount=0;
int LevelManager::currentTime=0;
int LevelManager::previousTime=0;
int LevelManager::fps=0;

void LevelManager::init(){

    glutDisplayFunc(display);
	glutMouseFunc(mouse);
    glutKeyboardFunc(keyboard);
	glutKeyboardUpFunc(keyboardUp);
    glutPassiveMotionFunc(mouseMotion);
    glutSpecialFunc(specialKeyboard);
	glutIdleFunc(idle);
	glutReshapeFunc(reshape);
	glEnable(GL_CULL_FACE);

    //texture manager
    glEnable(GL_DEPTH_TEST);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

    he = new ViewManager(vector3(1.0,0.0,5.0), 1.80, &entList);
    entList.push_back(he);
    blue = new Portal(vector3(0.0,100.0,0.0),vector3(0.0,0.0,-1.0),true,&entList);
    entList.push_back(blue);
    orange = new Portal(vector3(0.0,100.0,0.0),vector3(0.0,0.0,-1.0),false,&entList);
    blue->set_other_portal(orange);
    orange->set_other_portal(blue);
    entList.push_back(orange);

    ///TODO "LOAD LEVEL ELEMENTS"
    entList.push_back(new Cube(vector3(3.0,10.0,3.0),vector3(0.0,0.0,1.0),&entList));
    entList.push_back(new Bound());

    /*First Level */
    entList.push_back(new Wall(vector3(0.0,0.0,10.0),vector3(0.0,0.0,-1.0),vector3(-10.0,0.0,0.0),vector3(10.0,0.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),"wall.png"));
    entList.push_back(new Wall(vector3(0.0,0.0,-10.0),vector3(0.0,0.0,1.0),vector3(-10.0,0.0,0.0),vector3(10.0,0.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),"wall.png"));
    entList.push_back(new Wall(vector3(10.0,0.0,0.0),vector3(-1.0,0.0,0.0),vector3(-10.0,0.0,0.0),vector3(10.0,0.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),"wall.png"));
    entList.push_back(new Wall(vector3(-10.0,0.0,-15.0),vector3(-1.0,0.0,0.0),vector3(-5.0,-30.0,0.0),vector3(5.0,-30.0,0.0),vector3(5.0,10.0,0.0),vector3(-5.0,10.0,0.0),"wall.png"));
    entList.push_back(new Wall(vector3(-10.0,0.0,15.0),vector3(-1.0,0.0,0.0),vector3(-5.0,-30.0,0.0),vector3(5.0,-30.0,0.0),vector3(5.0,10.0,0.0),vector3(-5.0,10.0,0.0),"wall.png"));
    entList.push_back(new Wall(vector3(-20.0,0.0,20.0),vector3(0.0,0.0,-1.0),vector3(-10.0,-30.0,0.0),vector3(10.0,-30.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),"wall.png"));
    entList.push_back(new Wall(vector3(-20.0,0.0,-20.0),vector3(0.0,0.0,1.0),vector3(-10.0,-30.0,0.0),vector3(10.0,-30.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),"wall.png"));
    entList.push_back(new Wall(vector3(-30.0,0.0,0.0),vector3(1.0,0.0,0.0),vector3(-20.0,-30.0,0.0),vector3(20.0,-30.0,0.0),vector3(20.0,10.0,0.0),vector3(-20.0,10.0,0.0),"wall.png"));
    entList.push_back(new Wall(vector3(-10.0,-10.0,0.0),vector3(-1.0,0.0,0.0),vector3(-10.0,-20.0,0.0),vector3(10.0,-20.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),"wall.png"));

    entList.push_back(new Floor(vector3(0.0,0.0,0.0),vector3(0.0,1.0,0.0),vector3(1.0,0.0,0.0),vector3(-10.0,-10.0,0.0),vector3(10.0,-10.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),"floor.png"));
    entList.push_back(new Floor(vector3(-20.0,-5.0,0.0),vector3(0.0,1.0,0.5),vector3(1.0,0.0,0.0),vector3(-11.185,-10.0,0.0),vector3(10.0,-10.0,0.0),vector3(10.0,10.0,0.0),vector3(-11.185,10.0,0.0),"floor.png"));
    entList.push_back(new Floor(vector3(-20.0,0.0,-15.0),vector3(0.0,1.0,0.0),vector3(1.0,0.0,0.0),vector3(-5,-10.0,0.0),vector3(5.0,-10.0,0.0),vector3(5.0,10.0,0.0),vector3(-5.0,10.0,0.0),"floor.png"));
    entList.push_back(new Floor(vector3(-20.0,-30.0,-10.0),vector3(0.0,1.0,0.0),vector3(1.0,0.0,0.0),vector3(-10.0,-10.0,0.0),vector3(10.0,-10.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),"floor.png"));
    entList.push_back(new Floor(vector3(-20.0,-26.0,5.0),vector3(0.0,1.0,-0.5),vector3(1.0,0.0,0.0),vector3(-10.0,-10.0,0.0),vector3(10.0,-10.0,0.0),vector3(10.0,10.0,0.0),vector3(-10.0,10.0,0.0),"floor.png"));
    entList.push_back(new Floor(vector3(-20.0,-21.55,17.9),vector3(0.0,1.0,0.0),vector3(1.0,0.0,0.0),vector3(-4,-10.0,0.0),vector3(4.0,-10.0,0.0),vector3(4.0,10.0,0.0),vector3(-4.0,10.0,0.0),"floor.png"));
    entList.push_back(new Floor(vector3(-20.0,-9.45,-11.1),vector3(0.0,-1.0,0.0),vector3(1.0,0.0,0.0),vector3(-20.0,-10.0,0.0),vector3(10.0,-10.0,0.0),vector3(10.0,10.0,0.0),vector3(-20.0,10.0,0.0),"floor.png"));
    entList.push_back(new Floor(vector3(0.0,10.0,0.0),vector3(0.0,-1.0,0.0),vector3(1.0,0.0,0.0),vector3(-30.0,-30.0,0.0),vector3(30.0,-30.0,0.0),vector3(30.0,30.0,0.0),vector3(-30.0,30.0,0.0),"floor.png"));

    he->init(blue,orange);
}

void LevelManager::reshape(int w, int h){
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 0.5, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void LevelManager::idle(void){
    calculateFPS();
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

    dynamic_cast<Character*>(*entList.begin())->look();
    list<Entity*>::iterator p = entList.end();

    for (p--; p!=entList.begin(); p--){
        glPushMatrix();
        (*p)->drawEntity();
        glPopMatrix();
    }

    blue->make_texture();
    orange->make_texture();
	/*glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, blue->hole_texture);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0, 0.0);
            glVertex3f(-3.0, 0.0, 0.0);
            glTexCoord2f(1.0, 0.0);
            glVertex3f(3.0, 0.0, 0.0);
            glTexCoord2f(1.0, 1.0);
            glVertex3f(3.0, 5.0, 0.0);
            glTexCoord2f(0.0, 1.0);
            glVertex3f(-3.0, 5.0, 0.0);
        glEnd();
    glDisable(GL_TEXTURE_2D);*/

	glLoadIdentity();
    (*entList.begin())->drawEntity();

	glutSwapBuffers();
}

void LevelManager::calculateFPS(){
    //  Increase frame count
    LevelManager::frameCount++;
    //  Get the number of milliseconds since glutInit called
    //  (or first call to glutGet(GLUT ELAPSED TIME)).
    LevelManager::currentTime = glutGet(GLUT_ELAPSED_TIME);

    //  Calculate time passed
    int timeInterval = LevelManager::currentTime - LevelManager::previousTime;

    if(timeInterval > 1000){
        LevelManager::fps = LevelManager::frameCount / (timeInterval / 1000.0f);
        LevelManager::previousTime = LevelManager::currentTime;
        LevelManager::frameCount = 0;
        printf("\r%d FPS",LevelManager::fps);
        fflush(stdout);
    }
}
