#include "cv.h"
#include "QDebug"

#define sign( x ) ((x) > 0 ? 1 : ((x) == 0 ? 0: (-1)))

cv::cv()
{

}

cv::~cv()
{

}

void cv::sepia( KImageColor &image, const double hue, const double saturation)
{
    KArray<KHSV> hsvArray;
    image.RGBtoHSV(hsvArray);

    for(int i=0; i<hsvArray.Col(); i++)
    {
        for(int j=0; j<hsvArray.Row(); j++)
        {
            hsvArray[j][i].h = hue;
            hsvArray[j][i].s = saturation;
        }
    }

    image.FromHSV(hsvArray);
}

int cv::otsuThreshold(const KImageGray &image)
{
    int n[256];
    double p[256];
    for(int i=0; i<256; i++)
    {
        n[i] = 0;
        p[0] = 0;
    }


    //get p[]
    int intensitySum = 0;
    for(int i=0; i < image.Row(); i++)
    {
        for(int j=0; j<image.Col(); j++)
        {
            n[image[i][j]]++;
            intensitySum+=image[i][j];
        }
    }

    //get N, n[]
    int N = image.Row()*image.Col();
    for(int i=0; i<256; i++)
    {
        p[i] = (double)n[i]/N;
    }

    int tArgmin = 0;
    double minvar =-1;
    double q1 = 0, q2 = 0;
    double u1=0, u2 = 0;
    double var1, var2, var;

    for(int t=1; t<256; t++)
    {
        q1 = 0;
        for(int i=0; i<=t; i++)
        {
            q1 += p[i];
        }

        q2 = 0;
        for(int i=t+1; i<=256; i++)
        {
            q2 += p[i];
        }

        u1 = 0;
        for(int i=0; i<=t; i++)
        {
            u1 += i*p[i]/q1;
        }

        u2 = 0;
        for(int i=t+1; i<=256; i++)
        {
            u2 += i*p[i]/q2;
        }

        var1 = 0;
        for(int i=0; i<=t; i++)
        {
            var1+=(pow(i-u1,2) * p[i] / q1);
        }

        var2 = 0;
        for(int i=t+1; i<=256; i++)
        {
            var2+=(pow(i-u2,2) * p[i] / q2);
        }

        var = var1 + var2;

        if(!isnan(var) && minvar == -1 || var < minvar)
        {
            minvar = var;
            tArgmin = t;
        }
    }

    for(int i=0; i < image.Row(); i++)
    {
        for(int j=0; j<image.Col(); j++)
        {
            if(image[i][j] > tArgmin) image[i][j] = 255;
            else image[i][j] = 0;
        }
    }

    return tArgmin;
}

void cv::erode(const KImageGray &image, const KImageGray &result, int kernelSquareSize)
{
    int margin = (kernelSquareSize-1)/2;

    qDebug()<<"image size : "<<image.Row()<<"*"<<image.Col()<<"\n";
    for(int i=margin; i < image.Row()-margin; i++)
    {
        for(int j=margin; j<image.Col()-margin; j++)
        {
            if(kernelSquareSize == 3)
            {
                if(image[i-1][j-1] && image[i][j-1] && image[i+1][j-1] &&
                   image[i-1][j] && image[i][j] && image[i+1][j] &&
                   image[i-1][j+1] && image[i][j+1] && image[i+1][j+1]) result[i][j] = 255;
                else result[i][j] = 0;
            }
            else if(kernelSquareSize == 5)
            {
                if(image[i-2][j-2] && image[i-1][j-2] && image[i+0][j-2] && image[i+1][j-2] && image[i+2][j-2] &&
                   image[i-2][j-1] && image[i-1][j-1] && image[i+0][j-1] && image[i+1][j-1] && image[i+2][j-1] &&
                   image[i-2][j+0] && image[i-1][j+0] && image[i+0][j+0] && image[i+1][j+0] && image[i+2][j+0] &&
                   image[i-2][j+1] && image[i-1][j+1] && image[i+0][j+1] && image[i+1][j+1] && image[i+2][j+1] &&
                   image[i-2][j+2] && image[i-1][j+2] && image[i+0][j+2] && image[i+1][j+2] && image[i+2][j+2]) result[i][j] = 255;
                else result[i][j] = 0;
            }
        }
    }
    qDebug()<<"done\n";
}

void cv::dilate(const KImageGray &image, const KImageGray &result, int kernelSquareSize)
{
    int margin = (kernelSquareSize-1)/2;

    qDebug()<<"image size : "<<image.Row()<<"*"<<image.Col()<<"\n";
    for(int i=margin; i < image.Row()-margin; i++)
    {
        for(int j=margin; j<image.Col()-margin; j++)
        {
            if(kernelSquareSize == 3)
            {
                if(image[i-1][j-1] || image[i][j-1] && image[i+1][j-1] &&
                   image[i-1][j] && image[i][j] && image[i+1][j] &&
                   image[i-1][j+1] && image[i][j+1] && image[i+1][j+1]) result[i][j] = 255;
                else result[i][j] = 0;
            }
            else if(kernelSquareSize == 5)
            {
                if(image[i-2][j-2] || image[i-1][j-2] || image[i+0][j-2] || image[i+1][j-2] || image[i+2][j-2] ||
                   image[i-2][j-1] || image[i-1][j-1] || image[i+0][j-1] || image[i+1][j-1] || image[i+2][j-1] ||
                   image[i-2][j+0] || image[i-1][j+0] || image[i+0][j+0] || image[i+1][j+0] || image[i+2][j+0] ||
                   image[i-2][j+1] || image[i-1][j+1] || image[i+0][j+1] || image[i+1][j+1] || image[i+2][j+1] ||
                   image[i-2][j+2] || image[i-1][j+2] || image[i+0][j+2] || image[i+1][j+2] || image[i+2][j+2]) result[i][j] = 255;
                else result[i][j] = 0;
            }
        }
    }
}

KImageColor cv::labeling(const KImageGray &image, const KBlobList& blobList)
{
    KArray<int> labeledImage(image.Row(), image.Col());
    for(int i=0; i < image.Row(); i++)
    {
        for(int j=0; j<image.Col(); j++)
        {
            labeledImage[i][j] = 0;
        }
    }
    int newLabelNum = 1;

   std::vector<LabelEquivalence> equivalanceTable;

    for(int i=0; i < image.Row()-1; i++)
    {
        for(int j=0; j<image.Col()-1; j++)
        {
            if(image[i][j] != 0)
            {
                if(j-1!=-1 && i-1!= -1 && image[i][j-1] != 0 && image[i-1][j] != 0)
                {
                    if(labeledImage[i][j-1] != labeledImage[i-1][j])
                    {
                        equivalanceTable.push_back(LabelEquivalence{labeledImage[i][j-1],labeledImage[i-1][j]});
                        //qDebug()<<"new eq "<<labeledImage[i][j-1]<<">"<<labeledImage[i-1][j]<<"\n";
                    }
                    labeledImage[i][j] = labeledImage[i-1][j];
                }
                else if(j-1!=-1 && i-1!= -1 && image[i][j-1] != 0) labeledImage[i][j] = labeledImage[i][j-1];
                else if(j-1!=-1 && i-1!= -1 && image[i-1][j] != 0) labeledImage[i][j] = labeledImage[i-1][j];
                else
                {
                    //qDebug()<<"new label"<<newLabelNum<<"\n";
                    labeledImage[i][j] = newLabelNum++;
                }
            }
        }
    }

    qDebug()<<"label n : "<<newLabelNum<<"\n";
    for(int i=0; i<equivalanceTable.size(); i++) qDebug()<<equivalanceTable[i].sequentialNumber<<" -> "<<equivalanceTable[i].equivalantNumber<<"\n";


    std::vector<LabelEquivalence> optimizedEquivalanceTable;
    cv::optimizeLabelEquivalanceTable(equivalanceTable, optimizedEquivalanceTable);

    for(int i=0; i < image.Row(); i++)
    {
        for(int j=0; j<image.Col(); j++)
        {
            int sequentialLabelNum = labeledImage[i][j];

            for(int k=0; k < optimizedEquivalanceTable.size(); k++)
            {
                if(optimizedEquivalanceTable[k].sequentialNumber == sequentialLabelNum)
                {
                    labeledImage[i][j] =optimizedEquivalanceTable[k].equivalantNumber;
                }
            }
        }
    }

    KArray<KHSV> colorArray(image.Row(), image.Col());
    for(int i=0; i < image.Row(); i++)
    {
        for(int j=0; j<image.Col(); j++)
        {
            if(labeledImage[i][j] != 0)
            {
            colorArray[i][j].h = labeledImage[i][j]%255;
            colorArray[i][j].s = 255;
            colorArray[i][j].v = 255;
            }
        }
    }
    KImageColor displayImage;
    displayImage.FromHSV(colorArray);
    return displayImage;
}

void cv::equalizeHistogram(KImageColor &image)
{
    KArray<KHSV> hsvImage;
    image.RGBtoHSV(hsvImage);

    KImageGray vImage(image.Row(), image.Col());

    for(int i=0; i<image.Row(); i++)
    {
        for(int j=0; j<image.Col(); j++)
        {
            vImage[i][j]=hsvImage[i][j].v;
        }
    }

    KHisto histogram(vImage);
    double* dpHisto = histogram.Address();

    for(int i=1; i<histogram.Dim(); i++) dpHisto[i] += dpHisto[i-1];
    for(int i=0; i<histogram.Dim(); i++) dpHisto[i] /= (double)vImage.Size();

    for(int i=0; i<image.Row(); i++)
    {
        for(int j=0; j<image.Col(); j++)
        {
            vImage[i][j] = (unsigned char)(dpHisto[vImage[i][j]]*255);
        }
    }

    for(int i=0; i<image.Row(); i++)
    {
        for(int j=0; j<image.Col(); j++)
        {
            hsvImage[i][j].v = vImage[i][j];
        }
    }

    image.FromHSV(hsvImage);

}

void cv::matchHistogram(KImageColor &image, const KImageColor &target)
{
    KImageGray imageR(image.Row(), image.Col());
    KImageGray imageG(image.Row(), image.Col());
    KImageGray imageB(image.Row(), image.Col());
    KImageGray targetR(image.Row(), image.Col());
    KImageGray targetG(image.Row(), image.Col());
    KImageGray targetB(image.Row(), image.Col());

    for(int i=0; i<image.Row(); i++)
    {
        for(int j=0; j<image.Col(); j++)
        {
            imageR[i][j]=image[i][j].r;
            imageG[i][j]=image[i][j].g;
            imageB[i][j]=image[i][j].b;
            targetR[i][j]=target[i][j].r;
            targetG[i][j]=target[i][j].g;
            targetB[i][j]=target[i][j].b;
        }
    }

    KHisto imageHistogramR, imageHistogramG, imageHistogramB, targetHistogramR, targetHistogramG, targetHistogramB;
    imageHistogramR.HEQ(imageR);
    imageHistogramG.HEQ(imageG);
    imageHistogramB.HEQ(imageB);
    targetHistogramR.HEQ(targetR);
    targetHistogramG.HEQ(targetG);
    targetHistogramB.HEQ(targetB);

    KHisto transferHistogramR(256);
    KHisto transferHistogramG(256);
    KHisto transferHistogramB(256);


    for(int i=0; i<256; i++)
    {
        double minDiffR = 1, minDiffG = 1, minDiffB = 1;
        int rArgminR = -1, rArgminG = -1, rArgminB = -1;
        for(int j=0; j<256; j++)
        {
            double diffR = fabs(imageHistogramR[i] - targetHistogramR[j]);
            if(diffR < minDiffR)
            {
                minDiffR = diffR;
                rArgminR = j;
            }
            double diffG = fabs(imageHistogramG[i] - targetHistogramG[j]);
            if(diffG < minDiffG)
            {
                minDiffG = diffG;
                rArgminG = j;
            }
            double diffB = fabs(imageHistogramB[i] - targetHistogramB[j]);
            if(diffB < minDiffB)
            {
                minDiffB = diffB;
                rArgminB = j;
            }
        }

        transferHistogramR[i] =rArgminR;
        transferHistogramG[i] =rArgminG;
        transferHistogramB[i] =rArgminB;
    }

    for(int i=0; i<image.Row(); i++)
    {
        for(int j=0; j<image.Col(); j++)
        {
            image[i][j].r = (unsigned char)(transferHistogramR[image[i][j].r]);
            image[i][j].g = (unsigned char)(transferHistogramG[image[i][j].g]);
            image[i][j].b = (unsigned char)(transferHistogramB[image[i][j].b]);
        }
    }
}

void cv::colorToGray(const KImageColor &color, KImageGray &gray)
{
    gray = KImageGray(color.Row(), color.Col());

    for(int i=0; i<color.Row(); i++)
    {
        for(int j=0; j<color.Col(); j++)
        {
            gray[i][j] = (color[i][j].r + color[i][j].g + color[i][j].b) / 3;
        }
    }
}

void cv::gaussianNoise(KImageGray &image)
{
    unsigned char a;

    KGaussian g(0,10);
    for(int i=0; i<image.Row(); i++)
    {
        for(int j=0; j<image.Col(); j++)
        {
            a = util::limit<int>(image[i][j]+g.Generate() , 0, 255);
            image[i][j] = a;

            //qDebug()<<g.Generate();
        }
    }
}

void cv::optimizeLabelEquivalanceTable(const std::vector<cv::LabelEquivalence> &equivalanceTable, std::vector<cv::LabelEquivalence> &optimizedEquivalanceTable)
{
    for(int i=0; i<equivalanceTable.size(); i++)
    {
        int sequentialNumber = equivalanceTable[i].equivalantNumber;

        for(int j=equivalanceTable.size()-1; j >= 0; j--)
        {
            if(equivalanceTable[j].sequentialNumber == sequentialNumber)
            {
                sequentialNumber = equivalanceTable[j].equivalantNumber;
            }
        }

        optimizedEquivalanceTable.push_back(LabelEquivalence{equivalanceTable[i].sequentialNumber, sequentialNumber});

    }

    //qDebug()<<"s : "<<equivalanceTable.size()<<"\n";
    //for(int i=0; i<optimizedEquivalanceTable.size(); i++) qDebug()<<optimizedEquivalanceTable[i].sequentialNumber<<" -> "<<optimizedEquivalanceTable[i].equivalantNumber<<"\n";
}

KImageColor cv::SaltPepperNoise(KImageColor &input, double threshold)
{
    KRandom random;
    random.OnRandom(1000000);
    KImageColor ouput(input.Row(), input.Col());
    double whiteNoise = 1 - threshold;
    double blackNoise = threshold;
    for(int y = 0; y < input.Row(); y++)
        for(int x = 0; x < input.Col(); x++)
        {
            double rand = random.Generate();
            if(rand>whiteNoise)
            {
                ouput._ppA[y][x].r = (unsigned char)255;
                ouput._ppA[y][x].g = (unsigned char)255;
                ouput._ppA[y][x].b = (unsigned char)255;
            }
            else if(rand < blackNoise)
            {
                ouput._ppA[y][x].r = (unsigned char)0;
                ouput._ppA[y][x].g = (unsigned char)0;
                ouput._ppA[y][x].b = (unsigned char)0;
            }
            else
            {
                ouput._ppA[y][x].r = (unsigned char)input._ppA[y][x].r;
                ouput._ppA[y][x].g = (unsigned char)input._ppA[y][x].g;
                ouput._ppA[y][x].b = (unsigned char)input._ppA[y][x].b;
            }
        }
    return ouput;
}

KImageGray cv::GaussianNoise(KImageGray &input, int variance)
{
    KGaussian gaussian;
    gaussian.Create(0,variance);
    gaussian.OnRandom(10000);
    KImageGray output(input.Row(), input.Col());
    for(int y = 0; y < input.Row(); y++)
        for(int x = 0; x < input.Col(); x++)
        {
            double n = gaussian.Generate();
            int data = (input._ppA[y][x] + n) < 0 ? 0 : ( (input._ppA[y][x] + n) > 255 ? 255 : (input._ppA[y][x] + n));
            output._ppA[y][x] = (unsigned char)data;
        }
    return output;
}

KImageColor cv::GaussianNoise(KImageColor &input, int variance)
{
    KImageColor outputImage(input.Row(), input.Col());

    vector<KImageGray> rgbsplit(3);
    splitRGB(input, rgbsplit[0], rgbsplit[1], rgbsplit[2]);

    vector<KImageGray> result(3);

    result[0] = GaussianNoise(rgbsplit[0], variance);
    result[1] = GaussianNoise(rgbsplit[1], variance);
    result[2] = GaussianNoise(rgbsplit[2], variance);

    for(int y = 0; y < input.Row(); y++)
        for(int x = 0; x < input.Col(); x++)
        {
            outputImage._ppA[y][x].r = (unsigned char)result[0]._ppA[y][x];
            outputImage._ppA[y][x].g = (unsigned char)result[1]._ppA[y][x];
            outputImage._ppA[y][x].b = (unsigned char)result[2]._ppA[y][x];
        }
    return outputImage;
}

KImageGray cv::Median(KImageGray &input, int mask)
{
    int center = (mask*mask+1)/2;
    vector<int> median;
    int maskNUm = (mask-1)/2;

    KImageGray output(input.Row(), input.Col());
    for(int y = 0; y < input.Row(); y++)
        for(int x = 0; x < input.Col(); x++)
        {
            for(int j = 0; j < mask; j++)
                for(int i = 0; i < mask; i++)
                {
                    int nX = x-maskNUm+i;
                    int nY = y+j;
                    if(nX <= 0 || nX > input.Col()-1 || nY <= 0 || nY > input.Row()-1)    continue;
                    int data = input._ppA[nY][nX];
                    median.push_back(data);
                }
            sort(median.begin(), median.end());
            output._ppA[y][x] = (unsigned char)median[center];
            median.clear();
        }

    return output;
}

KImageColor cv::Median(KImageColor &input, int mask)
{
    KImageColor outputImage(input.Row(), input.Col());

    vector<KImageGray> rgbsplit(3);
    splitRGB(input, rgbsplit[0], rgbsplit[1], rgbsplit[2]);

    vector<KImageGray> result(3);

    result[0] = Median(rgbsplit[0],mask);
    result[1] = Median(rgbsplit[1],mask);
    result[2] = Median(rgbsplit[2],mask);

    for(int y = 0; y < input.Row(); y++)
        for(int x = 0; x < input.Col(); x++)
        {
            outputImage._ppA[y][x].r = (unsigned char)result[0]._ppA[y][x];
            outputImage._ppA[y][x].g = (unsigned char)result[1]._ppA[y][x];
            outputImage._ppA[y][x].b = (unsigned char)result[2]._ppA[y][x];
        }

    return outputImage;
}

KImageGray cv::boxFilter(const KImageGray &image, int kernelSquareSize)
{
    KImageGray result(image.Row(), image.Col());
    int margin = (kernelSquareSize-1)/2;

    qDebug()<<"image size : "<<image.Row()<<"*"<<image.Col()<<"\n";
    for(int i=margin; i < image.Row()-margin; i++)
    {
        for(int j=margin; j<image.Col()-margin; j++)
        {
            int sum =0;
            for(int k=0; k<kernelSquareSize; k++)
            {
                for(int l=0; l<kernelSquareSize; l++)
                {
                    //qDebug()<<i-margin+k<<"."<<j-margin+l;
                    sum += image[i-margin+k][j-margin+l];
                }
            }

            result[i][j] = sum/(kernelSquareSize*kernelSquareSize);
        }
    }
    qDebug()<<"done\n";
    return result;
}


KImageColor cv::boxFilter(const KImageColor &image, int kernelSquareSize)
{
    KImageColor outputImage(image.Row(), image.Col());

    vector<KImageGray> rgbsplit(3);
    splitRGB(image, rgbsplit[0], rgbsplit[1], rgbsplit[2]);

    vector<KImageGray> result(3);

    result[0] = boxFilter(rgbsplit[0],kernelSquareSize);
    result[1] = boxFilter(rgbsplit[1],kernelSquareSize);
    result[2] = boxFilter(rgbsplit[2],kernelSquareSize);

    for(int y = 0; y < image.Row(); y++)
        for(int x = 0; x < image.Col(); x++)
        {
            outputImage._ppA[y][x].r = (unsigned char)result[0]._ppA[y][x];
            outputImage._ppA[y][x].g = (unsigned char)result[1]._ppA[y][x];
            outputImage._ppA[y][x].b = (unsigned char)result[2]._ppA[y][x];
        }

    return outputImage;
}

KImageGray cv::CannyEdge(double sigma, double dLow, double dHigh, const KImageGray &igIn)
{
    double width = igIn.Col();
    double height = igIn.Row();
    KImageGray igOut(height, width);
    KImageGray ig22(height, width);
    KImageGray ligOut(height, width);

    double dSigma = sigma;

    KEdge FDG;
    FDG.Create(dSigma);
    FDG.Gradient(igIn, ig22);

    int half = (int)(3.0*dSigma+0.3);

    vector<vector<double>> mask;
    vector<double> _mask(half*2+1);
    for(int k = 0; k < half*2+1; k++)
        mask.push_back(_mask);

    double _sigma = 2.0*(sigma*sigma);
    double _const = 1.0/(2*M_PI*sigma*sigma);
    double scale = 0;

    for(int i = -half, r=0; i < half; i++,r++)
    {
        for(int j = -half,c=0; j < half; j++,c++)
        {
            mask[r][c] = _const*exp(-(i*i+j*j)/_sigma);
            scale     +=  mask[r][c];
        }
    }
    // nomalize
    for(int i = -half, r =0; i < half; i++,r++)
        for(int j = -half, c = 0; j < half; j++,c++)
            mask [r][c] /= scale;


    half = FDG.Half(); // ch!
    vector<vector<double>> magnitude;
    magnitude.assign(height, vector<double>(width, 0.0));
    vector<vector<double>> angle;
    vector<vector<double>> _idBuf;

    _idBuf = angle = magnitude;

    double gradientX, gradientY, temp;
    KImageGray dir(height, width);

    for(int y = half; y < height - half; y++)
    {
        for(int x = half; x < width - half; x++)
        {
            gradientX = gradientY = 0.0;

            for(int r = -half,rr = 0; r <= half; r++,rr++)
                for(int c = -half,cc = 0; c <= half; c++, cc++)
                {
                    gradientX += igIn._ppA[y+r][x+c] * FDG.KernelX()._ppA[rr][cc];
                    gradientY += igIn._ppA[y+r][x+c] * FDG.KernelY()._ppA[rr][cc];
                }
            //magnitude
            magnitude[y][x] = _ABS(gradientX) + _ABS(gradientY);
            if( magnitude[y][x] > dLow)
            {
                temp =  atan((float)gradientY/(float)gradientX);

                temp = fmod(temp, 360.0);
                angle[y][x] = (unsigned short)(temp+0.5);               //0~360
                dir._ppA[y][x] = (unsigned char)((((int)(temp/22.5)+1)>>1) & 0x00000003); //0~3

            }
            else
                magnitude[y][x] = 0.0;

        }
    }

    KImageGray ImgBuf(height, width);

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(dir._ppA[y][x] == 0)
            {
                if(magnitude[y][x] < magnitude[y][x+1] || magnitude[y][x] < magnitude[y][x-1])
                    igOut._ppA[y][x] = 0;
                else
                {
                    if(magnitude[y][x] > dHigh)
                        igOut._ppA[y][x] = 255;
                    else if((magnitude[y][x] > dLow) && (magnitude[y][x] < dHigh))
                        ImgBuf._ppA[y][x] = 1;
                    else if(magnitude[y][x] < dLow)
                        igOut._ppA[y][x] = 0;
                }
            }
            else if(dir._ppA[y][x] == 1)
            {
                if(magnitude[y][x] < magnitude[y-1][x+1] || magnitude[y][x] < magnitude[y+1][x-1])
                    igOut._ppA[y][x] = 0;
                else
                {
                    if(magnitude[y][x] > dHigh)
                        igOut._ppA[y][x] = 255;
                    else if((magnitude[y][x] > dLow) && (magnitude[y][x] < dHigh))
                        ImgBuf._ppA[y][x] = 1;
                    else if(magnitude[y][x] < dLow)
                        igOut._ppA[y][x] = 0;
                }
            }
            else if(dir._ppA[y][x] == 2)
            {
                if(magnitude[y][x] < magnitude[y-1][x] || magnitude[y][x] < magnitude[y+1][x])
                    igOut._ppA[y][x] = 0;
                else
                {
                    if(magnitude[y][x] > dHigh)
                        igOut._ppA[y][x] = 255;
                    else if((magnitude[y][x] > dLow) && (magnitude[y][x] < dHigh))
                        ImgBuf._ppA[y][x] = 1;
                    else if(magnitude[y][x] < dLow)
                        igOut._ppA[y][x] = 0;
                }
            }
            else if(dir._ppA[y][x] == 3)
            {
                if(magnitude[y][x] < magnitude[y+1][x+1] || magnitude[y][x] < magnitude[y-1][x-1])
                    igOut._ppA[y][x] = 0;
                else
                {
                    if(magnitude[y][x] > dHigh)
                        igOut._ppA[y][x] = 255;
                    else if((magnitude[y][x] > dLow) && (magnitude[y][x] < dHigh))
                        ImgBuf._ppA[y][x] = 1;
                    else if(magnitude[y][x] < dLow)
                        igOut._ppA[y][y] = 0;
                }
            }
        }
    }


    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(ImgBuf._ppA[y][x] == 1)
            {
                if(dir._ppA[y][x] == 0)
                {
                    if(igOut._ppA[y][x+1] == 255 && igOut._ppA[y][x-1] == 255)
                        igOut._ppA[y][x] = 255;
                    else
                        igOut._ppA[y][x] = 0;
                }
                else if(dir._ppA[y][x] == 1)
                {
                    if( igOut._ppA[y-1][x+1] == 255 && igOut._ppA[y+1][x-1] == 255)
                        igOut._ppA[y][x] = 255;
                    else
                        igOut._ppA[y][x] = 0;

                }
                else if(dir._ppA[y][x] == 2)
                {
                    if(igOut._ppA[y-1][x] == 255 && igOut._ppA[y+1][x] == 255)
                        igOut._ppA[y][x] = 255;
                    else
                        igOut._ppA[y][x] = 0;
                }
                else if(dir._ppA[y][x] == 3)
                {
                    if(igOut._ppA[y+1][x+1] == 255 && igOut._ppA[y-1][x-1] == 255)
                        igOut._ppA[y][x] = 255;
                    else
                        igOut._ppA[y][x] = 0;
                }

            }
        }
    }

    return igOut;
}

cv::GeneralizedHoughResult cv::generalizedHough(KImageGray image, vector<vector<_ShapeTableElement> > &shapeTable)
{
    double sigma =1.0;
    double low  = 40;
    double high = 80;

    double dMaxAngle = 360.0;
    double dSAngle = 10.0;
    double dSScale = 0.2;
    double dMinScale =0.6, dMaxScale=0.9;
    double nScaleSize = (int)(1 + (1.0 - dMinScale)/dSScale + (dMaxScale - 1.0)/dSScale);

    double nVoteSpaceHeight = image.Col();
    double nVoteSpaceWidth = image.Row();
    double nVoteSpaceAngle = (int)(dMaxAngle/dSAngle);

    KRect imgRoi;
    imgRoi.Create(0, 0, image.Col(), image.Row());
    KEdge edge;
    edge.Create(sigma);
    edge.Canny(low, high,imgRoi, image);

    int edgeSize = edge.Count();
    KEDGEPIXEL tempEdge;
    std::vector<std::vector<std::vector<std::vector<double> > > > dVotingSpace;

    dVotingSpace.clear();
    dVotingSpace.resize(nVoteSpaceHeight);
    for(int i = 0; i < nVoteSpaceHeight; i++){
        dVotingSpace[i].resize(nVoteSpaceWidth);
        for(int j = 0; j< nVoteSpaceWidth; j++){
            dVotingSpace[i][j].resize(nVoteSpaceAngle);
            for(int k = 0; k < nVoteSpaceAngle; k++){
                dVotingSpace[i][j][k].resize(nScaleSize);
                for(int l = 0; l< nScaleSize; l++){
                    dVotingSpace[i][j][k][l] = 0;
                }
            }
        }
    }

    for(int x = 0; x < edgeSize; x++)
    {
        for(double dAng = 0.0; dAng<(double)dMaxAngle; dAng += dSAngle)
        {
            edge.Pop(tempEdge);
            int nAng = (int)(dAng/dSAngle);
            double dTmp = tempEdge.wAng - dAng;

            int nDir = ((((int)(dTmp/22.5)+1)>>1) & 0x00000003);

            for(int i = 0; i<shapeTable[nDir].size(); i++)
            {
                for(double dScale = dMinScale; dScale <= dMaxScale; dScale += dSScale)
                {
                    int nScale = (int)((dScale - dMinScale)/dSScale);

                    double Cx = tempEdge.u - (dScale * shapeTable[nDir][i].distance) * cos(shapeTable[nDir][i].angle + _RADIAN(dAng));
                    double Cy = tempEdge.v - (dScale * shapeTable[nDir][i].distance) * sin(shapeTable[nDir][i].angle + _RADIAN(dAng));

                    int nCx = (int)(Cx+0.5);
                    int nCy = (int)(Cy+0.5);

                    for(int ii=-1; ii<2; ii++)
                        for(int jj=-1; jj<2; jj++)
                            for(int kk=-1; kk<2; kk++)
                                for(int ll=-1; ll<2; ll++)
                                {
                                    if(nCy+ii<0 || nCx+jj< 0 || nAng+kk< 0 || nScale + ll < 0)
                                        continue;
                                    if(nCy+ii>=nVoteSpaceHeight || nCx+jj>= nVoteSpaceWidth || nAng+kk >= nVoteSpaceAngle || nScale + ll >= nScaleSize)
                                        continue;
                                    dVotingSpace[nCy+ii][nCx+jj][nAng+kk][nScale + ll] += 0.7;
                                }

                    if(nCy<0 || nCx< 0 || nAng< 0 || nScale< 0)
                        continue;
                    if(nCy>=nVoteSpaceHeight || nCx>= nVoteSpaceWidth || nAng >= nVoteSpaceAngle || nScale>= nScaleSize)
                        continue;
                    dVotingSpace[nCy][nCx][nAng][nScale] += 0.3;
                }
            }
        }
    }

    for(int i = 1; i < nVoteSpaceHeight - 1; i++){
        for(int j = 1; j < nVoteSpaceWidth - 1; j++){
            for(int k = 1; k < nVoteSpaceAngle - 1; k++){
                for(int l = 1; l < nScaleSize -1; l++){
                    bool Maximum_flag = true;
                    for(int ii = -1; ii <= 1 && Maximum_flag; ii++)
                        for(int jj = -1; jj <= 1 && Maximum_flag; jj++)
                            for(int kk = -1; kk <= 1 && Maximum_flag; kk++){
                                for(int ll = -1; ll <= 1 && Maximum_flag; ll++){
                                    if(dVotingSpace[i+ii][j+jj][k+kk][l+ll] > dVotingSpace[i][j][k][l]){
                                        dVotingSpace[i][j][k][l] = 0;
                                        Maximum_flag = false;
                                    }
                                }
                            }
                }
            }
        }
    }

    double dMaxVotes = 0.0;
    double Cx = 0.0;
    double Cy = 0.0;
    double dAng = 0.0;
    double dScale = 0.1;

    for(int i = 0; i < nVoteSpaceHeight; i++){
        for(int j = 0; j< nVoteSpaceWidth; j++){
            for(int k = 0; k < nVoteSpaceAngle; k++){
                for(int l = 0; l< nScaleSize; l++){
                    if(dMaxVotes < dVotingSpace[i][j][k][l]){
                        dMaxVotes = dVotingSpace[i][j][k][l];
                        Cx = j;
                        Cy = i;
                        dAng = k * dSAngle;
                        dScale = (l * dSScale) + dMinScale;
                    }
                }
            }
        }
    }

    qDebug()<<"result : ("<<Cx<<"."<<Cy<<")"<<" X"<<dScale<<"angle:"<<dAng;

    cv::GeneralizedHoughResult r;
    r.x = Cx;
    r.y = Cy;
    r.angle = dAng/180.0*3.141592;
    r.scale = dScale;

    return r;
}

KImageColor cv::drawShape(KImageColor &result, KImageGray &image, vector<KPoint> &shapePoints, int shapeCenterX, int shapeCenterY, cv::GeneralizedHoughResult &r)
{
    for(int i=0; i<shapePoints.size(); i++)
    {
        int x = (r.x + r.scale*(shapePoints[i]._dX - shapeCenterX)*cos(r.angle) - r.scale*(shapePoints[i]._dY - shapeCenterY)*sin(r.angle));
        int y = (r.y + r.scale*(shapePoints[i]._dX - shapeCenterX)*sin(r.angle) + r.scale*(shapePoints[i]._dY - shapeCenterY)*cos(r.angle));

        result[y][x].r = 255;
        result[y][x].g = 0;
        result[y][x].b = 0;
    }

    return result;
}

KImageColor cv::circleHough(const KImageGray image, const int voteTreshold, const int &minR, const int &maxR)
{

    double sigma =1.0;
    double low  = 40;
    double high = 80;

    KRect imgRoi;
    imgRoi.Create(0, 0, image.Col(), image.Row());
    KEdge edge;
    edge.Create(sigma);
    edge.Canny(low, high,imgRoi, image);

    double width = image.Col();
    double height = image.Row();
    KImageGray temp = image;
    KImageColor outputImg;
    temp.GrayToRGB(outputImg);


    double nLeft       = -1;    // ROI
    double nRight      = 1;     // ROI
    double nTop        = -1;   // ROI
    double nBottom     = 1;   // ROI
    double nMinR       = minR;   // 반지름이 너무 작을 경우
    double nMaxR       = maxR; // 반지름이 너무 클 경우
    double nNumGridCx  = image.Col();    // Cell의 크기 X
    double nNumGridCy  = image.Row();   // Cell의 크기 Y
    double nNumGridR   = nMaxR - nMinR; // Cell의 크기 Radius
    double nDirEdge    = 0;
    double nThreshVote = voteTreshold; // voting 된 수 임계값


    vector<vector<vector<double>>> arVotes;
    arVotes.assign(nNumGridCy, vector < vector <double> >(nNumGridCx, vector <double>(nNumGridR, 0.0)));

    int nGridR, nGridCx, nGridCy;
    double dAngle,  dMaxVote, dRadius = 0.0;


    tagKEDGEPIXEL oEdge;
    while(edge.Pop(oEdge) != -1) // gradient를 얻기 위해 Canny Edge를 통해 얻은 데이터를 하나씩 빼서 oEdge에 저장
    {
        // votes for radius start
        dRadius = (double)nMinR;
        nGridR = 1;
        dAngle = (oEdge.wAng)/180.0*3.141592;

        do{
            double a = oEdge.u - dRadius*cos(dAngle); // a = x - r*cos(pi)
            double b = oEdge.v - dRadius*sin(dAngle); // b = y - r*sin(pi)

            // votes to avoid edge noises
            for(int j= -5; j<= 5; j++)
            {
                for(int i=-5 ; i<= 5 ; i++)
                {
                    if(b+i < 0 || b+i >= nNumGridCy ||
                            a+j < 0 || a+j >=nNumGridCx)    continue;

                    arVotes[b + i][a + j][nGridR-1] += 0.7;
                    arVotes[b + i][a + j][nGridR] += 0.7;
                    arVotes[b + i][a + j][nGridR+1] += 0.7;
                }
            }
            arVotes[b][a][nGridR] += 0.3;
            dRadius += 1;

        }
        while(++nGridR < nNumGridR - 1);         // votes for radius end
        //next edge ->
    }

    double maxVote = 0.0;
    int maxVoteCx, maxVoteCy = 0.0;
    double maxVoteR = 0.0;
    for(int i = 0; i < nNumGridCy; i++)
        for(int j = 0; j < nNumGridCx; j++)
            for(int r = 0; r < nNumGridR; r++)
            {

                if(maxVote < arVotes[i][j][r])
                {
                    maxVote =    arVotes[i][j][r];
                    maxVoteCx = j;
                    maxVoteCy = i;
                    maxVoteR =nMinR + r;
                }
            }

    qDebug()<<"x"<<maxVoteCx<<"y"<<maxVoteCy;

    // draw circle
    for(int y = 0; y < nNumGridCy; y++)
    {
        for(int x = 0; x < nNumGridCx; x++)
        {
            double radiusSquared = (x-maxVoteCx)*(x-maxVoteCx) + (y-maxVoteCy)*(y-maxVoteCy);
            double diff = (maxVoteR*maxVoteR) - radiusSquared;
            if(fabs(diff) < 50)
            {
                outputImg._ppA[y][x].r =255;
                outputImg._ppA[y][x].g =0;
                outputImg._ppA[y][x].b =0;
            }
        }
    }

    return outputImg;
}

KImageColor cv::GaussianFiltering(KImageColor &input, double sigma)
{
    //    int     i,j,r,c,rr,cc;

    KImageColor output(input.Row(), input.Col());
    //create the gaussian kernal
    int     half = (int)(3.0*sigma+0.3);
    vector<vector<double>> mask;
    vector<double> _mask(half*2+1);
    for(int k = 0; k < half*2+1; k++)
        mask.push_back(_mask);

    double _sigma = 2.0*(sigma*sigma);
    double _const = 1.0/(2*M_PI*sigma*sigma);
    double scale = 0;

    for(int i = -half, r=0; i < half; i++,r++)
    {
        for(int j = -half,c=0; j < half; j++,c++)
        {
            mask[r][c] = _const*exp(-(i*i+j*j)/_sigma);
            scale     +=  mask[r][c];
        }
    }

    // nomalize
    for(int i = -half, r =0; i < half; i++,r++)
        for(int j = -half, c = 0; j < half; j++,c++)
            mask [r][c] /= scale;


    for(int y = half; y < input.Row()-half; y++)
        for(int x = half; x < input.Col() - half; x++)
        {
            double dataR = 0;
            double dataG = 0;
            double dataB = 0;

            for(int i = -half,r =0; i < half; i++, r++)
                for(int j = -half, c =0; j < half; j++, c++)
                {
                    dataR += input._ppA[y+i][x+j].r * mask[r][c];
                    dataG += input._ppA[y+i][x+j].g * mask[r][c];
                    dataB += input._ppA[y+i][x+j].b * mask[r][c];

                }
            output._ppA[y][x].r = (unsigned char)dataR;
            output._ppA[y][x].g = (unsigned char)dataG;
            output._ppA[y][x].b = (unsigned char)dataB;
        }
    return output;
}

KImageDouble cv::GaussianFiltering(KImageDouble &input, double sigma)
{
    //    int     i,j,r,c,rr,cc;

    KImageDouble output(input.Row(), input.Col());
    //create the gaussian kernal
    int     half = (int)(3.0*sigma+0.3);
    vector<vector<double>> mask;
    vector<double> _mask(half*2+1);
    for(int k = 0; k < half*2+1; k++)
        mask.push_back(_mask);

    double _sigma = 2.0*(sigma*sigma);
    double _const = 1.0/(2*M_PI*sigma*sigma);
    double scale = 0;

    for(int i = -half, r=0; i < half; i++,r++)
    {
        for(int j = -half,c=0; j < half; j++,c++)
        {
            mask[r][c] = _const*exp(-(i*i+j*j)/_sigma);
            scale     +=  mask[r][c];
        }
    }

    // nomalize
    for(int i = -half, r =0; i < half; i++,r++)
        for(int j = -half, c = 0; j < half; j++,c++)
            mask [r][c] /= scale;

//    for(int y = 0; y < input.Row(); y++)
//    {
//        for(int x = 0; x < input.Col(); x++)
//        {
//            if(half <= y && y < input.Row()-half && half <= x && x <= input.Col()-half)
//            {
//            double data=0;

//            for(int i = -half,r =0; i < half; i++, r++)
//            {
//                for(int j = -half, c =0; j < half; j++, c++)
//                {
//                    data += input._ppA[y+i][x+j] * mask[r][c];
//                }
//            }
//            output._ppA[y][x] = data;
//            }
//            else
//            {
//                output._ppA[y][x] = input._ppA[y][x];
//            }
//        }
//    }


    for(int y = half; y < input.Row()-half; y++)
    {
        for(int x = half; x < input.Col() - half; x++)
        {
            double data=0;

            for(int i = -half,r =0; i < half; i++, r++)
            {
                for(int j = -half, c =0; j < half; j++, c++)
                {
                    data += input._ppA[y+i][x+j] * mask[r][c];
                }
            }
            output._ppA[y][x] = data;
        }
    }


    return output;
}

void cv::splitRGB(KImageColor rgbImage, KImageGray &r, KImageGray &g, KImageGray &b)
{
    r.Create(rgbImage.Row(), rgbImage.Col());
    g.Create(rgbImage.Row(), rgbImage.Col());
    b.Create(rgbImage.Row(), rgbImage.Col());


    for(int y = 0; y < rgbImage.Row(); y++)
        for(int x = 0; x < rgbImage.Col(); x++)
        {
            r._ppA[y][x] = rgbImage._ppA[y][x].r;
            g._ppA[y][x] = rgbImage._ppA[y][x].g;
            b._ppA[y][x] = rgbImage._ppA[y][x].b;
        }
}

cv::SiftDB cv::generateSiftDb(const KImageGray &image, int octaveMinimumSize, int scaleInOctave, vector<vector<KImageDouble>> &scales, vector<vector<KImageDouble>> &dogs, vector<vector<KImageColor>> &keypointImage)
{
    double sigma = 0.5;
    qDebug()<<"image size :"<<image.Row()<<image.Col();
    int minDim;
    if(image.Row() > image.Col()) minDim = image.Col();
    else minDim = image.Row();
    int s = scaleInOctave - 3;

    int imageOctave;

    //compute imageOctave(N')
    for(int i=0;;i++)
    {
        if(pow(2,i) > minDim)
        {
            imageOctave = i-1;
            break;
        }
    }

    int octaveN = imageOctave - (octaveMinimumSize-1);
    std::cout
            <<"image dimension : "
            <<minDim<<"(>=2^"
            <<imageOctave<<") "
            <<"octave minimum size : "
            <<pow(2,octaveMinimumSize)
            <<"(==2^"
            <<octaveMinimumSize
            <<")"
            <<" octave N : "
            <<octaveN
            <<std::endl;

    std::cout<<"downsampling dimensions : ";

    //resize scale, dog vectors
    scales.resize(octaveN);
    for(int i=0; i<octaveN; i++) scales[i].resize(scaleInOctave);
    dogs.resize(octaveN);
    for(int i=0; i<octaveN; i++) dogs[i].resize(scaleInOctave-1);
    vector<vector<ScaleInfo>> scaleInfos;
    scaleInfos.resize(octaveN);
    for(int i=0; i<octaveN; i++) scaleInfos[i].resize(scaleInOctave);

    //generate ovtaves&scales
    int downSampledDimension = minDim;
    KImageDouble downsampledImage(image);

    for(int i=0; i<octaveN ; i++)
    {
        std::cout<<downSampledDimension<<" ";

        //push scale images

        scales[i] = SCalesGaussian(downsampledImage, scaleInOctave);
//        for(int j=0; j<scaleInOctave; j++)
//        {
//            KImageDouble gaussianImage(downsampledImage);


//            KVector vKernel  = KGaussianMulti::Kernel_1D(pow(2,(double)j/s)*sigma);
//            gaussianImage.Convolution(vKernel,_COL,false).Convolution(vKernel,_ROW,false,downsampledImage);


//            scales[i][j] = gaussianImage;
//            scaleInfos[i][j].sigma = pow(2,(double)j/s)*sigma;
//        }

        //push dog images
        for(int j=0; j<scaleInOctave-1; j++)
        {
            KImageDouble dog = KImageDouble(scales[i][j+1]);
            dog -= scales[i][j];
            dogs[i][j] = dog;
        }

        downsampledImage = cv::downSample(downsampledImage, 0.5);
        downSampledDimension /=2;
    }
    std::cout<<std::endl;

    //find keypoints
    vector<vector<vector<cv::Keypoint>>> keypoints;
    getKeypoint(scales, dogs, keypoints, scaleInfos);

    //resize, init keypoint vector
    keypointImage.resize(dogs.size());
    for(int i=0; i<dogs.size(); i++)
    {
        keypointImage[i].resize(dogs[i].size());

        for(int j=0; j<dogs[i].size(); j++)
        {
            keypointImage[i][j].Create(dogs[i][j].Row(), dogs[i][j].Col());
        }
    }

    //draw on keypoint images
    for(int i=0; i<keypoints.size(); i++)
    {
        for(int j=0; j<keypoints[i].size(); j++)
        {
            for(int k=0; k<keypoints[i][j].size(); k++)
            {
                keypointImage[i][j][keypoints[i][j][k].x][keypoints[i][j][k].y].r=255;
                keypointImage[i][j][keypoints[i][j][k].x][keypoints[i][j][k].y].g=0;
                keypointImage[i][j][keypoints[i][j][k].x][keypoints[i][j][k].y].b=0;
            }
        }
    }

    vector<cv::Descriptor> descriptors;
    getDescriptor(scales, scaleInfos,keypoints, descriptors);


    SiftDB db;

    for(int i=0; i<descriptors.size(); i++)
    {
        db.push_back(descriptors[i]);
        descriptors[i].print();
    }

    return db;
}

KImageDouble cv::downSample(const KImageDouble image, double samplingRate)
{
    KImageDouble result(image.Row()*samplingRate, image.Col()*samplingRate);

    int step = (int)(1.0 / samplingRate);

    for(int i=0, ii=0; i<image.Row(), ii<result.Row(); i+=step, ii++)
    {
        for(int j=0, jj=0; j<image.Col(), jj<result.Col(); j+= step, jj++)
        {
            result[ii][jj] = image[i][j];
        }
    }

    return result;
}

KImageGray cv::doubleImageToGray(const KImageDouble &image, double low, double high)
{
    KImageGray result(image.Row(), image.Col());

    for(int i=0; i<image.Row(); i++)
    {
        for(int j=0; j<image.Col(); j++)
        {
            result[i][j] = (unsigned char)util::map(image[i][j],low,high,0,255);
        }
    }

    return result;
}

void cv::getKeypoint(vector<vector<KImageDouble> > &scales, vector<vector<KImageDouble> > &dogs, vector<vector<vector<cv::Keypoint>>> &keypoints, const vector<vector<ScaleInfo>> &scaleInfos)
{
    keypoints.resize(dogs.size());
    for(int i=0; i<dogs.size(); i++) keypoints[i].resize(dogs[i].size());

    for(int iOctave=0; iOctave<dogs.size(); iOctave++)
    {
        vector<KImageDouble> &octaveDogs = dogs[iOctave];

        for(int iDog=1; iDog<dogs[iOctave].size()-1; iDog++)
        {
            //qDebug()<<"comparing"<<iDog-1<<iDog<<iDog+1;
            keypoints[iOctave][iDog].clear();

            for(int i=1; i<dogs[iOctave][iDog].Row()-1; i++)
            {
                for(int j=1; j<dogs[iOctave][iDog].Col()-1; j++)
                {
                    double v = octaveDogs[iDog][i][j];

                    continue;
                    //if(abs(v) < 0.03) continue;

                    if(v > 0)
                    {
                       if(     v < octaveDogs[iDog-1][i-1][j-1] || v < octaveDogs[iDog-1][i-1][j+0] || v < octaveDogs[iDog-1][i-1][j+1] ||
                               v < octaveDogs[iDog-1][i+0][j-1] || v < octaveDogs[iDog-1][i+0][j+0] || v < octaveDogs[iDog-1][i+0][j+1] ||
                               v < octaveDogs[iDog-1][i+1][j-1] || v < octaveDogs[iDog-1][i+1][j+0] || v < octaveDogs[iDog-1][i+1][j+1] ||

                               v < octaveDogs[iDog+0][i-1][j-1] || v < octaveDogs[iDog+0][i-1][j+0] || v < octaveDogs[iDog+0][i-1][j+1] ||
                               v < octaveDogs[iDog+0][i+0][j-1]                                     || v < octaveDogs[iDog+0][i+0][j+1] ||
                               v < octaveDogs[iDog+0][i+1][j-1] || v < octaveDogs[iDog+0][i+1][j+0] || v < octaveDogs[iDog+0][i+1][j+1] ||

                               v < octaveDogs[iDog+1][i-1][j-1] || v < octaveDogs[iDog+1][i-1][j+0] || v < octaveDogs[iDog+1][i-1][j+1] ||
                               v < octaveDogs[iDog+1][i+0][j-1] || v < octaveDogs[iDog+1][i+0][j+0] || v < octaveDogs[iDog+1][i+0][j+1] ||
                               v < octaveDogs[iDog+1][i+1][j-1] || v < octaveDogs[iDog+1][i+1][j+0] || v < octaveDogs[iDog+1][i+1][j+1]     )continue;
                    }
                    else
                    {
                       if(     v > octaveDogs[iDog-1][i-1][j-1] || v > octaveDogs[iDog-1][i-1][j+0] || v > octaveDogs[iDog-1][i-1][j+1] ||
                               v > octaveDogs[iDog-1][i+0][j-1] || v > octaveDogs[iDog-1][i+0][j+0] || v > octaveDogs[iDog-1][i+0][j+1] ||
                               v > octaveDogs[iDog-1][i+1][j-1] || v > octaveDogs[iDog-1][i+1][j+0] || v > octaveDogs[iDog-1][i+1][j+1] ||

                               v > octaveDogs[iDog+0][i-1][j-1] || v > octaveDogs[iDog+0][i-1][j+0] || v > octaveDogs[iDog+0][i-1][j+1] ||
                               v > octaveDogs[iDog+0][i+0][j-1]                                     || v > octaveDogs[iDog+0][i+0][j+1] ||
                               v > octaveDogs[iDog+0][i+1][j-1] || v > octaveDogs[iDog+0][i+1][j+0] || v > octaveDogs[iDog+0][i+1][j+1] ||

                               v > octaveDogs[iDog+1][i-1][j-1] || v > octaveDogs[iDog+1][i-1][j+0] || v > octaveDogs[iDog+1][i-1][j+1] ||
                               v > octaveDogs[iDog+1][i+0][j-1] || v > octaveDogs[iDog+1][i+0][j+0] || v > octaveDogs[iDog+1][i+0][j+1] ||
                               v > octaveDogs[iDog+1][i+1][j-1] || v > octaveDogs[iDog+1][i+1][j+0] || v > octaveDogs[iDog+1][i+1][j+1]     )continue;
                    }

                    //gradient histogram
                    int histogram[36] = {0, };
                    int margin = (int)(3.0*scaleInfos[iOctave][iDog+1].sigma+0.3) + 1; //+1 for gradient differentiation

                    //reject keypoints on margin
                    if(i < margin || scales[iOctave][iDog+1].Row()-margin < i) continue;
                    if(j < margin || scales[iOctave][iDog+1].Col()-margin < j) continue;

                    //generate gradient histogram
                    KImageDouble &scale = scales[iOctave][iDog];
                    for(int x=margin; x<scale.Row()-margin; x++)
                    {
                        for(int y=margin; y<scale.Col()-margin; y++)
                        {
                            double gradX = scale[x+1][y] - scale[x-1][y];
                            double gradY = scale[x][y+1] - scale[x][y-1];
                            double angle = atan2(gradY, gradX)/M_PI*180.0+180.0;

                            qDebug()<<x<<y<<"gradX"<<gradX<<"gradY"<<gradY<<"angle"<<angle;

                            histogram[(int)(angle)/10]++;
                        }
                    }

                    //compute maxima
                    int maxN = histogram[0];
                    int maxAngle = 0;
                    for(int i=1; i<36; i++)
                    {
                        if(histogram[i] > maxN)
                        {
                            maxAngle = i;
                            maxN = histogram[i];
                        }
                    }

                    //0~18 to 0~180
                    maxAngle*=10;

                    //create Keypoint
                    Keypoint k;
                    k.x = i;
                    k.y = j;
                    k.angle = maxAngle;
                    keypoints[iOctave][iDog+1].push_back(k);
                    //if(iDog == 1)qDebug()<<"inserting 1"<<i<<j;
                    //if(iDog == 2)qDebug()<<"inserting 2"<<i<<j;
                }
            }



        }
    }
}

void cv::getDescriptor(vector<vector<KImageDouble>> &scales, const vector<vector<cv::ScaleInfo> > &scaleInfos, vector<vector<vector<cv::Keypoint>>> &keypoints, vector<cv::Descriptor> &descriptors)
{
    for(int iOctave=0; iOctave<keypoints.size(); iOctave++)
    {
        for(int iScale=0; iScale<keypoints[iOctave].size(); iScale++)
        {
            for(int iKeypoint=0; iKeypoint<keypoints[iOctave][iScale].size(); iKeypoint++)
            {
                //keypoints[iOctave][iScale][iKeypoint];
                Keypoint &keypoint = keypoints[iOctave][iScale][iKeypoint];
                KImageDouble &scale = scales[iOctave][iScale];

                int patchSize = scaleInfos[iOctave][iScale].sigma * 20;
                int margin = patchSize/2;
                int step = patchSize/16;

                double tf[18][18] = {{0}, };

                bool ignoreKeypoint = false;
                int ignoredKeypointN = 0;

                //get transform
                for(int i=keypoint.x-margin-step, ii=0; ii<16; i+= step, ii++)
                {
                    for(int j=keypoint.y-margin-step, jj=0 ; jj<16; j+= step, jj++)
                    {
                        int offsetAngle = keypoints[iOctave][iScale][iKeypoint].angle;
                        int offsetX = i*cos(offsetAngle/180.0*M_PI) - j*sin(offsetAngle/180.0*M_PI);
                        int offsetY = i*sin(offsetAngle/180.0*M_PI) + j*cos(offsetAngle/180.0*M_PI);

                        //qDebug()<<"TF"<<offsetX<<offsetY;

                        if(scale.Row() <= offsetX || offsetX < 0 || scale.Col() <= offsetY || offsetY < 0)
                        {
                            //qDebug()<<"out of bound";
                            ignoreKeypoint = true;
                            ignoredKeypointN++;
                        }
                        else
                        {
                            tf[ii][jj] = scale[offsetX][offsetY];
                        }
                    }
                }


                if(!ignoreKeypoint)
                {

                    //get gradient patch
                    int patch[16][16] = {{0}, };

                    for(int i=0; i<16; i++)
                    {
                        for(int j=0; j<16; j++)
                        {
                            double gradX = tf[i+2][j+1] - scale[i][j+1];
                            double gradY = tf[i+1][j+2] - scale[i+1][j];

                            double angle = atan2(gradY, gradX)/M_PI*180.0+180;
                            patch[i][j] = angle/45;
                            //qDebug()<<i<<j<<"gradX"<<gradX<<"gradY"<<gradY<<"angle"<<angle;
                        }
                    }

                    //generate descriptor
                    Descriptor d;

                    for(int i=0; i<4; i++)
                    {
                        for(int j=0; j<4; j++)
                        {
                            for(int iCom=0; iCom<4; iCom++)
                            {
                                for(int jCom=0; jCom<4; jCom++)
                                {
                                    d.data[4*i+j][patch[i+iCom][j+jCom]]++;
                                }
                            }
                        }
                    }

                    d.x = keypoint.x;
                    d.y = keypoint.y;

                    descriptors.push_back(d);
                }
            }
        }
    }
}

void putPixel(KImageColor& input,
              int x,
              int y,
              int R=255,
              int G=0,
              int B=0)
{
    if(x < 0 || y < 0) return ;
    if(x >= input.Col() || y >= input.Row()) return ;
    input._ppA[y][x].r = R;
    input._ppA[y][x].g = G;
    input._ppA[y][x].b = B;
}

void drawLine(KImageColor& input, int x0, int y0, int x1, int y1)
{
    int x,y;
    int dx = x1 - x0;
    int dy = y1 - y0;
    int ix = abs(dx);
    int iy = abs(dy);
    int inc = max(ix, iy);
    int plotx = x1;
    int ploty = y1;

    x = y = 0;
    for(int  I = 0; I <= inc ; I++)
    {
        x += ix;
        y += iy;
        if( x > inc)
        {
            x -= inc;
            plotx += sign(dx);
        }
        if( y > inc )
        {
            y -= inc;
            ploty += sign(dy);
        }
        putPixel(input, plotx, ploty);

    }
}

vector<KImageDouble> cv::SCalesGaussian(KImageDouble &dimg, int imageInScale)
{
    vector<KImageDouble> lpScales;
    KImageDouble tmpimg(dimg);

    double dSigma1,dSigma2,dSigma;
    double _SIGMA_0 = 0.5;
    double dK = pow(2, 1.0/imageInScale);
    KImageDouble idTmp;
    KImageDouble idpImgS(dimg);
    KVector vKernel;

    dSigma = pow(dK, 0) * _SIGMA_0;
    vKernel  = KGaussianMulti::Kernel_1D(dSigma);
    idpImgS.Convolution(vKernel,_COL,false).Convolution(vKernel,_ROW,false,idpImgS);
    lpScales.push_back(idpImgS);

    for(int i = 1; i <imageInScale + 3; i++){
        //create Gaussian Kernal
        dSigma1 = pow(dK, i - 1) * _SIGMA_0;
        dSigma2 = pow(dK, i) * _SIGMA_0;
        dSigma  = sqrt(_SQR(dSigma2) - _SQR(dSigma1));
        vKernel  = KGaussianMulti::Kernel_1D(dSigma);
        idpImgS = lpScales[i-1];
        idpImgS.Convolution(vKernel,_COL,false).Convolution(vKernel,_ROW,false,idpImgS);
        lpScales.push_back(idpImgS);
    }


    return lpScales;
}

void OPTICALFLOW::_computeGradX(KImageGray curImage, KImageDouble &I_x)
{
    const int ROW = curImage.Row();
    const int COL = curImage.Col();

    if(I_x.Address() == 0)
    {
        I_x.Create(ROW, COL);
    }

    const int MASK_X[3] = {-1, 0, 1};

    for(int i = 1; i < ROW - 1; i++)
        for(int j = 1; j < COL - 1; j++)
        {
            int sum = 0;
            for(int jj = -1; jj <= 1; jj++)
            {
                sum += curImage._ppA[i][j + jj] * MASK_X[jj + 1];
            }

            I_x._ppA[i][j] = (sum);
        }
}

void OPTICALFLOW::_computeGradY(KImageGray curImage, KImageDouble &I_y)
{
    const int ROW = curImage.Row();
    const int COL = curImage.Col();

    if(I_y.Address() == 0)
    {
        I_y.Create(ROW, COL);
    }

    const int MASK_Y[3] = {-1, 0, 1};

    for(int i = 1; i < ROW - 1; i++)
        for(int j = 1; j < COL - 1; j++)
        {
            int sum = 0;
            for(int ii = -1; ii <= 1; ii++)
            {
                sum += curImage._ppA[i + ii][j]*MASK_Y[ii + 1];
            }

            I_y._ppA[i][j] = (sum);
        }
}

void OPTICALFLOW::_computeGradT(KImageGray preImage, KImageGray curImage, KImageDouble &I_t)
{
    const int ROW = curImage.Row();
    const int COL = curImage.Col();

    if(I_t.Address() == 0)
    {
        I_t.Create(ROW, COL);
    }

    for(int y = 0; y < ROW; y++)
        for(int x = 0; x < COL; x++)
        {
            I_t._ppA[y][x] = curImage._ppA[y][x] - preImage._ppA[y][x];
        }
}

void OPTICALFLOW::_makeWeightedMask(KMatrix &weightedMask, const int maskSize)
{

    double normSum = 0.0;

    double sigma = 0.5;


    for(int j = -maskSize/2; j< maskSize/2; j++)
        for(int i = -maskSize/2; i< maskSize/2; i++)
        {
            double gaussian_denominator = exp(-(pow(i, 2.0) + pow(j , 2.0)) / 2.0 * pow(sigma, 2.0) );
            double gaussian_numerator   = 2.0 * 3.14 * pow(sigma,2.0);

            weightedMask._ppA[j+maskSize/2][i+maskSize/2] = gaussian_denominator/ gaussian_numerator;
            normSum += weightedMask._ppA[j+maskSize/2][i+maskSize/2];
        }

    for(int j = 0; j< maskSize; j++)
        for(int i = 0; i< maskSize; i++)
        {
            weightedMask._ppA[j][i] /= normSum;
        }
}

void OPTICALFLOW::runOpticalFlow(KImageGray preImage, KImageGray curImage, KImageColor &output)
{
    const int Row = curImage.Row();
    const int Col = preImage.Col();
    const int maskWidth = 5;
    const int maskHeight = 5;
    const int maskSize = 25;

    KImageDouble I_x(Row,Col);
    KImageDouble I_y(Row,Col);
    KImageDouble I_t(Row,Col);

    _computeGradX(curImage, I_x);
    _computeGradY(curImage, I_y);
    _computeGradT(preImage, curImage, I_t);

    KMatrix weightedMask(maskSize, maskSize);
    _makeWeightedMask(weightedMask, maskSize);

    KMatrix matA(maskSize, 2);
    KMatrix matB(maskSize, 1);
    KMatrix matD(2, 1);
    cout << "compute_complete" << endl;
    for(int row = 2 ; row < Row - 2 ; row += 2 *2)
        for(int col = 2 ; col < Col - 2 ; col += 2 *2)
        {
            int idx = 0;
            for(int i = -2 ; i <= 2 ; i ++)
                for(int j = -2 ; j <= 2 ; j ++)
                {
                    matA._ppA[idx][0] = I_x._ppA[row + i][col + j];
                    matA._ppA[idx][1] = I_y._ppA[row + i][col + j];
                    matB._ppA[idx][0] = -I_t._ppA[row + i][col + j];

                    idx++;
                }

            KMatrix A_t = matA.Tr();

            KMatrix ATr_x_W_x_A = A_t * matA;

            KMatrix mU,mV;
            KVector vW;
            ATr_x_W_x_A.SVD(mU, vW, mV);

            if(vW[1] == 0.0)
            {
                continue;
            }
            if(fabs(vW[0]) / fabs(vW[1]) > 10000)continue;

            bool bRet = false;
            KMatrix ATr_x_W_x_A_inv = ATr_x_W_x_A.Iv(bRet);

            if(bRet == false) continue;

            if(ATr_x_W_x_A_inv.Col() != 2 || ATr_x_W_x_A_inv.Row() != 2) continue;

            if(ATr_x_W_x_A_inv.Size() == 0) continue;

            matD = (ATr_x_W_x_A_inv) * A_t * matB;

            drawLine(output,
                     col,
                     row,
                     (int)(col + matD._ppA[0][0]),
                    (int)(row + matD._ppA[1][0]));
        }

}

