#include "tabpage.h"
#include "ui_tabpage.h"

TabPage::TabPage(QWidget *parent) : QWidget(parent), _ui(new Ui::TabPage)
{
    _ui->setupUi(this);

    _state.copyAvaliable = _state.redoAvaliable = _state.undoAvaliable = false;

    connect(_ui->textEdit, &QTextEdit::textChanged, this, &TabPage::textEdited);
    connect(_ui->textEdit, &QTextEdit::undoAvailable, this, &TabPage::setUndoState);
    connect(_ui->textEdit, &QTextEdit::redoAvailable, this, &TabPage::setRedoState);
    connect(_ui->textEdit, &QTextEdit::copyAvailable, this, &TabPage::setCopyAndCutState);
    connect(_ui->textEdit, &QTextEdit::cursorPositionChanged, this, &TabPage::updateSatusBar);
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
    page->_ui->textEdit->setText(page->_lastSavedContent);
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
    _lastSavedContent = _ui->textEdit->toPlainText();
    delete _file;
    _file = new QFileInfo(file);
    QTextStream(&file) << _lastSavedContent;
    file.close();
    emit UpdateTitle(GetFileName());
    emit SetSaveState(NeedToBeSaved() && CanBeSaved());
}

void TabPage::Activate(QTextOption::WrapMode wrapMode)
{
    _ui->textEdit->setWordWrapMode(wrapMode);
    emit SetCopyAndCutState(_state.copyAvaliable);
    emit SetUndoState(_state.undoAvaliable);
    emit SetRedoState(_state.redoAvaliable);
    emit SetSaveState(NeedToBeSaved() && CanBeSaved());
    emit SetSelectAllState(!_ui->textEdit->toPlainText().isEmpty());
    emit UpdateTitle(GetFileName());
    emit UpdateStatusBar(GetCurrentLineIndex(), GetCountOfCharsInLeftOfCursor());
}

bool TabPage::NeedToBeSaved()
{
    return _lastSavedContent != _ui->textEdit->toPlainText();
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
    delete _ui;
}

int TabPage::GetCurrentLineIndex()
{
    QStringList lines = _ui->textEdit->toPlainText().split("\n");
    int counter = 0;
    for (int i = 0; i < lines.count(); i++)
    {
        if (lines[i].length() >= _ui->textEdit->textCursor().position() - counter)
            return i + 1;
        counter += lines[i].length() + 1;
    }

    return 0;
}

int TabPage::GetCountOfCharsInLeftOfCursor()
{
    QStringList lines = _ui->textEdit->toPlainText().split("\n");
    int counter = 0;
    for (int i = 0; i < lines.count(); i++)
    {
        if (lines[i].length() >= _ui->textEdit->textCursor().position() - counter)
            return _ui->textEdit->textCursor().position() - counter;
        counter += lines[i].length() + 1;
    }

    return 0;
}

void TabPage::Undo()
{
    _ui->textEdit->undo();
}

void TabPage::Redo()
{
    _ui->textEdit->redo();
}

void TabPage::Cut()
{
    _ui->textEdit->cut();
}

void TabPage::Copy()
{
    _ui->textEdit->copy();
}

void TabPage::Paste()
{
    _ui->textEdit->paste();
}

void TabPage::SelectAll()
{
    _ui->textEdit->selectAll();
}

void TabPage::textEdited()
{
    emit SetSaveState(NeedToBeSaved() && CanBeSaved());
    emit SetSelectAllState(!_ui->textEdit->toPlainText().isEmpty());
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

void TabPage::updateSatusBar()
{
    emit UpdateStatusBar(GetCurrentLineIndex(), GetCountOfCharsInLeftOfCursor());
}
