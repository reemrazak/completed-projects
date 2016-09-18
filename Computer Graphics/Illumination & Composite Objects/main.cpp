// CS3241Lab3.cpp : Defines the entry point for the console application.
//#include <cmath>
#include "math.h"
#include <iostream>
#include <fstream>

#ifdef _WIN32
	#include <Windows.h>
	#include "glut.h"
	#define M_PI 3.141592654
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>
#endif

// global variable

int drawAlienButterfly(int n, int first);

bool m_Smooth = false;
bool m_Highlight = false;
GLfloat angle = 0;   /* in degrees */
GLfloat angle2 = 0;   /* in degrees */
GLfloat zoom = 1.0;
int mouseButton = 0;
int moving, startx, starty;

static double rotation = 0.0;


#define NO_OBJECT 4;
int current_object = 0;

using namespace std;


void timer_function( int value)
{
    rotation = rotation + 1;
    glutPostRedisplay();
    glutTimerFunc( 200,timer_function , 0);
}

void setupLighting()
{
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);

	// Lights, material properties
    GLfloat	ambientProperties[]  = {0.7f, 0.7f, 0.7f, 1.0f};
	GLfloat	diffuseProperties[]  = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat	specularProperties[] = {1.0f, 1.0f, 1.0f, 1.0f};
	GLfloat lightPosition[] = {-100.0f,100.0f,100.0f,1.0f};
	
    glClearDepth( 1.0 );

    glLightfv( GL_LIGHT0, GL_AMBIENT, ambientProperties);
    glLightfv( GL_LIGHT0, GL_DIFFUSE, diffuseProperties);
	glLightfv( GL_LIGHT0, GL_SPECULAR, specularProperties);
	glLightfv( GL_LIGHT0, GL_POSITION, lightPosition);
	
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, 0.0);

	// Default : lighting
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);

}

void drawTorus(double outerRadius, double innerRadius)
{

    int numOfSlices = 15;
    int numOfRings = 30;
    int i;
    int j;
    double s1;
    double s2;
    double centreCos1;
    double centreCos2;
    double centreSin1;
    double centreSin2;
    
    double centreRadius = (innerRadius + outerRadius) / 2;
    double tubeRadius = outerRadius - centreRadius;
    
    float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    float mat_diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
    float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
    float no_shininess = 0.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    
    /*
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
     */
    if(m_Highlight)
    {
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat low_shininess[] = { 100.0 };
        glColorMaterial(GL_FRONT, GL_DIFFUSE);

        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);
        glEnable(GL_COLOR_MATERIAL);

        
        // your codes for highlight here
    } else {
        glColorMaterial(GL_FRONT, GL_DIFFUSE);
        glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
        glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
        glEnable(GL_COLOR_MATERIAL);

    }

    
    
    for(i = 0; i < numOfSlices; i++)
    {
        s1 = 1.0/numOfSlices * i;
        s2 = 1.0/numOfSlices * (i + 1);
        centreCos1 = cos(2 * M_PI * s1);
        centreSin1 = sin(2 * M_PI * s1);
        centreCos2 = cos(2 * M_PI * s2);
        centreSin2 = sin(2 * M_PI * s2);

        glColor3f(1.0f, 0.0f, 0.0f);
        glBegin(GL_QUAD_STRIP);

        
        for(j = 0; j <= numOfRings; j++)
        {
            double t = 1.0/numOfRings * j;
            double c = cos(2 * M_PI * t - M_PI);
            double s = sin(2 * M_PI * t - M_PI);
            double x1 = centreCos1 * (centreRadius + tubeRadius * c);
            double y1 = centreSin1 * (centreRadius + tubeRadius * c);
            double x2 = centreCos2 * (centreRadius + tubeRadius * c);
            double y2 = centreSin2 * (centreRadius + tubeRadius * c);
            double z = s * tubeRadius;
            
            glNormal3d(centreCos1 * c, centreSin1 * c, s);
            glVertex3d(x1, y1, z);
            if(m_Smooth)
            {
                glNormal3d(centreCos2 * c, centreSin2 * c, s);
            }
            glVertex3d(x2, y2, z);
            
        }
        
        glEnd();
        glDisable(GL_COLOR_MATERIAL);
    }
}

void drawSphere(double r)
{

	float no_mat[] = {0.0f, 0.0f, 0.0f, 1.0f};
    float mat_ambient[] = {0.3f, 0.3f, 0.3f, 1.0f};
    float mat_diffuse[] = {0.1f, 0.5f, 0.8f, 1.0f};
	float mat_emission[] = {0.3f, 0.2f, 0.2f, 0.0f};
	float no_shininess = 0.0f;
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);

    /*
     glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, whiteSpecularMaterial);
     glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, mShininess);
     */
	if(m_Highlight)
	{
        GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
        GLfloat low_shininess[] = { 50.0 };
        glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);

		// your codes for highlight here
	} else {
		glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
		glMaterialf(GL_FRONT, GL_SHININESS, no_shininess);
	}

	
    int i,j;
	int n = 20;
    for(i=0;i<n;i++)
		for(j=0;j<2*n;j++)
		if(m_Smooth)
		{
			glBegin(GL_POLYGON);

			    // the normal of each vertex is actaully its own coordinates normalized for a sphere

			    // your normal here
                glNormal3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
			    // your normal here
                glNormal3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
			    // your normal here
                glNormal3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
			    // your normal here
                glNormal3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
 			glEnd();
		} else	{
			glBegin(GL_POLYGON);
			    // Explanation: the normal of the whole polygon is the coordinate of the center of the polygon for a sphere
			    glNormal3d(sin((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),cos((i+0.5)*M_PI/n)*cos((j+0.5)*M_PI/n),sin((j+0.5)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos(j*M_PI/n),r*cos(i*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos(j*M_PI/n),r*cos((i+1)*M_PI/n)*cos(j*M_PI/n),r*sin(j*M_PI/n));
				glVertex3d(r*sin((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*cos((i+1)*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
				glVertex3d(r*sin(i*M_PI/n)*cos((j+1)*M_PI/n),r*cos(i*M_PI/n)*cos((j+1)*M_PI/n),r*sin((j+1)*M_PI/n));
 			glEnd();
		}

}


void drawBranch(int n, int first)
{
    float distance = 1;
    bool rotations[] = {1, 0, 1};
    glPushMatrix();
    
    for(int i = 0; i < 3; i++)
    {
        glTranslatef(distance, 0, 0);
        glRotatef(10, rotations[0], rotations[1], rotations[2]);
        rotations[0] = !rotations[0];
        rotations[2] = !rotations[2];
        drawTorus(.6, .5);
        
        
        
        
    }

}


int drawAlienButterfly(int n, int first)
{
    
    if(n <= 0)
    {
        return 0;
    }
    if(n == first)
    {
        glRotatef(90, 1, 0, 0);
        glScalef(.1, .1, .1);
    }
    
    glPushMatrix();
        drawTorus(.6, .5);
        glPushMatrix();
            glRotatef(90, 1, 0, 0);
            drawTorus(.6, .5);
            glRotatef(90, 0, 1, 0);
            drawTorus(.6, .5);
        glPopMatrix();
        drawSphere(.5);
    
    drawBranch(n, first);
    drawAlienButterfly(n -1, first);
    glPopMatrix();


    glRotatef(90, 0, 0, 1);
    drawBranch(n, first);
    glRotatef(270, 0, 0, 1);

    drawAlienButterfly(n -4, first);
    glPopMatrix();




    
    glPopMatrix();
    
    return 1;
    
}

void drawTower(double torusRadius, double unitSphereRadius, int towerHeight)
{
    int i;
    
    
    glPushMatrix();
    
    glTranslatef(torusRadius, 0, 0);
    glTranslatef(0, 0, unitSphereRadius);
    glScalef(0.5, 0.5, 0.5);
    
    drawSphere(unitSphereRadius);
    
    for(i = 0; i <towerHeight; i ++)
    {
        glTranslatef(0, 0, unitSphereRadius * 2);
        drawSphere(unitSphereRadius);
        
        
    }
    
    
    
    glPopMatrix();
    
}

int drawLayer(double unitSphereRadius, int towerHeight, bool endTorus)
{
    int i;
    int interval = 45;
    double torusOuterRadius = 0.6;
    double torusInnerRadius = 0.5;
    drawTorus(torusOuterRadius, torusInnerRadius);
    
    if(endTorus)
    {
        return 1;
    }
    
    glPushMatrix();
    
    for(i = 0; i < 360; i+=interval)
    {
        glRotatef(i, 0, 0, 1);
        drawTower((torusOuterRadius + torusInnerRadius)/2, unitSphereRadius, towerHeight);
        
    }
    
    glPopMatrix();
    
    return 1;

}

void drawComplexCylinder()
{
    double unitSphereRadius = .1;
    int towerHeight = 5;
    float torusDistance = (float)unitSphereRadius * ((float)towerHeight) + 2*(float)unitSphereRadius;
    
    glPushMatrix();
    
    glRotatef(rotation, 0, 1, 0);
    
    glRotatef(-90, 1, 0, 0);
    
    glPushMatrix();
    drawLayer(unitSphereRadius, towerHeight, false);
    
    glTranslatef(0, 0, torusDistance);
    drawLayer(unitSphereRadius, towerHeight, false);
    glTranslatef(0, 0, torusDistance);
    
    drawLayer(unitSphereRadius, towerHeight, true);
    glPopMatrix();
    
    glRotatef(180, 0, 1, 0);
    
    glPushMatrix();
    drawLayer(unitSphereRadius, towerHeight, false);
    
    glTranslatef(0, 0, torusDistance);
    drawLayer(unitSphereRadius, towerHeight, false);
    glTranslatef(0, 0, torusDistance);
    
    drawLayer(unitSphereRadius, towerHeight, true);
    glPopMatrix();

    
    glPopMatrix();
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix();
		glTranslatef(0, 0, -6);

	    glRotatef(angle2, 1.0, 0.0, 0.0);
		glRotatef(angle, 0.0, 1.0, 0.0);

		glScalef(zoom,zoom,zoom);

		switch (current_object) {
		case 0:
			drawSphere(1);
			break;
		case 1:
                drawTorus(0.5, 1.0/6);
			// draw your second primitive object here
			break;
		case 2:
                glPushMatrix();
                glRotatef(180, 0, 1, 0);
                drawAlienButterfly(8, 8);
                glPopMatrix();
                
                glPushMatrix();
                glRotatef(180, 1, 1, 1);
                drawAlienButterfly(8, 8);
                glPopMatrix();
                
			// draw your first composite object here
			break;
		case 3:
                drawComplexCylinder();
			// draw your second composite object here
			break;
		default:
			break;
		};
	glPopMatrix();
	glutSwapBuffers ();
}




void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
	case 'p':
	case 'P':
		glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
		break;			
	case 'w':
	case 'W':
		glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
		break;			
	case 'v':
	case 'V':
		glPolygonMode(GL_FRONT_AND_BACK,GL_POINT);
		break;			
	case 's':
	case 'S':
		m_Smooth = !m_Smooth;
		break;
	case 'h':
	case 'H':
		m_Highlight = !m_Highlight;
		break;

	case '1':
	case '2':
	case '3':
	case '4':
		current_object = key - '1';
		break;

	case 27:
		exit(0);
		break;
		
	default:
	break;
	}

	glutPostRedisplay();
}



void
mouse(int button, int state, int x, int y)
{
  if (state == GLUT_DOWN) {
	mouseButton = button;
    moving = 1;
    startx = x;
    starty = y;
  }
  if (state == GLUT_UP) {
	mouseButton = button;
    moving = 0;
  }
}

void motion(int x, int y)
{
  if (moving) {
	if(mouseButton==GLUT_LEFT_BUTTON)
	{
		angle = angle + (x - startx);
		angle2 = angle2 + (y - starty);
	}
	else zoom += ((y-starty)*0.001);
    startx = x;
    starty = y;
	glutPostRedisplay();
  }
  
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 3"<< endl<< endl;

	cout << "1-4: Draw different objects"<<endl;
	cout << "S: Toggle Smooth Shading"<<endl;
	cout << "H: Toggle Highlight"<<endl;
	cout << "W: Draw Wireframe"<<endl;
	cout << "P: Draw Polygon"<<endl;
	cout << "V: Draw Vertices"<<endl;
	cout << "ESC: Quit" <<endl<< endl;

	cout << "Left mouse click and drag: rotate the object"<<endl;
	cout << "Right mouse click and drag: zooming"<<endl;

	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow ("CS3241 Assignment 3");
	glClearColor (1.0,1.0,1.0, 1.0);
	glutDisplayFunc(display);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
	glutKeyboardFunc(keyboard);
	setupLighting();
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST); 
	glDepthMask(GL_TRUE);

    glMatrixMode(GL_PROJECTION);
    gluPerspective( /* field of view in degree */ 40.0,
  /* aspect ratio */ 1.0,
    /* Z near */ 1.0, /* Z far */ 80.0);
	glMatrixMode(GL_MODELVIEW);
    
    glutTimerFunc (1, timer_function,0);

	glutMainLoop();

	return 0;
}
