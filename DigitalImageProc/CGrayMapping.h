#pragma once
#include "CGrayImgData.h"
template<class S, class T>
class CGrayMapping :
    public CGrayImgData<T>
{
public:
    CGrayMapping(CGrayImgData<T>& other) : CGrayImgData(other) {}

    void ReadData() {   
        fstream fs;
        unsigned long w, h;
        fs >> w >> h;
        nHeight = h, nWidth = w;
        pSpixels = new S[nHeght * nWidth];
        for (int i = 0; i < nHeight; i++)
            for (int j = 0; j < nWidth; j++)
                fs >> pSpixels[i * nWidth + j];
    }

    void GrayMapping(int wndPos, int wndLen) {
        int wndL = wndPos - wndLen / 2, wndR = wndPos + wndLen / 2;
        for (int i = 0; i < nHeight; i++)
            for (int j = 0; j < nWidth; j++)
                if (pSpixels[i * nWidth + j] < wndL)
                    pPiXels[i * nWidth + j] = 0;
                else  if (pSpixels[i * nWidth + j] > wndR)
                    pPiXels[i * nWidth + j] = 255;
                else
                    pPiXels[i * nWidth + j] = 1.0 * (pSPixels[i * nWidth + j] - wndL) / (wndLen + 1) * 255;
    }


protected:
    S* pSPixels;
};

