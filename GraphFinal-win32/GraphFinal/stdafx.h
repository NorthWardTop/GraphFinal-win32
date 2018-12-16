// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             //  �� Windows ͷ�ļ����ų�����ʹ�õ���Ϣ
// Windows ͷ�ļ�: 
#include <windows.h>
//#include <afxwin.h>
#include <atltypes.h>

// C ����ʱͷ�ļ�
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <cstring>
#include <math.h>

// TODO:  �ڴ˴����ó�����Ҫ������ͷ�ļ�
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
//10 HPEN hPen[7];          //���������ǻ��ʼ���ˢ������������
//11 HBRUSH hBru[7];
//12 int sPen[7] = { PS_SOLID, PS_DASH, PS_DOT, PS_DASHDOT, PS_DASHDOTDOT, PS_NULL, PS_INSIDEFRAME };//ǰ3��������(ʵ�����䡢�̼�)������ϣ�
//13 int sBru[7] = { HS_VERTICAL, HS_HORIZONTAL, HS_CROSS, HS_DIAGCROSS, HS_FDIAGONAL, HS_BDIAGONAL };//�ᡢ������б�񡢨K���J)
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
//		31     MyRegisterClass(hInstance);//���ú�����ϵͳע�ᴰ������������hInstance��Ŀǰ���г���Ķ�����룻
//	32
//		33     // ����InitInstance���������г�ʼ��������
//		34     if (!InitInstance(hInstance, nCmdShow))
//		35     {
//		36         return FALSE;
//		37     }
//	38
//		39     // ��Ϣѭ����ͨ����Ϣѭ������ȡ��Ϣ��
//		40     //���б�Ҫ�ļ�����Ϣת�����󽫿���Ȩ��������ϵͳ��
//		41     //�в���ϵͳ�����ĸ��������Ϣ������������Ϣ
//		42     while (GetMessage(&msg, NULL, 0, 0)) //��ȡ������Ϣ
//		43     {
//		44             TranslateMessage(&msg);//ת��α�뼰�ַ�
//		45             DispatchMessage(&msg);//������Ȩ����ϵͳ������ϵͳ������������Ϣ�ĳ���
//		46     }
//	47
//		48     return msg.wParam;
//	49 }
//50 //=====================================================================================
//51
//52
//53
//54 //=============================================================================================
//55 //�ڽ������򴰿�ʵ��֮ǰ�������ȶ���һ������������а�����Ҫ�������ڵ���Ϣ��
//56 //����ϵͳע�ᣬ�����MyRegisterClass�������ǽ��ж��弰ע�ᴰ�����ĺ�����
//57 //==============================================================================================
//58 ATOM MyRegisterClass(HINSTANCE hInstance)
//59 {
//	60     WNDCLASSEX wcex;            //����һ���������WNDCLASSEX���ͽṹ��wcex��
//	61                                 //--------------------------------------------------------------
//		62                                 //����vcex�ṹ�ĸ�����Ϣ�������趨��Ϣ��������lpfnWndProc��
//		63                                 //ΪWNDPROC���������Ϊ��lpszClassName��Ϊ��fe";
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
//		80     return RegisterClassEx(&wcex);//����RegisterClassEx����ע����𣬷���һ����ATOM"��̬���ַ���
//	81                                   //���ַ�����Ϊ������ơ�fe";
//		82 }
//83 //============================================================================================
//84
//85
//86 //============================================================================================
//87 //����ǰ��������Ĵ����������������ʾʵ�ʵĳ��򴰿�
//88 //============================================================================================
//89 BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
//90 {
//	91
//		92    int i;
//	93
//		94
//		95    hInst = hInstance; // ��instance handle ������ȫ�ֱ����У�
//	96
//		97    hWnd = CreateWindow("fe", "��ͼ����", WS_OVERLAPPEDWINDOW,
//		98       CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
//	99                       //-----------------------------------------------
//		100                       //����CreateWindow����������һ�����ڶ���
//		101                       //��һ���������Ǵ��ڽ������ݵ��������
//		102                       //-----------------------------------------------
//		103    if (!hWnd)
//		104    {
//		105       return FALSE;
//		106    }
//	107    //------------------------------------------------
//		108    //�趨���ڵ�λ�ü����ڵĴ�С��Ȼ�������ʾ���豸��
//		109    //-------------------------------------------------
//		110    MoveWindow(hWnd, 10, 10, 650, 450, true);//λ�ü���С
//	111    ShowWindow(hWnd, nCmdShow);//�Ķ�������ʾʱ��״̬
//	112    UpdateWindow(hWnd);//�����ڻ�������ʾ�豸��
//	113
//		114    //--------------------------------------------------
//		115    //ѭ���������ֻ����뻭ˢ
//		116    //--------------------------------------------------
//		117    for (i = 0; i <= 6; i++)
//		118    {
//		119        hPen[i] = CreatePen(sPen[i], 1, RGB(255, 0, 0));//sPen[]���ͣ���ϸ����ɫ
//		120        if (i == 6)hBru[i] = CreateSolidBrush(RGB(0, 255, 0));//i=6ʱ����CreateSolidBrush()����������ɫ��
//		121        else hBru[i] = CreateHatchBrush(sBru[i], RGB(0, 255, 0));//i!=6ʱ������sBru[]��Ӱˢ
//		122    }
//	123
//		124    hdc = GetDC(hWnd);//ȡ�ô���DC;
//	125
//		126    SetTimer(hWnd, 1, 5, NULL);
//	127    MyPaint(hdc);//��DC���ڳ���ʱ��ͼ
//	128
//		129
//		130
//		131    return TRUE;
//	132 }
//133 //============================================================================================
//134
//135
//136 //============================================================================================
//137 //�Զ����ͼ����(�Ը�ʽ���ʼ���ˢ����������������)
//138 //============================================================================================
//139 void MyPaint(HDC hdc)
//140 {
//	141     int i, x1, x2, y;//x1��x2��y�������
//	142
//		143     for (i = 0; i <= 6; i++)//��7�ֲ�ͬ���ʻ�������
//		144     {
//		145         y = (i + 1) * 30;
//		146
//			147         SelectObject(hdc, hPen[i]);//ѡ�û���
//		148         MoveToEx(hdc, 30, y, NULL);//�Ƶ��������//-----GDI�������ߺ���
//		149         LineTo(hdc, 100, y);//����  ||-BOOL MoveToEx(HDC hdc,int x����,int y����,LPPOINT Ŀǰ����);
//		150     }                     //      ||-BOOL LineTo(HDC hdc,int x����,int y����);
//	151
//		152     x1 = 120;
//	153     x2 = 180;
//	154
//		155     for (i = 0; i <= 6; i++)//��7�ֲ�ͬ��ˢ������
//		156     {
//		157         SelectObject(hdc, hBru[i]);//ѡ��ˢ
//		158         Rectangle(hdc, x1, 30, x2, y);//����վ���||-------���ƾ��κ���
//		159         x1 += 70;      //------||-BOOL Rectangle(HDC hdc,int �������ϵ�x����,int �������ϵ�y����,int x,int y����);
//		160         x2 += 70;
//		161     }
//	162 }
//163 //============================================================================================
//164
//165
//166 //============================================================================================
//167 //��ǰ�涨������ʱ���WndProc����Ϊ��Ϣ����������ĳЩ�ⲿ��Ϣ����ʱ���ᰴ��Ϣ������
//168 //����������ν��д�������ú���Ҳ��һ���ؽк�����CALLBACK)��windowsϵͳ������ÿһ��
//169 //���򶼻������Ϣ��ѡ���Խ��ܡ�����
//170 //============================================================================================
//171 LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
//172 {
//	173     PAINTSTRUCT ps;
//	174
//		175     int i;
//	176
//		177     switch (message)                   //�ж���Ϣ����
//		178     {
//		179         case WM_TIMER:
//			180             MyPaint(hdc);
//			181             break;
//			182         case WM_PAINT:                //�����ػ���
//				183             hdc = BeginPaint(hWnd, &ps);
//				184             MyPaint(hdc);//�����ػ濪ʼʱ����MyPaint()��ͼ
//				185             EndPaint(hWnd, &ps);
//				186             break;
//				187         case WM_DESTROY:              //�����ڽ�����Ϣ
//					188             for (i = 0; i <= 6; i++)//������Ϣ����ʱɾ��GDI����
//						189             {
//						190                 DeleteObject(hPen[i]);
//						191                 DeleteObject(hBru[i]);
//						192             }
//					193             PostQuitMessage(0);
//					194             ReleaseDC(hWnd, hdc);//�ͷ���ռDC;
//					195             break;
//					196         default:
//						197             return DefWindowProc(hWnd, message, wParam, lParam);
//						198    }
//	199    return 0;
//	200 }
//201 //============================================================================================