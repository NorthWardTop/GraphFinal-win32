
// MFCGraph3View.cpp : CMFCGraph3View 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
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
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
END_MESSAGE_MAP()

// CMFCGraph3View 构造/析构

CMFCGraph3View::CMFCGraph3View()
{
	// TODO:  在此处添加构造代码

}

CMFCGraph3View::~CMFCGraph3View()
{
}

BOOL CMFCGraph3View::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO:  在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CMFCGraph3View 绘制

void CMFCGraph3View::OnDraw(CDC* pDC)
{
	CMFCGraph3Doc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO:  在此处为本机数据添加绘制代码
	OnBeginPrinting(pDC, NULL);
	ScanlineSeedfill(pDC, 30, 40, RGB(255, 0, 0), RGB(0, 255, 0));
}


// CMFCGraph3View 打印

BOOL CMFCGraph3View::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CMFCGraph3View::OnBeginPrinting(CDC* pDC, CPrintInfo* /*pInfo*/)
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

void CMFCGraph3View::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO:  添加打印后进行的清理过程
}


// CMFCGraph3View 诊断

#ifdef _DEBUG
void CMFCGraph3View::AssertValid() const
{
	CView::AssertValid();
}

void CMFCGraph3View::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CMFCGraph3Doc* CMFCGraph3View::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CMFCGraph3Doc)));
	return (CMFCGraph3Doc*)m_pDocument;
}
#endif //_DEBUG


// CMFCGraph3View 消息处理程序
void CMFCGraph3View::ScanlineSeedfill(CDC *pDC, int x, int y, COLORREF boundaryvalue, COLORREF newvalue)
{

	int x0,xl,xr,y0,xid;
	int flag,xnextspan;
	
	stack<CPoint> s;//堆栈
	CPoint p;
	s.push(CPoint(x,y));//第一个种子入栈
	while (!s.empty())//堆栈不为空
	{
	p = s.top();
	s.pop();//取栈顶元素并弹栈
	pDC->SetPixel(p.x,p.y,newvalue);//绘制像素点为指定颜色
	x = p.x;y = p.y;
	x0 =x + 1;
	while (pDC->GetPixel(x0,y) != boundaryvalue)//填充右方元素
	{
	pDC->SetPixel(x0,y,newvalue);
	x0++;
	}
	xr = x0 -1;//最右边像素
	x0 = x -1;
	while (pDC->GetPixel(x0,y) != boundaryvalue)//填充左方像素
	{
	pDC->SetPixel(x0,y,newvalue);
	x0--;
	}
	xl = x0 + 1;//最左边像素
	//检查上一条和下一条扫描线，若存在边界且未填充的像素
	//则选取代表各连续区间的种子像素入栈
	y0 = y;
	for (int i=1;i>=-1;i-=2)
	{
	x0 = xr;
	y = y0 + i;//获得上一行和下一行
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
	s.push(CPoint(xid,y));//新种子入栈
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
