#ifndef PORTAL_H
#define PORTAL_H

#define GL_GLEXT_PROTOTYPES //set up GL extension

#include "Item.h"
#include "glext.h"

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
        void setup_offscreen_rendering(GLuint fbo);
        GLuint mask;
        GLuint texture;
        GLuint texture_open;
        GLuint hole_texture;
        GLuint fbo;
        void make_texture();
        GLenum param;
    protected:
        void movement(){};
    private:
        GLuint size;
        GLboolean type;
        GLuint listIndex;
};

#endif // PORTAL_H
