#include "savepagecontentcheckbutton.h"
#include "ui_savepagecontentcheckbutton.h"

SavePageContentCheckButton::SavePageContentCheckButton(TabPage *page, QWidget *parent) : QWidget(parent), _ui(new Ui::SavePageContentCheckButton)
{
    _ui->setupUi(this);
    this->_page = page;
    _ui->checkBox->setText(page->GetFileName());
    if (page->IsNew())
    {
        _ui->line->close();
        _ui->path->close();
    }

    else
        _ui->path->setText(page->GetFilePath());
    connect(_ui->checkBox, &QCheckBox::clicked, this, &SavePageContentCheckButton::checked);
}

bool SavePageContentCheckButton::isChecked()
{
    return _ui->checkBox->isChecked();
}

void SavePageContentCheckButton::save()
{
    if (_page->CanBeSaved())
        return _page->SaveFile(_page->GetFilePath());
    _page->SaveFile(QFileDialog::getSaveFileName(parentWidget(), "Save file " + _page->GetFileName()));
}

SavePageContentCheckButton::~SavePageContentCheckButton()
{
    delete _ui;
}

void SavePageContentCheckButton::checked(bool b)
{
    emit checkedSignal(b);
}
