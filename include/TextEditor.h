#pragma once
#include <iostream>
#include "DoublyLinkedList.hpp"
using namespace std;

class TextEditor{
    private:
        DoublyLinkedList<DoublyLinkedList<char>*> text;
        Node<char>* currentNode;
        Node<DoublyLinkedList<char>*>* currentLineNode;
        int nodeIndex;
        int lineIndex;
    public:
        TextEditor();
        ~TextEditor();

        void insertChar(char value);
        void insertString(string value);

        void removeChar();

        void addNewLine();
        void removeLine();

        void moveCursor(int x, int y);

        string getText();
        int getLineIndex();
        int getNodeIndex();
};