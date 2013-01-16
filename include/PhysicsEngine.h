#ifndef PHYSISCSENGINE_H
#define PHYSISCSENGINE_H

#include <iostream>
#include <GL/glut.h>
#include <cml/cml.h>

using namespace cml;
using namespace std;
typedef vector3f vector3;

class PhysicsEngine
{
    public:
        PhysicsEngine();
        PhysicsEngine(vector3 gravityA);
        float idle();
        vector3 getProjectileMotion(vector3 x0, vector3 v0, GLfloat t0);
        virtual ~PhysicsEngine();
        vector3 gravityA;
    protected:
    private:
        float timer, prevTime;

};

#endif // PHYSISCSENGINE_H
