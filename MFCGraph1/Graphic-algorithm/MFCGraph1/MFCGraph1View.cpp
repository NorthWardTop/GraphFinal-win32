
// MFCGraph1View.cpp : CMFCGraph1View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "MFCGraph1.h"
#endif

#include "MFCGraph1Doc.h"
#include "MFCGraph1View.h"
#include <GL/glut.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCGraph1View

IMPLEMENT_DYNCREATE(CMFCGraph1View, CView)

BEGIN_MESSAGE_MAP(CMFCGraph1View, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCGraph1View 构造/析构

CMFCGraph1View::CMFCGraph1View()
{
	// TODO:  在此处添加构造代码

}

CMFCGraph1View::~CMFCGraph1View()
{

}


BOOL CMFCGraph1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCGraph1View 绘制
//*******************************************************************************************
void CMFCGraph1View::OnDraw(CDC* pDC)
{
	CMFCGraph1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//坐标初始化
	drawCoorSys(pDC);
	//第一象限
	bresLine(20, 20, 200, 200, pDC);
	DDALine(20, 20+10, 200, 200+10, pDC);
	midBresLine(20, 20+20, 200, 200+20, pDC);
	//第二象限
	midBresCircle(-120, 120, 100, pDC);
	//第三象限
	midBresEllipse(-120, -120, 50, 70, pDC);
	//第四象限
	glRect(20, -20, 200, -200, pDC);
}



// CMFCGraph1View 打印

BOOL CMFCGraph1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCGraph1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
}

void CMFCGraph1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMFCGraph1View 诊断

#ifdef _DEBUG
void CMFCGraph1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCGraph1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCGraph1Doc* CMFCGraph1View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCGraph1Doc)));
	return (CMFCGraph1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCGraph1View 消息处理程序

//
//// 画线
//void CMFCGraph1View::draw(int x1, int y1, int x2, int y2, CDC* pDC)
//{
//	//1.画线
//	pDC->MoveTo(100, 150);
//	pDC->LineTo(300, 400);
//	//2.设置画笔
//	CPen linePen;
//	linePen.CreatePen(PS_ENDCAP_SQUARE, 10, RGB(0, 255, 0));
//	pDC->SelectObject(&linePen);
//	pDC->LineTo(400, 500);
//	//3.画矩形
//	pDC->Rectangle(50, 50, 100, 100);
//}

//DDA画线
void CMFCGraph1View::DDALine(int x1, int y1, int x2, int y2, CDC* pDC)
{
	pDC->TextOut(x2, y2, L"DDA画线");
	int dx=x2-x1, dy=y2-y1, epsl;
	float x=x1, y=y1, xIncre, yIncre;
	if (abs(dx) > abs(dy))
		epsl = abs(dx);
	else
		epsl = abs(dy);
	xIncre = (float)dx / (float)epsl;
	yIncre = (float)dy / (float)epsl;
	for (int k = 0; k <= epsl; k++)
	{
		pDC->SetPixel((int)x + 0.5, (int)y + 0.5,RGB(0,0,255));
		x += xIncre;
		y += yIncre;
	}
}

//Bresenham画线
void CMFCGraph1View::bresLine(int x1, int y1, int x2, int y2, CDC* pDC)
{
	pDC->TextOut(x2, y2, L"Bresenham画线");
	int x = x1, y = y1, dx = x2 - x1, dy = y2 - y1, e = -dx;
	while (x <= x2)
	{
		pDC->SetPixel(x, y, RGB(0, 255, 0));
		x++;
		e =e+ (2 * dy);
		if (e > 0)
		{
			y++;
			e =e- (2 * dx);
		}
	}
}

//中点Bresenham画线
void CMFCGraph1View::midBresLine(int x1, int y1, int x2, int y2, CDC* pDC)
{
	pDC->TextOut(x2, y2, L"中点Bresenham画线");
	int dx, dy, d, upIncre, downIncre, x = x1, y = y1;
	if (x1 > x2)
	{
		x = x2; x2 = x1; x1 = x;
		y = y2; y2 = y1; y1 = y;
	}
	x = x1; y = y1;
	dx = x2 - x1;		dy = y2 - y1;
	d = dx - 2 * dy;
	upIncre = 2 * dx - 2 * dy;		downIncre = -2 * dy;
	while (x<=x2)
	{
		pDC->SetPixel(x, y, RGB(0, 255, 255));
		x++;
		if (d < 0)
		{
			y++;
			d += upIncre;
		}
		else
			d += downIncre;
	}
}

//中点Bresenham画圆
static void  point(int x, int y, int x0, int y0, CDC* pDC)
{
	pDC->SetPixel(x0 + x, y0 + y, RGB(255, 0, 0));	pDC->SetPixel(x0 + y, y0+ x, RGB(255, 0, 0));
	pDC->SetPixel(x0 - y, y0 + x, RGB(0, 255, 0)); pDC->SetPixel(x0 - x, y0+y, RGB(0, 255, 0));
	pDC->SetPixel(x0 - x, y0 - y, RGB(0, 0, 255));	pDC->SetPixel(x0 - y, y0 - x, RGB(0, 0, 255));
	pDC->SetPixel(x0 + y, y0 - x, RGB(255, 255, 0)); pDC->SetPixel(x0 + x, y0 - y, RGB(255, 255, 0));
}

void CMFCGraph1View::midBresCircle(int x0, int  y0, int r, CDC* pDC)
{
	pDC->TextOut(x0, y0, L"中点Bresenham画圆");
	int x=0, y=r, d=1-r;
	while (x <= y)
	{
		point(x, y, x0,y0,pDC);
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}

//中点Bresenham椭圆
static void  point2(int x, int y, int x0, int y0, CDC* pDC)
{
	pDC->SetPixel(x0 + x, y0 + y, RGB(255, 0, 0)); pDC->SetPixel(x0 - x, y0 - y, RGB(0, 0, 255));
	pDC->SetPixel(x0 - x, y0 + y, RGB(0, 0, 255)); pDC->SetPixel(x0 + x, y0 - y, RGB(0, 0, 255));
}


void CMFCGraph1View::midBresEllipse(int x0,int y0,int a,int b, CDC* pDC)
{
	pDC->TextOut(x0, y0, L"中点Bresenham椭圆");
	int x=0, y=b;
	float d1 = b*b + a*a*(-b + 0.25);
	float d2 = b*b*(x + 0.5)*(x + 0.5) + a*a*(y - 1)*(y - 1) - a*a*b*b;
	point2(x, y, x0, y0, pDC);
	while (b*b*(x + 1) < a*a*(y - 0.5))
	{
		if (d1 <= 0)
		{
			d1 += b*b*(3 * x + 3);
			x++; 
		}
		else
		{
			d1 += b*b*(2 * x + 3) + a*a*(-2 * y + 2);
			x++; y--;
		}
		point2(x, y, x0, y0, pDC);
	}

	while (y>0)
	{
		if (d2 <= 0)
		{
			d2 += b*b*(2 * x + 2)+a*a*(-2*y+3);
			x++; y--;
		}
		else
		{
			d2 +=  a*a*(-2 * y + 3);
			 y--;
		}
		point2(x, y, x0, y0, pDC);
	}
}

//矩形绘制GL
void CMFCGraph1View::glRect(int x0, int y0, int x1, int y1,CDC* pDC)
{
	pDC->TextOut(x1, y1, L"MFC库函数画矩形");
	pDC->Rectangle(x0, y0, x1, y1);
}


//画坐标系,初始化
void CMFCGraph1View::drawCoorSys(CDC* pDC)
{
	//获取视图窗口大小
	CRect wndSize;
	this->GetClientRect(&wndSize); 
	pDC->SetMapMode(4);//修改映射模式
	pDC->SetViewportOrg(	\
		wndSize.right / 2, wndSize.bottom / 2);//设置视图逻辑原点

	//画坐标系x
	pDC->MoveTo(-wndSize.right/2, 0);
	pDC->LineTo(wndSize.right / 2, 0);
	//箭头
	pDC->MoveTo(wndSize.right / 2, 0);
	pDC->LineTo((wndSize.right / 2)-10, 10);
	//画坐标系y
	pDC->MoveTo(0, -wndSize.bottom / 2);
	pDC->LineTo(0, wndSize.bottom / 2);
	//箭头
	pDC->MoveTo(0, wndSize.bottom / 2);
	pDC->LineTo(-10, wndSize.bottom / 2-10);
}