#include<GL/freeglut.h>

//global variable declaration
bool gbFullScreen = false;

int main(int argc, char **argv) {

	//function prototypes
	void initialize(void);
	void display(void);
	void resize(int, int);
	void keyboard(unsigned char, int, int);
	void  mouse(int, int, int, int);
	void uninitialize(void);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(800, 600);	//to declare initial window size

	glutInitWindowPosition(100, 100);	//to declare initial window position

	glutCreateWindow("One 2D Shape : Triangle (Ortho)");	


	

	initialize();
	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);
	
	glutMainLoop();




}

void initialize(void)
{
	//to clear background color
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	

}

void display(void)
{
	//clear all pixels

	glClear(GL_COLOR_BUFFER_BIT);

	//######## TRIANGLE #########
	glBegin(GL_TRIANGLES);
		//red:Color of triangle
	glColor3f(1.0f, 0.0f, 0.0f);

	//co-ordinates of a triangle

	glVertex3f(0.0f, 50.0f, 0.0f);		//apex of a triangle
	glVertex3f(-50.0f, -50.0f, 0.0f);	//left bottom of a triangle
	glVertex3f(50.0f, -50.0f, 0.0f);

	glEnd();

	//to process buffered OpenGL Routines
	glFlush();


}
void resize(int width, int height)
{

	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glOrtho(left,right,bottom,top,near,far);
	if (width <= height)
		glOrtho(-100.0f, 100.0f, (-100.0f *(height / width)), (100.0f * (height / width)), -100.0f, 100.0f);
	//co-oerdinates written for glVertex3f() are relative to viewing volume of (-100.0f, 100.0f, (-100.0f *(height / width)),(100.0f * (height/width)),-100.0f,100.0f)

	else
		glOrtho(-100.0f, 100.0f, (-100.0f *(width / height)),(100.0f *(width/height)),-100.0f,100.0f);
	//co-ordinates written for glVertex3f() are relative to viewing volume of glOrtho(-100.0f, 100.0f, (-100.0f *(width / height)),(100.0f *(width/height)),-100.0f,100.0f)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27:	//Escape 
			glutLeaveMainLoop();
		break;
	case 'F':
		case 'f':
			if (gbFullScreen == false)
			{
				glutFullScreen();
				gbFullScreen = true;
			}
			else
			{
				glutLeaveFullScreen();
				gbFullScreen = false;
			}
			break;
		default:
			break;
	}


}

void mouse(int button, int state, int x, int y)
{
	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		break;
	default:
		break;
	}



}
void uninitialize(void)
{
	//NULL

}