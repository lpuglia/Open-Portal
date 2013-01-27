#include "../include/Geometry.h"

Geometry::Geometry(vector3 pos, vector3 dir, vector3 up, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, string texture_path):
            LevelDelimiter(pos,dir.normalize(),up.normalize(),vertex1,vertex2,vertex3,vertex4,texture_path)
{
    GLfloat orizzontal = ((int)length)/2;
    GLfloat vertical = ((int)height)/2;
    texcoords={ 0.0,0.0,
            orizzontal,0.0,
            orizzontal,vertical,
            0.0,vertical};
}

vector3 Geometry::shot_detection(vector3 pos, vector3 dir, GLfloat* min_dist){
    vector3 plane_point = vector3(vertices[0],vertices[1], vertices[2]);
    vector3 zeros = vector3(0,0,0);

    GLfloat tmp = dot(dir,Geometry::dir);
    GLfloat dist = dot((plane_point-pos),Geometry::dir)/tmp;
    //if not in front OR not minimum distance OR at back
    if(dist<0.0 || dist>=*min_dist || tmp/(dir.length()*Geometry::dir.length())>=0.0)
        return zeros;

    pos = (dist-0.01)*dir+pos;

    //if shot in wall
    if (collision_detection(pos)!=zeros){
        *min_dist=dist;
        return pos;
    }else return zeros;
}
