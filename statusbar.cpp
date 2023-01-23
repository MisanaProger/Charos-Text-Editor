#include "statusbar.h"
#include "ui_statusbar.h"

StatusBar::StatusBar(QWidget *parent) : QWidget(parent),
                                        _ui(new Ui::StatusBar)
{
    _ui->setupUi(this);
}

StatusBar::~StatusBar()
{
    delete _ui;
}

void StatusBar::Update(int line, int chars)
{
    _ui->lineLabel->setText(QString("Line: " + QString::number(line)));
    _ui->charsLable->setText(QString("Chars: " + QString::number(chars)));
}
