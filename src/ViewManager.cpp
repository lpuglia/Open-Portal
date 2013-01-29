#include "../include/ViewManager.h"

ViewManager::ViewManager(vector3 pos, GLfloat peak, EntityList *entList)
            :Character(pos,80.0,entList)
{
    hWidth=glutGet(GLUT_WINDOW_WIDTH)/2;
    hHeight=glutGet(GLUT_WINDOW_HEIGHT)/2;
    ViewManager::peak = peak;

    view = vector3(1.0,0.0,0.0);

    glutSetCursor(GLUT_CURSOR_NONE);
    glutWarpPointer(hWidth, hHeight);
}

void ViewManager::look(){
    gluLookAt(pos[0], pos[1]+peak, pos[2], at[0], at[1]+peak, at[2], up[0], up[1], up[2]);
    //cout << pos[0] <<" "<< pos[1]+peak <<" "<< pos[2] <<" "<< at[0] <<" "<< at[1]+peak <<" "<< at[2] <<" "<< up[0] <<" "<< up[1] <<" "<< up[2] << endl;
}

void ViewManager::mouseMotion(int x, int y){
    int centerX = hWidth;
    int centerY = hHeight;
    glutWarpPointer(centerX, centerY);

    dir = rotate_vector(dir, vector3(0.0, 1.0, 0.0), -((float)(x-centerX))*0.002);
    side = cross(-dir, up);
    side.normalize();

    dir1 += -0.001*(float)(y-centerY);
    at = pos + dir;
    at[1] += dir1;
}
