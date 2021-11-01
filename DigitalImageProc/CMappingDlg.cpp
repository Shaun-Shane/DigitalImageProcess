// CMappingDlg.cpp: 实现文件
//

#include "pch.h"
#include "DigitalImageProc.h"
#include "CMappingDlg.h"
#include "afxdialogex.h"


// CMappingDlg 对话框

IMPLEMENT_DYNAMIC(CMappingDlg, CDialog)

CMappingDlg::CMappingDlg(CWnd* pParent /*=nullptr*/)
	: CDialog(IDD_MappingDlg, pParent)
	, fileName(_T(""))
	, wndPos(0)
	, wndLen(0)
{

}

CMappingDlg::~CMappingDlg()
{
}

void CMappingDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT2, fileName);
	DDX_Text(pDX, IDC_EDIT1, wndPos);
	DDX_Text(pDX, IDC_EDIT3, wndLen);
}


BEGIN_MESSAGE_MAP(CMappingDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &CMappingDlg::OnBnClickedUpload)
END_MESSAGE_MAP()


// CMappingDlg 消息处理程序


void CMappingDlg::OnBnClickedUpload()
{
	// TODO: 在此添加控件通知处理程序代码
	LPCTSTR szFilter = _T("||");
	CFileDialog dlgBKFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	CString strBKFileName;

	if (dlgBKFile.DoModal() == IDOK)
		strBKFileName = dlgBKFile.GetPathName();
	else
		return;
	fileName = strBKFileName;
	this->SetDlgItemTextW(IDC_EDIT2, fileName);
}
