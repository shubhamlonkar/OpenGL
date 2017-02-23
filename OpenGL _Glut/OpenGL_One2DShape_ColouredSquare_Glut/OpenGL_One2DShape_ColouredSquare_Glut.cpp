#include<GL/freeglut.h>

bool gbFullScreen = false;

int main(int argc,char** argv)
{
	//function prototype
	void initialize(void);
	void display(void);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void resize(int, int);
	void uninitialize(void);



	//code
	glutInit(&argc, argv);

	glutInitWindowSize(800, 600);		//declare initial window size
		
	glutInitWindowPosition(100, 100);	//declare intial window position

	glutCreateWindow("One 2D Shape:Coloured Square");

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
	//to clear background 
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	//black

}
void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -3.0f);
	glBegin(GL_QUADS);
		glColor3f(1.0f, 0.0f, 0.0f);

		//square
		glVertex3f(1.0f, 1.0f, 0.0f);	//right-top of square
		glVertex3f(-1.0f, 1.0f, 0.0f);	//left-top of sqaure
		glVertex3f(-1.0f, -1.0f, 0.0f);	//left-bottom of square
		glVertex3f(1.0f, -1.0f, 0.0f); //right-bottom of square

	glEnd();

	glFlush();

}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 27: //Escape
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

	gluPerspective(45.0f, (GLfloat)width / (GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void uninitialize(void)
{
	//NULL

}