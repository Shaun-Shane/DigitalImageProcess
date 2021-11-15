#pragma once
#include "CGrayImgData.h"
#include <string>

template<class S, class T>
class CGrayMapping :
    public CGrayImgData<T>
{
public:
    CGrayMapping(CGrayImgData<T>& other) : CGrayImgData(other) {}

    CGrayMapping() : CGrayImgData(), pSrcPixels(NULL){}
    
    virtual ~CGrayMapping() {
        delete[] pSrcPixels;
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
        
        pSrcPixels = new S[nHeight * nWidth] { 0 };
        pPixels = new T[nHeight * nWidth]{ 0 };
        fread(pSrcPixels, 2, nHeight * nWidth, fp);                    
        
        fclose(fp);
    }

    void GrayMapping(int wndPos, int wndLen) {
        int wndL = wndPos - wndLen / 2, wndR = wndPos + wndLen / 2;
        for (int i = 0 ; i < nHeight * nWidth; i++) {
                if (pSrcPixels[i] < wndL)
                    pPixels[i] = 0;
                else if (pSrcPixels[i] >= wndR)
                    pPixels[i] = 255;
                else 
                    pPixels[i] = static_cast<T>(1.0 * (pSrcPixels[i] - wndL) / wndLen * 255);
            }
    }

protected:
    S* pSrcPixels;
};

