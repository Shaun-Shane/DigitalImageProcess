#pragma once
#include "CGrayImgData.h"

template<class T>
class CGeometricTrans: public CGrayImgData<T>
{
public:
	CGeometricTrans(CGrayImgData<T>& other): CGrayImgData(other){}

	T BilinearInterpolation(double _y, double _x, T* p) {
		int y = static_cast<int>(_y), x = static_cast<int>(_x);
		if (x >= nWidth || y >= nHeight || x < 0 || y < 0) return 0;
		if (y == nHeight - 1 && x == nWidth - 1) return p[y * nWidth + x];
		double ky = _y - y, kx = _x - x;
		if (y == nHeight - 1) return static_cast<T>((1 - kx) * p[y * nWidth + x] + kx * p[y * nWidth + x + 1]);
		if (x == nWidth - 1) return static_cast<T>((1 - ky) * p[y * nWidth + x] + ky * p[(y + 1) * nWidth + x + 1]);
		return static_cast<T>((1 - kx) * (1 - ky) * p[y * nWidth + x] + (1 - kx) * ky * p[(y + 1) * nWidth + x]
			+ kx * (1 - ky) * p[y * nWidth + x + 1] + kx * ky * p[(y + 1) * nWidth + x + 1]);
	}

	void Translate(double deltaH, double deltaW) {
		T* tmp = new T[nHeight * nWidth];
		for (int i = 0; i < nHeight * nWidth; i++) tmp[i] = pPixels[i];
		for (int i = 0; i < nHeight; i++)
			for (int j = 0; j < nWidth; j++) 
				pPixels[i * nWidth + j] = BilinearInterpolation(- deltaH + i, - deltaW + j, tmp);
		delete[] tmp;
	}

	void Rotate(double centerX, double centerY, double theta) {
		T* tmp = new T[nHeight * nWidth];
		for (int i = 0; i < nHeight * nWidth; i++) tmp[i] = pPixels[i];
		theta = theta / 360 * acos(-1.0);    // ½Ç¶È×ª»¡¶È
		CGrayImgData<T> resData(nHeight, nWidth);
		for (int i = 0; i < nHeight; i++)
			for (int j = 0; j < nWidth; j++) 
				pPixels[i * nWidth + j] = 
				BilinearInterpolation(centerY + (-centerY + i) * cos(theta) - (-centerX + j) * sin(theta),
					                  centerX + (-centerY + i) * sin(theta) + (-centerX + j) * cos(theta), 
									  tmp);
		delete[] tmp;
	}

	void Zoom(double ratio) {
		T* tmp = new T[nHeight * nWidth];
		for (int i = 0; i < nHeight * nWidth; i++) tmp[i] = pPixels[i];
		CGrayImgData<T> resData(nHeight, nWidth);
		for (int i = 0; i < nHeight; i++)
			for (int j = 0; j < nWidth; j++) 
				pPixels[i * nWidth + j] = BilinearInterpolation((double)i / ratio, (double)j / ratio, tmp);
		delete[] tmp;
	}
	virtual ~CGeometricTrans() {}
};

