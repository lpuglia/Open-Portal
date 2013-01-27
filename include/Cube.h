#ifndef CUBE_H
#define CUBE_H

#include "Item.h"
#include "Portal.h"


class Cube : public Item
{
    public:
        Cube(){};
        Cube(vector3 pos, vector3 dir, EntityList *entList);
        void drawEntity();
        void movement();
        void setCollide(bool collide);
        bool getCollide();
        vector3 collision_detection(vector3 pos);
        virtual ~Cube(){};
    protected:
    private:
        bool floor_collide, wall_collide;
        Portal* collision(std::vector<vector3>* walls, std::vector<Floor*>* floors);
        GLfloat* vertices;
        GLfloat* texcoords;
        GLubyte* cubeIndices;
        GLuint listIndex;
        GLboolean init;
        void initialize();
};

#endif // CUBE_H
