
// MFCGraph1View.cpp : CMFCGraph1View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCGraph1View ����/����

CMFCGraph1View::CMFCGraph1View()
{
	// TODO:  �ڴ˴���ӹ������

}

CMFCGraph1View::~CMFCGraph1View()
{

}


BOOL CMFCGraph1View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCGraph1View ����
//*******************************************************************************************
void CMFCGraph1View::OnDraw(CDC* pDC)
{
	CMFCGraph1Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	//�����ʼ��
	drawCoorSys(pDC);
	//��һ����
	bresLine(20, 20, 200, 200, pDC);
	DDALine(20, 20+10, 200, 200+10, pDC);
	midBresLine(20, 20+20, 200, 200+20, pDC);
	//�ڶ�����
	midBresCircle(-120, 120, 100, pDC);
	//��������
	midBresEllipse(-120, -120, 50, 70, pDC);
	//��������
	glRect(20, -20, 200, -200, pDC);
}



// CMFCGraph1View ��ӡ

BOOL CMFCGraph1View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCGraph1View::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CMFCGraph1View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMFCGraph1View ���

#ifdef _DEBUG
void CMFCGraph1View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCGraph1View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCGraph1Doc* CMFCGraph1View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCGraph1Doc)));
	return (CMFCGraph1Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCGraph1View ��Ϣ�������

//
//// ����
//void CMFCGraph1View::draw(int x1, int y1, int x2, int y2, CDC* pDC)
//{
//	//1.����
//	pDC->MoveTo(100, 150);
//	pDC->LineTo(300, 400);
//	//2.���û���
//	CPen linePen;
//	linePen.CreatePen(PS_ENDCAP_SQUARE, 10, RGB(0, 255, 0));
//	pDC->SelectObject(&linePen);
//	pDC->LineTo(400, 500);
//	//3.������
//	pDC->Rectangle(50, 50, 100, 100);
//}

//DDA����
void CMFCGraph1View::DDALine(int x1, int y1, int x2, int y2, CDC* pDC)
{
	pDC->TextOut(x2, y2, L"DDA����");
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

//Bresenham����
void CMFCGraph1View::bresLine(int x1, int y1, int x2, int y2, CDC* pDC)
{
	pDC->TextOut(x2, y2, L"Bresenham����");
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

//�е�Bresenham����
void CMFCGraph1View::midBresLine(int x1, int y1, int x2, int y2, CDC* pDC)
{
	pDC->TextOut(x2, y2, L"�е�Bresenham����");
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

//�е�Bresenham��Բ
static void  point(int x, int y, int x0, int y0, CDC* pDC)
{
	pDC->SetPixel(x0 + x, y0 + y, RGB(255, 0, 0));	pDC->SetPixel(x0 + y, y0+ x, RGB(255, 0, 0));
	pDC->SetPixel(x0 - y, y0 + x, RGB(0, 255, 0)); pDC->SetPixel(x0 - x, y0+y, RGB(0, 255, 0));
	pDC->SetPixel(x0 - x, y0 - y, RGB(0, 0, 255));	pDC->SetPixel(x0 - y, y0 - x, RGB(0, 0, 255));
	pDC->SetPixel(x0 + y, y0 - x, RGB(255, 255, 0)); pDC->SetPixel(x0 + x, y0 - y, RGB(255, 255, 0));
}

void CMFCGraph1View::midBresCircle(int x0, int  y0, int r, CDC* pDC)
{
	pDC->TextOut(x0, y0, L"�е�Bresenham��Բ");
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

//�е�Bresenham��Բ
static void  point2(int x, int y, int x0, int y0, CDC* pDC)
{
	pDC->SetPixel(x0 + x, y0 + y, RGB(255, 0, 0)); pDC->SetPixel(x0 - x, y0 - y, RGB(0, 0, 255));
	pDC->SetPixel(x0 - x, y0 + y, RGB(0, 0, 255)); pDC->SetPixel(x0 + x, y0 - y, RGB(0, 0, 255));
}


void CMFCGraph1View::midBresEllipse(int x0,int y0,int a,int b, CDC* pDC)
{
	pDC->TextOut(x0, y0, L"�е�Bresenham��Բ");
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

//���λ���GL
void CMFCGraph1View::glRect(int x0, int y0, int x1, int y1,CDC* pDC)
{
	pDC->TextOut(x1, y1, L"MFC�⺯��������");
	pDC->Rectangle(x0, y0, x1, y1);
}


//������ϵ,��ʼ��
void CMFCGraph1View::drawCoorSys(CDC* pDC)
{
	//��ȡ��ͼ���ڴ�С
	CRect wndSize;
	this->GetClientRect(&wndSize); 
	pDC->SetMapMode(4);//�޸�ӳ��ģʽ
	pDC->SetViewportOrg(	\
		wndSize.right / 2, wndSize.bottom / 2);//������ͼ�߼�ԭ��

	//������ϵx
	pDC->MoveTo(-wndSize.right/2, 0);
	pDC->LineTo(wndSize.right / 2, 0);
	//��ͷ
	pDC->MoveTo(wndSize.right / 2, 0);
	pDC->LineTo((wndSize.right / 2)-10, 10);
	//������ϵy
	pDC->MoveTo(0, -wndSize.bottom / 2);
	pDC->LineTo(0, wndSize.bottom / 2);
	//��ͷ
	pDC->MoveTo(0, wndSize.bottom / 2);
	pDC->LineTo(-10, wndSize.bottom / 2-10);
}