#pragma once

#include <iostream>
#include <QMainWindow>
#include <QMessageBox>
#include <QAction>
#include <QPainter>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QCoreApplication>
#include <QFontMetrics>
#include <QDir>
#include <QFileDialog>

#include "ui_texteditor.h"
#include "TextEditorManager.h"

using namespace std;

class TextEditorManager;
class TextDisplayWidget;

namespace Ui {
class TextEditor;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    private:
        Ui::TextEditor *ui;
        TextDisplayWidget *textDisplayWidget;
        TextEditorManager* editorManager;
        QString currentText;
        int cursorLine;
        int cursorColumn;

    public:
        explicit MainWindow(TextEditorManager* manager = nullptr, QWidget *parent = nullptr);
        ~MainWindow();

        void setText(const string &text);
        QString getText() const;
        
        TextDisplayWidget* getTextDisplayWidget() const { return textDisplayWidget; }

        void setCursorPosition(int line, int column);
        void getCursorPosition(int &line, int &column) const;

    private slots:
        void onSaveFile();
        void onOpenFile();
        void onNewFile();
};

// Custom widget class declared in header
class TextDisplayWidget : public QWidget
{
    Q_OBJECT

    private:
        TextEditorManager* editorManager;
        QString text;
        int cursorLine;
        int cursorColumn;
        bool cursorVisible;
        QTimer cursorTimer;
        QFont font;
        bool selecting;
        QPoint selectionStart;
        QPoint selectionEnd;

        void getSelectionBounds(int &startLine, int &startCol, int &endLine, int &endCol) const;
        QPoint getCursorCoordinates() const;

    public:
        explicit TextDisplayWidget(TextEditorManager* manager = nullptr, QWidget *parent = nullptr);
        
        void setText(const QString &text);
        QString getText() const;
        
        void setCursorPosition(int line, int column);
        void getCursorPosition(int &line, int &column) const;

    protected:
        void paintEvent(QPaintEvent *event) override;
        void keyPressEvent(QKeyEvent *event) override;
        void mousePressEvent(QMouseEvent *event) override;
        void mouseMoveEvent(QMouseEvent *event) override;
        void mouseReleaseEvent(QMouseEvent *event) override;

    private slots:
        void blinkCursor();
};