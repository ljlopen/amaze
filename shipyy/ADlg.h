#pragma once


// CADlg 对话框

class CADlg : public CDialogEx
{
	DECLARE_DYNAMIC(CADlg)

public:
	CADlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CADlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
