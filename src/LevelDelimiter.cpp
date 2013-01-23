#include "../include/LevelDelimiter.h"

LevelDelimiter::LevelDelimiter(vector3 pos, vector3 dir, vector3 up, vector3 vertex1, vector3 vertex2, vector3 vertex3,
                                vector3 vertex4, vector3 color):Entity(pos, dir.normalize(), up)
{
    updateDirMat();

    vertices[0]=dirMat[0]*vertex1[0]+dirMat[4]*vertex1[1]+dirMat[8]*vertex1[2]+pos[0];
    vertices[1]=dirMat[1]*vertex1[0]+dirMat[5]*vertex1[1]+dirMat[9]*vertex1[2]+pos[1];
    vertices[2]=dirMat[2]*vertex1[0]+dirMat[6]*vertex1[1]+dirMat[10]*vertex1[2]+pos[2];

    vertices[3]=dirMat[0]*vertex2[0]+dirMat[4]*vertex2[1]+dirMat[8]*vertex2[2]+pos[0];
    vertices[4]=dirMat[1]*vertex2[0]+dirMat[5]*vertex2[1]+dirMat[9]*vertex2[2]+pos[1];
    vertices[5]=dirMat[2]*vertex2[0]+dirMat[6]*vertex2[1]+dirMat[10]*vertex2[2]+pos[2];

    vertices[6]=dirMat[0]*vertex3[0]+dirMat[4]*vertex3[1]+dirMat[8]*vertex3[2]+pos[0];
    vertices[7]=dirMat[1]*vertex3[0]+dirMat[5]*vertex3[1]+dirMat[9]*vertex3[2]+pos[1];
    vertices[8]=dirMat[2]*vertex3[0]+dirMat[6]*vertex3[1]+dirMat[10]*vertex3[2]+pos[2];

    vertices[9]=dirMat[0]*vertex4[0]+dirMat[4]*vertex4[1]+dirMat[8]*vertex4[2]+pos[0];
    vertices[10]=dirMat[1]*vertex4[0]+dirMat[5]*vertex4[1]+dirMat[9]*vertex4[2]+pos[1];
    vertices[11]=dirMat[2]*vertex4[0]+dirMat[6]*vertex4[1]+dirMat[10]*vertex4[2]+pos[2];

    colors={color[0],color[1],color[2],
            color[0],color[1],color[2],
            color[0],color[1],color[2],
            color[0],color[1],color[2]};
    faceIndices={0,1,2,3};
}

void LevelDelimiter::drawEntity(){
    glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawElements(GL_QUADS, 12, GL_UNSIGNED_BYTE, faceIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);
}
