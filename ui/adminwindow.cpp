#include "adminwindow.h"
#include "ui_adminwindow.h"

AdminWindow::AdminWindow(const User& user, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
}

AdminWindow::~AdminWindow()
{
    delete ui;
}
