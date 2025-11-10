#pragma once

#include "TextEditor.h"
#include "mainwindow.h"
class MainWindow;

class TextEditorManager{
    private:
        TextEditor* textEditor;
        MainWindow* mainWindow;

    public:
        TextEditorManager();
        ~TextEditorManager();

        void insertChar(char c);

        void deleteChar();
        void deleteCharFront();

        void moveCursor(int x, int y);
        void setCursorPosition(int line, int column);

        std::string getText();

        void saveToFile(const string& filePath);
        void loadFromFile(const string& filePath);

        void updateDisplay();
        void run();
};