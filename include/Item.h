#ifndef ITEM_H
#define ITEM_H

#include <list>
#include "PhysicsEngine.h"
#include "Entity.h"
#include "Wall.h"
#include "Floor.h"
#include "Geometry.h"
#include <vector>


typedef std::list<Entity*> EntityList;

class Item: public Entity
{
    public:
        Item(){};
        Item(vector3 pos, vector3 dir, GLfloat mass, vector3 v0, EntityList *entList);
        Item(vector3 pos, vector3 dir, EntityList *entList);
        vector3 getV0();
        void setV0(vector3 v0);
        GLfloat getMass();
        void setMass(GLfloat mass);
        virtual void movement()=0;
        virtual ~Item(){};
    protected:
        EntityList* entityList;
        PhysicsEngine pe;
        vector3 v0;
        GLfloat t0;
        GLfloat mass;
        Floor* actual_floor;
    private:
};

class Bound: public Entity{
    public:
        Bound(){}
        ~Bound(){}
        void drawEntity(){}
    protected:
    private:
};

#endif // ITEM_H
