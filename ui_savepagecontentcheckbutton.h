/********************************************************************************
** Form generated from reading UI file 'savepagecontentcheckbutton.ui'
**
** Created by: Qt User Interface Compiler version 5.15.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAVEPAGECONTENTCHECKBUTTON_H
#define UI_SAVEPAGECONTENTCHECKBUTTON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SavePageContentCheckButton
{
public:
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox;
    QFrame *line;
    QLabel *path;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *SavePageContentCheckButton)
    {
        if (SavePageContentCheckButton->objectName().isEmpty())
            SavePageContentCheckButton->setObjectName(QString::fromUtf8("SavePageContentCheckButton"));
        SavePageContentCheckButton->resize(404, 41);
        horizontalLayout = new QHBoxLayout(SavePageContentCheckButton);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBox = new QCheckBox(SavePageContentCheckButton);
        checkBox->setObjectName(QString::fromUtf8("checkBox"));

        horizontalLayout->addWidget(checkBox);

        line = new QFrame(SavePageContentCheckButton);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout->addWidget(line);

        path = new QLabel(SavePageContentCheckButton);
        path->setObjectName(QString::fromUtf8("path"));

        horizontalLayout->addWidget(path);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        retranslateUi(SavePageContentCheckButton);

        QMetaObject::connectSlotsByName(SavePageContentCheckButton);
    } // setupUi

    void retranslateUi(QWidget *SavePageContentCheckButton)
    {
        SavePageContentCheckButton->setWindowTitle(QCoreApplication::translate("SavePageContentCheckButton", "Form", nullptr));
        checkBox->setText(QCoreApplication::translate("SavePageContentCheckButton", "file name", nullptr));
        path->setText(QCoreApplication::translate("SavePageContentCheckButton", "path", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SavePageContentCheckButton: public Ui_SavePageContentCheckButton {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAVEPAGECONTENTCHECKBUTTON_H
