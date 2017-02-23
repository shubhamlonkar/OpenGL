#include<GL/freeglut.h>

GLfloat angleTri = 0.0f;
GLfloat angleSquare = 0.0f;

bool gbFullScreen = false;

int main(int argc, char** argv)
{
	//function prototype
	void initialize(void);
	void display(void);
	void keyboard(unsigned char, int, int);
	void resize(int, int);
	void mouse(int, int, int, int);
	void spin(void);
	void uninitialize(void);

	//code
	glutInit(&argc, argv);
	
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);

	glutCreateWindow("3D Rotation: Pyramid and Cube");

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
	glShadeModel(GL_SMOOTH);	//set background clearing color to black

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	//set-up depth buffer

	glClearDepth(1.0f);		//enable depth testing

	glEnable(GL_DEPTH_TEST);		//depth test to do

	glDepthFunc(GL_LEQUAL);	//set really nice perspective calculations

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//#####PYRAMID#######
	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f);
	glRotatef(angleTri, 1.0f, 0.0f, 0.0f);

	glBegin(GL_TRIANGLES);

	//**********FRONT FACE **************
	glColor3f(1.0f, 0.0f, 0.0f);		//red
	glVertex3f(0.0f, 1.0f, 0.0f);		//apex

	glColor3f(0.0f, 1.0f, 0.0f);		//green
	glVertex3f(-1.0f, -1.0f, 1.0f);		//left - bottom

	glColor3f(0.0f, 0.0f, 1.0f);		//blue
	glVertex3f(1.0f, -1.0f, 1.0f);		//right - bottom

	//******RIGHT FACE ************
	glColor3f(1.0f, 0.0f, 0.0f);		//red
	glVertex3f(0.0f, 1.0f, 0.0f);		//apex

	glColor3f(0.0f, 1.0f, 0.0f);		//green
	glVertex3f(1.0f, -1.0f, 1.0f);		//left - bottom

	glColor3f(0.0f, 0.0f, 1.0f);		//blue
	glVertex3f(1.0f, -1.0f, -1.0f);		//right - bottom

	//*****BACK FACE *******
	glColor3f(1.0f, 0.0f, 0.0f);		//red
	glVertex3f(0.0f, 1.0f, 0.0f);		//apex

	glColor3f(0.0f, 1.0f, 0.0f);		//green
	glVertex3f(1.0f, -1.0f, -1.0f);		//left - bottom

	glColor3f(0.0f, 0.0f, 1.0f);		//blue
	glVertex3f(-1.0f, -1.0f, -1.0f);	//right - bottom

	//****LEFT FACE ********
	glColor3f(1.0f, 0.0f, 0.0f);		//red
	glVertex3f(0.0f, 1.0f, 0.0f);		//apex

	glColor3f(0.0f, 1.0f, 0.0f);		//green
	glVertex3f(-1.0f, -1.0f, -1.0f);	//left - bottom

	glColor3f(0.0f, 0.0f, 1.0f);		//blue
	glVertex3f(-1.0f, -1.0f, 1.0f);		//right - bottom

	//*******BASE 1 of PYRAMID**********		this base (square) is divided into two triangles 
	glColor3f(0.0f, 1.0f, 0.0f);		//green
	glVertex3f(1.0f, -1.0f, 1.0f);		//right 
	glVertex3f(-1.0f,-1.0f,1.0f);		//left
	glVertex3f(-1.0f, -1.0f, -1.0f);		//bottom

	//*******BASE 2 of PYRAMID**********		this base (square) is divided into two triangles 
	glColor3f(0.0f, 1.0f, 0.0f);		//green
	glVertex3f(1.0f, -1.0f, 1.0f);		//right 
	glVertex3f(-1.0f, -1.0f, -1.0f);	//left
	glVertex3f(1.0f, -1.0f, -1.0f);		//bottom
	glEnd();

	//###CUBE###
	glLoadIdentity();
	glTranslatef(1.5f, 0.0f, -6.0f);
	glScalef(0.75f, 0.75f, 0.75f);
	glRotatef(angleSquare,1.0f,1.0f,1.0f);

	glBegin(GL_QUADS);	
						
	//***TOP FACE****
	glColor3f(1.0f,0.0f,0.0f);		//red color of top face
 	glVertex3f(1.0f, 1.0f, -1.0f);	//right-top	of top face 
	glVertex3f(-1.0f, 1.0f, -1.0f);	//left-top  of top face
	glVertex3f(-1.0f, 1.0f, 1.0f);	//left-bottom  of top face
	glVertex3f(1.0f ,1.0f ,1.0f);	//right-bottom of top face

	//***BOTTOM FACE****
	glColor3f(0.0f, 1.0f, 0.0f);		//green color of bottom face
	glVertex3f(1.0f, -1.0f, -1.0f);		//right-top	of bottom face 
	glVertex3f(-1.0f, -1.0f, -1.0f);	//left-top  of bottom face
	glVertex3f(-1.0f, -1.0f, 1.0f);		//left-bottom  of bottom face
	glVertex3f(1.0f, -1.0f, 1.0f);		//right-bottom of bottom face

	//***FRONT FACE****
	glColor3f(0.0f, 0.0f, 1.0f);		//blue color of front face
	glVertex3f(1.0f, 1.0f, 1.0f);		//right-top	of front face 
	glVertex3f(-1.0f, 1.0f, 1.0f);		//left-top  of front face
	glVertex3f(-1.0f, -1.0f, 1.0f);		//left-bottom  of front face
	glVertex3f(1.0f, -1.0f, 1.0f);		//right-bottom of front face

	//***BACK FACE****
	glColor3f(1.0f, 1.0f, 0.0f);		//yellow color of back face
	glVertex3f(1.0f, 1.0f, -1.0f);		//right-top	of back face 
	glVertex3f(-1.0f, 1.0f, -1.0f);		//left-top  of back face
	glVertex3f(-1.0f, -1.0f, -1.0f);	//left-bottom  of back face
	glVertex3f(1.0f, -1.0f, -1.0f);		//right-bottom of back face

	//***LEFT FACE****
	glColor3f(0.0f, 1.0f, 1.0f);		//cyan color of left face
	glVertex3f(-1.0f, 1.0f, 1.0f);		//right-top	of left face 
	glVertex3f(-1.0f, 1.0f, -1.0f);		//left-top  of left face
	glVertex3f(-1.0f, -1.0f, -1.0f);	//left-bottom  of left face
	glVertex3f(-1.0f, -1.0f, 1.0f);		//right-bottom of left face

	//***RIGHT FACE****
	glColor3f(1.0f, 0.0f, 1.0f);		//cyan color of right face
	glVertex3f(1.0f, 1.0f, -1.0f);		//right-top	of right face 
	glVertex3f(1.0f, 1.0f, 1.0f);		//left-top  of right face
	glVertex3f(1.0f, -1.0f, 1.0f);		//left-bottom  of right face
	glVertex3f(1.0f, -1.0f, -1.0f);		//right-bottom of right face

	glEnd();

	glutSwapBuffers();	//process OpenGL Routines
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
		case'f':
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
	//NULL;

}