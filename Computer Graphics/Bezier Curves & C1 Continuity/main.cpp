// CS3241Lab4.cpp : Defines the entry point for the console application.
//#include <cmath>
#include "math.h"
#include <iostream>
#include <fstream>

/* Include header files depending on platform */
#ifdef _WIN32
	#include "glut.h"
	#define M_PI 3.14159
#elif __APPLE__
	#include <OpenGL/gl.h>
	#include <GLUT/GLUT.h>
#endif

#define MAXPTNO 1000
#define NLINESEGMENT 32
#define NOBJECTONCURVE 8

using namespace std;

// Global variables that you can use
struct Point {
	int x,y;
};

// Storage of control points
int nPt = 0;
Point ptList[MAXPTNO];
Point c1List[MAXPTNO];

// Display options
bool displayControlPoints = true;
bool displayControlLines = true;
bool displayTangentVectors = false;
bool displayObjects = false;
bool C1Continuity = false;

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

int randomColour() //range : [min, max)
{
    static bool first = true;
    if ( first )
    {
        srand(time(NULL)); //seeding for the first time only!
        first = false;
    }
    return 1 + rand() % (253);
}

void drawYinYang()
{
    float radius = 10;
    float innerRadius = radius/2;
    float smallestRadius = innerRadius/4;
    int colour1r = randomColour();
    int colour1g = randomColour();
    int colour1b = randomColour();
    int colour2r = randomColour();
    int colour2g = randomColour();
    int colour2b = randomColour();

    
    glColor3ub(colour1r, colour1g, colour1b);
    drawCircle(0, 180, radius, 270, GL_POLYGON);
    
    glColor3ub(colour2r, colour2g, colour2b);
    drawCircle(90, 270, radius, 0, GL_POLYGON);
    
    
    glTranslatef(0, innerRadius, 0);
    
    glColor3ub(colour1r, colour1g, colour1b);
    drawCircle(90, 270, innerRadius, 0, GL_POLYGON);
    
    glColor3ub(colour2r, colour2g, colour2b);
    drawCircle(0, 360, smallestRadius, 0, GL_POLYGON);
    
    glTranslatef(0, -radius, 0);
    
    glColor3ub(colour2r, colour2g, colour2b);
    drawCircle(0, 360, innerRadius, 0, GL_POLYGON);
    
    
    glColor3ub(colour1r, colour1g, colour1b);
    drawCircle(0, 360, smallestRadius, 0, GL_POLYGON);
}

void drawRightArrow()
{
	glColor3f(0,1,0);
	glBegin(GL_LINE_STRIP);
		glVertex2f(0,0);
		glVertex2f(100,0);
		glVertex2f(95,5);
		glVertex2f(100,0);
		glVertex2f(95,-5);
	glEnd();
}

int getPosition(int a, int b, float interval)
{
    int difference = b - a;
    
    return a + (difference * interval);
}

void drawCurve(Point points[], int Pt)
{
    double t = 0;
    double interval = 1.0/NLINESEGMENT;
    double x1;
    double y1;
    
    glBegin(GL_LINE_STRIP);
    glColor3f(0,0,0);


    while(t <= 1)
    {

       x1 = pow (1-t, 3) * points[0].x + 3 * t * pow (1-t, 2) * points[1].x +
        3 * pow (t, 2) * (1-t) * points[2].x + pow (t, 3) * points[3].x;
    
        y1 = pow (1-t, 3) * points[0].y + 3 * t * pow (1-t, 2) * points[1].y +
        3 * pow (t, 2) * (1-t) * points[2].y + pow (t, 3) * points[3].y;
        
        glVertex2d(x1, y1);
        
        
        
        t = t + interval;
        
        
    }
    glEnd();

}

int drawBezier()
{
    int i;
    
    Point points[4];
                      
    
    for(i = 0; i < nPt - 3; i += 3)
    {
        points[0] = ptList[i];
        points[1] = ptList[i + 1];
        points[2] = ptList[i + 2];
        points[3] = ptList[i + 3];
        
        if((i > 2) && (C1Continuity))
        {
            Point originalPoint = ptList[i - 1];
            points[1].x = (2 * ptList[i].x) - originalPoint.x;
            points[1].y = (2 * ptList[i].y) - originalPoint.y;
            c1List[i + 1] = points[1];
        }
        
        drawCurve(points, i);
        
    }
    
    
    return 1;
    
}

void drawTangents()
{
    
    glColor3f(0,1,0);
    //for every bezier curve
    for (int i = 3; i < nPt; i+=3)
    {
        //divide into number of objects per curve
        for (int n = 0; n < NOBJECTONCURVE; n++)
        {
            float t = (float)n/NOBJECTONCURVE;
            
            float x0 = ptList[i-3].x; // control point 1
            float x1 = ptList[i-2].x;       // control point 2
            float x2 = ptList[i-1].x;       //  control point 3
            float x3 = ptList[i].x;          //control point 4
            float y0 = ptList[i-3].y;
            float y1 = ptList[i-2].y;
            float y2 = ptList[i-1].y;
            float y3 = ptList[i].y;
 
            
            
            float x = pow(1.0 - t, 3) * x0 + 3 * t * pow(1.0 - t, 2) * x1 +
            3 * pow(t, 2) * (1.0 - t) * x2 + pow(t, 3) * x3;
            
            float y = pow(1.0-t, 3) * y0 + 3 * t * pow(1.0 - t, 2) * y1 +
            3 * pow(t, 2) * (1.0 - t) * y2 + pow(t, 3) * y3;
 
            

            
            float dx = 3 * pow((1 - t), 2) * (x1 - x0) + 6 * (1 - t) * t * (x2 - x1) +  3 * pow(t, 2) * (x3 - x2);
            float dy = 3 * pow((1 - t), 2) * (y1 - y0) + 6 * (1 - t) * t * (y2 - y1) +  3 * pow(t, 2) * (y3 - y2);
            

            double angle = atan2((double)dy, (double)dx);

            glPushMatrix();
            glTranslatef(x, y, 0);
            glRotatef(angle * 180 / M_PI, 0, 0, 1);
            
            if(displayTangentVectors)
            {
                drawRightArrow();
            }
            if(displayObjects)
            {
                drawYinYang();
            }
            
            glPopMatrix();
        }
    }
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glPushMatrix();
    if(C1Continuity)
    {
        int j = 0;
        for(int i = 3; i < nPt; i+=3)
        {
            c1List[j].x = (ptList[i].x - ptList[i - 1].x) + ptList[i].x;
            c1List[j].y = (ptList[i].x - ptList[i - 1].x) + ptList[i].y;
            j++;
        }
    }
    
	if(displayControlPoints)
	{
        int j = 0;
		glPointSize(5);
		glBegin(GL_POINTS);
		for(int i=0;i<nPt; i++)
		{
                if((C1Continuity) && (i % 3 == 1) && (i > 2))
                {
                    glColor3f(1,0,0);
                    glVertex2d(c1List[j].x, c1List[j].y);
                    glColor3f(160.0/256.0, 160.0/256.0, 160.0/256.0);
                    glVertex2d(ptList[i].x,ptList[i].y);
                    j++;

                }
                else
                {
                    glColor3f(0,0,0);
                    glVertex2d(ptList[i].x,ptList[i].y);
                }
		}
        
        
		glEnd();
		glPointSize(1);

	}

	if(displayControlLines)
	{
        int j = 0;
        
        glColor3f(0,1,0);
        glBegin(GL_LINE_STRIP);
        for(int i = 0; i < nPt; i++)
        {
            if((C1Continuity) && (i > 2) && (i % 3 == 1 ))
            {
                glVertex2f(c1List[j].x, c1List[j].y);
                j++;
            }
            else
            {
                glVertex2f(ptList[i].x, ptList[i].y);

            }
        }
        glEnd();

	}
    
    if((displayTangentVectors) || (displayObjects))
    {
        drawTangents();
    }
    
    drawBezier();


	glPopMatrix();

	glutSwapBuffers ();
}

void reshape (int w, int h)
{
	glViewport (0, 0, (GLsizei) w, (GLsizei) h);
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0,w,h,0);  
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	
}

void init(void)
{
	glClearColor (1.0,1.0,1.0, 1.0);
}

void readFile()
{

	std::ifstream file;
    file.open("savefile.txt");
	file >> nPt;

	if(nPt>MAXPTNO)
	{
		cout << "Error: File contains more than the maximum number of points." << endl;
		nPt = MAXPTNO;
	}

	for(int i=0;i<nPt;i++)
	{
		file >> ptList[i].x;
		file >> ptList[i].y;
	}
    file.close();// is not necessary because the destructor closes the open file by default
}

void writeFile()
{
	std::ofstream file;
    file.open("savefile.txt");
    file << nPt << endl;

	for(int i=0;i<nPt;i++)
	{
		file << ptList[i].x << " ";
		file << ptList[i].y << endl;
	}
   
    file.close();// is not necessary because the destructor closes the open file by default
}

void clearPoints()
{
    nPt = 0;
}

void keyboard (unsigned char key, int x, int y)
{
	switch (key) {
		case 'r':
		case 'R':
			readFile();
		break;

		case 'w':
		case 'W':
			writeFile();
		break;

		case 'T':
		case 't':
			displayTangentVectors = !displayTangentVectors;
		break;

		case 'o':
		case 'O':
			displayObjects = !displayObjects;
		break;

		case 'p':
		case 'P':
			displayControlPoints = !displayControlPoints;
		break;

		case 'L':
		case 'l':
			displayControlLines = !displayControlLines;
		break;

		case 'C':
		case 'c':
			C1Continuity = !C1Continuity;
		break;

		case 'e':
		case 'E':
			// Do something to erase all the control points added
            clearPoints();

		break;

		case 27:
			exit(0);
		break;

		default:
		break;
	}

	glutPostRedisplay();
}



void mouse(int button, int state, int x, int y)
{
	/*button: GLUT_LEFT_BUTTON, GLUT_MIDDLE_BUTTON, or GLUT_RIGHT_BUTTON */
	/*state: GLUT_UP or GLUT_DOWN */
	enum
	{
		MOUSE_LEFT_BUTTON = 0,
		MOUSE_MIDDLE_BUTTON = 1,
		MOUSE_RIGHT_BUTTON = 2,
		MOUSE_SCROLL_UP = 3,
		MOUSE_SCROLL_DOWN = 4
	};
	if((button == MOUSE_LEFT_BUTTON)&&(state == GLUT_UP))
	{
		if(nPt==MAXPTNO)
		{
			cout << "Error: Exceeded the maximum number of points." << endl;
			return;
		}
		ptList[nPt].x=x;
		ptList[nPt].y=y;
		nPt++;
	}
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	cout<<"CS3241 Lab 4"<< endl<< endl;
	cout << "Left mouse click: Add a control point"<<endl;
	cout << "ESC: Quit" <<endl;
	cout << "P: Toggle displaying control points" <<endl;
	cout << "L: Toggle displaying control lines" <<endl;
	cout << "E: Erase all points (Clear)" << endl;
	cout << "C: Toggle C1 continuity" <<endl;	
	cout << "T: Toggle displaying tangent vectors" <<endl;
	cout << "O: Toggle displaying objects" <<endl;
	cout << "R: Read in control points from \"savefile.txt\"" <<endl;
	cout << "W: Write control points to \"savefile.txt\"" <<endl;
	glutInit(&argc, argv);
	glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize (600, 600);
	glutInitWindowPosition (50, 50);
	glutCreateWindow ("CS3241 Assignment 4");
	init ();
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutKeyboardFunc(keyboard);
	glutMainLoop();

	return 0;
}
