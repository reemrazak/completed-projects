#include <iostream>
#include <cmath>
#include <stdlib.h>
#include <stdio.h>

/* Include header files depending on platform */
#ifdef _WIN32
	#include "glut.h"
	#define M_PI 3.14159
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>
#endif

using namespace std;
GLuint texSet[46];


// You may add more functions here if you like
// ========================================================================


// ========================================================================


void drawCylinder(float radius, float height, float x, float z){
    
    float angleInterval = 0.1;
    float angle = 0;
    float radian;
    

    
    glBegin(GL_QUAD_STRIP);

    for(angle = 0; angle < 360; angle += angleInterval) {
        radian = angle * M_PI /180;
        z = radius * sin(angle);
        x = radius * cos(angle);
        glTexCoord2d(0,1);
        glVertex3f(x, height , z);
        glTexCoord2d(0,0);
        glVertex3f(x, 0 , z);
    }
    glEnd();
    
}

void drawRectangle(float width, float height){
    
    
    glBegin(GL_POLYGON);
    glTexCoord2d(0,1);
    glVertex2f(0, height);
    glTexCoord2d(1,1);
    glVertex2f(width, height);
    glTexCoord2d(1,0);
    glVertex2f(width, 0);
    glTexCoord2d(0,0);
    glVertex2f(0, 0);
    
    glEnd();
}

void drawBase(float x,float y, float z){
    float halfX = x/2;
    float halfZ = z/2;
    
    drawRectangle(x, y);
    

    glPushMatrix();
    glTranslatef(0, 0, z);
    drawRectangle(x, y);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(-z, 0, 0);
    drawRectangle(z, y);
    glPopMatrix();
    
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glTranslatef(-z, 0, x);
    drawRectangle(z, y);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(0, y, 0);
    glRotatef(90, 1, 0, 0);
    drawRectangle(x, z);
    glPopMatrix();
    
}

void drawColumn(float baseHeight, float baseWidth, float columnHeight){

    float columnRadius = baseWidth * .7/2;

        drawBase(baseWidth, baseHeight, baseWidth);
        glPushMatrix();
            glTranslatef(baseWidth/2, baseHeight, baseWidth/2);
            drawCylinder(columnRadius, columnHeight, 0, 0);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0, baseHeight + columnHeight, 0);
            drawBase(baseWidth, baseHeight, baseWidth);
        glPopMatrix();
    

}

void drawColumnRow(float numberOfColumns, float baseHeight, float baseWidth, float columnHeight){
    glPushMatrix();
    for(int i = 0; i < numberOfColumns; i ++)
    {
        drawColumn(baseHeight, baseWidth, columnHeight);
        glTranslatef(baseWidth *2, 0, 0);
    }
    
    glPopMatrix();
}

void drawColumnEdgeRow(float numberOfColumns, float baseHeight, float baseWidth, float columnHeight){
    glPushMatrix();
        drawColumn(baseHeight, baseWidth, columnHeight);
        glTranslatef(baseWidth *2 * (numberOfColumns - 1), 0, 0);
        drawColumn(baseHeight, baseWidth, columnHeight);
    
    glPopMatrix();
}

void drawTriangle(float baseLeft, float baseRight, float height){
    glBegin(GL_POLYGON);
    glTexCoord2d(0,0);
    glVertex2d(baseLeft, 0);
    glTexCoord2d(.5,1);
    glVertex2d((baseLeft + baseRight) / 2, height);
    glTexCoord2d(1,0);
    glVertex2d(baseRight, 0);
    glEnd();
}

void drawTriangularPrism(float x, float y, float z){
    float pythagorean = sqrt(pow(x/2, 2) + pow(y, 2));
    float angle = 180 * tan(pythagorean/y)/M_PI;
    glPushMatrix();
        drawTriangle(0, x, y);
        glPushMatrix();
            glTranslatef(0, 0, z);
            drawTriangle(0, x, y);
        glPopMatrix();
        glRotatef(90, 1 , 0, 0);
        glTranslatef(x/2, 0, -y);

        glRotatef( angle - 90, 0 , 1, 0);
        drawRectangle(pythagorean, z);
        glRotatef(-180 + angle, 0 , 1, 0);
        drawRectangle(pythagorean, z);
    glPopMatrix();
}




void drawMyHouse(GLuint texSet[])
{
	//plot dimension
	//x: -5:5
	//y: >= 0
	//z: -5:5

	// Your main drawing code goes here
	// =========================================
    float drawingSpace = 10;
    float forwardPosition = 3;
    float numberOfColumns = 13;
    float baseHeight = .2;
    float baseWidth = drawingSpace/(numberOfColumns + numberOfColumns);
    float columnHeight = 3;
    float numberOfEdgeRows = 4;
    float currentPosition = forwardPosition;
    
    glEnable(GL_TEXTURE_2D);

        glPushMatrix();
        glTranslatef(-baseWidth * numberOfColumns, 0, currentPosition);
            glBindTexture(GL_TEXTURE_2D, texSet[23]);

            drawColumnRow(numberOfColumns, baseHeight, baseWidth, columnHeight);
        glPopMatrix();
        glPushMatrix();
            for(int i = 1; i <= numberOfEdgeRows; i++)
            {
                currentPosition = forwardPosition - (2*baseWidth * i);
                glPushMatrix();
                glTranslatef(-baseWidth * numberOfColumns, 0, currentPosition);

                drawColumnEdgeRow(numberOfColumns, baseHeight, baseWidth, columnHeight);
                glPopMatrix();
            }
        glPopMatrix();
        glPushMatrix();
            currentPosition -= baseWidth *2;
            glTranslatef(-baseWidth * numberOfColumns, 0, currentPosition);
            drawColumnRow(numberOfColumns, baseHeight, baseWidth, columnHeight);
        glPopMatrix();
        glPushMatrix();
            glTranslatef((-baseWidth * numberOfColumns) + (baseWidth * 2), 0, (2 * baseWidth) - (baseWidth * 2));
                glBindTexture(GL_TEXTURE_2D, texSet[33]);
            drawBase(numberOfColumns - 13 * baseWidth, (columnHeight + baseWidth), ((numberOfEdgeRows + (numberOfEdgeRows - 1))  * baseWidth));
        glPopMatrix();
    glPushMatrix();
    glRotatef(90, 0, 1,0);
    glTranslatef(-forwardPosition - baseWidth, (columnHeight + baseWidth), -numberOfColumns*baseWidth);
    glBindTexture(GL_TEXTURE_2D, texSet[36]);

        drawTriangularPrism((numberOfEdgeRows + 2) * baseWidth * 2 - baseWidth, 1, numberOfColumns  * baseWidth * 2 - baseWidth);
    glPopMatrix();
    
    //draw pool
    glPushMatrix();
    glTranslatef(1, 0, -4.5);
    
    glBindTexture(GL_TEXTURE_2D, texSet[0]);
    drawBase(3, .11, 3);
    glPushMatrix();
    glTranslatef(-5.5, 0, 0);
    drawBase(4.6, .11, 3);
    glPopMatrix();
    glBindTexture(GL_TEXTURE_2D, texSet[8]);
    glTranslatef(.2, 0, .2);
    drawBase(2.6, .13, 2.6);
    glBindTexture(GL_TEXTURE_2D, texSet[44]);
    glTranslatef(-5.5, 0, 0);

    drawBase(4.2, .13, 2.6);


    

    
    glPopMatrix();
    
    
    
	// floor plane (you may remove this)
    glBindTexture(GL_TEXTURE_2D, texSet[10]);
	glBegin(GL_POLYGON);
        glTexCoord2d(0,0);
		glVertex3f(-5, -0.02, -5);
        glTexCoord2d(1,0);
		glVertex3f( 5, -0.02, -5);
        glTexCoord2d(1,1);
		glVertex3f( 5, -0.02,  5);
        glTexCoord2d(0,1);

		glVertex3f(-5, -0.02,  5);
	glEnd();
    
    glDisable(GL_TEXTURE_2D);


	// =========================================
}

// ********** You do not need to edit any code beyond this point **********

// The following code supports loading textures from disk
// ========================================================================
GLuint loadMyTextures(char *filename)
{
	GLuint myTexture;
	FILE * file;
	unsigned char *tex, *tex2;

	// texture data
	int width = 256;
	int height = 256;

	// allocate buffer
	tex = (unsigned char *)malloc(width * height * 3);
	tex2 = (unsigned char *)malloc(width * height * 3);

	// open and read texture data
	file = fopen(filename, "rb");

	if (file == NULL)
		cout << "Error! Missing texture!\n";

	fread(tex, width * height * 3, 1, file);
	fclose(file);

	for (int i = 0; i<width*height; i++)
	{
		tex2[i * 3] = tex[i * 3 + 2];
		tex2[i * 3 + 1] = tex[i * 3 + 1];
		tex2[i * 3 + 2] = tex[i * 3];
	}

	// allocate a texture name
	glGenTextures(1, &myTexture);
	glBindTexture(GL_TEXTURE_2D, myTexture);

	// select modulate to mix texture with color for shading
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_DECAL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_DECAL);

	// when texture area is small, bilinear filter the closest mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_NEAREST);
	// when texture area is large, bilinear filter the first mipmap
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// texture should tile
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// build texture mipmaps
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, width, height, GL_RGB, GL_UNSIGNED_BYTE, tex2);

	// free buffers
	free(tex);
	free(tex2);
	return myTexture;
}
// ========================================================================

// The following code is used to support rotation of the scene with your mouse
// ========================================================================
bool isDraggingLeft = false;
bool isDraggingRight = false;
int prevX = 0, prevY = 0;
int curX = 0, curY = 0;
float angle1 = M_PI, angle2 = -1;	// angles are in radians
float dist = 12.0;
float lookY = 5;
float aspectRatio = 1.0;

void LMBDragged(float dx, float dy) {
	angle1 -= ((float)dx) / 150.0;
	angle2 += ((float)dy) / 150.0;

	if (angle1 < 0)	angle1 += 2 * M_PI;
	else if (angle1 > 2 * M_PI) angle1 -= 2 * M_PI;
	if (angle2 < 0)	angle2 += 2 * M_PI;
	else if (angle2 > 2 * M_PI) angle2 -= 2 * M_PI;
}

void RMBDragged(float dx, float dy) {
	dist += ((float)dx) / 100.0;
	lookY += ((float)dy) / 50.0;
}

void computeCameraPosition() {
	float camX = dist * sin(angle1) * sin(angle2);
	float camY = dist * cos(angle2);
	float camZ = dist * cos(angle1) * sin(angle2);

	float upVectorY = 1.0;
	if (angle2 >= 0 && angle2 < M_PI) {
		upVectorY = -1.0;
	}

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, aspectRatio, 1, 75);
	gluLookAt(camX, camY+lookY, camZ, 0, lookY, 0, 0, upVectorY, 0);
	glMatrixMode(GL_MODELVIEW);
}

void resetCamera() {
	angle1 = M_PI;
	angle2 = -1;
	lookY = 5;
	dist = 15.0;
}
// ========================================================================


// The following code is the usual stuff you give OpenGL
// ========================================================================

void init(void)
{
	glClearColor (0.73, 0.90, 0.96, 1.0);
	glShadeModel (GL_SMOOTH);
    glEnable(GL_NORMALIZE);

	texSet[0] = loadMyTextures("brick1.bmp");
	texSet[1] = loadMyTextures("brick2.bmp");
	texSet[2] = loadMyTextures("brick3.bmp");
	texSet[3] = loadMyTextures("brick4.bmp");
	texSet[4] = loadMyTextures("door1.bmp");
	texSet[5] = loadMyTextures("door2.bmp");
	texSet[6] = loadMyTextures("flower1.bmp");
	texSet[7] = loadMyTextures("flower2.bmp");
	texSet[8] = loadMyTextures("flower3.bmp");
	texSet[9] = loadMyTextures("grass1.bmp");

	texSet[10] = loadMyTextures("grass2.bmp");
	texSet[11] = loadMyTextures("leaves1.bmp");
	texSet[12] = loadMyTextures("leaves2.bmp");
	texSet[13] = loadMyTextures("roof1.bmp");
	texSet[14] = loadMyTextures("roof2.bmp");
	texSet[15] = loadMyTextures("roof3.bmp");
	texSet[16] = loadMyTextures("roof4.bmp");
	texSet[17] = loadMyTextures("roof5.bmp");
	texSet[18] = loadMyTextures("roof6.bmp");
	texSet[19] = loadMyTextures("stone1.bmp");

	texSet[20] = loadMyTextures("stone2.bmp");
	texSet[21] = loadMyTextures("tile1.bmp");
	texSet[22] = loadMyTextures("tile2.bmp");
	texSet[23] = loadMyTextures("tile3.bmp");
	texSet[24] = loadMyTextures("tile4.bmp");
	texSet[25] = loadMyTextures("tile5.bmp");
	texSet[26] = loadMyTextures("tile6.bmp");
	texSet[27] = loadMyTextures("window1.bmp");
	texSet[28] = loadMyTextures("window2.bmp");
	texSet[29] = loadMyTextures("window3.bmp");

	texSet[30] = loadMyTextures("window4.bmp");
	texSet[31] = loadMyTextures("window5.bmp");
	texSet[32] = loadMyTextures("window6.bmp");
	texSet[33] = loadMyTextures("wood1.bmp");
	texSet[34] = loadMyTextures("wood2.bmp");
	texSet[35] = loadMyTextures("wood3.bmp");
	texSet[36] = loadMyTextures("wood4.bmp");
	texSet[37] = loadMyTextures("wood5.bmp");
	texSet[38] = loadMyTextures("wood6.bmp");
	texSet[39] = loadMyTextures("wood7.bmp");

	texSet[40] = loadMyTextures("custom/custom1.bmp");
	texSet[41] = loadMyTextures("custom/custom2.bmp");
	texSet[42] = loadMyTextures("custom/custom3.bmp");
	texSet[43] = loadMyTextures("custom/custom4.bmp");
	texSet[44] = loadMyTextures("custom/custom5.bmp");
    texSet[44] = loadMyTextures("water0.bmp");


	cout << "Texture loading complete" << endl;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, 1.0, 1, 75);
	computeCameraPosition();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	aspectRatio = (float)w / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(80, aspectRatio, 1, 75);
	computeCameraPosition();

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(void)
{
	int startTime=glutGet(GLUT_ELAPSED_TIME);
	int counter = 1;
	
	glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL);
    glEnable(GL_DEPTH_TEST);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	drawMyHouse(texSet);
	
	int endTime=glutGet(GLUT_ELAPSED_TIME);
	// cout<<"Frame Rate: "<<(float)1000/(endTime-startTime)<<"\n";
	glFlush();
	glutSwapBuffers();

}

void mouse(int button, int state, int x, int y)
{

	if(!isDraggingLeft && button == GLUT_LEFT_BUTTON && state==GLUT_DOWN)
	{
		isDraggingLeft = true;
		isDraggingRight = false;
		prevX = x;
		prevY = y;
	}

	else if(button == GLUT_LEFT_BUTTON && state==GLUT_UP)
	{		
		isDraggingLeft = false;
		prevX = 0;
		prevY = 0;
	}

	if (!isDraggingRight && button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
	{
		isDraggingLeft = false;
		isDraggingRight = true;
		prevX = x;
		prevY = y;
	}

	else if (button == GLUT_RIGHT_BUTTON && state == GLUT_UP)
	{
		isDraggingRight = false;
		prevX = 0;
		prevY = 0;
	}

	if (button == GLUT_MIDDLE_BUTTON && state == GLUT_UP) {
		resetCamera();
		computeCameraPosition();
		glutPostRedisplay();
	}

}

void mouseMotion(int x, int y) {
	if (isDraggingLeft) {
		float dx = x - prevX;
		float dy = y - prevY;

		LMBDragged(dx, dy);
		computeCameraPosition();
		glutPostRedisplay();

		prevX = x;
		prevY = y;
	}

	if (isDraggingRight) {
		float dx = x - prevX;
		float dy = y - prevY;

		RMBDragged(dx, dy);
		computeCameraPosition();
		glutPostRedisplay();

		prevX = x;
		prevY = y;
	}
}

void keyboard(unsigned char key, int x, int y) {
	if (key == 'w' || key == 'W') {
		dist -= 1.0;
		computeCameraPosition();
		glutPostRedisplay();
	}

	if (key == 's' || key == 'S') {
		dist += 1.0;
		computeCameraPosition();
		glutPostRedisplay();
	}
	
	if (key == 27) {
		exit(0);
	}
}

int main(int argc, char **argv)
{
	cout << "CS3241 Lab 5\n\n";
	cout << "+++++CONTROLS+++++++\n\n";
	cout << "Left Click and Drag: Rotate camera\n";
	cout << "Right Click and Drag:\n";
	cout << "\tVertical: Change camera elevation\n";
	cout << "\tHorizontal: Zoom in and out\n";
	cout << "Middle Click: Reset camera\n";
	cout << "W: Zoom In\n";
	cout << "S: Zoom Out\n";
	cout <<"ESC: Quit\n";

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);

	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);	
	glutMouseFunc(mouse);
	glutMotionFunc(mouseMotion);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}

// ========================================================================

