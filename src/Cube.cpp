#include "../include/Cube.h"

Cube::Cube(vector3 pos, vector3 dir, EntityList *entList)
    :Item(pos, dir, 5.0, vector3(0.0,0.0,0.0),entList)
{
    GLfloat vert[48] =
     {-0.5f, 0.0f, 0.5f,   0.5f, 0.0f, 0.5f,   0.5f, 1.0f, 0.5f,  -0.5f, 1.0f, 0.5f,
      -0.5f, 1.0f, -0.5f,  0.5f, 1.0f, -0.5f,  0.5f, 0.0f, -0.5f, -0.5f, 0.0f, -0.5f,
       0.5f, 0.0f, 0.5f,   0.5f, 0.0f, -0.5f,  0.5f, 1.0f, -0.5f,  0.5f, 1.0f, 0.5f,
       -0.5f, 0.0f, -0.5f,  -0.5f, 0.0f, 0.5f,  -0.5f, 1.0f, 0.5f, -0.5f, 1.0f, -0.5f
      }; vertices=vert;

    GLfloat texc[32] = { 0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
                      0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
                      0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0,
                      0.0,0.0, 1.0,0.0, 1.0,1.0, 0.0,1.0
                    }; texcoords=texc;

    GLubyte cind[24] = {0,1,2,3, 4,5,6,7, 3,2,5,4, 7,6,1,0,  8,9,10,11, 12,13,14,15};
    cubeIndices=cind;

    init = false;
    floor_collide=false;
    wall_collide=false;
    texture = LoadTextureRAW("texture/cube.png");
    initialize();
}

/* maxi combo Vertex Array + Display List */
void Cube::initialize(){
    listIndex = glGenLists(1);
    glNewList(listIndex, GL_COMPILE);
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);
        glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glColor3f(1.0f, 1.0f, 1.0f);

        glEnableClientState(GL_TEXTURE_COORD_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);

        glTexCoordPointer(2, GL_FLOAT, 0, texcoords);
        glVertexPointer(3, GL_FLOAT, 0, vertices);

        glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);
        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_TEXTURE_COORD_ARRAY);
        glDisable(GL_TEXTURE_2D);
    glEndList();
    init=true;
}

void Cube::drawEntity(){
    glTranslatef(pos[0],pos[1],pos[2]);
    glMultMatrixf(dirMat);
    //glRotatef(angle, 0.0, 1.0, 0.0);
    //cout << vertices[0] << " " << vertices[1] << " " << vertices[2] << endl;
    glCallList(listIndex);
}

void Cube::movement(){
  	std::vector<vector3> walls;
	std::vector<Floor*> floors;
	Portal* teleport_portal = collision(&walls, &floors);

	if(teleport_portal!=NULL){
        vector3 other_dir = teleport_portal->other_portal->getDir();
        GLfloat rot_angle = asin(dir[0]*other_dir[2]-dir[2]*other_dir[0]);

        if(teleport_portal->getDir()[1]==0.0){
            pos = teleport_portal->getPos()+teleport_portal->getDir()*1.3;
            dir[0] = teleport_portal->getDir()[0];
            dir[2] = teleport_portal->getDir()[2];
        }else
            pos = teleport_portal->getPos()+teleport_portal->getDir()*1.3;

        floor_collide=false;
        v0 = vector3(0.0,0.0,0.0);
        t0 = glutGet(GLUT_ELAPSED_TIME);
        return;
	}

    //find below floor
    std::vector<Floor*>::iterator its;
    Floor* below_floor;
    GLfloat below_height=-100.0;
    for(its=floors.begin(); its!=floors.end(); its++){
        Floor* fl = *its;
        GLfloat floor_height = fl->get_height(pos);
        //cout << pos[1] << " " << floor_height << " " << below_height << endl;
        if(floor_height-1.0<=pos[1] && floor_height>=below_height && fl->getDir()[1]>0.0){
            below_floor=fl;
            below_height=floor_height;
        }
    }

    //colide reaction and landing
	if(!floor_collide){
        if(walls.size()!=0 && !wall_collide){
            setCollide(false);
            wall_collide=true;
            setV0(vector3(0.0,0.0,0.0));
        }
        pos = pe.getProjectileMotion(pos, v0, t0);
        if(pos[1]<=below_height){
            up =  below_floor->getDir();
            dir = below_floor->getUp();
            updateDirMat();
            floor_collide=true;
            wall_collide=false;
            pos[1]=below_floor->get_height(pos);
        }
	}
    /*if(!collide){
        if(pos[1]>0.0){
            pos = pe.getProjectileMotion(pos, v0, t0);
        }else{
            pos[1]=0.0; collide=true;
        }
    }*/
}

Portal* Cube::collision(std::vector<vector3>* walls, std::vector<Floor*>* floors){
    Portal* teleport_portal=NULL;
    vector3 ld;
    vector3 zeros = vector3(0,0,0);
    list<Entity*>::iterator p;
    for (p = entityList->begin(), p++; p!=entityList->end(); p++){
        if (Portal* portal = dynamic_cast<Portal*>(*p)) {
            teleport_portal = portal->teleport_detection(pos);
            if(teleport_portal!=NULL) break;
        }else if (Wall* wall = dynamic_cast<Wall*>(*p)) {
            ld = wall->collision_detection(pos);
            if(ld!=zeros) walls->push_back(ld);
        }
        else if (Floor* floor = dynamic_cast<Floor*>(*p)) {
            ld = floor->collision_detection(pos);
            if(ld!=zeros) floors->push_back(floor);
        }
    }
    return teleport_portal;
}

vector3 Cube::collision_detection(vector3 pos){
    ///OPTIMIZE
    //note #10
    return vector3(0.0,0.0,0.0);
}

void Cube::setCollide(bool collide){
    floor_collide=collide;
    t0 = glutGet(GLUT_ELAPSED_TIME);
}
bool Cube::getCollide(){
    return floor_collide;
}
