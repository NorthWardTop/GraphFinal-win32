
// MFCGraph3View.cpp : CMFCGraph3View ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
#ifndef SHARED_HANDLERS
#include "MFCGraph3.h"
#endif

#include "MFCGraph3Doc.h"
#include "MFCGraph3View.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMFCGraph3View

IMPLEMENT_DYNCREATE(CMFCGraph3View, CView)

BEGIN_MESSAGE_MAP(CMFCGraph3View, CView)
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCGraph3View ����/����

CMFCGraph3View::CMFCGraph3View()
{
	// TODO:  �ڴ˴���ӹ������

}

CMFCGraph3View::~CMFCGraph3View()
{
}

BOOL CMFCGraph3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}

// CMFCGraph3View ����

void CMFCGraph3View::OnDraw(CDC* pDC)
{
	CMFCGraph3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  �ڴ˴�Ϊ����������ӻ��ƴ���
	OnBeginPrinting(pDC, NULL);
	ScanlineSeedfill(pDC, 30, 40, RGB(255, 0, 0), RGB(0, 255, 0));
}


// CMFCGraph3View ��ӡ

BOOL CMFCGraph3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CMFCGraph3View::OnBeginPrinting(CDC* pDC, CPrintInfo* /*pInfo*/)
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

void CMFCGraph3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  ��Ӵ�ӡ����е��������
}


// CMFCGraph3View ���

#ifdef _DEBUG
void CMFCGraph3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCGraph3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCGraph3Doc* CMFCGraph3View::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCGraph3Doc)));
	return (CMFCGraph3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCGraph3View ��Ϣ�������
void CMFCGraph3View::ScanlineSeedfill(CDC *pDC, int x, int y, COLORREF boundaryvalue, COLORREF newvalue)
{

	int x0,xl,xr,y0,xid;
	int flag,xnextspan;
	
	stack<CPoint> s;//��ջ
	CPoint p;
	s.push(CPoint(x,y));//��һ��������ջ
	while (!s.empty())//��ջ��Ϊ��
	{
	p = s.top();
	s.pop();//ȡջ��Ԫ�ز���ջ
	pDC->SetPixel(p.x,p.y,newvalue);//�������ص�Ϊָ����ɫ
	x = p.x;y = p.y;
	x0 =x + 1;
	while (pDC->GetPixel(x0,y) != boundaryvalue)//����ҷ�Ԫ��
	{
	pDC->SetPixel(x0,y,newvalue);
	x0++;
	}
	xr = x0 -1;//���ұ�����
	x0 = x -1;
	while (pDC->GetPixel(x0,y) != boundaryvalue)//���������
	{
	pDC->SetPixel(x0,y,newvalue);
	x0--;
	}
	xl = x0 + 1;//���������
	//�����һ������һ��ɨ���ߣ������ڱ߽���δ��������
	//��ѡȡ������������������������ջ
	y0 = y;
	for (int i=1;i>=-1;i-=2)
	{
	x0 = xr;
	y = y0 + i;//�����һ�к���һ��
	while (x0 >= xl)
	{
	flag = 0;
	while ((pDC->GetPixel(x0,y) != boundaryvalue)
	&& (pDC->GetPixel(x0,y) != newvalue)
	&& (x0 > xl))
	{
	if (flag == 0)
	{
	flag = 1;
	xid = x0;
	}
	x0--;
	}
	if (flag == 1)
	{
	s.push(CPoint(xid,y));//��������ջ
	flag = 0;
	}
	xnextspan = x0;
	while ((pDC->GetPixel(x0,y) == boundaryvalue)
	|| (pDC->GetPixel(x0,y) == newvalue)
	&& (x0 >= xl))
	x0--;
	if (xnextspan == x0) x0--;
	}
	}
	}

}
