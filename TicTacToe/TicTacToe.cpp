#include<Windows.h>
#include"TicTacToe.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int iCmdShow)
{
	WNDCLASSEX wndclass;
	TCHAR szAppName[] = TEXT("TIC_TAC_TOE");
	HWND hwnd;
	MSG msg;

	wndclass.cbClsExtra = 0;
	wndclass.cbSize = sizeof(wndclass);
	wndclass.cbWndExtra = 0;
	wndclass.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
//	wndclass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));
//	wndclass.hIconSm = LoadIcon(hInstance, MAKEINTRESOURCE(MY_ICON));
	wndclass.hIcon = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hIconSm = LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hInstance = hInstance;
	wndclass.lpfnWndProc = WndProc;
	wndclass.lpszClassName = szAppName;
	wndclass.lpszMenuName = NULL;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wndclass))
	{
		MessageBox(NULL, TEXT("Class Registration Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
		return 0;
	}

	hwnd = CreateWindow(szAppName, TEXT("TicTacToe"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, SW_HIDE);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return((int)msg.wParam);
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	switch (iMsg)
	{
	case WM_CREATE:
		if (DialogBox((HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE), MAKEINTRESOURCE(TICTACTOE), hwnd, (DLGPROC)MyDlgProc) == PB_CLOSE)
		{
			DestroyWindow(hwnd);
		}
		else
		{
			//MessageBox(hwnd, TEXT("Dialog Box Creation Failed"), TEXT("ERROR"), MB_OK | MB_ICONERROR);
			//DestroyWindow(hwnd);
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return(DefWindowProc(hwnd, iMsg, wParam, lParam));
}

BOOL CALLBACK MyDlgProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	// declaration of variables
	static HBRUSH hBrush;
	static char str = 'X';
	
	
	// code
	switch (iMsg)
	{
#pragma region DEFAULT
	case WM_INITDIALOG:
		EnableWindow(GetDlgItem(hwnd, PB_1), TRUE);
		EnableWindow(GetDlgItem(hwnd, PB_2), TRUE);
		EnableWindow(GetDlgItem(hwnd, PB_3), TRUE);
		EnableWindow(GetDlgItem(hwnd, PB_4), TRUE);
		EnableWindow(GetDlgItem(hwnd, PB_5), TRUE);
		EnableWindow(GetDlgItem(hwnd, PB_6), TRUE);
		EnableWindow(GetDlgItem(hwnd, PB_7), TRUE);
		EnableWindow(GetDlgItem(hwnd, PB_8), TRUE);
		EnableWindow(GetDlgItem(hwnd, PB_9), TRUE);

		// clear all push buttons
		SetDlgItemText(hwnd, PB_1, TEXT(""));
		SetDlgItemText(hwnd, PB_2, TEXT(""));
		SetDlgItemText(hwnd, PB_3, TEXT(""));
		SetDlgItemText(hwnd, PB_4, TEXT(""));
		SetDlgItemText(hwnd, PB_5, TEXT(""));
		SetDlgItemText(hwnd, PB_6, TEXT(""));
		SetDlgItemText(hwnd, PB_7, TEXT(""));
		SetDlgItemText(hwnd, PB_8, TEXT(""));
		SetDlgItemText(hwnd, PB_9, TEXT(""));
		break;

	case WM_CTLCOLORDLG:
	case WM_CTLCOLORBTN:
	case WM_CTLCOLOREDIT:
	case WM_CTLCOLORLISTBOX:
	case WM_CTLCOLORSTATIC:
	case WM_CTLCOLORMSGBOX:
		//SetBkColor((HDC)wParam, RGB(255, 255, 255));
		//SetBkMode((HDC)wParam, RGB(0, 0, 0));
		//SetTextColor((HDC)wParam, RGB(64, 224, 208));
		SetBkMode((HDC)wParam, RGB(255, 255, 255));
		SetTextColor((HDC)wParam, RGB(0, 0, 128));

		hBrush = CreateSolidBrush(RGB(255, 255, 255));
		return (INT_PTR)hBrush;
		break;
#pragma endregion

	case WM_COMMAND:
#pragma region HIWORD
		switch (HIWORD(wParam))
		{
		case CTLCOLOR_DLG:
			return TRUE;

		case CTLCOLOR_EDIT:
			return TRUE;
		}
#pragma endregion

		switch (LOWORD(wParam))
		{
		
		case PB_1:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_1, TEXT("X"));
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_1, TEXT("O"));
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_1), FALSE);
			break;

		case PB_2:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_2, TEXT("X"));
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_2, TEXT("O"));
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_2), FALSE);
			break;

		case PB_3:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_3, TEXT("X"));
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_3, TEXT("O"));
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_3), FALSE);
			break;

		case PB_4:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_4, TEXT("X"));
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_4, TEXT("O"));
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_4), FALSE);
			break;

		case PB_5:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_5, TEXT("X"));
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_5, TEXT("O"));
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_5), FALSE);
			break;

		case PB_6:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_6, TEXT("X"));
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_6, TEXT("O"));
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_6), FALSE);
			break;

		case PB_7:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_7, TEXT("X"));
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_7, TEXT("O"));
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_7), FALSE);
			break;

		case PB_8:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_8, TEXT("X"));
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_8, TEXT("O"));
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_8), FALSE);
			break;

		case PB_9:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_9, TEXT("X"));
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_9, TEXT("O"));
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_9), FALSE);
			break;

#pragma region RESETCLOSE
		case PB_RESET:
			// enable all push buttons
			EnableWindow(GetDlgItem(hwnd, PB_1), TRUE);
			EnableWindow(GetDlgItem(hwnd, PB_2), TRUE);
			EnableWindow(GetDlgItem(hwnd, PB_3), TRUE);
			EnableWindow(GetDlgItem(hwnd, PB_4), TRUE);
			EnableWindow(GetDlgItem(hwnd, PB_5), TRUE);
			EnableWindow(GetDlgItem(hwnd, PB_6), TRUE);
			EnableWindow(GetDlgItem(hwnd, PB_7), TRUE);
			EnableWindow(GetDlgItem(hwnd, PB_8), TRUE);
			EnableWindow(GetDlgItem(hwnd, PB_9), TRUE);
			
			// clear all push buttons
			SetDlgItemText(hwnd, PB_1, TEXT(""));
			SetDlgItemText(hwnd, PB_2, TEXT(""));
			SetDlgItemText(hwnd, PB_3, TEXT(""));
			SetDlgItemText(hwnd, PB_4, TEXT(""));
			SetDlgItemText(hwnd, PB_5, TEXT(""));
			SetDlgItemText(hwnd, PB_6, TEXT(""));
			SetDlgItemText(hwnd, PB_7, TEXT(""));
			SetDlgItemText(hwnd, PB_8, TEXT(""));
			SetDlgItemText(hwnd, PB_9, TEXT(""));
			
			break;
		case PB_CLOSE:
			EndDialog(hwnd, wParam);
			break;
#pragma endregion

		}
	}
	return FALSE;
}
