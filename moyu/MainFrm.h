
// MainFrm.h : CMainFrame ��Ľӿ�
//

#pragma once

//�Զ�����Ϣ
#define NM_SHOWIMG (WM_USER + 100)
#define NM_GRAYIMG (WM_USER + 101)
#define NM_BINARYIMG (WM_USER + 102)

class CMainFrame : public CFrameWnd
{
	
protected: // �������л�����
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// ����
public:

// ����
public:

// ��д
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// ʵ��
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // �ؼ���Ƕ���Ա
	CStatusBar        m_wndStatusBar;

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

private:
	CSplitterWnd m_spliter;			//�зִ��������
	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnMainExit();
	afx_msg void OnChangeShowTyle();
	afx_msg void OnUpdateChangeShowTyle(CCmdUI *pCmdUI);
};


