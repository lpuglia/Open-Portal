#include "../include/Floor.h"

Floor::Floor(vector3 pos, vector3 dir, vector3 up, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, string texture_path):
            LevelDelimiter(pos,dir.normalize(),up,vertex1,vertex2,vertex3,vertex4,texture_path)
{
    ///TODO BOUNDING BOX
    //build_bounding_box();
    const_term = dir[0]*vertices[0]+dir[1]*vertices[1]+dir[2]*vertices[2];
    GLfloat orizzontal = ((int)length)/2;
    GLfloat vertical = ((int)height)/2;
    texcoords={ 0.0,0.0,
            orizzontal,0.0,
            orizzontal,vertical,
            0.0,vertical};

}

void Floor::build_bounding_box(){
}

vector3 Floor::collision_detection(vector3 pos){
    //note #10
    vector3 gamma = vector3(pos[0] - vertices[0], pos[1] - vertices[1], pos[2] - vertices[2]);
    vector3 delta = vector3(pos[0] - vertices[6], pos[1] - vertices[7], pos[2] - vertices[8]);

    GLfloat dl = delta.length();
    GLfloat gl = gamma.length();
    GLfloat sindelta = (delta[2])/(dl);//GLfloat sindelta = (dir[1]*delta[2]-dir[2]*delta[1])/(dl);
    GLfloat singamma = (gamma[2])/(gl);//GLfloat singamma = (dir[1]*gamma[2]-dir[2]*gamma[1])/(gl);

    GLfloat sinalpha = (-delta[0])/(dl);//GLfloat sinalpha = (dir[0]*delta[1]-dir[1]*delta[0])/(dl);
    GLfloat sinbeta = (-gamma[0])/(gl);//GLfloat sinbeta = (dir[0]*gamma[1]-dir[1]*gamma[0])/(gl);

    /*cout << signbit(sindelta) << " " << signbit(singamma) << endl;
    cout << signbit(sinalpha) << " " << signbit(sinbeta) << endl;
    cout << "------" << endl;*/

    if(signbit(sindelta)!=signbit(singamma) && signbit(sinalpha)!=signbit(sinbeta))
        return dir;

    return vector3(0.0,0.0,0.0);
}

GLfloat Floor::get_height(vector3 pos){
    return ((dir[0]*pos[0]+dir[2]*pos[2]-const_term)/-dir[1]);
}

vector3 Floor::shot_detection(vector3 pos, vector3 dir, GLfloat* min_dist){
    vector3 plane_point = vector3(vertices[0],vertices[1], vertices[2]);
    vector3 zeros = vector3(0,0,0);

    GLfloat tmp = dot(dir,Floor::dir);
    GLfloat dist = dot((plane_point-pos),Floor::dir)/tmp;
    //if not in front OR not minimum distance OR at back
    if(dist<0.0 || dist>=*min_dist || tmp/(dir.length()*Floor::dir.length())>=0.0)
        return zeros;

    pos = (dist-0.01)*dir+pos;

    //if shot in wall
    if (collision_detection(pos)!=zeros){
        *min_dist=dist;
        return pos;
    }else return zeros;
}
