#ifndef INTERFACE_H
#define INTERFACE_H

#include "Item.h"


class Interface : public Item
{
    public:
        Interface();
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
};

#endif // INTERFACE_H
