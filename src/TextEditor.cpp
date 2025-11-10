#include "TextEditor.h"

TextEditor::TextEditor(){
    nodeIndex = 0;
    lineIndex = 0;
    currentNode = nullptr;
    DoublyLinkedList<char>* newList = new DoublyLinkedList<char>;
    text.insertAtHead(newList);
    currentLineNode = text.getHead();
}

TextEditor::~TextEditor(){
    Node<DoublyLinkedList<char>*>* currentLine = text.getHead();
    
    while (currentLine != nullptr) {
        DoublyLinkedList<char>* line = currentLine->value;
        if (line != nullptr) {
            delete line;
        }
        currentLine = currentLine->next;
    }
}


void TextEditor::insertString(string value) {
    // ✅ Clean up existing lines safely
    while (text.head != nullptr) {
        DoublyLinkedList<char>* line = text.head->value;
        delete line;
        Node<DoublyLinkedList<char>*>* temp = text.head;
        text.head = text.head->next;
        delete temp;
    }
    text.tail = nullptr;

    // ✅ Reset editor state
    currentNode = nullptr;
    currentLineNode = nullptr;
    nodeIndex = 0;
    lineIndex = 0;

    // ✅ Ensure at least one line exists before inserting chars
    addNewLine();

    // ✅ Loop through all characters and handle newline
    for (char c : value) {
        if (c == '\n') {
            addNewLine();
        } else {
            insertChar(c);
        }
    }
  
    // ✅ Set cursor to beginning (or end, depending on desired behavior)
    currentLineNode = text.head;
    currentNode = currentLineNode ? currentLineNode->value->head : nullptr;
    lineIndex = 0;
    nodeIndex = 0;
}

void TextEditor::insertChar(char value){
    // uses insertAtNode in DoublyLinkedList
    currentNode = currentLineNode->value->insertAtNode(currentNode, value);
    nodeIndex++;
}

void TextEditor::removeChar(){
    // Special case: if cursor is at the start of line, remove the line
    if(!currentNode){
        removeLine();
        return;
    }

    // uses removeFromNode in DoublyLinkedList
    currentNode = currentLineNode->value->removeFromNode(currentNode);
    nodeIndex--;
}

void TextEditor::removeCharFront(){
    // TODO: add removing of line
    // Special case: if cursor is at the start of line, remove from head if it exists
    if(!currentNode){
        if(!currentLineNode->value->getHead()) return;
        currentLineNode->value->removeFromHead();
        return;                    
    }
    if(!currentNode->next) return;  // TODO: add removing of line

    // uses removeFromNode in DoublyLinkedList
    currentNode = currentLineNode->value->removeFromNode(currentNode->next);
}

void TextEditor::addNewLine(){
    // if cursor is at the start of line, create a new line and insert correctly
    if(nodeIndex <= 0){
        DoublyLinkedList<char>* newList = new DoublyLinkedList<char>;
        text.insertAtIndex(lineIndex, newList);
        lineIndex++;
    }else{
        // splitting of list into two and creating a new line when in middle of the string
        DoublyLinkedList<char>* newList = currentLineNode->value->splitList(nodeIndex - 1);
        text.insertAtNode(currentLineNode, newList);
        currentLineNode = currentLineNode->next;
        lineIndex++;
    }

    currentNode = nullptr;
    nodeIndex = 0;
}

void TextEditor::removeLine(){
    // condition to check if there are no lines before 
    if(lineIndex <= 0) return;

    // merging of current line with previous one to form a singular line

    Node<DoublyLinkedList<char>*>* prevLine = currentLineNode->prev;

    currentNode = prevLine->value->getTail();
    nodeIndex = prevLine->value->getSize();

    prevLine->value->mergeList(currentLineNode->value);

    text.removeFromNode(currentLineNode);

    lineIndex--;
    currentLineNode = prevLine;
}

void TextEditor::moveCursor(int x, int y){
    // for vertical
    if (y != 0) {
        int newLineIndex = lineIndex + y;
        
        // Boundary check
        if (newLineIndex < 0) newLineIndex = 0;
        if (newLineIndex >= text.getSize()) newLineIndex = text.getSize() - 1;
        
        if (newLineIndex != lineIndex) {
            lineIndex = newLineIndex;
            currentLineNode = text[lineIndex];
            
            // adjust horizontal position for the new line
            if(nodeIndex == 0)
                currentNode = nullptr;
            else
                currentNode = (*currentLineNode->value)[nodeIndex - 1]; // this gets the last element if node index > size

            if(currentNode == currentLineNode->value->getTail()){
                nodeIndex = currentLineNode->value->getSize();
            }
        }
    }
    
    // for horizontal
    if (x != 0) {
        int lineLength = currentLineNode->value->getSize();
        
        // for right
        if (x > 0) {
            for (int i = 0; i < x; i++) {
                if (nodeIndex < lineLength) {
                    // move right within current line
                    if (currentNode == nullptr) {
                        // if at start of line, move to first character
                        currentNode = currentLineNode->value->getHead();
                    } else {
                        currentNode = currentNode->next;
                    }
                    nodeIndex++;
                } else if (currentLineNode->next != nullptr) {
                    // move to next line
                    lineIndex++;
                    currentLineNode = currentLineNode->next;
                    lineLength = currentLineNode->value->getSize();
                    currentNode = nullptr; // start of new line
                    nodeIndex = 0;
                }
                // else can't move further right
            }
        } else {    // for left

            for (int i = 0; i < - x; i++) {
                if (nodeIndex > 0) {
                    // move left within current line
                    currentNode = currentNode->prev;
                    nodeIndex--;
                } else if (currentLineNode->prev != nullptr) {
                    // move to previous line
                    lineIndex--;
                    currentLineNode = currentLineNode->prev;
                    lineLength = currentLineNode->value->getSize();
                    currentNode = currentLineNode->value->getTail(); // end of previous line
                    nodeIndex = lineLength;
                }
                // else can't move further left
            }
        }
    }
    
}

void TextEditor::setCursorPosition(int lineIndex, int nodeIndex){
    // Vertical positioning
    // boundary check
    if (lineIndex < 0) lineIndex = 0;
    if (lineIndex >= text.getSize()) lineIndex = text.getSize() - 1;
    
    currentLineNode = text[lineIndex];
    this->lineIndex = lineIndex;
    
    //Horizontal positioning
    if (nodeIndex > currentLineNode->value->getSize()) nodeIndex = currentLineNode->value->getSize();
    
    if (nodeIndex <= 0) 
        currentNode = nullptr;
    else
        currentNode = (*currentLineNode->value)[nodeIndex - 1];
    this->nodeIndex = nodeIndex;
}

string TextEditor::getText(){
    string str = "";
    Node<DoublyLinkedList<char>*>* line = text[0];

    // traverse and extract each char
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

    return str;
}

int TextEditor::getLineIndex(){
    return lineIndex;
}

int TextEditor::getNodeIndex(){
    return nodeIndex;
}