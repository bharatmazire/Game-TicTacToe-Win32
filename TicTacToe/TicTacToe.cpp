#include<Windows.h>
#include"TicTacToe.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
BOOL    CALLBACK MyDlgProc(HWND, UINT, WPARAM, LPARAM);

bool iState[10];

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
	// declaration of function

	int CheckGame();
	void StopAll(HWND);
	
	// declaration of variables
	static HBRUSH hBrush;
	static char str = 'X';
	static short sCount = 0;
	iState[0] = 0;
	static int iWinner;
	//static bool bIsResultOut = 0;

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
				iState[1] = 1;
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_1, TEXT("O"));
				iState[1] = 0;
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_1), FALSE);
			//iState[1] = 1;
			if (++sCount > 4)
			{
				iWinner = CheckGame();
				if (iWinner)
				{
					StopAll(hwnd);
				}
			}
			break;

		case PB_2:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_2, TEXT("X"));
				iState[2] = 1;
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_2, TEXT("O"));
				iState[2] = 0;
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_2), FALSE);
			//iState[2] = 1;
			if (++sCount > 4)
			{
				iWinner = CheckGame();
				if (iWinner)
				{
					StopAll(hwnd);
				}
			}
			break;

		case PB_3:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_3, TEXT("X"));
				iState[3] = 1;
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_3, TEXT("O"));
				iState[3] = 0;
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_3), FALSE);
			//iState[3] = 1;
			if (++sCount > 4)
			{
				iWinner = CheckGame();
				if (iWinner)
				{
					StopAll(hwnd);
				}
			}
			break;

		case PB_4:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_4, TEXT("X"));
				iState[4] = 1;
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_4, TEXT("O"));
				iState[4] = 0;
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_4), FALSE);
			//iState[4] = 1;
			if (++sCount > 4)
			{
				iWinner = CheckGame();
				if (iWinner)
				{
					StopAll(hwnd);
				}
			}
			break;

		case PB_5:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_5, TEXT("X"));
				iState[5] = 1;
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_5, TEXT("O"));
				iState[5] = 0;
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_5), FALSE);
			//iState[5] = 1;
			if (++sCount > 4)
			{
				iWinner = CheckGame();
				if (iWinner)
				{
					StopAll(hwnd);
				}
			}
			break;

		case PB_6:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_6, TEXT("X"));
				iState[6] = 1;
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_6, TEXT("O"));
				iState[6] = 0;
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_6), FALSE);
			//iState[6] = 1;
			if (++sCount > 4)
			{
				iWinner = CheckGame();
				if (iWinner)
				{
					StopAll(hwnd);
				}
			}
			break;

		case PB_7:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_7, TEXT("X"));
				iState[7] = 1;
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_7, TEXT("O"));
				iState[7] = 0;
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_7), FALSE);
			//iState[7] = 1;
			if (++sCount > 4)
			{
				iWinner = CheckGame();
				if (iWinner)
				{
					StopAll(hwnd);
				}
			}
			break;

		case PB_8:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_8, TEXT("X"));
				iState[8] = 1;
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_8, TEXT("O"));
				iState[8] = 0;
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_8), FALSE);
			//iState[8] = 1;
			if (++sCount > 4)
			{
				iWinner = CheckGame();
				if (iWinner)
				{
					StopAll(hwnd);
				}
			}
			break;

		case PB_9:
			if (str == 'X')
			{
				SetDlgItemText(hwnd, PB_9, TEXT("X"));
				iState[9] = 1;
				str = 'O';
			}
			else
			{
				SetDlgItemText(hwnd, PB_9, TEXT("O"));
				iState[9] = 0;
				str = 'X';
			}
			EnableWindow(GetDlgItem(hwnd, PB_9), FALSE);
			//iState[9] = 1;
			if (++sCount > 4)
			{
				iWinner = CheckGame();
				if (iWinner)
				{
					StopAll(hwnd);
				}
			}
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
			//ResetAll(hwnd);
			
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
			SetDlgItemText(hwnd, LT_RESULT, TEXT(""));
			
			str = 'X';
			sCount = 0;
			iWinner = 0;
			for (int p = 0; p < 11; p++)
				iState[p] = 0;

			break;
		case PB_CLOSE:
			EndDialog(hwnd, wParam);
			break;
#pragma endregion

		}
#pragma region WINNER
		switch(iWinner)
		{
		case 1:
			if(iState[1] == 1)
				SetDlgItemText(hwnd, LT_RESULT, TEXT("X is WINNER!"));
			else
				SetDlgItemText(hwnd, LT_RESULT, TEXT("O is WINNER!"));
			break;
		case 2:
			if (iState[4] == 1)
				SetDlgItemText(hwnd, LT_RESULT, TEXT("X is WINNER!"));
			else
				SetDlgItemText(hwnd, LT_RESULT, TEXT("O is WINNER!"));
			break;
		case 3:
			if (iState[7] == 1)
				SetDlgItemText(hwnd, LT_RESULT, TEXT("X is WINNER!"));
			else
				SetDlgItemText(hwnd, LT_RESULT, TEXT("O is WINNER!"));
			break;
		case 4:
			if (iState[1] == 1)
				SetDlgItemText(hwnd, LT_RESULT, TEXT("X is WINNER!"));
			else
				SetDlgItemText(hwnd, LT_RESULT, TEXT("O is WINNER!"));
			break;
		case 5:
			if (iState[2] == 1)
				SetDlgItemText(hwnd, LT_RESULT, TEXT("X is WINNER!"));
			else
				SetDlgItemText(hwnd, LT_RESULT, TEXT("O is WINNER!"));
			break;
		case 6:
			if (iState[3] == 1)
				SetDlgItemText(hwnd, LT_RESULT, TEXT("X is WINNER!"));
			else
				SetDlgItemText(hwnd, LT_RESULT, TEXT("O is WINNER!"));
			break;
		case 7:
			if (iState[1] == 1)
				SetDlgItemText(hwnd, LT_RESULT, TEXT("X is WINNER!"));
			else
				SetDlgItemText(hwnd, LT_RESULT, TEXT("O is WINNER!"));
			break;
		case 8:
			if (iState[3] == 1)
				SetDlgItemText(hwnd, LT_RESULT, TEXT("X is WINNER!"));
			else
				SetDlgItemText(hwnd, LT_RESULT, TEXT("O is WINNER!"));
			break;
		default:
			break;
		}
	}
#pragma endregion
	return FALSE;
}


int CheckGame()
{
	if (iState[1] == iState[2] == iState[3])
		return(1);
	else if (iState[4] == iState[5] == iState[6])
		return(2);
	else if (iState[7] == iState[8] == iState[9])
		return(3);
	else if (iState[1] == iState[4] == iState[7])
		return(4);
	else if (iState[2] == iState[5] == iState[8])
		return(5);
	else if (iState[3] == iState[6] == iState[9])
		return(6);
	else if (iState[1] == iState[5] == iState[9])
		return(7);
	else if (iState[3] == iState[5] == iState[7])
		return(8);
	else
		return(0);
}

void StopAll(HWND hwnd)
{
	EnableWindow(GetDlgItem(hwnd, PB_1), FALSE);
	EnableWindow(GetDlgItem(hwnd, PB_2), FALSE);
	EnableWindow(GetDlgItem(hwnd, PB_3), FALSE);
	EnableWindow(GetDlgItem(hwnd, PB_4), FALSE);
	EnableWindow(GetDlgItem(hwnd, PB_5), FALSE);
	EnableWindow(GetDlgItem(hwnd, PB_6), FALSE);
	EnableWindow(GetDlgItem(hwnd, PB_7), FALSE);
	EnableWindow(GetDlgItem(hwnd, PB_8), FALSE);
	EnableWindow(GetDlgItem(hwnd, PB_9), FALSE);
}
