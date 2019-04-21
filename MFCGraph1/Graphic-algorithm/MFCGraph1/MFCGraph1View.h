
// MFCGraph1View.h : CMFCGraph1View ��Ľӿ�
//

#pragma once


class CMFCGraph1View : public CView
{
protected: // �������л�����
	CMFCGraph1View();
	DECLARE_DYNCREATE(CMFCGraph1View)

// ����
public:
	CMFCGraph1Doc* GetDocument() const;

// ����
public:

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CMFCGraph1View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
public:
	// ����
	void draw(int x1, int y1, int x2, int y2, CDC* pDC);
	void DDALine(int x1, int y1, int x2, int y2, CDC* pDC);
	void bresLine(int x1, int y1, int x2, int y2, CDC* pDC);
	void midBresLine(int x1, int y1, int x2, int y2, CDC* pDC);
	void midBresCircle(int x0, int y0, int r, CDC* pDC);
	void midBresEllipse(int x0, int y0, int a, int b, CDC* pDC);
	void glRect(int x0, int y0, int x1, int y1, CDC* pDC);
	void drawCoorSys(CDC* pDC);
};

#ifndef _DEBUG  // MFCGraph1View.cpp �еĵ��԰汾
inline CMFCGraph1Doc* CMFCGraph1View::GetDocument() const
   { return reinterpret_cast<CMFCGraph1Doc*>(m_pDocument); }
#endif

