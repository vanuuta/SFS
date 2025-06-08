#ifndef TEACHERWINDOW_H
#define TEACHERWINDOW_H

#include <QWidget>
#include <QSqlTableModel>
#include "user.h"

namespace Ui {
class TeacherWindow;
}

class TeacherWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TeacherWindow(const User& user, QWidget *parent = nullptr);
    ~TeacherWindow();

private slots:
    void on_updateStatusButton_clicked();
    void on_filterComboBox_currentIndexChanged(int index);

private:
    Ui::TeacherWindow *ui;
    QSqlTableModel* requestModel;
    void setupModel(const User& user);
    void updateFilter();
};
#endif // TEACHERWINDOW_H
