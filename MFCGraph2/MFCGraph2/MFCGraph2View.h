
// MFCGraph2View.h : CMFCGraph2View ��Ľӿ�
//

#pragma once


class CMFCGraph2View : public CView
{
protected: // �������л�����
	CMFCGraph2View();
	DECLARE_DYNCREATE(CMFCGraph2View)

// ����
public:
	CMFCGraph2Doc* GetDocument() const;

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
	virtual ~CMFCGraph2View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()

public:
	void moveEllipse(int x0, int y0, int x1, int y1, CDC* pDC);//��Բ��ƽ��
	void rateEllipse(int x0, int y0, int x1, int y1, CDC* pDC); //��Բ�ı����任
	void symmRect(int x0, int y0, int x1, int y1, CDC* pDC);
	void compRect(CPoint p0, CPoint p1, int sX, float bY, CDC* pDC);
};

#ifndef _DEBUG  // MFCGraph2View.cpp �еĵ��԰汾
inline CMFCGraph2Doc* CMFCGraph2View::GetDocument() const
   { return reinterpret_cast<CMFCGraph2Doc*>(m_pDocument); }
#endif

