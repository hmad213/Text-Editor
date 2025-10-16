#include "mainwindow.h"
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    auto *button = new QPushButton("Hello, Qt!", this);
    setCentralWidget(button);
}

MainWindow::~MainWindow() {}