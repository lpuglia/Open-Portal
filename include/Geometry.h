#ifndef GEOMETRY_H
#define GEOMETRY_H

#include "LevelDelimiter.h"


class Geometry : public LevelDelimiter
{
    public:
        Geometry(){};
        Geometry(vector3 pos, vector3 dir, vector3 up, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, string texture_path);
        vector3 collision_detection(vector3 pos){};
        virtual ~Geometry(){};
    protected:
    private:
        void build_bounding_box(){};
};

#endif // GEOMETRY_H
