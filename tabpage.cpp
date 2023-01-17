#include "tabpage.h"
#include "ui_tabpage.h"

TabPage::TabPage(QWidget *parent) : QWidget(parent), ui(new Ui::TabPage)
{
    ui->setupUi(this);

    _state.copyAvaliable = _state.redoAvaliable = _state.undoAvaliable = false;

    connect(ui->textEdit, &QTextEdit::textChanged, this, &TabPage::textEdited);
    connect(ui->textEdit, &QTextEdit::undoAvailable, this, &TabPage::setUndoState);
    connect(ui->textEdit, &QTextEdit::redoAvailable, this, &TabPage::setRedoState);
    connect(ui->textEdit, &QTextEdit::copyAvailable, this, &TabPage::setCopyAndCutState);
}

TabPage *TabPage::OpenFile(QString path, QWidget *parent)
{
    if (path.isEmpty())
        return nullptr;
    QFile file(path);
    if (!file.open(QIODevice::ReadWrite | QIODevice::Text))
        // TODO! придумать механизм выбрасывания исключеий
        return nullptr;
    TabPage *page = new TabPage(parent);
    page->_file = new QFileInfo(file);
    page->_lastSavedContent = QTextStream(&file).readAll();
    page->ui->textEdit->setText(page->_lastSavedContent);
    file.close();
    return page;
}

TabPage *TabPage::NewFile(QWidget *parent)
{
    TabPage *page = new TabPage(parent);
    page->_file = nullptr;
    return page;
}

void TabPage::SaveFile(QString path)
{
    if (path.isEmpty())
        return;
    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        // TODO! придумать механизм выбрасывания исключеий
        return;
    _lastSavedContent = ui->textEdit->toPlainText();
    delete _file;
    _file = new QFileInfo(file);
    QTextStream(&file) << _lastSavedContent;

    file.close();
    emit UpdateTitle(GetFileName());
    emit SetSaveState(NeedToBeSaved() && CanBeSaved());
}

void TabPage::Activate()
{
    emit SetCopyAndCutState(_state.copyAvaliable);
    emit SetUndoState(_state.undoAvaliable);
    emit SetRedoState(_state.redoAvaliable);
    emit SetSaveState(NeedToBeSaved() && CanBeSaved());
    emit SetSelectAllState(!ui->textEdit->toPlainText().isEmpty());
    emit UpdateTitle(GetFileName());
}

bool TabPage::NeedToBeSaved()
{
    return _lastSavedContent != ui->textEdit->toPlainText();
}

bool TabPage::CanBeSaved()
{
    return !IsNew();
}

bool TabPage::IsNew()
{
    return _file == nullptr;
}

QString TabPage::GetFileName()
{
    return IsNew() ? "*NewFile" : _file->fileName();
}

QString TabPage::GetFilePath()
{
    return IsNew() ? "None" : _file->absoluteFilePath();
}

TabPage::~TabPage()
{
    delete _file;
    delete ui;
}

void TabPage::Undo()
{
    ui->textEdit->undo();
}

void TabPage::Redo()
{
    ui->textEdit->redo();
}

void TabPage::Cut()
{
    ui->textEdit->cut();
}

void TabPage::Copy()
{
    ui->textEdit->copy();
}

void TabPage::Paste()
{
    ui->textEdit->paste();
}

void TabPage::SelectAll()
{
    ui->textEdit->selectAll();
}

void TabPage::textEdited()
{
    emit SetSaveState(NeedToBeSaved() && CanBeSaved());
    emit SetSelectAllState(!ui->textEdit->toPlainText().isEmpty());
}

void TabPage::setUndoState(bool val)
{
    emit SetUndoState(val);
    _state.undoAvaliable = val;
}

void TabPage::setRedoState(bool val)
{
    emit SetRedoState(val);
    _state.redoAvaliable = val;
}

void TabPage::setCopyAndCutState(bool val)
{
    emit SetCopyAndCutState(val);
    _state.copyAvaliable = val;
}
