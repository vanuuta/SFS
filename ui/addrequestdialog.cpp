#include "addrequestdialog.h"
#include "ui_addrequestdialog.h"

addrequestdialog::addrequestdialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addrequestdialog)
{
    ui->setupUi(this);
    ui->statusComboBox->addItems({"новая", "в работе", "выполнена", "отклонена"});

}

addrequestdialog::~addrequestdialog()
{
    delete ui;
}
