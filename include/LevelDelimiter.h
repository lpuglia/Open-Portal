#ifndef LEVELDELIMITER_H
#define LEVELDELIMITER_H

#include "Entity.h"

class LevelDelimiter: public Entity
{
    public:
        LevelDelimiter(){};
        LevelDelimiter(vector3 pos, vector3 dir, vector3 up, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, vector3 color);
        void drawEntity();
        virtual vector3 collision_detection(vector3 pos)=0;
        virtual ~LevelDelimiter(){};
    protected:
        GLfloat vertices[12];
        vector3 surfacePosition;
        GLfloat length;
        GLfloat height;
        GLubyte faceIndices[12];
        GLfloat colors[12];
        GLfloat texcoords[8];
        GLuint LoadTextureRAW(const char* filename);
        GLuint texture;
    private:
        virtual void build_bounding_box()=0;
};

#endif // LEVELDELIMITER_H
