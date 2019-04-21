
// MFCGraph2View.cpp : CMFCGraph2View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCGraph2.h"
#endif

#include "MFCGraph2Doc.h"
#include "MFCGraph2View.h"
#include <GL/glut.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCGraph2View

IMPLEMENT_DYNCREATE(CMFCGraph2View, CView)

BEGIN_MESSAGE_MAP(CMFCGraph2View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCGraph2View ����/����

CMFCGraph2View::CMFCGraph2View()
{
	// TODO:  �ڴ˴���ӹ������

}

CMFCGraph2View::~CMFCGraph2View()
{
}

BOOL CMFCGraph2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCGraph2View ����
void CMFCGraph2View::OnDraw(CDC* pDC)
{
	CMFCGraph2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	OnBeginPrinting(pDC, NULL);
	//moveEllipse(30, 30, 200, 200, pDC);//ƽ�Ʊ任
	//rateEllipse(-30, 30, -200, 200, pDC);
	symmRect(-200, -100, -300, -200,pDC);
	CPoint p0 = { 0, 0 }, p1 = { 100, -100 };
	compRect(p0, p1, 2, 1.5, pDC);
}


// CMFCGraph2View ��ӡ

BOOL CMFCGraph2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCGraph2View::OnBeginPrinting(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
	//������ϵ
	//��ȡ��ͼ���ڴ�С
	CRect wndSize;
	this->GetClientRect(&wndSize);
	pDC->SetMapMode(4);//�޸�ӳ��ģʽ
	pDC->SetViewportOrg(\
		wndSize.right / 2, wndSize.bottom / 2);//������ͼ�߼�ԭ��

	//������ϵx
	pDC->MoveTo(-wndSize.right / 2, 0);
	pDC->LineTo(wndSize.right / 2, 0);
	//��ͷ
	pDC->MoveTo(wndSize.right / 2, 0);
	pDC->LineTo((wndSize.right / 2) - 10, 10);
	//������ϵy
	pDC->MoveTo(0, -wndSize.bottom / 2);
	pDC->LineTo(0, wndSize.bottom / 2);
	//��ͷ
	pDC->MoveTo(0, wndSize.bottom / 2);
	pDC->LineTo(-10, wndSize.bottom / 2 - 10);
}

void CMFCGraph2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMFCGraph2View ���

#ifdef _DEBUG
void CMFCGraph2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCGraph2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCGraph2Doc* CMFCGraph2View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCGraph2Doc)));
	return (CMFCGraph2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCGraph2View ��Ϣ�������
/*
��3����дƽ�ơ����������С��ԳƱ任�ĺ���
��4����д����ƽ�ơ����������б任���ϱ任������
*/

//��Բ��ƽ�Ʊ任
void CMFCGraph2View::moveEllipse(int x0, int y0, int x1, int y1, CDC* pDC)
{
	pDC->TextOut(x0, y0, L"��Բ��ƽ�Ʊ任");
	pDC->Ellipse(x0, y0, x1, y1);
	pDC->TextOut(x0+300, y0+200, L"ƽ��300,200��");
	pDC->Ellipse(x0+300, y0+200, x1+300, y1+200);
}

//��Բ�ı����任
void CMFCGraph2View::rateEllipse(int x0, int y0, int x1, int y1, CDC* pDC)
{
	int Sx=2 , Sy = 2;
	pDC->TextOut(x0*Sx, y0*Sy, L"��Բ�ı����任");
	pDC->Ellipse(x0, y0, x1, y1);
	pDC->TextOut(x0*Sx*Sx, y0*Sy*Sy, L"�����仯Sx,Sy��");
	pDC->Ellipse(x0*Sx, y0*Sy, x1*Sx, y1*Sy);
}

//���εĶԳƱ任
void CMFCGraph2View::symmRect(int x0, int y0, int x1, int y1, CDC* pDC)
{
	pDC->TextOut(x0, y0, L"���εĶԳƱ任ǰ");
	pDC->Rectangle(x0, y0, x1, y1);
	pDC->TextOut(-x0, -y0, L"���εĶԳƱ任��");
	pDC->Rectangle(-x0, -y0, -x1, -y1);
}

//���εĸ��ϱ任(�Ƚ�x����, �ٽ�y����)
void CMFCGraph2View::compRect(CPoint p0, CPoint p1, int sX, float bY, CDC* pDC)
{
	pDC->TextOut(p0.x+p1.x,p0.y, L"���εı����任ǰ");
	pDC->Rectangle(p0.x,p0.y,p1.x,p1.y);
	pDC->TextOut(p0.x*sX+p1.x*2, p0.y-150 , L"�����仯sX��");
	pDC->Rectangle(p0.x*sX, p0.y-150, p1.x*sX, p1.y-150);//Ϊ��ʾ����, ��Ҫƽ��
	pDC->TextOut((p0.x*sX + 210)*bY, (p1.y - 150), L"���б任��");
	pDC->Rectangle((p0.x*sX+210)*bY, (p0.y - 150), (p1.x*sX+210)*bY, (p1.y - 150));
}



