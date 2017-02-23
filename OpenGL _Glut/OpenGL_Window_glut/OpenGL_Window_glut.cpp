#include<GL/freeglut.h>

//global variable declaration

bool gbFullScreen = false;	//variable to toggle for fullscreen

int main(int argc,char **argv)

{
		//function prototypes
		
	void initialize(void);
	void display(void);
	void resize(int, int);
	void keyboard(unsigned char,int,int);
	void mouse(int, int, int, int);
	void uninitialize(void);
		//glut code

	glutInit(&argc, argv);		//initialize global variable of freeglut

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);	//glut demands colour and buffer configuration of a Window

	glutInitWindowSize(800, 600);	//to declare initial window size
	
	glutInitWindowPosition(100, 100);	//to declare initial window position 

	glutCreateWindow("OpenGL First Window : Hello World !!!"); //open the window with "OpenGL First Window : Hello World" in the title bar

	initialize();		//initialize OpenGL
	glutDisplayFunc(display);	//callback function called by glut for display  
	glutReshapeFunc(resize);		//callback function
	glutKeyboardFunc(keyboard);		//callback function
	glutMouseFunc(mouse);
	glutCloseFunc(uninitialize);

	glutMainLoop();			//MessageLoop
	

}

void initialize(void)
{
	//code
	//to select clearing(background)clear
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f); //color is given by OpenGL
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);	//to clear all pixels i.e. repaint.Clear by color mentioned in initialize();

	glFlush();	//to process rendered OpenGL APIs

}

void resize(int width, int height)
{

	//NULL 
	//function is to resize the diagram or object inside the window.
	//Right now no code is needed becaues program is only for creating a window.
	//no diagram or object is created or drawn

}

void keyboard(unsigned char key, int x, int y) {

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

void mouse(int button, int state, int x ,int y) {

	//code
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