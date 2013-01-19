#ifndef ENTITY_H
#define ENTITY_H

#include <iostream>
#include <typeinfo>
#include <GL/glut.h>
#include <cml/cml.h>

using namespace cml;
using namespace std;
typedef vector3f vector3;

//abstract class for the entity
class Entity
{
    public:
        Entity() {};
        Entity(vector3 pos,GLfloat angle);
        Entity(vector3 pos,vector3 dir, vector3 up);
        vector3 getPos();
        void setPos(vector3 pos);
        GLfloat* getBBox();
        void setBBox(GLfloat* bbox);
        vector3 getDir(){ return dir; };
        void updateDirMat();
        virtual void drawEntity()=0;
        virtual ~Entity() {};
    protected:
        vector3 pos;
        vector3 dir;
        vector3 up;
        vector3 side;
        GLfloat dirMat[16];
        GLfloat angle;
        GLfloat* bbox;
    private:
};

#endif // ENTITY_H
