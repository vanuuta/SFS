#include "addrequestdialog.h"
#include "ui_addrequestdialog.h"

AddRequestDialog::AddRequestDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddRequestDialog)
{
    ui->setupUi(this);

    // Статусы заявок
    ui->statusComboBox->addItems({"новая", "в работе", "выполнена", "отклонена"});
}

// AddRequestDialog::~AddRequestDialog()
// {
//     delete ui;
// }

// int AddRequestDialog::studentId() const
// {
//     return ui->studentIdSpinBox->value();
// }

// int AddRequestDialog::departmentId() const
// {
//     return ui->departmentIdSpinBox->value();
// }

// QString AddRequestDialog::message() const
// {
//     return ui->messageLineEdit->text();
// }

// QString AddRequestDialog::status() const
// {
//     return ui->statusComboBox->currentText();
// }
