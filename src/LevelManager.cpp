#include "../include/LevelManager.h"

Character* LevelManager::he;
EntityList LevelManager::entList;
int LevelManager::width;
int LevelManager::height;
int LevelManager::frameCount=0;
int LevelManager::currentTime=0;
int LevelManager::previousTime=0;
int LevelManager::fps=0;

void LevelManager::init(int width, int height){

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

    LevelManager::width=width;
    LevelManager::height=height;

    he = new ViewManager(vector3(1.0,0.0,5.0), 1.80, width, height, &entList);
    entList.push_back(he);
    Portal* blue = new Portal(vector3(0.0,100.0,0.0),vector3(0.0,0.0,-1.0),true,&entList);
    entList.push_back(blue);
    Portal* orange = new Portal(vector3(0.0,100.0,0.0),vector3(0.0,0.0,-1.0),false,&entList);
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


GLuint loadTexture(char* textName){
	GLuint idTexture;
	FREE_IMAGE_FORMAT fifmt = FreeImage_GetFileType(textName, 0);
	FIBITMAP *dib = FreeImage_Load(fifmt, textName,0);
	if( dib != NULL ){
		glGenTextures( 1, &idTexture );
		glBindTexture( GL_TEXTURE_2D, idTexture );
		BYTE *pixels = (BYTE*)FreeImage_GetBits(dib);
		glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA,
               FreeImage_GetWidth(dib), FreeImage_GetHeight(dib),
                0, GL_BGRA, GL_UNSIGNED_BYTE, pixels );

		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER, GL_LINEAR );
		glTexParameteri( GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER, GL_LINEAR );
		FreeImage_Unload(dib);
	}
	return idTexture;
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
