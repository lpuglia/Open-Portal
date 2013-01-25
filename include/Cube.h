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
        vector3 collision_detection(vector3 pos);
        virtual ~Cube(){};
    protected:
    private:
        bool floor_collide, wall_collide;
        std::pair<std::vector<vector3>,std::vector<Floor*> > collision();
        GLfloat* vertices;
        GLfloat* texcoords;
        GLubyte* cubeIndices;
        GLuint listIndex;
        GLboolean init;
        void initialize();
};

#endif // CUBE_H
