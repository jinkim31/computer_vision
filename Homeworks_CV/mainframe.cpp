#include <QFileDialog>
#include <QPainter>

#include "mainframe.h"
#include "ui_mainframe.h"
#include "imageform.h"

#include "iostream"
using namespace std;

MainFrame::MainFrame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainFrame)
{
    ui->setupUi(this);

    _plpImageForm       = new KPtrList<ImageForm*>(10,false,false);
    _q_pFormFocused     = 0;

    //객체 맴버의 초기화

    //get a current directory
    char st[100];
    GetCurrentDirectoryA(100,st);

    //리스트 출력창을 안보이게
    ui->listWidget->setVisible(false);
    this->adjustSize();

    //UI 활성화 갱신
    UpdateUI();
}

MainFrame::~MainFrame()
{ 
    delete ui;
    delete _plpImageForm;


}

void MainFrame::CloseImageForm(ImageForm *pForm)
{
    //ImageForm 포인터 삭제
    _plpImageForm->Remove(pForm);

    //활성화 ImageForm 초기화
    _q_pFormFocused     = 0;

    //관련 객체 삭제

    //UI 활성화 갱신
    UpdateUI();
}
//    FDG.Canny(dLow,dHigh,igIn,ligOut);

void MainFrame::UpdateUI()
{
    if(ui->tabWidget->currentIndex() == 0)
    {
        ui->buttonSepiaTone ->setEnabled( _q_pFormFocused &&  _q_pFormFocused->ID() == "OPEN" );
        ui->pushButtonLCT   ->setEnabled( _q_pFormFocused &&  _q_pFormFocused->ID() == "OPEN" );
    }
    else if(ui->tabWidget->currentIndex() == 1)
    {
        ui->pushButtonOtsu  ->setEnabled( _q_pFormFocused &&  _q_pFormFocused->ID() == "OPEN" );
    }
    else if(ui->tabWidget->currentIndex() == 2)
    {
        ui->pushButtonHE -> setEnabled( _q_pFormFocused &&  _q_pFormFocused->ID() == "OPEN" );
        ui->pushButtonME -> setEnabled( _q_pFormFocused &&  _q_pFormFocused->ID() == "OPEN" );
    }
    else if(ui->tabWidget->currentIndex() == 3)
    {

    }
    else if(ui->tabWidget->currentIndex() == 4)
    {

    }
    else if(ui->tabWidget->currentIndex() == 5)
    {

    }
    else if(ui->tabWidget->currentIndex() == 6)
    {

    }

}
void MainFrame::on_tabWidget_currentChanged(int index)
{
    UpdateUI();
}
void MainFrame::OnMousePos(const int &nX, const int &nY, ImageForm* q_pForm)
{

    UpdateUI();
}

void MainFrame::closeEvent(QCloseEvent* event)
{
    //생성된 ImageForm을 닫는다.
    for(int i=_plpImageForm->Count()-1; i>=0; i--)
        _plpImageForm->Item(i)->close();

    //리스트에서 삭제한다.
    _plpImageForm->RemoveAll();
}


void MainFrame::on_buttonOpen_clicked()
{
    //이미지 파일 선택
    QFileDialog::Options    q_Options   =  QFileDialog::DontResolveSymlinks  | QFileDialog::DontUseNativeDialog; // | QFileDialog::ShowDirsOnly
    QString                 q_stFile    =  QFileDialog::getOpenFileName(this, tr("Select a Image File"),  "./data", "Image Files(*.bmp *.ppm *.pgm *.png)",0, q_Options);

    if(q_stFile.length() == 0)
        return;
    OPF_Path = q_stFile.toStdString();
    cout << OPF_Path << endl;
    //이미지 출력을 위한 ImageForm 생성
    ImageForm*              q_pForm   = new ImageForm(q_stFile, "OPEN", this);

    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    //UI 활성화 갱신
    UpdateUI();
}

void MainFrame::on_buttonDeleteContents_clicked()
{
    //생성된 ImageForm을 닫는다.
    for(int i=_plpImageForm->Count()-1; i>=0; i--)
        _plpImageForm->Item(i)->close();

    //리스트에서 삭제한다.
    _plpImageForm->RemoveAll();
}


void MainFrame::on_buttonSepiaTone_clicked()
{
    K_VISION homework1;

    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    //hue, saturation 값 가져오기
    double dHue = ui->spinHue->text().toDouble();
    double dSat = ui->spinSaturation->text().toDouble(); // 위와 같은 식으로

    KArray<KHSV> transformImage;
    transformImage = homework1.RGBtoHSV(icMain);

    vector<KImageGray> hsvSplit(3);
    homework1.splitHSV(transformImage, hsvSplit[0], hsvSplit[1], hsvSplit[2]);
    homework1.sepiaTone(transformImage, dHue, dSat);

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(homework1.HSVtoRGB(transformImage), "Sepia Tone", this);
    ImageForm*  q_pFormH = new ImageForm(hsvSplit[0], "H", this);
    ImageForm*  q_pFormS = new ImageForm(hsvSplit[1], "S", this);
    ImageForm*  q_pFormV = new ImageForm(hsvSplit[2], "V", this);

    _plpImageForm->Add(q_pForm);
    _plpImageForm->Add(q_pFormH);
    _plpImageForm->Add(q_pFormS);
    _plpImageForm->Add(q_pFormV);

    q_pForm->show();
    q_pFormH->show();
    q_pFormS->show();
    q_pFormV->show();

    //UI 활성화 갱신
    UpdateUI();
}


void MainFrame::on_buttonShowList_clicked()
{
    static int nWidthOld = ui->tabWidget->width();

    if(ui->listWidget->isVisible())
    {
        nWidthOld = ui->listWidget->width();
        ui->listWidget->hide();
        this->adjustSize();
    }
    else
    {
        ui->listWidget->show();
        QRect q_rcWin = this->geometry();

        this->setGeometry(q_rcWin.left(), q_rcWin.top(), q_rcWin.width()+nWidthOld, q_rcWin.height());
    }
}

void MainFrame::on_pushButtonLCT_clicked()
{
    K_VISION homework1;
    KImageGray igImage;
    KImageColor icImage;
    ImageForm*  q_pForm_result;

    double a = ui->spinBoxA->text().toDouble();
    double b = ui->spinBoxB->text().toDouble();

    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
    {
        icImage = homework1.LCT(0, 255, a, b, _q_pFormFocused->ImageColor());
        q_pForm_result =  new ImageForm(icImage, "LCT - Color image", this);
    }
    else if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
    {
        igImage = homework1.LCT(0, 255, a, b, _q_pFormFocused->ImageGray());
        q_pForm_result =  new ImageForm(igImage, "LCT - Gray image", this);
    }
    else
        return;

    _plpImageForm->Add(q_pForm_result);
    q_pForm_result->show();

    //UI 활성화 갱신
    UpdateUI();
}

//  ---------------------------------------------------- homework 2 ----------------------------------------------------

void MainFrame::on_pushButtonOtsu_clicked()
{
    K_VISION homework2;
    KImageGray igImage_otsu;
    KImageGray imgLabeling;
    KImageColor drawedImg;
    ImageForm*  q_pForm_result_otsu;
    ImageForm*  q_pForm_result_label;

    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
    {
        igImage_otsu = homework2.Otsu(_q_pFormFocused->ImageGray());
        q_pForm_result_otsu =  new ImageForm(igImage_otsu, "Otsu - Gray image", this);


        imgLabeling.Create(igImage_otsu.Row(), igImage_otsu.Col());
        KPOINT curPoint;
        int index = 1;
        for(int i = 0 ; i < igImage_otsu.Row() ; i ++)
            for(int j = 0 ; j < igImage_otsu.Col() ; j ++)
            {
                curPoint = KPOINT(i, j);
                if(igImage_otsu[i][j] != 0 && imgLabeling[i][j] == 0)
                {
                    imgLabeling[i][j] = index;
                    labeling_8_neighbor(igImage_otsu, imgLabeling, curPoint, index);
                    index++;
                }
            }

        int colorIndex = 0;
        cout << "labeling finish" << endl;

        drawedImg.Create(imgLabeling.Row(), imgLabeling.Col());
        for(int i = 0 ; i < imgLabeling.Row() ; i++)
            for(int j = 0 ; j < imgLabeling.Col() ; j ++)
            {
                if(imgLabeling[i][j] != 0)
                {
                    colorIndex = imgLabeling[i][j] % 5;
                    switch(colorIndex)
                    {
                    case 0:
                        drawedImg[i][j].r = 255;
                        drawedImg[i][j].g = 0;
                        drawedImg[i][j].b = 0;
                        break;
                    case 1:
                        drawedImg[i][j].r = 0;
                        drawedImg[i][j].g = 255;
                        drawedImg[i][j].b = 0;
                        break;
                    case 2:
                        drawedImg[i][j].r = 0;
                        drawedImg[i][j].g = 0;
                        drawedImg[i][j].b = 255;
                        break;
                    case 3:
                        drawedImg[i][j].r = 255;
                        drawedImg[i][j].g = 0;
                        drawedImg[i][j].b = 255;
                        break;
                    case 4:
                        drawedImg[i][j].r = 0;
                        drawedImg[i][j].g = 255;
                        drawedImg[i][j].b = 255;
                        break;
                    case 5:
                        drawedImg[i][j].r = 255;
                        drawedImg[i][j].g = 255;
                        drawedImg[i][j].b = 0;
                        break;
                    default:
                        cout << "error" << endl;
                        break;
                    }
                }
            }
        cout << "labeling drawing finish" << endl;
        q_pForm_result_label = new ImageForm(drawedImg, "Labeling", this);

    }
    else
        return;

    _plpImageForm->Add(q_pForm_result_otsu);
    _plpImageForm->Add(q_pForm_result_label);

    q_pForm_result_otsu->show();
    q_pForm_result_label->show();

}

//void MainFrame::on_pushButtonOtsu_clicked()
//{
//    K_VISION homework2;
//    KImageGray igImage_otsu;
//    KImageGray igImage_label;
//    KImageGray imgLabeling;
//    KImageColor drawedImg;
//    KImageColor iCImage;
//    map<int, int> equivalenceTable;
//    ImageForm*  q_pForm_result_otsu;
//    ImageForm*  q_pForm_result_label;

//    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
//    {
//        igImage_otsu = homework2.Otsu(_q_pFormFocused->ImageGray());
//        q_pForm_result_otsu =  new ImageForm(igImage_otsu, "Otsu - Gray image", this);

//        imgLabeling.Create(igImage_otsu.Row(), igImage_otsu.Col());

//        homework2.Labeling(igImage_otsu, igImage_label, equivalenceTable);
//        iCImage.Create(igImage_label.Row(), igImage_label.Col());
//        for(int y = 0; y < igImage_label.Row(); y++)
//            for(int x = 0; x < igImage_label.Col(); x++)
//            {
//                if(igImage_label[y][x] != 0)
//                {
////                    cout<<"(int)igImage_label[y][x]: "<<(int)igImage_label[y][x]<<endl;
////                    cout<<"equivalenceTable[(int)igImage_label[y][x]]: "<<equivalenceTable[(int)igImage_label[y][x]]<<endl;
//                    if(equivalenceTable[(int)igImage_label[y][x]] %2 == 0)
//                    {
//                        iCImage._ppA[y][x].r =  255;
//                        iCImage._ppA[y][x].g = equivalenceTable[(int)igImage_label[y][x]]*50 > 254 ? 254 : equivalenceTable[(int)igImage_label[y][x]]*50;
//                        iCImage._ppA[y][x].b = equivalenceTable[(int)igImage_label[y][x]]*2;
//                    }
//                    else
//                    {
//                        iCImage._ppA[y][x].r = equivalenceTable[(int)igImage_label[y][x]]*50 > 254 ? 254 : equivalenceTable[(int)igImage_label[y][x]]*50;
//                        iCImage._ppA[y][x].b =  255;
//                        iCImage._ppA[y][x].g = equivalenceTable[(int)igImage_label[y][x]]*4;
//                    }
//                }

//            }
//        iCImage._ppA[48][185].r =  0;
//        iCImage._ppA[48][185].b = 255;
//        iCImage._ppA[48][185].g = 0;

//        iCImage._ppA[47][185].r =  0;
//        iCImage._ppA[47][185].b = 255;
//        iCImage._ppA[47][185].g = 0;

//        iCImage._ppA[49][185].r =  0;
//        iCImage._ppA[49][185].b = 255;
//        iCImage._ppA[49][185].g = 0;

//        iCImage._ppA[48][186].r =  0;
//        iCImage._ppA[48][186].b = 255;
//        iCImage._ppA[48][186].g = 0;

//        iCImage._ppA[48][184].r =  0;
//        iCImage._ppA[48][184].b = 255;
//        iCImage._ppA[48][184].g = 0;

//        q_pForm_result_label = new ImageForm(iCImage, "Labeling", this);

//    }
//    else
//        return;

//    _plpImageForm->Add(q_pForm_result_otsu);
//    _plpImageForm->Add(q_pForm_result_label);

//    q_pForm_result_otsu->show();
//    q_pForm_result_label->show();

//}

void MainFrame::labeling_8_neighbor(KImageGray &input, KImageGray &output, KPOINT &nowPoint, const int &index)
{
    KPOINT neighborPoint[8];
    enum{W, NW, N, NE, E, SE, S, SW};
    neighborPoint[W]        = KPOINT(nowPoint.nX     , nowPoint.nY - 1);
    neighborPoint[NW]       = KPOINT(nowPoint.nX - 1 , nowPoint.nY - 1);
    neighborPoint[N]        = KPOINT(nowPoint.nX - 1 , nowPoint.nY);
    neighborPoint[NE]       = KPOINT(nowPoint.nX - 1 , nowPoint.nY + 1);
    neighborPoint[E]        = KPOINT(nowPoint.nX     , nowPoint.nY + 1);
    neighborPoint[SE]       = KPOINT(nowPoint.nX + 1 , nowPoint.nY + 1);
    neighborPoint[S]        = KPOINT(nowPoint.nX + 1 , nowPoint.nY);
    neighborPoint[SW]       = KPOINT(nowPoint.nX + 1 , nowPoint.nY - 1);

    if(neighborPoint[W].nY >= 0)
    {
        if(input._ppA[neighborPoint[W].nX][neighborPoint[W].nY] != 0 &&
                output._ppA[neighborPoint[W].nX][neighborPoint[W].nY] == 0)
        {
            output[neighborPoint[W].nX][neighborPoint[W].nY] = index;
            labeling_8_neighbor(input, output, neighborPoint[W], index);
        }
    }

    if(neighborPoint[NW].nX >= 0 && neighborPoint[NW].nY >= 0)
    {
        if(input._ppA[neighborPoint[NW].nX][neighborPoint[NW].nY]  != 0&&
                output._ppA[neighborPoint[NW].nX][neighborPoint[NW].nY] == 0)
        {
            output._ppA[neighborPoint[NW].nX][neighborPoint[NW].nY] = index;
            labeling_8_neighbor(input, output, neighborPoint[NW], index);
        }
    }

    if(neighborPoint[N].nX >= 0)
    {
        if(input[neighborPoint[N].nX][neighborPoint[N].nY]  != 0&&
                output[neighborPoint[N].nX][neighborPoint[N].nY] == 0)
        {
            output[neighborPoint[N].nX][neighborPoint[N].nY] = index;
            labeling_8_neighbor(input, output, neighborPoint[N], index);
        }
    }

    if(neighborPoint[NE].nX >= 0 && neighborPoint[NE].nY < input.Col())
    {
        if(input[neighborPoint[NE].nX][neighborPoint[NE].nY]  != 0&&
                output[neighborPoint[NE].nX][neighborPoint[NE].nY] == 0)
        {
            output[neighborPoint[NE].nX][neighborPoint[NE].nY] = index;
            labeling_8_neighbor(input, output, neighborPoint[NE], index);
        }
    }

    if(neighborPoint[E].nY < input.Col())
    {
        if(input[neighborPoint[E].nX][neighborPoint[E].nY] != 0 &&
                output[neighborPoint[E].nX][neighborPoint[E].nY] == 0)
        {
            output[neighborPoint[E].nX][neighborPoint[E].nY] = index;
            labeling_8_neighbor(input, output, neighborPoint[E], index);
        }
    }

    if(neighborPoint[SE].nX < input.Row() && neighborPoint[SE].nY < input.Col())
    {
        if(input[neighborPoint[SE].nX][neighborPoint[SE].nY]  != 0&&
                output[neighborPoint[SE].nX][neighborPoint[SE].nY] == 0)
        {
            output[neighborPoint[SE].nX][neighborPoint[SE].nY] = index;
            labeling_8_neighbor(input, output, neighborPoint[SE], index);
        }
    }

    if(neighborPoint[S].nX < input.Row())
    {
        if(input[neighborPoint[S].nX][neighborPoint[S].nY] != 0 &&
                output[neighborPoint[S].nX][neighborPoint[S].nY] == 0)
        {
            output[neighborPoint[S].nX][neighborPoint[S].nY] = index;
            labeling_8_neighbor(input, output, neighborPoint[S], index);
        }
    }

    if(neighborPoint[SW].nX < input.Row() && neighborPoint[SW].nY >= 0)
    {
        if(input[neighborPoint[SW].nX][neighborPoint[SW].nY] != 0 &&
                output[neighborPoint[SW].nX][neighborPoint[SW].nY] == 0)
        {
            output[neighborPoint[SW].nX][neighborPoint[SW].nY] = index;
            labeling_8_neighbor(input, output, neighborPoint[SW], index);
        }
    }
}

//  ---------------------------------------------------- homework 3 ----------------------------------------------------


void MainFrame::on_pushButtonHE_clicked()
{
    K_VISION homework3;
    ImageForm*  q_pForm_result_HE;

    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
    {
        KImageColor icMain;
        KImageColor icImageHE;

        icMain = _q_pFormFocused->ImageColor();
        icImageHE = homework3.HE(icMain);
        q_pForm_result_HE =  new ImageForm(icImageHE, "Histogram Equalization - Color Image", this);
    }
    else if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
    {
        KImageGray igMain;
        KImageGray igImageHE;
        igMain = _q_pFormFocused->ImageGray();
        igImageHE = homework3.HE(igMain);
        q_pForm_result_HE =  new ImageForm(igImageHE, "Histogram Equalization - Gray Image", this);

    }
    else
        return;

    _plpImageForm->Add(q_pForm_result_HE);

    q_pForm_result_HE->show();
}

void MainFrame::on_pushButtonME_clicked()
{
    if(mHMSrcImg.Row()  != 0 &&mHMRefImg.Row() != 0)
    {
        K_VISION homework3;
        ImageForm*  q_pForm_result_HM;
        KImageColor icImageHM;

        icImageHM = homework3.HM(mHMSrcImg, mHMRefImg);
        q_pForm_result_HM =  new ImageForm(icImageHM, "Histogram Matching - Color Image", this);

        _plpImageForm->Add(q_pForm_result_HM);
        q_pForm_result_HM->show();

        ui->pushButtonMESrc->setStyleSheet("background-color: rgb(221, 221, 221)");
        ui->pushButtonMERef->setStyleSheet("background-color: rgb(221, 221, 221)");

        mHMSrcImg.Release();
        mHMRefImg.Release();
    }

}

void MainFrame::on_pushButtonMESrc_clicked()
{
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
    {
        mHMSrcImg = _q_pFormFocused->ImageColor();
        ui->pushButtonMESrc->setStyleSheet("background-color: red");
    }
}

void MainFrame::on_pushButtonMERef_clicked()
{
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
    {
        mHMRefImg = _q_pFormFocused->ImageColor();
        ui->pushButtonMERef->setStyleSheet("background-color: red");
    }
}




//  ---------------------------------------------------- homework 4 ----------------------------------------------------


void MainFrame::on_pushButtonSaltPepper_clicked()
{
    K_VISION homework3;
    ImageForm*  q_pForm_result;

    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
    {
        KImageColor icImage;
        double threshold = ui->spinSaltPepper->text().toDouble();
        icImage = homework3.SaltPepperNoise(_q_pFormFocused->ImageColor(), threshold);
        q_pForm_result =  new ImageForm(icImage, "Salt and pepper Noise", this);
        mNoise = icImage;
    }
    else if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
    {
        KImageGray igImage;
        q_pForm_result =  new ImageForm(igImage, "Salt and pepper Noise", this);
    }
    else
        return;

    _plpImageForm->Add(q_pForm_result);
    q_pForm_result->show();
}


void MainFrame::on_pushButtonMedianFilter_clicked()
{
    K_VISION homework3;
    ImageForm*  q_pForm_result;
    if(mNoise.Row()  != 0)
    {
        KImageColor icImage;
        double mask = ui->spinBoxMedian->text().toDouble();
        icImage = homework3.Median(mNoise, mask);
        q_pForm_result =  new ImageForm(icImage, "Median Filter", this);
    }
    else
        return;
    _plpImageForm->Add(q_pForm_result);
    q_pForm_result->show();
}


void MainFrame::on_pushButtonGaussianNoise_clicked()
{
    K_VISION homework3;
    ImageForm*  q_pForm_result;

    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
    {
        KImageColor icImage;
        double variance = ui->spinGaussianNoise->text().toDouble();
        icImage = homework3.GaussianNoise(_q_pFormFocused->ImageColor(), variance);
        q_pForm_result =  new ImageForm(icImage, "Gaussian Noise", this);
        mNoise = icImage;
    }
    else if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
    {
        KImageGray igImage;
        q_pForm_result =  new ImageForm(igImage, "Gaussian Noise", this);
    }
    else
        return;
    _plpImageForm->Add(q_pForm_result);
    q_pForm_result->show();
}


void MainFrame::on_pushButtonGaussianFilter_clicked()
{
    K_VISION homework3;
    ImageForm*  q_pForm_result;
    if(mNoise.Row()  != 0)
    {
        KImageColor icImage;
        double sigma = ui->spinBoxGaussianFilter->text().toDouble();
        icImage = homework3.GaussianFiltering(mNoise, sigma);
        q_pForm_result =  new ImageForm(icImage, "Gaussian Filter", this);
    }
    else
        return;
    _plpImageForm->Add(q_pForm_result);
    q_pForm_result->show();
}

//  ---------------------------------------------------- homework 5 ----------------------------------------------------



void MainFrame::on_pushButtonCanny_clicked()
{
    K_VISION homework5;
    ImageForm*  q_pForm_result;

    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
    {
        KImageGray icImage;
        double sigma = ui->spinBoxCannySigma->text().toDouble();
        double low  = ui->spinBoxCannyLow ->text().toDouble();
        double high = ui->spinBoxCannyHigh->text().toDouble();

        icImage = homework5.CannyEdge(sigma,low,high,_q_pFormFocused->ImageGray());
        q_pForm_result =  new ImageForm(icImage, "Canny Edge", this);
    }
    else
        return;

    _plpImageForm->Add(q_pForm_result);
    q_pForm_result->show();
}

//  ---------------------------------------------------- homework 6 ----------------------------------------------------


void MainFrame::on_pushButtonHT_clicked()
{
    ImageForm*  q_pForm_result;

    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
    {
        K_VISION homework6;
        GHT homework6_GHT;

        KImageGray igMain = _q_pFormFocused->ImageGray();

        double sigma =1.0;
        double low  = 40;
        double high = 80;

        KRect imgRoi;
        imgRoi.Create(0, 0, igMain.Col(), igMain.Row());

        KEdge oEdge;
        oEdge.Create(sigma);
        oEdge.Canny(low, high,imgRoi, igMain);
        KImageColor icImage = homework6.CircleByHT(oEdge,igMain,30,40,60);

        oEdge.Canny(low, high, imgRoi, igMain);
        homework6_GHT.GHT_init(igMain, 0.6, 0.8, 150);
        homework6_GHT.runGHT(oEdge);
        homework6_GHT.drawModel(icImage);

        q_pForm_result =  new ImageForm(icImage, "Hough Circle", this);
    }
    else
        return;

    _plpImageForm->Add(q_pForm_result);
    q_pForm_result->show();
}
//  ---------------------------------------------------- homework 7 ----------------------------------------------------


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
void putPixel(KImageColor& input,
              int x,
              int y,
              int R,
              int G,
              int B)
{
    if(x < 0 || y < 0) return ;
    if(x >= input.Col() || y >= input.Row()) return ;
    input._ppA[y][x].r = R;
    input._ppA[y][x].g = G;
    input._ppA[y][x].b = B;
}
void MainFrame::on_pushButton_optical_flow_clicked()
{
    if(!OPF_Path.empty())
    {
        int     dot_idx             =   OPF_Path.find_last_of(".") - 2;
        string  strPrevImgNum       =   OPF_Path.substr(dot_idx, 2);
        int     nCurImgNum          =   stoi(strPrevImgNum) + 1;
        string  strCurImgNum        =   (nCurImgNum > 9)?
                    std::to_string(nCurImgNum):
                    "0" + std::to_string(nCurImgNum);
        string  strCurImgPath       =   OPF_Path;
        strCurImgPath.at(dot_idx)       =   strCurImgNum[0];
        strCurImgPath.at(dot_idx + 1)   =   strCurImgNum[1];
        cout << strCurImgPath << endl;
        QString qstrPrevImgPath = QString::fromStdString(OPF_Path);
        QString qstrCurImgPath  = QString::fromStdString(strCurImgPath);

        cout<<"aaaaaaaaaaaaaaaa"<<endl;
        if(nCurImgNum <= 16)
        {
            OPF_Path = strCurImgPath;
        }
        else
        {
            return ;
        }

        OPTICALFLOW OPF;
        ImageForm*  q_pFormPrev = new ImageForm(qstrPrevImgPath, "pre_image", this);
        ImageForm*  q_pFormCur = new ImageForm(qstrCurImgPath, "cur_image", this);


        KImageGray      preImage = q_pFormPrev -> ImageGray();
        KImageGray      curImage = q_pFormCur -> ImageGray();
        KImageColor     opticalFlowImage;
        opticalFlowImage = curImage.GrayToRGB();
        OPF.runOpticalFlow(preImage, curImage, opticalFlowImage);
        cout << "compute_complete2" << endl;
        ImageForm*  q_pFormOpticalFlow = new ImageForm(opticalFlowImage, "Optical Flow", this);
        cout << "compute_complete3" << endl;
        _plpImageForm->Add(q_pFormCur);
        _plpImageForm->Add(q_pFormOpticalFlow);

        q_pFormOpticalFlow->show();
        q_pFormCur->show();

        UpdateUI();

        delete q_pFormPrev;
    }
    else
    {
        return;
    }
}
