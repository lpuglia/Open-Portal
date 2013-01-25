#ifndef WEAPON_H
#define WEAPON_H

#include "Item.h"


class Weapon : public Item
{
    public:
        Weapon();
        void drawEntity();
        virtual ~Weapon(){};
    protected:
        void movement();
    private:
        GLfloat gun1[12]; GLuint texgun1;
        GLfloat gun2[12]; GLuint texgun2;
        GLfloat gun3[12]; GLuint texgun3;
        GLfloat gun4[12]; GLuint texgun4;
        GLfloat gun5[12]; GLuint texgun5;
        GLuint listIndex;
        GLfloat texcoords[8];
};

#endif // WEAPON_H
