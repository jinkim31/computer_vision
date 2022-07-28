#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QDialog>
#include "kfc.h"
#include "cv.h"
#include "fstream"

namespace Ui {
class MainFrame;

}

class ImageForm;
class KVoronoiDgm;
class KPotentialField;

class MainFrame : public QDialog
{
    Q_OBJECT

private:
    Ui::MainFrame *ui;

    KPtrList<ImageForm*>*   _plpImageForm;
    ImageForm*              _q_pFormFocused;

    KImageColor targetHistogramImage;
    bool targetHistogramAvailable;

    KImageColor noisedImage;

    vector<vector<cv::_ShapeTableElement>> shapeTable;
    vector<KPoint> points;
    int shapeCenterX, shapeCenterY;

    KImageGray sift1, sift2;

    std::string OPF_Path;

public:
    explicit MainFrame(QWidget *parent = 0);
    ~MainFrame();

    void            ImageFormFocused(ImageForm* q_pImageForm)
                    {   _q_pFormFocused  = q_pImageForm;   //활성화된 창의 포인터를 저장함
                        UpdateUI();                        //UI 활성화 갱신
                    }
    void            UpdateUI();
    void            CloseImageForm(ImageForm* pForm);

public:
    void            OnMousePos(const int& nX, const int& nY, ImageForm* q_pForm);

private slots:
    void on_buttonOpen_clicked();
    void on_buttonDeleteContents_clicked();    
    void on_buttonSepiaTone_clicked();
    void on_buttonShowList_clicked();

    void on_otsuButton_clicked();

    void on_erodeButton_clicked();

    void on_dilateButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_setTargetHisoButton_clicked();

    void on_matchHistogramButton_clicked();

    void on_pushButtonSaltPepper_clicked();

    void on_pushButtonGaussianNoise_clicked();

    void on_pushButtonMedianFilter_clicked();

    void on_pushButtonGaussianFilter_clicked();

    void on_pushButton_3_clicked();

    void on_pushButtonCanny_clicked();

    void on_loadTableBtn_clicked();

    void on_generalizedHoughButton_clicked();

    void on_siftBtn_clicked();

    void on_sift1Btn_clicked();

    void on_sift2Btn_clicked();

    void on_pushButton_4_clicked();

protected:
    void closeEvent(QCloseEvent* event);
};

#endif // MAINFRAME_H
