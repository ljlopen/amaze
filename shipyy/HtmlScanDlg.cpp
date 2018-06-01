// HtmlScanDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "shipyy.h"
#include "HtmlScanDlg.h"


// CHtmlScanDlg 对话框

IMPLEMENT_DYNCREATE(CHtmlScanDlg, CDHtmlDialog)

CHtmlScanDlg::CHtmlScanDlg(CWnd* pParent /*=NULL*/)
	: CDHtmlDialog(IDD_DIALOG_HTML_SCAN, IDR_HTML_HTMLSCANDLG, pParent)
{

}

CHtmlScanDlg::~CHtmlScanDlg()
{
}

void CHtmlScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDHtmlDialog::DoDataExchange(pDX);
}

BOOL CHtmlScanDlg::OnInitDialog()
{
	SetHostFlags(DOCHOSTUIFLAG_FLAT_SCROLLBAR | DOCHOSTUIFLAG_NO3DBORDER);//必须在 CDHtmlDialog::OnInitDialog();之前
	CDHtmlDialog::OnInitDialog();
	m_pBrowserApp->put_Silent(VARIANT_TRUE);//屏蔽警告提示

	//this->SetElementText(_T("shipname"), "11111111111");
	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

BEGIN_MESSAGE_MAP(CHtmlScanDlg, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CHtmlScanDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// CHtmlScanDlg 消息处理程序

HRESULT CHtmlScanDlg::OnButtonOK(IHTMLElement* /*pElement*/)
{
	OnOK();
	return S_OK;
}

HRESULT CHtmlScanDlg::OnButtonCancel(IHTMLElement* /*pElement*/)
{
	OnCancel();
	return S_OK;
}
