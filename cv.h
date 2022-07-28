#ifndef CV_H
#define CV_H

#include "kfc.h"
#include "util.h"
#include "vector"
#include <iostream>
#include <QDebug>

using namespace std;

typedef class OPTICAL_FLOW
{
    void _computeGradX(KImageGray curImage, KImageDouble &I_x);
    void _computeGradY(KImageGray curImage, KImageDouble &I_y);
    void _computeGradT(KImageGray preImage, KImageGray curImage, KImageDouble &I_t);
    void _makeWeightedMask(KMatrix &weightedMask, const int maskSize);
public:
    void runOpticalFlow(KImageGray preImage, KImageGray curImage, KImageColor &output);
}OPTICALFLOW;

class cv
{
public:
    typedef struct _ShapeTableElement
    {
        double distance;
        double angle;
    }_ShapeTableElement;

    typedef struct _GeneralizedHoughResult
    {
        int x;
        int y;
        double angle;
        double scale;
    }GeneralizedHoughResult;

    typedef struct _Keypoint
    {
        int x,y;
        int angle;
    }Keypoint;

    typedef struct _ScaleInfo
    {
        double sigma;
    }ScaleInfo;

    class Descriptor
    {
    public:
        Descriptor()
        {
            data.resize(16);
            for(int i=0; i<16; i++) data[i].resize(8);
        }
        ~Descriptor(){};

        void print()
        {

        }

        vector<vector<int>> data; //16*8 vector
        int x, y;
        double octave;
    };

    class SiftDB : public vector<Descriptor>
    {
    public:
        SiftDB(){}
        ~SiftDB(){}
        SiftDB compare(SiftDB db, double threshold)
        {
            qDebug()<<"a size:"<<db.size()<<"b size"<<this->size();
            SiftDB intersection;

            if(db.size()==0 || this->size() ==0) return intersection;
            double low=euclideanDistance(db[0], this->at(0)), high=euclideanDistance(db[0], this->at(0));

            double sum = 0;
            double minDistance = 99999999;
            for(int i=0; i<db.size(); i++)
            {
                for(int j=0; j<this->size(); j++)
                {
                    double distance = euclideanDistance(db[i], this->at(j));

                    if(distance < minDistance) minDistance = distance;
                    if(high < distance) high = distance;
                    if(low > distance) low = distance;
                }

                if(minDistance < threshold)
                {
                    intersection.push_back(db[i]);
                }
                else
                {
                    Descriptor d;
                    d.x = -1;
                    d.y = -1;

                    intersection.push_back(d);
                }
            }

            qDebug()<<"low"<<low<<"high"<<high;
            return intersection;
        }

    private:
        double euclideanDistance(Descriptor a, Descriptor b)
        {
            double sum = 0;
            for(int i=0; i<16; i++)
            {
                for(int j=0; j<8; j++)
                {
                    sum += pow(a.data[i][j] - b.data[i][j],2);
                }
            }

            //qDebug()<<"distance :"<<sqrt(sum);
            return sqrt(sum);
        }

    };

    cv();
    ~cv();
    static void sepia(KImageColor &image, const double hue, const double saturation);
    static int otsuThreshold(const KImageGray &image);
    static void erode(const KImageGray &image, const KImageGray &result, int kernelSquareSize);
    static void dilate(const KImageGray &image, const KImageGray &result, int kernelSquareSize);
    static KImageColor labeling(const KImageGray &image, const KBlobList &);
    static void splitRGB(KImageColor rgbImage, KImageGray& r, KImageGray& g, KImageGray& b);
    static void equalizeHistogram(KImageColor &image);
    static void matchHistogram(KImageColor &image, const KImageColor &target);
    static void colorToGray(const KImageColor &color, KImageGray &gray);
    static void gaussianNoise(KImageGray &image);
    static KImageGray GaussianNoise(KImageGray &input, int variance);
    static KImageColor SaltPepperNoise(KImageColor &input, double threshold);
    static KImageColor GaussianNoise(KImageColor &input, int variance);
    static KImageColor Median(KImageColor &input, int mask);
    static KImageGray Median(KImageGray &input, int mask);
    static KImageGray GaussianFiltering(KImageGray &input, double sigma);
    static KImageDouble GaussianFiltering(KImageDouble &input, double sigma);
    static KImageColor GaussianFiltering(KImageColor &input, double sigma);
    static KImageGray boxFilter(const KImageGray &image, int kernelSquareSize);
    static KImageColor boxFilter(const KImageColor &image, int kernelSquareSize);
    static KImageGray CannyEdge(double sigma, double lowerThreshold,double opperThreshold,const KImageGray& image);
    static GeneralizedHoughResult generalizedHough(KImageGray image, vector<vector<cv::_ShapeTableElement>> &shapeTable);
    static KImageColor drawShape(KImageColor &result, KImageGray &image, vector<KPoint> &shapePoints, int shapeCenterX, int shapeCenterY, cv::GeneralizedHoughResult &r);
    static KImageColor circleHough(const KImageGray inputImg, const int voteTreshold, const int &minR, const int &maxR);
    static SiftDB generateSiftDb(const KImageGray &image, int octaveMinimumSize, int scaleInOctave, vector<vector<KImageDouble>> &scales, vector<vector<KImageDouble>> &dogs, vector<vector<KImageColor>> &keypointImage);
    static KImageDouble downSample(const KImageDouble image, double samplingRate);
    static KImageGray doubleImageToGray(const KImageDouble &image, double low, double high);
    static void getKeypoint(vector<vector<KImageDouble> > &scales, vector<vector<KImageDouble> > &dogs, vector<vector<vector<cv::Keypoint>>> &keypoints, const vector<vector<ScaleInfo> > &scaleInfos);
    static void getDescriptor(vector<vector<KImageDouble> > &scales, const vector<vector<ScaleInfo> > &scaleInfos, vector<vector<vector<cv::Keypoint>>> &keypoints, vector<Descriptor> &descriptors);
    static vector<KImageDouble> SCalesGaussian(KImageDouble &dimg, int imageInScale);
private:
    typedef struct _LabelEquivalence
    {
        int sequentialNumber;
        int equivalantNumber;
    }LabelEquivalence;

    static void optimizeLabelEquivalanceTable(const std::vector<cv::LabelEquivalence> &equivalanceTable, std::vector<cv::LabelEquivalence> &optimizedEquivalanceTable);

};

#endif // CV_H
