#pragma once
#include "CGrayImgData.h"
#include <string>

template<class S, class T>
class CGrayMapping :
    public CGrayImgData<T>
{
public:
    CGrayMapping(CGrayImgData<T>& other) : CGrayImgData(other) {}

    CGrayMapping() : CGrayImgData(), pSPixels(NULL){}
    
    virtual ~CGrayMapping() {
        delete[] pSPixels;
    }

    void ReadData(CString strBKFileName) {
        std::string s = (CStringA)strBKFileName;
        const char* p = s.c_str();
        FILE* fp = fopen(p, "rb");
        if (!fp) {
            AfxMessageBox(_T("´ò¿ªÍ¼ÏñÊ§°Ü!"));
            return;
        }
        unsigned long w = 0, h = 0;
        fread(&w, 4, 1, fp);
        fread(&h, 4, 1, fp);
        nHeight = h, nWidth = w;
        pSPixels = new S[nHeight * nWidth] { 0 };
        fread(pSPixels, 2, nHeight * nWidth, fp);                    
        pPixels = new T[nHeight * nWidth]{ 0 };
        fclose(fp);
    }

    void GrayMapping(int wndPos, int wndLen) {
        int wndL = wndPos - wndLen / 2, wndR = wndPos + wndLen / 2;
        for (int i = 0; i < nHeight; i++)
            for (int j = 0; j < nWidth; j++) {
                if (pSPixels[i * nWidth + j] < wndL)
                    pPixels[i * nWidth + j] = 0;
                else if (pSPixels[i * nWidth + j] >= wndR)
                    pPixels[i * nWidth + j] = 255;
                else 
                    pPixels[i * nWidth + j] = static_cast<T>(1.0 * (pSPixels[i * nWidth + j] - wndL) / wndLen * 255);
            }
    }

protected:
    S* pSPixels;
};

