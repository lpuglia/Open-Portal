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
        static GLfloat vertices[24];
        static GLfloat colors[24];
        static GLubyte cubeIndices[24];
        static GLuint listIndex;
        static GLboolean init;
        static void initialize();
};

#endif // CUBE_H
