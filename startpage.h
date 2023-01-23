#ifndef STARTPAGE_H
#define STARTPAGE_H

#include <QWidget>

namespace Ui
{
    class StartPage;
}

class StartPage : public QWidget
{
    Q_OBJECT

public:
    explicit StartPage(QWidget *parent = nullptr);
    ~StartPage();

signals:
    void open();
    void newFile();

private slots:
    void openPressed();
    void newPressed();

private:
    Ui::StartPage *_ui;
};

#endif // STARTPAGE_H
