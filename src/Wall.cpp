#include "../include/Wall.h"

Wall::Wall(vector3 pos, vector3 dir, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, vector3 color):
            LevelDelimiter(pos,dir.normalize(),vector3(0.0,1.0,0.0),vertex1,vertex2,vertex3,vertex4,color)
{
    build_bounding_box();
}

void Wall::build_bounding_box(){
    vector3 perp = vector3(-dir[2],dir[1],dir[0]);
    bbox= new GLfloat[24];
    bbox[0]=vertices[0]+perp[0];
    bbox[1]=vertices[1]+perp[1];
    bbox[2]=vertices[2]+perp[2];

    bbox[3]=vertices[3]-perp[0];
    bbox[4]=vertices[4]-perp[1];
    bbox[5]=vertices[5]-perp[2];

    bbox[6]=vertices[6]+perp[0];
    bbox[7]=vertices[7]+perp[1];
    bbox[8]=vertices[8]+perp[2];

    bbox[9]=vertices[9]-perp[0];
    bbox[10]=vertices[10]-perp[1];
    bbox[11]=vertices[11]-perp[2];


    bbox[12]=vertices[0]+dir[0]+perp[0];
    bbox[13]=vertices[1]+dir[1]+perp[1];
    bbox[14]=vertices[2]+dir[2]+perp[2];

    bbox[15]=vertices[3]+dir[0]-perp[0];
    bbox[16]=vertices[4]+dir[1]-perp[1];
    bbox[17]=vertices[5]+dir[2]-perp[2];

    bbox[18]=vertices[6]+dir[0]+perp[0];
    bbox[19]=vertices[7]+dir[1]+perp[1];
    bbox[20]=vertices[8]+dir[2]+perp[2];

    bbox[21]=vertices[9]+dir[0]-perp[0];
    bbox[22]=vertices[10]+dir[1]-perp[1];
    bbox[23]=vertices[11]+dir[2]-perp[2];

    /*cout << "dir ---" << dir << endl;
    for (int i=0; i<24; i++){
        cout << bbox[i] << ' ' << vertices[i%12] << endl;
    }
    cout << endl;*/
}

vector3 Wall::collision_detection(vector3 pos){

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
