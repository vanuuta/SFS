#include "studentwindow.h"
#include "../themetogglebutton.h"
#include <QLayout>
StudentWindow::StudentWindow(const User& user, QWidget* parent)
    : QWidget(parent),  ui(new Ui::StudentWindow),  user(user)
{
    isDark = false;
    ui->setupUi(this);
    this->setWindowTitle("Кабинет студента");
    // setMinimumSize(600, 400);
    auto* mainLayout = new QVBoxLayout(this);

    this->setLayout(mainLayout); // Установим layout окну
    setMinimumSize(800, 600);    // Минимальный размер окна

    auto* topBarLayout = new QVBoxLayout;
    contentWidget = new QWidget(this);


    themeToggleButton = new ThemeToggleButton();
    themeToggleButton->setIcon(QIcon("sun.png"));
    themeToggleButton->setIconSize(QSize(24, 24));
    themeToggleButton->setFixedSize(36, 36);
    themeToggleButton->setFlat(true);
    topBarLayout->addStretch(); // Чтобы кнопка ушла вправо
    topBarLayout->addWidget(themeToggleButton);

    mainLayout->addWidget(ui->OrderQueuePushButton);
    mainLayout->addWidget(ui->SelfOrganizingQueuePushButton);
    mainLayout->addWidget(ui->WaitingQueuePushButton);

    mainLayout->addWidget(contentWidget);
    mainLayout->addLayout(topBarLayout);

    // welcomeLabel = new QLabel("Добро пожаловать, " + user.username);
    // welcomeLabel->setAlignment(Qt::AlignCenter);
    // mainLayout->addWidget(welcomeLabel);

    connect(themeToggleButton, &QPushButton::clicked, this, &StudentWindow::toggleTheme);
}
StudentWindow::~StudentWindow()
{
    delete ui;
}
void StudentWindow::toggleTheme()
{
    isDark = !isDark;
    if (isDark) {
        QFile f("dark.qss");
        if (f.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString style = f.readAll();
            qApp->setStyleSheet(style);
            f.close();
            themeToggleButton->setIcon(QIcon("moon.png"));
        } else {
            qDebug() << "Не удалось открыть dark.qss";
        }
    } else {
        qApp->setStyleSheet("");
        themeToggleButton->setIcon(QIcon("sun.png"));
    }
}



void StudentWindow::on_WaitingQueuePushButton_clicked() {
    clearContentWidget();
    openWaitingQueue();
}

void StudentWindow::on_SelfOrganizingQueuePushButton_clicked() {
    clearContentWidget();
    openSelfOrganizingQueue();
}

void StudentWindow::on_OrderQueuePushButton_clicked() {
    clearContentWidget();
    openOrderQueue();
}
void StudentWindow::openSelfOrganizingQueue(){
    auto* widget = new SelfOrganizingQueueWidget(user.username, this);
    ui->contentLayout->addWidget(widget);
}
void StudentWindow::openOrderQueue(){
    auto* widget = new OrderCertificateWidget(user, this);
    ui->contentLayout->addWidget(widget);
}
void StudentWindow::openWaitingQueue()
{
    auto* window = new ConsultationRequestWindow(user.username, this);
    ui->contentLayout->addWidget(window);
}
void StudentWindow::clearContentWidget()
{
    QLayoutItem* child;
    while ((child = ui->contentLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }
}
