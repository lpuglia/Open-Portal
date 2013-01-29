#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#define GL_GLEXT_PROTOTYPES //set up GL extension

#include "Item.h"
#include "ViewManager.h"
#include "Cube.h"
#include "Wall.h"
#include "Floor.h"
#include "Geometry.h"
#include "Entity.h"
#include "glext.h"

using namespace std;

class LevelManager
{
    public:
        static void init();
        static void reshape(int w, int h);
        static void display();
        static void idle(void);
        static void mouse(int button, int state, int x, int y);
        static void mouseMotion(int x, int y);
        static void keyboard(unsigned char key, int x, int y);
        static void keyboardUp(unsigned char key, int x, int y);
        static void specialKeyboard(int key, int x, int y);
    protected:

    private:
        static int frameCount, currentTime, previousTime, fps;
        static Character* he;
        static EntityList entList;
        static void calculateFPS();
        static Portal* blue;
        static Portal* orange;
};

#endif // LEVELMANAGER_H
