#include "../include/LevelDelimiter.h"

LevelDelimiter::LevelDelimiter(vector3 pos, vector3 dir, vector3 up, vector3 vertex1, vector3 vertex2, vector3 vertex3,
                                vector3 vertex4, string texture_path):Entity(pos, dir.normalize(), up)
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

    length = sqrt(pow((vertex1[0]-vertex2[0]),2)+pow((vertex1[1]-vertex2[1]),2)+pow((vertex1[2]-vertex2[2]),2));
    height = sqrt(pow((vertex1[0]-vertex4[0]),2)+pow((vertex1[1]-vertex4[1]),2)+pow((vertex1[2]-vertex4[2]),2));

    faceIndices={0,1,2,3};
    /*faceIndices[0]=0;
    faceIndices[1]=1;
    faceIndices[2]=2;
    faceIndices[3]=3;*/

    texture = LoadTextureRAW("texture/"+texture_path);

}

void LevelDelimiter::drawEntity(){
  	glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1.0f, 1.0f, 1.0f);

    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawElements(GL_QUADS, 12, GL_UNSIGNED_BYTE, faceIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_TEXTURE_COORD_ARRAY);

    glDisable(GL_TEXTURE_2D);

}

vector3 LevelDelimiter::shot_detection(vector3 pos, vector3 dir, GLfloat* min_dist){
    vector3 plane_point = vector3(vertices[0],vertices[1], vertices[2]);
    vector3 zeros = vector3(0,0,0);

    GLfloat tmp = dot(dir,LevelDelimiter::dir);
    GLfloat dist = dot((plane_point-pos),LevelDelimiter::dir)/tmp;
    //if not in front OR not minimum distance OR at back
    if(dist<0.0 || dist>=*min_dist || tmp/(dir.length()*LevelDelimiter::dir.length())>=0.0)
        return zeros;

    pos = (dist-0.01)*dir+pos;

    //if shot in wall
    if (collision_detection(pos)!=zeros){
        *min_dist=dist;
        return pos;
    }else return zeros;
}
