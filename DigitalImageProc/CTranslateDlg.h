#pragma once


// CTranslateDlg 对话框

class CTranslateDlg : public CDialog
{
	DECLARE_DYNAMIC(CTranslateDlg)

public:
	CTranslateDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CTranslateDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_TranslateDlg };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	double transY;
	double transX;
};
