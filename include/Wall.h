#ifndef WALL_H
#define WALL_H

#include "LevelDelimiter.h"

class Wall: public LevelDelimiter
{
    public:
        Wall(){};
        Wall(vector3 pos, vector3 dir, vector3 up, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, vector3 color):
            LevelDelimiter(pos,dir,up,vertex1,vertex2,vertex3,vertex4,color){}
        vector3 isInFront(vector3 pos, vector3 dir);
        virtual ~Wall(){};
    protected:
    private:
};

#endif // WALL_H
