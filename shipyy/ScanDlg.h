#pragma once
#include "resource.h"       // 主符号

// CScanDlg 对话框

typedef std::map<CString, CString> MapStr;
class CScanDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CScanDlg)

public:
	CScanDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CScanDlg();
	IGridppReportPtr m_pGridppReport;
	IGRPrintViewerPtr m_pPrintViewer;
	CWnd *m_ViewerWnd;
	std::map<CString, CString> m_reportData;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SCAN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void AdjustViewerSize();
	CString GetInstallPath(void);
};
