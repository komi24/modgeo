/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLCDNumber>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionLoad_mesh;
    QAction *actionSave_mesh;
    QAction *actionExit;
    QAction *actionAzerty;
    QAction *actionQwerty;
    QAction *actionSkeleton;
    QAction *actionWeight;
    QAction *actionNo_picking;
    QAction *actionRemove_selected_mesh;
    QAction *action_Unselect;
    QAction *actionYafaray;
    QAction *actionPovRay;
    QAction *actionLuxRender;
    QAction *actionExport_sunflow;
    QAction *actionSettings_sunflow;
    QAction *actionExport_indigo;
    QAction *actionSettings_indigo;
    QAction *actionCamera;
    QAction *actionLight;
    QAction *actionLoad_scene;
    QAction *actionSave_scene;
    QAction *actionSkeleton_picking;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *layout_scene;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *verticalLayoutWidget_4;
    QGridLayout *gridLayout_2;
    QCheckBox *wireframe_checkbox;
    QPushButton *debug_button;
    QWidget *tab_2;
    QSlider *slider_factor;
    QLabel *label;
    QPushButton *simple_algo_button;
    QLCDNumber *lcd_factor;
    QPushButton *optimized_algo_button;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuEdit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(938, 606);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        actionLoad_mesh = new QAction(MainWindow);
        actionLoad_mesh->setObjectName(QString::fromUtf8("actionLoad_mesh"));
        actionSave_mesh = new QAction(MainWindow);
        actionSave_mesh->setObjectName(QString::fromUtf8("actionSave_mesh"));
        actionExit = new QAction(MainWindow);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionAzerty = new QAction(MainWindow);
        actionAzerty->setObjectName(QString::fromUtf8("actionAzerty"));
        actionQwerty = new QAction(MainWindow);
        actionQwerty->setObjectName(QString::fromUtf8("actionQwerty"));
        actionSkeleton = new QAction(MainWindow);
        actionSkeleton->setObjectName(QString::fromUtf8("actionSkeleton"));
        actionWeight = new QAction(MainWindow);
        actionWeight->setObjectName(QString::fromUtf8("actionWeight"));
        actionNo_picking = new QAction(MainWindow);
        actionNo_picking->setObjectName(QString::fromUtf8("actionNo_picking"));
        actionRemove_selected_mesh = new QAction(MainWindow);
        actionRemove_selected_mesh->setObjectName(QString::fromUtf8("actionRemove_selected_mesh"));
        action_Unselect = new QAction(MainWindow);
        action_Unselect->setObjectName(QString::fromUtf8("action_Unselect"));
        actionYafaray = new QAction(MainWindow);
        actionYafaray->setObjectName(QString::fromUtf8("actionYafaray"));
        actionPovRay = new QAction(MainWindow);
        actionPovRay->setObjectName(QString::fromUtf8("actionPovRay"));
        actionLuxRender = new QAction(MainWindow);
        actionLuxRender->setObjectName(QString::fromUtf8("actionLuxRender"));
        actionExport_sunflow = new QAction(MainWindow);
        actionExport_sunflow->setObjectName(QString::fromUtf8("actionExport_sunflow"));
        actionSettings_sunflow = new QAction(MainWindow);
        actionSettings_sunflow->setObjectName(QString::fromUtf8("actionSettings_sunflow"));
        actionExport_indigo = new QAction(MainWindow);
        actionExport_indigo->setObjectName(QString::fromUtf8("actionExport_indigo"));
        actionSettings_indigo = new QAction(MainWindow);
        actionSettings_indigo->setObjectName(QString::fromUtf8("actionSettings_indigo"));
        actionCamera = new QAction(MainWindow);
        actionCamera->setObjectName(QString::fromUtf8("actionCamera"));
        actionLight = new QAction(MainWindow);
        actionLight->setObjectName(QString::fromUtf8("actionLight"));
        actionLoad_scene = new QAction(MainWindow);
        actionLoad_scene->setObjectName(QString::fromUtf8("actionLoad_scene"));
        actionSave_scene = new QAction(MainWindow);
        actionSave_scene->setObjectName(QString::fromUtf8("actionSave_scene"));
        actionSkeleton_picking = new QAction(MainWindow);
        actionSkeleton_picking->setObjectName(QString::fromUtf8("actionSkeleton_picking"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        sizePolicy.setHeightForWidth(centralwidget->sizePolicy().hasHeightForWidth());
        centralwidget->setSizePolicy(sizePolicy);
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        layout_scene = new QVBoxLayout();
        layout_scene->setObjectName(QString::fromUtf8("layout_scene"));

        gridLayout->addLayout(layout_scene, 0, 1, 2, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));

        gridLayout->addLayout(verticalLayout_3, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy1);
        tabWidget->setMinimumSize(QSize(270, 200));
        tabWidget->setBaseSize(QSize(0, 0));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        verticalLayoutWidget_4 = new QWidget(tab);
        verticalLayoutWidget_4->setObjectName(QString::fromUtf8("verticalLayoutWidget_4"));
        verticalLayoutWidget_4->setGeometry(QRect(10, 10, 251, 151));
        gridLayout_2 = new QGridLayout(verticalLayoutWidget_4);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        wireframe_checkbox = new QCheckBox(verticalLayoutWidget_4);
        wireframe_checkbox->setObjectName(QString::fromUtf8("wireframe_checkbox"));

        gridLayout_2->addWidget(wireframe_checkbox, 0, 0, 1, 1);

        debug_button = new QPushButton(verticalLayoutWidget_4);
        debug_button->setObjectName(QString::fromUtf8("debug_button"));

        gridLayout_2->addWidget(debug_button, 1, 0, 1, 1);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        slider_factor = new QSlider(tab_2);
        slider_factor->setObjectName(QString::fromUtf8("slider_factor"));
        slider_factor->setGeometry(QRect(60, 40, 160, 29));
        slider_factor->setAcceptDrops(false);
        slider_factor->setMinimum(1);
        slider_factor->setMaximum(1000);
        slider_factor->setPageStep(100);
        slider_factor->setOrientation(Qt::Horizontal);
        label = new QLabel(tab_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 20, 141, 17));
        simple_algo_button = new QPushButton(tab_2);
        simple_algo_button->setObjectName(QString::fromUtf8("simple_algo_button"));
        simple_algo_button->setGeometry(QRect(10, 130, 99, 27));
        lcd_factor = new QLCDNumber(tab_2);
        lcd_factor->setObjectName(QString::fromUtf8("lcd_factor"));
        lcd_factor->setGeometry(QRect(100, 70, 64, 23));
        lcd_factor->setSegmentStyle(QLCDNumber::Flat);
        lcd_factor->setProperty("value", QVariant(1));
        optimized_algo_button = new QPushButton(tab_2);
        optimized_algo_button->setObjectName(QString::fromUtf8("optimized_algo_button"));
        optimized_algo_button->setGeometry(QRect(130, 130, 121, 27));
        tabWidget->addTab(tab_2, QString());

        verticalLayout_2->addWidget(tabWidget);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 938, 25));
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuEdit = new QMenu(menubar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuEdit->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionExit);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionLoad_mesh->setText(QApplication::translate("MainWindow", "Load mesh", 0, QApplication::UnicodeUTF8));
        actionSave_mesh->setText(QApplication::translate("MainWindow", "Save mesh", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("MainWindow", "Exit", 0, QApplication::UnicodeUTF8));
        actionAzerty->setText(QApplication::translate("MainWindow", "azerty", 0, QApplication::UnicodeUTF8));
        actionQwerty->setText(QApplication::translate("MainWindow", "qwerty", 0, QApplication::UnicodeUTF8));
        actionSkeleton->setText(QApplication::translate("MainWindow", "Skeleton", 0, QApplication::UnicodeUTF8));
        actionWeight->setText(QApplication::translate("MainWindow", "Weight", 0, QApplication::UnicodeUTF8));
        actionNo_picking->setText(QApplication::translate("MainWindow", "no picking", 0, QApplication::UnicodeUTF8));
        actionRemove_selected_mesh->setText(QApplication::translate("MainWindow", "Remove (&X)", 0, QApplication::UnicodeUTF8));
        action_Unselect->setText(QApplication::translate("MainWindow", "&Unselect", 0, QApplication::UnicodeUTF8));
        actionYafaray->setText(QApplication::translate("MainWindow", "Yafaray", 0, QApplication::UnicodeUTF8));
        actionPovRay->setText(QApplication::translate("MainWindow", "PovRay", 0, QApplication::UnicodeUTF8));
        actionLuxRender->setText(QApplication::translate("MainWindow", "LuxRender", 0, QApplication::UnicodeUTF8));
        actionExport_sunflow->setText(QApplication::translate("MainWindow", "Export", 0, QApplication::UnicodeUTF8));
        actionSettings_sunflow->setText(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        actionExport_indigo->setText(QApplication::translate("MainWindow", "Export", 0, QApplication::UnicodeUTF8));
        actionSettings_indigo->setText(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        actionCamera->setText(QApplication::translate("MainWindow", "Camera", 0, QApplication::UnicodeUTF8));
        actionLight->setText(QApplication::translate("MainWindow", "Light", 0, QApplication::UnicodeUTF8));
        actionLoad_scene->setText(QApplication::translate("MainWindow", "Load scene", 0, QApplication::UnicodeUTF8));
        actionSave_scene->setText(QApplication::translate("MainWindow", "Save scene", 0, QApplication::UnicodeUTF8));
        actionSkeleton_picking->setText(QApplication::translate("MainWindow", "skeleton picking", 0, QApplication::UnicodeUTF8));
        wireframe_checkbox->setText(QApplication::translate("MainWindow", "Wireframe", 0, QApplication::UnicodeUTF8));
        debug_button->setText(QApplication::translate("MainWindow", "Debug", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Viewer", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("MainWindow", "Simplification factor", 0, QApplication::UnicodeUTF8));
        simple_algo_button->setText(QApplication::translate("MainWindow", "Simple Algo", 0, QApplication::UnicodeUTF8));
        optimized_algo_button->setText(QApplication::translate("MainWindow", "Optimized Algo", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Simplification", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Edit", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
