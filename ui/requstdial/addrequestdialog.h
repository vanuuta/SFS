#ifndef ADDREQUESTDIALOG_H
#define ADDREQUESTDIALOG_H

#include <QDialog>

namespace Ui {
class AddRequestDialog;
}

class AddRequestDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddRequestDialog(QWidget *parent = nullptr);
    ~AddRequestDialog();

    int studentId() const;
    int departmentId() const;
    QString message() const;
    QString status() const;

private:
    Ui::AddRequestDialog *ui;
};

#endif // ADDREQUESTDIALOG_H
