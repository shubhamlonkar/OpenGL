#include<GL/freeglut.h>

bool gbFullScreen = false;

int main(int argc, char **argv)
{
		//function prototype
	void initialize(void);
	void display(void);
	void resize(int, int);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);
		//code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);		//requires color buffer configuration of a window

	glutInitWindowSize(800, 600);		// initial size of a window

	glutInitWindowPosition(100, 100);	//initial window position

	glutCreateWindow("One 2D Shape:Traingle(Perspective)"); //title bar

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

	//clear background 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	//black

}

void display(void)
{

	//clear all pixels
	glClear(GL_COLOR_BUFFER_BIT);

	//######TRIANGLE########
	glLoadIdentity();	//reset matrix to identity matrix
	glTranslatef(0.0f,0.0f,-3.0f);
	glBegin(GL_TRIANGLES);
		//red:color of triangle
		glColor3f(1.0f, 0.0f, 0.0f);
		//co-ordinates of triangle
		glVertex3f(0.0f, 1.0f, 0.0f);	//apex of triangle
		glVertex3f(-1.0f, -1.0f, 0.0f); //left-bottom tip of triangle
		glVertex3f(1.0f, -1.0f, 0.0f);	//right-bottom tip of triangle
	glEnd();
	
	//process buffered OpenGL Routines
	glFlush();

}

void resize(int width, int height)
{

	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);	//(field of view,aspect ratio,z-near,z-far);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();



}

void keyboard(unsigned char key, int x, int y)
{

	switch (key)
	{
	case 27://Escape
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

	//null

}