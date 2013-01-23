#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "Item.h"
#include "ViewManager.h"
#include "Cube.h"
#include "Wall.h"
#include "Floor.h"
#include "Geometry.h"

using namespace std;

class LevelManager
{
    public:
        static void init(int width, int height);
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
        static int width, height, frameCount, currentTime, previousTime, fps;
        static Character* he;
        static EntityList entList;
        static void calculateFPS();
};

#endif // LEVELMANAGER_H
