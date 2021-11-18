#pragma once
#include "CGrayImgData.h"
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

template<class T>
class CImgEnhance:public CGrayImgData<T>
{
public:
    CImgEnhance(CGrayImgData<T>& other) : CGrayImgData(other) {}

    CImgEnhance() : CGrayImgData() {}

    virtual ~CImgEnhance() {}

    void AveragingFilter() {
        const int coreSize = 5;
        static int core[coreSize][coreSize] = {};
        for (int i = 0; i < coreSize; i++)
            for (int j = 0; j < coreSize; j++)
                core[i][j] = 1;
        const int totWeight = coreSize * coreSize;

        T* tmp = new T[nHeight * nWidth];
        for (int i = 0; i < nHeight * nWidth; i++) tmp[i] = pPixels[i];
        
        for (int i = 0; i <= nHeight - coreSize; i++)
            for (int j = 0; j <= nWidth - coreSize; j++) {
                int w = 0;
                for (int p = 0; p < coreSize; p++)
                    for (int q = 0; q < coreSize; q++)
                        w += core[p][q] * tmp[(i + p) * nWidth + j + q];
                pPixels[(i + coreSize / 2) * nWidth + j + coreSize / 2] = w / totWeight;
            }
        delete[] tmp;
    }

    void GaussFilter() {
        const double pi = acos(-1.0);
        const double sigma = 0.01;
        const int coreSize = 3;
        double core[3][3] = {};
        double totWeight = 0;
        for (int i = 0; i < coreSize; i++)
            for (int j = 0; j < coreSize; j++) {
                core[i][j] = sqrt(2 * pi) * sigma 
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
        const int coreSize = 3;
        /*
        const static int core[5][5] = {
            {1, 1, 1, 1, 1},
            {1, 1, 2, 1, 1},
            {1, 2, 3, 2, 1},
            {1, 1, 2, 1, 1},
            {1, 1, 1, 1, 1}
        };
        */
        const int core[3][3] = {
            {0, -1, 0},
            {-1, 4, -1},
            {0, -1, 0},
        };
        const double a = 20.4;

        T* tmp = new T[nHeight * nWidth];
        for (int i = 0; i < nHeight * nWidth; i++) tmp[i] = pPixels[i];

        for (int i = 0; i <= nHeight - coreSize; i++)
            for (int j = 0; j <= nWidth - coreSize; j++) {
               int w = 0;
                for (int p = 0; p < coreSize; p++)
                    for (int q = 0; q < coreSize; q++)
                        w += core[p][q] * tmp[(i + p) * nWidth + j + q];
                if (a * w <= pPixels[(i + coreSize / 2) * nWidth + j + coreSize / 2]) pPixels[(i + coreSize / 2) * nWidth + j + coreSize / 2] -= a * w;
                else pPixels[(i + coreSize / 2) * nWidth + j + coreSize / 2] = 0;
            }
        delete[] tmp;
    }
};

