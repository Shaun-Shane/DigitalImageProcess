#pragma once
#include "CGrayImgData.h"
#include <string>

template<class T>
class CGrayMapping :
    public CGrayImgData<T>
{
public:
    CGrayMapping(CGrayImgData<T>& other) : CGrayImgData(other) {}

    CGrayMapping() : CGrayImgData(){}
    
    virtual ~CGrayMapping() {}

    void GrayMapping(int wndPos, int wndLen) {
        int wndL = wndPos - wndLen / 2, wndR = wndPos + wndLen / 2;
        for (int i = 0 ; i < nHeight * nWidth; i++) {
                if (pPixels[i] < wndL)
                    pPixels[i] = 0;
                else if (pPixels[i] >= wndR)
                    pPixels[i] = 255;
                else 
                    pPixels[i] = static_cast<T>(1.0 * (pPixels[i] - wndL) / wndLen * 255);
            }
    }
};

