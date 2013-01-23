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
    floor_collide=false;
    wall_collide=false;
    initialize();
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
        if(floor_height-1.0<=pos[1] && floor_height>=below_height){
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
