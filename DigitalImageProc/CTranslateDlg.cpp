// CTranslateDlg.cpp: 实现文件
//

#include "pch.h"
#include "DigitalImageProc.h"
#include "CTranslateDlg.h"
#include "afxdialogex.h"


// CTranslateDlg 对话框

IMPLEMENT_DYNAMIC(CTranslateDlg, CDialog)

CTranslateDlg::CTranslateDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_TranslateDlg, pParent)
	, transY(0)
	, transX(0)
{

}

CTranslateDlg::~CTranslateDlg()
{
}

void CTranslateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, transY);
	DDX_Text(pDX, IDC_EDIT3, transX);
}


BEGIN_MESSAGE_MAP(CTranslateDlg, CDialog)
END_MESSAGE_MAP()


// CTranslateDlg 消息处理程序
