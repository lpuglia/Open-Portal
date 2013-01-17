#include "../include/Wall.h"

vector3 Wall::isInFront(vector3 pos, vector3 dir){

    //note #10
    vector3 gamma = vector3(pos[0] -    bbox[0], 0, pos[2] -    bbox[2]);
    vector3 delta = vector3(pos[0] -    bbox[3], 0, pos[2] -    bbox[5]);
    vector3 alpha = vector3(pos[0] - bbox[0+12], pos[1] - bbox[1+12], pos[2] - bbox[2+12]);
    //vector3 beta = vector3(pos[0] - bbox[3+12], pos[1] - bbox[4+12], pos[2] - bbox[5+12]);
    vector3 eps   = vector3(pos[0] - bbox[9], pos[1] - bbox[10], pos[2] - bbox[11]);
    vector3 zeta  = alpha;

    /*cout << eps << endl;
    cout << zeta << endl;
    cout << Wall::dir << endl;*/

    /*cout << alpha.length() << endl;
    cout << beta.length() << endl;
    cout << gamma.length() << endl;
    cout << delta.length() << endl;
    cout << "------------" << endl;*/

    /*GLfloat cosalpha = (Wall::dir[0]*alpha[0]+Wall::dir[2]*alpha[2])/(Wall::dir.length()*alpha.length());
    GLfloat cosbeta  = (Wall::dir[0]*beta[0]+Wall::dir[2]*beta[2])/(Wall::dir.length()*beta.length());
    GLfloat sindelta = (Wall::dir[0]*delta[2]-Wall::dir[2]*delta[0])/(Wall::dir.length()*delta.length());
    GLfloat singamma = (Wall::dir[0]*gamma[2]-Wall::dir[2]*gamma[0])/(Wall::dir.length()*gamma.length());*/

    GLfloat dl = delta.length();

    GLfloat cosalpha = (Wall::dir[0]*alpha[0]+Wall::dir[2]*alpha[2])/(alpha.length());
    //GLfloat cosbeta  = (Wall::dir[0]*beta[0]+Wall::dir[2]*beta[2])/(beta.length());
    GLfloat cosdelta = (Wall::dir[0]*delta[0]+Wall::dir[2]*delta[2])/(dl);
    //GLfloat cosgamma = (Wall::dir[0]*gamma[0]+Wall::dir[2]*gamma[2])/(gl);
    GLfloat sindelta = (Wall::dir[0]*delta[2]-Wall::dir[2]*delta[0])/(dl);
    GLfloat singamma = (Wall::dir[0]*gamma[2]-Wall::dir[2]*gamma[0])/(gamma.length());

    //cout << cross(Wall::dir,eps) << "<<<<<<<<<<<<<" << endl;

    /*GLfloat sineps   = (Wall::dir[0]*eps[1])/(eps.length());
    GLfloat sinzeta  = (Wall::dir[0]*zeta[1])/(zeta.length());
    sineps  += (Wall::dir[2]*eps[1])/(eps.length());
    sinzeta += (Wall::dir[2]*zeta[1])/(zeta.length());*/

    //perpendicular of collider
    vector3 perp = vector3(-Wall::dir[2],Wall::dir[1],Wall::dir[0]);
    perp = cross(perp,Wall::dir);
    //cout << Wall::dir << endl;
    //cout << perp << endl;
    //cout << (perp[0]*eps[0]+perp[1]*eps[1])/(eps.length()) << endl;
    //cout << (perp[0]*zeta[0]+perp[1]*zeta[1])/(zeta.length()) << endl;
    GLfloat sineps = (perp[0]*eps[0]+perp[1]*eps[1])/(eps.length());
    GLfloat sinzeta = (perp[0]*zeta[0]+perp[1]*zeta[1])/(zeta.length());


    //cout << sinzeta << endl;
    //cout << (Wall::dir[2]*zeta[1])/zeta.length() << endl;
    //cout << sinzeta << endl;
    //cout << zeta << endl;
    //cout << zeta.length() << endl;
    //GLfloat sineps   = (Wall::dir[1]*eps[2]-Wall::dir[2]*eps[1])/(eps.length());
    //GLfloat sinzeta  = (Wall::dir[1]*zeta[2]-Wall::dir[2]*zeta[1])/(zeta.length());
    //GLfloat singamma = (Wall::dir[0]*gamma[2]-Wall::dir[2]*gamma[0])/(gl);

    //cout << cosalpha << endl;//' ' << cosbeta << endl;
    //cout << cosdelta << endl;//' ' << cosgamma << endl;
    //cout << sindelta << ' ' << singamma << endl << "----------" << endl;
    //cout << sineps << ' ' << sinzeta << endl << "-------" << endl;

    //vector3 dist = Wall::pos - pos;
    /*vector3 dist = surfacePosition - pos;
    dist[0] = Wall::dir[0]*(dist[0]);
    dist[1] = Wall::dir[1]*(dist[1]);
    dist[2] = Wall::dir[2]*(dist[2]);

    GLfloat Ax = pos[0]-vertices[0];
    GLfloat Ay = pos[1]-vertices[1];
    GLfloat Az = pos[2]-vertices[2];
    GLfloat Cx = pos[0]-vertices[6];
    GLfloat Cy = pos[1]-vertices[7];
    GLfloat Cz = pos[2]-vertices[8];*/

    //if(cosalpha<0.0 && cosbeta<0.0 && (signbit(sindelta)!=signbit(singamma)))
    //    return Wall::dir;

    //cout << signbit(sindelta) << " " << signbit(singamma) << endl;
    //cout << signbit(sineps)  << " " << signbit(sinzeta) << endl;
    //cout << signbit(cosalpha) << " " << signbit(cosdelta) << endl;
    //cout << "----------" << endl;

    if(signbit(sindelta)!=signbit(singamma) && (signbit(sineps)!=signbit(sinzeta)) && signbit(cosalpha)!=signbit(cosdelta))// && signbit(cosbeta)!=signbit(cosgamma))
        return Wall::dir;

    return vector3(0.0,0.0,0.0);
}
