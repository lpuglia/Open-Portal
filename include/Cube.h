#ifndef CUBE_H
#define CUBE_H

#include "Item.h"

class Cube : public Item
{
    public:
        Cube(){};
        Cube(vector3 pos, vector3 dir, EntityList *entList);
        void drawEntity();
        void movement();
        void setCollide(bool collide);
        bool getCollide();
        virtual ~Cube(){};

    protected:
    private:
        bool collide;
        static GLfloat vertices[24];
        static GLfloat colors[24];
        static GLubyte cubeIndices[24];
        static GLuint listIndex;
        static GLboolean init;
        static void initialize();
};

#endif // CUBE_H
