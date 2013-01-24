#include "../include/Wall.h"

Wall::Wall(vector3 pos, vector3 dir, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, vector3 color):
            LevelDelimiter(pos,dir.normalize(),vector3(0.0,1.0,0.0),vertex1,vertex2,vertex3,vertex4,color)
{
    build_bounding_box();
    texcoords={ 0.0,0.0,
            10.0,0.0,
            10.0,2.0,
            0.0,2.0};
    texture = LoadTextureRAW("wall.png");
}

void Wall::build_bounding_box(){
    vector3 perp = vector3(-dir[2],dir[1],dir[0]);
    bbox= new GLfloat[24];

    int sign=1;
    int flag=0;
    for(int i=0; i<24; i+=3){
        if(i==12) flag=1;
        bbox[i+0]=vertices[(i+0)%12]+flag*dir[0]+sign*perp[0];
        bbox[i+1]=vertices[(i+1)%12]+flag*dir[1]+sign*perp[1];
        bbox[i+2]=vertices[(i+2)%12]+flag*dir[2]+sign*perp[2];
        sign = -sign;
    }
}

vector3 Wall::collision_detection(vector3 pos){
    ///OPTIMIZE
    //note #10
    vector3 gamma = vector3(pos[0] - bbox[0], 0, pos[2] - bbox[2]);
    vector3 delta = vector3(pos[0] - bbox[3], 0, pos[2] - bbox[5]);
    vector3 alpha = vector3(pos[0] - bbox[0+12], pos[1] - bbox[1+12], pos[2] - bbox[2+12]);
    vector3 eps   = vector3(pos[0] - bbox[9], pos[1] - bbox[10], pos[2] - bbox[11]);
    vector3 zeta  = alpha;

    GLfloat dl = delta.length();
    GLfloat cosalpha = (dir[0]*alpha[0]+dir[2]*alpha[2])/(alpha.length());
    GLfloat cosdelta = (dir[0]*delta[0]+dir[2]*delta[2])/(dl);
    GLfloat sindelta = (dir[0]*delta[2]-dir[2]*delta[0])/(dl);
    GLfloat singamma = (dir[0]*gamma[2]-dir[2]*gamma[0])/(gamma.length());

    //perpendicular of collider
    vector3 perp = vector3(-dir[2],dir[1],dir[0]);
    perp = cross(perp,dir);
    GLfloat sineps = (perp[0]*eps[0]+perp[1]*eps[1])/(eps.length());
    GLfloat sinzeta = (perp[0]*zeta[0]+perp[1]*zeta[1])/(zeta.length());

    if(signbit(sindelta)!=signbit(singamma) && (signbit(sineps)!=signbit(sinzeta)) && signbit(cosalpha)!=signbit(cosdelta))
        return dir;

    return vector3(0.0,0.0,0.0);
}
