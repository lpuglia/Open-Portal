#ifndef WALL_H
#define WALL_H

#include "LevelDelimiter.h"

class Wall: public LevelDelimiter
{
    public:
        Wall(){};
        Wall(vector3 pos, vector3 dir, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, string texture_path);
        vector3 collision_detection(vector3 pos);
        virtual ~Wall(){};
        GLfloat get_distance(vector3 pos);
    protected:
    private:
        void build_bounding_box();
        GLfloat const_term; //of the equation plane
        GLfloat square_root;
};

#endif // WALL_H
