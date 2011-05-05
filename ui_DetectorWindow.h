/********************************************************************************
** Form generated from reading UI file 'DetectorWindow.ui'
**
** Created: Tue May 3 14:16:33 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DETECTORWINDOW_H
#define UI_DETECTORWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <ntk/gui/image_widget.h>

QT_BEGIN_NAMESPACE

class Ui_DetectorWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_2;
    QLabel *minThresholdLabel;
    QSlider *minThresholdSlider;
    QLabel *maxThresholdLabel;
    QSlider *maxThresholdSlider;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout;
    ntk::ImageWidget *maskImage;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *DetectorWindow)
    {
        if (DetectorWindow->objectName().isEmpty())
            DetectorWindow->setObjectName(QString::fromUtf8("DetectorWindow"));
        DetectorWindow->resize(800, 600);
        centralwidget = new QWidget(DetectorWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame);
        horizontalLayout_2->setContentsMargins(4, 4, 4, 4);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        minThresholdLabel = new QLabel(frame);
        minThresholdLabel->setObjectName(QString::fromUtf8("minThresholdLabel"));

        horizontalLayout_2->addWidget(minThresholdLabel);

        minThresholdSlider = new QSlider(frame);
        minThresholdSlider->setObjectName(QString::fromUtf8("minThresholdSlider"));
        minThresholdSlider->setMaximum(1000);
        minThresholdSlider->setValue(100);
        minThresholdSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(minThresholdSlider);

        maxThresholdLabel = new QLabel(frame);
        maxThresholdLabel->setObjectName(QString::fromUtf8("maxThresholdLabel"));
        maxThresholdLabel->setFrameShape(QFrame::NoFrame);

        horizontalLayout_2->addWidget(maxThresholdLabel);

        maxThresholdSlider = new QSlider(frame);
        maxThresholdSlider->setObjectName(QString::fromUtf8("maxThresholdSlider"));
        maxThresholdSlider->setMaximum(1000);
        maxThresholdSlider->setValue(200);
        maxThresholdSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(maxThresholdSlider);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame_2);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        maskImage = new ntk::ImageWidget(frame_2);
        maskImage->setObjectName(QString::fromUtf8("maskImage"));

        horizontalLayout->addWidget(maskImage);


        verticalLayout->addWidget(frame_2);

        DetectorWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(DetectorWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 19));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        DetectorWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(DetectorWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        DetectorWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());

        retranslateUi(DetectorWindow);

        QMetaObject::connectSlotsByName(DetectorWindow);
    } // setupUi

    void retranslateUi(QMainWindow *DetectorWindow)
    {
        DetectorWindow->setWindowTitle(QApplication::translate("DetectorWindow", "Object Detector", 0, QApplication::UnicodeUTF8));
        minThresholdLabel->setText(QApplication::translate("DetectorWindow", "0 m", 0, QApplication::UnicodeUTF8));
        maxThresholdLabel->setText(QApplication::translate("DetectorWindow", "0 m", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("DetectorWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class DetectorWindow: public Ui_DetectorWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DETECTORWINDOW_H
