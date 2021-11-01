#pragma once

template<class T>
class CGrayImgData
{
public:
	CGrayImgData() : nWidth(0), nHeight(0), pPixels(NULL) {}

	CGrayImgData(const CGrayImgData& other) {
		nWidth = other.nWidth, nHeight = other.nHeight;
		pPixels = new T[nWidth * nHeight];
		for(int i = 0; i < nWidth * nHeight; i++) pPixels[i] = other.pPixels[i];
	}

	CGrayImgData(int Height, int Width): nWidth(Width), nHeight(Height) {
		pPixels = new T[Width * Height];
		for (int i = 0; i < nWidth * nHeight; i++) pPixels[i] = 0;
	}

	CGrayImgData& operator = (const CGrayImgData& other) {
		nWidth = other.nWidth, nHeight = other.nHeight;
		delete[] pPixels;
		pPixels = new T[nWidth * nHeight];
		for (int i = 0; i < nWidth * nHeight; i++) pPixels[i]= other.pPixels[i];
		return *this;
	}

	virtual ~CGrayImgData() {
		delete[] pPixels;
	}

	void SetPixel(int i, int j, T val) {
		pPixels[i * nWidth + j] = val;
	}

	T GetPixel(int i, int j) {
		return pPixels[i * nWidth + j];
	}

	void LoadFromCImage(CImage* pImg) {
		nWidth = pImg->GetWidth(), nHeight = pImg->GetHeight();
		delete[] pPixels;
		pPixels = new T[nWidth * nHeight];
	    BYTE* tmp = (BYTE*)pImg->GetBits();
		int pitch = pImg->GetPitch();
		for (int i = 0; i < nHeight; i++) {
			for (int j = 0; j < nWidth; j++)
				pPixels[i * nWidth + j] = *(tmp + j); 
			tmp = tmp + pitch;
		}
	}

	void SaveToCImage(CImage*& pImg) {
		if (pImg != NULL) delete pImg;
		pImg = new CImage();
		if (!pImg->Create(nWidth, -nHeight, 8)) {
			AfxMessageBox(_T("¥¥Ω®CImage ß∞‹!"));
			delete pImg;
			pImg = NULL;
			return;
		}
		RGBQUAD* pLUT = new RGBQUAD[256];
		for (int i = 0; i < 256; i++) {
			(pLUT + i)->rgbRed = (pLUT + i)->rgbGreen = (pLUT + i)->rgbBlue = i;
			(pLUT + i)->rgbReserved = 0;
		}
		pImg->SetColorTable(0, 256, pLUT);
		delete[] pLUT;

		BYTE* tmp = (BYTE*)pImg->GetBits();
		int pitch = pImg->GetPitch();

		for (int i = 0; i < nHeight; i++) {
			for (int j = 0; j < nWidth; j++)
				*(tmp + j) = pPixels[i * nWidth + j];
			tmp = tmp + pitch;
		}
	}

	int GetWidth() { return nWidth; }
	int GetHeight() { return nHeight; }

protected:
	int nWidth, nHeight;
	T* pPixels;
};

