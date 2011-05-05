/********************************************************************************
** Form generated from reading UI file 'View3dWindow.ui'
**
** Created: Tue May 3 14:16:33 2011
**      by: Qt User Interface Compiler version 4.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW3DWINDOW_H
#define UI_VIEW3DWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QFrame>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <ntk/mesh/mesh_viewer.h>

QT_BEGIN_NAMESPACE

class Ui_View3DWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QCheckBox *colorMappingCheckBox;
    QPushButton *saveMeshPushButton;
    QPushButton *pointCloudPushButton;
    QPushButton *surfelsPushButton;
    QPushButton *trianglePushButton;
    QSpacerItem *horizontalSpacer;
    QPushButton *resetCamera;
    QFrame *frame_2;
    QHBoxLayout *horizontalLayout_2;
    ntk::MeshViewer *mesh_view;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *View3DWindow)
    {
        if (View3DWindow->objectName().isEmpty())
            View3DWindow->setObjectName(QString::fromUtf8("View3DWindow"));
        View3DWindow->resize(913, 600);
        centralwidget = new QWidget(View3DWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        colorMappingCheckBox = new QCheckBox(frame);
        colorMappingCheckBox->setObjectName(QString::fromUtf8("colorMappingCheckBox"));
        colorMappingCheckBox->setChecked(true);

        horizontalLayout->addWidget(colorMappingCheckBox);

        saveMeshPushButton = new QPushButton(frame);
        saveMeshPushButton->setObjectName(QString::fromUtf8("saveMeshPushButton"));

        horizontalLayout->addWidget(saveMeshPushButton);

        pointCloudPushButton = new QPushButton(frame);
        pointCloudPushButton->setObjectName(QString::fromUtf8("pointCloudPushButton"));

        horizontalLayout->addWidget(pointCloudPushButton);

        surfelsPushButton = new QPushButton(frame);
        surfelsPushButton->setObjectName(QString::fromUtf8("surfelsPushButton"));

        horizontalLayout->addWidget(surfelsPushButton);

        trianglePushButton = new QPushButton(frame);
        trianglePushButton->setObjectName(QString::fromUtf8("trianglePushButton"));

        horizontalLayout->addWidget(trianglePushButton);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        resetCamera = new QPushButton(frame);
        resetCamera->setObjectName(QString::fromUtf8("resetCamera"));

        horizontalLayout->addWidget(resetCamera);


        verticalLayout->addWidget(frame);

        frame_2 = new QFrame(centralwidget);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        horizontalLayout_2 = new QHBoxLayout(frame_2);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        mesh_view = new ntk::MeshViewer(frame_2);
        mesh_view->setObjectName(QString::fromUtf8("mesh_view"));

        horizontalLayout_2->addWidget(mesh_view);


        verticalLayout->addWidget(frame_2);

        View3DWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(View3DWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 913, 21));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        View3DWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(View3DWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        View3DWindow->setStatusBar(statusbar);

        menubar->addAction(menu_File->menuAction());

        retranslateUi(View3DWindow);

        QMetaObject::connectSlotsByName(View3DWindow);
    } // setupUi

    void retranslateUi(QMainWindow *View3DWindow)
    {
        View3DWindow->setWindowTitle(QApplication::translate("View3DWindow", "3D View", 0, QApplication::UnicodeUTF8));
        colorMappingCheckBox->setText(QApplication::translate("View3DWindow", "Color", 0, QApplication::UnicodeUTF8));
        saveMeshPushButton->setText(QApplication::translate("View3DWindow", "SaveMesh", 0, QApplication::UnicodeUTF8));
        pointCloudPushButton->setText(QApplication::translate("View3DWindow", "PointCloud", 0, QApplication::UnicodeUTF8));
        surfelsPushButton->setText(QApplication::translate("View3DWindow", "Surfels", 0, QApplication::UnicodeUTF8));
        trianglePushButton->setText(QApplication::translate("View3DWindow", "Triangles", 0, QApplication::UnicodeUTF8));
        resetCamera->setText(QApplication::translate("View3DWindow", "Reset camera", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("View3DWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class View3DWindow: public Ui_View3DWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW3DWINDOW_H
