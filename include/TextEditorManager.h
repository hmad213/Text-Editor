#ifndef TEXTEDITORMANAGER_H
#define TEXTEDITORMANAGER_H

#include "TextEditor.h"
#include "mainwindow.h"
#include <QObject>
class MainWindow;

class TextEditorManager : public QObject {
    Q_OBJECT

private:
    TextEditor* textEditor;
    MainWindow* mainWindow;

public:
    TextEditorManager();
    ~TextEditorManager();

    // Core functionality methods
    void insertChar(char c);
    void deleteChar();
    void deleteCharFront();
    void moveCursor(int x, int y);
    void setCursorPosition(int line, int column);
    std::string getText();
    void run();

    void saveToFile(const string& filePath);
    void loadFromFile(const string& filePath);
private:
    void updateDisplay();
};

#endif