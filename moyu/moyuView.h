
// moyuView.h : CmoyuView ��Ľӿ�
//

#pragma once


class CmoyuView : public CView
{
protected: // �������л�����
	CmoyuView();
	DECLARE_DYNCREATE(CmoyuView)

// ����
public:
	CmoyuDoc* GetDocument() const;

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
	virtual ~CmoyuView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // moyuView.cpp �еĵ��԰汾
inline CmoyuDoc* CmoyuView::GetDocument() const
   { return reinterpret_cast<CmoyuDoc*>(m_pDocument); }
#endif

