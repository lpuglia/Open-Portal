#include "../include/Floor.h"

vector3 Floor::collision_detection(vector3 pos){
    vector3 dist = Floor::pos - pos;
    dist = surfacePosition - pos;
    dist[0] = Floor::dir[0]*(dist[0]);
    dist[1] = Floor::dir[1]*(dist[1]);
    dist[2] = Floor::dir[2]*(dist[2]);

    GLfloat Ax = pos[0]-vertices[0];
    GLfloat Ay = pos[1]-vertices[1];
    GLfloat Az = pos[2]-vertices[2];
    GLfloat Cx = pos[0]-vertices[6];
    GLfloat Cy = pos[1]-vertices[7];
    GLfloat Cz = pos[2]-vertices[8];

    //cout << vertices[0] << " " << vertices[1] << " " << vertices[6] << " " << vertices[7] << endl;//<<<<<<<<<<<<<<
    //cout << Ax << " " << Ay << " " << Az << " " << Cx << " " << Cy << " " << Cz << endl;//<<<<<<<<<<<<<<
    //cout << abs(Ax)+abs(Cx) << " " << abs(Ay)+abs(Cy) << " " << abs(Az)+abs(Cz) << endl;

    if(abs(Ax)+abs(Cx)>length || abs(Ay)+abs(Cy)>height || abs(Az)+abs(Cz)>length) return vector3(0.0,0.0,0.0);

    if(dist[0]>-0.0 || dist[1]>-0.0 || dist[2]>-0.0){
        return Floor::dir;
    }
    //cout << dist << endl;
    return vector3(0.0,0.0,0.0);
}
