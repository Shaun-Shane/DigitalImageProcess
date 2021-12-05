
// DigitalImageProcDoc.h: CDigitalImageProcDoc 类的接口
//


#pragma once
#include "DigitalImageProcView.h"
#include "CGrayImgData.h"
#include "CGeometricTrans.h"
#include "CTranslateDlg.h"
#include "CZoomDlg.h"
#include "CRotateDlg.h"
#include "CGrayMapping.h"
#include "CMappingDlg.h"
#include "CImgEnhance.h"
#include "CImgSegmentation.h"
class CDigitalImageProcView;

class CDigitalImageProcDoc : public CDocument
{
protected: // 仅从序列化创建
	CDigitalImageProcDoc() noexcept;
	DECLARE_DYNCREATE(CDigitalImageProcDoc)
public:
	CDigitalImageProcView* pView;
	CGrayImgData<unsigned char>* pSrcImgData;
	CGrayImgData<unsigned short>* pCustomData;
	CGrayImgData<unsigned char>* pEnhancedSrcImgData;
	CGrayImgData<unsigned short>* pEnhancedCustomData;
	CImage* pResImg;
	CImage* pSrcImg;
	CImage* pEnhancedImg;
	bool denoisingTag;
	bool sharpeningTag;
// 特性
public:

// 操作
public:

// 重写
public:
	virtual BOOL OnNewDocument();
	virtual void Serialize(CArchive& ar);
#ifdef SHARED_HANDLERS
	virtual void InitializeSearchContent();
	virtual void OnDrawThumbnail(CDC& dc, LPRECT lprcBounds);
#endif // SHARED_HANDLERS

// 实现
public:
	virtual ~CDigitalImageProcDoc();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	DECLARE_MESSAGE_MAP()

#ifdef SHARED_HANDLERS
	// 用于为搜索处理程序设置搜索内容的 Helper 函数
	void SetSearchContent(const CString& value);
#endif // SHARED_HANDLERS
public:
	afx_msg void OnOpenGrayImg();
	afx_msg void OnClickTranslation();
	void TranslateImg(double y, double x);
	afx_msg void OnClickZoom();
	void ZoomImg(double ratio);
	afx_msg void OnClickRotation();
	void RotateImg(double X, double Y, double theta);
	afx_msg void OnSaveResImg();
	afx_msg void OnGrayMapping();
	void GrayMapping(CString fileName, int wndPos, int wndLen);
	void ReadCustomData(CString fileName);
	afx_msg void OnClickDenoising();
	afx_msg void OnClickSharpening();
	afx_msg void OnUpdateDenoising(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSharpening(CCmdUI* pCmdUI);
	void Enhance();
	afx_msg void OnSegimg();
	void Segmentation();
};
