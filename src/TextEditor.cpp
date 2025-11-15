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

void TextEditor::initialize(){
    while (text.getHead() != nullptr) {
        text.removeFromHead();
    }

    nodeIndex = 0;
    lineIndex = 0;
    currentNode = nullptr;
    DoublyLinkedList<char>* newList = new DoublyLinkedList<char>;
    text.insertAtHead(newList);
    currentLineNode = text.getHead();
}

void TextEditor::overwriteText(string value){
    initialize();
    insertString(value);
}

void TextEditor::insertString(string value) {
    for (int i = 0; i < value.size(); i++) {
        if (value[i] == '\n') {
            addNewLine();
        } else {
            insertChar(value[i]);
        }
    }
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
        if(!currentLineNode->value->getHead() && currentLineNode->next){
            lineIndex++;
            currentLineNode = currentLineNode->next;
            removeLine();
        }
        if(currentLineNode->value->getHead())
            currentLineNode->value->removeFromHead();
        cout << getText();
        return;                    
    }
    if(!currentNode->next && currentLineNode->next){
        lineIndex++;
        currentLineNode = currentLineNode->next;
        removeLine();
        currentNode = currentLineNode->value->removeFromNode(currentNode->next);
    }

    // uses removeFromNode in DoublyLinkedList
    if(currentNode->next)
        currentNode = currentLineNode->value->removeFromNode(currentNode->next);
    cout << getText();
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

void TextEditor::startSelection(){
    selection.isSelecting = true;
    selection.startLine = lineIndex;
    selection.startNode = nodeIndex;
    selection.endLine = lineIndex;
    selection.endNode = nodeIndex;
}

void TextEditor::updateSelection(){
    if(selection.isSelecting){
        selection.endLine = lineIndex;
        selection.endNode = nodeIndex;
    }
}

void TextEditor::endSelection(){
    selection.isSelecting = false;
}

void TextEditor::deleteSelection(){
    if (!hasSelection()) return;


    int startLine = selection.startLine;
    int endLine = selection.endLine;
    int startNode = selection.startNode;
    int endNode = selection.endNode;

    if (startLine > endLine || (startLine == endLine && startNode > endNode)) {
        swap(startLine, endLine);
        swap(startNode, endNode);
    }

    setCursorPosition(startLine, startNode);

    int totalChars = 0;
    if (startLine == endLine) {
        totalChars = endNode - startNode;
    } else {
        Node<DoublyLinkedList<char>*>* line = text[startLine];
        for (int i = startLine; i <= endLine; i++) {
            int lineStart = (i == startLine) ? startNode : 0;
            int lineEnd = (i == endLine) ? endNode : line->value->getSize();
            totalChars += (lineEnd - lineStart);
            line = line->next;
        }
    }

    for (int i = 0; i < totalChars; i++) {
        removeCharFront();
    }

    selection.isSelecting = false;
}

string TextEditor::getSelectedText(){
    if (!hasSelection()) return "";

    string str = "";

    int startLine = selection.startLine;
    int endLine = selection.endLine;
    int startNode = selection.startNode;
    int endNode = selection.endNode;

    if (startLine > endLine || (startLine == endLine && startNode > endNode)) {
        swap(startLine, endLine);
        swap(startNode, endNode);
    }

    Node<DoublyLinkedList<char>*>* line = text[startLine];

    int i = startLine, j = startNode;
    while(i <= endLine && line != nullptr){
        int size = (*line->value).getSize();
        Node<char>* cur;
        if(j < size)
            cur = (*line->value)[j];
        else
            cur = nullptr;

        while(cur != nullptr && ((endLine != i) || (endLine == i && endNode > j))){
            str += cur->value;
            cur = cur->next;
            j++;
        }
        j = 0;
        i++;
        line = line->next;
        if(i <= endLine && line)
        str += '\n';
    }
    return str;
}

Selection TextEditor::getSelectionDetails(){
    return selection;
}

bool TextEditor::hasSelection(){
    return (selection.isSelecting && !(selection.startLine == selection.endLine & selection.startNode == selection.endNode));
}

int TextEditor::getLineIndex(){
    return lineIndex;
}

int TextEditor::getNodeIndex(){
    return nodeIndex;
}