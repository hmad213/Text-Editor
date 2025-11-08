#pragma once
#include <iostream>
#include "TextEditor.h"
#include "mainwindow.h"
#include <QObject>
#include <QKeyEvent>
using namespace std;

class TextEditorManager : public QObject{

    Q_OBJECT

    private:
        TextEditor* textEditor;
        MainWindow* mainWindow;
    public:
        TextEditorManager();
        ~TextEditorManager();
        
        void insertChar(char c);
        void handleKeyPress(QKeyEvent *event);
        void deleteChar();
        
        std::string getText();
        
        void run();
        
        bool eventFilter(QObject *obj, QEvent *event) override;
};