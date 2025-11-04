#include "TextEditor.h"

TextEditor::TextEditor(){
    nodeIndex = 0;
    lineIndex = 0;
    currentNode = nullptr;
    DoublyLinkedList<char>* newList = new DoublyLinkedList<char>;
    text.insertAtHead(newList);
    currentLineNode = text[0];
}

TextEditor::~TextEditor(){
    Node<DoublyLinkedList<char>*>* currentLine = text[0];
    
    while (currentLine != nullptr) {
        DoublyLinkedList<char>* line = currentLine->value;
        if (line != nullptr) {
            delete line;
        }
        currentLine = currentLine->next;
    }
}

void TextEditor::insertChar(char value){

}

void TextEditor::insertString(string value){

}

void TextEditor::removeChar(){

}

void TextEditor::addNewLine(){

}

void TextEditor::removeLine(){

}

string TextEditor::getText(){
    string text = "";
    Node<char>* newNode = text[0][0];
}