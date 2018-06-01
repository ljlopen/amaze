
// shipyyDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "shipyy.h"
#include "shipyyDlg.h"
#include "afxdialogex.h"

#include <stdlib.h>
#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include "AddDlg.h"
#include "ScanDlg.h"
#include "HtmlScanDlg.h"

using namespace std;

#include "CDbUtil.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CshipyyDlg 对话框



CshipyyDlg::CshipyyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_SHIPYY_DIALOG, pParent)
	, m_hc(_T(""))
	, m_pm(_T(""))
	, m_zg(_T(""))
	, m_xg(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CshipyyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_HC, m_hc);
	DDX_Text(pDX, IDC_EDIT_PM, m_pm);
	DDX_Text(pDX, IDC_EDIT_ZG, m_zg);
	DDX_Text(pDX, IDC_EDIT_XG, m_xg);
	DDX_Control(pDX, IDC_LIST_RESULT, m_list);
}

BEGIN_MESSAGE_MAP(CshipyyDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_TESTCON, &CshipyyDlg::OnBnClickedButtonTestcon)
	ON_BN_CLICKED(IDC_BUTTON_SEARCH, &CshipyyDlg::OnBnClickedButtonSearch)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CshipyyDlg::OnBnClickedButtonAdd)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_RESULT, &CshipyyDlg::OnNMDblclkListResult)
	ON_NOTIFY(NM_CLICK, IDC_LIST_RESULT, &CshipyyDlg::OnNMClickListResult)
END_MESSAGE_MAP()


// CshipyyDlg 消息处理程序

BOOL CshipyyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标
	CString columns[7] = {_T("船名"),_T("航次"),_T("装港"),_T("卸港"),_T("品名"),_T("编辑"),_T("删除") };
	int widths[7] = { 300,150,150,150,200,100,100 };
	for (int i = 0; i < 7; i++) {
		m_list.InsertColumn(i, columns[i], LVCFMT_LEFT, widths[i]);
	}
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);

 
	m_list.ShowWindow(TRUE);
 

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CshipyyDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CshipyyDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CshipyyDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CshipyyDlg::OnBnClickedButtonTestcon()
{
 

	try {
		sql::Connection *con;
		sql::Statement *stmt;
		sql::ResultSet *res;

		con = CDbUtil::getConnection();
		stmt = con->createStatement();
		res = stmt->executeQuery("select '1' str");
		 
		if (res->first() && 0 == res->getString("str").compare("1"))
		{
			AfxMessageBox(_T("服务器正常连接！"));
			delete res;
			delete con;
			return;
		}
 
		delete res;
		delete con;

	}
	catch (sql::SQLException &e) {
		 
	}
	AfxMessageBox(_T("未能正常连接到服务器，请联系QQ:57694878！"));
}


void CshipyyDlg::OnBnClickedButtonSearch()
{
	UpdateData();
	this->SetDlgItemTextW(IDC_STATIC_MSG, _T("正在检索...."));
	m_list.DeleteAllItems();
	sql::Connection *con = CDbUtil::getConnection();

	CString sql = _T("select * from shipyy where gd_bj='0' ");
	if (m_hc.GetLength() > 0) 
	{
		sql.AppendFormat(_T(" and hc='%s'"), m_hc);
	}
	if (m_pm.GetLength() > 0)
	{
		sql.AppendFormat(_T(" and pm='%s'"), m_pm);
	}
	if (m_zg.GetLength() > 0)
	{
		sql.AppendFormat(_T(" and zg='%s'"), m_zg);
	}
	if (m_xg.GetLength() > 0)
	{
		sql.AppendFormat(_T(" and xg='%s'"), m_xg);
	}

	sql.Append(_T(" order by cdate desc"));
	sql::Statement *stmt;
	sql::ResultSet * res;
	stmt = con->createStatement();

	res = stmt->executeQuery(sql::SQLString(Unicode2Utf8((char *)sql.GetString())));
	int row = 0;
	while (res->next()) {
 
		sql::SQLString rowdata[7] = 
		{ res->getString("shipname"),
			res->getString("hc"),
			res->getString("zg"),
			res->getString("xg"),
			res->getString("pm"),
			Ansi2Utf8("编辑"),
			Ansi2Utf8("删除")
		 };
		int itemindex = m_list.InsertItem(row, CString(res->getString("id").c_str()));
		uint32_t id = res->getUInt("id");
		m_list.SetItemData(itemindex, (DWORD)id);
		for (int i = 0; i < 7; i++) {
			m_list.SetItemText(itemindex, i, CString(Utf82Ansi(rowdata[i].c_str())));
	
		}
		row++;
	}

	delete stmt;
	delete res;
	delete con;
	this->SetDlgItemTextW(IDC_STATIC_MSG, _T(""));
    
}


void CshipyyDlg::OnBnClickedButtonAdd()
{
	CAddDlg dlg(this);
	if (IDOK == dlg.DoModal()) 
	{
		OnBnClickedButtonSearch();
	}
}


void CshipyyDlg::OnNMDblclkListResult(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int row  = pNMItemActivate->iItem;
	if (row >= 0 && row<m_list.GetItemCount())//判断双击位置是否在有数据的列表项上面  
	{
		DWORD_PTR id = m_list.GetItemData(row);
	 

		std::map<CString, CString> reportData;
		CScanDlg scanDlg;
		sql::Connection *con = CDbUtil::getConnection();

		CString sql;
		sql.Format(_T("select shipname,hc,zg,zgsj,zgcdbj,xg,xgsj,xgcdbj,laycan,pm,ht,portinfo,cdate from shipyy where id=%d"), id);
		sql::Statement *stmt;
		sql::ResultSet * res;
		stmt = con->createStatement();

		res = stmt->executeQuery(sql::SQLString(CW2A(sql.GetString())));
		if (res->next()) {
			//reportData[_T("id")] = CString(Utf82Ansi(res->getString("id").c_str()));
			reportData[_T("shipname")] = CString(Utf82Ansi(res->getString("shipname").c_str()));
			reportData[_T("hc")] = CString(Utf82Ansi(res->getString("hc").c_str()));
			reportData[_T("zg")] = CString(Utf82Ansi(res->getString("zg").c_str()));
			reportData[_T("zgsj")] = CString(Utf82Ansi(res->getString("zgsj").c_str()));
			CString zgcdbj = _T("卸港不用船吊");
			if (0==res->getString("zgcdbj").compare("1"))
			{
				zgcdbj = _T("卸港启用船吊");
			}

			reportData[_T("zgcdbj")] = zgcdbj;
			reportData[_T("xg")] = CString(Utf82Ansi(res->getString("xg").c_str()));
			reportData[_T("xgsj")] = CString(Utf82Ansi(res->getString("xgsj").c_str()));
			CString xgcdbj = _T("卸港不用船吊");
			if (0 == res->getString("xgcdbj").compare("1"))
			{
				xgcdbj = _T("卸港启用船吊");
			}

			reportData[_T("xgcdbj")] = xgcdbj;
			reportData[_T("laycan")] = CString(Utf82Ansi(res->getString("laycan").c_str()));
			reportData[_T("pm")] = CString(Utf82Ansi(res->getString("pm").c_str()));
			reportData[_T("ht")] = CString(Utf82Ansi(res->getString("ht").c_str()));
			reportData[_T("portinfo")] = CString(Utf82Ansi(res->getString("portinfo").c_str()));
			CTime cdate(res->getInt("cdate"));
			CString strCdate = cdate.Format(_T("%Y-%m-%d %H:%M:%S"));
			reportData[_T("cdate")] = strCdate;
			//reportData[_T("gd_bj")] = CString(Utf82Ansi(res->getString("gd_bj").c_str()));
		  
		}

		delete stmt;
		delete res;
		delete con;
		scanDlg.m_reportData = reportData;
		scanDlg.DoModal();

	}
 
	*pResult = 0;
}


void CshipyyDlg::OnNMClickListResult(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	int row = pNMItemActivate->iItem;
	if (row >= 0 && row < m_list.GetItemCount())//判断双击位置是否在有数据的列表项上面  
	{
		if (pNMItemActivate->iSubItem == 6) {
			if (IDOK == AfxMessageBox(_T("确定要删除?"), MB_OKCANCEL)) {
				DWORD_PTR id = m_list.GetItemData(row);
				sql::Connection *con = CDbUtil::getConnection();

				CString sql;
				sql.Format(_T("update shipyy set gd_bj='1' where id=%d"), id);
				sql::Statement *stmt;
				sql::ResultSet * res;
				stmt = con->createStatement();
				stmt->executeUpdate(sql::SQLString(CW2A(sql.GetString())));

				delete stmt;
				delete con;
				OnBnClickedButtonSearch();
		  }
		}
		else if (pNMItemActivate->iSubItem == 5) { //编辑
			this->SetDlgItemTextW(IDC_STATIC_MSG, _T("正在查询数据...."));
			DWORD_PTR id = m_list.GetItemData(row);
 
			CAddDlg addDlg;
			sql::Connection *con = CDbUtil::getConnection();

			CString sql;
			sql.Format(_T("select id,gd_bj, shipname,hc,zg,zgsj,zgcdbj,xg,xgsj,xgcdbj,laycan,pm,ht,portinfo,cdate from shipyy where id=%d"), id);
			sql::Statement *stmt;
			sql::ResultSet * res;
			stmt = con->createStatement();

			res = stmt->executeQuery(sql::SQLString(CW2A(sql.GetString())));
			if (res->next()) {
				addDlg.m_id = res->getInt("id");
				addDlg.m_shipname = CString(Utf82Ansi(res->getString("shipname").c_str()));
				addDlg.m_gd_bj = CString(Utf82Ansi(res->getString("gd_bj").c_str()));

				addDlg.m_hc = CString(Utf82Ansi(res->getString("hc").c_str()));
				addDlg.m_zg = CString(Utf82Ansi(res->getString("zg").c_str()));
				addDlg.m_zgsj = CString(Utf82Ansi(res->getString("zgsj").c_str()));
				BOOL zgcdbj = FALSE;
				if (0 == res->getString("zgcdbj").compare("1"))
				{
					zgcdbj = TRUE;
				}
				addDlg.m_zgcd = zgcdbj;

				addDlg.m_xg = CString(Utf82Ansi(res->getString("xg").c_str()));
				addDlg.m_xgsj = CString(Utf82Ansi(res->getString("xgsj").c_str()));
				BOOL xgcdbj = FALSE;
				if (0 == res->getString("xgcdbj").compare("1"))
				{
					xgcdbj = TRUE;
				}
				addDlg.m_xgcd = xgcdbj;

				addDlg.m_laycan = CString(Utf82Ansi(res->getString("laycan").c_str()));
				addDlg.m_pm = CString(Utf82Ansi(res->getString("pm").c_str()));
				addDlg.m_ht = CString(Utf82Ansi(res->getString("ht").c_str()));
				addDlg.m_portinfo = CString(Utf82Ansi(res->getString("portinfo").c_str()));
			
			 
			 

			}

			delete stmt;
			delete res;
			delete con;
			this->SetDlgItemTextW(IDC_STATIC_MSG, _T(""));
			
			if (IDOK == addDlg.DoModal())
			{
				OnBnClickedButtonSearch();
			}
		}
		
	}
	*pResult = 0;
}
