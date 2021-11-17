
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
	ON_COMMAND(ID_OpenImg, &CDigitalImageProcDoc::OnOpenGrayImg)
	ON_COMMAND(ID_Translation, &CDigitalImageProcDoc::OnClickTranslation)
	ON_COMMAND(ID_Zoom, &CDigitalImageProcDoc::OnClickZoom)
	ON_COMMAND(ID_Rotation, &CDigitalImageProcDoc::OnClickRotation)
	ON_COMMAND(ID_SaveResImg, &CDigitalImageProcDoc::OnSaveResImg)
	ON_COMMAND(ID_32792, &CDigitalImageProcDoc::OnGrayMapping)
	ON_COMMAND(ID_Denoising, &CDigitalImageProcDoc::OnClickDenoising)
	ON_COMMAND(ID_Sharpening, &CDigitalImageProcDoc::OnClickSharpening)
	ON_UPDATE_COMMAND_UI(ID_Denoising, &CDigitalImageProcDoc::OnUpdateDenoising)
	ON_UPDATE_COMMAND_UI(ID_Sharpening, &CDigitalImageProcDoc::OnUpdateSharpening)
END_MESSAGE_MAP()


// CDigitalImageProcDoc 构造/析构

CDigitalImageProcDoc::CDigitalImageProcDoc() noexcept : pView(NULL), pSrcImgData(NULL)
, pResImg(NULL), pSrcImg(NULL), pCustomData(NULL), denoisingTag(0), sharpeningTag(0)
, pEnhancedImg(NULL)
{
	// TODO: 在此添加一次性构造代码

}

CDigitalImageProcDoc::~CDigitalImageProcDoc()
{
	delete pSrcImgData;
	delete pCustomData;
	delete pResImg;
	delete pSrcImg;
	delete pEnhancedImg;
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

void CDigitalImageProcDoc::OnOpenGrayImg()
{
	// TODO: 在此添加命令处理程序代码
	// LPCTSTR szFilter = _T("JPEG(*.jpg)|*.jpg|PNG(*.png)|*.png|BMP(*.bmp)|*.bmp||");
	LPCTSTR szFilter = _T("||");
	CFileDialog dlgBKFile(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, szFilter, NULL);

	CString strBKFileName;

	if (dlgBKFile.DoModal() == IDOK)
		strBKFileName = dlgBKFile.GetPathName();
	else
		return;

	if (pSrcImg == NULL) pSrcImg = new CImage();
	pSrcImg->Destroy();
	pSrcImg->Load(strBKFileName);
	if (pSrcImg->IsNull()) {
		AfxMessageBox(_T("建立图像指针失败!"));
		delete pSrcImg;
		pSrcImg = NULL;
		return;
	}

	if (pSrcImgData == NULL) pSrcImgData = new CGrayImgData<unsigned char>;
	// 更新数据
	pSrcImgData->LoadFromCImage(pSrcImg);
	// 打开图像同时开启窗口显示图像
	if (pView->pSrcWnd == NULL) pView->OnSrcWnd();
	UpdateAllViews(NULL);
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
	// 更新数据
	tmp.Translate(y, x);
	tmp.SaveToCImage(pResImg);
	if (pView->pResWnd == NULL) pView->OnResWnd();
	UpdateAllViews(NULL);
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
	// 更新数据
	tmp.Zoom(ratio);
	tmp.SaveToCImage(pResImg);
	if (pView->pResWnd == NULL) pView->OnResWnd();
	UpdateAllViews(NULL);
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
	// 更新数据
	tmp.Rotate(X, Y, theta);
	tmp.SaveToCImage(pResImg);
	if (pView->pResWnd == NULL) pView->OnResWnd();
	UpdateAllViews(NULL);
}


void CDigitalImageProcDoc::OnSaveResImg()
{
	// TODO: 在此添加命令处理程序代码
	if (pResImg == NULL) {
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
	pResImg->Save(strBKFileName, Gdiplus::ImageFormatBMP);
}


void CDigitalImageProcDoc::OnGrayMapping()
{
	// TODO: 在此添加命令处理程序代码



	CMappingDlg* mappingDlg = new CMappingDlg;
	mappingDlg->Create(IDD_MappingDlg, pView);
	mappingDlg->pDoc = this;
	mappingDlg->ShowWindow(SW_SHOW);
}


void CDigitalImageProcDoc::GrayMapping(CString fileName, int wndPos, int wndLen)
{
	// TODO: 在此处添加实现代码.
	ReadCustomData(fileName);
	CGrayMapping<unsigned short> myGrayMapping(*pCustomData);
	myGrayMapping.GrayMapping(wndPos, wndLen);
	myGrayMapping.SaveToCImage(pSrcImg);
	if (pView->pSrcWnd == NULL) pView->OnSrcWnd();
	UpdateAllViews(NULL);
}


void CDigitalImageProcDoc::ReadCustomData(CString fileName)
{
	// TODO: 在此处添加实现代码.
	pCustomData = new CGrayImgData<unsigned short>;
	std::string s = (CStringA)fileName;
	const char* p = s.c_str();

	FILE* fp = fopen(p, "rb");
	if (!fp) {
		AfxMessageBox(_T("打开图像失败!"));
		return;
	}

	unsigned long w = 0, h = 0;
	fread(&w, 4, 1, fp);
	fread(&h, 4, 1, fp);
	unsigned short* tmp = new unsigned short[w * h];
	fread(tmp, 2, w * h, fp);
	
	fclose(fp);

	pCustomData->Create(h, w, tmp);
	delete[] tmp;
}



void CDigitalImageProcDoc::OnClickDenoising()
{
	// TODO: 在此添加命令处理程序代码
	denoisingTag ^= 1;
}


void CDigitalImageProcDoc::OnClickSharpening()
{
	// TODO: 在此添加命令处理程序代码
	sharpeningTag ^= 1;
}


void CDigitalImageProcDoc::OnUpdateDenoising(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(denoisingTag);
}


void CDigitalImageProcDoc::OnUpdateSharpening(CCmdUI* pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(sharpeningTag);
}
