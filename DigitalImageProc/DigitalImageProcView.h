
// DigitalImageProcView.h: CDigitalImageProcView 类的接口
//

#pragma once
#include "CImgWnd.h"
#include "CGrayImgData.h"
#include "DigitalImageProcDoc.h"

class CDigitalImageProcDoc;

class CDigitalImageProcView : public CView
{
protected: // 仅从序列化创建
	CDigitalImageProcView() noexcept;
	DECLARE_DYNCREATE(CDigitalImageProcView)
public:
	CImgWnd* pSrcWnd;
	CImgWnd* pResWnd;
	CImgWnd* pEnhanceWnd;
	CDigitalImageProcDoc* pDoc;
// 特性
public:
	CDigitalImageProcDoc* GetDocument() const;

// 操作
public:

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CDigitalImageProcView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnSrcWnd();
	afx_msg void OnUpdateSrcWnd(CCmdUI* pCmdUI);
	afx_msg void OnResWnd();
	afx_msg void OnUpdateResWnd(CCmdUI* pCmdUI);
	virtual void OnInitialUpdate();
	virtual void OnUpdate(CView* /*pSender*/, LPARAM /*lHint*/, CObject* /*pHint*/);
	afx_msg void OnEnhancedimgwnd();
	afx_msg void OnUpdateEnhancedimgwnd(CCmdUI* pCmdUI);
};

#ifndef _DEBUG  // DigitalImageProcView.cpp 中的调试版本
inline CDigitalImageProcDoc* CDigitalImageProcView::GetDocument() const
   { return reinterpret_cast<CDigitalImageProcDoc*>(m_pDocument); }
#endif

