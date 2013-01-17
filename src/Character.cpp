#include "../include/Character.h"

Character::Character(vector3 pos, GLfloat mass, EntityList *entList)
         :Item(pos,vector3(0.0,0.0,-1.0), mass, vector3(0.0,700.0,0.0)*(1/mass)*0.5, entList)
{
    releaseForce = vector3(0.0,5.0,0.0);
    shotForce = 30.0;
    at=vector3(0.0,0.0,0.0);
    dir1=0.0;

    moveForward=false; moveBackward=false; moveRight=false; moveLeft=false;
    jump = false; run = false;
    takenEntity=NULL;
}

void Character::mouse(int button, int state, int x, int y){
    if(takenEntity!=NULL)
        if(button==GLUT_LEFT_BUTTON && state==GLUT_DOWN){
            throwEntity();
        }
}

void Character::keyboard(unsigned char key)
{
	switch (key) {
	    /* Exit (Escape key)  */
        case 27: exit (0); break;
        /* Move Forward */
        case 'w': moveForward = true; FB=1.0; break;
        /* Move Backward */
        case 's': moveBackward = true; FB=-1.0; break;
        /* Right Strafe */
        case 'd': moveRight = true; RL=-1.0; break;
        /* Left Strafe */
        case 'a': moveLeft = true; RL=1.0; break;
        /* Jump (Space key) */
        case 32:
            if(!jump){
                jump = true;
                t0 = glutGet(GLUT_ELAPSED_TIME);
                x0 = pos;
            }
            break;
        default:
            break;
	}
}

void Character::keyboardUp(unsigned char key)
{

	switch ( key ) {
        /* Move Forward */
        case 'w': moveForward = false; break;
        /* Move Backward */
        case 's': moveBackward = false; break;
        /* Right Strafe */
        case 'd': moveRight = false; break;
        /* Left Strafe */
        case 'a': moveLeft = false; break;
        /* Take */
        case 'e':
            if(takenEntity==NULL) takeEntity();
            else releaseEntity();
            break;
        default:
            break;
	}
}

void Character::specialKeyboard(int key){
}

void Character::movement(){

    float interval = pe.idle()/100;
    float temp;
    vector3 tmp2;
    vector3 tmp3;

    vector3 tmp = dir;
    tmp2 = tmp;
	std::vector<vector3> colliders = collision();

    std::vector<vector3>::const_iterator it;
    if(colliders.size()!=0){
        for(it=colliders.begin(); it!=colliders.end(); it++){
            vector3 collider = *it;
            cout << collider << endl;

            //perpendicular of collider
            collider[0] = collider[0] + collider[2];
            collider[2] = collider[0] - collider[2];
            collider[0] = collider[0] - collider[2];
            collider[2] = -collider[2];
            collider[1] = 0;

            GLfloat cosangle1 = (tmp2[0]*collider[0]+tmp2[2]*collider[2])/(tmp2.length()*collider.length());
            GLfloat sinangle1 = (tmp2[0]*collider[2]-tmp2[2]*collider[0])/(tmp2.length()*collider.length());
            GLfloat cosangle2 = (side[0]*collider[0]+side[2]*collider[2])/(side.length()*collider.length());

            /*cout << cosangle1 << endl;
            cout << sinangle1 << endl;
            cout << collider << endl;
            cout << tmp2 << endl;
            cout << collider*cosangle1 << endl;
            //cout << tmp2 << endl;
            cout << "------------" << endl;*/
            if((cosangle1<0.0 && moveRight) || (cosangle1>=0.0 && moveLeft)){
                tmp3 = collider*cosangle2;
            }else{
                tmp3 = side;
            }
            if((sinangle1>0.0 && moveForward) || (sinangle1<=0.0 && moveBackward))
                tmp2 = collider*cosangle1;


            //tmp2.normalize();
            //tmp2[1]=0.0;
            tmp3[1]=0.0;
        }
        //cout << "-----" << endl;
    }else{
        tmp2 = tmp;
        tmp3 = side;
    }
    tmp[1]=dir1;

    /*if(collider[0]!=0.0 && FB*collider[0]*dir[0]<0.0)
        tmp2[0]=0.0;
    if(collider[2]!=0.0 && FB*collider[2]*dir[2]<0.0)
        tmp2[2]=0.0;
    if(collider[0]!=0.0 && RL*collider[0]*side[0]<0.0)
        tmp3[0]=0.0;
    if(collider[2]!=0.0 && RL*collider[2]*side[2]<0.0)
        tmp3[2]=0.0;*/

 	if(moveForward){
		pos = pos + interval*tmp2;
		at = pos + tmp;
	}
	if(moveBackward){
		pos = pos - interval*tmp2;
		at = pos + tmp;
	}
	if(moveRight){
		pos = pos - interval*tmp3;
		at = pos + tmp;
	}
	if(moveLeft){
		pos = pos + interval*tmp3;
		at = pos + tmp;
	}

    //cout << collider[1] << endl;
	if(jump){
        pos = pe.getProjectileMotion(pos, v0, t0);
        if(pos[1]<x0[1]){
            pos[1]=0.02;
            jump=false;
        }
        at[1]=pos[1]+dir1;
	}

}

std::vector<vector3> Character::collision(){
    std::vector<vector3> collider;

    Wall* wall = new Wall();
    Floor* fl = new Floor();
    vector3 ld;
    vector3 zeros = vector3(0,0,0);
    list<Entity*>::iterator p;
    for (p = entityList->begin(), p++; p!=entityList->end(); p++){
        if (typeid(**p) == typeid(*wall) || typeid(**p) == typeid(*fl)){
            ld = ((LevelDelimiter*)(*p))->isInFront(pos,dir);
            if(ld!=zeros){
                collider.push_back(ld);
            }
        }
    }
    return collider;
}


void Character::drawEntity(){
    glPushMatrix();
    if(takenEntity!=NULL){
        takenEntity->drawEntity();
    }
    glPopMatrix();
    look();
}

void Character::takeEntity(){
    list<Entity*>::iterator nearest;
    vector3 minDist;
    GLfloat minDistLength = 10000000;
    GLfloat dirLength = dir.length();

    list<Entity*>::iterator p;
    for (p = entityList->begin(), p++; p!=entityList->end(); p++){
        if (typeid(**p) != typeid(bound)){
            //cout << typeid(**p).name() << endl;
            vector3 pos = (*p)->getPos();
            vector3 dist = Character::pos - pos;
            GLfloat distLength = dist.length();
            GLfloat angleCos = (dir[0]*dist[0]+dir[1]*dist[1]+dir[2]*dist[2])/(dirLength*distLength);

            if(angleCos<-0.75 && distLength<3.0 && distLength<minDistLength){
                    nearest = p;
                    takenEntity = *p;
                    minDist = dist;
                    minDistLength = distLength;
            }
        }else break;
    }

    if(takenEntity!=NULL){
        ///TODO
        //Note #7
        /*GLfloat angle = ((Cube*)takenEntity)->getAngle();

        vector3 cubeDir = rotate_vector(vector3(0.0,0.0,1.0), vector3(0.0, 1.0, 0.0), angle);
        cout << cubeDir << endl;
        GLfloat cosAlfa = (cubeDir[0]*minDist[0]+cubeDir[1]*minDist[1]+cubeDir[2]*minDist[2])/(minDistLength);
        cout << cosAlfa << endl;
        GLfloat gamma = ((acos(cosAlfa)/3.14)*180.0);
        //if(minDist[0]>0) gamma=-gamma;//<<<<<<<<<<
        cout << gamma << endl << endl;
        ((Cube*)takenEntity)->setAngle(gamma);*/

        takenEntity->setPos(vector3(0.0,-0.5,-2.0));
        entityList->erase(nearest);
    }
}

void Character::releaseEntity(){
    Cube* cube = ((Cube*)takenEntity);
    ///TODO
    /*GLfloat angle = dir[2]/(dir.length());
    angle = (acos(angle)/3.14)*180.0;
    cout << angle << endl;
    cube->setAngle(angle + cube->getAngle());*/
    cube->setCollide(false);
    cube->setV0(releaseForce*(1/cube->getMass())*0.5);
    takenEntity->setPos(pos+vector3(0.0,1.0+dir1,0.0)+dir*2);
    cout << takenEntity->getPos() << endl;
    entityList->insert(++(entityList->begin()),takenEntity); //insert after the first element
    takenEntity = NULL;
}

void Character::throwEntity(){
    Cube* cube = ((Cube*)takenEntity);
    cube->setCollide(false);
    cube->setV0(((shotForce)*vector3(dir[0],dir1,dir[2]))*(1/cube->getMass())*0.5);
    takenEntity->setPos(pos+vector3(0.0,1.4+dir1,0.0)+dir*2);
    entityList->insert(++(entityList->begin()),takenEntity); //insert after the first element
    takenEntity = NULL;
}
