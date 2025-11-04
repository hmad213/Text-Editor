#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TextEditor)
{
    ui->setupUi(this);
    
    connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);
    connect(ui->actionAbout, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, tr("About Application"),
                          tr("This is a text editor application made by:\nMuhammad Hammad 24k-0602\nAliyan Masood 24k-1007"));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}