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

signals:
    void checkedSignal(bool b);

public:
    explicit SavePageContentCheckButton(TabPage *page, QWidget *parent = nullptr);
    bool isChecked();
    void save();

    ~SavePageContentCheckButton();
private slots:
    void checked(bool b);

private:
    Ui::SavePageContentCheckButton *_ui;
    TabPage *_page;
};

#endif // SAVEPAGECONTENTCHECKBUTTON_H
