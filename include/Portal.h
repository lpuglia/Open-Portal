#ifndef PORTAL_H
#define PORTAL_H

#include "Item.h"


class Portal : public Item
{
    public:
        Portal(vector3 pos, vector3 dir, GLboolean type, EntityList *entList);
        void drawEntity();
        void set_position(vector3 pos, vector3 dir);
        virtual ~Portal(){};
    protected:
        void movement(){};
    private:
        GLuint listIndex;
        GLuint texture;

};

#endif // PORTAL_H
