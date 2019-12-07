
// MainFrm.h : CMainFrame 类的接口
//

#pragma once

//自定义消息
#define NM_SHOWIMG (WM_USER + 100)
#define NM_GRAYIMG (WM_USER + 101)
#define NM_BINARYIMG (WM_USER + 102)

class CMainFrame : public CFrameWnd
{
	
protected: // 仅从序列化创建
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 实现
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // 控件条嵌入成员
	CStatusBar        m_wndStatusBar;

// 生成的消息映射函数
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

private:
	CSplitterWnd m_spliter;			//切分窗口类对象
	afx_msg LRESULT OnMyChange(WPARAM wParam, LPARAM lParam);
public:
	afx_msg void OnMainExit();
	afx_msg void OnChangeShowTyle();
	afx_msg void OnUpdateChangeShowTyle(CCmdUI *pCmdUI);
};


