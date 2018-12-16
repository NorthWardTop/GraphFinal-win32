// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  从 Windows 头文件中排除极少使用的信息
// Windows 头文件: 
#include <windows.h>
//#include <afxwin.h>
#include <atltypes.h>

// C 运行时头文件
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cstring>
#include <math.h>

// TODO:  在此处引用程序需要的其他头文件
//#include <easyx.h>











//1 #include "stdafx.h"
//2 #include "resourse.h"
//3
//4 #define MAX_LOADSTRING 100
//5
//6 // Global Variables:
//7 HINSTANCE hInst;                                // current instance
//8 TCHAR szTitle[MAX_LOADSTRING];                                // The title bar text
//9 TCHAR szWindowClass[MAX_LOADSTRING];                                // The title bar text
//10 HPEN hPen[7];          //以下四行是画笔及画刷对象数组声明
//11 HBRUSH hBru[7];
//12 int sPen[7] = { PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT, PS_NULL, PS_INSIDEFRAME };//前3个基本型(实、长间、短间)可以组合；
//13 int sBru[7] = { HS_VERTICAL, HS_HORIZONTAL, HS_CROSS, HS_DIAGCROSS, HS_FDIAGONAL, HS_BDIAGONAL };//横、竖、格、斜格、↘、↗)
//14 HWND  hWnd;
//15 HDC   hdc;
//16 // Foward declarations of functions included in this code module:
//17 ATOM                MyRegisterClass(HINSTANCE hInstance);
//18 BOOL                InitInstance(HINSTANCE, int);
//19 LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
//20 LRESULT CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
//21 void                MyPaint(HDC hdc);
//22 //========================================================================================
//23 int APIENTRY WinMain(HINSTANCE hInstance,
//24                      HINSTANCE hPrevInstance,
//25                      LPSTR     lpCmdLine,
//26                      int       nCmdShow)
//27 {
//	28      // TODO: Place code here.
//		29     MSG msg;
//	30
//		31     MyRegisterClass(hInstance);//调用函数向系统注册窗口类别，输入参数hInstance是目前运行程序的对象代码；
//	32
//		33     // 调用InitInstance函数，进行初始化操作；
//		34     if (!InitInstance(hInstance, nCmdShow))
//		35     {
//		36         return FALSE;
//		37     }
//	38
//		39     // 消息循环（通过消息循环来获取信息，
//		40     //进行必要的键盘信息转换而后将控制权交给操作系统，
//		41     //有操作系统决定哪个程序的消息处理函数处理消息
//		42     while (GetMessage(&msg, NULL, 0, 0)) //获取程序消息
//		43     {
//		44             TranslateMessage(&msg);//转换伪码及字符
//		45             DispatchMessage(&msg);//将控制权交给系统，再有系统决定负责处理消息的程序；
//		46     }
//	47
//		48     return msg.wParam;
//	49 }
//50 //=====================================================================================
//51
//52
//53
//54 //=============================================================================================
//55 //在建立程序窗口实体之前，必须先定义一个窗口类别，其中包含所要建立窗口的信息，
//56 //并向系统注册，这里的MyRegisterClass函数就是进行定义及注册窗口类别的函数。
//57 //==============================================================================================
//58 ATOM MyRegisterClass(HINSTANCE hInstance)
//59 {
//	60     WNDCLASSEX wcex;            //申请一个窗口类别“WNDCLASSEX”和结构”wcex“
//	61                                 //--------------------------------------------------------------
//		62                                 //定义vcex结构的各项信息，其中设定信息处理函数（lpfnWndProc）
//		63                                 //为WNDPROC，类别名称为（lpszClassName）为”fe";
//		64                                 //--------------------------------------------------------------
//		65     wcex.cbSize = sizeof(WNDCLASSEX);
//	66
//		67     wcex.style = CS_HREDRAW | CS_VREDRAW;
//	68     wcex.lpfnWndProc = (WNDPROC)WndProc;
//	69     wcex.cbClsExtra = 0;
//	70     wcex.cbWndExtra = 0;
//	71     wcex.hInstance = hInstance;
//	72     wcex.hIcon = NULL;
//	73     wcex.hCursor = NULL;
//	74     wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
//	75     wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
//	76     wcex.lpszMenuName = NULL;
//	77     wcex.lpszClassName = "fe";
//	78     wcex.hIconSm = NULL;
//	79
//		80     return RegisterClassEx(&wcex);//调用RegisterClassEx函数注册类别，返回一个“ATOM"形态的字符串
//	81                                   //此字符串即为类别名称”fe";
//		82 }
//83 //============================================================================================
//84
//85
//86 //============================================================================================
//87 //按照前面所定义的窗口类别来建立并显示实际的程序窗口
//88 //============================================================================================
//89 BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//90 {
//	91
//		92    int i;
//	93
//		94
//		95    hInst = hInstance; // 把instance handle 储存在全局变量中；
//	96
//		97    hWnd = CreateWindow("fe", "绘图窗口", WS_OVERLAPPEDWINDOW,
//		98       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
//	99                       //-----------------------------------------------
//		100                       //调用CreateWindow函数来建立一个窗口对象
//		101                       //第一个参数就是窗口建立依据的类别名称
//		102                       //-----------------------------------------------
//		103    if (!hWnd)
//		104    {
//		105       return FALSE;
//		106    }
//	107    //------------------------------------------------
//		108    //设定窗口的位置及窗口的大小，然后绘制显示在设备上
//		109    //-------------------------------------------------
//		110    MoveWindow(hWnd, 10, 10, 650, 450, true);//位置及大小
//	111    ShowWindow(hWnd, nCmdShow);//改定窗口显示时的状态
//	112    UpdateWindow(hWnd);//将窗口绘制在显示设备上
//	113
//		114    //--------------------------------------------------
//		115    //循环建立各种画笔与画刷
//		116    //--------------------------------------------------
//		117    for (i = 0; i <= 6; i++)
//		118    {
//		119        hPen[i] = CreatePen(sPen[i], 1, RGB(255, 0, 0));//sPen[]笔型；粗细；颜色
//		120        if (i == 6)hBru[i] = CreateSolidBrush(RGB(0, 255, 0));//i=6时调用CreateSolidBrush()函数建立单色笔
//		121        else hBru[i] = CreateHatchBrush(sBru[i], RGB(0, 255, 0));//i!=6时；根据sBru[]阴影刷
//		122    }
//	123
//		124    hdc = GetDC(hWnd);//取得窗口DC;
//	125
//		126    SetTimer(hWnd, 1, 5, NULL);
//	127    MyPaint(hdc);//在DC窗口出现时画图
//	128
//		129
//		130
//		131    return TRUE;
//	132 }
//133 //============================================================================================
//134
//135
//136 //============================================================================================
//137 //自定义绘图函数(以格式画笔及画刷绘制线条与填充矩形)
//138 //============================================================================================
//139 void MyPaint(HDC hdc)
//140 {
//	141     int i, x1, x2, y;//x1、x2、y坐标变量
//	142
//		143     for (i = 0; i <= 6; i++)//以7种不同画笔绘制线条
//		144     {
//		145         y = (i + 1) * 30;
//		146
//			147         SelectObject(hdc, hPen[i]);//选用画笔
//		148         MoveToEx(hdc, 30, y, NULL);//移到线条起点//-----GDI两个画线函数
//		149         LineTo(hdc, 100, y);//画线  ||-BOOL MoveToEx(HDC hdc,int x坐标,int y坐标,LPPOINT 目前坐标);
//		150     }                     //      ||-BOOL LineTo(HDC hdc,int x坐标,int y坐标);
//	151
//		152     x1 = 120;
//	153     x2 = 180;
//	154
//		155     for (i = 0; i <= 6; i++)//以7种不同画刷填充矩形
//		156     {
//		157         SelectObject(hdc, hBru[i]);//选画刷
//		158         Rectangle(hdc, x1, 30, x2, y);//画封闭矩形||-------绘制矩形函数
//		159         x1 += 70;      //------||-BOOL Rectangle(HDC hdc,int 矩形左上点x坐标,int 矩形左上点y坐标,int x,int y右下);
//		160         x2 += 70;
//		161     }
//	162 }
//163 //============================================================================================
//164
//165
//166 //============================================================================================
//167 //在前面定义类别的时候把WndProc定义为消息处理函数（当某些外部消息发生时，会按消息的类型
//168 //来决定该如何进行处理。此外该函数也是一个回叫函数（CALLBACK)（windows系统函数）每一个
//169 //程序都会接收信息，选择性接受、处理；
//170 //============================================================================================
//171 LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//172 {
//	173     PAINTSTRUCT ps;
//	174
//		175     int i;
//	176
//		177     switch (message)                   //判断消息类型
//		178     {
//		179         case WM_TIMER:
//			180             MyPaint(hdc);
//			181             break;
//			182         case WM_PAINT:                //窗口重绘制
//				183             hdc = BeginPaint(hWnd, &ps);
//				184             MyPaint(hdc);//窗口重绘开始时调用MyPaint()绘图
//				185             EndPaint(hWnd, &ps);
//				186             break;
//				187         case WM_DESTROY:              //处理窗口结束消息
//					188             for (i = 0; i <= 6; i++)//窗口消息结束时删除GDI对象
//						189             {
//						190                 DeleteObject(hPen[i]);
//						191                 DeleteObject(hBru[i]);
//						192             }
//					193             PostQuitMessage(0);
//					194             ReleaseDC(hWnd, hdc);//释放所占DC;
//					195             break;
//					196         default:
//						197             return DefWindowProc(hWnd, message, wParam, lParam);
//						198    }
//	199    return 0;
//	200 }
//201 //============================================================================================