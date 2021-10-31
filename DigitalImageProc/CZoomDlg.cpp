// CZoomDlg.cpp: 实现文件
//

#include "pch.h"
#include "DigitalImageProc.h"
#include "CZoomDlg.h"
#include "afxdialogex.h"


// CZoomDlg 对话框

IMPLEMENT_DYNAMIC(CZoomDlg, CDialog)

CZoomDlg::CZoomDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_DIALOG1, pParent)
	, ratio(0)
{

}

CZoomDlg::~CZoomDlg()
{
}

void CZoomDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, ratio);
}


BEGIN_MESSAGE_MAP(CZoomDlg, CDialog)
END_MESSAGE_MAP()


// CZoomDlg 消息处理程序
