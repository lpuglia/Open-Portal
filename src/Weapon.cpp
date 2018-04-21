#include "Weapon.h"

Weapon::Weapon(EntityList *entList)
    :Item(vector3(0.0,0.0,0.0),vector3(0.0,0.0,-1.0), entList)
{
    GLfloat gun1c[]={0.4,-1.0,-0.1, 0.8,-1.0,-0.1, 0.8,-0.5,-1.3, 0.4,-0.5,-1.3};
    GLfloat gun2c[]={0.4,-2.0,0.1, 0.4,-1.0,-0.1, 0.4,-0.5,-1.3, 0.4,-1.0,-1.3};
    GLfloat gun3c[]={0.5,-0.6,-1.3, 0.7,-0.6,-1.3, 0.7,-0.5,-1.5, 0.5,-0.5,-1.5};
    GLfloat gun4c[]={0.5,-0.6,-1.3, 0.5,-0.5,-1.5, 0.5,-1.0,-1.5, 0.5,-1.0,-1.5};
    GLfloat gun5c[]={0.3,-0.7,-1.5, 0.8,-0.7,-1.5, 0.8,-0.3,-1.5, 0.3,-0.3,-1.5};
    GLfloat texcoordsc[] = { 0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0};
    memcpy(gun1, gun1c, sizeof(GLfloat)*12);
    memcpy(gun2, gun2c, sizeof(GLfloat)*12);
    memcpy(gun3, gun3c, sizeof(GLfloat)*12);
    memcpy(gun4, gun4c, sizeof(GLfloat)*12);
    memcpy(gun5, gun5c, sizeof(GLfloat)*12);
    memcpy(texcoords, texcoordsc, sizeof(GLfloat)*8);

    texgun1 = LoadTextureRAW("../texture/gun1.png");
    texgun2 = LoadTextureRAW("../texture/gun2.png");
    texgun3 = LoadTextureRAW("../texture/gun3.png");
    texgun5 = LoadTextureRGBA("../texture/gun5.png");

    listIndex = glGenLists(1);
    glNewList(listIndex, GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, texgun5);
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

            glBindTexture(GL_TEXTURE_2D, texgun3);
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

            glBindTexture(GL_TEXTURE_2D, texgun1);
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

        glDisable(GL_TEXTURE_2D);
    glEndList();
}


void Weapon::drawEntity(){
    glCallList(listIndex);
}

void Weapon::movement(){
}

void Weapon::shot_portal(vector3 pos, vector3 dir, vector3* portal_pos, vector3* portal_dir, vector3* portal_up){
    vector3 ld_pos;
    GLfloat min_dist = 10000.0;
    vector3 zeros = vector3(0.0,0.0,0.0);
    list<Entity*>::iterator p;
    for (p = entityList->begin(), p++; p!=entityList->end(); p++){
        if (Wall* wall = dynamic_cast<Wall*>(*p)) {
            ld_pos = wall->shot_detection(pos, dir, &min_dist);
            if(ld_pos!=zeros){
                *portal_pos=ld_pos;
                *portal_dir=wall->getDir();
                *portal_up=wall->getUp();
            }
        }else if (Floor* floor = dynamic_cast<Floor*>(*p)) {
            ld_pos = floor->shot_detection(pos, dir, &min_dist);
            if(ld_pos!=zeros){
                *portal_pos=ld_pos;
                *portal_dir=floor->getDir();
                *portal_up=floor->getUp();
            }
        }else if (Geometry* geometry = dynamic_cast<Geometry*>(*p)) {
            ld_pos = geometry->shot_detection(pos, dir, &min_dist);
            if(ld_pos!=zeros){
                *portal_pos=ld_pos;
                *portal_dir=geometry->getDir();
                *portal_up=geometry->getUp();
            }
        }
    }
}
