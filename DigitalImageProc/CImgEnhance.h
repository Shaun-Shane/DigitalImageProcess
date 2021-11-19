#pragma once
#include "CGrayImgData.h"

template<class T>
class CImgEnhance:public CGrayImgData<T>
{
public:
    CImgEnhance(CGrayImgData<T>& other) : CGrayImgData(other) {}

    CImgEnhance() : CGrayImgData() {}

    virtual ~CImgEnhance() {}

    void AveragingFilter() {
        const static int coreSize = 5;
        static int core[coreSize][coreSize] = {};
        for (int i = 0; i < coreSize; i++)
            for (int j = 0; j < coreSize; j++)
                core[i][j] = 1;
        const static int totWeight = coreSize * coreSize;

        T* tmp = new T[nHeight * nWidth];
        for (int i = 0; i < nHeight * nWidth; i++) tmp[i] = pPixels[i];
        
        for (int i = 0; i <= nHeight - coreSize; i++)
            for (int j = 0; j <= nWidth - coreSize; j++) {
                int w = 0;
                for (int p = 0; p < coreSize; p++)
                    for (int q = 0; q < coreSize; q++)
                        w += core[p][q] * tmp[(i + p) * nWidth + j + q];
                pPixels[(i + coreSize / 2) * nWidth + j + coreSize / 2] =  w / totWeight;
            }
        delete[] tmp;
    }

    void GaussFilter() {
        const static double pi = acos(-1.0);
        const static double sigma = 0.001;
        const static double A = 1;
        const static int coreSize = 3;
        static double core[3][3] = {};
        double totWeight = 0;
        for (int i = 0; i < coreSize; i++)
            for (int j = 0; j < coreSize; j++) {
                core[i][j] = A * sqrt(2 * pi) * sigma 
                    * exp(- 2.0 * pi * pi * sigma * sigma * ((i - coreSize / 2) * (i - coreSize / 2) + (j - coreSize / 2) * (j - coreSize / 2)));
                totWeight += core[i][j];
            }
        for (int i = 0; i < coreSize; i++)
            for (int j = 0; j < coreSize; j++)
                core[i][j] /= totWeight;

        T* tmp = new T[nHeight * nWidth];
        for (int i = 0; i < nHeight * nWidth; i++) tmp[i] = pPixels[i];

        for (int i = 0; i <= nHeight - coreSize; i++)
            for (int j = 0; j <= nWidth - coreSize; j++) {
                double w = 0;
                for (int p = 0; p < coreSize; p++)
                    for (int q = 0; q < coreSize; q++)
                        w += core[p][q] * tmp[(i + p) * nWidth + j + q];
                pPixels[(i + coreSize / 2) * nWidth + j + coreSize / 2] = w;
            }
        delete[] tmp;
    }

    void Laplacian() {
        const static int coreSize = 3;
        const static int core[3][3] = {
            {1, 1, 1},
            {1, -8, 1},
            {1, 1, 1},
        };
        const static double a = 5.5;

        T* tmp = new T[nHeight * nWidth];
        for (int i = 0; i < nHeight * nWidth; i++) tmp[i] = pPixels[i];

        for (int i = 0; i <= nHeight - coreSize; i++)
            for (int j = 0; j <= nWidth - coreSize; j++) {
               int w = 0;
                for (int p = 0; p < coreSize; p++)
                    for (int q = 0; q < coreSize; q++)
                        w += core[p][q] * tmp[(i + p) * nWidth + j + q];
                if (w * a <=  pPixels[(i + coreSize / 2) * nWidth + j + coreSize / 2]) pPixels[(i + coreSize / 2) * nWidth + j + coreSize / 2] -= w * a;
                else pPixels[(i + coreSize / 2) * nWidth + j + coreSize / 2] = 0;
            }
        delete[] tmp;
    }
};

