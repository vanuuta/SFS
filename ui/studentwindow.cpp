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

    auto* topBarLayout = new QHBoxLayout;


    themeToggleButton = new ThemeToggleButton();
    themeToggleButton->setIcon(QIcon("sun.png"));
    themeToggleButton->setIconSize(QSize(24, 24));
    themeToggleButton->setFixedSize(36, 36);
    themeToggleButton->setFlat(true);
    topBarLayout->addStretch(); // Чтобы кнопка ушла вправо
    topBarLayout->addWidget(themeToggleButton);
    // themeToggleButton->setStyleSheet("background: red;");

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

    // QFile styleFile(isDark ? "dark.qss" : ":light.qss");
    // if (styleFile.open(QFile::ReadOnly)) {
    //     QString style = styleFile.readAll();
    //     qApp->setStyleSheet(style);
    //     styleFile.close();
    // }


    // qDebug() << ;
    // QString pwd = isDark ? "moon.png" : "sun.png";
    // QIcon icon(pwd);
    // if (icon.isNull()) {
    //     qDebug() << "Icon load failed!";
    // } else {
    //     qDebug() << "Icon loaded successfully!";
    // }

    // themeToggleButton->setIcon(icon);
}



void StudentWindow::on_WaitingQueuePushButton_clicked() {
    openWaitingQueue();
    // WaitingQueue* wq = new WaitingQueue(this);
    // auto wqw = new WaitingQueueWindow(wq, this);
    // wqw->show();
}

void StudentWindow::on_SelfOrganizingQueuePushButton_clicked() {
    QPoint point = this->pos();
    SelfOrganizingQueue* soq = new SelfOrganizingQueue(this);
    auto soqw = new SelfOrganizingQueueWindow(soq, this);
    soqw->setGeometry(point.x() + 100, point.y() + 400, 200, 200);
    soqw->show();
}
void StudentWindow::on_OrderQueuePushButton_clicked() {
    OrderQueue* oq = new OrderQueue(this);
    auto oqw = new OrderQueueWindow(oq, this);
    oqw->show();
}

void StudentWindow::openWaitingQueue()
{
    auto* window = new ConsultationRequestWindow(user.username, this);
    window->show();
}
