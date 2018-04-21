#include "Interface.h"

Interface::Interface(Portal* blue, Portal* orange) {
    Interface::blue = blue;
    Interface::orange = orange;
    GLfloat uic[] = {-0.1,-0.1,-0.7, 0.1,-0.1,-0.7, 0.1,0.1,-0.7, -0.1,0.1,-0.7};
    memcpy(ui, uic, sizeof(GLfloat)*12);

    uiblue = LoadTextureRGBA("../texture/uiblue.png");
    uiorange = LoadTextureRGBA("../texture/uiorange.png");
    uiblueorange = LoadTextureRGBA("../texture/uiblueorange.png");
    uivoid = LoadTextureRGBA("../texture/uivoid.png");

    listIndex = glGenLists(1);
    glNewList(listIndex, GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
            glColor3f(1.0f, 1.0f, 1.0f);
            glEnable (GL_BLEND);
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
    if(!blue->open && !orange->open) glBindTexture(GL_TEXTURE_2D, uiblueorange);
    else if(blue->open && !orange->open) glBindTexture(GL_TEXTURE_2D, uiorange);
    else if(!blue->open && orange->open) glBindTexture(GL_TEXTURE_2D, uiblue);
    else if(blue->open && orange->open) glBindTexture(GL_TEXTURE_2D, uivoid);

    glCallList(listIndex);
}

void Interface::movement(){
}
