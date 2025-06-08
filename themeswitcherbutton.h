// ThemeToggleButton.h
#pragma once
#include <QPushButton>
#include <QApplication>
#include <QFile>

class ThemeToggleButton : public QPushButton {
    Q_OBJECT
public:
    explicit ThemeToggleButton(QWidget* parent = nullptr);

private slots:
    void toggleTheme();

private:
    bool darkMode = true;
    void applyTheme(bool dark);
};
