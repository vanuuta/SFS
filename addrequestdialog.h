#ifndef ADDREQUESTDIALOG_H
#define ADDREQUESTDIALOG_H

#include <QWidget>

namespace Ui {
class addrequestdialog;
}

class addrequestdialog : public QWidget
{
    Q_OBJECT

public:
    explicit addrequestdialog(QWidget *parent = nullptr);
    ~addrequestdialog();
    int studentId() const;
private:
    Ui::addrequestdialog *ui;
};

#endif // ADDREQUESTDIALOG_H
