#ifndef TABPAGE_H
#define TABPAGE_H

#include <QWidget>
#include <QFile>
#include <QTextDocument>
#include <QFileInfo>
#include <QStringList>
#include <QTextOption>
#include <QTextStream>

namespace Ui
{
    class TabPage;
}
struct TextEditState
{
    bool undoAvaliable = false;
    bool redoAvaliable = false;
    bool copyAvaliable = false;
};

class TabPage : public QWidget
{
    Q_OBJECT

signals:
    void SetUndoState(bool);
    void SetRedoState(bool);
    void SetCopyAndCutState(bool);
    void SetSaveState(bool);
    void SetSelectAllState(bool);
    void UpdateTitle(QString);
    void UpdateStatusBar(int line, int chars);

public:
    static TabPage *OpenFile(QString path, QWidget *parent);
    static TabPage *NewFile(QWidget *parent);

    void SaveFile(QString path);
    void Activate(QTextOption::WrapMode wrapMode);
    bool NeedToBeSaved();
    bool CanBeSaved();

    void Undo();
    void Redo();
    void Cut();
    void Copy();
    void Paste();
    void SelectAll();

    bool IsNew();
    QString GetFileName();
    QString GetFilePath();
    ~TabPage();

    int GetCurrentLineIndex();
    int GetCountOfCharsInLeftOfCursor();

private slots:
    void textEdited();
    void setUndoState(bool val);
    void setRedoState(bool val);
    void setCopyAndCutState(bool val);
    void updateSatusBar();

private:
    explicit TabPage(QWidget *parent = nullptr);
    QString _lastSavedContent;
    TextEditState _state;
    QFileInfo *_file;
    Ui::TabPage *_ui;
};

#endif // TABPAGE_H
