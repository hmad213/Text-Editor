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
#include <QTimer>

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

    // Cursor position methods
    void setCursorPosition(int line, int column);
    void getCursorPosition(int &line, int &column) const;

signals:
    void keyPressed(QKeyEvent* event);

protected:
    void keyPressEvent(QKeyEvent *event) override;

private:
    Ui::TextEditor *ui;
    TextDisplayWidget *textDisplayWidget;
    QString currentText;
    int cursorLine;
    int cursorColumn;
};

// Custom widget class declared in header
class TextDisplayWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextDisplayWidget(QWidget *parent = nullptr);
    
    void setText(const QString &text);
    QString getText() const;
    
    void setCursorPosition(int line, int column);
    void getCursorPosition(int &line, int &column) const;

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private slots:
    void blinkCursor();

private:
    QString m_text;
    int m_cursorLine;
    int m_cursorColumn;
    bool m_cursorVisible;
    QTimer m_cursorTimer;
    QFont m_font;
    
    QPoint getCursorCoordinates() const;
    void updateCursorBlink();
};

#endif