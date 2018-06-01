// AddDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "shipyy.h"
#include "AddDlg.h"
#include "afxdialogex.h"


// CAddDlg 对话框

IMPLEMENT_DYNAMIC(CAddDlg, CDialogEx)

CAddDlg::CAddDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
	, m_shipname(_T(""))
	, m_hc(_T(""))
	, m_zg(_T(""))
	, m_zgsj(_T(""))
	, m_zgcd(FALSE)
	, m_xg(_T(""))
	, m_xgsj(_T(""))
	, m_xgcd(FALSE)
	, m_portinfo(_T(""))
	, m_laycan(_T(""))
	, m_pm(_T(""))
	, m_ht(_T(""))
	, m_id(0)
	, m_gd_bj(_T(""))
{

}

CAddDlg::~CAddDlg()
{
}

void CAddDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_shipname);
	DDX_Text(pDX, IDC_EDIT2, m_hc);
	DDX_Text(pDX, IDC_EDIT3, m_zg);
	DDX_Text(pDX, IDC_EDIT4, m_zgsj);
	DDX_Check(pDX, IDC_CHECK1, m_zgcd);
	DDX_Text(pDX, IDC_EDIT5, m_xg);
	DDX_Text(pDX, IDC_EDIT6, m_xgsj);
	DDX_Check(pDX, IDC_CHECK2, m_xgcd);
	DDX_Text(pDX, IDC_EDIT10, m_portinfo);
	DDX_Text(pDX, IDC_EDIT7, m_laycan);
	DDX_Text(pDX, IDC_EDIT8, m_pm);
	DDX_Text(pDX, IDC_EDIT9, m_ht);
}


BEGIN_MESSAGE_MAP(CAddDlg, CDialogEx)
	ON_BN_CLICKED(ID_BTN_SAVE, &CAddDlg::OnBnClickedBtnSave)
END_MESSAGE_MAP()


// CAddDlg 消息处理程序





void CAddDlg::OnBnClickedBtnSave()
{
	UpdateData();

	if (m_id == 0) 
	{
		if (m_shipname.GetLength() <= 0 || m_hc.GetLength() <= 0) {
			AfxMessageBox(_T("船名和航次必录!"));
			return;
		}

		sql::Connection *con = CDbUtil::getConnection();
		CString sql = _T("INSERT INTO `shipyy` ( `shipname`, `hc`, `zg`, `zgsj`, `zgcdbj`, `xg`, `xgsj`, `xgcdbj`, `laycan`, `pm`, `ht`, `portinfo`, `cdate`, `gd_bj`) VALUES(?, ?, ?, ?, ?, ?,  ?, ?, ?, ?, ?, ? , now(), ?);");
		sql::PreparedStatement* pstmt = con->prepareStatement(sql::SQLString(CW2A(sql.GetString())));

	
		pstmt->setString(1, sql::SQLString(Unicode2Utf8((char*)m_shipname.GetString())));
		pstmt->setString(2, sql::SQLString(Unicode2Utf8((char*)m_hc.GetString())));
		pstmt->setString(3, sql::SQLString(Unicode2Utf8((char*)m_zg.GetString())));
		pstmt->setString(4, sql::SQLString(Unicode2Utf8((char*)m_zgsj.GetString())));
		pstmt->setString(5, m_zgcd ? "1" : "0");
		pstmt->setString(6, sql::SQLString(Unicode2Utf8((char*)m_xg.GetString())));
		pstmt->setString(7, sql::SQLString(Unicode2Utf8((char*)m_xgsj.GetString())));
		pstmt->setString(8, m_xgcd ? "1" : "0");
		pstmt->setString(9, sql::SQLString(Unicode2Utf8((char*)m_laycan.GetString())));
		pstmt->setString(10, sql::SQLString(Unicode2Utf8((char*)m_pm.GetString())));
		pstmt->setString(11, sql::SQLString(Unicode2Utf8((char*)m_ht.GetString())));
		pstmt->setString(12, sql::SQLString(Unicode2Utf8((char*)m_portinfo.GetString())));
		pstmt->setString(13, "0");
		pstmt->executeUpdate();
		delete pstmt;
		delete con;
		AfxMessageBox(_T("保存成功!"));
		this->OnOK();
	}
	else 
	{ //更新

		if (m_shipname.GetLength() <= 0 || m_hc.GetLength() <= 0) {
			AfxMessageBox(_T("船名和航次必录!"));
			return;
		}
		sql::Connection *con = CDbUtil::getConnection();
		CString sql = _T("UPDATE `shipyy` SET `shipname`=?, `hc`=?, `zg`=?, `zgsj`=?, `zgcdbj`=?, `xg`=?, `xgsj`=?, `xgcdbj`=?, `laycan`=?, `pm`=?, `ht`=?, `portinfo`=? where id=?;");
		sql::PreparedStatement* pstmt = con->prepareStatement(sql::SQLString(CW2A(sql.GetString())));

		

		pstmt->setString(1, sql::SQLString(Unicode2Utf8((char*)m_shipname.GetString())));
		pstmt->setString(2, sql::SQLString(Unicode2Utf8((char*)m_hc.GetString())));
		pstmt->setString(3, sql::SQLString(Unicode2Utf8((char*)m_zg.GetString())));
		pstmt->setString(4, sql::SQLString(Unicode2Utf8((char*)m_zgsj.GetString())));
		pstmt->setString(5, m_zgcd ? "1" : "0");
		pstmt->setString(6, sql::SQLString(Unicode2Utf8((char*)m_xg.GetString())));
		pstmt->setString(7, sql::SQLString(Unicode2Utf8((char*)m_xgsj.GetString())));
		pstmt->setString(8, m_xgcd ? "1" : "0");
		pstmt->setString(9, sql::SQLString(Unicode2Utf8((char*)m_laycan.GetString())));
		pstmt->setString(10, sql::SQLString(Unicode2Utf8((char*)m_pm.GetString())));
		pstmt->setString(11, sql::SQLString(Unicode2Utf8((char*)m_ht.GetString())));
		pstmt->setString(12, sql::SQLString(Unicode2Utf8((char*)m_portinfo.GetString())));
		pstmt->setInt(13, m_id);
		pstmt->executeUpdate();
		delete pstmt;
		delete con;
		AfxMessageBox(_T("更新成功!"));
		this->OnOK();
	
	}
}


BOOL CAddDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

 
	UpdateData(FALSE);
	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
