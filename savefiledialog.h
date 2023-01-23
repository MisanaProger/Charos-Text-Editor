#ifndef SAVEFILEDIALOG_H
#define SAVEFILEDIALOG_H

#pragma once
#include <QDialog>
#include <QAbstractButton>
#include <QPushButton>
#include <QFileDialog>
#include "tabpage.h"
#include "savepagecontentcheckbutton.h"

namespace Ui
{
    class SaveFileDialog;
}

class SaveFileDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SaveFileDialog(QList<TabPage *> pages, QWidget *parent = nullptr);
    void saveFiles();
    ~SaveFileDialog();
private slots:

    void onClicked(QAbstractButton *button);
    void updateSaveButton();

private:
    bool isAnyFileChecked();
    Ui::SaveFileDialog *_ui;
};

#endif // SAVEFILEDIALOG_H
