// ScanDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "shipyy.h"
#include "ScanDlg.h"
#include "afxdialogex.h"


// CScanDlg 对话框

IMPLEMENT_DYNAMIC(CScanDlg, CDialogEx)

CScanDlg::CScanDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_SCAN, pParent)
{

}

CScanDlg::~CScanDlg()
{
}

void CScanDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CScanDlg, CDialogEx)
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CScanDlg 消息处理程序


BOOL CScanDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: Add extra initialization here
	//取得查询显示器控件的接口指针
	m_ViewerWnd = GetDlgItem(IDC_GRPRINTVIEWER1);
	LPUNKNOWN spUnk = m_ViewerWnd->GetControlUnknown();
	spUnk->QueryInterface(__uuidof(IGRPrintViewer), (void**)(&m_pPrintViewer));
	ATLASSERT(m_pPrintViewer != NULL);



	//创建报表主对象
	m_pGridppReport.CreateInstance(__uuidof(GridppReport));
	ATLASSERT(m_pGridppReport != NULL);
	m_pGridppReport->Utility->SetSkin(234, 234, 255, 1);



	HINSTANCE hinstance = AfxGetInstanceHandle();
	// 读取资源包文件  
	HRSRC hRsrc = FindResource(hinstance, MAKEINTRESOURCE(IDR_REPORT3), _T("REPORT"));


	//获取资源的大小  
	DWORD dwSize = SizeofResource(hinstance, hRsrc);


	//加载资源  
	HGLOBAL hGlobal = LoadResource(hinstance, hRsrc);
	//if (NULL == hGlobal)
	//	return FALSE;
	//锁定资源  
	LPVOID pBuffer = LockResource(hGlobal);

	// 这里转换为BYTE*，根据自己业务需要，也可转换为其它类型  
	BYTE* pByte = new BYTE[dwSize + 1];
	memcpy(pByte, pBuffer, dwSize);

	GlobalUnlock(hGlobal);
	// 读取资源到此结束，
 
	m_pGridppReport->LoadFromMemory(pByte, dwSize);

	delete[] pByte;
	pByte = NULL;

	for (MapStr::iterator iter = m_reportData.begin(); iter != m_reportData.end(); iter++) 
	{
		LPCWSTR k = (*iter).first.GetString();
		LPCWSTR v = (*iter).second.GetString();
		m_pGridppReport->ParameterByName(k)->AsString = v;
	}

	//m_pGridppReport->ParameterByName("shipname")->AsString = "哈哈哈";

	//查询显示器控件关联报表主对象
	m_pPrintViewer->Report = m_pGridppReport;
	

	//启动查询显示器的运行
	m_pPrintViewer->Start();

	//AdjustViewerSize();
	ShowWindow(SW_MAXIMIZE);

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}



 CString CScanDlg::GetInstallPath(void)
{
	TCHAR FileName[MAX_PATH];
	GetModuleFileName(NULL, FileName, MAX_PATH);
	::CharLower(FileName);
	CString path(FileName);
	return path;
};


void CScanDlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	AdjustViewerSize();
}


void CScanDlg::AdjustViewerSize()
{
	CWnd *pDispalyViewerWnd = GetDlgItem(IDC_GRPRINTVIEWER1);
	if (pDispalyViewerWnd)
	{
		RECT ClientRect;
		GetClientRect(&ClientRect);
		pDispalyViewerWnd->MoveWindow(&ClientRect, FALSE);
	}
}
