// CImgWnd.cpp: 实现文件
//

#include "pch.h"
#include "DigitalImageProc.h"
#include "CImgWnd.h"


// CImgWnd

IMPLEMENT_DYNAMIC(CImgWnd, CWnd)

CImgWnd::CImgWnd(CWnd* pParent, RECT rect, LPCTSTR pName, CGrayImgData<unsigned char>* pData): CWnd(), pImgData(pData)
{
	static int cntWnd = 0;
	CWnd::Create(AfxRegisterWndClass(NULL), pName, WS_CHILD | WS_CAPTION | WS_VISIBLE | WS_BORDER | WS_HSCROLL | WS_VSCROLL, rect, pParent, ++cntWnd);
}

CImgWnd::~CImgWnd()
{
}


BEGIN_MESSAGE_MAP(CImgWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_MOVE()
END_MESSAGE_MAP()



// CImgWnd 消息处理程序


void CImgWnd::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CWnd::OnPaint()
	if (pImgData == NULL) return;
	CImage* pImg = NULL;
	pImgData->SaveToCImage(pImg);
	if (pImg == NULL) {
		AfxMessageBox(_T("获取图像数据失败!"));
		return;
	}
	int nImgWidth, nImgHeight;  //图像的长宽
	CRect rectWndDraw;         //绘图窗口的矩形

	//获取图像的长宽
	nImgWidth = pImg->GetWidth();
	nImgHeight = pImg->GetHeight();

	//获取绘制窗口的长宽
	this->GetClientRect(&rectWndDraw);

	//绘制图像
	dc.FillSolidRect(rectWndDraw, RGB(255, 255, 255));
	pImg->Draw(dc.GetSafeHdc(), 0, 0);
	delete pImg;
}


void CImgWnd::OnMove(int x, int y)
{
	CWnd::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
}
