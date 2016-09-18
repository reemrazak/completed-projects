// CS3241Lab1.cpp : Defines the entry point for the console application.
#include <cmath>
#include <iostream>

/* Include header files depending on platform */
#ifdef _WIN32
	#include "glut.h"
	#define M_PI 3.14159
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>
#endif

using namespace std;

float alpha = 0.0, k=1;
float tx = 0.0, ty=0.0;

void drawSpiroGraph();

void drawCircle(float lowerBound, float upperBound, float radius, float offset, GLenum mode)
{
    float degree;
    float radian;
    float adjacent;
    float opposite;
    
    //resets to original reference frame
    //glLoadIdentity();
    
    
    glBegin(mode);
    
    for(degree = lowerBound; degree <= upperBound; degree++)
    {
        //radius = radius + .001;
        radian = (degree + offset) * M_PI /180;
        adjacent = cos(radian) * radius;
        opposite = sin(radian) * radius;
        glVertex2f(adjacent, opposite);
    }
    
    glEnd();
}

void drawLine(float ax, float ay, float bx, float by)
{
    glBegin(GL_LINES);
        glVertex2f(ax, ay);
        glVertex2f(bx, by);
    glEnd();
}

void drawFork(int n, float lineX, float lineY)
{
    drawLine(0, 0, lineX, lineY);
    if(n == 0)
    {
        return;
    }
    glPushMatrix();
        glTranslatef(0, lineY, 0);
        glPushMatrix();
            glRotatef(35,0,0,1);
            glScalef(0.7, 0.7, 0.7);
            drawFork(n-1, lineX, lineY);
        glPopMatrix();
        glPushMatrix();
            glRotatef(-80,0,0,1);
            glScalef(0.5,0.5,0.5);
            drawFork(n-1, lineX, lineY);
        glPopMatrix();
    
    glPopMatrix();
    
    
}

void drawYinYang()
{
    float radius = .25;
    float innerRadius = .125;
    float smallestRadius = .03;

    
    glColor3ub(0, 0, 0);
    drawCircle(0, 180, radius, 270, GL_POLYGON);
    glColor3ub(235, 230, 223);
    
    drawCircle(90, 270, radius, 0, GL_POLYGON);
    
    
    glTranslatef(0, .125, 0);
    
    glColor3ub(0, 0, 0);
    drawCircle(90, 270, innerRadius, 0, GL_POLYGON);
    
    glColor3ub(235, 230, 223);
    drawCircle(0, 360, smallestRadius, 0, GL_POLYGON);
    
    glTranslatef(0, -.25, 0);
    glColor3ub(235, 230, 223);
    drawCircle(0, 360, innerRadius, 0, GL_POLYGON);
    
    
    glColor3ub(0, 0, 0);
    
    drawCircle(0, 360, smallestRadius, 0, GL_POLYGON);
}
void display(void)
{

    float lineX = 0;
    float lineY = 0.1;
    int forkSize = 11;
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glPushMatrix();

	//controls transformation
	glScalef(k, k, k);	
	glTranslatef(tx, ty, 0);	
	glRotatef(alpha, 0, 0, 1);
	
    
    drawYinYang();
    /******Finished drawing Yin Yang********/

    glLineWidth(1.5);
    glColor3ub(235, 230, 223);
    
    glTranslatef(0, .1, 0);
    glRotatef(-35, 0, 0, 1);
    drawFork(forkSize, lineX, lineY);
    glRotatef(-30, 0, 0, 1);
    drawFork(forkSize, lineX, lineY);
    

    glColor3ub(0, 0, 0);
    
    glRotatef(-150, 0, 0, 1);
    glTranslatef(.04, -.04, 0);


    drawFork(forkSize, lineX, lineY);    glRotatef(-30, 0, 0, 1);
    drawFork(forkSize, lineX, lineY);
    
    /*glRotatef(40, 0, 0, 1);
    drawFork(forkSize, lineX, lineY);
    glRotatef(40, 0, 0, 1);
    drawFork(forkSize, lineX, lineY);
    glRotatef(40, 0, 0, 1);
    drawFork(forkSize, lineX, lineY);*/
    
    glColor3ub(86, 230, 119);


    
	glPopMatrix();
	glFlush ();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);

	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();

	glOrtho(-10, 10, -10, 10, -10, 10);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void init(void)
{
	glClearColor (1.0, 1.0, 1.0, 1.0);
	glShadeModel (GL_SMOOTH);
}



void keyboard (unsigned char key, int x, int y)
{
	//keys to control scaling - k
	//keys to control rotation - alpha
	//keys to control translation - tx, ty
	switch (key) {

		case 'a':
			alpha+=10;
			glutPostRedisplay();
		break;

		case 'd':
			alpha-=10;
			glutPostRedisplay();
		break;

		case 'q':
			k+=0.1;
			glutPostRedisplay();
		break;

		case 'e':
			if(k>0.1)
				k-=0.1;
			glutPostRedisplay();
		break;

		case 'z':
			tx-=0.1;
			glutPostRedisplay();
		break;

		case 'c':
			tx+=0.1;
			glutPostRedisplay();
		break;

		case 's':
			ty-=0.1;
			glutPostRedisplay();
		break;

		case 'w':
			ty+=0.1;
			glutPostRedisplay();
		break;
			
		case 27:
			exit(0);
		break;

		default:
		break;
	}
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 1\n\n";
	cout<<"+++++CONTROL BUTTONS+++++++\n\n";
	cout<<"Scale Up/Down: Q/E\n";
	cout<<"Rotate Clockwise/Counter-clockwise: A/D\n";
	cout<<"Move Up/Down: W/S\n";
	cout<<"Move Left/Right: Z/C\n";
	cout <<"ESC: Quit\n";

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow (argv[0]);
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	//glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
