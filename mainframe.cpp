#include <QFileDialog>
#include <QPainter>

#include "mainframe.h"
#include "ui_mainframe.h"
#include "imageform.h"
#include "qdebug.h"
#include<cstdlib>
#include<ctime>


MainFrame::MainFrame(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainFrame)
{
    ui->setupUi(this);

    _plpImageForm       = new KPtrList<ImageForm*>(10,false,false);
    _q_pFormFocused     = 0;

    //객체 맴버의 초기화
    targetHistogramAvailable = false;
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

void MainFrame::UpdateUI()
{
    if(ui->tabWidget->currentIndex() == 0)
    {
        ui->buttonSepiaTone->setEnabled( _q_pFormFocused &&  _q_pFormFocused->ID() == "OPEN" );    

    }
    else if(ui->tabWidget->currentIndex() == 1)
    {

    }
    else if(ui->tabWidget->currentIndex() == 2)
    {

    }    
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
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageColor   icMain;    
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    //hue, saturation 값 가져오기
    double dHue = ui->spinHue->text().toDouble();
    double dSat = ui->spinSaturation->text().toDouble();

    cv::sepia(icMain, dHue, dSat);

    //출력을 위한 ImageForm 생성
    ImageForm*  q_pForm = new ImageForm(icMain, "Sepia Tone", this);

    _plpImageForm->Add(q_pForm);
    q_pForm->show();

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

void MainFrame::on_otsuButton_clicked()
{
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageGray();
    else
        return;
    //CODE_START

    KImageGray thresholded;
    cv::otsuThreshold(icMain);

    //CODE_END
    ImageForm*  q_pForm = new ImageForm(icMain, "Otsu", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();
    UpdateUI();
}

void MainFrame::on_erodeButton_clicked()
{
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageGray();
    else
        return;
    //CODE_START

    KImageGray eroded(icMain.Row(), icMain.Col());
    cv::otsuThreshold(icMain);
    cv::erode(icMain, eroded, ui->mophologyComboBox->currentText().toInt());

    //CODE_END
    ImageForm*  q_pForm = new ImageForm(eroded, "Erode", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();
    UpdateUI();
}

void MainFrame::on_dilateButton_clicked()
{
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageGray();
    else
        return;
    //CODE_START

    KImageGray dilated(icMain.Row(), icMain.Col());
    cv::otsuThreshold(icMain);
    cv::dilate(icMain, dilated, ui->mophologyComboBox->currentText().toInt());

    //CODE_END
    ImageForm*  q_pForm = new ImageForm(dilated, "Dilate", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();
    UpdateUI();
}

void MainFrame::on_pushButton_clicked()
{
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageGray();
    else
        return;
    //CODE_START

    cv::otsuThreshold(icMain);
    KBlobList l;
    KImageColor label = cv::labeling(icMain, l);

    //CODE_END
    ImageForm*  q_pForm = new ImageForm(label, "Labeling", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    ImageForm*  q_pForm2 = new ImageForm(icMain, "Binary", this);
    _plpImageForm->Add(q_pForm2);
    q_pForm2->show();
    UpdateUI();
}

void MainFrame::on_pushButton_2_clicked()
{
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;
    //CODE_START

    cv::equalizeHistogram(icMain);

    //CODE_END
    ImageForm*  q_pForm = new ImageForm(icMain, "Hitogram equalization", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();
    UpdateUI();
}

void MainFrame::on_setTargetHisoButton_clicked()
{
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;
    //CODE_START

    targetHistogramImage = icMain;
    targetHistogramAvailable = true;
    ui->targetHistogramLabel->setStyleSheet("background-color: rgb(38, 212, 113);");
    ui->targetHistogramLabel->setText("OK");
    ui->matchHistogramButton->setEnabled(true);

    //CODE_END
}

void MainFrame::on_matchHistogramButton_clicked()
{
    if(!targetHistogramAvailable) return;
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;
    //CODE_START

    cv::matchHistogram(icMain, targetHistogramImage);

    //CODE_END
    ImageForm*  q_pForm = new ImageForm(icMain, "Hitgoram matching", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();
    UpdateUI();
}

void MainFrame::on_pushButtonSaltPepper_clicked()
{
    //포커스 된 ImageForm으로부터 영상을 가져옴
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    icMain = cv::SaltPepperNoise(_q_pFormFocused->ImageColor(), ui->spinSaltPepper->text().toDouble());
    noisedImage = icMain;

    ImageForm*  q_pForm = new ImageForm(icMain, "salt and pepper noise", this);

    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}

void MainFrame::on_pushButtonGaussianNoise_clicked()
{
    KImageColor   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageColor().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageColor();
    else
        return;

    icMain = cv::GaussianNoise(_q_pFormFocused->ImageColor(), ui->spinGaussianNoise->text().toDouble());
    noisedImage = icMain;

    ImageForm*  q_pForm = new ImageForm(icMain, "gaussian noise", this);

    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}

void MainFrame::on_pushButtonMedianFilter_clicked()
{
    KImageColor   icMain;
    icMain = cv::Median(noisedImage, ui->spinBoxMedian->text().toInt());


    ImageForm*  q_pForm = new ImageForm(icMain, "median filter", this);

    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}

void MainFrame::on_pushButtonGaussianFilter_clicked()
{
    KImageColor   icMain;
    icMain = cv::GaussianFiltering(noisedImage,  ui->spinBoxGaussianFilter->text().toDouble());


    ImageForm*  q_pForm = new ImageForm(icMain, "gaussian filter", this);

    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}

void MainFrame::on_pushButton_3_clicked()
{
    KImageColor   icMain;
    icMain = cv::boxFilter(noisedImage, ui->spinBoxBoxFilter->text().toInt());


    ImageForm*  q_pForm = new ImageForm(icMain, "box filter", this);

    _plpImageForm->Add(q_pForm);
    q_pForm->show();

    UpdateUI();
}

void MainFrame::on_pushButtonCanny_clicked()
{
    ImageForm*  q_pForm_result;

    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
    {
        KImageGray icImage;
        double sigma = ui->spinBoxCannySigma->text().toDouble();
        double low  = ui->spinBoxCannyLow ->text().toDouble();
        double high = ui->spinBoxCannyHigh->text().toDouble();

        icImage = cv::CannyEdge(sigma,low,high,_q_pFormFocused->ImageGray());
        q_pForm_result =  new ImageForm(icImage, "Canny Edge", this);
    }
    else
        return;

    _plpImageForm->Add(q_pForm_result);
    q_pForm_result->show();
}

void MainFrame::on_loadTableBtn_clicked()
{
    QString file = QFileDialog::getOpenFileName(this,"table","", "Files (*.txt*)");
    qDebug()<<file;

    ifstream fileStream(file.toStdString());
    if(!fileStream.is_open()) return;


    int header;
    fileStream >> header;

    int pointN = 86;

    qDebug()<<"Loading"<<pointN<<"points in table.";

    points.clear();
    int xSum=0, ySum=0, centerX, centerY;

    for(int i=0; i<pointN; i++)
    {
        int x,y;
        fileStream >> x;
        fileStream >> y;
        xSum +=x;
        ySum +=y;
        points.push_back(KPoint(x,y));
    }

    centerX = xSum / pointN;
    centerY = ySum / pointN;

    shapeCenterX = centerX;
    shapeCenterY = centerY;

    qDebug()<<"Center :("<<centerX<<","<<centerY<<")";
    KMath   oMath;

    shapeTable.clear();
    shapeTable.resize(4);

    cv::_ShapeTableElement shapeTableElement;

    for(int i=1; i<points.size() - 2; i++)
    {
        double dTmp = oMath.Atan((float)(points[i+1]._dX - points[i-1]._dX),
                (float)(points[i+1]._dY - points[i-1]._dY));
        dTmp += 90.0;

        int nDir = ((((int)(dTmp/22.5)+1)>>1) & 0x00000003);
        double dDist = sqrt(_SQR(centerX - points[i]._dX) + _SQR(centerY - points[i]._dY));
        double dAng = atan2(points[i]._dY - centerY,
                            points[i]._dX - centerX);

        shapeTableElement.distance  = dDist;
        shapeTableElement.angle   = dAng;

        shapeTable[nDir].push_back(shapeTableElement);
    }

    qDebug()<<"Load completed";

    ui->tableReadyLbl->setStyleSheet("background-color: rgb(38, 212, 113);");
    ui->tableReadyLbl->setText("OK");
    ui->generalizedHoughButton->setEnabled(true);
//    for(int i = 0; i<4; i++)
//    {
//        qDebug()<<"idx :"<<i;
//        for(int j=0; j<shapeTable[i].size(); j++)
//        {
//            qDebug()<<shapeTable[i][j].angle<<shapeTable[i][j].distance;
//        }
//    }
}

void MainFrame::on_generalizedHoughButton_clicked()
{
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageGray();
    else
        return;
    //CODE_START

    KImageColor result;

    result = cv::circleHough(icMain, 30,50,60);
    cv::GeneralizedHoughResult r = cv::generalizedHough(icMain, shapeTable);
    //icMain.GrayToRGB(result);
    cv::drawShape(result, icMain, points, shapeCenterX, shapeCenterY, r);


    //CODE_END
    ImageForm*  q_pForm = new ImageForm(result, "Hough", this);
    _plpImageForm->Add(q_pForm);
    q_pForm->show();
    UpdateUI();
}

void MainFrame::on_siftBtn_clicked()
{

    vector<vector<KImageDouble>> scales1;
    vector<vector<KImageDouble>> dogs1;
    vector<vector<KImageColor>> keypointImage1;
    cv::SiftDB db1 = cv::generateSiftDb(sift1, 6, 4, scales1, dogs1, keypointImage1);
    vector<vector<KImageDouble>> scales2;
    vector<vector<KImageDouble>> dogs2;
    vector<vector<KImageColor>> keypointImage2;
    cv::SiftDB db2 = cv::generateSiftDb(sift2, 6, 4, scales2, dogs2, keypointImage2);

    cv::SiftDB intersection = db1.compare(db2, 10.0);

    KImageColor matchImage1 = sift1.GrayToRGB();
    KImageColor matchImage2 = sift2.GrayToRGB();

    for(int i=0; i<intersection.size(); i++)
    {
        //qDebug()<<"point :"<<intersection[i].x<<intersection[i].y;
        int r,g,b;
        r = rand()/100+125;
        g = rand()/100+125;
        b = rand()/100+125;

        matchImage1[db1[i].x][db1[i].y].r = r;
        matchImage1[db1[i].x][db1[i].y].g = g;
        matchImage1[db1[i].x][db1[i].y].b = b;
        matchImage1[db1[i].x-1][db1[i].y].r = r;
        matchImage1[db1[i].x-1][db1[i].y].g = g;
        matchImage1[db1[i].x-1][db1[i].y].b = b;
        matchImage1[db1[i].x+1][db1[i].y].r = r;
        matchImage1[db1[i].x+1][db1[i].y].g = g;
        matchImage1[db1[i].x+1][db1[i].y].b = b;
        matchImage1[db1[i].x][db1[i].y+1].r = r;
        matchImage1[db1[i].x][db1[i].y+1].g = g;
        matchImage1[db1[i].x][db1[i].y+1].b = b;
        matchImage1[db1[i].x][db1[i].y-1].r = r;
        matchImage1[db1[i].x][db1[i].y-1].g = g;
        matchImage1[db1[i].x][db1[i].y-1].b = b;

        if(intersection[i].x != -1)
        {
            matchImage2[intersection[i].x][intersection[i].y].r = r;
            matchImage2[intersection[i].x][intersection[i].y].g = g;
            matchImage2[intersection[i].x][intersection[i].y].b = b;
            matchImage2[intersection[i].x-1][intersection[i].y].r = r;
            matchImage2[intersection[i].x-1][intersection[i].y].g = g;
            matchImage2[intersection[i].x-1][intersection[i].y].b = b;
            matchImage2[intersection[i].x+1][intersection[i].y].r = r;
            matchImage2[intersection[i].x+1][intersection[i].y].g = g;
            matchImage2[intersection[i].x+1][intersection[i].y].b = b;
            matchImage2[intersection[i].x][intersection[i].y-1].r = r;
            matchImage2[intersection[i].x][intersection[i].y-1].g = g;
            matchImage2[intersection[i].x][intersection[i].y-1].b = b;
            matchImage2[intersection[i].x][intersection[i].y+1].r = r;
            matchImage2[intersection[i].x][intersection[i].y+1].g = g;
            matchImage2[intersection[i].x][intersection[i].y+1].b = b;
        }
    }

    qDebug()<<"0";
    qDebug()<<"Intersecting keypoints :"<<intersection.size();
    for(int i=0; i<scales1.size(); i++)
    {
        for(int j=0; j<scales1[i].size(); j++)
        {
            //ImageForm*  q_pForm = new ImageForm(cv::doubleImageToGray(scales1[i][j], 0,255), "Scale "+QString::number(i)+"/"+QString::number(j), this);
            //_plpImageForm->Add(q_pForm);
            //q_pForm->show();
        }

        for(int j=0; j<dogs1[i].size(); j++)
        {
            ImageForm*  q_pForm = new ImageForm(cv::doubleImageToGray(dogs1[i][j], -255,255), "Dog "+QString::number(i)+"/"+QString::number(j), this);
            _plpImageForm->Add(q_pForm);
            q_pForm->show();
        }

        for(int j=0; j<keypointImage1[i].size(); j++)
        {
            ImageForm*  q_pForm = new ImageForm(keypointImage1[i][j], "Keypoints "+QString::number(i)+"/"+QString::number(j), this);
            _plpImageForm->Add(q_pForm);
            q_pForm->show();
        }
    }

    ImageForm*  q_pForm1 = new ImageForm(matchImage1, "match 1", this);
    _plpImageForm->Add(q_pForm1);
    q_pForm1->show();

    ImageForm*  q_pForm2 = new ImageForm(matchImage2, "match 2", this);
    _plpImageForm->Add(q_pForm2);
    q_pForm2->show();
}

void MainFrame::on_sift1Btn_clicked()
{
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageGray();
    else
        return;
    sift1 = icMain;
}

void MainFrame::on_sift2Btn_clicked()
{
    KImageGray   icMain;
    if(_q_pFormFocused != 0 && _q_pFormFocused->ImageGray().Address() &&  _q_pFormFocused->ID() == "OPEN")
        icMain = _q_pFormFocused->ImageGray();
    else
        return;
    sift2 = icMain;
}

void MainFrame::on_pushButton_4_clicked()
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
