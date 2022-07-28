/********************************************************************************
** Form generated from reading UI file 'mainframe.ui'
**
** Created by: Qt User Interface Compiler version 6.0.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFRAME_H
#define UI_MAINFRAME_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainFrame
{
public:
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_3;
    QToolButton *buttonOpen;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QToolButton *buttonDeleteContents;
    QSpacerItem *horizontalSpacer;
    QToolButton *buttonShowList;
    QHBoxLayout *horizontalLayout;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QLabel *label_5;
    QSpinBox *spinHue;
    QLabel *label_6;
    QDoubleSpinBox *spinSaturation;
    QPushButton *buttonSepiaTone;
    QWidget *tab_3;
    QPushButton *otsuButton;
    QComboBox *mophologyComboBox;
    QPushButton *erodeButton;
    QPushButton *dilateButton;
    QLabel *label;
    QPushButton *pushButton;
    QWidget *tab_4;
    QPushButton *pushButton_2;
    QPushButton *setTargetHisoButton;
    QPushButton *matchHistogramButton;
    QLabel *targetHistogramLabel;
    QWidget *tab;
    QLabel *label_4;
    QSpinBox *spinBoxMedian;
    QPushButton *pushButtonSaltPepper;
    QDoubleSpinBox *spinSaltPepper;
    QPushButton *pushButtonMedianFilter;
    QLabel *label_7;
    QLabel *label_8;
    QPushButton *pushButtonGaussianFilter;
    QDoubleSpinBox *spinBoxGaussianFilter;
    QPushButton *pushButtonGaussianNoise;
    QLabel *label_3;
    QDoubleSpinBox *spinGaussianNoise;
    QPushButton *pushButton_3;
    QLabel *label_9;
    QSpinBox *spinBoxBoxFilter;
    QWidget *tab_5;
    QPushButton *pushButtonCanny;
    QSpinBox *spinBoxCannyHigh;
    QSpinBox *spinBoxCannyLow;
    QDoubleSpinBox *spinBoxCannySigma;
    QLabel *label_2;
    QLabel *label_10;
    QLabel *label_11;
    QWidget *cv6;
    QPushButton *generalizedHoughButton;
    QPushButton *loadTableBtn;
    QLabel *tableReadyLbl;
    QWidget *tab_6;
    QPushButton *siftBtn;
    QPushButton *sift1Btn;
    QPushButton *sift2Btn;
    QWidget *tab_7;
    QPushButton *pushButton_4;
    QListWidget *listWidget;

    void setupUi(QDialog *MainFrame)
    {
        if (MainFrame->objectName().isEmpty())
            MainFrame->setObjectName(QString::fromUtf8("MainFrame"));
        MainFrame->resize(622, 461);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainFrame->sizePolicy().hasHeightForWidth());
        MainFrame->setSizePolicy(sizePolicy);
        MainFrame->setMinimumSize(QSize(0, 461));
        MainFrame->setModal(false);
        verticalLayout = new QVBoxLayout(MainFrame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(MainFrame);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy1);
        frame->setMinimumSize(QSize(0, 41));
        frame->setMaximumSize(QSize(16777215, 41));
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_3 = new QHBoxLayout(frame);
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        buttonOpen = new QToolButton(frame);
        buttonOpen->setObjectName(QString::fromUtf8("buttonOpen"));
        buttonOpen->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(buttonOpen->sizePolicy().hasHeightForWidth());
        buttonOpen->setSizePolicy(sizePolicy2);
        buttonOpen->setMinimumSize(QSize(41, 41));
        buttonOpen->setMaximumSize(QSize(41, 41));
        buttonOpen->setLayoutDirection(Qt::LeftToRight);
        buttonOpen->setAutoFillBackground(false);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/open.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonOpen->setIcon(icon);
        buttonOpen->setIconSize(QSize(41, 41));
        buttonOpen->setCheckable(false);
        buttonOpen->setAutoRepeat(false);
        buttonOpen->setAutoExclusive(false);
        buttonOpen->setPopupMode(QToolButton::DelayedPopup);
        buttonOpen->setToolButtonStyle(Qt::ToolButtonIconOnly);
        buttonOpen->setAutoRaise(false);

        horizontalLayout_3->addWidget(buttonOpen);

        toolButton_2 = new QToolButton(frame);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        sizePolicy2.setHeightForWidth(toolButton_2->sizePolicy().hasHeightForWidth());
        toolButton_2->setSizePolicy(sizePolicy2);
        toolButton_2->setMinimumSize(QSize(41, 41));
        toolButton_2->setMaximumSize(QSize(41, 41));

        horizontalLayout_3->addWidget(toolButton_2);

        toolButton_3 = new QToolButton(frame);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        sizePolicy2.setHeightForWidth(toolButton_3->sizePolicy().hasHeightForWidth());
        toolButton_3->setSizePolicy(sizePolicy2);
        toolButton_3->setMinimumSize(QSize(41, 41));
        toolButton_3->setMaximumSize(QSize(41, 41));

        horizontalLayout_3->addWidget(toolButton_3);

        buttonDeleteContents = new QToolButton(frame);
        buttonDeleteContents->setObjectName(QString::fromUtf8("buttonDeleteContents"));
        sizePolicy2.setHeightForWidth(buttonDeleteContents->sizePolicy().hasHeightForWidth());
        buttonDeleteContents->setSizePolicy(sizePolicy2);
        buttonDeleteContents->setMinimumSize(QSize(41, 41));
        buttonDeleteContents->setMaximumSize(QSize(41, 41));
        buttonDeleteContents->setAutoFillBackground(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/1-21.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDeleteContents->setIcon(icon1);
        buttonDeleteContents->setIconSize(QSize(41, 41));

        horizontalLayout_3->addWidget(buttonDeleteContents);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        buttonShowList = new QToolButton(frame);
        buttonShowList->setObjectName(QString::fromUtf8("buttonShowList"));
        sizePolicy2.setHeightForWidth(buttonShowList->sizePolicy().hasHeightForWidth());
        buttonShowList->setSizePolicy(sizePolicy2);
        buttonShowList->setMinimumSize(QSize(41, 41));
        buttonShowList->setMaximumSize(QSize(41, 41));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/2-3.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonShowList->setIcon(icon2);
        buttonShowList->setIconSize(QSize(82, 41));

        horizontalLayout_3->addWidget(buttonShowList);


        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, -1, -1, -1);
        tabWidget = new QTabWidget(MainFrame);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy3);
        tabWidget->setMinimumSize(QSize(299, 394));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        palette.setBrush(QPalette::Active, QPalette::Window, brush);
        QBrush brush1(QColor(255, 85, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::NoRole, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush);
        palette.setBrush(QPalette::Inactive, QPalette::NoRole, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush);
        palette.setBrush(QPalette::Disabled, QPalette::NoRole, brush1);
        tabWidget->setPalette(palette);
        tabWidget->setCursor(QCursor(Qt::ArrowCursor));
        tabWidget->setAutoFillBackground(false);
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(31, 31));
        tabWidget->setElideMode(Qt::ElideMiddle);
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(40, 83, 31, 16));
        spinHue = new QSpinBox(tab_2);
        spinHue->setObjectName(QString::fromUtf8("spinHue"));
        spinHue->setGeometry(QRect(65, 80, 61, 22));
        spinHue->setAlignment(Qt::AlignCenter);
        spinHue->setMaximum(360);
        spinHue->setSingleStep(20);
        spinHue->setValue(250);
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(140, 83, 31, 16));
        spinSaturation = new QDoubleSpinBox(tab_2);
        spinSaturation->setObjectName(QString::fromUtf8("spinSaturation"));
        spinSaturation->setGeometry(QRect(163, 80, 62, 22));
        spinSaturation->setAlignment(Qt::AlignCenter);
        spinSaturation->setMaximum(1.000000000000000);
        spinSaturation->setSingleStep(0.100000000000000);
        spinSaturation->setValue(0.300000000000000);
        buttonSepiaTone = new QPushButton(tab_2);
        buttonSepiaTone->setObjectName(QString::fromUtf8("buttonSepiaTone"));
        buttonSepiaTone->setGeometry(QRect(30, 30, 201, 41));
        buttonSepiaTone->setAutoFillBackground(false);
        buttonSepiaTone->setIconSize(QSize(41, 41));
        buttonSepiaTone->setCheckable(false);
        buttonSepiaTone->setAutoRepeat(false);
        buttonSepiaTone->setAutoExclusive(false);
        buttonSepiaTone->setAutoDefault(true);
        buttonSepiaTone->setFlat(false);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        otsuButton = new QPushButton(tab_3);
        otsuButton->setObjectName(QString::fromUtf8("otsuButton"));
        otsuButton->setGeometry(QRect(30, 30, 231, 21));
        mophologyComboBox = new QComboBox(tab_3);
        mophologyComboBox->addItem(QString());
        mophologyComboBox->addItem(QString());
        mophologyComboBox->setObjectName(QString::fromUtf8("mophologyComboBox"));
        mophologyComboBox->setGeometry(QRect(80, 110, 181, 22));
        erodeButton = new QPushButton(tab_3);
        erodeButton->setObjectName(QString::fromUtf8("erodeButton"));
        erodeButton->setGeometry(QRect(30, 140, 231, 23));
        dilateButton = new QPushButton(tab_3);
        dilateButton->setObjectName(QString::fromUtf8("dilateButton"));
        dilateButton->setGeometry(QRect(30, 170, 231, 23));
        label = new QLabel(tab_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 110, 41, 16));
        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(30, 60, 231, 21));
        tabWidget->addTab(tab_3, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QString::fromUtf8("tab_4"));
        pushButton_2 = new QPushButton(tab_4);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 20, 261, 21));
        setTargetHisoButton = new QPushButton(tab_4);
        setTargetHisoButton->setObjectName(QString::fromUtf8("setTargetHisoButton"));
        setTargetHisoButton->setGeometry(QRect(10, 90, 171, 23));
        matchHistogramButton = new QPushButton(tab_4);
        matchHistogramButton->setObjectName(QString::fromUtf8("matchHistogramButton"));
        matchHistogramButton->setEnabled(false);
        matchHistogramButton->setGeometry(QRect(10, 120, 261, 23));
        targetHistogramLabel = new QLabel(tab_4);
        targetHistogramLabel->setObjectName(QString::fromUtf8("targetHistogramLabel"));
        targetHistogramLabel->setGeometry(QRect(190, 90, 81, 20));
        targetHistogramLabel->setStyleSheet(QString::fromUtf8("background-color: rgb(221, 69, 69);"));
        targetHistogramLabel->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(tab_4, QString());
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        label_4 = new QLabel(tab);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(150, 50, 81, 21));
        label_4->setAlignment(Qt::AlignCenter);
        spinBoxMedian = new QSpinBox(tab);
        spinBoxMedian->setObjectName(QString::fromUtf8("spinBoxMedian"));
        spinBoxMedian->setGeometry(QRect(230, 130, 61, 21));
        spinBoxMedian->setMinimum(1);
        spinBoxMedian->setMaximum(9);
        spinBoxMedian->setSingleStep(2);
        spinBoxMedian->setValue(3);
        pushButtonSaltPepper = new QPushButton(tab);
        pushButtonSaltPepper->setObjectName(QString::fromUtf8("pushButtonSaltPepper"));
        pushButtonSaltPepper->setGeometry(QRect(10, 20, 131, 21));
        spinSaltPepper = new QDoubleSpinBox(tab);
        spinSaltPepper->setObjectName(QString::fromUtf8("spinSaltPepper"));
        spinSaltPepper->setGeometry(QRect(230, 20, 61, 21));
        spinSaltPepper->setAlignment(Qt::AlignCenter);
        spinSaltPepper->setDecimals(3);
        spinSaltPepper->setMaximum(1.000000000000000);
        spinSaltPepper->setSingleStep(0.005000000000000);
        spinSaltPepper->setValue(0.010000000000000);
        pushButtonMedianFilter = new QPushButton(tab);
        pushButtonMedianFilter->setObjectName(QString::fromUtf8("pushButtonMedianFilter"));
        pushButtonMedianFilter->setGeometry(QRect(10, 130, 131, 21));
        label_7 = new QLabel(tab);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(150, 160, 81, 21));
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(tab);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(150, 130, 81, 21));
        label_8->setAlignment(Qt::AlignCenter);
        pushButtonGaussianFilter = new QPushButton(tab);
        pushButtonGaussianFilter->setObjectName(QString::fromUtf8("pushButtonGaussianFilter"));
        pushButtonGaussianFilter->setGeometry(QRect(10, 160, 131, 21));
        spinBoxGaussianFilter = new QDoubleSpinBox(tab);
        spinBoxGaussianFilter->setObjectName(QString::fromUtf8("spinBoxGaussianFilter"));
        spinBoxGaussianFilter->setGeometry(QRect(230, 160, 61, 21));
        spinBoxGaussianFilter->setAlignment(Qt::AlignCenter);
        spinBoxGaussianFilter->setDecimals(2);
        spinBoxGaussianFilter->setMaximum(10.000000000000000);
        spinBoxGaussianFilter->setSingleStep(0.500000000000000);
        spinBoxGaussianFilter->setValue(1.000000000000000);
        pushButtonGaussianNoise = new QPushButton(tab);
        pushButtonGaussianNoise->setObjectName(QString::fromUtf8("pushButtonGaussianNoise"));
        pushButtonGaussianNoise->setGeometry(QRect(10, 50, 131, 21));
        label_3 = new QLabel(tab);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(150, 20, 81, 21));
        label_3->setAlignment(Qt::AlignCenter);
        spinGaussianNoise = new QDoubleSpinBox(tab);
        spinGaussianNoise->setObjectName(QString::fromUtf8("spinGaussianNoise"));
        spinGaussianNoise->setGeometry(QRect(230, 50, 61, 21));
        spinGaussianNoise->setAlignment(Qt::AlignCenter);
        spinGaussianNoise->setDecimals(0);
        spinGaussianNoise->setMaximum(500.000000000000000);
        spinGaussianNoise->setSingleStep(10.000000000000000);
        spinGaussianNoise->setValue(300.000000000000000);
        pushButton_3 = new QPushButton(tab);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(10, 100, 131, 23));
        label_9 = new QLabel(tab);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(150, 100, 81, 21));
        label_9->setAlignment(Qt::AlignCenter);
        spinBoxBoxFilter = new QSpinBox(tab);
        spinBoxBoxFilter->setObjectName(QString::fromUtf8("spinBoxBoxFilter"));
        spinBoxBoxFilter->setGeometry(QRect(230, 100, 61, 21));
        spinBoxBoxFilter->setMinimum(1);
        spinBoxBoxFilter->setMaximum(9);
        spinBoxBoxFilter->setSingleStep(2);
        spinBoxBoxFilter->setValue(3);
        tabWidget->addTab(tab, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QString::fromUtf8("tab_5"));
        pushButtonCanny = new QPushButton(tab_5);
        pushButtonCanny->setObjectName(QString::fromUtf8("pushButtonCanny"));
        pushButtonCanny->setGeometry(QRect(20, 140, 261, 21));
        spinBoxCannyHigh = new QSpinBox(tab_5);
        spinBoxCannyHigh->setObjectName(QString::fromUtf8("spinBoxCannyHigh"));
        spinBoxCannyHigh->setGeometry(QRect(170, 100, 101, 20));
        spinBoxCannyHigh->setAlignment(Qt::AlignCenter);
        spinBoxCannyHigh->setMaximum(100);
        spinBoxCannyHigh->setValue(20);
        spinBoxCannyLow = new QSpinBox(tab_5);
        spinBoxCannyLow->setObjectName(QString::fromUtf8("spinBoxCannyLow"));
        spinBoxCannyLow->setGeometry(QRect(170, 70, 101, 20));
        spinBoxCannyLow->setAlignment(Qt::AlignCenter);
        spinBoxCannyLow->setMaximum(100);
        spinBoxCannyLow->setValue(10);
        spinBoxCannySigma = new QDoubleSpinBox(tab_5);
        spinBoxCannySigma->setObjectName(QString::fromUtf8("spinBoxCannySigma"));
        spinBoxCannySigma->setGeometry(QRect(170, 40, 101, 21));
        spinBoxCannySigma->setAlignment(Qt::AlignCenter);
        spinBoxCannySigma->setDecimals(2);
        spinBoxCannySigma->setMaximum(10.000000000000000);
        spinBoxCannySigma->setSingleStep(0.500000000000000);
        spinBoxCannySigma->setValue(1.500000000000000);
        label_2 = new QLabel(tab_5);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 40, 56, 16));
        label_10 = new QLabel(tab_5);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(20, 70, 111, 16));
        label_11 = new QLabel(tab_5);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(20, 110, 111, 16));
        tabWidget->addTab(tab_5, QString());
        cv6 = new QWidget();
        cv6->setObjectName(QString::fromUtf8("cv6"));
        generalizedHoughButton = new QPushButton(cv6);
        generalizedHoughButton->setObjectName(QString::fromUtf8("generalizedHoughButton"));
        generalizedHoughButton->setEnabled(false);
        generalizedHoughButton->setGeometry(QRect(10, 40, 271, 31));
        loadTableBtn = new QPushButton(cv6);
        loadTableBtn->setObjectName(QString::fromUtf8("loadTableBtn"));
        loadTableBtn->setGeometry(QRect(10, 10, 181, 23));
        tableReadyLbl = new QLabel(cv6);
        tableReadyLbl->setObjectName(QString::fromUtf8("tableReadyLbl"));
        tableReadyLbl->setGeometry(QRect(200, 10, 81, 20));
        tableReadyLbl->setStyleSheet(QString::fromUtf8("background-color: rgb(221, 69, 69);"));
        tableReadyLbl->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(cv6, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QString::fromUtf8("tab_6"));
        siftBtn = new QPushButton(tab_6);
        siftBtn->setObjectName(QString::fromUtf8("siftBtn"));
        siftBtn->setGeometry(QRect(20, 50, 251, 31));
        sift1Btn = new QPushButton(tab_6);
        sift1Btn->setObjectName(QString::fromUtf8("sift1Btn"));
        sift1Btn->setGeometry(QRect(20, 20, 121, 23));
        sift2Btn = new QPushButton(tab_6);
        sift2Btn->setObjectName(QString::fromUtf8("sift2Btn"));
        sift2Btn->setGeometry(QRect(150, 20, 121, 23));
        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QString::fromUtf8("tab_7"));
        pushButton_4 = new QPushButton(tab_7);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(10, 10, 261, 23));
        tabWidget->addTab(tab_7, QString());

        horizontalLayout->addWidget(tabWidget);

        listWidget = new QListWidget(MainFrame);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        QSizePolicy sizePolicy4(QSizePolicy::Ignored, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(listWidget->sizePolicy().hasHeightForWidth());
        listWidget->setSizePolicy(sizePolicy4);
        listWidget->setMinimumSize(QSize(0, 394));
        QPalette palette1;
        QBrush brush2(QColor(255, 255, 0, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush3(QColor(0, 0, 127, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush3);
        QBrush brush4(QColor(255, 255, 255, 128));
        brush4.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush4);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        QBrush brush5(QColor(255, 255, 255, 128));
        brush5.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        QBrush brush6(QColor(120, 120, 120, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush6);
        QBrush brush7(QColor(240, 240, 240, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush7);
        QBrush brush8(QColor(255, 255, 255, 128));
        brush8.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush8);
#endif
        listWidget->setPalette(palette1);
        QFont font;
        font.setFamily(QString::fromUtf8("Times New Roman"));
        font.setPointSize(10);
        listWidget->setFont(font);

        horizontalLayout->addWidget(listWidget);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MainFrame);

        tabWidget->setCurrentIndex(7);


        QMetaObject::connectSlotsByName(MainFrame);
    } // setupUi

    void retranslateUi(QDialog *MainFrame)
    {
        MainFrame->setWindowTitle(QCoreApplication::translate("MainFrame", "Homeworks", nullptr));
#if QT_CONFIG(tooltip)
        buttonOpen->setToolTip(QCoreApplication::translate("MainFrame", "open an image file", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonOpen->setText(QString());
        toolButton_2->setText(QCoreApplication::translate("MainFrame", "...", nullptr));
        toolButton_3->setText(QCoreApplication::translate("MainFrame", "...", nullptr));
#if QT_CONFIG(tooltip)
        buttonDeleteContents->setToolTip(QCoreApplication::translate("MainFrame", "close all forms", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonDeleteContents->setText(QString());
#if QT_CONFIG(tooltip)
        buttonShowList->setToolTip(QCoreApplication::translate("MainFrame", "show the list view", nullptr));
#endif // QT_CONFIG(tooltip)
        buttonShowList->setText(QString());
        label_5->setText(QCoreApplication::translate("MainFrame", "Hue", nullptr));
        label_6->setText(QCoreApplication::translate("MainFrame", "Sat.", nullptr));
        buttonSepiaTone->setText(QCoreApplication::translate("MainFrame", "Sepia Tone", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainFrame", "1 ", nullptr));
        otsuButton->setText(QCoreApplication::translate("MainFrame", "Otsu", nullptr));
        mophologyComboBox->setItemText(0, QCoreApplication::translate("MainFrame", "3", nullptr));
        mophologyComboBox->setItemText(1, QCoreApplication::translate("MainFrame", "5", nullptr));

        erodeButton->setText(QCoreApplication::translate("MainFrame", "Erode", nullptr));
        dilateButton->setText(QCoreApplication::translate("MainFrame", "Dilate", nullptr));
        label->setText(QCoreApplication::translate("MainFrame", "Kernel", nullptr));
        pushButton->setText(QCoreApplication::translate("MainFrame", "Labeling", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QCoreApplication::translate("MainFrame", "2 ", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainFrame", "HEQ", nullptr));
        setTargetHisoButton->setText(QCoreApplication::translate("MainFrame", "Set target histogram", nullptr));
        matchHistogramButton->setText(QCoreApplication::translate("MainFrame", "Match histogram", nullptr));
        targetHistogramLabel->setText(QCoreApplication::translate("MainFrame", "Not assigned", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QCoreApplication::translate("MainFrame", "3 ", nullptr));
        label_4->setText(QCoreApplication::translate("MainFrame", "<html><head/><body><p><span style=\" font-weight:600; color:#000000;\">Variance</span></p></body></html>", nullptr));
        pushButtonSaltPepper->setText(QCoreApplication::translate("MainFrame", "Salt and pepper", nullptr));
        pushButtonMedianFilter->setText(QCoreApplication::translate("MainFrame", "Median Filter", nullptr));
        label_7->setText(QCoreApplication::translate("MainFrame", "<html><head/><body><p><span style=\" font-weight:600;\">Sigma</span></p></body></html>", nullptr));
        label_8->setText(QCoreApplication::translate("MainFrame", "<html><head/><body><p><span style=\" font-weight:600;\">Kernel</span></p></body></html>", nullptr));
        pushButtonGaussianFilter->setText(QCoreApplication::translate("MainFrame", "Gaussian Filter", nullptr));
        pushButtonGaussianNoise->setText(QCoreApplication::translate("MainFrame", "Gaussian", nullptr));
        label_3->setText(QCoreApplication::translate("MainFrame", "<html><head/><body><p><span style=\" font-weight:600;\">Threshold</span></p></body></html>", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainFrame", "Box Filter", nullptr));
        label_9->setText(QCoreApplication::translate("MainFrame", "<html><head/><body><p><span style=\" font-weight:600;\">Kernel</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("MainFrame", "4 ", nullptr));
        pushButtonCanny->setText(QCoreApplication::translate("MainFrame", "Canny Edge", nullptr));
        label_2->setText(QCoreApplication::translate("MainFrame", "Sigma", nullptr));
        label_10->setText(QCoreApplication::translate("MainFrame", "Lower Threshold", nullptr));
        label_11->setText(QCoreApplication::translate("MainFrame", "Upper Threshold", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QCoreApplication::translate("MainFrame", "5", nullptr));
        generalizedHoughButton->setText(QCoreApplication::translate("MainFrame", "Generalized Hough Transform", nullptr));
        loadTableBtn->setText(QCoreApplication::translate("MainFrame", "Load table", nullptr));
        tableReadyLbl->setText(QCoreApplication::translate("MainFrame", "Not loaded", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(cv6), QCoreApplication::translate("MainFrame", "6", nullptr));
        siftBtn->setText(QCoreApplication::translate("MainFrame", "SIFT", nullptr));
        sift1Btn->setText(QCoreApplication::translate("MainFrame", "Load image 1", nullptr));
        sift2Btn->setText(QCoreApplication::translate("MainFrame", "Load image 2", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QCoreApplication::translate("MainFrame", "7", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainFrame", "optical flow", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QCoreApplication::translate("MainFrame", "8", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainFrame: public Ui_MainFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRAME_H
