// GraphFinal.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "GraphFinal.h"


#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名
HWND  g_hWnd;
HDC		g_hDc;

static int cxClient, cyClient;



// 此代码模块中包含的函数的前向声明: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
//绘制坐标系统
void drawCoorSys();

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  在此放置代码。
	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_GRAPHFINAL, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_GRAPHFINAL));

	// 主消息循环: 
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
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
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
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

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
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
/*
基本图形绘制
1.直线绘制
	IDM_Bresenham
	IDM_DDA
	IDM_MidBresenham
	IDM_LibLine
2.	Bresenham绘制圆:IDM_BresenhamCircle
3.	Bresenham绘制椭圆:IDM_BresenhamEllipse
4.	矩形的绘制:IDM_Rect
5.	多边形的绘制:IDM_Polygon
6.	圆弧的绘制:IDM_Arc
图形变换
1.	基本图形变换
	1）平移变换:IDM_MOVE
	2）比例变换:IDM_RATE
	3）错切变换:IDM_ 
	4）对称变换:IDM_Symmetric
	5) 旋转变换:IDM_TURN
2.	复合变换：
	1）复合平移变换:IDM_ComplexMove
	2）复合比例变换:IDM_ComplexRate
	3）复合旋转变换:IDM_ComplexTurn
3.  相对任意参考点的变换:IDM_ArbitraryPoint
4.	相对任意直线的变换:IDM_ArbitraryLine
自由曲线
1.Bezier 曲线绘制
	1)1次Bezier曲线:IDM_OnceBezier
	2)2次Bezier曲线:IDM_ScndBezier
	3)3次Bezier曲线:IDM_ThirdBezier
2.3次B样条曲线:IDM_ThirdBCurve
3.Hermite三次样条曲线:IDM_ThirdHermite
4.曲线的拼接设计:IDM_CurveSpell
图形裁剪:IDM_LineCut

*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;
	//InvalidateRect(g_hWnd, NULL, true);
//	drawCoorSys();//每次绘制坐标系统
	//CDC* pDC = GetCDC(g_hdc);
	switch (message)
	{
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// 分析菜单选择: 
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
		//以下为绘图消息分析
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
			moveEllipse(-30, -30, -200,-200);//平移变换
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

// “关于”框的消息处理程序。
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

//绘制坐标系统
void drawCoorSys()
{
	//获取视图窗口大小
	CRect wndSize;
	GetClientRect(g_hWnd,&wndSize);
	SetMapMode(g_hDc, 4);//修改映射模式
	SetViewportOrgEx(g_hDc,wndSize.right / 2, wndSize.bottom / 2,NULL);//设置视图逻辑原点(MFC)

	//画坐标系x
	MoveToEx(g_hDc, -wndSize.right / 2, 0, NULL);
	LineTo(g_hDc,wndSize.right / 2, 0);
	//箭头
	MoveToEx(g_hDc,wndSize.right / 2, 0,NULL);
	LineTo(g_hDc,(wndSize.right / 2) - 10, 10);
	//画坐标系y
	MoveToEx(g_hDc,0, -wndSize.bottom / 2,NULL);
	LineTo(g_hDc,0, wndSize.bottom / 2);
	//箭头
	MoveToEx(g_hDc,0, wndSize.bottom / 2,NULL);
	LineTo(g_hDc,-10, wndSize.bottom / 2 - 10);
}