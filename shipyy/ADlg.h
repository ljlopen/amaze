#pragma once


// CADlg �Ի���

class CADlg : public CDialogEx
{
	DECLARE_DYNAMIC(CADlg)

public:
	CADlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CADlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_ADD };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
