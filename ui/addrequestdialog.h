#ifndef ADDREQUESTDIALOG_H
#define ADDREQUESTDIALOG_H

#include <QDialog>

namespace Ui {
class addrequestdialog;
}

class addrequestdialog : public QDialog
{
    Q_OBJECT

public:
    explicit addrequestdialog(QWidget *parent = nullptr);
    ~addrequestdialog();
    int studentId() const;
    int departmentId() const;
    QString message() const;
    QString status() const;

private:
    Ui::addrequestdialog *ui;
};

#endif // ADDREQUESTDIALOG_H
