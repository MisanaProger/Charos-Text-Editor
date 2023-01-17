#ifndef SAVEPAGECONTENTCHECKBUTTON_H
#define SAVEPAGECONTENTCHECKBUTTON_H

#include <QWidget>
#include "savefiledialog.h"
#include "tabpage.h"

namespace Ui
{
    class SavePageContentCheckButton;
}

class SavePageContentCheckButton : public QWidget
{
    Q_OBJECT

public:
    explicit SavePageContentCheckButton(TabPage *page, QWidget *parent = nullptr);
    bool isChecked();

    ~SavePageContentCheckButton();

private:
    Ui::SavePageContentCheckButton *ui;
    TabPage *_page;
    friend class SaveFileDialog;
};

#endif // SAVEPAGECONTENTCHECKBUTTON_H
