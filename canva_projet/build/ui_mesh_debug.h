/********************************************************************************
** Form generated from reading UI file 'mesh_debug.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESH_DEBUG_H
#define UI_MESH_DEBUG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_mesh_debug
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox;
    QCheckBox *debug_mode_button;
    QCheckBox *inverted_normal_button;
    QCheckBox *vertex_index_button;
    QCheckBox *face_index_button;
    QCheckBox *vertex_show_button;

    void setupUi(QDialog *mesh_debug)
    {
        if (mesh_debug->objectName().isEmpty())
            mesh_debug->setObjectName(QString::fromUtf8("mesh_debug"));
        mesh_debug->resize(370, 189);
        buttonBox = new QDialogButtonBox(mesh_debug);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(20, 150, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox = new QGroupBox(mesh_debug);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 351, 121));
        debug_mode_button = new QCheckBox(groupBox);
        debug_mode_button->setObjectName(QString::fromUtf8("debug_mode_button"));
        debug_mode_button->setGeometry(QRect(10, 30, 111, 22));
        inverted_normal_button = new QCheckBox(groupBox);
        inverted_normal_button->setObjectName(QString::fromUtf8("inverted_normal_button"));
        inverted_normal_button->setEnabled(true);
        inverted_normal_button->setGeometry(QRect(10, 90, 141, 22));
        inverted_normal_button->setCheckable(true);
        inverted_normal_button->setChecked(false);
        inverted_normal_button->setTristate(false);
        vertex_index_button = new QCheckBox(groupBox);
        vertex_index_button->setObjectName(QString::fromUtf8("vertex_index_button"));
        vertex_index_button->setGeometry(QRect(10, 60, 111, 22));
        vertex_index_button->setChecked(true);
        face_index_button = new QCheckBox(groupBox);
        face_index_button->setObjectName(QString::fromUtf8("face_index_button"));
        face_index_button->setGeometry(QRect(150, 60, 94, 22));
        face_index_button->setChecked(true);
        vertex_show_button = new QCheckBox(groupBox);
        vertex_show_button->setObjectName(QString::fromUtf8("vertex_show_button"));
        vertex_show_button->setGeometry(QRect(150, 90, 111, 22));
        vertex_show_button->setChecked(true);

        retranslateUi(mesh_debug);
        QObject::connect(buttonBox, SIGNAL(accepted()), mesh_debug, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), mesh_debug, SLOT(reject()));

        QMetaObject::connectSlotsByName(mesh_debug);
    } // setupUi

    void retranslateUi(QDialog *mesh_debug)
    {
        mesh_debug->setWindowTitle(QApplication::translate("mesh_debug", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("mesh_debug", "Mesh debug", 0, QApplication::UnicodeUTF8));
        debug_mode_button->setText(QApplication::translate("mesh_debug", "Debug mode", 0, QApplication::UnicodeUTF8));
        inverted_normal_button->setText(QApplication::translate("mesh_debug", "inverted normal", 0, QApplication::UnicodeUTF8));
        vertex_index_button->setText(QApplication::translate("mesh_debug", "Vertex index", 0, QApplication::UnicodeUTF8));
        face_index_button->setText(QApplication::translate("mesh_debug", "Face index", 0, QApplication::UnicodeUTF8));
        vertex_show_button->setText(QApplication::translate("mesh_debug", "Vertex show", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class mesh_debug: public Ui_mesh_debug {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESH_DEBUG_H
