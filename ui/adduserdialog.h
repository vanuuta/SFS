#ifndef ADDUSERDIALOG_H
#define ADDUSERDIALOG_H

#include <QDialog>

namespace Ui {
class AddUserDialog;
}

class AddUserDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddUserDialog(QWidget *parent = nullptr);
    ~AddUserDialog();

signals:
    void userAdded();  // сигнал об успешном добавлении

private slots:
    void on_pushButtonAdd_clicked();

private:
    Ui::AddUserDialog *ui;
};

#endif // ADDUSERDIALOG_H
