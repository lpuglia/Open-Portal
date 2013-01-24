#include "../include/Floor.h"

Floor::Floor(vector3 pos, vector3 dir, vector3 up, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, vector3 color):
            LevelDelimiter(pos,dir.normalize(),up,vertex1,vertex2,vertex3,vertex4,color)
{
    ///TODO BOUNDING BOX
    //build_bounding_box();
    const_term = dir[0]*vertices[0]+dir[1]*vertices[1]+dir[2]*vertices[2];
    texcoords={ 0.0,0.0,
            10.0,0.0,
            10.0,10.0,
            0.0,10.0};
    texture = LoadTextureRAW("floor.png");

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
