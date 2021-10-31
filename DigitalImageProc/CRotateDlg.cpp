// CRotateDlg.cpp: 实现文件
//

#include "pch.h"
#include "DigitalImageProc.h"
#include "CRotateDlg.h"
#include "afxdialogex.h"


// CRotateDlg 对话框

IMPLEMENT_DYNAMIC(CRotateDlg, CDialog)

CRotateDlg::CRotateDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_RotateDlg, pParent)
	, centerX(0)
	, centerY(0)
	, theta(0)
	, pDoc(NULL)
{
}

CRotateDlg::~CRotateDlg()
{
}

void CRotateDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, centerX);
	DDX_Text(pDX, IDC_EDIT3, centerY);
	DDX_Text(pDX, IDC_EDIT4, theta);
}


BEGIN_MESSAGE_MAP(CRotateDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CRotateDlg::OnBnClickedSetX)
	ON_BN_CLICKED(IDC_BUTTON2, &CRotateDlg::OnBnClickedSetY)
END_MESSAGE_MAP()


// CRotateDlg 消息处理程序


void CRotateDlg::OnBnClickedSetX()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pDoc->pSrcImgData != NULL) 
		centerX = 1.0 * pDoc->pSrcImgData->GetWidth() / 2;
	CString str;
	str.Format(_T("%.1lf"), centerX);
	this->SetDlgItemTextW(IDC_EDIT1, str);
}


void CRotateDlg::OnBnClickedSetY()
{
	// TODO: 在此添加控件通知处理程序代码
	if (pDoc->pSrcImgData != NULL)
		centerY = 1.0 * pDoc->pSrcImgData->GetHeight() / 2;
	CString str;
	str.Format(_T("%.1lf"), centerY);
	this->SetDlgItemTextW(IDC_EDIT3, str);
}
