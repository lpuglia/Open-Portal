#include "../include/Weapon.h"

Weapon::Weapon()
{
    gun1={0.4,-1.0,-0.1, 0.8,-1.0,-0.1, 0.8,-0.5,-1.3, 0.4,-0.5,-1.3};
    gun2={0.4,-1.0,-0.1, 0.4,-0.5,-1.3, 0.4,-1.0,-1.3, 0.4,-2.0,0.1};
    gun3={0.5,-0.6,-1.3, 0.7,-0.6,-1.3, 0.7,-0.5,-1.5, 0.5,-0.5,-1.5};
    gun4={0.5,-0.6,-1.3, 0.5,-0.5,-1.5, 0.5,-1.0,-1.5, 0.5,-1.0,-1.5};
    gun5={0.3,-0.8,-1.5, 0.8,-0.8,-1.5, 0.8,-0.3,-1.5, 0.3,-0.3,-1.5};
    //vertices={-1.0,0.0,-0.5, 1.0,0.0,-0.5, 1.0,1.0,-0.5, -1.0,1.0,-0.5 };
    //faceIndices={0,1,2,3, 0,3,4,5, 6,7,8,9, 6,9,10,11};
    texcoords = { 0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0};

    texgun1 = LoadTextureRAW("texture/gun1.png");
    texgun2 = LoadTextureRAW("texture/gun2.png");
    texgun3 = LoadTextureRAW("texture/gun3.png");
    texgun5 = LoadTextureRGBA("texture/gun5.png");

    listIndex = glGenLists(1);
    glNewList(listIndex, GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texgun1);
            glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0);
                glVertex3f(gun1[0], gun1[1], gun1[2]);
                glTexCoord2f(1.0, 0.0);
                glVertex3f(gun1[3], gun1[4], gun1[5]);
                glTexCoord2f(1.0, 1.0);
                glVertex3f(gun1[6], gun1[7], gun1[8]);
                glTexCoord2f(0.0, 1.0);
                glVertex3f(gun1[9], gun1[10], gun1[11]);
            glEnd();

            glBindTexture(GL_TEXTURE_2D, texgun2);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0);
                glVertex3f(gun2[0], gun2[1], gun2[2]);
                glTexCoord2f(1.0, 0.0);
                glVertex3f(gun2[3], gun2[4], gun2[5]);
                glTexCoord2f(1.0, 1.0);
                glVertex3f(gun2[6], gun2[7], gun2[8]);
                glTexCoord2f(0.0, 1.0);
                glVertex3f(gun2[9], gun2[10], gun2[11]);
            glEnd();

            glBindTexture(GL_TEXTURE_2D, texgun3);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0);
                glVertex3f(gun3[0], gun3[1], gun3[2]);
                glTexCoord2f(1.0, 0.0);
                glVertex3f(gun3[3], gun3[4], gun3[5]);
                glTexCoord2f(1.0, 1.0);
                glVertex3f(gun3[6], gun3[7], gun3[8]);
                glTexCoord2f(0.0, 1.0);
                glVertex3f(gun3[9], gun3[10], gun3[11]);
            glEnd();
            glBindTexture(GL_TEXTURE_2D, texgun3);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glColor3f(1.0f, 1.0f, 1.0f);
            glBegin(GL_QUADS);
                glTexCoord2f(0.0, 0.0);
                glVertex3f(gun4[0], gun4[1], gun4[2]);
                glTexCoord2f(1.0, 0.0);
                glVertex3f(gun4[3], gun4[4], gun4[5]);
                glTexCoord2f(1.0, 1.0);
                glVertex3f(gun4[6], gun4[7], gun4[8]);
                glTexCoord2f(0.0, 1.0);
                glVertex3f(gun4[9], gun4[10], gun4[11]);
            glEnd();

                glBindTexture(GL_TEXTURE_2D, texgun5);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
                glColor3f(1.0f, 1.0f, 1.0f);
                glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
                glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
                glEnable (GL_BLEND);
                    glBegin(GL_QUADS);
                        glTexCoord2f(0.0, 0.0);
                        glVertex3f(gun5[0], gun5[1], gun5[2]);
                        glTexCoord2f(1.0, 0.0);
                        glVertex3f(gun5[3], gun5[4], gun5[5]);
                        glTexCoord2f(1.0, 1.0);
                        glVertex3f(gun5[6], gun5[7], gun5[8]);
                        glTexCoord2f(0.0, 1.0);
                        glVertex3f(gun5[9], gun5[10], gun5[11]);
                    glEnd();
                glDisable(GL_BLEND);
        glDisable(GL_TEXTURE_2D);
    glEndList();
}


void Weapon::drawEntity(){
    glCallList(listIndex);
}

void Weapon::movement(){
}
