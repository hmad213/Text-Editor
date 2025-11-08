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
    currentNode = currentLineNode->value->insertAtNode(currentNode, value);
}

// TODO: loop through the string and use insertChar to insert all the characters.
// Specical case: \n. Use addNewLine()
void TextEditor::insertString(string value){

}

void TextEditor::removeChar(){
    currentNode = currentLineNode->value->removeFromNode(currentNode);
}

// TODO: add a new line. A line in this case is a new node of DoublyLinkedList<char>*. Make sure to dynamically allocate
// Special Case: Pressing enter in the middle of the line. use the function in DoublyLinkedList.hpp splitList
// Note: The splitList function is not completed.
void TextEditor::addNewLine(){

}

// TODO: remove a line. A line in this case is a new node of DoublyLinkedList<char>*.
// Special Case: Pressing backspace at the start of the line in which case it will merge this linked list with the previous one
// Note: The function has to be implemented in DoublyLinkedList.hpp
void TextEditor::removeLine(){

}

// TODO: adjusts the line depending on user input.
// Changing X: update currentNode and nodeIndex. 
// Special case for X: Moving x after end of line or before start of line
// Changing Y: update currentLineNode, lineIndex, and currentNode while also adjusting to nodeIndex. 
// Special case for Y: if nodeIndex exceeds possible nodeIndex in the new currentLineNode, then nodeIndex is at tail.
void TextEditor::moveCursor(int x, int y){

}

string TextEditor::getText(){
    string str = "";
    Node<DoublyLinkedList<char>*>* line = text[0];
    while(line != nullptr){
        Node<char>* cur = (*line->value)[0];
        while(cur != nullptr){
            str += cur->value;
            cur = cur->next;
        }
        line = line->next;
        if(line)
        str += '\n';
    }
    cout << str << endl;
    return str;
}