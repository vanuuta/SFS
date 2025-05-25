#ifndef LOGINWINDOW_H
#define LOGINWINDOW_H

#include <QDialog>

namespace Ui {
class LoginWindow;
}

class LoginWindow : public QDialog
{
    Q_OBJECT

public:
    explicit LoginWindow(QWidget *parent = nullptr);
    ~LoginWindow();

private slots:
    void on_loginButton_clicked();
    void on_registerButton_clicked();


private:
    Ui::LoginWindow *ui;

    void authenticateUser(const QString &username, const QString &password);
};

#endif // LOGINWINDOW_H
