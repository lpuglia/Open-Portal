#include "Geometry.h"

Geometry::Geometry(vector3 pos, vector3 dir, vector3 up, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, string texture_path):
            LevelDelimiter(pos,dir.normalize(),up.normalize(),vertex1,vertex2,vertex3,vertex4,texture_path)
{
    GLfloat orizzontal = ((int)length)/2;
    GLfloat vertical = ((int)height)/2;
    GLfloat texc[8]={ 0.0,0.0,
            orizzontal,0.0,
            orizzontal,vertical,
            0.0,vertical};
    memcpy(texcoords, texc, sizeof(GLfloat)*8);

}
