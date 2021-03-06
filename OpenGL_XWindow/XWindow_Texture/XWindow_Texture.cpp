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

using namespace std;

Display *gpDisplay = NULL;
XVisualInfo *gpXVisualInfo = NULL;
Colormap gcolormap;
Window gWindow;
bool gbFullscreen = false;
int giWindowWidth = 800;
int giWindowHeight= 600;

GLfloat angleTri = 0.0f;
GLfloat angleSquare = 0.0f;

GLXContext gGLXContext;

GLuint giStoneTexture;
GLuint giKundaliTexture;



int main(void)
{
	void ToggleFullscreen(void);
	void uninitialize(void);
	void CreateWindow(void);
	void initialize(void);
	void display(void);
	void resize(int,int);
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
					bDone = true;
					break;
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
	
	int defaultScreen;
	int styleMask;

	XSetWindowAttributes winAttribs;
	
	static int frameBufferAttributes[] = 
	{
		GLX_DOUBLEBUFFER , True,	
		GLX_RGBA,
		GLX_RED_SIZE,1,
		GLX_GREEN_SIZE,1,
		GLX_BLUE_SIZE,1,
		GLX_ALPHA_SIZE,1,
		GLX_DEPTH_SIZE, 3,
		None
	};

	gpDisplay = XOpenDisplay(NULL);
	if(gpDisplay == NULL)
	{
		printf("ERROR:Unable To Open X Display.\n Exitting Now...\n");
		uninitialize();
		exit(1);
	}

	defaultScreen = XDefaultScreen(gpDisplay);

	gpXVisualInfo = glXChooseVisual(gpDisplay,defaultScreen,frameBufferAttributes);

	winAttribs.border_pixel = 0;
	winAttribs.background_pixmap = 0;
	winAttribs.colormap = XCreateColormap(gpDisplay,
					      RootWindow(gpDisplay,gpXVisualInfo->screen),
					      gpXVisualInfo->visual,
					      AllocNone);
	gcolormap = winAttribs.colormap;
	
	winAttribs.background_pixel = BlackPixel(gpDisplay,defaultScreen);
	winAttribs.event_mask = ExposureMask | VisibilityChangeMask | ButtonPressMask | KeyPressMask | PointerMotionMask | StructureNotifyMask;

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
		printf("ERROR: Failed To Create Main Window.\nExitting Now...\n");
		uninitialize();
		exit(1);
	}

	XStoreName(gpDisplay,gWindow,"Texture");

	Atom windowManagerDelete = XInternAtom(gpDisplay,"WM_DELETE_WINDOW",True);
	XSetWMProtocols(gpDisplay,gWindow,&windowManagerDelete,1);

	XMapWindow(gpDisplay,gWindow);
}

void ToggleFullscreen(void)
{
	Atom wm_state;
	Atom fullscreen;
	XEvent xev = {0};

	wm_state = XInternAtom(gpDisplay,"_NET_WM_STATE",False);

	memset(&xev,0,sizeof(xev));

	xev.type = ClientMessage;
	xev.xclient.window = gWindow;
	xev.xclient.message_type = wm_state;
	xev.xclient.format = 32;
	xev.xclient.data.l[0] = gbFullscreen ? 0 : 1;
	
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
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);

	giStoneTexture = SOIL_load_OGL_texture("Stone.bmp", SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS);
	giKundaliTexture = SOIL_load_OGL_texture("Vijay_Kundali.bmp", SOIL_LOAD_AUTO,SOIL_CREATE_NEW_ID,SOIL_FLAG_MIPMAPS);

	glEnable(GL_TEXTURE_2D);

	resize(giWindowWidth,giWindowHeight);

	
}

void display(void)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glTranslatef(-1.5f,0.0f,-6.0f);
	glRotatef(angleTri,0.0f,1.0f,0.0f);
	glBindTexture(GL_TEXTURE_2D,giStoneTexture);

	//pyramid
	glBegin(GL_TRIANGLES);
		//Front Face
		glTexCoord2f(0.5f,1.0f);
		glVertex3f(0.0f,1.0f,0.0f);
	
		glTexCoord2f(0.0f,0.0f);
		glVertex3f(-1.0f,-1.0f,1.0f);
		
		glTexCoord2f(1.0f,0.0f);
		glVertex3f(1.0f,-1.0f,1.0f);
		
		//Right Face
		glTexCoord2f(0.5f,1.0f);
		glVertex3f(0.0f,1.0f,0.0f);

		glTexCoord2f(1.0f,0.0f);
		glVertex3f(1.0f,-1.0f,1.0f);

		glTexCoord2f(0.0f,0.0f);
		glVertex3f(1.0f,-1.0f,-1.0f);

		//Back Face
		glTexCoord2f(0.5f,1.0f);
		glVertex3f(0.0f,1.0f,0.0f);

		glTexCoord2f(1.0f,0.0f);
		glVertex3f(1.0f,-1.0f,-1.0f);

		glTexCoord2f(0.0f,0.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);

		//Left Face
		glTexCoord2f(0.5f,1.0f);
		glVertex3f(0.0f,1.0f,0.0f);

		glTexCoord2f(0.0f,0.0f);
		glVertex3f(-1.0f,-1.0f,-1.0f);

		glTexCoord2f(1.0f,0.0f);
		glVertex3f(-1.0f,-1.0f,1.0f);
		
		glEnd();

		
		//cube

		glLoadIdentity();
		glTranslatef(1.5f,0.0f,-6.0f);
		glScalef(0.75f,0.75f,0.75f);
		glRotatef(angleSquare,1.0f,1.0f,1.0f);
		glBindTexture(GL_TEXTURE_2D,giKundaliTexture);

		glBegin(GL_QUADS);
			//topface
			glTexCoord2f(0.0f,1.0f);
			glVertex3f(1.0f,1.0f,-1.0f);

			glTexCoord2f(0.0f,0.0f);
			glVertex3f(-1.0f,1.0f,-1.0f);

			glTexCoord2f(1.0f,0.0f);
			glVertex3f(-1.0f,1.0f,1.0f);

			glTexCoord2f(1.0f,1.0f);
			glVertex3f(1.0f,1.0f,1.0f);
		
			//bottom face
			glTexCoord2f(1.0f,1.0f);
			glVertex3f(1.0f,-1.0f,-1.0f);
			
			glTexCoord2f(0.0f,1.0f);
			glVertex3f(-1.0f,-1.0f,-1.0f);
		
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(-1.0f,-1.0f,1.0f);

			glTexCoord2f(1.0f,0.0f);
			glVertex3f(1.0f,-1.0f,1.0f);

			//front face
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(1.0f,1.0f,1.0f);

			glTexCoord2f(1.0f,0.0f);
			glVertex3f(-1.0f,1.0f,1.0f);
	
			glTexCoord2f(1.0f,1.0f);
			glVertex3f(-1.0f,-1.0f,1.0f);

			glTexCoord2f(0.0f,1.0f);
			glVertex3f(1.0f,-1.0f,1.0f);
		
		
			//back face
			glTexCoord2f(1.0f,0.0f);
			glVertex3f(1.0f,1.0f,-1.0f);

			glTexCoord2f(1.0f,1.0f);
			glVertex3f(-1.0f,1.0f,-1.0f);

			glTexCoord2f(0.0f,1.0f);
			glVertex3f(-1.0f,-1.0f,-1.0f);
		
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(1.0f,-1.0f,-1.0f);

			//left face
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(-1.0f, 1.0f, 1.0f);		
	
			glTexCoord2f(1.0f,0.0f);
			glVertex3f(-1.0f, 1.0f, -1.0f);		

			glTexCoord2f(1.0f,1.0f);
			glVertex3f(-1.0f, -1.0f, -1.0f);	
			
			glTexCoord2f(0.0f,1.0f);
			glVertex3f(-1.0f, -1.0f, 1.0f);	
		
		
			//right face
			glTexCoord2f(1.0f,0.0f);
			glVertex3f(1.0f, 1.0f, -1.0f);		

			glTexCoord2f(1.0f,1.0f);
			glVertex3f(1.0f, 1.0f, 1.0f);		
			
			glTexCoord2f(0.0f,1.0f);
			glVertex3f(1.0f, -1.0f, 1.0f);	
	
			glTexCoord2f(0.0f,0.0f);
			glVertex3f(1.0f, -1.0f, -1.0f);		

			glEnd();
				
			glXSwapBuffers(gpDisplay,gWindow);
		
}

void resize(int width,int height)	
{
	if(height == 0)
	{
		height = 1;
	}
	
	glViewport(0,0,(GLsizei)width,(GLsizei)height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f,(GLfloat)width/(GLfloat)height,0.1f,100.0f);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void spin(void)
{
	angleTri = angleTri + 0.5f;
		if(angleTri >= 360.0f)
			angleTri = angleTri - 360.0f;

	angleSquare = angleSquare + 0.5f;
		if(angleSquare >= 0.0)
			angleSquare = angleSquare - 360.0f;

}

void uninitialize(void)
{
	GLXContext ctx;
	ctx=glXGetCurrentContext();
	
	//OGL changes
	if(ctx!=NULL && ctx==gGLXContext)
	{
		glXMakeCurrent(gpDisplay,0,0);
	}
	
	if(ctx)
	{
		glXDestroyContext(gpDisplay,ctx);
	}
	
	
	if(gWindow)
	{
		XDestroyWindow(gpDisplay,gWindow);
	}
	
	if(gcolormap)
	{
		XFreeColormap(gpDisplay,gcolormap);
	}
	
	if(gpXVisualInfo)
	{
		free(gpXVisualInfo);
		gpXVisualInfo=NULL;
	}
	
	if(gpDisplay)
	{
		XCloseDisplay(gpDisplay);
		gpDisplay=NULL;
}

}
