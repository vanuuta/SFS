#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include "user.h"
namespace Ui {
class AdminWindow;
}

class AdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWindow(const User& user, QWidget *parent = nullptr);
    ~AdminWindow();

private:
    Ui::AdminWindow *ui;
};

#endif // ADMINWINDOW_H
