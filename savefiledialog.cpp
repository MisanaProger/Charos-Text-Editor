#include "savefiledialog.h"
#include "ui_savefiledialog.h"

SaveFileDialog::SaveFileDialog(QList<TabPage *> pages, QWidget *parent) : QDialog(parent),
                                                                          _ui(new Ui::SaveFileDialog)
{
    _ui->setupUi(this);
    for (int i = 0; i < pages.count(); i++)
    {
        SavePageContentCheckButton *checkBox = new SavePageContentCheckButton(pages[i]);
        _ui->verticalLayout_2->addWidget(checkBox);
        connect(checkBox, &SavePageContentCheckButton::checkedSignal,
                this, &SaveFileDialog::updateSaveButton);
    }
    _ui->verticalLayout_2->addSpacerItem(new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Expanding));
    connect(_ui->buttonBox, &QDialogButtonBox::clicked, this, &SaveFileDialog::onClicked);
    _ui->buttonBox->button(QDialogButtonBox::StandardButton::Save)->setEnabled(isAnyFileChecked());
}

SaveFileDialog::~SaveFileDialog()
{
    delete _ui;
}

void SaveFileDialog::onClicked(QAbstractButton *button)
{
    switch (_ui->buttonBox->standardButton(button))
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

void SaveFileDialog::updateSaveButton()
{
    _ui->buttonBox->button(QDialogButtonBox::StandardButton::Save)->setEnabled(isAnyFileChecked());
}

bool SaveFileDialog::isAnyFileChecked()
{
    auto pages = _ui->field->findChildren<SavePageContentCheckButton *>();
    for (int i = 0; i < pages.count(); i++)
        if (pages[i]->isChecked())
            return true;
    return false;
}

void SaveFileDialog::saveFiles()
{
    auto pages = _ui->field->findChildren<SavePageContentCheckButton *>();
    for (int i = 0; i < pages.count(); i++)
        if (pages[i]->isChecked())
            pages[i]->save();
}
