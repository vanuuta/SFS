#include <QDialog>
#include <QSqlTableModel>
#include <QStandardItemModel>
#include "ui_waitingqueuewindow.h"
#include "db/queuemanager.h"

namespace Ui {
class WaitingQueueWindow;
}

class WaitingQueueWindow : public QDialog
{
    Q_OBJECT

public:
    explicit WaitingQueueWindow(QWidget *parent = nullptr);
    ~WaitingQueueWindow();

private slots:
    void on_addButton_clicked();
    void on_removeButton_clicked();
    void on_refreshButton_clicked();

private:
    Ui::WaitingQueueWindow *ui;
    QSqlTableModel* model;
    void setupModel();
    void showStatusMessage(const QString& message);
};


