#ifndef FLOOR_H
#define FLOOR_H

#include "LevelDelimiter.h"

class Floor: public LevelDelimiter
{
    public:
        Floor(){};
        Floor(vector3 pos, vector3 dir, vector3 up, vector3 vertex1, vector3 vertex2, vector3 vertex3, vector3 vertex4, vector3 color);
        vector3 collision_detection(vector3 pos);
        GLfloat get_height(vector3 pos);
        virtual ~Floor(){};
    protected:
    private:
        GLuint LoadTextureRAW(const char* filename, bool wrap);
        void build_bounding_box();
        GLfloat const_term; //of the equation plane
};

#endif // FLOOR_H
