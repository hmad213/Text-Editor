#include "TextEditorManger.h"

TextEditorManager::TextEditorManager() {
    textEditor = new TextEditor();
    mainWindow = new MainWindow();
}

TextEditorManager::~TextEditorManager() {
    delete textEditor;
    delete mainWindow;
}

void TextEditorManager::insertChar(char c, int line, int pos) {

}

void TextEditorManager::deleteChar(int line, int pos) {
    
}

string TextEditorManager::getText() {
    return textEditor->getText();
}

void TextEditorManager::run() {
    mainWindow->show();
}