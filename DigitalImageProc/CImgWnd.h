#pragma once


// CImgWnd
#include "CGrayImgData.h"

class CImgWnd : public CWnd
{
	DECLARE_DYNAMIC(CImgWnd)

public:
	CImgWnd(CWnd* pParent, RECT rect, LPCTSTR pName = NULL, CImage* pImg = NULL);
	virtual ~CImgWnd();
	void SetPImg(CImage* _pImg);

protected:
	DECLARE_MESSAGE_MAP()
	CImage* pImg;
public:
	afx_msg void OnPaint();
	afx_msg void OnMove(int x, int y);
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnSize(UINT nType, int cx, int cy);
private:
	int scrollH;
	int scrollV;
	int cursorX;
	int cursorY;
	bool isMouseDown;
public:
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};


