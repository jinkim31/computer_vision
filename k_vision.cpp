#include "k_vision.h"

#define g_MIN(a, b) (((a) < (b)) ? (a) : (b))
#define g_MAX(a,b) (((a) > (b)) ? (a) : (b))

#define DEG2RAD 0.0174532925199
#define RAD2DEG 57.2957795130823

K_VISION::K_VISION()
{

}

KImageGray K_VISION::LCT(const int& a, const int& b, const int& a_, const int& b_, KImageGray img) // Luminance Contrast Transform - Gray image
{
    KImageGray outImage(img);
    double X_in, slope = (double)(b_ - a_) / (double)(b - a);

    for(int y =0; y < img.Row(); y++)
    {
        for(int x = 0; x < img.Col(); x++)
        {
            X_in = (img._ppA[y][x] < a ? a : (img._ppA[y][x] > b ? b : img._ppA[y][x]));
            outImage._ppA[y][x] =  (unsigned char)(slope *(X_in - a)  + a_);
        }
    }

    return outImage;
}


KImageColor K_VISION::LCT(const double& a, const double& b, const double& a_, const double& b_, KImageColor img) // Luminance Contrast Transform - Color image
{
    KImageColor outImage(img);
    double slope = (b_ - a_) / (b - a);

    for(int y =0; y < img.Row(); y++)
    {
        for(int x = 0; x < img.Col(); x++)
        {
            double X_in_r = (img._ppA[y][x].r < a ? a : (img._ppA[y][x].r > b ? b : img._ppA[y][x].r));
            outImage._ppA[y][x].r = (slope *(X_in_r - a)  + a_);

            double X_in_g = (img._ppA[y][x].g < a ? a : (img._ppA[y][x].g > b ? b : img._ppA[y][x].g));
            outImage._ppA[y][x].g = (slope *(X_in_g - a)  + a_);

            double X_in_b = (img._ppA[y][x].b < a ? a : (img._ppA[y][x].b > b ? b : img._ppA[y][x].b));
            outImage._ppA[y][x].b = (slope *(X_in_b - a)  + a_);
        }
    }

    return outImage;
}


KArray<KHSV> K_VISION::RGBtoHSV(KImageColor &inputImage)
{
    // output Image
    KArray<KHSV> outputImage;
    outputImage.Create(inputImage.Row(), inputImage.Col());

    for(int y = 0; y < inputImage.Row(); y++)
    {
        for(int x = 0; x < inputImage.Col(); x++)
        {
            double max = g_MAX(inputImage._ppA[y][x].r,(g_MAX(inputImage._ppA[y][x].g, inputImage._ppA[y][x].b)));
            double min = g_MIN(inputImage._ppA[y][x].r,(g_MIN(inputImage._ppA[y][x].g, inputImage._ppA[y][x].b)));
            double diff = max - min;

            if(diff == 0.0)
            {
                outputImage._ppA[y][x].h = -1;
                outputImage._ppA[y][x].s = 0;
                outputImage._ppA[y][x].v = max;
                continue;
            }

            // hue range 0 ~ 360
            if(max == (double)inputImage._ppA[y][x].r)
                outputImage._ppA[y][x].h = 60.0 * (double)(inputImage._ppA[y][x].g - inputImage._ppA[y][x].b)/(diff);
            else if(max == (double)inputImage._ppA[y][x].g)
                outputImage._ppA[y][x].h = (60.0 * (double)(inputImage._ppA[y][x].b - inputImage._ppA[y][x].r)/(diff)) + 120;
            else if(max == (double)inputImage._ppA[y][x].b)
                outputImage._ppA[y][x].h = (60.0 * (double)(inputImage._ppA[y][x].r - inputImage._ppA[y][x].g)/(diff)) + 240;
            outputImage._ppA[y][x].h += (outputImage._ppA[y][x].h<0.0) ? 360.0 : 0.0;

            // saturation range 0 ~ 1
            outputImage._ppA[y][x].s = diff/max;

            // value 0 ~ 255
            outputImage._ppA[y][x].v = max;
        }
    }

    return outputImage;
}

KImageColor K_VISION::HSVtoRGB(KArray<KHSV> &inputImage)
{
    int row = inputImage.Row();
    int col = inputImage.Col();
    KImageColor outputImage(row,col);

    for(int y = 0; y < row; y++)
    {
        for(int x = 0; x < col; x++)
        {
            double h = inputImage._ppA[y][x].h;
            double s = inputImage._ppA[y][x].s;
            double v = inputImage._ppA[y][x].v;

            if(s < 0)
            {
                outputImage._ppA[y][x].r = v;
                outputImage._ppA[y][x].g = v;
                outputImage._ppA[y][x].b = v;
            }
            if(h == 360)
                h = 0;

            double min_rgb = v * (1.0 - s);
            double hh = h/60.0;
            int index = hh;

            switch (index) {
            case 0:
                outputImage._ppA[y][x].r = v;
                outputImage._ppA[y][x].g = v*(1.0 - s*(1.0 - hh));
                outputImage._ppA[y][x].b = min_rgb;
                break;
            case 1:
                outputImage._ppA[y][x].r = v*(1.0 - s*(hh - 1.0));
                outputImage._ppA[y][x].g = v;
                outputImage._ppA[y][x].b = min_rgb;
                break;
            case 2:
                outputImage._ppA[y][x].r = min_rgb;
                outputImage._ppA[y][x].g = v;
                outputImage._ppA[y][x].b = v*(1.0 - s*(3.0 - hh));
                break;
            case 3:
                outputImage._ppA[y][x].r = min_rgb;
                outputImage._ppA[y][x].g = v*(1.0 - s*(hh - 3.0));
                outputImage._ppA[y][x].b = v;
                break;
            case 4:
                outputImage._ppA[y][x].r = v*(1.0 - s*(5.0 - hh));
                outputImage._ppA[y][x].g = min_rgb;
                outputImage._ppA[y][x].b = v;
                break;
            case 5:
                outputImage._ppA[y][x].r = v;
                outputImage._ppA[y][x].g = min_rgb;
                outputImage._ppA[y][x].b = v*(1.0 - s*(1.0 + hh));
                break;
            default:
                break;
            }
        }
    }

    return outputImage;
}

void K_VISION::splitHSV(KArray<KHSV> hsvImage, KImageGray &h, KImageGray &s, KImageGray &v)
{
    int row = hsvImage.Row();
    int col = hsvImage.Col();
    h.Create(row, col);
    s.Create(row, col);
    v.Create(row, col);

    for(int y = 0; y < row; y++)
    {
        for(int x = 0; x < col; x++)
        {
            h._ppA[y][x] = hsvImage._ppA[y][x].h * 255.0 / 360.0;    // hue range 0 ~ 255
            s._ppA[y][x] = hsvImage._ppA[y][x].s * 255.0;              // saturation range 0 ~ 255
            v._ppA[y][x] = hsvImage._ppA[y][x].v;                        // value range 0 ~ 255
        }
    }
}

void K_VISION::splitRGB(KImageColor rgbImage, KImageGray &r, KImageGray &g, KImageGray &b)
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

void K_VISION::sepiaTone(KArray<KHSV> &image, double hue, double saturation)
{
    for(int i = 0 ; i < image.Col() ; i++)
    {
        for(int j = 0 ; j < image.Row() ; j++)
        {
            image._ppA[j][i].h = hue;
            image._ppA[j][i].s = saturation;
        }
    }
}


KImageGray K_VISION::Otsu(KImageGray &inputImage)
{
    KHisto hTmp;
    hTmp.Histogram(inputImage);

    double P[255] = {0,};

    double size = inputImage.Size();
    double myu_g = 0;
    for(int i = 0; i < 255; i++)
    {
        P[i] = hTmp[i]/size;
        myu_g = myu_g + i*P[i];
    }

    double q_1[254] = {0,};
    double q_2[254] = {0,};
    double myu_1[254] = {0,};
    double myu_2[254] = {0,};

    q_1[0] = P[0];
    q_2[0] = 1 - q_1[0];
    myu_1[0] = 0;

    double sigmaB = 0;
    double max = 0;
    double index = 0;

    for(int t = 0; t < 254; t++)
    {
        q_1[t+1] = q_1[t] + P[t+1];
        q_2[t+1] = 1-q_1[t+1];

        if(q_1[t+1]  == 0.0)
        {
            myu_1[t+1] = 0.0;
            continue;
        }

        myu_1[t+1] = (q_1[t]*myu_1[t] + (double)(t+1)*P[t+1])/(q_1[t+1]);
        myu_2[t+1] = (myu_g - q_1[t+1]*myu_1[t+1])/(1-q_1[t+1]);

        max = q_1[t+1]*(myu_1[t+1] - myu_g)*(myu_1[t+1] - myu_g) + q_2[t+1]*(myu_2[t+1] - myu_g)*(myu_2[t+1] - myu_g); // sigma_b^2

        if(sigmaB < max)
        {
            index = t+1;
            sigmaB = max;
        }
    }

    KImageGray outputImage(inputImage.Row(), inputImage.Col());

    for(int y = 0; y < outputImage.Row(); y++)
        for(int x = 0; x < outputImage.Col(); x++)
        {
            if(inputImage[y][x] < index)
            {
                outputImage[y][x] = 0;
            }
            else
            {
                outputImage[y][x] = 255;
            }
        }

    return outputImage;
}

void K_VISION::Labeling(KImageGray &inputImage, KImageGray  &outputImage, map<int, int> &equivalenceTable)
{
    //    map<int, int> equivalenceTable;
    //    KImageGray  outputImage(inputImage.Row(), inputImage.Col());
    outputImage.Create(inputImage.Row(), inputImage.Col());
    equivalenceTable.clear();

    int cnt = 0;
    int index = 1;

    for(int y = 0; y < inputImage.Row(); y++)
    {
        for(int x = 0; x < inputImage.Col(); x++)
        {
            //            outputImage[y][x] = 0;
            int up = y-1;
            int left = x-1;
            if(x == 185 && y == 48) continue;
            if(inputImage[y][x] != 0)
            {
                if(left < 0 && up < 0) // new label
                {
                    //                    index++;
                    //                    equivalenceTable[index]=index;  // map[key]=value
                    //                    outputImage[y][x] = index;
                    continue;
                }
                else if(left<0)
                {
                    //                    if(outputImage[up][x] != 0) // label[y][x] = label[y-1][x]
                    //                        outputImage[y][x] = outputImage[up][x];
                    //                    else // new label
                    //                    {
                    //                        index++;
                    //                        equivalenceTable[index]=index;  // map[key]=value
                    //                        outputImage[y][x] = index;
                    //                    }
                    continue;
                }
                else if(up<0)
                {
                    //                    if(outputImage[y][left] != 0)
                    //                        outputImage[y][x] = outputImage[y][left];
                    //                    else                                                        //new label
                    //                    {
                    //                        index++;
                    //                        equivalenceTable[index]=index;  // map[key]=value
                    //                        outputImage[y][x] = index;
                    //                    }
                    continue;
                }
                else
                {
                    if(outputImage[y][left] == 0 && outputImage[up][x] == 0 && outputImage[up][left] == 0) // new label
                    {
                        index++;
                        equivalenceTable[index]=index;  // map[key]=value
                        outputImage[y][x] = index;
                    }

                    else if(outputImage[y][left] == 0 && outputImage[up][x] == 0 && outputImage[up][left] != 0)
                        outputImage[y][x] = outputImage[up][left];

                    else if(outputImage[y][left] == 0 && outputImage[up][x] != 0 && outputImage[up][left] == 0)
                        outputImage[y][x] = outputImage[up][x];

                    else if(outputImage[y][left] != 0 && outputImage[up][x] == 0 && outputImage[up][left] == 0)
                        outputImage[y][x] = outputImage[y][left];

                    else if(outputImage[y][left] != 0 && outputImage[up][x] != 0) // Create Equivalence Tabel
                    {
                        // //                        outputImage[y][x] = (outputImage[y][left] > outputImage[up][x]) ? outputImage[up][x] : outputImage[y][left];
                        // //                        equivalenceTable[outputImage[y][left]] = outputImage[up][x];

                        // //                        int value = (outputImage[y][left] >= outputImage[up][x]) ? outputImage[up][x] : outputImage[y][left];
                        // //                        int key   = (outputImage[y][left] >= outputImage[up][x]) ? outputImage[y][left]: outputImage[up][x];
                        // //                        outputImage[y][x] = key;
                        // //                        equivalenceTable[key] = value;

                        int key_left = outputImage[y][left];
                        int value_left = equivalenceTable[key_left];
                        int key_up = outputImage[up][x];
                        int value_up = equivalenceTable[key_up];
                        if((value_up == 0 || key_up == 0 || value_left == 0 || key_left == 0) )
                        {
                            //                            cout<<"left: "<<left<<endl;
                            //                            cout<<"up: "<<up<<endl;
                            //                            cout<<"key_up: "<<key_up<<endl;
                            //                            cout<<"key_left: "<<key_left<<endl;
                            //                            cout<<"value_up: "<<value_up<<endl;
                            //                            cout<<"value_left: "<<value_left<<endl;
                            //                            cout<<"outputImage[y][x]: "<<outputImage[y][x]<<endl;
                            continue;

                        }
                        if(value_left < value_up)
                        {
                            equivalenceTable[key_up] = value_left;
                            outputImage[y][x] = value_left;
                        }
                        else
                        {
                            equivalenceTable[key_left] = value_up;
                            outputImage[y][x] = value_up;
                        }


                        cnt++;
                    }
                }

            }
            else{

                //                if(left > 0 && up > 0 && outputImage[y][left] != 0 && outputImage[up][x] != 0) // Create Equivalence Tabel
                //                {

                //                    int value_left = equivalenceTable[outputImage[y][left]];
                //                    int key_left = outputImage[y][left];
                //                    int value_up = equivalenceTable[outputImage[up][x]];
                //                    int key_up = outputImage[up][x];

                //                    if(value_left < value_up) equivalenceTable[key_up] = value_left;
                //                    else equivalenceTable[key_left] = value_up;
                //                }
            }

            if(index == 0)
            {
                //                cout<<"@@@@@@@@@@@@@@@@@@@@@@@@@@@@"<<endl;
                //                cout<<"x: "<<x<<"    y: "<<y<<endl;
                //                cout<<"left: "<<left<<endl;
                //                cout<<"up: "<<up<<endl;
            }
        }
    }
}

KImageGray K_VISION::HE(KImageGray &inputImage)
{
    double row = inputImage.Row();
    double col = inputImage.Col();
    KImageGray outputImage(row,col);

    // image histogram
    KHisto histogram(inputImage);

    // Cumulative Density Function
    for(int i = 1; i < 254; i++)
        histogram[i] += histogram[i-1];

    // Histogram Equalization // 합이 1이 되도록
    double size = inputImage.Size();
    for(int i = 0; i < 255; i++)
        histogram[i] = (double)histogram[i]/(double)size;

    for(int y = 0; y < row; y++)
        for(int x = 0; x < col; x++)
        {
            outputImage[y][x] = (unsigned char)(histogram[inputImage[y][x]] * 255.0) ;
        }

    return outputImage;

}

KImageColor K_VISION::HE(KImageColor &inputImage)
{
    KImageColor outputImage(inputImage.Row(), inputImage.Col());
    vector<KImageGray> rgbsplit(3);
    splitRGB(inputImage, rgbsplit[0], rgbsplit[1], rgbsplit[2]);

    rgbsplit[0] = HE(rgbsplit[0]);
    rgbsplit[1] = HE(rgbsplit[1]);
    rgbsplit[2] = HE(rgbsplit[2]);

    for(int y = 0; y < inputImage.Row(); y++)
        for(int x = 0; x < inputImage.Col(); x++)
        {
            outputImage._ppA[y][x].r = rgbsplit[0]._ppA[y][x];
            outputImage._ppA[y][x].g = rgbsplit[1]._ppA[y][x];
            outputImage._ppA[y][x].b = rgbsplit[2]._ppA[y][x];
        }

    return outputImage;
}

KImageGray K_VISION::HM(KImageGray &srcImage, KImageGray &refImage)
{
    double row = srcImage.Row();
    double col = srcImage.Col();
    KImageGray outputImage(row,col);

    // image histogram
    KHisto srcHistogram(srcImage);
    KHisto refHistogram(refImage);

    // Cumulative Density Function - CDF
    for(int i = 1; i < 256; i++)
    {
        srcHistogram[i] += srcHistogram[i-1];
        refHistogram[i] += refHistogram[i-1];

    }

    // Histogram Equalization // 합이 1이 되도록
    double size = srcImage.Size();
    for(int i = 0; i < 256; i++)
    {
        srcHistogram[i] = (double)srcHistogram[i]/(double)size * 255.0;
        refHistogram[i] = (double)refHistogram[i]/(double)size * 255.0;
    }

    int last = 0;
    int lut[256] = {0,};
    for(int i = 0; i < 256; i++)
    {
        int src_data = srcHistogram[i];
        double min = 1000.0;
        double index = 0;
        double diff = 0;

        for(int k = last; k < 256; k++)
        {
            int ref_data = refHistogram[k];
            diff = abs(ref_data - src_data);

            if(diff < min)
            {
                min = diff;
                index = k;
                last = k;
            }
        }
        lut[i] = last;
    }

    for(int y = 0; y < row; y++)
        for(int x = 0; x < col; x++)
            outputImage._ppA[y][x] = lut[(int)srcImage._ppA[y][x]];


    return outputImage;
}

KImageColor K_VISION::HM(KImageColor &srcImage, KImageColor &refImage)
{
    KImageColor outputImage(srcImage.Row(), srcImage.Col());

    vector<KImageGray> rgbsplit_src(3);
    splitRGB(srcImage, rgbsplit_src[0], rgbsplit_src[1], rgbsplit_src[2]);

    vector<KImageGray> rgbsplit_ref(3);
    splitRGB(refImage, rgbsplit_ref[0], rgbsplit_ref[1], rgbsplit_ref[2]);

    vector<KImageGray> result(3);

    result[0] = HM(rgbsplit_src[0],rgbsplit_ref[0]);
    result[1] = HM(rgbsplit_src[1],rgbsplit_ref[1]);
    result[2] = HM(rgbsplit_src[2],rgbsplit_ref[2]);

    for(int y = 0; y < srcImage.Row(); y++)
        for(int x = 0; x < srcImage.Col(); x++)
        {
            outputImage._ppA[y][x].r = (unsigned char)result[0]._ppA[y][x];
            outputImage._ppA[y][x].g = (unsigned char)result[1]._ppA[y][x];
            outputImage._ppA[y][x].b = (unsigned char)result[2]._ppA[y][x];
        }

    return outputImage;
}

KImageGray K_VISION::SaltPepperNoise(KImageGray &input, double threshold)
{

    KRandom random;
    KImageGray ouput(input.Row(), input.Col());
    double whiteNoise = 1 - threshold;
    for(int y = 0; y < input.Row(); y++)
        for(int x = 0; x < input.Col(); x++)
        {
            double rand = random.Generate();
            ouput._ppA[y][x] = rand > whiteNoise ? 255 : (rand < threshold ? 0 : input._ppA[y][x]);
        }
    return ouput;
}
KImageColor K_VISION::SaltPepperNoise(KImageColor &input, double threshold)
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

KImageGray K_VISION::GaussianNoise(KImageGray &input, int variance)
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
KImageColor K_VISION::GaussianNoise(KImageColor &input, int variance)
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


KImageGray K_VISION::Median(KImageGray &input, int mask)
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

KImageColor K_VISION::Median(KImageColor &input, int mask)
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

KImageGray K_VISION::GaussianFiltering(KImageGray &input, double sigma)
{
    KImageGray output(input.Row(), input.Col());
    //create the gaussian kernal
    int     half = (int)(3.0*sigma+0.3);
    vector<vector<double>> mask;
    vector<double> _mask(half*2+1);
    mask.push_back(_mask);
    mask.push_back(_mask);
    mask.push_back(_mask);

    double _sigma = 2.0*(sigma*sigma);
    double _const = 1.0/(2*M_PI*sigma*sigma);
    double scale = 0;
    int r = 0;
    int c = 0;
    for(int i = -half; i < half; i++)
    {
        for(int j = -half; j < half; j++)
        {
            mask[r++][c++] = _const*exp(-(i*i+j*j)/_sigma);
            scale     += mask[i][j];
        }
    }
    // nomalize
    for(int i = -half; i < half; i++)
        for(int j = -half; j < half; j++)
            mask [r++][c++]/= scale;

    for(int y = 0; y < input.Row()-half; y++)
        for(int x = half; input.Col(); x++)
        {
            double data = 0;
            for(int i = -half; i < half; i++)
                for(int j = -half; j < half; j++)
                {
                    data += input._ppA[y][x] * mask[i][j];
                }
            output._ppA[y][x] = (unsigned char)data;

        }
    return output;
}

KImageColor K_VISION::GaussianFiltering(KImageColor &input, double sigma)
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




KImageGray K_VISION::CannyEdge(double sigma, double dLow,double dHigh,const KImageGray& igIn)
{
    double width = igIn.Col();
    double height = igIn.Row();
    KImageGray igOut(height, width);
    KImageGray ig22(height, width);
    KImageGray ligOut(height, width);

    double dSigma = sigma;//시그마 값을 설정 할 수 있도록 한다.

    KEdge FDG;  //Edge 클래스 변수를 선언한다.

    FDG.Create(dSigma);//미분을 한 가우시안 식에 시그마 값을 넣어준다. 이로 시그널에대해서 FDG를 통해 Kernel영역을 만든다.
    FDG.Gradient(igIn, ig22);//signal과 convolution을 한다. 이로 엣지를 찾아 낼 수있도록 한다.

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
    vector<vector<double>> _idBuf; // 확실하지 않은 엣지

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
                    // ch!
                    //                    gradientX += igIn._ppA[y+r][x+c] * mask[rr][cc];
                    //                    gradientY += igIn._ppA[y+r][x+c] * mask[rr][cc];
                    gradientX += igIn._ppA[y+r][x+c] * FDG.KernelX()._ppA[rr][cc];
                    gradientY += igIn._ppA[y+r][x+c] * FDG.KernelY()._ppA[rr][cc];
                }
            //magnitude
            magnitude[y][x] = _ABS(gradientX) + _ABS(gradientY);
            if( magnitude[y][x] > dLow)
            {
                temp =  atan((float)gradientY/(float)gradientX);
                //                temp = temp %360.0;
                temp = fmod(temp, 360.0);
                angle[y][x] = (unsigned short)(temp+0.5);               //0~360
                dir._ppA[y][x] = (unsigned char)((((int)(temp/22.5)+1)>>1) & 0x00000003); //0~3
                //                cout<<"magnitude["<<y<<"]["<<x<<"]:"<<magnitude[y][x]<<endl;
            }
            else
                magnitude[y][x] = 0.0;

        }
    }

    //Non-maxima suppression
    KImageGray ImgBuf(height, width);

    for(int y = 0; y < height; y++)
    {
        for(int x = 0; x < width; x++)
        {
            if(dir._ppA[y][x] == 0)
            {
                //좌우 픽셀이 크면 엣지 X
                if(magnitude[y][x] < magnitude[y][x+1] || magnitude[y][x] < magnitude[y][x-1])
                    igOut._ppA[y][x] = 0;
                else
                {
                    //지정한 사이의 밝기값 이상이면 무조건 엣지
                    if(magnitude[y][x] > dHigh)
                        igOut._ppA[y][x] = 255;
                    //그 사이이 값이면 Hysteresis-based Tresholding과정을 통하여 엣지를 판별
                    else if((magnitude[y][x] > dLow) && (magnitude[y][x] < dHigh))
                        ImgBuf._ppA[y][x] = 1;
                    //지정한 사이의 밝기값 이하이면 무조건 엣지
                    else if(magnitude[y][x] < dLow)
                        igOut._ppA[y][x] = 0;
                }
            }
            else if(dir._ppA[y][x] == 1)
            {
                // 대각선 픽셀이 크면 엣지 X
                if(magnitude[y][x] < magnitude[y-1][x+1] || magnitude[y][x] < magnitude[y+1][x-1])
                    igOut._ppA[y][x] = 0;
                else
                {
                    //지정한 사이의 밝기값 이상이면 무조건 엣지
                    if(magnitude[y][x] > dHigh)
                        igOut._ppA[y][x] = 255;
                    //그 사이이 값이면 Hysteresis-based Tresholding과정을 통하여 엣지를 판별
                    else if((magnitude[y][x] > dLow) && (magnitude[y][x] < dHigh))
                        ImgBuf._ppA[y][x] = 1;
                    //지정한 사이의 밝기값 이하이면 무조건 엣지
                    else if(magnitude[y][x] < dLow)
                        igOut._ppA[y][x] = 0;
                }
            }
            else if(dir._ppA[y][x] == 2)
            {
                //상하 픽셀이 크면 엣지 X
                if(magnitude[y][x] < magnitude[y-1][x] || magnitude[y][x] < magnitude[y+1][x])
                    igOut._ppA[y][x] = 0;
                else
                {
                    //지정한 사이의 밝기값 이상이면 무조건 엣지
                    if(magnitude[y][x] > dHigh)
                        igOut._ppA[y][x] = 255;
                    //그 사이이 값이면 Hysteresis-based Tresholding과정을 통하여 엣지를 판별한다.
                    else if((magnitude[y][x] > dLow) && (magnitude[y][x] < dHigh))
                        ImgBuf._ppA[y][x] = 1;
                    //지정한 사이의 밝기값 이하이면 무조건 엣지
                    else if(magnitude[y][x] < dLow)
                        igOut._ppA[y][x] = 0;
                }
            }
            else if(dir._ppA[y][x] == 3)
            {
                //대각선 픽셀이 크면 엣지 X
                if(magnitude[y][x] < magnitude[y+1][x+1] || magnitude[y][x] < magnitude[y-1][x-1])
                    igOut._ppA[y][x] = 0;
                else
                {
                    //지정한 사이의 밝기값 이상이면 무조건 엣지
                    if(magnitude[y][x] > dHigh)
                        igOut._ppA[y][x] = 255;
                    //그 사이이 값이면 Hysteresis-based Tresholding과정을 통하여 엣지를 판별
                    else if((magnitude[y][x] > dLow) && (magnitude[y][x] < dHigh))
                        ImgBuf._ppA[y][x] = 1;
                    //지정한 사이의 밝기값 이하이면 무조건 엣지
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
            if(ImgBuf._ppA[y][x] == 1) // 아까 그 애매 한 아이들 t0 < x,y < t1
            {
                if(dir._ppA[y][x] == 0)
                {
                    //좌우 픽셀값이 모두 High이면 엣지
                    if(igOut._ppA[y][x+1] == 255 && igOut._ppA[y][x-1] == 255)
                        igOut._ppA[y][x] = 255;
                    else
                        igOut._ppA[y][x] = 0;
                }
                else if(dir._ppA[y][x] == 1)
                {
                    //대각선 픽셀값이 모두 High이면 엣지
                    if( igOut._ppA[y-1][x+1] == 255 && igOut._ppA[y+1][x-1] == 255)
                        igOut._ppA[y][x] = 255;
                    else
                        igOut._ppA[y][x] = 0;

                }
                else if(dir._ppA[y][x] == 2)
                {
                    //상하 픽셀값이 모두 High이면 엣지
                    if(igOut._ppA[y-1][x] == 255 && igOut._ppA[y+1][x] == 255)
                        igOut._ppA[y][x] = 255;
                    else
                        igOut._ppA[y][x] = 0;
                }
                else if(dir._ppA[y][x] == 3)
                {
                    //대각선 픽셀값이 모두 High이면 엣지
                    if(igOut._ppA[y+1][x+1] == 255 && igOut._ppA[y-1][x-1] == 255)
                        igOut._ppA[y][x] = 255;
                    else
                        igOut._ppA[y][x] = 0;
                }

            }
        }
    }


    //    int         nShiftX[4] = {-1,1,0,-1};
    //    int         nShiftY[4] = {0,1,1,1};
    //    int         nH=height-half-1, nW=width-half-1;
    //    KEDGEPIXEL    oEdgeMag;
    //    KStack<KEDGEPIXEL> _skTmp;

    //    for(int y = half; y < height - half; y++)
    //    {
    //        for(int x = half; x < width - half; x++)
    //        {
    //            if(magnitude[y][x] == 0.0) continue;

    //            if(magnitude[y][x] > magnitude[y + nShiftY[dir._ppA[y][x]] ][x + nShiftX[dir._ppA[y][x]] ] &&
    //                 magnitude[y][x] > magnitude[y - nShiftY[dir._ppA[y][x]] ][x - nShiftX[dir._ppA[y][x]] ])
    //            {
    //                if(magnitude[y][x] > dHigh){
    //                    oEdgeMag.u    = (unsigned short)y;
    //                    oEdgeMag.v 	  = (unsigned short)x;
    //                    oEdgeMag.wAng = angle[y][x];
    //                    oEdgeMag.wDir = dir._ppA[y][x];
    //                    oEdgeMag.dMag = magnitude[y][x];
    //                    _skTmp.Push(oEdgeMag);
    //                }
    //                _idBuf[y][x] = magnitude[y][x];
    //            }
    //        }
    //    }

    //    //hysteresis thresholding
    //    int iy,jx;
    //    while(_skTmp.Pop(oEdgeMag) != -1)
    //    {
    //        //store edge list
    ////        out.push_back(oEdgeMag);
    //        //get edge coordinate
    //        jx  = oEdgeMag.u;
    //        iy  = oEdgeMag.v;
    //        //search neighbor edges
    //        for(int i=-1; i<2; i++)
    //            for(int j=-1; j<2; j++)
    //                if(_idBuf[iy+i][jx+j] && _idBuf[iy+i][jx+j]<=dHigh)
    //                {
    //                    oEdgeMag.u    = (unsigned short)(jx+j);
    //                    oEdgeMag.v 	  = (unsigned short)(iy+i);
    //                    oEdgeMag.wAng = angle[iy+i][jx+j];
    //                    oEdgeMag.wDir = dir._ppA[iy+i][jx+j];
    //                    oEdgeMag.dMag = _idBuf[iy+i][jx+j];

    //                    _skTmp.Push(oEdgeMag);
    //                    _idBuf[iy+i][jx+j] = 0.;
    //                }
    //    }

    //    for(int i = 0; i < _skTmp.Count(); i++)
    //    {
    //        igOut._ppA[_skTmp[i].u][_skTmp[i].v];
    //    }
    return igOut;
}

KImageColor K_VISION::CircleByHT(KEdge &opEdge, const KImageGray inputImg, const int voteTreshold, const int &minR, const int &maxR)
{

    KImageGray temp = inputImg;
    KImageColor outputImg;
    temp.GrayToRGB(outputImg);


    HOUGHCIRCLE_INFO circleInfo;
    circleInfo.nLeft       = -1;    // ROI
    circleInfo.nRight      = 1;     // ROI
    circleInfo.nTop        = -1;   // ROI
    circleInfo.nBottom     = 1;   // ROI
    circleInfo.nMinR       = minR;   // 반지름이 너무 작을 경우
    circleInfo.nMaxR       = maxR; // 반지름이 너무 클 경우
    circleInfo.nNumGridCx  = inputImg.Col();    // Cell의 크기 X
    circleInfo.nNumGridCy  = inputImg.Row();   // Cell의 크기 Y
    circleInfo.nNumGridR   = circleInfo.nMaxR - circleInfo.nMinR; // Cell의 크기 Radius
    circleInfo.nDirEdge    = 0;
    circleInfo.nThreshVote = voteTreshold; // voting 된 수 임계값


    vector<vector<vector<double>>> arVotes;
    arVotes.assign(circleInfo.nNumGridCy, vector < vector <double> >(circleInfo.nNumGridCx, vector <double>(circleInfo.nNumGridR, 0.0)));

    int nGridR, nGridCx, nGridCy;
    double dAngle,  dMaxVote, dRadius = 0.0;


    tagKEDGEPIXEL oEdge;
    while(opEdge.Pop(oEdge) != -1) // gradient를 얻기 위해 Canny Edge를 통해 얻은 데이터를 하나씩 빼서 oEdge에 저장
    {
        // votes for radius start
        dRadius = (double)circleInfo.nMinR;
        nGridR = 1;
        dAngle = (oEdge.wAng)*DEG2RAD;

        do{
            double a = oEdge.u - dRadius*cos(dAngle); // a = x - r*cos(pi)
            double b = oEdge.v - dRadius*sin(dAngle); // b = y - r*sin(pi)

            // votes to avoid edge noises
            for(int j= -5; j<= 5; j++)
            {
                for(int i=-5 ; i<= 5 ; i++)
                {
                    if(b+i < 0 || b+i >= circleInfo.nNumGridCy ||
                            a+j < 0 || a+j >= circleInfo.nNumGridCx)    continue;

                    arVotes[b + i][a + j][nGridR-1] += 0.7; // 노이즈가 있을 수 있기 때문에 픽셀 중심으로 5x5 만큼 0.7씩 더해줌
                    arVotes[b + i][a + j][nGridR] += 0.7;
                    arVotes[b + i][a + j][nGridR+1] += 0.7;
                }
            }
            arVotes[b][a][nGridR] += 0.3; // 해당하는 픽셀은 위코드에서 더해준 0.7에서 0.3을 더 더해줘서 1을 만듬
            dRadius += 1;

        }
        while(++nGridR < circleInfo.nNumGridR - 1);         // votes for radius end
        //next edge ->
    }

    double maxVote = 0.0;
    int maxVoteCx, maxVoteCy = 0.0;
    double maxVoteR = 0.0;
    for(int i = 0; i < circleInfo.nNumGridCy; i++)
        for(int j = 0; j < circleInfo.nNumGridCx; j++)
            for(int r = 0; r < circleInfo.nNumGridR; r++)
            {

                if(maxVote < arVotes[i][j][r])
                {
                    maxVote =    arVotes[i][j][r];
                    maxVoteCx = j;
                    maxVoteCy = i;
                    maxVoteR = circleInfo.nMinR + r;
                }
            }

    cout<<"@@@@@@@@@@@@ maxVoteR: "<<maxVoteR<<"@@@@@@@@@@@@"<<endl;

    // draw circle
    for(int y = 0; y < circleInfo.nNumGridCy; y++)
    {
        for(int x = 0; x < circleInfo.nNumGridCx; x++)
        {
            double radiusSquared = (x-maxVoteCx)*(x-maxVoteCx) + (y-maxVoteCy)*(y-maxVoteCy);
            double diff = (maxVoteR*maxVoteR) - radiusSquared;
            if(fabs(diff) < 50)
            {
                outputImg._ppA[y][x].g =255;
            }
        }
    }

    return outputImg;
}

void GHT::_ReadData()
{

    ifstream get_point;
    KPOINT temp;
    get_point.open("data/plug.txt");

    ptModel.clear();

    if(get_point.is_open() == 0 ){
        std::cout << "file open wrong" << std::endl;
        return ;
    }
    else
    {
        std::cout << "file open success" << std::endl;
    }

    get_point>>nModelPtNum;
    cout << nModelPtNum << endl;
    dModelPtCen.dX = 0;
    dModelPtCen.dY = 0;


    for(int i = 0; i < nModelPtNum ; i++)
    {
        get_point >> temp.nX;
        get_point >> temp.nY;

        dModelPtCen.dX += temp.nX;
        dModelPtCen.dY += temp.nY;

        ptModel.push_back(temp);
    }
    dModelPtCen.dX = (int)(dModelPtCen.dX / nModelPtNum);
    dModelPtCen.dY = (int)(dModelPtCen.dY / nModelPtNum);

    get_point.close();
}

void GHT::_initShapeTable()
{
    SHAPE_TABLE shapeTable;
    KMath   oMath;

    for(int i=1; i<ptModel.size() - 2; i++)
    {
        //에지 방향 설정 - 양 옆 점의 기울기로 부터 에지 방향 계산
        double dTmp = oMath.Atan((float)(ptModel[i+1].nX - ptModel[i-1].nX),
                (float)(ptModel[i+1].nY - ptModel[i-1].nY));
        dTmp += 90.0; //에지 방향(0~360)

        int nDir = ((((int)(dTmp/22.5)+1)>>1) & 0x00000003); //에지 방향(0~3)
//        cout << nDir << endl;
        //중심과의 거리
        double dDist = sqrt(_SQR(dModelPtCen.dX - ptModel[i].nX) + _SQR(dModelPtCen.dY - ptModel[i].nY));

        //중심과 이루는 각도
        double dAng = atan2(ptModel[i].nY - dModelPtCen.dY,
                            ptModel[i].nX - dModelPtCen.dX);

        shapeTable.dDistance  = dDist;
        //cout << dDist << endl;
        shapeTable.dAngle   = dAng;
        //cout << dAng << endl;

        vShapeTable[nDir].push_back(shapeTable);
    }
}

void GHT::_NonMaxiaSuppresion()
{
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

}

void GHT::GHT_init(KImageGray input, const double &minScale, const double &maxScale, const int &voteThresh)
{
    _ReadData();
    dMinScale = minScale;
    dMaxScale = maxScale;
    nVoteThrshold = voteThresh;

    dMaxAngle = 360.0;
    dSAngle = 10.0;
    dSScale = 0.2;
    nScaleSize = (int)(1 + (1.0 - dMinScale)/dSScale + (dMaxScale - 1.0)/dSScale);

    nVoteSpaceHeight = input.Col();
    nVoteSpaceWidth = input.Row();
    nVoteSpaceAngle = (int)(dMaxAngle/dSAngle);

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

    _initShapeTable();
}

void GHT::runGHT(KEdge &edgePixel)
{
    int edgeSize = edgePixel.Count();
    KEDGEPIXEL tempEdge;

    for(int x = 0; x < edgeSize; x++)
    {
        for(double dAng = 0.0; dAng<(double)dMaxAngle; dAng += dSAngle)
        {
            edgePixel.Pop(tempEdge);
            int nAng = (int)(dAng/dSAngle);
            double dTmp = tempEdge.wAng - dAng;

            int nDir = ((((int)(dTmp/22.5)+1)>>1) & 0x00000003);

            for(int i = 0; i<vShapeTable[nDir].size(); i++)
            {
                for(double dScale = dMinScale; dScale <= dMaxScale; dScale += dSScale)
                {
                    int nScale = (int)((dScale - dMinScale)/dSScale);

                    double Cx = tempEdge.u - (dScale * vShapeTable[nDir][i].dDistance) * cos(vShapeTable[nDir][i].dAngle + _RADIAN(dAng));
                    double Cy = tempEdge.v - (dScale * vShapeTable[nDir][i].dDistance) * sin(vShapeTable[nDir][i].dAngle + _RADIAN(dAng));

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
    _NonMaxiaSuppresion();
}

void GHT::drawModel(KImageColor &output)
{
    double dMaxVotes = 0.0;
    double Cx = 0.0;
    double Cy = 0.0;
    double dAng = 0.0;
    double dScale = 1.0;


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

    for(KPOINT modelPoint:ptModel){
        double moveX = (Cx + dScale*(modelPoint.nX - dModelPtCen.dX)*cos(_RADIAN(dAng)) - dScale*(modelPoint.nY - dModelPtCen.dY)*sin(_RADIAN(dAng)));
        double moveY = (Cy + dScale*(modelPoint.nX- dModelPtCen.dX)*sin(_RADIAN(dAng)) + dScale*(modelPoint.nY - dModelPtCen.dY)*cos(_RADIAN(dAng)));
        output._ppA[(int)moveY][(int)moveX].r = 255;
        output._ppA[(int)moveY][(int)moveX].g = 0;
        output._ppA[(int)moveY][(int)moveX].b = 0;

        output._ppA[(int)moveY][(int)moveX+1].r = 255;
        output._ppA[(int)moveY][(int)moveX+1].g = 0;
        output._ppA[(int)moveY][(int)moveX+1].b = 0;

        output._ppA[(int)moveY][(int)moveX-1].r = 255;
        output._ppA[(int)moveY][(int)moveX-1].g = 0;
        output._ppA[(int)moveY][(int)moveX-1].b = 0;

        output._ppA[(int)moveY-1][(int)moveX].r = 255;
        output._ppA[(int)moveY-1][(int)moveX].g = 0;
        output._ppA[(int)moveY-1][(int)moveX].b = 0;

        output._ppA[(int)moveY+1][(int)moveX].r = 255;
        output._ppA[(int)moveY+1][(int)moveX].g = 0;
        output._ppA[(int)moveY+1][(int)moveX].b = 0;
    }

}

