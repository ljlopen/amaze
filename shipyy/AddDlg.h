#pragma once


// CAddDlg 对话框

class CAddDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CAddDlg)

public:
	CAddDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAddDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	// 船名
	CString m_shipname;
	// 航次
	CString m_hc;
	// 装港
	CString m_zg;
	// 装港时间
	CString m_zgsj;
	// 装港是否启用船吊
	BOOL m_zgcd;
	// 卸港
	CString m_xg;
	// 卸港在港时间
	CString m_xgsj;
	// 卸港是否启用船吊
	BOOL m_xgcd;
	// port information
	CString m_portinfo;
	// laycan
	CString m_laycan;
	// 品名
	CString m_pm;
	// 合同
	CString m_ht;
	afx_msg void OnBnClickedBtnSave();
	virtual BOOL OnInitDialog();
	// id
	int m_id;
	// 归档标记
	CString m_gd_bj;
};
