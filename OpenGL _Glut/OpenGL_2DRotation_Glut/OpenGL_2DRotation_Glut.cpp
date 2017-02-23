#include<GL/freeglut.h>

bool gbFullScreen = false;

GLfloat angleTri = 0.0f;
GLfloat angleSquare = 0.0f;

int main(int argc, char** argv)
{
	//function prototype
	void initialize(void);
	void display(void);
	void resize(int, int);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void spin(void);
	void uninitialize(void);

	//code
	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("2D Rotation:Triangle And Square");

	initialize();

	glutDisplayFunc(display);
	glutReshapeFunc(resize);
	glutKeyboardFunc(keyboard);
	glutMouseFunc(mouse);
	glutIdleFunc(spin);
	glutCloseFunc(uninitialize);

	glutMainLoop();
}

void initialize(void)
{

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	//black
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	//####TRIANGLE######
	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f);

	glRotatef(angleTri, 0.0f, 1.0f, 0.0f);

	glBegin(GL_TRIANGLES);
		glColor3f(1.0f, 0.0f, 0.0f);		//red
		glVertex3f(0.0f, 1.0f, 0.0f);		//apex of a triangle

		glColor3f(0.0f, 1.0f, 0.0f);		//green
		glVertex3f(-1.0f, -1.0f, 0.0f);		//left-bottom

		glColor3f(0.0f, 0.0f, 1.0f);		//blue
		glVertex3f(1.0f, -1.0f, 0.0f);		//right-bottom
		
	glEnd();

	//#####SQUARE######
	glLoadIdentity();
	glTranslatef(1.5f, 0.0f, -6.0f);
	glRotatef(angleSquare, 1.0f, 0.0f, 0.0f);

	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);	//red
		glVertex3f(1.0f, 1.0f, 0.0f);	//right-top of square

		glColor3f(0.0f, 1.0f, 0.0f);	//green
		glVertex3f(-1.0f, 1.0f, 0.0f);	//left-top of square

		glColor3f(0.0f, 0.0f, 1.0f);	//blue
		glVertex3f(-1.0f, -1.0f, 0.0f);	//left-bottom of square

		glColor3f(1.0f, 1.0f, 1.0f);	//white
		glVertex3f(1.0f, -1.0f, 0.0f);	//right-bottom of square
	glEnd();

	glutSwapBuffers();	//proces buffered OpenGL Routines
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

void resize(int width, int height)
{
	if (height == 0)
		height = 1;
	glViewport(0, 0, (GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void spin(void)
{
	angleTri = angleTri + 0.05f;
	if (angleTri >= 360.0f)
		angleTri = angleTri - 360.0f;

	angleSquare = angleSquare + 0.05f;
	if (angleSquare >= 360.0f)
		angleSquare = angleSquare - 360.0f;

	glutPostRedisplay();

}

void uninitialize(void)
{
	//NULL
}
