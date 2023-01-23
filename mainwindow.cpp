#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), _ui(new Ui::MainWindow)
{
    _ui->setupUi(this);
    _startPage = new StartPage();
    _statusBar = new StatusBar();
    _ui->gridLayout->addWidget(_startPage);
    _ui->statusbar->addWidget(_statusBar);

    // tab widget
    connect(_ui->tabWidget, &QTabWidget::tabCloseRequested, this, &MainWindow::closeTab);
    connect(_ui->tabWidget, &QTabWidget::currentChanged, this, &MainWindow::onTabChanged);

    // Start page
    connect(_startPage, &StartPage::open, this, &MainWindow::openFile);
    connect(_startPage, &StartPage::newFile, this, &MainWindow::newFile);

    // tool bar
    // File
    connect(_ui->actionNew, &QAction::triggered, this, &MainWindow::newFile);
    connect(_ui->actionOpen, &QAction::triggered, this, &MainWindow::openFile);
    connect(_ui->actionSave, &QAction::triggered, this, &MainWindow::save);
    connect(_ui->actionSave_as, &QAction::triggered, this, &MainWindow::saveAs);
    connect(_ui->actionClose, &QAction::triggered, this, &MainWindow::closeCurrentTab);
    connect(_ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    // tool bar
    // Edit
    connect(_ui->actionUndo, &QAction::triggered, this, &MainWindow::undo);
    connect(_ui->actionRedo, &QAction::triggered, this, &MainWindow::redo);
    connect(_ui->actionCopy, &QAction::triggered, this, &MainWindow::copy);
    connect(_ui->actionPaste, &QAction::triggered, this, &MainWindow::paste);
    connect(_ui->actionCut, &QAction::triggered, this, &MainWindow::cut);
    connect(_ui->actionSelect_all, &QAction::triggered, this, &MainWindow::selectAll);

    // tool bar
    // View
    connect(_ui->actionAutohide_tab_bar, &QAction::toggled, _ui->tabWidget, &QTabWidget::setTabBarAutoHide);
    connect(_ui->actionShow_status_bar, &QAction::toggled, this, &MainWindow::showStatusBar);
    connect(_ui->actionWrap_line, &QAction::toggled, this, &MainWindow::wrapWords);

    showStartPage();
    _ui->statusbar->hide();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

void MainWindow::openFile()
{
    TabPage *page = TabPage::OpenFile(QFileDialog::getOpenFileName(this, "Open doc"), this);
    if (page == nullptr)
        return;
    connectNewTabPage(page);
    _ui->tabWidget->insertTab(_ui->tabWidget->currentIndex() + 1, page, page->GetFileName());
    _ui->tabWidget->setCurrentIndex(_ui->tabWidget->currentIndex() + 1);
    hideStartPage();
}

void MainWindow::newFile()
{
    qDebug() << "New file";
    TabPage *page = TabPage::NewFile(this);
    connectNewTabPage(page);
    _ui->tabWidget->insertTab(_ui->tabWidget->currentIndex() + 1, page, page->GetFileName());
    _ui->tabWidget->setCurrentIndex(_ui->tabWidget->currentIndex() + 1);
    hideStartPage();
}

void MainWindow::onTabChanged(int index)
{
    _ui->actionClose->setEnabled(_ui->tabWidget->count());
    if (!_ui->tabWidget->count())
        return showStartPage();

    getCurrentPage()->Activate(_wrapMode);
    updateTitle(getCurrentPage()->GetFileName());
    _ui->actionSave_as->setEnabled(true);
    _ui->actionPaste->setEnabled(true);
    _ui->actionShow_status_bar->setEnabled(true);
    showStatusBar(_ui->actionShow_status_bar->isChecked());
}

void MainWindow::save()
{
    getCurrentPage()->SaveFile(getCurrentPage()->GetFilePath());
}

void MainWindow::closeCurrentTab()
{
    closeTab(_ui->tabWidget->currentIndex());
}

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
    _ui->tabWidget->setTabText(_ui->tabWidget->currentIndex(), title);
}

void MainWindow::selectAll()
{
    getCurrentPage()->SelectAll();
}

void MainWindow::showStatusBar(bool val)
{
    if (val)
        _ui->statusbar->show();
    else
        _ui->statusbar->hide();
}

void MainWindow::wrapWords(bool val)
{
    if (val)
        _wrapMode = QTextOption::WordWrap;
    else
        _wrapMode = QTextOption::NoWrap;
    getCurrentPage()->Activate(_wrapMode);
}

void MainWindow::showStartPage()
{
    _ui->tabWidget->hide();
    _startPage->show();

    _ui->actionSave->setEnabled(false);
    _ui->actionSave_as->setEnabled(false);
    _ui->actionUndo->setEnabled(false);
    _ui->actionRedo->setEnabled(false);
    _ui->actionCopy->setEnabled(false);
    _ui->actionPaste->setEnabled(false);
    _ui->actionCut->setEnabled(false);
    _ui->actionSelect_all->setEnabled(false);
    _ui->actionClose->setEnabled(false);
    _ui->actionShow_status_bar->setEnabled(false);
    showStatusBar(false);
    updateTitle();
}

void MainWindow::hideStartPage()
{
    _ui->tabWidget->show();
    _startPage->hide();
}

void MainWindow::connectNewTabPage(TabPage *tab)
{
    connect(tab, &TabPage::SetUndoState, _ui->actionUndo, &QAction::setEnabled);
    connect(tab, &TabPage::SetRedoState, _ui->actionRedo, &QAction::setEnabled);
    connect(tab, &TabPage::SetCopyAndCutState, _ui->actionCut, &QAction::setEnabled);
    connect(tab, &TabPage::SetCopyAndCutState, _ui->actionCopy, &QAction::setEnabled);
    connect(tab, &TabPage::SetSaveState, _ui->actionSave, &QAction::setEnabled);
    connect(tab, &TabPage::SetSelectAllState, _ui->actionSelect_all, &QAction::setEnabled);
    connect(tab, &TabPage::UpdateTitle, this, &MainWindow::updateTitle);
    connect(tab, &TabPage::UpdateStatusBar, _statusBar, &StatusBar::Update);
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!_ui->tabWidget->count())
        return;
    QList<TabPage *> pages;
    for (int i = 0; i < _ui->tabWidget->count(); i++)
        if (qobject_cast<TabPage *>(_ui->tabWidget->widget(i))->NeedToBeSaved())
            pages.append(qobject_cast<TabPage *>(_ui->tabWidget->widget(i)));
    if (pages.empty())
        return;
    SaveFileDialog dialog(pages, this);
    if (!dialog.exec())
        return event->ignore();
    event->accept();
}

TabPage *MainWindow::getCurrentPage()
{
    return qobject_cast<TabPage *>(_ui->tabWidget->currentWidget());
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
    _ui->tabWidget->removeTab(index);
    if (!_ui->tabWidget->count())
        showStartPage();
}
