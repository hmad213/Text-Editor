#pragma once

#include "TextEditor.h"
#include "mainwindow.h"
#include <QApplication>
#include <QClipboard>
class MainWindow;

class TextEditorManager{
    private:
        TextEditor* textEditor;
        MainWindow* mainWindow;

    public:
        TextEditorManager();
        ~TextEditorManager();
        void initializeEditor();

        void insertChar(char c);

        void deleteChar();
        void deleteCharFront();

        void moveCursor(int x, int y);
        void setCursorPosition(int line, int column);

        std::string getText();

        void saveToFile(const string& filePath);
        void loadFromFile(const string& filePath);

        void startSelection();
        void updateSelection();
        void clearSelection();
        std::string getSelectedText();
        Selection getSelectionDetails();
        bool hasSelection();

        void copyToClipboard();
        void cutToClipboard();
        void pasteFromClipboard();

        void updateDisplay();
        void run();
};