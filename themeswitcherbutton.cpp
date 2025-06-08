// ThemeToggleButton.cpp
#include "ThemeToggleButton.h"

ThemeToggleButton::ThemeToggleButton(QWidget* parent)
    : QPushButton(parent)
{
    setFixedSize(32, 32);
    setIcon(QIcon(":/resources/icons/moon.png"));
    setIconSize(QSize(24, 24));
    setFlat(true);

    connect(this, &QPushButton::clicked, this, &ThemeToggleButton::toggleTheme);
    applyTheme(true);
}

void ThemeToggleButton::toggleTheme() {
    darkMode = !darkMode;
    applyTheme(darkMode);
}

void ThemeToggleButton::applyTheme(bool dark) {
    QFile file(dark ? ":/styles/dark.qss" : ":/styles/light.qss");
    if (file.open(QFile::ReadOnly)) {
        qApp->setStyleSheet(QString(file.readAll()));
        setIcon(QIcon(dark ? ":/resources/icons/moon.png" : ":/resources/icons/sun.png"));
    }
}
