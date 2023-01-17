#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QTabBar>
#include <QDebug>
#include <QCloseEvent>
#include <QDialogButtonBox>
#include "tabpage.h"
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
    void closeTab(int index);
    void openFile();
    void newFile();
    void onTabChanged(int index);
    void save();
    void closeCurrentTab();
    bool saveAs();
    void undo();
    void redo();
    void cut();
    void copy();
    void paste();
    void updateTitle(QString title = "");
    void selectAll();

    void exitEditMode();

private:
    void connectNewTabPage(TabPage *tab);
    void closeEvent(QCloseEvent *event) override;
    TabPage *getCurrentPage();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
