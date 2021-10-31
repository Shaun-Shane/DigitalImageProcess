
// DigitalImageProcDoc.cpp: CDigitalImageProcDoc 类的实现
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "DigitalImageProc.h"
#endif

#include "DigitalImageProcDoc.h"

#include <propkey.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CDigitalImageProcDoc

IMPLEMENT_DYNCREATE(CDigitalImageProcDoc, CDocument)

BEGIN_MESSAGE_MAP(CDigitalImageProcDoc, CDocument)
	ON_COMMAND(ID_OpenImg, &CDigitalImageProcDoc::OnOpenImg)
	ON_COMMAND(ID_Translation, &CDigitalImageProcDoc::OnClickTranslation)
	ON_COMMAND(ID_Zoom, &CDigitalImageProcDoc::OnClickZoom)
	ON_COMMAND(ID_Rotation, &CDigitalImageProcDoc::OnClickRotation)
	ON_COMMAND(ID_SaveResImg, &CDigitalImageProcDoc::OnSaveResImg)
END_MESSAGE_MAP()


// CDigitalImageProcDoc 构造/析构

CDigitalImageProcDoc::CDigitalImageProcDoc() noexcept : pView(NULL), pSrcImgData(NULL), pResImgData(NULL)
{
	// TODO: 在此添加一次性构造代码

}

CDigitalImageProcDoc::~CDigitalImageProcDoc()
{
	delete pSrcImgData;
	delete pResImgData;
}

BOOL CDigitalImageProcDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 在此添加重新初始化代码
	// (SDI 文档将重用该文档)

	return TRUE;
}


// CDigitalImageProcDoc 序列化

void CDigitalImageProcDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 在此添加存储代码
	}
	else
	{
		// TODO: 在此添加加载代码
	}
}

#ifdef SHARED_HANDLERS

// 缩略图的支持
void CDigitalImageProcDoc::OnDrawThumbnail(CDC& dc, LPRECT lprcBounds)
{
	// 修改此代码以绘制文档数据
	dc.FillSolidRect(lprcBounds, RGB(255, 255, 255));

	CString strText = _T("TODO: implement thumbnail drawing here");
	LOGFONT lf;

	CFont* pDefaultGUIFont = CFont::FromHandle((HFONT)GetStockObject(DEFAULT_GUI_FONT));
	pDefaultGUIFont->GetLogFont(&lf);
	lf.lfHeight = 36;

	CFont fontDraw;
	fontDraw.CreateFontIndirect(&lf);

	CFont* pOldFont = dc.SelectObject(&fontDraw);
	dc.DrawText(strText, lprcBounds, DT_CENTER | DT_WORDBREAK);
	dc.SelectObject(pOldFont);
}

// 搜索处理程序的支持
void CDigitalImageProcDoc::InitializeSearchContent()
{
	CString strSearchContent;
	// 从文档数据设置搜索内容。
	// 内容部分应由“;”分隔

	// 例如:     strSearchContent = _T("point;rectangle;circle;ole object;")；
	SetSearchContent(strSearchContent);
}

void CDigitalImageProcDoc::SetSearchContent(const CString& value)
{
	if (value.IsEmpty())
	{
		RemoveChunk(PKEY_Search_Contents.fmtid, PKEY_Search_Contents.pid);
	}
	else
	{
		CMFCFilterChunkValueImpl* pChunk = nullptr;
		ATLTRY(pChunk = new CMFCFilterChunkValueImpl);
		if (pChunk != nullptr)
		{
			pChunk->SetTextValue(PKEY_Search_Contents, value, CHUNK_TEXT);
			SetChunkValue(pChunk);
		}
	}
}

#endif // SHARED_HANDLERS

// CDigitalImageProcDoc 诊断

#ifdef _DEBUG
void CDigitalImageProcDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CDigitalImageProcDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CDigitalImageProcDoc 命令

void CDigitalImageProcDoc::OnOpenImg()
{
	// TODO: 在此添加命令处理程序代码
	// LPCTSTR szFilter = _T("JPEG(*.jpg)|*.jpg|PNG(*.png)|*.png|BMP(*.bmp)|*.bmp||");
	LPCTSTR szFilter = _T("BMP(*.bmp)|*.bmp||");
	CFileDialog dlgBKFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	CString strBKFileName;

	if (dlgBKFile.DoModal() == IDOK)
		strBKFileName = dlgBKFile.GetPathName();
	else
		return;
	
	CImage* pImg = new CImage();
	pImg->Load(strBKFileName);

	if (pImg->IsNull()) {
		AfxMessageBox(_T("建立图像指针失败!"));
		delete pImg;
		return;
	}
	if (pSrcImgData == NULL) pSrcImgData = new CGrayImgData<unsigned char>;
	// 更新数据
	pSrcImgData->LoadFromCImage(pImg);
	delete pImg;
	// 打开图像同时开启窗口显示图像
	if (pView->pSrcWnd == NULL)
		pView->OnSrcWnd();
	else if (pView->pSrcWnd->pImgData == NULL)
		pView->pSrcWnd->pImgData = pSrcImgData;
	// 重绘
	pView->pSrcWnd->RedrawWindow();
}

void CDigitalImageProcDoc::OnClickTranslation()
{
	// TODO: 在此添加命令处理程序代码
	if (pSrcImgData == NULL) {
		AfxMessageBox(_T("请先打开图像!"));
		return;
	}
	CTranslateDlg transDlg;
	if (transDlg.DoModal() == IDOK) 
		TranslateImg(transDlg.transY, transDlg.transX);
}


void CDigitalImageProcDoc::TranslateImg(double y, double x)
{
	// TODO: 在此处添加实现代码.
	CGeometricTrans<unsigned char> tmp(*pSrcImgData);
	if (pResImgData == NULL) pResImgData = new CGrayImgData<unsigned char>;
	// 更新数据
	*pResImgData = tmp.Translate(y, x);
	if (pView->pResWnd == NULL) 
		pView->OnResWnd();
	else if (pView->pResWnd->pImgData == NULL)
		pView->pResWnd->pImgData = pResImgData;
	// 重绘
	pView->pResWnd->RedrawWindow();
}


void CDigitalImageProcDoc::OnClickZoom()
{
	// TODO: 在此添加命令处理程序代码
	if (pSrcImgData == NULL) {
		AfxMessageBox(_T("请先打开图像!"));
		return;
	}
	CZoomDlg zoomDlg;
	if (zoomDlg.DoModal() == IDOK) {
		if (zoomDlg.ratio <= 0) {
			AfxMessageBox(_T("缩放比例需为正实数!"));
			return;
		}
		ZoomImg(zoomDlg.ratio);
	}
}


void CDigitalImageProcDoc::ZoomImg(double ratio)
{
	// TODO: 在此处添加实现代码.
	CGeometricTrans<unsigned char> tmp(*pSrcImgData);
	if (pResImgData == NULL) pResImgData = new CGrayImgData<unsigned char>;
	// 更新数据
	*pResImgData = tmp.Zoom(ratio);
	if (pView->pResWnd == NULL)
		pView->OnResWnd();
	else if (pView->pResWnd->pImgData == NULL)
		pView->pResWnd->pImgData = pResImgData;
	// 重绘
	pView->pResWnd->RedrawWindow();
}


void CDigitalImageProcDoc::OnClickRotation()
{
	// TODO: 在此添加命令处理程序代码
	if (pSrcImgData == NULL) {
		AfxMessageBox(_T("请先打开图像!"));
		return;
	}
	CRotateDlg rotateDlg;
	rotateDlg.pDoc = this;
	if (rotateDlg.DoModal() == IDOK) 
		RotateImg(rotateDlg.centerX, rotateDlg.centerY, rotateDlg.theta);
}


void CDigitalImageProcDoc::RotateImg(double X, double Y, double theta)
{
	// TODO: 在此处添加实现代码.
	CGeometricTrans<unsigned char> tmp(*pSrcImgData);
	if (pResImgData == NULL) pResImgData = new CGrayImgData<unsigned char>;
	// 更新数据
	*pResImgData = tmp.Rotate(X, Y, theta);
	if (pView->pResWnd == NULL)
		pView->OnResWnd();
	else if (pView->pResWnd->pImgData == NULL)
		pView->pResWnd->pImgData = pResImgData;
	// 重绘
	pView->pResWnd->RedrawWindow();
}


void CDigitalImageProcDoc::OnSaveResImg()
{
	// TODO: 在此添加命令处理程序代码
	if (pResImgData == NULL) {
		AfxMessageBox(_T("无结果图像数据!"));
		return;
	}
	LPCTSTR szFilter = _T("BMP(*.bmp)|*.bmp||");
	CFileDialog dlgBKFile(FALSE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	CString strBKFileName;

	if (dlgBKFile.DoModal() == IDOK)
		strBKFileName = dlgBKFile.GetPathName();
	else
		return;
	
	CImage* pImg = NULL;
	pResImgData->SaveToCImage(pImg);
	pImg->Save(strBKFileName, Gdiplus::ImageFormatBMP);
	delete pImg;
}
