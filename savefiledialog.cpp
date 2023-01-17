#include "savefiledialog.h"
#include "ui_savefiledialog.h"

SaveFileDialog::SaveFileDialog(QList<TabPage *> pages, QWidget *parent) : QDialog(parent),
                                                                          ui(new Ui::SaveFileDialog)
{
    ui->setupUi(this);
    for (int i = 0; i < pages.count(); i++)
        ui->verticalLayout_2->addWidget(new SavePageContentCheckButton(pages[i], this));
    ui->verticalLayout_2->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &SaveFileDialog::onClicked);
}

SaveFileDialog::~SaveFileDialog()
{
    delete ui;
}

void SaveFileDialog::onClicked(QAbstractButton *button)
{
    switch (ui->buttonBox->standardButton(button))
    {
    case QDialogButtonBox::Save:
        qDebug("Save");
        saveFiles();
        accept();
        break;
    case QDialogButtonBox::Cancel:
        reject();
        break;
    case QDialogButtonBox::Discard:
        accept();
        break;
    }
}

void SaveFileDialog::saveFiles()
{
    auto pages = ui->field->findChildren <SavePageContentCheckButton *>();
    for (int i = 0; i < pages.count(); i++)
        if (pages[i]->isChecked())
        {
            if (pages[i]->_page->CanBeSaved())
                pages[i]->_page->SaveFile(pages[i]->_page->GetFilePath());
            else
                pages[i]->_page->SaveFile(QFileDialog::getSaveFileName(this, "Save " + pages[i]->_page->GetFileName(), ""));
        }
}
