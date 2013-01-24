#include "../include/LevelDelimiter.h"

LevelDelimiter::LevelDelimiter(vector3 pos, vector3 dir, vector3 up, vector3 vertex1, vector3 vertex2, vector3 vertex3,
                                vector3 vertex4, vector3 color):Entity(pos, dir.normalize(), up)
{
    updateDirMat();

    /*texcoords={ vertex1[0],vertex1[1],vertex1[2],
                vertex2[3],vertex2[4],vertex2[5],
                vertex3[6],vertex3[7],vertex3[8],
                vertex4[9],vertex4[10],vertex4[11]};*/

    vertices[0]=dirMat[0]*vertex1[0]+dirMat[4]*vertex1[1]+dirMat[8]*vertex1[2]+pos[0];
    vertices[1]=dirMat[1]*vertex1[0]+dirMat[5]*vertex1[1]+dirMat[9]*vertex1[2]+pos[1];
    vertices[2]=dirMat[2]*vertex1[0]+dirMat[6]*vertex1[1]+dirMat[10]*vertex1[2]+pos[2];

    vertices[3]=dirMat[0]*vertex2[0]+dirMat[4]*vertex2[1]+dirMat[8]*vertex2[2]+pos[0];
    vertices[4]=dirMat[1]*vertex2[0]+dirMat[5]*vertex2[1]+dirMat[9]*vertex2[2]+pos[1];
    vertices[5]=dirMat[2]*vertex2[0]+dirMat[6]*vertex2[1]+dirMat[10]*vertex2[2]+pos[2];

    vertices[6]=dirMat[0]*vertex3[0]+dirMat[4]*vertex3[1]+dirMat[8]*vertex3[2]+pos[0];
    vertices[7]=dirMat[1]*vertex3[0]+dirMat[5]*vertex3[1]+dirMat[9]*vertex3[2]+pos[1];
    vertices[8]=dirMat[2]*vertex3[0]+dirMat[6]*vertex3[1]+dirMat[10]*vertex3[2]+pos[2];

    vertices[9]=dirMat[0]*vertex4[0]+dirMat[4]*vertex4[1]+dirMat[8]*vertex4[2]+pos[0];
    vertices[10]=dirMat[1]*vertex4[0]+dirMat[5]*vertex4[1]+dirMat[9]*vertex4[2]+pos[1];
    vertices[11]=dirMat[2]*vertex4[0]+dirMat[6]*vertex4[1]+dirMat[10]*vertex4[2]+pos[2];

    colors={color[0],color[1],color[2],
            color[0],color[1],color[2],
            color[0],color[1],color[2],
            color[0],color[1],color[2]};

    faceIndices={0,1,2,3};
}

void LevelDelimiter::drawEntity(){
    /*glEnableClientState(GL_COLOR_ARRAY);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);
    glDrawElements(GL_QUADS, 12, GL_UNSIGNED_BYTE, faceIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);*/

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
    glDrawElements(GL_QUADS, 12, GL_UNSIGNED_BYTE, faceIndices);
    glDisableClientState(GL_VERTEX_ARRAY);
    glDisableClientState(GL_COLOR_ARRAY);

    glDisable(GL_TEXTURE_2D);
}

GLuint LevelDelimiter::LoadTextureRAW(const char* filename) {
    GLuint texture;
    //image format
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	//pointer to the image, once loaded
	FIBITMAP *dib(0);
	//pointer to the image data
	BYTE* bits(0);
	//image width and height
	unsigned int width(0), height(0);


    fif = FreeImage_GetFileType(filename, 0);
	//if still unknown, try to guess the file format from the file extension
	if(fif == FIF_UNKNOWN){
		fif = FreeImage_GetFIFFromFilename(filename);
		cout << "Getting Image Type" << endl;
	}
	//if still unkown, return failure
	if(fif == FIF_UNKNOWN) cout << "Failed to get image type" << endl;

	//check that the plugin has reading capabilities and load the file
	if(FreeImage_FIFSupportsReading(fif)){
		//dib = FreeImage_ConvertTo32Bits(dib);
		dib = FreeImage_Load(fif, filename);
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
