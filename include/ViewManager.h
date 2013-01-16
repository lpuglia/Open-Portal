#ifndef VIEWMANAGER_H
#define VIEWMANAGER_H

#include "Character.h"

class ViewManager: public Character
{
    public:
        ViewManager(){};
        ViewManager(vector3 pos, GLfloat peak, int width, int height, EntityList *entList);
        void look();
        void mouseMotion(int x, int y);

        virtual ~ViewManager(){};
    protected:
        GLfloat peak;
        int hWidth, hHeight;

};

#endif // VIEWMANAGER_H
