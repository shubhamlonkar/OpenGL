#include <GL/freeglut.h>

#include "OpenGL_Lights_Glut.h"


bool gbFullScreen = false;

GLfloat angleTri = 0.0f;
GLfloat angleSquare = 0.0f;

//Lights
bool bLight = false;
GLfloat LightAmbient[] = { 0.5f,0.5f,0.5f,1.0f };
GLfloat LightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat LightPosition[] = { 0.0f,0.0f,2.0f,1.0f };

GLuint Texture_Kundali;		//texture object for Kundali texture
GLuint Texture_Stone;		//texture object for Stone texture

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

	glutCreateWindow("Lights on Textured Pyramid And Cube");

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
	//function declarations
	int LoadGLTextures(GLuint *, TCHAR[]);

	glShadeModel(GL_SMOOTH);	//set background clearing color to black

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	//set-up depth buffer

	glClearDepth(1.0f);		//enable depth testing

	glEnable(GL_DEPTH_TEST);		//depth test to do

	glDepthFunc(GL_LEQUAL);	//set really nice perspective calculations

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	LoadGLTextures(&Texture_Kundali, MAKEINTRESOURCE(IDBITMAP_KUNDALI));
	LoadGLTextures(&Texture_Stone, MAKEINTRESOURCE(IDBITMAP_STONE));

	glEnable(GL_TEXTURE_2D);

	//Lights
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);		//setup ambient light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);		//setup diffuse light
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);	//position the light
	glEnable(GL_LIGHT1);	//enable above configured LIGHT1
}

int LoadGLTextures(GLuint *texture, TCHAR ImageResourceId[])
{
	HBITMAP hBitmap;
	BITMAP bmp;
	int iStatus = -1;
	//code
	glGenTextures(1, texture);	// 1 image
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), ImageResourceId, IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION);
	if (hBitmap)			//if bitmap exists (hBitmap is not null)
	{
		iStatus = 0;
		GetObject(hBitmap, sizeof(bmp), &bmp);		//takes handle,demands empty structure of bitmap
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);		//pixel storage mode(word alignment/4 bytes)
		glBindTexture(GL_TEXTURE_2D, *texture);		//bind texture
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);	//generate mipmapped texture(3 bytes,width,height and data from bmp)
		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE, bmp.bmBits);

		DeleteObject(hBitmap);		//delete unwanted bitmap handle

	}
	return(iStatus);
}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//#####PYRAMID#######
	glLoadIdentity();
	glTranslatef(-1.5f, 0.0f, -6.0f);
	glRotatef(angleTri, 0.0f, 1.0f, 0.0f);
	glBindTexture(GL_TEXTURE_2D, Texture_Stone);
	glBegin(GL_TRIANGLES);

	//**********FRONT FACE **************
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);		//apex

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);		//left - bottom

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);		//right - bottom

	//******RIGHT FACE ************
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);		//apex

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);		//left - bottom

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);		//right - bottom

	//*****BACK FACE *******
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);		//apex

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);		//left - bottom

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);	//right - bottom

	//****LEFT FACE ********
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0.5f, 1.0f);
	glVertex3f(0.0f, 1.0f, 0.0f);		//apex

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);	//left - bottom

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);		//right - bottom

	glEnd();

	//###CUBE###
	glLoadIdentity();
	glTranslatef(1.5f, 0.0f, -6.0f);
	glScalef(0.75f, 0.75f, 0.75f);
	glRotatef(angleSquare, 1.0f, 1.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, Texture_Kundali);
	glBegin(GL_QUADS);

	//***TOP FACE****
	glNormal3f(0.0f, 1.0f, 0.0f);

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);	//right-top	of top face 

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);	//left-top  of top face

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);	//left-bottom  of top face

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);	//right-bottom of top face

	//***BOTTOM FACE****
	glNormal3f(0.0f, -1.0f, 0.0f);

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);		//right-top	of bottom face 

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);	//left-top  of bottom face

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);		//left-bottom  of bottom face

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);		//right-bottom of bottom face

	//***FRONT FACE****
	glNormal3f(0.0f, 0.0f, 1.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);		//right-top	of front face 

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);		//left-top  of front face

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);		//left-bottom  of front face

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);		//right-bottom of front face

	//***BACK FACE****
	glNormal3f(0.0f, 0.0f, -1.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, -1.0f, -1.0f);		//right-top	of back face 

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);		//left-top  of back face

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);	//left-bottom  of back face

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);		//right-bottom of back face

	//***LEFT FACE****
	glNormal3f(-1.0f, 0.0f, 0.0f);

	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, 1.0f);		//right-top	of left face 

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-1.0f, 1.0f, -1.0f);		//left-top  of left face

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, -1.0f);	//left-bottom  of left face

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-1.0f, -1.0f, 1.0f);		//right-bottom of left face

	//***RIGHT FACE****
	glNormal3f(1.0f, 0.0f, 0.0f);

	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(1.0f, 1.0f, -1.0f);		//right-top	of right face 

	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(1.0f, 1.0f, 1.0f);		//left-top  of right face

	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(1.0f, -1.0f, 1.0f);		//left-bottom  of right face

	glTexCoord2f(0.0f, 0.0f);
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
	case 'L':
	case 'l':if (bLight == false)
				{
					bLight = true;
					glEnable(GL_LIGHTING);
				}
			 else
				{
					bLight = false;
					glDisable(GL_LIGHTING);
				}
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