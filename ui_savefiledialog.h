/********************************************************************************
** Form generated from reading UI file 'savefiledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEFILEDIALOG_H
#define UI_SAVEFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SaveFileDialog
{
public:
    QGridLayout *gridLayout;
    QDialogButtonBox *buttonBox;
    QScrollArea *scrollArea;
    QWidget *field;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;

    void setupUi(QDialog *SaveFileDialog)
    {
        if (SaveFileDialog->objectName().isEmpty())
            SaveFileDialog->setObjectName(QString::fromUtf8("SaveFileDialog"));
        SaveFileDialog->setEnabled(true);
        SaveFileDialog->resize(400, 300);
        SaveFileDialog->setAutoFillBackground(true);
        gridLayout = new QGridLayout(SaveFileDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        buttonBox = new QDialogButtonBox(SaveFileDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Discard|QDialogButtonBox::Save);

        gridLayout->addWidget(buttonBox, 2, 0, 1, 1);

        scrollArea = new QScrollArea(SaveFileDialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setAutoFillBackground(true);
        scrollArea->setWidgetResizable(true);
        field = new QWidget();
        field->setObjectName(QString::fromUtf8("field"));
        field->setGeometry(QRect(0, 0, 380, 224));
        verticalLayout_2 = new QVBoxLayout(field);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setSizeConstraint(QLayout::SetNoConstraint);
        verticalLayout_2->setContentsMargins(3, 3, 3, 3);
        scrollArea->setWidget(field);

        gridLayout->addWidget(scrollArea, 1, 0, 1, 1);

        label = new QLabel(SaveFileDialog);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(16777215, 38));
        QFont font;
        font.setFamily(QString::fromUtf8("DejaVu Sans Condensed"));
        font.setPointSize(12);
        font.setBold(false);
        font.setItalic(true);
        label->setFont(font);
        label->setTextFormat(Qt::AutoText);
        label->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);


        retranslateUi(SaveFileDialog);

        QMetaObject::connectSlotsByName(SaveFileDialog);
    } // setupUi

    void retranslateUi(QDialog *SaveFileDialog)
    {
        SaveFileDialog->setWindowTitle(QCoreApplication::translate("SaveFileDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SaveFileDialog", "    Do you want to save this files?", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SaveFileDialog: public Ui_SaveFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEFILEDIALOG_H
