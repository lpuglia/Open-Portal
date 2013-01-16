#include "../include/Cube.h"

GLfloat Cube::vertices[] = {-0.5f, 0.0f, 0.5f,   0.5f, 0.0f, 0.5f,   0.5f, 1.0f, 0.5f,
                            -0.5f, 1.0f, 0.5f,  -0.5f, 1.0f, -0.5f,  0.5f, 1.0f, -0.5f,
                             0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f};
GLfloat Cube::colors[] = { 1.0, 0.0, 0.0,  0.0, 1.0, 0.0,  0.0, 0.0, 1.0,
                           1.0, 1.0, 0.0,  0.0, 0.0, 0.0,  1.0, 0.0, 1.0,
                           1.0, 1.0, 1.0,  0.0, 1.0, 1.0 };
GLubyte Cube::cubeIndices[] = {0,1,2,3, 4,5,6,7, 3,2,5,4, 7,6,1,0, 1,6,5,2, 3,4,7,0};
GLuint Cube::listIndex;
GLboolean Cube::init = false;

/* maxi combo Vertex Array + Display List */
void Cube::initialize(){
    if(!init){
        glVertexPointer(3, GL_FLOAT, 0, vertices);
        glColorPointer(3, GL_FLOAT, 0, colors);
        listIndex = glGenLists(1);
        glNewList(listIndex, GL_COMPILE);
            glEnableClientState(GL_COLOR_ARRAY);
            glEnableClientState(GL_VERTEX_ARRAY);
            glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
            glDisableClientState(GL_VERTEX_ARRAY);
            glDisableClientState(GL_COLOR_ARRAY);
        glEndList();
        init=true;
    }
}

Cube::Cube(vector3 pos, vector3 dir, EntityList *entList)
    :Item(pos, dir, 5.0, vector3(0.0,0.0,0.0),entList)
{
    collide=false;
    initialize();
}

void Cube::drawEntity(){
    glTranslatef(pos[0],pos[1],pos[2]);
    glMultMatrixf(dirMat);
    //glRotatef(angle, 0.0, 1.0, 0.0);
    glCallList(listIndex);
}

void Cube::movement(){
    if(!collide){
        if(pos[1]>0.0){
            pos = pe.getProjectileMotion(pos, v0, t0);
        }else{
            pos[1]=0.0; collide=true;
        }
    }
}

void Cube::setCollide(bool collide){
    Cube::collide=collide;
    t0 = glutGet(GLUT_ELAPSED_TIME);
}
bool Cube::getCollide(){
    return collide;
}
