#include "TextEditorManager.h"

TextEditorManager::TextEditorManager() {
    textEditor = new TextEditor();
    mainWindow = new MainWindow(this); // Pass 'this' to MainWindow
}

TextEditorManager::~TextEditorManager() {
    delete textEditor;
    delete mainWindow;
}

void TextEditorManager::insertChar(char c) {
    if(c == '\n')
        textEditor->addNewLine();
    else
        textEditor->insertChar(c);
    updateDisplay();
}

void TextEditorManager::deleteChar() {
    textEditor->removeChar();
    updateDisplay();
}

void TextEditorManager::deleteCharFront(){
    textEditor->removeCharFront();
    updateDisplay();
}

void TextEditorManager::moveCursor(int x, int y){
    textEditor->moveCursor(x, y);
    updateDisplay();
}

void TextEditorManager::setCursorPosition(int line, int column) {
    textEditor->setCursorPosition(line, column);
    updateDisplay();
}

string TextEditorManager::getText() {
    return textEditor->getText();
}

void TextEditorManager::run() {
    mainWindow->show();
}

void TextEditorManager::updateDisplay() {
    mainWindow->setText(textEditor->getText());
    mainWindow->setCursorPosition(textEditor->getLineIndex(), textEditor->getNodeIndex());
}

void TextEditorManager::saveToFile(const string& filePath){

}

void TextEditorManager::loadFromFile(const string& filePath){

}