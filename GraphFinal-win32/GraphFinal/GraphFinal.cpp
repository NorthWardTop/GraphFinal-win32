// GraphFinal.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "GraphFinal.h"


#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������
HWND  g_hWnd;
HDC		g_hDc;

static int cxClient, cyClient;



// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//��������ϵͳ
void drawCoorSys();

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  �ڴ˷��ô��롣
	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GRAPHFINAL, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GRAPHFINAL));

	// ����Ϣѭ��: 
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
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
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
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GRAPHFINAL));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_GRAPHFINAL);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   g_hWnd = hWnd;
   g_hDc = GetDC(hWnd);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);
   drawCoorSys();
   return TRUE;
}

//
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
/*
����ͼ�λ���
1.ֱ�߻���
	IDM_Bresenham
	IDM_DDA
	IDM_MidBresenham
	IDM_LibLine
2.	Bresenham����Բ:IDM_BresenhamCircle
3.	Bresenham������Բ:IDM_BresenhamEllipse
4.	���εĻ���:IDM_Rect
5.	����εĻ���:IDM_Polygon
6.	Բ���Ļ���:IDM_Arc
ͼ�α任
1.	����ͼ�α任
	1��ƽ�Ʊ任:IDM_MOVE
	2�������任:IDM_RATE
	3�����б任:IDM_ 
	4���ԳƱ任:IDM_Symmetric
	5) ��ת�任:IDM_TURN
2.	���ϱ任��
	1������ƽ�Ʊ任:IDM_ComplexMove
	2�����ϱ����任:IDM_ComplexRate
	3��������ת�任:IDM_ComplexTurn
3.  �������ο���ı任:IDM_ArbitraryPoint
4.	�������ֱ�ߵı任:IDM_ArbitraryLine
��������
1.Bezier ���߻���
	1)1��Bezier����:IDM_OnceBezier
	2)2��Bezier����:IDM_ScndBezier
	3)3��Bezier����:IDM_ThirdBezier
2.3��B��������:IDM_ThirdBCurve
3.Hermite������������:IDM_ThirdHermite
4.���ߵ�ƴ�����:IDM_CurveSpell
ͼ�βü�:IDM_LineCut

*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//InvalidateRect(g_hWnd, NULL, true);
//	drawCoorSys();//ÿ�λ�������ϵͳ
	//CDC* pDC = GetCDC(g_hdc);
	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			hdc = BeginPaint(hWnd, &ps);
			
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		case IDM_CLEAR:
			InvalidateRect(g_hWnd, NULL, true);
			break;
		//����Ϊ��ͼ��Ϣ����
		case IDM_Bresenham:
			bresLine(20, 20, 200, 200);
			break;
		case IDM_DDA:
			DDALine(20, 20 + 30, 200, 200 + 30);
			break;
		case IDM_MidBresenham:
			midBresLine(-20, -20 + 60, 20, 20 + 60);
			break;
		case IDM_LibLine:
			libLine(100, 10, 300, 100);
			break;
		case IDM_BresenhamCircle:
			midBresCircle(-120, 120, 100);
			break;
		case IDM_BresenhamEllipse:
			midBresEllipse(-120, -120, 50, 70);
			break;
		case IDM_Rect:
			glRect(20, -20, 200, -200);
			break;
		case IDM_Polygon:
		{
							CRect wndSize;
							GetClientRect(g_hWnd, &wndSize);
							FillRect(g_hDc, wndSize, (HBRUSH)(COLOR_WINDOW + 1));
							int arrX[5] = {-430,40,400,30,-300};
			int arrY[5] = {200,100,-50,-230,-150};
			polygon(arrX, arrY, 5);
		}
			break;
		case IDM_Arc:
			{
						int arrX[4] = { 0, 200, 0, -200 };
						int arrY[4] = { 200, 0, -200, 0 };
						arc(arrX, arrY);
			}
			break;
		case IDM_MOVE:
			moveEllipse(-30, -30, -200,-200);//ƽ�Ʊ任
			break;
		case IDM_RATE:
			rateEllipse(-30, 30, -200, 200);
			break;
		case IDM_Dislocat:
			dislocatRect(-200, 0, -100, 100);
			break;
		case IDM_Symmetric:
			symmRect(-50, -50, -10, -10);
			break;
		case IDM_TURN:
			turnRect();
			break;
		case IDM_ComplexMove:
			compMove(-250, -150, -10, -10);
			break;
		case IDM_ComplexRate:
			compRate(20, -20, 200, -200);
			break;
		case IDM_ComplexTurn:
			compTurn();
			break;
		case IDM_ArbitraryPoint:
			arbitPointRate(20, 20, 60, 60, 30, -20, -20);
			break;
		case IDM_ArbitraryLine:
		{
								  int m[8] = { 0, 200, 0, -200, 0, 0, -200, 0 };
								  arbitLineRate(m);
		}
			break;
		case IDM_OnceBezier:
			bezier1();
			break;
		case IDM_ScndBezier:
			bezier2();
			break;
		case IDM_ThirdBezier:
			bezier3();
			break;
		case IDM_ThirdBCurve:
			thirdBCurve();
			break;
		case IDM_ThirdHermite:
			thirdHermite();
			break;
		case IDM_CurveSpell:
			compCurve();
			break;
		case IDM_LineCut:
			fillRect(90,80,200,100);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;



	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
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

//��������ϵͳ
void drawCoorSys()
{
	//��ȡ��ͼ���ڴ�С
	CRect wndSize;
	GetClientRect(g_hWnd,&wndSize);
	SetMapMode(g_hDc, 4);//�޸�ӳ��ģʽ
	SetViewportOrgEx(g_hDc,wndSize.right / 2, wndSize.bottom / 2,NULL);//������ͼ�߼�ԭ��(MFC)

	//������ϵx
	MoveToEx(g_hDc, -wndSize.right / 2, 0, NULL);
	LineTo(g_hDc,wndSize.right / 2, 0);
	//��ͷ
	MoveToEx(g_hDc,wndSize.right / 2, 0,NULL);
	LineTo(g_hDc,(wndSize.right / 2) - 10, 10);
	//������ϵy
	MoveToEx(g_hDc,0, -wndSize.bottom / 2,NULL);
	LineTo(g_hDc,0, wndSize.bottom / 2);
	//��ͷ
	MoveToEx(g_hDc,0, wndSize.bottom / 2,NULL);
	LineTo(g_hDc,-10, wndSize.bottom / 2 - 10);
}