#pragma once
#include "CGrayImgData.h"
#include<utility>
#include<queue>
using std::pair;
using std::queue;

template<class T>
class CImgSegmentation: public CGrayImgData<T>
{
public:
    CImgSegmentation(CGrayImgData<T>& other) : CGrayImgData(other) {}

    CImgSegmentation() : CGrayImgData() {}

    virtual ~CImgSegmentation() {}

    int getTh(int x1, int y1, int x2, int y2) {
        int cnt[256] = {};

    }

    void SetSeed() {
        static int blockSz = min(nHeight, nWidth) / 3;
        for (int x = 0; x < nHeight; x+= blockSz)
            for (int y = 0; y < nWidth; y+= blockSz) {
                int mi = 255;
                pair<int, int> seedPos = { x, y };
                for (int i = x; i < min(x + blockSz, nHeight); i++) {
                    for (int j = y; j < min(y + blockSz, nWidth); j++)
                        if (pPixels[i * nWidth + j] < mi) {
                            int mi = pPixels[i * nWidth + j];
                            seedPos = { i, j };
                       }
                }
                q.push(seedPos);
            }
    }
    
    void RegionGrowing() {
        const static int dx[] = { 1, -1, 0, 0 };
        const static int dy[] = { 0, 0, 1, -1 };
        const static T th = 5;
        SetSeed();
        while (!q.empty()) {
            auto cur = q.front();
            int i = cur.first;
            int j = cur.second;
            q.pop();
            if (pPixels[i * nWidth + j] == 0) continue;
            for (int d = 0; d < 4; d++) {
                int ti = i + dx[d];
                int tj = j + dy[d];
                if (ti >= 0 && tj >= 0 && ti < nHeight && tj < nWidth) {
                    if (pPixels[ti * nWidth + tj] != 0) {
                        if(pPixels[i * nWidth + j] >= pPixels[ti * nWidth + tj] && pPixels[i * nWidth + j] - pPixels[ti * nWidth + tj] <= th)
                            q.push({ ti, tj });
                        else if (pPixels[i * nWidth + j] < pPixels[ti * nWidth + tj] && pPixels[ti * nWidth + tj] - pPixels[i * nWidth + j] <= th)
                            q.push({ ti, tj });
                    }             
                }
            }
            pPixels[i * nWidth + j] = 0;
        }
        for (int i = 0; i < nHeight * nHeight; i++)
            if (pPixels[i] != 0) pPixels[i] = 255;
    }

    void Segmentation() {
        RegionGrowing();
    }
protected:
    queue< pair<int, int> > q;
};

