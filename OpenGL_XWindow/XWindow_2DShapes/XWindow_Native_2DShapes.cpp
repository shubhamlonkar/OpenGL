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

using namespace std;

//global variables
bool gbFullscreen = false;
Display *gpDisplay = NULL;
XVisualInfo *gpXVisualInfo = NULL;
Colormap gColormap;
Window gWindow;

int giWindowWidth = 800;
int giWindowHeight = 600;

GLXContext gGLXContext;

//main function
int main(void)
{
	void ToggleFullscreen(void);	
	void CreateWindow(void);
	void initialize(void);
	void uninitialize(void);
	void resize(int,int);
	void display(void);
	
	//message loop
	XEvent event;
	KeySym keysym;

	int winWidth = giWindowWidth;
	int winHeight = giWindowHeight;

	bool bIsDone = false;

	CreateWindow();

	initialize();

	while(bIsDone == false)
	{
		while(XPending(gpDisplay))
		{
			XNextEvent(gpDisplay,&event);
			switch(event.type)
			{
				case MapNotify:
					break;

				case KeyPress:
					keysym = XkbKeycodeToKeysym(gpDisplay, event.xkey.keycode, 0, 0);
					switch(keysym)
					{
						case XK_Escape:
							uninitialize();
							exit(0);
						
						case XK_F:
						     case XK_f:
								if(gbFullscreen == false)
								{
									ToggleFullscreen();
									gbFullscreen = true;

								}
								else
								{
									ToggleFullscreen();
									gbFullscreen = false;
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
					bIsDone = true;
				default:
					break;
			}
		}
			display();
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
		GLX_RGBA,
		GLX_RED_SIZE, 1,
		GLX_GREEN_SIZE, 1,
		GLX_BLUE_SIZE, 1,
		GLX_ALPHA_SIZE, 1,
		None
	};

	gpDisplay = XOpenDisplay(NULL);
	if(gpDisplay == NULL)
	{
		printf("Error: Unable to open X display. \nExitting Now.");
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
	winAttribs.event_mask= ExposureMask | VisibilityChangeMask | ButtonPressMask | KeyPressMask | PointerMotionMask |
StructureNotifyMask;
	
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
		printf("Error: Failed to create main window.\n Exiting now.\n");
		uninitialize();
		exit(1);
	}

	XStoreName(gpDisplay,gWindow,"2D Colored Shapes");

	Atom windowManagerDelete = XInternAtom(gpDisplay, "WM_DELETE_WINDOW",True);
	XSetWMProtocols(gpDisplay,gWindow,&windowManagerDelete,1);

	XMapWindow(gpDisplay,gWindow);
}

void ToggleFullscreen(void)
{
	Atom wm_state;
	Atom fullscreen;
	XEvent xev = {0};

	wm_state = XInternAtom(gpDisplay,"_NET_WM_STATE",False);

	memset(&xev, 0,sizeof(xev));

	xev.type = ClientMessage;
	xev.xclient.window = gWindow;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = gbFullscreen ? 0 : 1;
	
	fullscreen = XInternAtom(gpDisplay, "_NET_WM_STATE_FULLSCREEN",False);
	xev.xclient.data.l[1] = fullscreen;

	XSendEvent(gpDisplay,RootWindow(gpDisplay, gpXVisualInfo->screen),False,StructureNotifyMask, &xev);
}

void initialize(void)
{
	void resize(int,int);

	gGLXContext = glXCreateContext(gpDisplay, gpXVisualInfo,NULL, GL_TRUE);

	glXMakeCurrent(gpDisplay,gWindow,gGLXContext);

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	resize(giWindowWidth, giWindowHeight);

}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);

	glLoadIdentity();

	glTranslatef(-1.5f,0.0f,-6.0f);
	glBegin(GL_TRIANGLES);
		
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(0.0f,1.0f,0.0f);	//apex

		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f,0.0f);	//left-bottom

		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(1.0f,-1.0f,0.0f);	//right-bottom

	glEnd();

	glLoadIdentity();

	glTranslatef(1.5f,0.0f,-6.0f);
	glBegin(GL_QUADS);
	
		glColor3f(1.0f,0.0f,0.0f);
		glVertex3f(1.0f,1.0f,0.0f);	//right-top

		glColor3f(0.0f,1.0f,0.0f);
		glVertex3f(-1.0f,1.0f,0.0f);	//left-top

		glColor3f(0.0f,0.0f,1.0f);
		glVertex3f(-1.0f,-1.0f,0.0f);	//left-bottom

		glColor3f(1.0f,1.0f,0.0f);
		glVertex3f(1.0f,-1.0f,0.0f);	//right-bottom
	glEnd();

	glFlush();
}

void resize(int width,int height)
{
	if(height == 0)
		height = 1;
	glViewport(0,0,(GLsizei)width, (GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)width/(GLfloat)height, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);	
	glLoadIdentity();

}


void uninitialize(void)
{
	GLXContext currentGLXContext;
	currentGLXContext = glXGetCurrentContext();

	if(currentGLXContext != NULL && currentGLXContext == gGLXContext)
	{
	
		glXMakeCurrent(gpDisplay, 0, 0);

	}
	
	if(gGLXContext)
	{
		
		glXDestroyContext(gpDisplay, gGLXContext);

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

