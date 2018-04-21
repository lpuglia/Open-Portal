#include "Portal.h"
#include "Character.h"
#include "LevelManager.h"

Portal::Portal(vector3 pos, vector3 dir, GLboolean type, EntityList *entList)
        :Item(pos, dir, entList)
{
    Portal::type=type;
    open = false;
    mask = LoadTextureRGBA("../texture/mask.png");
    if(type){
        texture = LoadTextureRGBA("../texture/bluewormhole.png");
        texture_open = LoadTextureRGBA("../texture/bluewormholeopen.png");
    }else{
        texture = LoadTextureRGBA("../texture/orangewormhole.png");
        texture_open = LoadTextureRGBA("../texture/orangewormholeopen.png");
    }
    param=GL_REPLACE;
    size=512; //px

    listIndex = glGenLists(1);
    glNewList(listIndex, GL_COMPILE);
        glEnable (GL_BLEND);
            glBegin(GL_QUADS);
                glMultiTexCoord2f(GL_TEXTURE0, 0.0, 0.0);
                glMultiTexCoord2f(GL_TEXTURE1, 0.0, 0.0);
                glMultiTexCoord2f(GL_TEXTURE2, 0.0, 0.0);
                glVertex3f(-0.9, -1.4, 0.0);

                glMultiTexCoord2f(GL_TEXTURE0, 1.0, 0.0);
                glMultiTexCoord2f(GL_TEXTURE1, 1.0, 0.0);
                glMultiTexCoord2f(GL_TEXTURE2, 1.0, 0.0);
                glVertex3f(0.9, -1.4, 0.0);

                glMultiTexCoord2f(GL_TEXTURE0, 1.0, 1.0);
                glMultiTexCoord2f(GL_TEXTURE1, 1.0, 1.0);
                glMultiTexCoord2f(GL_TEXTURE2, 1.0, 1.0);
                glVertex3f(0.9, 1.4, 0.0);

                glMultiTexCoord2f(GL_TEXTURE0, 0.0, 1.0);
                glMultiTexCoord2f(GL_TEXTURE1, 0.0, 1.0);
                glMultiTexCoord2f(GL_TEXTURE2, 0.0, 1.0);
                glVertex3f(-0.9, 1.4, 0.0);
            glEnd();
        glDisable(GL_BLEND);
    glEndList();

    glGenFramebuffers(1, &(fbo));
    setup_offscreen_rendering(fbo);
}

void Portal::set_other_portal(Portal* other_portal){
    Portal::other_portal=other_portal;
}

void Portal::setup_offscreen_rendering(GLuint fbo){
    glGenTextures(1, &hole_texture);
    glBindTexture(GL_TEXTURE_2D, hole_texture);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, size, size, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, 0);
    glBindTexture(GL_TEXTURE_2D, 0);

    // create a renderbuffer object to store depth info
    GLuint rboId;
    glGenRenderbuffers(1, &rboId);
    glBindRenderbuffer(GL_RENDERBUFFER, rboId);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, size, size);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

    // bind a framebuffer object
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);

    // attach the texture to FBO color attachment point
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
                           GL_TEXTURE_2D, hole_texture, 0);

    // attach the renderbuffer to depth attachment point
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT,
                              GL_RENDERBUFFER, rboId);

    // switch back to window-system-provided framebuffer
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    if(glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        cout << "error" << endl;
}

void Portal::make_texture(){
    if(other_portal->open){
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);
        LevelManager::reshape(size, size);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();

        vector3 ps = other_portal->getPos();
        vector3 a = other_portal->getDir();
        vector3 u = other_portal->getUp();
        vector3 char_dir = dynamic_cast<Character*>(*entityList->begin())->getDir();
        GLfloat dir1 = dynamic_cast<Character*>(*entityList->begin())->dir1;

        GLfloat orizzontal = asin((dir[0]*char_dir[2]-dir[2]*char_dir[0])/char_dir.length());
        GLfloat vertical = asin((dir[0]*dir1-dir[1]*char_dir[0])/char_dir.length());
        a = rotate_vector(a, vector3(0.0,0.0,1.0), -vertical);
        a = rotate_vector(a, vector3(0.0,1.0,0.0), orizzontal);

        a = ps + a;
        if(other_portal->open)
            gluLookAt(ps[0],ps[1],ps[2], a[0],a[1],a[2], u[0],u[1],u[2]);

        //dynamic_cast<Character*>(*entityList->begin())->look();
        list<Entity*>::iterator p = entityList->end();
        for (p--; p!=entityList->begin(); p--){
            glPushMatrix();
            (*p)->drawEntity();
            glPopMatrix();
        }

        // unbind FBO
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        LevelManager::reshape(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
    }
}

void Portal::drawEntity(){

    glTranslatef(pos[0],pos[1],pos[2]);
    glMultMatrixf(dirMat);

    glActiveTexture(GL_TEXTURE0);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, mask);
    glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_SUBTRACT);
    glActiveTexture(GL_TEXTURE1);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, hole_texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_SUBTRACT);
    glActiveTexture(GL_TEXTURE2);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture);
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, param);

    glCallList(listIndex);

    glActiveTexture (GL_TEXTURE2);
    glDisable (GL_TEXTURE_2D);
    glActiveTexture (GL_TEXTURE1);
    glDisable (GL_TEXTURE_2D);
    glActiveTexture (GL_TEXTURE0);
    glDisable (GL_TEXTURE_2D);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

}

void Portal::set_position(vector3 pos, vector3 dir, vector3 up){
    if(other_portal->open){
        texture = texture_open;
        other_portal->texture = other_portal->texture_open;
        param=GL_DECAL;
        other_portal->param = GL_DECAL;
    }
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
