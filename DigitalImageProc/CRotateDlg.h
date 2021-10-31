#pragma once


// CRotateDlg 对话框
#include"DigitalImageProcDoc.h"

class CDigitalImageProcDoc;

class CRotateDlg : public CDialog
{
	DECLARE_DYNAMIC(CRotateDlg)

public:
	CRotateDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CRotateDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_RotateDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double centerX;
	double centerY;
	double theta;
	CDigitalImageProcDoc* pDoc;
	afx_msg void OnBnClickedSetX();
	afx_msg void OnBnClickedSetY();
};
