#ifndef CHARACTER_H
#define CHARACTER_H

#include "Item.h"
#include "Cube.h"
#include "Weapon.h"
#include "Interface.h"
#include "Portal.h"

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
        virtual void mouseMotion(int x, int y)=0;
        virtual void look()=0;
        Entity* takenEntity[3];
        void init(Portal* blue, Portal* orange);
        GLfloat dir1;

    protected:
        vector3 releaseForce;
        GLfloat shotForce;
        vector3 at;
        GLboolean moveForward, moveBackward, moveRight, moveLeft, run, jump;
        GLfloat FB,RL;

    private:
        void takeEntity();
        void releaseEntity();
        void throwEntity();
        Portal* collision(std::vector<vector3>* walls, std::vector<Floor*>* floors);
        vector3 dist;
        vector3 precDist;
        Portal* blue;
        Portal* orange;
};

#endif // CHARACTER_H
