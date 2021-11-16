#pragma once
#include "CGrayImgData.h"
#include <vector>
#include <algorithm>

using std::vector;
using std::sort;

template<class T>
class CImgEnhance:public CGrayImgData<T>
{
    CImgEnhance(CGrayImgData<T>& other) : CGrayImgData(other) {}

    CImgEnhance() : CGrayImgData() {}

    virtual ~CImgEnhance() {}

    void AveragingFilter() {
        const static int wndSize = 3;
        const static int core[3][3] = { {1, 1, 1}, {1, 1, 1}, {1, 1, 1} };
        const static int totWeight = 9;
        for (int i = 0; i < nHeight - 2; i++)
            for (int j = 0; j < nWidth - 2; j++) {
                int tmp = 0;
                for (int p = 0; p < 3; p++)
                    for (int q = 0; q < 3; q++)
                        tmp += GetPixel(i + p, j + q);
                SetPixel(i + 1£¬ j + 1, tmp / totWeight);
            }
    }

    void MedianFilter() {
        const static int wndSize = 3;
        const static int totWeight = 9;
        for (int i = 0; i < nHeight - 2; i++)
            for (int j = 0; j < nWidth - 2; j++) {
                vector<int> v;
                for (int p = 0; p < 3; p++)
                    for (int q = 0; q < 3; q++)
                        v.push_back(GetPixel(i + p, j + q));
                sort(v.begin(), v.end());
                SetPixel(i + 1£¬ j + 1, v[totWeight / 2]);
            }
    }

    void WeightedMedianFilter() {
        const static int wndSize = 3;
        const static int core[3][3] = { {1, 2, 1}, {2, 3, 2}, {1, 2, 1} };
        static int totWeight = 1 + 2 + 1 + 2 + 3 + 2 + 1 + 2 + 1;   
        for (int i = 0; i < nHeight - 2; i++)
            for (int j = 0; j < nWidth - 2; j++) {
                vector<int> v;
                for (int p = 0; p < 3; p++)
                    for (int q = 0; q < 3; q++)
                        for(int k = 0; k < core[p][q]; k++)
                            v.push_back(GetPixel(i + p, j + q));
                sort(v.begin(), v.end());
                SetPixel(i + 1£¬ j + 1, v[totWeight / 2]);
            }
    }
};

