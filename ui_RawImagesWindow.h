/********************************************************************************
** Form generated from reading UI file 'RawImagesWindow.ui'
**
** Created: Tue May 3 14:16:33 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RAWIMAGESWINDOW_H
#define UI_RAWIMAGESWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDockWidget>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include <ntk/gui/image_widget.h>

QT_BEGIN_NAMESPACE

class Ui_RawImagesWindow
{
public:
    QAction *action_GrabOneFrame;
    QAction *action_Quit;
    QAction *action_Show_Object_Detector;
    QAction *action_3D_View;
    QAction *action_Screen_capture_mode;
    QAction *action_GrabFrames;
    QAction *action_Filters;
    QAction *actionPa10_Controller;
    QAction *action_Show_Modeler;
    QAction *actionStep_by_step;
    QAction *actionStep_by_step_2;
    QAction *actionPause;
    QAction *actionNext_frame;
    QAction *actionPedestrians;
    QAction *actionShow_IR;
    QAction *actionDual_RGB_IR_mode;
    QAction *actionSave_calibration_parameters;
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    ntk::ImageWidget *depthView;
    QMenuBar *menubar;
    QMenu *menuShow;
    QMenu *menuFile;
    QMenu *menuCapture;
    QStatusBar *statusbar;
    QDockWidget *dockWidget;
    QWidget *dockWidgetContents;
    QHBoxLayout *horizontalLayout_3;
    ntk::ImageWidget *colorView;
    QDockWidget *dockWidget_2;
    QWidget *dockWidgetContents_2;
    QHBoxLayout *horizontalLayout_4;
    ntk::ImageWidget *intensityView;
    QDockWidget *dockWidget_3;
    QWidget *dockWidgetContents_3;
    QHBoxLayout *horizontalLayout_5;
    ntk::ImageWidget *amplitudeView;
    QDockWidget *dockWidget_4;
    QWidget *dockWidgetContents_4;
    QHBoxLayout *horizontalLayout_6;
    QFrame *frame;
    QHBoxLayout *horizontalLayout_7;
    QFrame *line_3;
    QLineEdit *outputDirText;
    QLabel *label;
    QFrame *line_2;
    QCheckBox *syncMode;
    QFrame *line;
    QSpacerItem *horizontalSpacer;
    QLabel *distanceLabel;

    void setupUi(QMainWindow *RawImagesWindow)
    {
        if (RawImagesWindow->objectName().isEmpty())
            RawImagesWindow->setObjectName(QString::fromUtf8("RawImagesWindow"));
        RawImagesWindow->resize(735, 557);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RawImagesWindow->sizePolicy().hasHeightForWidth());
        RawImagesWindow->setSizePolicy(sizePolicy);
        action_GrabOneFrame = new QAction(RawImagesWindow);
        action_GrabOneFrame->setObjectName(QString::fromUtf8("action_GrabOneFrame"));
        action_Quit = new QAction(RawImagesWindow);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_Show_Object_Detector = new QAction(RawImagesWindow);
        action_Show_Object_Detector->setObjectName(QString::fromUtf8("action_Show_Object_Detector"));
        action_Show_Object_Detector->setCheckable(true);
        action_Show_Object_Detector->setChecked(false);
        action_3D_View = new QAction(RawImagesWindow);
        action_3D_View->setObjectName(QString::fromUtf8("action_3D_View"));
        action_3D_View->setCheckable(true);
        action_Screen_capture_mode = new QAction(RawImagesWindow);
        action_Screen_capture_mode->setObjectName(QString::fromUtf8("action_Screen_capture_mode"));
        action_Screen_capture_mode->setCheckable(true);
        action_Screen_capture_mode->setEnabled(true);
        action_GrabFrames = new QAction(RawImagesWindow);
        action_GrabFrames->setObjectName(QString::fromUtf8("action_GrabFrames"));
        action_GrabFrames->setCheckable(true);
        action_Filters = new QAction(RawImagesWindow);
        action_Filters->setObjectName(QString::fromUtf8("action_Filters"));
        action_Filters->setCheckable(true);
        actionPa10_Controller = new QAction(RawImagesWindow);
        actionPa10_Controller->setObjectName(QString::fromUtf8("actionPa10_Controller"));
        actionPa10_Controller->setCheckable(true);
        actionPa10_Controller->setEnabled(false);
        action_Show_Modeler = new QAction(RawImagesWindow);
        action_Show_Modeler->setObjectName(QString::fromUtf8("action_Show_Modeler"));
        action_Show_Modeler->setCheckable(true);
        action_Show_Modeler->setEnabled(false);
        actionStep_by_step = new QAction(RawImagesWindow);
        actionStep_by_step->setObjectName(QString::fromUtf8("actionStep_by_step"));
        actionStep_by_step_2 = new QAction(RawImagesWindow);
        actionStep_by_step_2->setObjectName(QString::fromUtf8("actionStep_by_step_2"));
        actionPause = new QAction(RawImagesWindow);
        actionPause->setObjectName(QString::fromUtf8("actionPause"));
        actionPause->setCheckable(true);
        actionNext_frame = new QAction(RawImagesWindow);
        actionNext_frame->setObjectName(QString::fromUtf8("actionNext_frame"));
        actionPedestrians = new QAction(RawImagesWindow);
        actionPedestrians->setObjectName(QString::fromUtf8("actionPedestrians"));
        actionPedestrians->setCheckable(true);
        actionShow_IR = new QAction(RawImagesWindow);
        actionShow_IR->setObjectName(QString::fromUtf8("actionShow_IR"));
        actionShow_IR->setCheckable(true);
        actionDual_RGB_IR_mode = new QAction(RawImagesWindow);
        actionDual_RGB_IR_mode->setObjectName(QString::fromUtf8("actionDual_RGB_IR_mode"));
        actionDual_RGB_IR_mode->setCheckable(true);
        actionSave_calibration_parameters = new QAction(RawImagesWindow);
        actionSave_calibration_parameters->setObjectName(QString::fromUtf8("actionSave_calibration_parameters"));
        centralwidget = new QWidget(RawImagesWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        depthView = new ntk::ImageWidget(frame_2);
        depthView->setObjectName(QString::fromUtf8("depthView"));
        depthView->setMinimumSize(QSize(320, 240));
        depthView->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout_2->addWidget(depthView);


        horizontalLayout->addWidget(frame_2);

        RawImagesWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(RawImagesWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 735, 18));
        menuShow = new QMenu(menubar);
        menuShow->setObjectName(QString::fromUtf8("menuShow"));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuCapture = new QMenu(menubar);
        menuCapture->setObjectName(QString::fromUtf8("menuCapture"));
        RawImagesWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(RawImagesWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        RawImagesWindow->setStatusBar(statusbar);
        dockWidget = new QDockWidget(RawImagesWindow);
        dockWidget->setObjectName(QString::fromUtf8("dockWidget"));
        dockWidgetContents = new QWidget();
        dockWidgetContents->setObjectName(QString::fromUtf8("dockWidgetContents"));
        dockWidgetContents->setMinimumSize(QSize(160, 120));
        horizontalLayout_3 = new QHBoxLayout(dockWidgetContents);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        colorView = new ntk::ImageWidget(dockWidgetContents);
        colorView->setObjectName(QString::fromUtf8("colorView"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(colorView->sizePolicy().hasHeightForWidth());
        colorView->setSizePolicy(sizePolicy1);

        horizontalLayout_3->addWidget(colorView);

        dockWidget->setWidget(dockWidgetContents);
        RawImagesWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget);
        dockWidget_2 = new QDockWidget(RawImagesWindow);
        dockWidget_2->setObjectName(QString::fromUtf8("dockWidget_2"));
        dockWidgetContents_2 = new QWidget();
        dockWidgetContents_2->setObjectName(QString::fromUtf8("dockWidgetContents_2"));
        dockWidgetContents_2->setMinimumSize(QSize(160, 120));
        horizontalLayout_4 = new QHBoxLayout(dockWidgetContents_2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        intensityView = new ntk::ImageWidget(dockWidgetContents_2);
        intensityView->setObjectName(QString::fromUtf8("intensityView"));

        horizontalLayout_4->addWidget(intensityView);

        dockWidget_2->setWidget(dockWidgetContents_2);
        RawImagesWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_2);
        dockWidget_3 = new QDockWidget(RawImagesWindow);
        dockWidget_3->setObjectName(QString::fromUtf8("dockWidget_3"));
        dockWidgetContents_3 = new QWidget();
        dockWidgetContents_3->setObjectName(QString::fromUtf8("dockWidgetContents_3"));
        dockWidgetContents_3->setMinimumSize(QSize(160, 120));
        horizontalLayout_5 = new QHBoxLayout(dockWidgetContents_3);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        amplitudeView = new ntk::ImageWidget(dockWidgetContents_3);
        amplitudeView->setObjectName(QString::fromUtf8("amplitudeView"));

        horizontalLayout_5->addWidget(amplitudeView);

        dockWidget_3->setWidget(dockWidgetContents_3);
        RawImagesWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(2), dockWidget_3);
        dockWidget_4 = new QDockWidget(RawImagesWindow);
        dockWidget_4->setObjectName(QString::fromUtf8("dockWidget_4"));
        dockWidgetContents_4 = new QWidget();
        dockWidgetContents_4->setObjectName(QString::fromUtf8("dockWidgetContents_4"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(dockWidgetContents_4->sizePolicy().hasHeightForWidth());
        dockWidgetContents_4->setSizePolicy(sizePolicy2);
        horizontalLayout_6 = new QHBoxLayout(dockWidgetContents_4);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        frame = new QFrame(dockWidgetContents_4);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy2.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy2);
        frame->setFrameShape(QFrame::Panel);
        frame->setFrameShadow(QFrame::Raised);
        frame->setLineWidth(1);
        horizontalLayout_7 = new QHBoxLayout(frame);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        line_3 = new QFrame(frame);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        horizontalLayout_7->addWidget(line_3);

        outputDirText = new QLineEdit(frame);
        outputDirText->setObjectName(QString::fromUtf8("outputDirText"));
        outputDirText->setMinimumSize(QSize(100, 0));
        outputDirText->setFocusPolicy(Qt::ClickFocus);

        horizontalLayout_7->addWidget(outputDirText);

        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_7->addWidget(label);

        line_2 = new QFrame(frame);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        horizontalLayout_7->addWidget(line_2);

        syncMode = new QCheckBox(frame);
        syncMode->setObjectName(QString::fromUtf8("syncMode"));
        syncMode->setChecked(false);

        horizontalLayout_7->addWidget(syncMode);

        line = new QFrame(frame);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_7->addWidget(line);

        horizontalSpacer = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        distanceLabel = new QLabel(frame);
        distanceLabel->setObjectName(QString::fromUtf8("distanceLabel"));

        horizontalLayout_7->addWidget(distanceLabel);


        horizontalLayout_6->addWidget(frame);

        dockWidget_4->setWidget(dockWidgetContents_4);
        RawImagesWindow->addDockWidget(static_cast<Qt::DockWidgetArea>(4), dockWidget_4);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuShow->menuAction());
        menubar->addAction(menuCapture->menuAction());
        menuShow->addAction(action_Show_Object_Detector);
        menuShow->addAction(action_3D_View);
        menuShow->addAction(action_Filters);
        menuFile->addAction(action_GrabOneFrame);
        menuFile->addAction(action_GrabFrames);
        menuFile->addAction(action_Screen_capture_mode);
        menuFile->addAction(actionSave_calibration_parameters);
        menuFile->addSeparator();
        menuFile->addAction(action_Quit);
        menuCapture->addAction(actionPause);
        menuCapture->addAction(actionNext_frame);
        menuCapture->addAction(actionShow_IR);
        menuCapture->addAction(actionDual_RGB_IR_mode);

        retranslateUi(RawImagesWindow);

        QMetaObject::connectSlotsByName(RawImagesWindow);
    } // setupUi

    void retranslateUi(QMainWindow *RawImagesWindow)
    {
        RawImagesWindow->setWindowTitle(QApplication::translate("RawImagesWindow", "RGB-D Capture", 0, QApplication::UnicodeUTF8));
        action_GrabOneFrame->setText(QApplication::translate("RawImagesWindow", "Grab one frame", 0, QApplication::UnicodeUTF8));
        action_GrabOneFrame->setShortcut(QApplication::translate("RawImagesWindow", "Ctrl+G", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("RawImagesWindow", "&Quit", 0, QApplication::UnicodeUTF8));
        action_Quit->setShortcut(QApplication::translate("RawImagesWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
        action_Show_Object_Detector->setText(QApplication::translate("RawImagesWindow", "&Object detector", 0, QApplication::UnicodeUTF8));
        action_3D_View->setText(QApplication::translate("RawImagesWindow", "3D &View", 0, QApplication::UnicodeUTF8));
        action_Screen_capture_mode->setText(QApplication::translate("RawImagesWindow", "&Screen capture mode", 0, QApplication::UnicodeUTF8));
        action_GrabFrames->setText(QApplication::translate("RawImagesWindow", "Grab all frames", 0, QApplication::UnicodeUTF8));
        action_Filters->setText(QApplication::translate("RawImagesWindow", "Filters", 0, QApplication::UnicodeUTF8));
        actionPa10_Controller->setText(QApplication::translate("RawImagesWindow", "Pa10 Controller", 0, QApplication::UnicodeUTF8));
        action_Show_Modeler->setText(QApplication::translate("RawImagesWindow", "3D Modeler", 0, QApplication::UnicodeUTF8));
        actionStep_by_step->setText(QApplication::translate("RawImagesWindow", "Step by step", 0, QApplication::UnicodeUTF8));
        actionStep_by_step_2->setText(QApplication::translate("RawImagesWindow", "Step by step", 0, QApplication::UnicodeUTF8));
        actionPause->setText(QApplication::translate("RawImagesWindow", "Pause", 0, QApplication::UnicodeUTF8));
        actionNext_frame->setText(QApplication::translate("RawImagesWindow", "Next frame", 0, QApplication::UnicodeUTF8));
        actionNext_frame->setShortcut(QApplication::translate("RawImagesWindow", "Ctrl+Right", 0, QApplication::UnicodeUTF8));
        actionPedestrians->setText(QApplication::translate("RawImagesWindow", "Pedestrians", 0, QApplication::UnicodeUTF8));
        actionShow_IR->setText(QApplication::translate("RawImagesWindow", "Show IR", 0, QApplication::UnicodeUTF8));
        actionDual_RGB_IR_mode->setText(QApplication::translate("RawImagesWindow", "Dual RGB/IR mode", 0, QApplication::UnicodeUTF8));
        actionSave_calibration_parameters->setText(QApplication::translate("RawImagesWindow", "Save calibration parameters", 0, QApplication::UnicodeUTF8));
        menuShow->setTitle(QApplication::translate("RawImagesWindow", "&Show", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("RawImagesWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuCapture->setTitle(QApplication::translate("RawImagesWindow", "Capture", 0, QApplication::UnicodeUTF8));
        dockWidget->setWindowTitle(QApplication::translate("RawImagesWindow", "Color Image", 0, QApplication::UnicodeUTF8));
        dockWidget_2->setWindowTitle(QApplication::translate("RawImagesWindow", "Intensity Image (IR)", 0, QApplication::UnicodeUTF8));
        dockWidget_3->setWindowTitle(QApplication::translate("RawImagesWindow", "Amplitude image", 0, QApplication::UnicodeUTF8));
        dockWidget_4->setWindowTitle(QApplication::translate("RawImagesWindow", "Options", 0, QApplication::UnicodeUTF8));
        outputDirText->setText(QApplication::translate("RawImagesWindow", "calibration", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RawImagesWindow", "Output dir.", 0, QApplication::UnicodeUTF8));
        syncMode->setText(QApplication::translate("RawImagesWindow", "Sync", 0, QApplication::UnicodeUTF8));
        distanceLabel->setText(QApplication::translate("RawImagesWindow", "D at (x,y) = 0 m ", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RawImagesWindow: public Ui_RawImagesWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RAWIMAGESWINDOW_H
