#include "Item.h"

Item::Item(vector3 pos, vector3 dir, GLfloat mass, vector3 v0, EntityList *entList):Entity(pos,dir,vector3(0.0,1.0,0.0)){
    Item::dir=dir;
    Item::mass = mass;
    t0 = glutGet(GLUT_ELAPSED_TIME);
    Item::v0 = v0;
    pe = PhysicsEngine();
    entityList = entList;
}

Item::Item(vector3 pos, vector3 dir, EntityList *entList):Entity(pos,dir,vector3(0.0,1.0,0.0)){
    Item::dir=dir;
    entityList = entList;
}

vector3 Item::getV0(){
    return v0;
}
void Item::setV0(vector3 v0){
    Item::v0 = v0;
}

GLfloat Item::getMass(){
    return mass;
}
void Item::setMass(GLfloat mass){
    Item::mass = mass;
}
