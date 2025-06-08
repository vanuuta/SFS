#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QSqlTableModel>
#include "user.h"
#include "adduserdialog.h"

namespace Ui {
class AdminWindow;
}

class AdminWindow : public QWidget
{
    Q_OBJECT

public:
    explicit AdminWindow(const User& user, QWidget *parent = nullptr);
    ~AdminWindow();
signals:
    void userAdded();  // сигнал об успешном добавлении

private slots:
    void on_addUserButton_clicked();
    void on_deleteUserButton_clicked();
    void on_roleFilterComboBox_currentIndexChanged(int index);
    void on_saveChangesButton_clicked();

private:
    Ui::AdminWindow *ui;
    QSqlTableModel* model;

    void loadUsers();
};

#endif // ADMINWINDOW_H
