#ifndef CHARACTER_H
#define CHARACTER_H

#include "Item.h"
#include "Cube.h"
#include "Wall.h"
#include "Floor.h"
#include <vector>

class Character: public Item
{
    public:
        Character(){}
        Character(vector3 pos, GLfloat mass, EntityList *entList);

        virtual ~Character(){};
        void mouse(int button, int state, int x, int y);
        void keyboard(unsigned char key);
        void keyboardUp(unsigned char key);
        void specialKeyboard(int key);
        void movement();
        void drawEntity();
        virtual void mouseMotion(int x, int y){};
        virtual void look(){};
        Entity* takenEntity;
        void init();

    protected:
        vector3 releaseForce;
        GLfloat shotForce;
        vector3 at;
        GLfloat dir1;
        GLboolean moveForward, moveBackward, moveRight, moveLeft, run, jump;
        GLfloat FB,RL;

    private:
        void takeEntity();
        void releaseEntity();
        void throwEntity();
        std::pair<std::vector<vector3>,std::vector<Floor*> > collision();
        vector3 dist;
        vector3 precDist;
        Bound bound;
        Floor* actual_floor;
};

#endif // CHARACTER_H
