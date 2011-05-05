/********************************************************************************
** Form generated from reading UI file 'FiltersWindow.ui'
**
** Created: Tue May 3 14:16:33 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FILTERSWINDOW_H
#define UI_FILTERSWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FiltersWindow
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *depthThresholdCheckBox;
    QFrame *line;
    QLabel *minDepthLabel;
    QSlider *minDepthSlider;
    QLabel *maxDepthLabel;
    QSlider *maxDepthSlider;
    QCheckBox *edgesCheckBox;
    QCheckBox *medianCheckBox;
    QCheckBox *normalsCheckBox;
    QCheckBox *unstableCheckBox;
    QCheckBox *removeSmallStructuresBox;
    QCheckBox *fillSmallHolesCheckBox;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label;
    QSlider *kinectTiltSlider;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FiltersWindow)
    {
        if (FiltersWindow->objectName().isEmpty())
            FiltersWindow->setObjectName(QString::fromUtf8("FiltersWindow"));
        FiltersWindow->resize(361, 282);
        centralwidget = new QWidget(FiltersWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout_2 = new QHBoxLayout(centralwidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        depthThresholdCheckBox = new QCheckBox(centralwidget);
        depthThresholdCheckBox->setObjectName(QString::fromUtf8("depthThresholdCheckBox"));

        horizontalLayout_3->addWidget(depthThresholdCheckBox);

        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_3->addWidget(line);

        minDepthLabel = new QLabel(centralwidget);
        minDepthLabel->setObjectName(QString::fromUtf8("minDepthLabel"));

        horizontalLayout_3->addWidget(minDepthLabel);

        minDepthSlider = new QSlider(centralwidget);
        minDepthSlider->setObjectName(QString::fromUtf8("minDepthSlider"));
        minDepthSlider->setMaximum(700);
        minDepthSlider->setSliderPosition(30);
        minDepthSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(minDepthSlider);

        maxDepthLabel = new QLabel(centralwidget);
        maxDepthLabel->setObjectName(QString::fromUtf8("maxDepthLabel"));

        horizontalLayout_3->addWidget(maxDepthLabel);

        maxDepthSlider = new QSlider(centralwidget);
        maxDepthSlider->setObjectName(QString::fromUtf8("maxDepthSlider"));
        maxDepthSlider->setMaximum(1000);
        maxDepthSlider->setValue(400);
        maxDepthSlider->setSliderPosition(400);
        maxDepthSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(maxDepthSlider);


        verticalLayout->addLayout(horizontalLayout_3);

        edgesCheckBox = new QCheckBox(centralwidget);
        edgesCheckBox->setObjectName(QString::fromUtf8("edgesCheckBox"));

        verticalLayout->addWidget(edgesCheckBox);

        medianCheckBox = new QCheckBox(centralwidget);
        medianCheckBox->setObjectName(QString::fromUtf8("medianCheckBox"));

        verticalLayout->addWidget(medianCheckBox);

        normalsCheckBox = new QCheckBox(centralwidget);
        normalsCheckBox->setObjectName(QString::fromUtf8("normalsCheckBox"));

        verticalLayout->addWidget(normalsCheckBox);

        unstableCheckBox = new QCheckBox(centralwidget);
        unstableCheckBox->setObjectName(QString::fromUtf8("unstableCheckBox"));

        verticalLayout->addWidget(unstableCheckBox);

        removeSmallStructuresBox = new QCheckBox(centralwidget);
        removeSmallStructuresBox->setObjectName(QString::fromUtf8("removeSmallStructuresBox"));

        verticalLayout->addWidget(removeSmallStructuresBox);

        fillSmallHolesCheckBox = new QCheckBox(centralwidget);
        fillSmallHolesCheckBox->setObjectName(QString::fromUtf8("fillSmallHolesCheckBox"));

        verticalLayout->addWidget(fillSmallHolesCheckBox);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_4->addWidget(label);

        kinectTiltSlider = new QSlider(centralwidget);
        kinectTiltSlider->setObjectName(QString::fromUtf8("kinectTiltSlider"));
        kinectTiltSlider->setMinimum(-31);
        kinectTiltSlider->setMaximum(31);
        kinectTiltSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_4->addWidget(kinectTiltSlider);


        verticalLayout->addLayout(horizontalLayout_4);


        horizontalLayout->addLayout(verticalLayout);


        horizontalLayout_2->addLayout(horizontalLayout);

        FiltersWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(FiltersWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 361, 21));
        FiltersWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(FiltersWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        FiltersWindow->setStatusBar(statusbar);

        retranslateUi(FiltersWindow);

        QMetaObject::connectSlotsByName(FiltersWindow);
    } // setupUi

    void retranslateUi(QMainWindow *FiltersWindow)
    {
        FiltersWindow->setWindowTitle(QApplication::translate("FiltersWindow", "Filters", 0, QApplication::UnicodeUTF8));
        depthThresholdCheckBox->setText(QApplication::translate("FiltersWindow", "Depth threshold", 0, QApplication::UnicodeUTF8));
        minDepthLabel->setText(QApplication::translate("FiltersWindow", "0 m", 0, QApplication::UnicodeUTF8));
        maxDepthLabel->setText(QApplication::translate("FiltersWindow", "7 m", 0, QApplication::UnicodeUTF8));
        edgesCheckBox->setText(QApplication::translate("FiltersWindow", "Edges", 0, QApplication::UnicodeUTF8));
        medianCheckBox->setText(QApplication::translate("FiltersWindow", "Median", 0, QApplication::UnicodeUTF8));
        normalsCheckBox->setText(QApplication::translate("FiltersWindow", "Normals", 0, QApplication::UnicodeUTF8));
        unstableCheckBox->setText(QApplication::translate("FiltersWindow", "Unstable pixels", 0, QApplication::UnicodeUTF8));
        removeSmallStructuresBox->setText(QApplication::translate("FiltersWindow", "Remove small structures", 0, QApplication::UnicodeUTF8));
        fillSmallHolesCheckBox->setText(QApplication::translate("FiltersWindow", "Fill small holes", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("FiltersWindow", "Kinect Tilt", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FiltersWindow: public Ui_FiltersWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FILTERSWINDOW_H
