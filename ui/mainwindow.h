#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QStandardItemModel>
#include <QMainWindow>
#include <QSqlTableModel>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void updateRequestTable();
private slots:
    // void onAddRequestClicked();

    void on_addRequestButton_clicked();

private:
    Ui::MainWindow *ui;
    QSqlTableModel * requestModel;
    // void loadRequests();

};
#endif // MAINWINDOW_H
