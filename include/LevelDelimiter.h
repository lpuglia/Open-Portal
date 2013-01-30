#ifndef LEVELDELIMITER_H
#define LEVELDELIMITER_H

#include <string.h>
#include "Entity.h"

class LevelDelimiter: public Entity
{
    public:
        LevelDelimiter(){};
        LevelDelimiter(vector3 pos, vector3 dir, vector3 up, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, string texture_path);
        void drawEntity();
        virtual vector3 collision_detection(vector3 pos)=0;
        vector3 shot_detection(vector3 pos, vector3 dir, GLfloat* min_dist);
        virtual ~LevelDelimiter(){};
    protected:
        GLfloat vertices[12];
        vector3 surfacePosition;
        GLfloat length;
        GLfloat height;
        GLubyte faceIndices[4];
        GLfloat texcoords[8];
    private:
        virtual void build_bounding_box()=0;
};

#endif // LEVELDELIMITER_H
