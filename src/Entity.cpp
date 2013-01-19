#include <stdio.h>
#include "../include/Entity.h"

Entity::Entity(vector3 pos, GLfloat angle){
    Entity::pos = pos;
    Entity::angle = angle;
}

Entity::Entity(vector3 pos, vector3 dir, vector3 up){
    Entity::pos = pos;//+vector3(0.0,0.02,0.0);
    Entity::dir = dir;
    Entity::up = up;
    dirMat[12]=0; dirMat[13]=0; dirMat[14]=0;
    dirMat[3]=0; dirMat[7]=0; dirMat[11]=0; dirMat[15]=1;
    updateDirMat();
}

void Entity::updateDirMat(){
    dir.normalize();
    vector3 right = cross(up, dir);
    right.normalize();
    dirMat[0]=right[0];   dirMat[4]=up[0]; dirMat[8]=dir[0];   //dirMat[12]=0;
    dirMat[1]=right[1];   dirMat[5]=up[1]; dirMat[9]=dir[1];   //dirMat[13]=0;
    dirMat[2]=right[2];   dirMat[6]=up[2]; dirMat[10]=dir[2];  //dirMat[14]=0;
    //dirMat[3]=0;        dirMat[7]=0;     dirMat[11]=0;         dirMat[15]=1;
}

vector3 Entity::getPos(){
    return pos;
}
void Entity::setPos(vector3 pos){
    Entity::pos = pos;
}

GLfloat* Entity::getBBox(){
    return bbox;
}
void Entity::setBBox(GLfloat* bbox){
    Entity::bbox = bbox;
}
