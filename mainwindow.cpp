#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    connect(ui->actionSave_as, &QAction::triggered, this, &MainWindow::saveAs);
    connect(ui->actionUndo, &QAction::triggered, this, &MainWindow::undo);
    connect(ui->actionRedo, &QAction::triggered, this, &MainWindow::redo);
    connect(ui->actionCopy, &QAction::triggered, this, &MainWindow::copy);
    connect(ui->actionPaste, &QAction::triggered, this, &MainWindow::paste);
    connect(ui->actionCut, &QAction::triggered, this, &MainWindow::cut);
    connect(ui->actionSelect_all, &QAction::triggered, this, &MainWindow::selectAll);
    connect(ui->actionClose, &QAction::triggered, this, &MainWindow::closeCurrentTab);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);
    exitEditMode();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openFile()
{
    TabPage *page = TabPage::OpenFile(QFileDialog::getOpenFileName(this, "Open doc"), this);
    if (page == nullptr)
        return;
    connectNewTabPage(page);
    ui->tabWidget->insertTab(ui->tabWidget->currentIndex() + 1, page, page->GetFileName());
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex() + 1);
}

void MainWindow::newFile()
{
    qDebug() << "New file";
    TabPage *page = TabPage::NewFile(this);
    connectNewTabPage(page);
    ui->tabWidget->insertTab(ui->tabWidget->currentIndex() + 1, page, page->GetFileName());
    ui->tabWidget->setCurrentIndex(ui->tabWidget->currentIndex() + 1);
}

void MainWindow::onTabChanged(int index)
{
    ui->actionClose->setEnabled(ui->tabWidget->count());
    if (!ui->tabWidget->count())
        return exitEditMode();

    getCurrentPage()->Activate();
    updateTitle(getCurrentPage()->GetFileName());
    ui->actionSave_as->setEnabled(true);
    ui->actionPaste->setEnabled(true);
}

void MainWindow::save()
{
    getCurrentPage()->SaveFile(getCurrentPage()->GetFilePath());
}

void MainWindow::closeCurrentTab()
{
    closeTab(ui->tabWidget->currentIndex());
}

/// @brief
/// retunrs true if any path was selected in file dialog
/// @return
bool MainWindow::saveAs()
{
    QString path = QFileDialog::getSaveFileName(this, "Save file");
    if (path.isEmpty())
        return false;
    getCurrentPage()->SaveFile(path);
    return true;
}

void MainWindow::undo()
{
    getCurrentPage()->Undo();
}

void MainWindow::redo()
{
    getCurrentPage()->Redo();
}

void MainWindow::cut()
{
    getCurrentPage()->Cut();
}

void MainWindow::copy()
{
    getCurrentPage()->Copy();
}

void MainWindow::paste()
{
    getCurrentPage()->Paste();
}

void MainWindow::updateTitle(QString title)
{
    setWindowTitle(title + " Charos Text Editor");
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(), title);
}

void MainWindow::selectAll()
{
    getCurrentPage()->SelectAll();
}

void MainWindow::exitEditMode()
{
    ui->actionSave->setEnabled(false);
    ui->actionSave_as->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    ui->actionCopy->setEnabled(false);
    ui->actionPaste->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionSelect_all->setEnabled(false);
    ui->actionClose->setEnabled(false);
    updateTitle();
}

void MainWindow::connectNewTabPage(TabPage *tab)
{
    connect(tab, &TabPage::SetUndoState, ui->actionUndo, &QAction::setEnabled);
    connect(tab, &TabPage::SetRedoState, ui->actionRedo, &QAction::setEnabled);
    connect(tab, &TabPage::SetCopyAndCutState, ui->actionCut, &QAction::setEnabled);
    connect(tab, &TabPage::SetCopyAndCutState, ui->actionCopy, &QAction::setEnabled);
    connect(tab, &TabPage::SetSaveState, ui->actionSave, &QAction::setEnabled);
    connect(tab, &TabPage::SetSelectAllState, ui->actionSelect_all, &QAction::setEnabled);
    connect(tab, &TabPage::UpdateTitle, this, &MainWindow::updateTitle);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!ui->tabWidget->count())
        return;
    QList<TabPage *> pages;
    for (int i = 0; i < ui->tabWidget->count(); i++)
        if (qobject_cast<TabPage *>(ui->tabWidget->widget(i))->NeedToBeSaved())
            pages.append(qobject_cast<TabPage *>(ui->tabWidget->widget(i)));
    if (pages.empty())
        return;
    SaveFileDialog dialog(pages, this);
    if (!dialog.exec())
        return event->ignore();
    event->accept();
}

TabPage *MainWindow::getCurrentPage()
{
    return qobject_cast<TabPage *>(ui->tabWidget->currentWidget());
}

void MainWindow::closeTab(int index)
{
    if (getCurrentPage()->NeedToBeSaved())
    {
        switch (QMessageBox::question(this, "Save file question", "Do you want to save file?",
                                      QMessageBox::StandardButton::Save | QMessageBox::StandardButton::Discard | QMessageBox::StandardButton::Cancel,
                                      QMessageBox::StandardButton::Save))
        {
        case QMessageBox::StandardButton::Save:
            if (getCurrentPage()->CanBeSaved())
            {
                save();
                break;
            }
            if (!saveAs())
                return;
            break;
        case QMessageBox::StandardButton::Cancel:
            return;
        default:
            break;
        }
    }
    ui->tabWidget->removeTab(index);
}
