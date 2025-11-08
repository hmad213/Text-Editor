#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <iostream>
#include <QMainWindow>
#include "ui_texteditor.h"
#include <QMessageBox>
#include <QAction>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>

class TextDisplayWidget;

namespace Ui {
class TextEditor;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setText(const std::string &text);
    QString getText() const;
    
    TextDisplayWidget* getTextDisplayWidget() const { return textDisplayWidget; }

signals:
    void keyPressed(QKeyEvent* event);

protected:
    void keyPressEvent(QKeyEvent *event) override;  // Make sure this is here

private:
    Ui::TextEditor *ui;
    TextDisplayWidget *textDisplayWidget;
    QString currentText;
};

// Custom widget class declared in header
class TextDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextDisplayWidget(QWidget *parent = nullptr);
    
    void setText(const QString &text);
    QString getText() const;
    
protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    QString m_text;
};

#endif