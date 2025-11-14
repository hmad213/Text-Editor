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

void TextEditorManager::initializeEditor(){
    textEditor->initialize();
    updateDisplay();
}

void TextEditorManager::insertChar(char c) {
    if(textEditor->hasSelection()){
        textEditor->deleteSelection();
    }
    if(c == '\n')
        textEditor->addNewLine();
    else
        textEditor->insertChar(c);
    updateDisplay();
}

void TextEditorManager::deleteChar() {
    if(textEditor->hasSelection()){
        textEditor->deleteSelection();
    }else{
        textEditor->removeChar();
    }
    updateDisplay();
}

void TextEditorManager::deleteCharFront(){
    if(textEditor->hasSelection()){
        textEditor->deleteSelection();
    }else{
        textEditor->removeCharFront();
    }
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

void TextEditorManager::startSelection(){
    textEditor->startSelection();
}

void TextEditorManager::updateSelection(){
    textEditor->updateSelection();
}

void TextEditorManager::clearSelection(){
    textEditor->endSelection();
}

std::string TextEditorManager::getSelectedText(){
    return textEditor->getSelectedText();
}

Selection TextEditorManager::getSelectionDetails(){
    return textEditor->getSelectionDetails();
}

bool TextEditorManager::hasSelection(){
    return textEditor->hasSelection();
}

void TextEditorManager::copyToClipboard() {
    if (textEditor->getSelectionDetails().isSelecting) {
        string selectedText = textEditor->getSelectedText();
        QApplication::clipboard()->setText(QString::fromStdString(selectedText));
    }
}

void TextEditorManager::cutToClipboard() {
    if (textEditor->getSelectionDetails().isSelecting) {
        string selectedText = textEditor->getSelectedText();
        QApplication::clipboard()->setText(QString::fromStdString(selectedText));
        
        textEditor->deleteSelection();
        updateDisplay();
    }
}

void TextEditorManager::pasteFromClipboard() {
    QString clipboardText = QApplication::clipboard()->text();
    if (!clipboardText.isEmpty()) {
        if (textEditor->hasSelection()) {
            textEditor->deleteSelection();
        }
        
        textEditor->insertString(clipboardText.toStdString());
        updateDisplay();
    }
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
    textEditor->overwriteText(data);
    updateDisplay();
}