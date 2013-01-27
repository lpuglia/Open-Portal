#ifndef PORTAL_H
#define PORTAL_H

#include "Item.h"


class Portal : public Item
{
    public:
        Portal(vector3 pos, vector3 dir, GLboolean type, EntityList *entList);
        void drawEntity();
        void set_position(vector3 pos, vector3 dir, vector3 up);
        Portal* teleport_detection(vector3 pos);
        void set_other_portal(Portal* other_portal);
        virtual ~Portal(){};
        Portal* other_portal;
        GLboolean open;
    protected:
        void movement(){};
    private:
        GLuint listIndex;
        GLuint texture;

};

#endif // PORTAL_H
