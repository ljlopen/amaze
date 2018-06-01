// ADlg.cpp : 实现文件
//

#include "stdafx.h"
#include "shipyy.h"
#include "ADlg.h"
#include "afxdialogex.h"


// CADlg 对话框

IMPLEMENT_DYNAMIC(CADlg, CDialogEx)

CADlg::CADlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_DIALOG_ADD, pParent)
{

}

CADlg::~CADlg()
{
}

void CADlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CADlg, CDialogEx)
END_MESSAGE_MAP()


// CADlg 消息处理程序
