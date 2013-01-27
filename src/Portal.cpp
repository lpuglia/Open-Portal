#include "../include/Portal.h"

Portal::Portal(vector3 pos, vector3 dir, GLboolean type, EntityList *entList)
        :Item(pos, dir, entList)
{
    open = false;
    if(type==true)
        texture = LoadTextureRGBA("texture/bluewormhole.png");
    else
        texture = LoadTextureRGBA("texture/orangewormhole.png");
    //ctor

    listIndex = glGenLists(1);
    glNewList(listIndex, GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glColor3f(1.0f, 1.0f, 1.0f);
            glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
            glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
            glEnable (GL_BLEND);
                glBegin(GL_QUADS);
                    glTexCoord2f(0.0, 0.0);
                    glVertex3f(-0.7, -1.3, 0.0);
                    glTexCoord2f(1.0, 0.0);
                    glVertex3f(0.7, -1.3, 0.0);
                    glTexCoord2f(1.0, 1.0);
                    glVertex3f(0.7, 1.3, 0.0);
                    glTexCoord2f(0.0, 1.0);
                    glVertex3f(-0.7, 1.3, 0.0);
                glEnd();
            glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glEndList();
}

void Portal::set_other_portal(Portal* other_portal){
    Portal::other_portal=other_portal;
}

void Portal::drawEntity(){
    glTranslatef(pos[0],pos[1],pos[2]);
    glMultMatrixf(dirMat);
    glCallList(listIndex);
}

void Portal::set_position(vector3 pos, vector3 dir, vector3 up){
    open=true;
    setPos(pos);
    setDir(dir);
    setUp(up);
    updateDirMat();
}

Portal* Portal::teleport_detection(vector3 pos){
    if (other_portal->open && 1.5 > pow(pos[0]-Portal::pos[0],2)+pow(pos[1]-Portal::pos[1],2)+pow(pos[2]-Portal::pos[2],2))
        return other_portal;
    return NULL;
}
