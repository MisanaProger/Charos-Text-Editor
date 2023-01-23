#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTabBar>
#include <QDebug>
#include <QCloseEvent>
#include <QDialogButtonBox>
#include "startpage.h"
#include "tabpage.h"
#include "statusbar.h"
#include "savefiledialog.h"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // tab widget
    void closeTab(int index);
    void onTabChanged(int index);

    // File menu
    void openFile();
    void newFile();
    void save();
    bool saveAs();
    void closeCurrentTab();

    // Edit menu
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void selectAll();

    // View menu
    void showStatusBar(bool val);
    void wrapWords(bool val);

    void updateTitle(QString title = "");
    void showStartPage();
    void hideStartPage();

private:
    void connectNewTabPage(TabPage *tab);
    void closeEvent(QCloseEvent *event) override;
    TabPage *getCurrentPage();

private:
    Ui::MainWindow *_ui;
    StartPage *_startPage;
    StatusBar *_statusBar;

    // Settings
    QTextOption::WrapMode _wrapMode = QTextOption::NoWrap;
};
#endif // MAINWINDOW_H
