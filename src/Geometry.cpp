#include "../include/Geometry.h"

Geometry::Geometry(vector3 pos, vector3 dir, vector3 up, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, vector3 color):
            LevelDelimiter(pos,dir.normalize(),up.normalize(),vertex1,vertex2,vertex3,vertex4,color)
{
}
