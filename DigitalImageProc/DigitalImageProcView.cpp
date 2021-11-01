
// DigitalImageProcView.cpp: CDigitalImageProcView 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DigitalImageProc.h"
#endif

#include "DigitalImageProcDoc.h"
#include "DigitalImageProcView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CDigitalImageProcView

IMPLEMENT_DYNCREATE(CDigitalImageProcView, CView)

BEGIN_MESSAGE_MAP(CDigitalImageProcView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_SrcWind, &CDigitalImageProcView::OnSrcWnd)
	ON_UPDATE_COMMAND_UI(ID_SrcWind, &CDigitalImageProcView::OnUpdateSrcWnd)
	ON_COMMAND(ID_ResWind, &CDigitalImageProcView::OnResWnd)
	ON_UPDATE_COMMAND_UI(ID_ResWind, &CDigitalImageProcView::OnUpdateResWnd)
END_MESSAGE_MAP()

// CDigitalImageProcView 构造/析构

CDigitalImageProcView::CDigitalImageProcView() noexcept : pSrcWnd(NULL), pResWnd(NULL), pDoc(NULL)
{
	// TODO: 在此处添加构造代码

}

CDigitalImageProcView::~CDigitalImageProcView()
{
	delete pSrcWnd;
	delete pResWnd;
}

BOOL CDigitalImageProcView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}

// CDigitalImageProcView 绘图

void CDigitalImageProcView::OnDraw(CDC* /*pDC*/)
{
	CDigitalImageProcDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码
}


// CDigitalImageProcView 打印

BOOL CDigitalImageProcView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CDigitalImageProcView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CDigitalImageProcView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}


// CDigitalImageProcView 诊断

#ifdef _DEBUG
void CDigitalImageProcView::AssertValid() const
{
	CView::AssertValid();
}

void CDigitalImageProcView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CDigitalImageProcDoc* CDigitalImageProcView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDigitalImageProcDoc)));
	return (CDigitalImageProcDoc*)m_pDocument;
}
#endif //_DEBUG


// CDigitalImageProcView 消息处理程序


void CDigitalImageProcView::OnSrcWnd()
{
	// TODO: 在此添加命令处理程序代码
	if (pSrcWnd == NULL) {
		pSrcWnd = new CImgWnd(this, CRect(0, 0, 700, 600), _T("Source Image"));
	}
	else {
		delete pSrcWnd;
		pSrcWnd = NULL;
	}
}


void CDigitalImageProcView::OnUpdateSrcWnd(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(pSrcWnd != NULL);
}


void CDigitalImageProcView::OnResWnd()
{
	// TODO: 在此添加命令处理程序代码
	if (pResWnd == NULL) {
		pResWnd = new CImgWnd(this, CRect(720, 0, 1420, 600), _T("Result Image"));
	}
	else { 
		delete pResWnd;
		pResWnd = NULL;
	}
}


void CDigitalImageProcView::OnUpdateResWnd(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(pResWnd != NULL);
}


void CDigitalImageProcView::OnInitialUpdate()
{
	CView::OnInitialUpdate();
	// TODO: 在此添加专用代码和/或调用基类
	pDoc = GetDocument();
	pDoc->pView = this;
}

void CDigitalImageProcView::OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/)
{
	// TODO: 在此添加专用代码和/或调用基类
}
