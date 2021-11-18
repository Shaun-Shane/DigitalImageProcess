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

	CGrayImgData(int Height, int Width, T* pPix = NULL): nWidth(Width), nHeight(Height) {
		pPixels = new T[Width * Height];
		if (pPix == NULL)
			for (int i = 0; i < nWidth * nHeight; i++) pPixels[i] = 0;
		else 
			for (int i = 0; i < nWidth * nHeight; i++) pPixels[i] = pPix[i];
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

	void Create(int Height, int Width, T* data) {
		delete[] pPixels;
		nHeight = Height, nWidth = Width;
		pPixels = new T[nHeight * nWidth];
		for (int i = 0; i < nHeight * nWidth; i++) pPixels[i] = data[i];
	}

	void CopyTo(CGrayImgData*& other) {
		delete other;
		other = new CGrayImgData<T>(nHeight, nWidth, pPixels);
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

