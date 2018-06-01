
// shipyyDlg.h: 头文件
//

#pragma once
#include "afxcmn.h"


// CshipyyDlg 对话框
class CshipyyDlg : public CDialog
{
// 构造
public:
	CshipyyDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SHIPYY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTestcon();
	// 航次
	CString m_hc;
	// 品名
	CString m_pm;
	// 装港
	CString m_zg;
	// 卸港
	CString m_xg;
	// 列表
	CListCtrl m_list;
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnBnClickedButtonAdd();

	afx_msg void OnNMDblclkListResult(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMClickListResult(NMHDR *pNMHDR, LRESULT *pResult);
};
