#ifndef LEVELDELIMITER_H
#define LEVELDELIMITER_H

#include "Entity.h"

class LevelDelimiter: public Entity
{
    public:
        LevelDelimiter(){};
        LevelDelimiter(vector3 pos, vector3 dir, vector3 up, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, vector3 color);
        void drawEntity();
        void movement(){};
        virtual vector3 isInFront(vector3 pos,vector3 dir)=0;
        virtual ~LevelDelimiter(){};
    protected:
        GLfloat vertices[12];
        vector3 surfacePosition;
        GLfloat length;
        GLfloat height;
    private:
        GLubyte faceIndices[12];
        GLfloat colors[12];
};

#endif // LEVELDELIMITER_H
