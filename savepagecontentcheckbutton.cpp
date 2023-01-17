#include "savepagecontentcheckbutton.h"
#include "ui_savepagecontentcheckbutton.h"

SavePageContentCheckButton::SavePageContentCheckButton(TabPage *page, QWidget *parent) : QWidget(parent),
                                                                                         ui(new Ui::SavePageContentCheckButton)
{
    ui->setupUi(this);
    this->_page = page;
    ui->checkBox->setText(page->GetFileName());
    if (!page->IsNew())
        ui->path->setText(page->GetFilePath());
    else
    {
        ui->line->close();
        ui->path->close();
    }
}

bool SavePageContentCheckButton::isChecked()
{
    return ui->checkBox->isChecked();
}

SavePageContentCheckButton::~SavePageContentCheckButton()
{
    delete ui;
}
