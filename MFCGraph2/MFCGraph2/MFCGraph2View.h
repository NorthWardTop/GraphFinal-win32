
// MFCGraph2View.h : CMFCGraph2View 类的接口
//

#pragma once


class CMFCGraph2View : public CView
{
protected: // 仅从序列化创建
	CMFCGraph2View();
	DECLARE_DYNCREATE(CMFCGraph2View)

// 特性
public:
	CMFCGraph2Doc* GetDocument() const;

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
	virtual ~CMFCGraph2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

public:
	void moveEllipse(int x0, int y0, int x1, int y1, CDC* pDC);//椭圆的平移
	void rateEllipse(int x0, int y0, int x1, int y1, CDC* pDC); //椭圆的比例变换
	void symmRect(int x0, int y0, int x1, int y1, CDC* pDC);
	void compRect(CPoint p0, CPoint p1, int sX, float bY, CDC* pDC);
};

#ifndef _DEBUG  // MFCGraph2View.cpp 中的调试版本
inline CMFCGraph2Doc* CMFCGraph2View::GetDocument() const
   { return reinterpret_cast<CMFCGraph2Doc*>(m_pDocument); }
#endif

