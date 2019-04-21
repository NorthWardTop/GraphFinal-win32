
// MFCGraph3View.h : CMFCGraph3View ��Ľӿ�
//

#pragma once


class CMFCGraph3View : public CView
{
protected: // �������л�����
	CMFCGraph3View();
	DECLARE_DYNCREATE(CMFCGraph3View)

// ����
public:
	CMFCGraph3Doc* GetDocument() const;

// ����
public:
	void ScanlineSeedfill(CDC *pDC, int x, int y, COLORREF boundaryvalue, COLORREF newvalue);
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
	virtual ~CMFCGraph3View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // MFCGraph3View.cpp �еĵ��԰汾
inline CMFCGraph3Doc* CMFCGraph3View::GetDocument() const
   { return reinterpret_cast<CMFCGraph3Doc*>(m_pDocument); }
#endif

