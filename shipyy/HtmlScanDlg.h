#pragma once

#ifdef _WIN32_WCE
#error "Windows CE 不支持 CDHtmlDialog。"
#endif 

// CHtmlScanDlg 对话框

class CHtmlScanDlg : public CDHtmlDialog
{
	DECLARE_DYNCREATE(CHtmlScanDlg)

public:
	CHtmlScanDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHtmlScanDlg();
// 重写
	HRESULT OnButtonOK(IHTMLElement *pElement);
	HRESULT OnButtonCancel(IHTMLElement *pElement);

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_HTML_SCAN, IDH = IDR_HTML_HTMLSCANDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()
	DECLARE_DHTML_EVENT_MAP()
};
