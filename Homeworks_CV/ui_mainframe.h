/********************************************************************************
** Form generated from reading UI file 'mainframe.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINFRAME_H
#define UI_MAINFRAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
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
    QGroupBox *groupBox;
    QLabel *label_6;
    QSpinBox *spinHue;
    QPushButton *buttonSepiaTone;
    QDoubleSpinBox *spinSaturation;
    QLabel *label_5;
    QGroupBox *groupBox_2;
    QSpinBox *spinBoxB;
    QSpinBox *spinBoxA;
    QLabel *label_2;
    QLabel *label;
    QPushButton *pushButtonLCT;
    QWidget *tab_3;
    QPushButton *pushButtonOtsu;
    QWidget *tab;
    QGroupBox *groupBox_3;
    QDoubleSpinBox *spinSaltPepper;
    QLabel *label_3;
    QPushButton *pushButtonGaussianNoise;
    QLabel *label_4;
    QPushButton *pushButtonSaltPepper;
    QDoubleSpinBox *spinGaussianNoise;
    QGroupBox *groupBox_4;
    QLabel *label_7;
    QLabel *label_8;
    QDoubleSpinBox *spinBoxGaussianFilter;
    QPushButton *pushButtonMedianFilter;
    QSpinBox *spinBoxMedian;
    QPushButton *pushButtonGaussianFilter;
    QWidget *tab_4;
    QPushButton *pushButtonHE;
    QPushButton *pushButtonME;
    QPushButton *pushButtonMESrc;
    QPushButton *pushButtonMERef;
    QWidget *tab_5;
    QDoubleSpinBox *spinBoxCannySigma;
    QLabel *label_9;
    QSpinBox *spinBoxCannyLow;
    QLabel *label_10;
    QSpinBox *spinBoxCannyHigh;
    QLabel *label_11;
    QPushButton *pushButtonCanny;
    QLabel *label_12;
    QWidget *tab_6;
    QLabel *label_13;
    QPushButton *pushButtonHT;
    QWidget *tab_7;
    QPushButton *pushButton_optical_flow;
    QListWidget *listWidget;

    void setupUi(QDialog *MainFrame)
    {
        if (MainFrame->objectName().isEmpty())
            MainFrame->setObjectName(QStringLiteral("MainFrame"));
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
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        frame = new QFrame(MainFrame);
        frame->setObjectName(QStringLiteral("frame"));
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
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        horizontalLayout_3->setContentsMargins(0, 0, 0, 0);
        buttonOpen = new QToolButton(frame);
        buttonOpen->setObjectName(QStringLiteral("buttonOpen"));
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
        icon.addFile(QStringLiteral(":/open.png"), QSize(), QIcon::Normal, QIcon::Off);
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
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        sizePolicy2.setHeightForWidth(toolButton_2->sizePolicy().hasHeightForWidth());
        toolButton_2->setSizePolicy(sizePolicy2);
        toolButton_2->setMinimumSize(QSize(41, 41));
        toolButton_2->setMaximumSize(QSize(41, 41));

        horizontalLayout_3->addWidget(toolButton_2);

        toolButton_3 = new QToolButton(frame);
        toolButton_3->setObjectName(QStringLiteral("toolButton_3"));
        sizePolicy2.setHeightForWidth(toolButton_3->sizePolicy().hasHeightForWidth());
        toolButton_3->setSizePolicy(sizePolicy2);
        toolButton_3->setMinimumSize(QSize(41, 41));
        toolButton_3->setMaximumSize(QSize(41, 41));

        horizontalLayout_3->addWidget(toolButton_3);

        buttonDeleteContents = new QToolButton(frame);
        buttonDeleteContents->setObjectName(QStringLiteral("buttonDeleteContents"));
        sizePolicy2.setHeightForWidth(buttonDeleteContents->sizePolicy().hasHeightForWidth());
        buttonDeleteContents->setSizePolicy(sizePolicy2);
        buttonDeleteContents->setMinimumSize(QSize(41, 41));
        buttonDeleteContents->setMaximumSize(QSize(41, 41));
        buttonDeleteContents->setAutoFillBackground(false);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/1-21.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonDeleteContents->setIcon(icon1);
        buttonDeleteContents->setIconSize(QSize(41, 41));

        horizontalLayout_3->addWidget(buttonDeleteContents);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);

        buttonShowList = new QToolButton(frame);
        buttonShowList->setObjectName(QStringLiteral("buttonShowList"));
        sizePolicy2.setHeightForWidth(buttonShowList->sizePolicy().hasHeightForWidth());
        buttonShowList->setSizePolicy(sizePolicy2);
        buttonShowList->setMinimumSize(QSize(41, 41));
        buttonShowList->setMaximumSize(QSize(41, 41));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/2-3.png"), QSize(), QIcon::Normal, QIcon::Off);
        buttonShowList->setIcon(icon2);
        buttonShowList->setIconSize(QSize(82, 41));

        horizontalLayout_3->addWidget(buttonShowList);


        verticalLayout->addWidget(frame);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(2, -1, -1, -1);
        tabWidget = new QTabWidget(MainFrame);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy3);
        tabWidget->setMinimumSize(QSize(350, 394));
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
        tab_2->setObjectName(QStringLiteral("tab_2"));
        groupBox = new QGroupBox(tab_2);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(40, 180, 261, 131));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(140, 90, 31, 16));
        spinHue = new QSpinBox(groupBox);
        spinHue->setObjectName(QStringLiteral("spinHue"));
        spinHue->setGeometry(QRect(65, 87, 61, 22));
        spinHue->setAlignment(Qt::AlignCenter);
        spinHue->setMaximum(360);
        spinHue->setSingleStep(20);
        spinHue->setValue(250);
        buttonSepiaTone = new QPushButton(groupBox);
        buttonSepiaTone->setObjectName(QStringLiteral("buttonSepiaTone"));
        buttonSepiaTone->setGeometry(QRect(30, 37, 201, 41));
        buttonSepiaTone->setAutoFillBackground(false);
        buttonSepiaTone->setIconSize(QSize(41, 41));
        buttonSepiaTone->setCheckable(false);
        buttonSepiaTone->setAutoRepeat(false);
        buttonSepiaTone->setAutoExclusive(false);
        buttonSepiaTone->setAutoDefault(true);
        buttonSepiaTone->setFlat(false);
        spinSaturation = new QDoubleSpinBox(groupBox);
        spinSaturation->setObjectName(QStringLiteral("spinSaturation"));
        spinSaturation->setGeometry(QRect(163, 87, 62, 22));
        spinSaturation->setAlignment(Qt::AlignCenter);
        spinSaturation->setMaximum(1);
        spinSaturation->setSingleStep(0.1);
        spinSaturation->setValue(0.3);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(40, 90, 31, 16));
        groupBox_2 = new QGroupBox(tab_2);
        groupBox_2->setObjectName(QStringLiteral("groupBox_2"));
        groupBox_2->setGeometry(QRect(40, 20, 261, 131));
        spinBoxB = new QSpinBox(groupBox_2);
        spinBoxB->setObjectName(QStringLiteral("spinBoxB"));
        spinBoxB->setGeometry(QRect(170, 80, 51, 22));
        spinBoxB->setMaximum(255);
        spinBoxB->setSingleStep(10);
        spinBoxB->setValue(200);
        spinBoxA = new QSpinBox(groupBox_2);
        spinBoxA->setObjectName(QStringLiteral("spinBoxA"));
        spinBoxA->setGeometry(QRect(60, 80, 51, 22));
        spinBoxA->setMaximum(255);
        spinBoxA->setSingleStep(10);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(130, 80, 31, 20));
        label_2->setAlignment(Qt::AlignCenter);
        label = new QLabel(groupBox_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(23, 80, 31, 20));
        label->setAlignment(Qt::AlignCenter);
        pushButtonLCT = new QPushButton(groupBox_2);
        pushButtonLCT->setObjectName(QStringLiteral("pushButtonLCT"));
        pushButtonLCT->setGeometry(QRect(30, 20, 201, 41));
        pushButtonLCT->setAutoFillBackground(false);
        pushButtonLCT->setIconSize(QSize(41, 41));
        pushButtonLCT->setCheckable(false);
        pushButtonLCT->setAutoRepeat(false);
        pushButtonLCT->setAutoExclusive(false);
        pushButtonLCT->setAutoDefault(true);
        pushButtonLCT->setFlat(false);
        tabWidget->addTab(tab_2, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        pushButtonOtsu = new QPushButton(tab_3);
        pushButtonOtsu->setObjectName(QStringLiteral("pushButtonOtsu"));
        pushButtonOtsu->setGeometry(QRect(110, 130, 121, 81));
        tabWidget->addTab(tab_3, QString());
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        groupBox_3 = new QGroupBox(tab);
        groupBox_3->setObjectName(QStringLiteral("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 40, 291, 131));
        spinSaltPepper = new QDoubleSpinBox(groupBox_3);
        spinSaltPepper->setObjectName(QStringLiteral("spinSaltPepper"));
        spinSaltPepper->setGeometry(QRect(150, 20, 61, 41));
        spinSaltPepper->setAlignment(Qt::AlignCenter);
        spinSaltPepper->setDecimals(3);
        spinSaltPepper->setMaximum(1);
        spinSaltPepper->setSingleStep(0.005);
        spinSaltPepper->setValue(0.01);
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(210, 30, 81, 21));
        label_3->setAlignment(Qt::AlignCenter);
        pushButtonGaussianNoise = new QPushButton(groupBox_3);
        pushButtonGaussianNoise->setObjectName(QStringLiteral("pushButtonGaussianNoise"));
        pushButtonGaussianNoise->setGeometry(QRect(10, 70, 131, 41));
        label_4 = new QLabel(groupBox_3);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(210, 80, 81, 21));
        label_4->setAlignment(Qt::AlignCenter);
        pushButtonSaltPepper = new QPushButton(groupBox_3);
        pushButtonSaltPepper->setObjectName(QStringLiteral("pushButtonSaltPepper"));
        pushButtonSaltPepper->setGeometry(QRect(10, 20, 131, 41));
        spinGaussianNoise = new QDoubleSpinBox(groupBox_3);
        spinGaussianNoise->setObjectName(QStringLiteral("spinGaussianNoise"));
        spinGaussianNoise->setGeometry(QRect(150, 70, 61, 41));
        spinGaussianNoise->setAlignment(Qt::AlignCenter);
        spinGaussianNoise->setDecimals(0);
        spinGaussianNoise->setMaximum(500);
        spinGaussianNoise->setSingleStep(10);
        spinGaussianNoise->setValue(300);
        groupBox_4 = new QGroupBox(tab);
        groupBox_4->setObjectName(QStringLiteral("groupBox_4"));
        groupBox_4->setGeometry(QRect(30, 190, 281, 121));
        label_7 = new QLabel(groupBox_4);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(200, 80, 81, 21));
        label_7->setAlignment(Qt::AlignCenter);
        label_8 = new QLabel(groupBox_4);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(200, 30, 81, 21));
        label_8->setAlignment(Qt::AlignCenter);
        spinBoxGaussianFilter = new QDoubleSpinBox(groupBox_4);
        spinBoxGaussianFilter->setObjectName(QStringLiteral("spinBoxGaussianFilter"));
        spinBoxGaussianFilter->setGeometry(QRect(150, 70, 51, 41));
        spinBoxGaussianFilter->setAlignment(Qt::AlignCenter);
        spinBoxGaussianFilter->setDecimals(2);
        spinBoxGaussianFilter->setMaximum(10);
        spinBoxGaussianFilter->setSingleStep(0.5);
        spinBoxGaussianFilter->setValue(1);
        pushButtonMedianFilter = new QPushButton(groupBox_4);
        pushButtonMedianFilter->setObjectName(QStringLiteral("pushButtonMedianFilter"));
        pushButtonMedianFilter->setGeometry(QRect(10, 20, 111, 41));
        spinBoxMedian = new QSpinBox(groupBox_4);
        spinBoxMedian->setObjectName(QStringLiteral("spinBoxMedian"));
        spinBoxMedian->setGeometry(QRect(150, 20, 51, 41));
        spinBoxMedian->setMaximum(9);
        spinBoxMedian->setValue(3);
        pushButtonGaussianFilter = new QPushButton(groupBox_4);
        pushButtonGaussianFilter->setObjectName(QStringLiteral("pushButtonGaussianFilter"));
        pushButtonGaussianFilter->setGeometry(QRect(10, 70, 111, 41));
        tabWidget->addTab(tab, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        pushButtonHE = new QPushButton(tab_4);
        pushButtonHE->setObjectName(QStringLiteral("pushButtonHE"));
        pushButtonHE->setGeometry(QRect(90, 100, 161, 51));
        pushButtonME = new QPushButton(tab_4);
        pushButtonME->setObjectName(QStringLiteral("pushButtonME"));
        pushButtonME->setGeometry(QRect(90, 170, 161, 51));
        pushButtonMESrc = new QPushButton(tab_4);
        pushButtonMESrc->setObjectName(QStringLiteral("pushButtonMESrc"));
        pushButtonMESrc->setGeometry(QRect(80, 250, 75, 23));
        pushButtonMESrc->setStyleSheet(QLatin1String("background-color: rgb(221, 221, 221);\n"
""));
        pushButtonMERef = new QPushButton(tab_4);
        pushButtonMERef->setObjectName(QStringLiteral("pushButtonMERef"));
        pushButtonMERef->setGeometry(QRect(190, 250, 75, 23));
        pushButtonMERef->setStyleSheet(QStringLiteral("background-color: rgb(221, 221, 221);"));
        tabWidget->addTab(tab_4, QString());
        tab_5 = new QWidget();
        tab_5->setObjectName(QStringLiteral("tab_5"));
        spinBoxCannySigma = new QDoubleSpinBox(tab_5);
        spinBoxCannySigma->setObjectName(QStringLiteral("spinBoxCannySigma"));
        spinBoxCannySigma->setGeometry(QRect(140, 100, 111, 41));
        spinBoxCannySigma->setAlignment(Qt::AlignCenter);
        spinBoxCannySigma->setDecimals(2);
        spinBoxCannySigma->setMaximum(10);
        spinBoxCannySigma->setSingleStep(0.5);
        spinBoxCannySigma->setValue(1);
        label_9 = new QLabel(tab_5);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(50, 100, 81, 41));
        label_9->setAlignment(Qt::AlignCenter);
        spinBoxCannyLow = new QSpinBox(tab_5);
        spinBoxCannyLow->setObjectName(QStringLiteral("spinBoxCannyLow"));
        spinBoxCannyLow->setGeometry(QRect(140, 160, 111, 41));
        spinBoxCannyLow->setAlignment(Qt::AlignCenter);
        spinBoxCannyLow->setMaximum(100);
        spinBoxCannyLow->setValue(15);
        label_10 = new QLabel(tab_5);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(50, 160, 81, 41));
        label_10->setAlignment(Qt::AlignCenter);
        spinBoxCannyHigh = new QSpinBox(tab_5);
        spinBoxCannyHigh->setObjectName(QStringLiteral("spinBoxCannyHigh"));
        spinBoxCannyHigh->setGeometry(QRect(140, 210, 111, 41));
        spinBoxCannyHigh->setAlignment(Qt::AlignCenter);
        spinBoxCannyHigh->setMaximum(100);
        spinBoxCannyHigh->setValue(30);
        label_11 = new QLabel(tab_5);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(50, 210, 81, 41));
        label_11->setAlignment(Qt::AlignCenter);
        pushButtonCanny = new QPushButton(tab_5);
        pushButtonCanny->setObjectName(QStringLiteral("pushButtonCanny"));
        pushButtonCanny->setGeometry(QRect(90, 270, 151, 51));
        label_12 = new QLabel(tab_5);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setGeometry(QRect(80, 30, 201, 31));
        label_12->setFrameShape(QFrame::Box);
        label_12->setAlignment(Qt::AlignCenter);
        tabWidget->addTab(tab_5, QString());
        tab_6 = new QWidget();
        tab_6->setObjectName(QStringLiteral("tab_6"));
        label_13 = new QLabel(tab_6);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setGeometry(QRect(80, 50, 201, 31));
        label_13->setFrameShape(QFrame::Box);
        label_13->setAlignment(Qt::AlignCenter);
        pushButtonHT = new QPushButton(tab_6);
        pushButtonHT->setObjectName(QStringLiteral("pushButtonHT"));
        pushButtonHT->setGeometry(QRect(90, 150, 181, 61));
        tabWidget->addTab(tab_6, QString());
        tab_7 = new QWidget();
        tab_7->setObjectName(QStringLiteral("tab_7"));
        pushButton_optical_flow = new QPushButton(tab_7);
        pushButton_optical_flow->setObjectName(QStringLiteral("pushButton_optical_flow"));
        pushButton_optical_flow->setGeometry(QRect(80, 120, 201, 101));
        tabWidget->addTab(tab_7, QString());

        horizontalLayout->addWidget(tabWidget);

        listWidget = new QListWidget(MainFrame);
        listWidget->setObjectName(QStringLiteral("listWidget"));
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
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush3);
        QBrush brush4(QColor(120, 120, 120, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        QBrush brush5(QColor(240, 240, 240, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush5);
        listWidget->setPalette(palette1);
        QFont font;
        font.setFamily(QStringLiteral("Times New Roman"));
        font.setPointSize(10);
        listWidget->setFont(font);

        horizontalLayout->addWidget(listWidget);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(MainFrame);

        tabWidget->setCurrentIndex(6);


        QMetaObject::connectSlotsByName(MainFrame);
    } // setupUi

    void retranslateUi(QDialog *MainFrame)
    {
        MainFrame->setWindowTitle(QApplication::translate("MainFrame", "Homeworks", 0));
#ifndef QT_NO_TOOLTIP
        buttonOpen->setToolTip(QApplication::translate("MainFrame", "open an image file", 0));
#endif // QT_NO_TOOLTIP
        buttonOpen->setText(QString());
        toolButton_2->setText(QApplication::translate("MainFrame", "...", 0));
        toolButton_3->setText(QApplication::translate("MainFrame", "...", 0));
#ifndef QT_NO_TOOLTIP
        buttonDeleteContents->setToolTip(QApplication::translate("MainFrame", "close all forms", 0));
#endif // QT_NO_TOOLTIP
        buttonDeleteContents->setText(QString());
#ifndef QT_NO_TOOLTIP
        buttonShowList->setToolTip(QApplication::translate("MainFrame", "show the list view", 0));
#endif // QT_NO_TOOLTIP
        buttonShowList->setText(QString());
        groupBox->setTitle(QApplication::translate("MainFrame", "HSV", 0));
        label_6->setText(QApplication::translate("MainFrame", "Sat.", 0));
        buttonSepiaTone->setText(QApplication::translate("MainFrame", "Sepia Tone", 0));
        label_5->setText(QApplication::translate("MainFrame", "Hue", 0));
        groupBox_2->setTitle(QApplication::translate("MainFrame", "Luminance Contrast Transform", 0));
        label_2->setText(QApplication::translate("MainFrame", "b", 0));
        label->setText(QApplication::translate("MainFrame", "a", 0));
        pushButtonLCT->setText(QApplication::translate("MainFrame", "LCT", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainFrame", "1 ", 0));
        pushButtonOtsu->setText(QApplication::translate("MainFrame", "Otsu's", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_3), QApplication::translate("MainFrame", "2 ", 0));
        groupBox_3->setTitle(QApplication::translate("MainFrame", "Noise", 0));
        label_3->setText(QApplication::translate("MainFrame", "<html><head/><body><p><span style=\" font-weight:600;\">Threshold</span></p></body></html>", 0));
        pushButtonGaussianNoise->setText(QApplication::translate("MainFrame", "Gaussian", 0));
        label_4->setText(QApplication::translate("MainFrame", "<html><head/><body><p><span style=\" font-weight:600; color:#000000;\">Variance</span></p></body></html>", 0));
        pushButtonSaltPepper->setText(QApplication::translate("MainFrame", "Salt and pepper", 0));
        groupBox_4->setTitle(QApplication::translate("MainFrame", "Filter", 0));
        label_7->setText(QApplication::translate("MainFrame", "<html><head/><body><p><span style=\" font-weight:600;\">Sigma</span></p></body></html>", 0));
        label_8->setText(QApplication::translate("MainFrame", "<html><head/><body><p><span style=\" font-weight:600;\">Kernel</span></p></body></html>", 0));
        pushButtonMedianFilter->setText(QApplication::translate("MainFrame", "Median Filter", 0));
        pushButtonGaussianFilter->setText(QApplication::translate("MainFrame", "Gaussian Filter", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainFrame", " 4 ", 0));
        pushButtonHE->setText(QApplication::translate("MainFrame", "Histogram Equalization", 0));
        pushButtonME->setText(QApplication::translate("MainFrame", "Histogram Matching", 0));
        pushButtonMESrc->setText(QApplication::translate("MainFrame", "Source", 0));
        pushButtonMERef->setText(QApplication::translate("MainFrame", "Reference", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_4), QApplication::translate("MainFrame", " 3 ", 0));
        label_9->setText(QApplication::translate("MainFrame", "<html><head/><body><p><span style=\" font-weight:600;\">Sigma</span></p></body></html>", 0));
        label_10->setText(QApplication::translate("MainFrame", "<html><head/><body><p><span style=\" font-weight:600;\">Low</span></p></body></html>", 0));
        label_11->setText(QApplication::translate("MainFrame", "<html><head/><body><p><span style=\" font-weight:600;\">High</span></p></body></html>", 0));
        pushButtonCanny->setText(QApplication::translate("MainFrame", "Canny", 0));
        label_12->setText(QApplication::translate("MainFrame", "Canny Edge", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_5), QApplication::translate("MainFrame", "5", 0));
        label_13->setText(QApplication::translate("MainFrame", "Hough Transform", 0));
        pushButtonHT->setText(QApplication::translate("MainFrame", "Circle Hough Transform", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_6), QApplication::translate("MainFrame", "6", 0));
        pushButton_optical_flow->setText(QApplication::translate("MainFrame", "Optical Flow", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_7), QApplication::translate("MainFrame", "7", 0));
    } // retranslateUi

};

namespace Ui {
    class MainFrame: public Ui_MainFrame {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINFRAME_H
