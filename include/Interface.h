#ifndef INTERFACE_H
#define INTERFACE_H

#include "Item.h"
#include "Portal.h"

class Interface : public Item
{
    public:
        Interface(Portal* blue, Portal* orange);
        void drawEntity();
        virtual ~Interface();
    protected:
        void movement();
    private:
        GLuint listIndex;
        GLfloat ui[12];
        GLuint uivoid;
        GLuint uiblue;
        GLuint uiorange;
        GLuint uiblueorange;
        Portal* blue;
        Portal* orange;
};

#endif // INTERFACE_H
