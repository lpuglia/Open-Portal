#ifndef ENTITY_H
#define ENTITY_H

#include <stdio.h>
#include <iostream>
#include <typeinfo>
#include <GL/glut.h>
#include <cml/cml.h>
#include <FreeImage.h>

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
        vector3 getUp();
        GLfloat* getBBox();
        void setBBox(GLfloat* bbox);
        void setDir(vector3 dir);
        vector3 getDir();
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
        GLuint texture;
        GLuint LoadTextureRAW(string filename);
        GLuint LoadTextureRGBA(string filename);
    private:
};

#endif // ENTITY_H
