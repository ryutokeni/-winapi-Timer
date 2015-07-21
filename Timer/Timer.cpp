// Timer.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Timer.h"
#include <windows.h>
#include <windowsx.h>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <queue>
#include <strsafe.h>
#include <CommCtrl.h>
#include "resource.h"
#include <queue>
#pragma comment(lib, "comctl32.lib")
#pragma comment( lib, "user32.lib") 
#pragma comment( lib, "gdi32.lib")
using namespace std;

#define MAX_LOADSTRING 100

typedef struct newtime
{
	int h;
	int m;
	int s;
};

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name
HWND hDialog, hDialog1;
INT_PTR CALLBACK StyleDialogProc(HWND hDialog, UINT uMsg, WPARAM wParam, LPARAM lParam);
UINT h = 0, m = 0, s = 0, h1 = 0, m1 = 0, s1 = 0, hb, mb, sb;
queue<newtime> List;
HWND hHeure;
HWND hMinute;
HWND hSecond;
HWND hWnd;
HANDLE hTimer, hStopwatch, hBreak;
BOOL StopStopwatch = true, StopTimer = true;
DWORD thrid;
DWORD WINAPI StartTimer(LPVOID);
DWORD WINAPI StartStopwatch(LPVOID);
HFONT hFont = CreateFont(150, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
	OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	DEFAULT_PITCH | FF_DONTCARE, TEXT("Digital-7"));

HFONT hFont1 = CreateFont(50, 0, 0, 0, FW_DONTCARE, FALSE, FALSE, FALSE, ANSI_CHARSET,
	OUT_TT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY,
	DEFAULT_PITCH | FF_DONTCARE, TEXT("Digital-7"));

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_TIMER, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_TIMER));
	

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_TIMER));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_TIMER);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
  

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
// Function I made to get the size of the text
int GetTextSize(LPTSTR a0)
{
	for (int iLoopCounter = 0;; iLoopCounter++)
	{
		if (a0[iLoopCounter] == '\0')
			return iLoopCounter;
	}
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	MSG msg;
	PAINTSTRUCT ps;
	HDC hdc;
	TCHAR time[20], time1[20], timebreak[20];
	queue<newtime> ListTemp = List;
	int i;
	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		SelectObject(hdc, hFont);
		_stprintf_s(time, _T("%02d:%02d:%02d"), h, m, s);
		_stprintf_s(time1, _T("%02d:%02d:%02d"), h1, m1, s1);
		TextOut(hdc, 10, 10, time, GetTextSize(time));
		TextOut(hdc, 10, 150, time1, GetTextSize(time1));
		SelectObject(hdc, hFont1);
		i = 170;
		while (!ListTemp.empty())
		{
			_stprintf_s(timebreak, _T("%02d:%02d:%02d"), ListTemp.front().h, ListTemp.front().m, ListTemp.front().s);
			ListTemp.pop();
			TextOut(hdc, 550, i, timebreak, GetTextSize(timebreak));
			i += 50;
		}
		EndPaint(hWnd, &ps);
		break;
	/*case WM_TIMER:

		switch (wParam)
		{
		case IDT_TIMER1:
			if (h == 0 && m == 0 && s == 0)
			{
				KillTimer(hWnd, IDT_TIMER1);
				break;
			}
			Beep(750, 200);
			// process the 10-second timer 
			//MessageBox(hWnd, L"WTF", L"WTF", MB_OKCANCEL);
			if (s > 0)
				s--;
			else
			{
				s = 59;
				if (m > 0)
					m--;
				else
				{
					m = 59;
					if (h > 0)
						h--;
					else
						KillTimer(hWnd, IDT_TIMER1);
				}
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		}*/
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case ID_FILE_SETTIME:
			InitCommonControls();
			if (!IsWindow(hDialog))
			{
				hDialog = (HWND)DialogBox(hInst,
					MAKEINTRESOURCE(IDD_DIALOG1),
					hWnd,
					(DLGPROC)StyleDialogProc);
				ShowWindow(hDialog, SW_SHOW);
			}
			
			while (GetMessage(&msg, NULL, 0, 0))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_FILE_RESET:
			h = m = s = 0;
			//KillTimer(hWnd, IDT_TIMER1);
			StopTimer = true;
			CloseHandle(hTimer);
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_FILE_STOP:
			//KillTimer(hWnd, IDT_TIMER1);
			StopTimer = true;
			break;
		case ID_FILE_START:
			StopTimer = false;
			//SetTimer(hWnd, IDT_TIMER1, 1000, (TIMERPROC)NULL);   
			hTimer = CreateThread(NULL, 0, StartTimer, NULL, 0, &thrid);
			break;		
		case ID_STOPWATCH_BREAK:
			List.push({ h1, m1, s1 });
			break;
		case ID_STOPWATCH_RESET:
			h1 = m1 = s1 = 0;
			//KillTimer(hWnd, IDT_TIMER1);
			StopStopwatch = true;
			CloseHandle(hStopwatch);
			while (!List.empty())
				List.pop();
			InvalidateRect(hWnd, NULL, TRUE);
			break;
		case ID_STOPWATCH_STOP:
			//KillTimer(hWnd, IDT_TIMER1);
			StopStopwatch = true;
			break;
		case ID_STOPWATCH_START:
			StopStopwatch = false;
			//SetTimer(hWnd, IDT_TIMER1, 1000, (TIMERPROC)NULL);   
			hTimer = CreateThread(NULL, 0, StartStopwatch, NULL, 0, &thrid);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_DESTROY:		
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

UINT hTemp, mTemp, sTemp;
INT_PTR CALLBACK StyleDialogProc(HWND hDialog, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		hHeure = GetDlgItem(hDialog, IDC_COMBO1);
		hMinute = GetDlgItem(hDialog, IDC_COMBO2);
		hSecond = GetDlgItem(hDialog, IDC_COMBO3);
		TCHAR Size[20];
		hTemp = h;
		mTemp = m;
		sTemp = s;
		for (int Count = 0; Count < 101; Count++)
		{
			_stprintf_s(Size, _T("%d"), Count);
			SendMessage(hHeure, CB_INSERTSTRING, -1, (LPARAM)Size);
		}
		SendMessage(hHeure, CB_SETCURSEL, h, 0);
		for (int Count = 0; Count < 60; Count++)
		{
			_stprintf_s(Size, _T("%d"), Count);
			SendMessage(hMinute, CB_INSERTSTRING, -1, (LPARAM)Size);
		}
		SendMessage(hMinute, CB_SETCURSEL, m, 0);
		for (int Count = 0; Count < 60; Count++)
		{
			_stprintf_s(Size, _T("%d"), Count);
			SendMessage(hSecond, CB_INSERTSTRING, -1, (LPARAM)Size);
		}
		SendMessage(hSecond, CB_SETCURSEL, s, 0);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			h = hTemp;
			m = mTemp;
			s = sTemp;
			EndDialog(hDialog, wParam);
			PostQuitMessage(0);
			return TRUE;

		case IDCANCEL:
			EndDialog(hDialog, wParam);
			hDialog = NULL;
			PostQuitMessage(0);
			return TRUE;

		case IDC_COMBO1:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				hTemp = SendMessage(hHeure, CB_GETCURSEL, 0, 0);
				break;
			}
			break;
		case IDC_COMBO2:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				mTemp = SendMessage(hMinute, CB_GETCURSEL, 0, 0);
				break;
			}
			break;
		case IDC_COMBO3:
			switch (HIWORD(wParam))
			{
			case CBN_SELCHANGE:
				sTemp = SendMessage(hSecond, CB_GETCURSEL, 0, 0);
				break;
			}
			break;
		}
	}

	return FALSE;
}

DWORD WINAPI StartStopwatch(LPVOID)
{
	while (!StopStopwatch)
	{
		Beep(500, 200);
		// process the 10-second timer 
		//MessageBox(hWnd, L"WTF", L"WTF", MB_OKCANCEL);
		s1++;
		if (s1 == 60)
		{
			s1 = 0;
			m1++;
			if (m1 == 60)
			{
				m1 = 0;
				h1++;
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		Sleep(800);
	}
	return 0;
}

DWORD WINAPI StartTimer(LPVOID)
{
	while (!StopTimer)
	{
		if (h == 0 && m == 0 && s == 0)
		{
			CloseHandle(hTimer);
			break;
		}
		Beep(750, 200);
		// process the 10-second timer 
		//MessageBox(hWnd, L"WTF", L"WTF", MB_OKCANCEL);
		if (s > 0)
			s--;
		else
		{
			s = 59;
			if (m > 0)
				m--;
			else
			{
				m = 59;
				if (h > 0)
					h--;
				else
					CloseHandle(hTimer);
			}
		}
		InvalidateRect(hWnd, NULL, TRUE);
		Sleep(800);
	}
	return 0;
}
