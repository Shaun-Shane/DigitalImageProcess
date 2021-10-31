#pragma once
#include "CGrayImgData.h"

template<class T>
class CGeometricTrans: public CGrayImgData<T>
{
public:
	CGeometricTrans(CGrayImgData<T>& other): CGrayImgData(other){}

	T BilinearInterpolation(double _y, double _x) {
		int y = static_cast<int>(_y), x = static_cast<int>(_x);
		if (x >= nWidth || y >= nHeight || x < 0 || y < 0) return 0;
		if (y == nHeight - 1 && x == nWidth - 1) return pPixels[y * nWidth + x];
		double ky = _y - y, kx = _x - x;
		if (y == nHeight - 1) return static_cast<T>((1 - kx) * pPixels[y * nWidth + x] + kx * pPixels[y * nWidth + x + 1]);
		if (x == nWidth - 1) return static_cast<T>((1 - ky) * pPixels[y * nWidth + x] + ky * pPixels[(y + 1) * nWidth + x + 1]);
		return static_cast<T>((1 - kx) * (1 - ky) * pPixels[y * nWidth + x] + (1 - kx) * ky * pPixels[(y + 1) * nWidth + x]
			+ kx * (1 - ky) * pPixels[y * nWidth + x + 1] + kx * ky * pPixels[(y + 1) * nWidth + x + 1]);
	}

	CGrayImgData<T> Translate(double deltaH, double deltaW) {
		CGrayImgData<T> resData(nHeight, nWidth);
		for (int i = 0; i < nHeight; i++)
			for (int j = 0; j < nWidth; j++) 
					resData.SetPixel(i, j , BilinearInterpolation(- deltaH + i, - deltaW + j));
		return resData;
	}

	CGrayImgData<T> Rotate(double centerX, double centerY, double theta) {
		theta = theta / 360 * acos(-1.0);    // ½Ç¶È×ª»¡¶È
		CGrayImgData<T> resData(nHeight, nWidth);
		for (int i = 0; i < nHeight; i++)
			for (int j = 0; j < nWidth; j++) 
				resData.SetPixel(i, j, BilinearInterpolation(centerY + (-centerY + i) * cos(theta) - (-centerX + j) * sin(theta),
					                    centerX + (-centerY + i) * sin(theta) + (-centerX + j) * cos(theta)));
		return resData;
	}

	CGrayImgData<T> Zoom(double ratio) {
		CGrayImgData<T> resData(nHeight, nWidth);
		for (int i = 0; i < nHeight; i++)
			for (int j = 0; j < nWidth; j++) 
				resData.SetPixel(i, j, BilinearInterpolation((double)i / ratio, (double)j / ratio));
		return resData;
	}
	virtual ~CGeometricTrans() {}
};

