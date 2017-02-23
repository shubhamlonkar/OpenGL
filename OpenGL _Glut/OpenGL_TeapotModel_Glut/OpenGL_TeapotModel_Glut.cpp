#include<GL/freeglut.h>

#include"OGL.h"
#include"OpenGL_TeapotModel_Texture_Glut.h"

bool gbFullScreen = false;

GLfloat angle = 0.0f;

bool bLight = false;
bool bIsTextured = false;

GLfloat LightAmbient[] = { 0.5f,0.5f,0.5f,1.0f };
GLfloat LightDiffuse[] = { 1.0f,1.0f,1.0f,1.0f };
GLfloat LightPosition[] = {0.0f,0.0f,2.0f,1.0f};

GLuint Texture_Glass;

int main(int argc, char** argv)
{
	void initialize();
	void display(void);
	void resize(int, int);
	void keyboard(unsigned char, int, int);
	void mouse(int, int, int, int);
	void spin(void);
	void uninitialize(void);

	glutInit(&argc, argv);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

	glutInitWindowSize(800, 600);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Model Teapot Glut");

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
	int  LoadGLTextures(GLuint *, TCHAR[]);

	//code
	glShadeModel(GL_SMOOTH);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);	//set background clearing color to black

	glClearDepth(1.0f);		//set-up depth buffer

	glEnable(GL_DEPTH_TEST);	//enable depth testing

	glDepthFunc(GL_LEQUAL);	//set really nice perspective calculations

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	LoadGLTextures(&Texture_Glass, MAKEINTRESOURCE(IDBITMAP_GLASS));
	glBindTexture(GL_TEXTURE_2D, Texture_Glass);

	//Lights
	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);	//setup ambient light
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);	//setup diffuse light
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition); // position the light
	glEnable(GL_LIGHT1);	//enable above configured LIGHT1
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Teapot
	glLoadIdentity();
	glTranslatef(0.0f, 0.0f, -1.5f);
	glRotatef(angle, 0.0f, 1.0f, 0.0f);
	glBegin(GL_TRIANGLES);
	for (int i = 0; i < sizeof(face_indicies) / sizeof(face_indicies[0]); i++)
	{
		for (int j = 0; j < 3; j++)
		{
			int vi = face_indicies[i][j];	//vertex index
			int ni = face_indicies[i][j + 3];	//Normal index
			int ti = face_indicies[i][j + 6];	//Texture index
			glNormal3f(normals[ni][0], normals[ni][1], normals[ni][2]);
			glTexCoord2f(textures[ti][0], textures[ti][1]);
			glVertex3f(vertices[vi][0], vertices[vi][1], vertices[vi][2]);
		}
	}
	glEnd();

	glutSwapBuffers();
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

int  LoadGLTextures(GLuint *texture, TCHAR ImageResourceId[])
{
	HBITMAP hBitmap;
	BITMAP bmp;
	int iStatus = FALSE;
	glGenTextures(1, texture);
	hBitmap = (HBITMAP)LoadImage(GetModuleHandle(NULL), ImageResourceId,IMAGE_BITMAP,0,0,LR_CREATEDIBSECTION );
	if (hBitmap)
	{
		iStatus = TRUE;
		GetObject(hBitmap, sizeof(bmp), &bmp);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 4);
		glBindTexture(GL_TEXTURE_2D, *texture);
		glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		gluBuild2DMipmaps(GL_TEXTURE_2D, 3, bmp.bmWidth, bmp.bmHeight, GL_BGR_EXT, GL_UNSIGNED_BYTE,bmp.bmBits);

		DeleteObject(hBitmap);
	}
	return(iStatus);
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
	case 'L':
		case 'l':
			if (bLight == false)
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
	case 'T':
		case 't':
			if (bIsTextured == false)
			{
				bIsTextured = true;
				glEnable(GL_TEXTURE_2D);
			}
			else
			{
				bIsTextured = false;
				glDisable(GL_TEXTURE_2D);
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
	angle = angle + 0.5f;
	if (angle >= 360.0f)
		angle = angle - 360.0f;

	glutPostRedisplay();
}
void uninitialize(void)
{
		//NULL;
}