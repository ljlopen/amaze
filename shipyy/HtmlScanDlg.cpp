// HtmlScanDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "shipyy.h"
#include "HtmlScanDlg.h"


// CHtmlScanDlg �Ի���

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
	SetHostFlags(DOCHOSTUIFLAG_FLAT_SCROLLBAR | DOCHOSTUIFLAG_NO3DBORDER);//������ CDHtmlDialog::OnInitDialog();֮ǰ
	CDHtmlDialog::OnInitDialog();
	m_pBrowserApp->put_Silent(VARIANT_TRUE);//���ξ�����ʾ

	//this->SetElementText(_T("shipname"), "11111111111");
	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BEGIN_MESSAGE_MAP(CHtmlScanDlg, CDHtmlDialog)
END_MESSAGE_MAP()

BEGIN_DHTML_EVENT_MAP(CHtmlScanDlg)
	DHTML_EVENT_ONCLICK(_T("ButtonOK"), OnButtonOK)
	DHTML_EVENT_ONCLICK(_T("ButtonCancel"), OnButtonCancel)
END_DHTML_EVENT_MAP()



// CHtmlScanDlg ��Ϣ�������

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
