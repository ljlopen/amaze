#pragma once

#ifdef _WIN32_WCE
#error "Windows CE ��֧�� CDHtmlDialog��"
#endif 

// CHtmlScanDlg �Ի���

class CHtmlScanDlg : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CHtmlScanDlg)

public:
	CHtmlScanDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CHtmlScanDlg();
// ��д
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HTML_SCAN, IDH = IDR_HTML_HTMLSCANDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
