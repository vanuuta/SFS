#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QWidget>
#include <QSqlTableModel>
#include "user.h"


namespace Ui {
class StudentWindow;
}

class StudentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudentWindow(const User& user, QWidget *parent = nullptr);
    ~StudentWindow();

private slots:
    void on_addRequestButton_clicked();
    void on_refreshButton_clicked();

private:
    Ui::StudentWindow *ui;
    QSqlTableModel *requestModel;
    void setupModel(const User& user);
    void updateView();
};

#endif // STUDENTWINDOW_H
