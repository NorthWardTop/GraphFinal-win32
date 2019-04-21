
// MFCGraph2View.cpp : CMFCGraph2View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCGraph2View 构造/析构

CMFCGraph2View::CMFCGraph2View()
{
	// TODO:  在此处添加构造代码

}

CMFCGraph2View::~CMFCGraph2View()
{
}

BOOL CMFCGraph2View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCGraph2View 绘制
void CMFCGraph2View::OnDraw(CDC* pDC)
{
	CMFCGraph2Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	OnBeginPrinting(pDC, NULL);
	//moveEllipse(30, 30, 200, 200, pDC);//平移变换
	//rateEllipse(-30, 30, -200, 200, pDC);
	symmRect(-200, -100, -300, -200,pDC);
	CPoint p0 = { 0, 0 }, p1 = { 100, -100 };
	compRect(p0, p1, 2, 1.5, pDC);
}


// CMFCGraph2View 打印

BOOL CMFCGraph2View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCGraph2View::OnBeginPrinting(CDC* pDC, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加额外的打印前进行的初始化过程
	//画坐标系
	//获取视图窗口大小
	CRect wndSize;
	this->GetClientRect(&wndSize);
	pDC->SetMapMode(4);//修改映射模式
	pDC->SetViewportOrg(\
		wndSize.right / 2, wndSize.bottom / 2);//设置视图逻辑原点

	//画坐标系x
	pDC->MoveTo(-wndSize.right / 2, 0);
	pDC->LineTo(wndSize.right / 2, 0);
	//箭头
	pDC->MoveTo(wndSize.right / 2, 0);
	pDC->LineTo((wndSize.right / 2) - 10, 10);
	//画坐标系y
	pDC->MoveTo(0, -wndSize.bottom / 2);
	pDC->LineTo(0, wndSize.bottom / 2);
	//箭头
	pDC->MoveTo(0, wndSize.bottom / 2);
	pDC->LineTo(-10, wndSize.bottom / 2 - 10);
}

void CMFCGraph2View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMFCGraph2View 诊断

#ifdef _DEBUG
void CMFCGraph2View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCGraph2View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCGraph2Doc* CMFCGraph2View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCGraph2Doc)));
	return (CMFCGraph2Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCGraph2View 消息处理程序
/*
（3）编写平移、比例、错切、对称变换的函数
（4）编写关于平移、比例、错切变换复合变换函数。
*/

//椭圆的平移变换
void CMFCGraph2View::moveEllipse(int x0, int y0, int x1, int y1, CDC* pDC)
{
	pDC->TextOut(x0, y0, L"椭圆的平移变换");
	pDC->Ellipse(x0, y0, x1, y1);
	pDC->TextOut(x0+300, y0+200, L"平移300,200后");
	pDC->Ellipse(x0+300, y0+200, x1+300, y1+200);
}

//椭圆的比例变换
void CMFCGraph2View::rateEllipse(int x0, int y0, int x1, int y1, CDC* pDC)
{
	int Sx=2 , Sy = 2;
	pDC->TextOut(x0*Sx, y0*Sy, L"椭圆的比例变换");
	pDC->Ellipse(x0, y0, x1, y1);
	pDC->TextOut(x0*Sx*Sx, y0*Sy*Sy, L"比例变化Sx,Sy后");
	pDC->Ellipse(x0*Sx, y0*Sy, x1*Sx, y1*Sy);
}

//矩形的对称变换
void CMFCGraph2View::symmRect(int x0, int y0, int x1, int y1, CDC* pDC)
{
	pDC->TextOut(x0, y0, L"矩形的对称变换前");
	pDC->Rectangle(x0, y0, x1, y1);
	pDC->TextOut(-x0, -y0, L"矩形的对称变换后");
	pDC->Rectangle(-x0, -y0, -x1, -y1);
}

//矩形的复合变换(先将x比例, 再将y错切)
void CMFCGraph2View::compRect(CPoint p0, CPoint p1, int sX, float bY, CDC* pDC)
{
	pDC->TextOut(p0.x+p1.x,p0.y, L"矩形的比例变换前");
	pDC->Rectangle(p0.x,p0.y,p1.x,p1.y);
	pDC->TextOut(p0.x*sX+p1.x*2, p0.y-150 , L"比例变化sX后");
	pDC->Rectangle(p0.x*sX, p0.y-150, p1.x*sX, p1.y-150);//为显示区别, 需要平移
	pDC->TextOut((p0.x*sX + 210)*bY, (p1.y - 150), L"错切变换后");
	pDC->Rectangle((p0.x*sX+210)*bY, (p0.y - 150), (p1.x*sX+210)*bY, (p1.y - 150));
}



