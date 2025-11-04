#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "ui_texteditor.h"
#include <QMessageBox>
#include <QAction>

namespace Ui {
class TextEditor;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

    private:
        Ui::TextEditor *ui;
};

#endif