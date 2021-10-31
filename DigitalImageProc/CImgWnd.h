#pragma once


// CImgWnd
#include "CGrayImgData.h"

class CImgWnd : public CWnd
{
	DECLARE_DYNAMIC(CImgWnd)
public:
	CGrayImgData<unsigned char>* pImgData;
public:
	CImgWnd(CWnd* pParent, RECT rect, LPCTSTR pName = NULL, CGrayImgData<unsigned char>* pData = NULL);
	virtual ~CImgWnd();
	
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
};


