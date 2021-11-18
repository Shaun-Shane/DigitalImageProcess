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
	, wndPos(2048)
	, wndLen(4096)
	, pDoc(NULL)
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
	ON_WM_DESTROY()
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


void CMappingDlg::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类
	wndPos = GetDlgItemInt(IDC_EDIT1);
	wndLen = GetDlgItemInt(IDC_EDIT3);
	GetDlgItemText(IDC_EDIT2, fileName);
	if (wndLen == 0) {
		AfxMessageBox(_T("窗宽不能为0!"));
		return;
	}
	pDoc->GrayMapping(fileName, wndPos, wndLen);
	//CDialog::OnOK();
}


void CMappingDlg::OnDestroy()
{
	CDialog::OnDestroy();
	delete this;
	// TODO: 在此处添加消息处理程序代码
}


void CMappingDlg::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类
	CDialog::OnCancel();
	DestroyWindow();
}
