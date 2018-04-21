#include "PhysicsEngine.h"
#include <stdio.h>

PhysicsEngine::PhysicsEngine()
{
    PhysicsEngine::gravityA=vector3(0.0,-9.81,0.0);
    timer=0;
    prevTime=0;
}

PhysicsEngine::PhysicsEngine(vector3 gravityA)
{
    PhysicsEngine::gravityA=gravityA;
    timer=0;
    prevTime=0;
}

float PhysicsEngine::idle(){
    prevTime = timer;
    timer=glutGet(GLUT_ELAPSED_TIME);
    return timer - prevTime;
}

vector3 PhysicsEngine::getProjectileMotion(vector3 x0, vector3 v0, GLfloat t0){
    GLfloat t=glutGet(GLUT_ELAPSED_TIME);
    t=t-t0;
    t/=1000;

    vector3 v = v0*t;
    vector3 a = 0.5*gravityA*(t*t);
    vector3 x = x0 + v + a;

    //cout<<t<<endl;
    //cout<<v<<endl;
    //cout<<a<<endl;

    return x;
}

PhysicsEngine::~PhysicsEngine()
{
    //dtor
}
