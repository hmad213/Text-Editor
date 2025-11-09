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
    nodeIndex++;
    cout << lineIndex << ", " << nodeIndex << endl;
}

// TODO: loop through the string and use insertChar to insert all the characters.
// Specical case: \n. Use addNewLine()
void TextEditor::insertString(string value){

}

void TextEditor::removeChar(){
    if(!currentNode) return;
    currentNode = currentLineNode->value->removeFromNode(currentNode);
    if(!currentNode) nodeIndex--;
    nodeIndex--;
    cout << lineIndex << ", " << nodeIndex << endl;
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
        cout << "Moving cursor: " << x << ", " << y << endl;
    
    // Handle vertical movement first
    if (y != 0) {
        int newLineIndex = lineIndex + y;
        
        // Boundary check for vertical movement
        if (newLineIndex < 0) newLineIndex = 0;
        if (newLineIndex >= text.getSize()) newLineIndex = text.getSize() - 1;
        
        if (newLineIndex != lineIndex) {
            lineIndex = newLineIndex;
            currentLineNode = text[lineIndex];
            
            // Adjust horizontal position for the new line
            DoublyLinkedList<char>* newLine = currentLineNode->value;
            int newLineLength = newLine->getSize();
            
            if (nodeIndex > newLineLength) {
                // If current horizontal position is beyond new line length, go to end
                nodeIndex = newLineLength;
                currentNode = newLine->getTail();
            } else {
                // Try to maintain similar horizontal position
                if (nodeIndex == 0) {
                    currentNode = nullptr; // At start of line
                } else if (nodeIndex == newLineLength) {
                    currentNode = newLine->getTail(); // At end of line
                } else {
                    currentNode = (*newLine)[nodeIndex];
                }
            }
        }
    }
    
    // Handle horizontal movement
    if (x != 0) {
        DoublyLinkedList<char>* currentLine = currentLineNode->value;
        int lineLength = currentLine->getSize();
        
        if (x > 0) {
            // Move right
            for (int i = 0; i < x; i++) {
                if (nodeIndex < lineLength) {
                    // Move right within current line
                    if (currentNode == nullptr) {
                        // At start of line, move to first character
                        currentNode = currentLine->getHead();
                    } else {
                        currentNode = currentNode->next;
                    }
                    nodeIndex++;
                } else if (currentLineNode->next != nullptr) {
                    // Move to next line
                    lineIndex++;
                    currentLineNode = currentLineNode->next;
                    currentLine = currentLineNode->value;
                    lineLength = currentLine->getSize();
                    currentNode = nullptr; // Start of new line
                    nodeIndex = 0;
                }
                // Else can't move further right
            }
        } else {
            // Move left
            for (int i = 0; i < -x; i++) {
                if (nodeIndex > 0) {
                    // Move left within current line
                    if (currentNode == nullptr) {
                        // This shouldn't happen if nodeIndex > 0
                        currentNode = currentLine->getTail();
                    } else {
                        currentNode = currentNode->prev;
                    }
                    nodeIndex--;
                } else if (currentLineNode->prev != nullptr) {
                    // Move to previous line
                    lineIndex--;
                    currentLineNode = currentLineNode->prev;
                    currentLine = currentLineNode->value;
                    lineLength = currentLine->getSize();
                    currentNode = currentLine->getTail(); // End of previous line
                    nodeIndex = lineLength;
                }
                // Else can't move further left
            }
        }
    }
    
    cout << "New cursor position: " << lineIndex << ", " << nodeIndex << endl;
}

void TextEditor::setCursorPosition(int lineIndex, int nodeIndex){
    if (lineIndex < 0) lineIndex = 0;
    if (lineIndex >= text.getSize()) lineIndex = text.getSize() - 1;
    
    currentLineNode = text[lineIndex];
    this->lineIndex = lineIndex;
    
    DoublyLinkedList<char>* currentLine = currentLineNode->value;
    if (nodeIndex < 0) nodeIndex = 0;
    if (nodeIndex > currentLine->getSize()) nodeIndex = currentLine->getSize();
    
    currentNode = (*currentLineNode->value)[nodeIndex];
    this->nodeIndex = nodeIndex;
    
    cout << this->lineIndex << ", " << this->nodeIndex << endl;
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

int TextEditor::getLineIndex(){
    return lineIndex;
}

int TextEditor::getNodeIndex(){
    return nodeIndex;
}