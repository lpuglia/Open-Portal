#ifndef WALL_H
#define WALL_H

#include "LevelDelimiter.h"

class Wall: public LevelDelimiter
{
    public:
        Wall(){};
        Wall(vector3 pos, vector3 dir, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, vector3 color);
        vector3 collision_detection(vector3 pos);
        virtual ~Wall(){};
    protected:
    private:
        void build_bounding_box();
};

#endif // WALL_H
