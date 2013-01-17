#include "../include/Wall.h"

vector3 Wall::collision_detection(vector3 pos){

    //note #10
    vector3 gamma = vector3(pos[0] -    bbox[0], 0, pos[2] -    bbox[2]);
    vector3 delta = vector3(pos[0] -    bbox[3], 0, pos[2] -    bbox[5]);
    vector3 alpha = vector3(pos[0] - bbox[0+12], pos[1] - bbox[1+12], pos[2] - bbox[2+12]);
    vector3 eps   = vector3(pos[0] - bbox[9], pos[1] - bbox[10], pos[2] - bbox[11]);
    vector3 zeta  = alpha;

    GLfloat dl = delta.length();
    GLfloat cosalpha = (Wall::dir[0]*alpha[0]+Wall::dir[2]*alpha[2])/(alpha.length());
    GLfloat cosdelta = (Wall::dir[0]*delta[0]+Wall::dir[2]*delta[2])/(dl);
    GLfloat sindelta = (Wall::dir[0]*delta[2]-Wall::dir[2]*delta[0])/(dl);
    GLfloat singamma = (Wall::dir[0]*gamma[2]-Wall::dir[2]*gamma[0])/(gamma.length());

    //perpendicular of collider
    vector3 perp = vector3(-Wall::dir[2],Wall::dir[1],Wall::dir[0]);
    perp = cross(perp,Wall::dir);
    GLfloat sineps = (perp[0]*eps[0]+perp[1]*eps[1])/(eps.length());
    GLfloat sinzeta = (perp[0]*zeta[0]+perp[1]*zeta[1])/(zeta.length());

    if(signbit(sindelta)!=signbit(singamma) && (signbit(sineps)!=signbit(sinzeta)) && signbit(cosalpha)!=signbit(cosdelta))
        return Wall::dir;

    return vector3(0.0,0.0,0.0);
}
