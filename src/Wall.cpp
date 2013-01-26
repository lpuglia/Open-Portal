#include "../include/Wall.h"

Wall::Wall(vector3 pos, vector3 dir, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, string texture_path):
            LevelDelimiter(pos,dir.normalize(),vector3(0.0,1.0,0.0),vertex1,vertex2,vertex3,vertex4,texture_path)
{
    const_term = dir[0]*vertices[0]+dir[1]*vertices[1]+dir[2]*vertices[2];
    square_root = sqrt(dir[0]*dir[0]+dir[1]*dir[1]+dir[2]*dir[2]);
    build_bounding_box();
    GLfloat orizzontal = ((int)length)/2;
    GLfloat vertical = ((int)height)/5;
    texcoords={ 0.0,0.0,
            orizzontal,0.0,
            orizzontal,vertical,
            0.0,vertical};
}

void Wall::build_bounding_box(){
    vector3 perp = vector3(-dir[2],dir[1],dir[0]);
    bbox= new GLfloat[24];

    int sign[4]={1,1,-1,-1};
    int flag=0;
    for(int i=0; i<24; i+=3){
        if(i==12) flag=1;
        bbox[i+0]=vertices[(i+0)%12]+flag*dir[0]+sign[i%4]*perp[0];
        bbox[i+1]=vertices[(i+1)%12]+flag*dir[1]+sign[i%4]*perp[1];
        bbox[i+2]=vertices[(i+2)%12]+flag*dir[2]+sign[i%4]*perp[2];
    }
}

vector3 Wall::collision_detection(vector3 pos){
    //note #10
    vector3 gamma = vector3(pos[0] - bbox[0], 0, pos[2] - bbox[2]);
    vector3 delta = vector3(pos[0] - bbox[3], 0, pos[2] - bbox[5]);

    GLfloat sindelta = (dir[0]*delta[2]-dir[2]*delta[0])/(delta.length());
    GLfloat singamma = (dir[0]*gamma[2]-dir[2]*gamma[0])/(gamma.length());

    if(signbit(sindelta)!=signbit(singamma) && vertices[4]<=pos[1] && pos[1]<vertices[7] && get_distance(pos)<1.0)
        return dir;

    /*vector3 gamma = vector3(pos[0] - bbox[0], 0, pos[2] - bbox[2]);
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
        return dir;*/
    return vector3(0.0,0.0,0.0);
}

GLfloat Wall::get_distance(vector3 pos){
    return abs(dir[0]*pos[0]+dir[2]*pos[2]-const_term)/square_root;
}

vector3 Wall::shot_detection(vector3 pos, vector3 dir, GLfloat* min_dist){
    vector3 plane_point = vector3(vertices[0],vertices[1], vertices[2]);
    vector3 zeros = vector3(0,0,0);

    GLfloat tmp = dot(dir,Wall::dir);
    GLfloat dist = dot((plane_point-pos),Wall::dir)/tmp;
    //if not in front OR not minimum distance OR at back
    if(dist<0.0 || dist>=*min_dist || tmp/(dir.length()*Wall::dir.length())>=0.0)
        return zeros;

    pos = (dist-0.1)*dir+pos;

    //if shot in wall
    if (collision_detection(pos)!=zeros){
        *min_dist=dist;
        return pos;
    }else return zeros;
}
