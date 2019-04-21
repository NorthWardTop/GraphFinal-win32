
// MFCGraph1View.h : CMFCGraph1View 类的接口
//

#pragma once


class CMFCGraph1View : public CView
{
protected: // 仅从序列化创建
	CMFCGraph1View();
	DECLARE_DYNCREATE(CMFCGraph1View)

// 特性
public:
	CMFCGraph1Doc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CMFCGraph1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	// 画线
	void draw(int x1, int y1, int x2, int y2, CDC* pDC);
	void DDALine(int x1, int y1, int x2, int y2, CDC* pDC);
	void bresLine(int x1, int y1, int x2, int y2, CDC* pDC);
	void midBresLine(int x1, int y1, int x2, int y2, CDC* pDC);
	void midBresCircle(int x0, int y0, int r, CDC* pDC);
	void midBresEllipse(int x0, int y0, int a, int b, CDC* pDC);
	void glRect(int x0, int y0, int x1, int y1, CDC* pDC);
	void drawCoorSys(CDC* pDC);
};

#ifndef _DEBUG  // MFCGraph1View.cpp 中的调试版本
inline CMFCGraph1Doc* CMFCGraph1View::GetDocument() const
   { return reinterpret_cast<CMFCGraph1Doc*>(m_pDocument); }
#endif

