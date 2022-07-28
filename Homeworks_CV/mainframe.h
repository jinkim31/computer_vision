#ifndef MAINFRAME_H
#define MAINFRAME_H

#include <QDialog>
#include "kfc.h"
#include "k_vision.h"
#define sign( x ) ((x) > 0 ? 1 : ((x) == 0 ? 0: (-1)))

namespace Ui {
class MainFrame;

}

class ImageForm;
class KVoronoiDgm;
class KPotentialField;

typedef class OPTICAL_FLOW
{
    void _computeGradX(KImageGray curImage, KImageDouble &I_x);
    void _computeGradY(KImageGray curImage, KImageDouble &I_y);
    void _computeGradT(KImageGray preImage, KImageGray curImage, KImageDouble &I_t);
    void _makeWeightedMask(KMatrix &weightedMask, const int maskSize);
public:
    void runOpticalFlow(KImageGray preImage, KImageGray curImage, KImageColor &output);
}OPTICALFLOW;

void drawLine(KImageColor& input, int x0, int y0, int x1, int y1);
void putPixel(KImageColor& input, int x,  int y, int R = 0, int G = 255, int B = 0);


class MainFrame : public QDialog
{
    Q_OBJECT

private:
    Ui::MainFrame *ui;

    KPtrList<ImageForm*>*   _plpImageForm;
    ImageForm*              _q_pFormFocused;

    KImageColor mHMSrcImg;
    KImageColor mHMRefImg;
//    KImageGray mNoise;
    KImageColor mNoise;

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
    void            labeling_8_neighbor(KImageGray &input, KImageGray &output, KPOINT &nowPoint, const int &index);

    std::string OPF_Path;
private slots:
    void on_buttonOpen_clicked();

    void on_buttonDeleteContents_clicked();

    void on_buttonSepiaTone_clicked();

    void on_buttonShowList_clicked();

    void on_pushButtonLCT_clicked();

    void on_pushButtonOtsu_clicked();

    void on_tabWidget_currentChanged(int index);

    void on_pushButtonHE_clicked();

    void on_pushButtonME_clicked();

    void on_pushButtonMESrc_clicked();

    void on_pushButtonMERef_clicked();

    void on_pushButtonSaltPepper_clicked();

    void on_pushButtonMedianFilter_clicked();

    void on_pushButtonGaussianNoise_clicked();

    void on_pushButtonGaussianFilter_clicked();

    void on_pushButtonCanny_clicked();

    void on_pushButtonHT_clicked();

    void on_pushButton_optical_flow_clicked();

protected:
    void closeEvent(QCloseEvent* event);
};

#endif // MAINFRAME_H
