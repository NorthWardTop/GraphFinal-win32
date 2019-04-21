
// MFCGraph3View.h : CMFCGraph3View 类的接口
//

#pragma once


class CMFCGraph3View : public CView
{
protected: // 仅从序列化创建
	CMFCGraph3View();
	DECLARE_DYNCREATE(CMFCGraph3View)

// 特性
public:
	CMFCGraph3Doc* GetDocument() const;

// 操作
public:
	void ScanlineSeedfill(CDC *pDC, int x, int y, COLORREF boundaryvalue, COLORREF newvalue);
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
	virtual ~CMFCGraph3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFCGraph3View.cpp 中的调试版本
inline CMFCGraph3Doc* CMFCGraph3View::GetDocument() const
   { return reinterpret_cast<CMFCGraph3Doc*>(m_pDocument); }
#endif

