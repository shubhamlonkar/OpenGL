#include<GL/freeglut.h>

bool gbFullScreen = false;

int main(int argc, char** argv)
{
	//function prototypes
	void initialize(void);
	void display(void);
	void resize(int, int);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void uninitialize(void);

	//code
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("Two Coloured 2d Shapes : Triangle and Square");

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
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//####TRIANGLE######
	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);	//red:colour of apex of triangle
		glVertex3f(0.0f, 1.0f, 0.0f);	//apex of triangle

		glColor3f(0.0f, 1.0f, 0.0f);	//green:colour of left bottom of triangle
		glVertex3f(-1.0f,-1.0f,0.0f);	//left-bottom tip of triangle

		glColor3f(0.0f,0.0f,1.0f);		//blue:color of right bottom of triangle
		glVertex3f(1.0f, -1.0f, 0.0f);	//right-bottom tip of triangle

	glEnd();

	//####SQUARE#####

	glLoadIdentity();
	glTranslatef(1.5f, 0.0f, -6.0f);

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);	

		//square
		glColor3f(1.0f, 0.0f, 0.0f);
		glVertex3f(1.0f, 1.0f, 0.0f);//right-top of square
		
		glColor3f(0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f,1.0f,0.0f);	//left-top of square
		
		glColor3f(0.0f, 0.0f, 1.0f);
		glVertex3f(-1.0f, -1.0f, 0.0f);	 //left-bottom of square
		
		glColor3f(1.0f, 1.0f, 1.0f);
		glVertex3f(1.0f, -1.0f, 0.0f);	//right-bottom of square


	glEnd();

	glFlush();
}

void resize(int width, int height)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

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
