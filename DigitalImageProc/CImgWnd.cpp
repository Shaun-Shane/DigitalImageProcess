// CImgWnd.cpp: 实现文件
//

#include "pch.h"
#include "DigitalImageProc.h"
#include "CImgWnd.h"


// CImgWnd

IMPLEMENT_DYNAMIC(CImgWnd, CWnd)

CImgWnd::CImgWnd(CWnd* pParent, RECT rect, LPCTSTR pName, CImage* _pImg): 
	CWnd(), pImg(_pImg), scrollH(0), scrollV(0),isMouseDown(false)
{
	static int cntWnd = 0;
	CWnd::Create(AfxRegisterWndClass(NULL), pName, WS_SIZEBOX | WS_CLIPSIBLINGS | WS_CHILD | WS_CAPTION | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL, rect, pParent, ++cntWnd);
}

CImgWnd::~CImgWnd()
{
}

void CImgWnd::SetPImg(CImage* _pImg) { 
	pImg = _pImg; 
	SCROLLINFO info;
	GetScrollInfo(SB_HORZ, &info, SIF_ALL);
	info.nMax = pImg->GetWidth();
	SetScrollInfo(SB_HORZ, &info, TRUE);
	GetScrollInfo(SB_VERT, &info, SIF_ALL);
	info.nMax = pImg->GetHeight();
	SetScrollInfo(SB_VERT, &info, TRUE);
	RedrawWindow();
	UpdateWindow();
}


BEGIN_MESSAGE_MAP(CImgWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_MOVE()
	ON_WM_HSCROLL()
	ON_WM_VSCROLL()
	ON_WM_SIZE()
	ON_WM_MOUSEWHEEL()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSELEAVE()
	ON_WM_MOUSELEAVE()
END_MESSAGE_MAP()



// CImgWnd 消息处理程序


void CImgWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CWnd::OnPaint()
	if (pImg == NULL) return;
	int nImgWidth, nImgHeight;  //图像的长宽
	CRect rectWndDraw;         //绘图窗口的矩形

	//获取图像的长宽
	nImgWidth = pImg->GetWidth();
	nImgHeight = pImg->GetHeight();

	//获取绘制窗口的长宽
	this->GetClientRect(&rectWndDraw);

	//绘制图像
	dc.FillSolidRect(rectWndDraw, RGB(255, 255, 255));
	pImg->Draw(dc.GetSafeHdc(), -scrollH, -scrollV); // 改成 scroll 的 pos
}


void CImgWnd::OnMove(int x, int y)
{
	CWnd::OnMove(x, y);
	BringWindowToTop();
	// TODO: 在此处添加消息处理程序代码
}


void CImgWnd::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// origin: https://docs.microsoft.com/zh-cn/cpp/mfc/reference/cwnd-class?view=msvc-160#onhscroll
	// 示例
	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	GetScrollRange(SB_HORZ, &minpos, &maxpos);
	maxpos = GetScrollLimit(SB_HORZ);

	// Get the current position of scroll box.
	int curpos = GetScrollPos(SB_HORZ);

	// Determine the new position of scroll box.
	switch (nSBCode)
	{
	case SB_LEFT: // Scroll to far left.
		curpos = minpos;
		break;

	case SB_RIGHT: // Scroll to far right.
		curpos = maxpos;
		break;

	case SB_ENDSCROLL: // End scroll.
		break;

	case SB_LINELEFT: // Scroll left.
		if (curpos > minpos)
			curpos = max(0, curpos - 50); // 修改了移动距离
		break;

	case SB_LINERIGHT: // Scroll right.
		if (curpos < maxpos)
			curpos = min(maxpos, curpos + 50); // 修改了移动距离
		break;

	case SB_PAGELEFT: // Scroll one page left.
	{
		// Get the page size.
		SCROLLINFO info;
		GetScrollInfo(SB_HORZ, &info, SIF_ALL);

		if (curpos > minpos)
			curpos = max(minpos, curpos - (int)info.nPage);
	}
	break;

	case SB_PAGERIGHT: // Scroll one page right.
	{
		// Get the page size.
		SCROLLINFO info;
		GetScrollInfo(SB_HORZ, &info, SIF_ALL);

		if (curpos < maxpos)
			curpos = min(maxpos, curpos + (int)info.nPage);
	}
	break;

	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		curpos = nPos;      // of the scroll box at the end of the drag operation.
		break;

	case SB_THUMBTRACK: // Drag scroll box to specified position. nPos is the
		curpos = nPos;   // position that the scroll box has been dragged to.
		break;
	}

	// Set the new position of the thumb (scroll box).
	SetScrollPos(SB_HORZ, curpos);
	ScrollWindow(scrollH - curpos, 0);

	scrollH = curpos;
	UpdateWindow();

	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}


void CImgWnd::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	// Get the minimum and maximum scroll-bar positions.
	int minpos;
	int maxpos;
	GetScrollRange(SB_VERT, &minpos, &maxpos);
	maxpos = GetScrollLimit(SB_VERT);

	// Get the current position of scroll box.
	int curpos = GetScrollPos(SB_VERT);

	// Determine the new position of scroll box.
	switch (nSBCode)
	{
	case SB_LEFT: // Scroll to far left.
		curpos = minpos;
		break;

	case SB_RIGHT: // Scroll to far right.
		curpos = maxpos;
		break;

	case SB_ENDSCROLL: // End scroll.
		break;

	case SB_LINELEFT: // Scroll left.
		if (curpos > minpos)
			curpos  = max(0, curpos - 50);
		break;

	case SB_LINERIGHT: // Scroll right.
		if (curpos < maxpos) 
			curpos = min(maxpos, curpos + 50);
		break;

	case SB_PAGELEFT: // Scroll one page left.
	{
		// Get the page size.
		SCROLLINFO info;
		GetScrollInfo(SB_HORZ, &info, SIF_ALL);

		if (curpos > minpos)
			curpos = max(minpos, curpos - (int)info.nPage);
	}
	break;

	case SB_PAGERIGHT: // Scroll one page right.
	{
		// Get the page size.
		SCROLLINFO info;
		GetScrollInfo(SB_HORZ, &info, SIF_ALL);

		if (curpos < maxpos)
			curpos = min(maxpos, curpos + (int)info.nPage);
	}
	break;

	case SB_THUMBPOSITION: // Scroll to absolute position. nPos is the position
		curpos = nPos;      // of the scroll box at the end of the drag operation.
		break;

	case SB_THUMBTRACK: // Drag scroll box to specified position. nPos is the
		curpos = nPos;   // position that the scroll box has been dragged to.
		break;
	}

	// Set the new position of the thumb (scroll box).
	SetScrollPos(SB_VERT, curpos);
	ScrollWindow(0, scrollV - curpos);

	scrollV = curpos;
	UpdateWindow();

	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}


void CImgWnd::OnSize(UINT nType, int cx, int cy)
{
	CWnd::OnSize(nType, cx, cy);
	// TODO: 在此处添加消息处理程序代码
	//设置滚动条范围
	SCROLLINFO si;
	si.cbSize = sizeof(si);
	si.fMask = SIF_RANGE | SIF_PAGE;
	si.nMin = 0;
	si.nMax = (pImg == NULL ? 1024 : pImg->GetWidth());
	si.nPage = cx;
	SetScrollInfo(SB_HORZ, &si, TRUE);
	si.nMax = (pImg == NULL ? 1024 : pImg->GetHeight());
	si.nPage = cy;
	SetScrollInfo(SB_VERT, &si, TRUE);

	int curH = GetScrollPos(SB_HORZ);
	int curV = GetScrollPos(SB_VERT);
	if (curH < scrollH) ScrollWindow(scrollH - curH, 0);
	if (curV < scrollV) ScrollWindow(0, scrollV - curV);
	scrollH = GetScrollPos(SB_HORZ);
	scrollV = GetScrollPos(SB_VERT);
	UpdateWindow();
}


BOOL CImgWnd::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	int curpos = max(0, min(GetScrollLimit(SB_VERT), scrollV - zDelta / 2));
	SetScrollPos(SB_VERT, curpos);
	ScrollWindow(0, scrollV - curpos);
	scrollV = curpos;
	UpdateWindow();
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}


void CImgWnd::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	
	if (isMouseDown) {
		int maxposH = GetScrollLimit(SB_HORZ);
		int maxposV = GetScrollLimit(SB_VERT);
		
		int curH = max(0, min(maxposH, scrollH - (point.x - cursorX)));
		int curV = max(0, min(maxposV, scrollV - (point.y - cursorY)));
		SetScrollPos(SB_VERT, curV);
		SetScrollPos(SB_HORZ, curH);
		ScrollWindow(-curH + scrollH, -curV + scrollV);

		cursorX = point.x;
		cursorY = point.y;
		scrollH  = curH;
		scrollV = curV;
		UpdateWindow();
	}
	CWnd::OnMouseMove(nFlags, point);
}


void CImgWnd::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	isMouseDown = true;
	CWnd::OnLButtonDown(nFlags, point);
}


void CImgWnd::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	isMouseDown = false;
	CWnd::OnLButtonUp(nFlags, point);
}
