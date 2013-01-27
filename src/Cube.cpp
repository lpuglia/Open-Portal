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
	std::pair<std::vector<vector3>,std::vector<Floor*> > colliders = collision();

    //find below floor
    std::vector<Floor*>::iterator its;
    Floor* below_floor;
    GLfloat below_height=-100.0;
    for(its=colliders.second.begin(); its!=colliders.second.end(); its++){
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
        if(colliders.first.size()!=0 && !wall_collide){
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

std::pair<std::vector<vector3>,std::vector<Floor*> > Cube::collision(){
    std::pair<std::vector<vector3>,std::vector<Floor*> > collider;
    collider.first = std::vector<vector3>();
    collider.second = std::vector<Floor*>();

    vector3 ld;
    vector3 zeros = vector3(0,0,0);
    list<Entity*>::iterator p;
    for (p = entityList->begin(), p++; p!=entityList->end(); p++){
        if (Wall* wall = dynamic_cast<Wall*>(*p)) {
            ld = wall->collision_detection(pos);
            if(ld!=zeros)
                collider.first.push_back(ld);
        }
        else if (Floor* floor = dynamic_cast<Floor*>(*p)) {
            ld = floor->collision_detection(pos);
            if(ld!=zeros)
                collider.second.push_back(floor);
        }
    }
    return collider;
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
