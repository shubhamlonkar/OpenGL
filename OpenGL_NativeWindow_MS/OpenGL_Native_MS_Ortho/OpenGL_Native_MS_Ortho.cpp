#include<windows.h>
#include<gl/GL.h>
#include<gl/glu.h>


#define WIN_WIDTH 800
#define WIN_HEIGHT 600

#pragma comment(lib,"opengl32.lib")
#pragma comment(lib,"glu32.lib")

//Prototype of callback function WndProc
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declaration
HWND ghwnd = NULL;
HDC ghdc = NULL;
HGLRC ghrc = NULL;

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };

bool gbFullScreen = false;
bool gbActiveWindow = false;
bool gbEscapeKeyIsPressed = false;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE FreeProcInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	//function prototype 
	void initialize(void);
	void uninitialize(void);
	
	//variable declaration
	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("OpenGL Fixed Function Pipeline By Native Windowing : 2D Triangle (Orthogonal)");
	bool bDone = false;
	//initializing members of struct WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);		
	wndclass.style = CS_HREDRAW | CS_VREDRAW |CS_OWNDC;
	wndclass.cbClsExtra = 0;	//info about class
	wndclass.cbWndExtra = 0;	//info about a window
	wndclass.hInstance = hInstance;		//handle of instance
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;

	//Registering Class
	RegisterClassEx(&wndclass);

	//Create Window
	hwnd = CreateWindowEx(WS_EX_APPWINDOW,
						  szClassName,
						  TEXT("OpenGL Fixed Function Pipeline by Native Windowing: 2D Triangle (Orthogonal)"),
						  WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_VISIBLE,
						  0,
						  0,
						 WIN_WIDTH,
						 WIN_HEIGHT,
						 NULL,
						 NULL,
						 hInstance,
				   		 NULL);

	ghwnd = hwnd;

	if (NULL == hwnd)
	{
		MessageBox(NULL, TEXT("Window is not created"), TEXT("Error....."), 0);
		exit(0);
	}

	initialize();

	ShowWindow(hwnd, SW_SHOW);
	SetForegroundWindow(hwnd);		//set window on foreground
	SetFocus(hwnd);					//set focus on your window
	

	//Message Loop
	while (bDone == false)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT)
				bDone = true;
			else
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{
			
			if (gbActiveWindow == true)
			{
				if (gbEscapeKeyIsPressed == true)
					bDone = true;
			}
		}
	}
	uninitialize();
	return((int)msg.wParam);

}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	//function prototype
	void ToggleFullScreen(void);
	void display(void);
	void resize(int, int);
	void uninitialize(void);
	switch (iMsg)
	{
	case WM_ACTIVATE:
		if (HIWORD(wParam) == 0)
			gbActiveWindow = true;
		else
			gbActiveWindow = false;
		break;
	case WM_PAINT:
		display();
		break;
	case WM_ERASEBKGND:
		return(0);
		break;
	case WM_SIZE:
		resize(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
			if (gbEscapeKeyIsPressed == false)
				gbEscapeKeyIsPressed = true;
			break;
		case 0x46:	//for 'f' or 'F'
			if (gbFullScreen == false)
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
		default:
			break;
		}
		break;
	case WM_LBUTTONDOWN:
		break;
	case WM_CLOSE:
		uninitialize();
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));


}

void ToggleFullScreen(void)
{
	MONITORINFO mi;
	if (gbFullScreen == false)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);	//get style of the window
		if (dwStyle & WS_OVERLAPPEDWINDOW)
		{

			mi = { sizeof(MONITORINFO) };
			if (GetWindowPlacement(ghwnd, &wpPrev) && GetMonitorInfo(MonitorFromWindow(ghwnd, MONITORINFOF_PRIMARY), &mi))
			{
				SetWindowLong(ghwnd, GWL_STYLE, dwStyle & ~WS_OVERLAPPEDWINDOW);
				SetWindowPos(ghwnd,
							HWND_TOP, 
							mi.rcMonitor.left, 
							mi.rcMonitor.top, 
							mi.rcMonitor.right - mi.rcMonitor.left, 
							mi.rcMonitor.bottom - mi.rcMonitor.top, 
							SWP_NOZORDER | SWP_FRAMECHANGED);

			}
		}
		ShowCursor(FALSE);

	}
	else
	{	//code
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, 
					 HWND_TOP, 
					0, 
					0, 
					0, 
					0, 
					SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);

	}

}

void initialize(void)
{

	void resize(int, int);
	//variable  declaration
	PIXELFORMATDESCRIPTOR pfd;		//Windows Structure Of frambuffer ,gives direction to create frame buffer
	int iPixelFormatIndex;
	//code
	ZeroMemory(&pfd, sizeof(PIXELFORMATDESCRIPTOR));

	//Initialization pf structure 'PIXELFORMATDESCRIPTOR'

	pfd.nSize = sizeof(PIXELFORMATDESCRIPTOR);
	pfd.nVersion = 1;
	pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;			//Why this statement PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER gives wrong output?
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cRedBits = 8;
	pfd.cGreenBits = 8;
	pfd.cBlueBits = 8;
	pfd.cAlphaBits = 8;
	pfd.cDepthBits = 32;

	ghdc = GetDC(ghwnd);

	iPixelFormatIndex = ChoosePixelFormat(ghdc, &pfd);
	if (iPixelFormatIndex == 0)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;

	}

	if (SetPixelFormat(ghdc, iPixelFormatIndex, &pfd) == false)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;

	}
	ghrc = wglCreateContext(ghdc);		//creating openGL context
	if (ghrc == NULL)
	{
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}
	if (wglMakeCurrent(ghdc, ghrc) == false)
	{
		wglDeleteContext(ghrc);
		ghrc = NULL;
		ReleaseDC(ghwnd, ghdc);
		ghdc = NULL;
	}

	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

	resize(WIN_WIDTH, WIN_HEIGHT);
}

void display(void)
{
	//code 
	glClear(GL_COLOR_BUFFER_BIT);

	//#########TRIANGLE##############
	glBegin(GL_TRIANGLES);
		
	//red:Color of triangle
	glColor3f(1.0f, 0.0f, 0.0f);

	//co-ordinates of a triangle

	glVertex3f(0.0f, 50.0f, 0.0f);		//apex of a triangle
	glVertex3f(-50.0f, -50.0f, 0.0f);	//left bottom of a triangle
	glVertex3f(50.0f, -50.0f, 0.0f);

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

	//glOrtho(left,right,bottom,top,near,far);
	if (width <= height)
		glOrtho(-100.0f, 100.0f, (-100.0f *(height / width)), (100.0f * (height / width)), -100.0f, 100.0f);
	//co-oerdinates written for glVertex3f() are relative to viewing volume of (-100.0f, 100.0f, (-100.0f *(height / width)),(100.0f * (height/width)),-100.0f,100.0f)

	else
		glOrtho(-100.0f, 100.0f, (-100.0f *(width / height)), (100.0f *(width / height)), -100.0f, 100.0f);
	//co-ordinates written for glVertex3f() are relative to viewing volume of glOrtho(-100.0f, 100.0f, (-100.0f *(width / height)),(100.0f *(width/height)),-100.0f,100.0f)

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}

void uninitialize(void)
{
	if (gbFullScreen == true)
	{
		dwStyle = GetWindowLong(ghwnd, GWL_STYLE);
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd, &wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
	}

	wglMakeCurrent(NULL, NULL);

	wglDeleteContext(ghrc);
	ghrc = NULL;

	ReleaseDC(ghwnd, ghdc);
	ghdc = NULL;

	DestroyWindow(ghwnd);
}