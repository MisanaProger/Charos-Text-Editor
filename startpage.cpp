#include "startpage.h"
#include "ui_startpage.h"

StartPage::StartPage(QWidget *parent) : QWidget(parent),
                                        _ui(new Ui::StartPage)
{
    _ui->setupUi(this);
    connect(_ui->open, &QPushButton::clicked, this, &StartPage::open);
    connect(_ui->new_2, &QPushButton::clicked, this, &StartPage::newFile);
}

StartPage::~StartPage()
{
    delete _ui;
}

void StartPage::openPressed()
{
    emit open();
}

void StartPage::newPressed()
{
    emit newFile();
}
