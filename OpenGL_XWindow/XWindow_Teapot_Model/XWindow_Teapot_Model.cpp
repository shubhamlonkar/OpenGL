#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<memory.h>

#include<X11/Xlib.h>
#include<X11/Xutil.h>
#include<X11/XKBlib.h>
#include<X11/keysym.h>

#include<GL/gl.h>
#include<GL/glx.h>
#include<GL/glu.h>
#include<SOIL/SOIL.h>
#include"Model.h"

using namespace std;

bool gbFullScreen = false;
Display *gpDisplay = NULL;
XVisualInfo *gpXVisualInfo = NULL;
Colormap gColormap;
Window gWindow;
int giWindowWidth = 800;
int giWindowHeight = 600;

GLfloat rotateangle = 0.0f;

GLXContext gGLXContext;

GLuint giGlassTexture;

bool gbTexture = false;
bool gbLights = false;

GLfloat LightAmbient[] = {0.5f,0.5f,0.5f,1.0f};
GLfloat LightDiffuse[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat LightSpecular[] = {1.0f,1.0f,1.0f,1.0f};
GLfloat LightPosition[] = {0.0f,0.0f,2.0f,1.0f};
 
int main(void)
{

	void CreateWindow(void);
	void ToggleFullScreen(void);
	void resize(int,int);
	void initialize(void);
	void display(void);
	void uninitialize(void);
	void spin(void);

	int winWidth = giWindowWidth;
	int winHeight = giWindowHeight;

	bool bDone = false;

	CreateWindow();	

	initialize();
	
	XEvent event;
	KeySym keysym;

	while(bDone == false)
	{
		while(XPending(gpDisplay))
		{
			XNextEvent(gpDisplay,&event);
			switch(event.type)
			{
				case MapNotify:
					break;
				case KeyPress:
					keysym = XkbKeycodeToKeysym(gpDisplay,event.xkey.keycode,0,0);
					switch(keysym)
					{
						case XK_Escape:
								uninitialize();
								exit(0);
						case XK_F:
							case XK_f:
									if(gbFullScreen == false)
									{
										ToggleFullScreen();
										gbFullScreen = true;
									}
									else
									{
										ToggleFullScreen();
										gbFullScreen = false;
									}
									break;
						case XK_L:
							case XK_l:
									if(gbLights == false)
									{
										gbLights = true;
										glEnable(GL_LIGHTING);
									}
									else
									{
										gbLights = false;
										glDisable(GL_LIGHTING);
									}
									break;
						case XK_T:
							case XK_t:
									if(gbTexture == false)
									{
										gbTexture = true;
										glEnable(GL_TEXTURE_2D);
									}
									else
									{
										gbTexture = false;
										glDisable(GL_TEXTURE_2D);
									}
									break;
								default:
									break;
					}
					break;
				case ButtonPress:
					switch(event.xbutton.button)
						{
							case 1:
								break;
							case 2:
								break;
							case 3:
								break;
							default:
								break;

						}
					break;
				case MotionNotify:
					break;
				case ConfigureNotify:
						winWidth = event.xconfigure.width;
						winHeight = event.xconfigure.height;
						resize(winWidth,winHeight);
						break;
				case Expose:
					break;
				case DestroyNotify:
					break;
				case 33:
					bDone = true;
				default:
					break;
			}
		}
		display();
		spin();
	}
	uninitialize();
	return(0);

}

void CreateWindow(void)
{
	void uninitialize(void);

	XSetWindowAttributes winAttribs;	
	int defaultScreen;
	int styleMask;

	static int frameBufferAttributes[] = 
	{
			GLX_DOUBLEBUFFER, True,
			GLX_RGBA,
			GLX_RED_SIZE, 1,
			GLX_GREEN_SIZE, 1,
			GLX_BLUE_SIZE, 1,
			GLX_ALPHA_SIZE, 1,
			GLX_DEPTH_SIZE, 3,
			None
	};

	gpDisplay = XOpenDisplay(NULL);
	if(gpDisplay == NULL)
	{
		printf("ERROR: Unable To Open X Display.\n Exiting Now...\n");
		uninitialize();
		exit(1);
	}

	defaultScreen = XDefaultScreen(gpDisplay);

	gpXVisualInfo = glXChooseVisual(gpDisplay,defaultScreen,frameBufferAttributes);

	winAttribs.border_pixel = 0;
	winAttribs.background_pixmap = 0;
	winAttribs.colormap = XCreateColormap(gpDisplay,RootWindow(gpDisplay,gpXVisualInfo->screen),gpXVisualInfo->visual,AllocNone);
	
	gColormap = winAttribs.colormap;

	winAttribs.background_pixel = BlackPixel(gpDisplay,defaultScreen);
	winAttribs.event_mask = ExposureMask | VisibilityChangeMask | ButtonPressMask | KeyPressMask | PointerMotionMask | 			StructureNotifyMask;

	styleMask = CWBorderPixel | CWBackPixel | CWEventMask | CWColormap;
	
	gWindow = XCreateWindow(gpDisplay,
				RootWindow(gpDisplay,gpXVisualInfo->screen),
				0,
				0,
				giWindowWidth,
				giWindowHeight,
				0,
				gpXVisualInfo->depth,
				InputOutput,
				gpXVisualInfo->visual,
				styleMask,
				&winAttribs);
	if(!gWindow)
	{
		printf("ERROR:Failed To Create Main Window.\nExitting Now...\n");
		uninitialize();
		exit(1);

	}
	
	XStoreName(gpDisplay,gWindow,"Teapot Model");

	Atom windowManagerDelete = XInternAtom(gpDisplay,"WM_DELETE_WINDOW",True);
	XSetWMProtocols(gpDisplay,gWindow,&windowManagerDelete,1);

	XMapWindow(gpDisplay,gWindow);
		
}

void ToggleFullScreen(void)
{
	Atom wm_state;
	Atom fullscreen;
	XEvent xev = {0};

	wm_state=XInternAtom(gpDisplay,"_NET_WM_STATE",False);
	
	memset(&xev,0,sizeof(xev));

	xev.type = ClientMessage;
	xev.xclient.window = gWindow;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = gbFullScreen ? 0 : 1;

	fullscreen = XInternAtom(gpDisplay,"_NET_WM_STATE_FULLSCREEN",False);
	xev.xclient.data.l[1] = fullscreen;

	XSendEvent(gpDisplay,
		  RootWindow(gpDisplay,gpXVisualInfo->screen),
		  False,
		  StructureNotifyMask,
		  &xev);

}

void initialize(void)
{
	void resize(int,int);

	gGLXContext = glXCreateContext(gpDisplay,gpXVisualInfo,NULL,GL_TRUE);

	glXMakeCurrent(gpDisplay,gWindow,gGLXContext);

	glShadeModel(GL_SMOOTH);
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glLightfv(GL_LIGHT1, GL_AMBIENT, LightAmbient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, LightDiffuse);
	glLightfv(GL_LIGHT1, GL_POSITION, LightPosition);
	glEnable(GL_LIGHT1);

	giGlassTexture = SOIL_load_OGL_texture("Glass.bmp", SOIL_LOAD_AUTO, SOIL_CREATE_NEW_ID, SOIL_FLAG_MIPMAPS);
	glBindTexture(GL_TEXTURE_2D,giGlassTexture);

	resize(giWindowWidth,giWindowHeight);

}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(0.0f,0.0f,-1.5f);
	glRotatef(-90.0f,1.0f,0.0f,0.0f);
	glRotatef(rotateangle,0.0f,0.0f,1.0f);

	glBegin(GL_TRIANGLES);

	for(int i = 0; i < sizeof(face_indicies) / sizeof(face_indicies[0]); i++)
	{
			for(int j = 0;j < 3;j++)
			{
				int vi = face_indicies[i][j];
				int ni = face_indicies[i][j + 3];
				int ti = face_indicies[i][j + 6];

				glNormal3f(normals[ni][0],normals[ni][1],normals[ni][2]);
				glTexCoord2f(textures[ti][0],textures[ti][1]);
				glVertex3f(vertices[vi][0],vertices[vi][1],vertices[vi][2]);
			}

	}
	glEnd();
	
	glXSwapBuffers(gpDisplay,gWindow);

}


void resize(int width,int height)
{

	if(height == 0)
		height = 1;

	glViewport(0,0,(GLsizei)width,(GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,(GLfloat)width / (GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();


}

void uninitialize(void)
{
	GLXContext currentGLXContext;
	currentGLXContext = glXGetCurrentContext(); 

	if(currentGLXContext != NULL && currentGLXContext == gGLXContext)
	{
		glXMakeCurrent(gpDisplay,0,0);

	}

	if(gGLXContext)
	{

		glXDestroyContext(gpDisplay,gGLXContext);

	}

	if(gWindow)
	{
		XDestroyWindow(gpDisplay,gWindow);
	}

	if(gColormap)
	{
		XFreeColormap(gpDisplay,gColormap);
	}

	if(gpXVisualInfo)
	{
		free(gpXVisualInfo);
		gpXVisualInfo = NULL;
	}
	
	if(gpDisplay)
	{
		XCloseDisplay(gpDisplay);
		gpDisplay = NULL;	

	}
}

void spin(void)
{
	rotateangle = rotateangle + 1.0f;
	if(rotateangle >= 360.0f)
		rotateangle = rotateangle - 360.0f;
	

}
	
