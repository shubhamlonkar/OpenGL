#include<windows.h>

//Prototype Of WndProc() declared Globally

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);

//global variable declarations

DWORD dwStyle;
WINDOWPLACEMENT wpPrev = { sizeof(WINDOWPLACEMENT) };
bool gbFullScreen = false;
HWND ghwnd = NULL;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{

		//variable declaration

	WNDCLASSEX wndclass;
	HWND hwnd;
	MSG msg;
	TCHAR szClassName[] = TEXT("First Native Window");
	
	//code
	//initialzing members of struct WNDCLASSEX
	wndclass.cbSize = sizeof(WNDCLASSEX);
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.cbClsExtra = 0;	//info about class
	wndclass.cbWndExtra = 0;	//
	wndclass.hInstance = hInstance;		//handle of instance
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szClassName;
	wndclass.lpszMenuName = NULL;

	//Register Class
	RegisterClassEx(&wndclass);

	//CreateWindow
	hwnd = CreateWindow(szClassName,
						TEXT("First Native Window"),
						WS_OVERLAPPEDWINDOW,	
						CW_USEDEFAULT,	//x - coordinate
						CW_USEDEFAULT,	//y - coordinate
						CW_USEDEFAULT,	//width of a window
						CW_USEDEFAULT,	//height of a windo	w
						NULL,	//Parent Window handle (if a window is single i.e. no child,no parent then desktop become the parent).
						NULL,	//handle of menu
						hInstance,	//instance of a window
						NULL);	//extra information about a window
	if (NULL == hwnd)		//if handle is null then window is not created
	{
		MessageBox(NULL, TEXT("Window not Created"), TEXT("Error"), 0);
		exit(0);
	}

	ghwnd = hwnd;
		
	ShowWindow(hwnd, iCmdShow);	//to show the window
	UpdateWindow(hwnd);		//repaint the window

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
		//function prototype
	void ToggleFullScreen(void);

	//code
	switch (iMsg)
	{
	case WM_CREATE:
		break;
	case WM_KEYDOWN:
					switch (wParam)
						{	
							case VK_ESCAPE:
											DestroyWindow(hwnd);
									break;
							case 0x46: //for 'f' or 'F'
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
				SetWindowPos(ghwnd, HWND_TOP, mi.rcMonitor.left, mi.rcMonitor.top, mi.rcMonitor.right - mi.rcMonitor.left, mi.rcMonitor.bottom - mi.rcMonitor.top, SWP_NOZORDER | SWP_FRAMECHANGED);
			}
		}
		ShowCursor(FALSE);
	}
	else
	{
		SetWindowLong(ghwnd, GWL_STYLE, dwStyle | WS_OVERLAPPEDWINDOW);
		SetWindowPlacement(ghwnd,&wpPrev);
		SetWindowPos(ghwnd, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE | SWP_NOOWNERZORDER | SWP_NOZORDER | SWP_FRAMECHANGED);

		ShowCursor(TRUE);
	}


}