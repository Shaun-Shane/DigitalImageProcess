#pragma once


// CMappingDlg 对话框
#include "DigitalImageProcDoc.h"

class CMappingDlg : public CDialog
{
	DECLARE_DYNAMIC(CMappingDlg)

public:
	CMappingDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CMappingDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MappingDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString fileName;
	CDigitalImageProcDoc* pDoc;
	int wndPos;
	int wndLen;
	afx_msg void OnBnClickedUpload();
	virtual void OnOK();
	afx_msg void OnDestroy();
	virtual void OnCancel();
};
