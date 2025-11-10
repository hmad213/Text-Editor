#include "TextEditorManager.h"
#include <fstream>
#include <sstream>

TextEditorManager::TextEditorManager() {
    textEditor = new TextEditor();
    // passing pointer to mainWindow
    mainWindow = new MainWindow(this);
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
    string text= textEditor->getText();
    ofstream file(filePath,ios::out);
    if (file.is_open()) {
        file << text;
        file.close();
    } else {
        cout << "Error opening file.\n";
    }

}
void TextEditorManager::loadFromFile(const string& filePath){
    ifstream file(filePath,ios::in);
    if (!file.is_open()) {
    cout << "Error opening file.\n";
    return;
}
stringstream buffer;
buffer << file.rdbuf();
string data = buffer.str();
textEditor->insertString(data);
updateDisplay();
}