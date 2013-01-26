#include "../include/Entity.h"

Entity::Entity(vector3 pos, GLfloat angle){
    Entity::pos = pos;
    Entity::angle = angle;
}

Entity::Entity(vector3 pos, vector3 dir, vector3 up){
    Entity::pos = pos;//+vector3(0.0,0.02,0.0);
    Entity::dir = dir;
    Entity::up = up;
    dirMat[12]=0; dirMat[13]=0; dirMat[14]=0;
    dirMat[3]=0; dirMat[7]=0; dirMat[11]=0; dirMat[15]=1;
    updateDirMat();
}

void Entity::updateDirMat(){
    dir.normalize();
    vector3 right = cross(up, dir);
    right.normalize();
    dirMat[0]=right[0];   dirMat[4]=up[0]; dirMat[8]=dir[0];   //dirMat[12]=0;
    dirMat[1]=right[1];   dirMat[5]=up[1]; dirMat[9]=dir[1];   //dirMat[13]=0;
    dirMat[2]=right[2];   dirMat[6]=up[2]; dirMat[10]=dir[2];  //dirMat[14]=0;
    //dirMat[3]=0;        dirMat[7]=0;     dirMat[11]=0;         dirMat[15]=1;
}

vector3 Entity::getPos(){
    return pos;
}
void Entity::setPos(vector3 pos){
    Entity::pos = pos;
}

void Entity::setDir(vector3 dir){
    Entity::dir = dir;
}

vector3 Entity::getDir(){
    return dir;
}

vector3 Entity::getUp(){
    return up;
}

GLfloat* Entity::getBBox(){
    return bbox;
}
void Entity::setBBox(GLfloat* bbox){
    Entity::bbox = bbox;
}

GLuint Entity::LoadTextureRAW(string filename) {
    GLuint texture;
    //image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);


    fif = FreeImage_GetFileType(filename.c_str(), 0);
	//if still unknown, try to guess the file format from the file extension
	if(fif == FIF_UNKNOWN){
		fif = FreeImage_GetFIFFromFilename(filename.c_str());
		cout << "Getting Image Type" << endl;
	}
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN) cout << "Failed to get image type" << endl;

	//check that the plugin has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif)){
		//dib = FreeImage_ConvertTo32Bits(dib);
		dib = FreeImage_Load(fif, filename.c_str());
	}
	//if the image failed to load, return failure
	if(!dib) cout << "Failed to load image" << endl;


    bits = FreeImage_GetBits(dib);
    width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

    // allocate a texture name
    glGenTextures(1, &texture);


    glBindTexture(GL_TEXTURE_2D, texture); //Tell OpenGL which texture to edit
        //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGB,                       //Format OpenGL uses for image
                 width, height,  //Width and height
                 0,                            //The border of the image
                 GL_BGR, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                   //as unsigned numbers
                 bits);               //The actual pixel data

    FreeImage_Unload(dib);
    return texture;
}


GLuint Entity::LoadTextureRGBA(string filename) {
    GLuint texture;
    //image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);


    fif = FreeImage_GetFileType(filename.c_str(), 0);
	//if still unknown, try to guess the file format from the file extension
	if(fif == FIF_UNKNOWN){
		fif = FreeImage_GetFIFFromFilename(filename.c_str());
		cout << "Getting Image Type" << endl;
	}
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN) cout << "Failed to get image type" << endl;

	//check that the plugin has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif)){
		//dib = FreeImage_ConvertTo32Bits(dib);
		dib = FreeImage_Load(fif, filename.c_str());
	}
	//if the image failed to load, return failure
	if(!dib) cout << "Failed to load image" << endl;


    bits = FreeImage_GetBits(dib);
    width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

    // allocate a texture name
    glGenTextures(1, &texture);


    glBindTexture(GL_TEXTURE_2D, texture); //Tell OpenGL which texture to edit
        //Map the image to the texture
    glTexImage2D(GL_TEXTURE_2D,                //Always GL_TEXTURE_2D
                 0,                            //0 for now
                 GL_RGBA,                       //Format OpenGL uses for image
                 width, height,  //Width and height
                 0,                            //The border of the image
                 GL_BGRA, //GL_RGB, because pixels are stored in RGB format
                 GL_UNSIGNED_BYTE, //GL_UNSIGNED_BYTE, because pixels are stored
                                   //as unsigned numbers
                 bits);               //The actual pixel data

    FreeImage_Unload(dib);
    return texture;
}
