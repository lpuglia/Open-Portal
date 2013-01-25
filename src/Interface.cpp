#include "../include/Interface.h"

Interface::Interface() {
    ui={-0.1,-0.1,-0.5, 0.1,-0.1,-0.5, 0.1,0.1,-0.5, -0.1,0.1,-0.5};
    uiblue = LoadTextureRGBA("texture/uiblue.png");
    uiorange = LoadTextureRGBA("texture/uiorange.png");
    uiblueorange = LoadTextureRGBA("texture/uiblueorange.png");
    uivoid = LoadTextureRGBA("texture/uivoid.png");

    listIndex = glGenLists(1);
    glNewList(listIndex, GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, uiblueorange);
            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glColor3f(1.0f, 1.0f, 1.0f);
            glEnable (GL_BLEND);
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glBegin(GL_QUADS);
                    glTexCoord2f(0.0, 0.0);
                    glVertex3f(ui[0], ui[1], ui[2]);
                    glTexCoord2f(1.0, 0.0);
                    glVertex3f(ui[3], ui[4], ui[5]);
                    glTexCoord2f(1.0, 1.0);
                    glVertex3f(ui[6], ui[7], ui[8]);
                    glTexCoord2f(0.0, 1.0);
                    glVertex3f(ui[9], ui[10], ui[11]);
                glEnd();
            glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glEndList();
}

Interface::~Interface()
{
    //dtor
}

void Interface::drawEntity(){
    glCallList(listIndex);
}

void Interface::movement(){
}
