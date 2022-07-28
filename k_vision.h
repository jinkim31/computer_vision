#ifndef K_VISION_H
#define K_VISION_H

#include "iostream"
#include "kfc.h"
#include "vector"
#include "map"
#include <algorithm>
#include <math.h>
#include "iostream"
#include "fstream"

using namespace std;

typedef struct HOUGHCIRCLE_INFO
{
    int nLeft;
    int nRight;
    int nTop;
    int nBottom;
    int nMinR;
    int nMaxR;
    int nNumGridCx;
    int nNumGridCy;
    int nNumGridR;
    int nDirEdge;
    int nThreshVote;
} HOUGHCIRCLE_INFO;

class K_VISION
{
public:
    K_VISION();

    KImageGray LCT(const int& a, const int& b, const int& a_, const int& b_, KImageGray img);
    KImageColor LCT(const double& a, const double& b, const double& a_, const double& b_, KImageColor img); // Luminance Contrast Transform

    KArray<KHSV> RGBtoHSV(KImageColor& inputImage);
    KImageColor HSVtoRGB(KArray<KHSV>& inputImage);
    void splitHSV(KArray<KHSV> hsvImage, KImageGray& h, KImageGray& s, KImageGray& v);
    void splitRGB(KImageColor rgbImage, KImageGray& r, KImageGray& g, KImageGray& b);
    void sepiaTone(KArray<KHSV>& image, double hue, double saturation);

    KImageGray Otsu(KImageGray &inputImage);
    void Labeling(KImageGray &inputImage, KImageGray  &outputImage, map<int, int> &equivalenceTable);

    KImageGray HE(KImageGray &inputImage);
    KImageColor HE(KImageColor &inputImage);

    KImageGray HM(KImageGray &srcImage, KImageGray &refImage);
    KImageColor HM(KImageColor &srcImage, KImageColor &refImage);

    KImageGray SaltPepperNoise(KImageGray &input, double threshold);
    KImageColor SaltPepperNoise(KImageColor &input, double threshold);

    KImageGray Median(KImageGray &input, int mask);
    KImageColor Median(KImageColor &input, int mask);

    KImageGray GaussianNoise(KImageGray &input, int variance);
    KImageColor GaussianNoise(KImageColor &input, int variance);

    KImageGray GaussianFiltering(KImageGray &input, double sigma);
    KImageColor GaussianFiltering(KImageColor &input, double sigma);

    KImageGray CannyEdge(double sigma, double dLow,double dHigh,const KImageGray& igIn);

    KImageColor CircleByHT(KEdge &opEdge, const KImageGray inputImg, const int voteTreshold, const int &minR, const int &maxR);
};
typedef struct tagSHAPE_TABLE
{
    double dDistance;
    double dAngle;
}SHAPE_TABLE;

typedef class GENERALIZED_HOUGH_TRANSFORM
{
    int nModelPtNum, nVoteThrshold, nScaleSize, nVoteSpaceHeight, nVoteSpaceWidth, nVoteSpaceAngle;
    double dMinScale, dMaxScale, dMaxAngle, dSAngle, dSScale ;
    std::vector<std::vector<std::vector<std::vector<double> > > > dVotingSpace;
    std::vector<SHAPE_TABLE> vShapeTable[4];
    KPOINTD dModelPtCen;
    std::vector<KPOINT> ptModel;

    void _ReadData();
    void _initShapeTable();
    void _NonMaxiaSuppresion();

public:

    void GHT_init(KImageGray input, const double &minScale, const double &maxScale, const int &voteThresh);
    void runGHT(KEdge &edgePixel);
    void drawModel(KImageColor &output);
}GHT;
#endif // K_VISION_H
