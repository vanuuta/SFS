#ifndef STUDENTWINDOW_H
#define STUDENTWINDOW_H

#include <QWidget>

namespace Ui {
class StudentWindow;
}

class StudentWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StudentWindow(QWidget *parent = nullptr);
    ~StudentWindow();

private:
    Ui::StudentWindow *ui;
};

#endif // STUDENTWINDOW_H
