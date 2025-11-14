#pragma once

#include <iostream>
#include "DoublyLinkedList.hpp"
using namespace std;

struct Selection{
    bool isSelecting;
    int startLine;
    int startNode;
    int endLine;
    int endNode;

    Selection() : isSelecting(false), startLine(0), startNode(0), endLine(0), endNode(0){}
};

class TextEditor{
    private:
        DoublyLinkedList<DoublyLinkedList<char>*> text;
        Node<char>* currentNode;
        Node<DoublyLinkedList<char>*>* currentLineNode;
        int nodeIndex;
        int lineIndex;
        Selection selection;
    public:
        TextEditor();
        ~TextEditor();
        void initialize();

        void overwriteText(string value);

        void insertChar(char value);
        void insertString(string value);

        void removeChar();
        void removeCharFront();

        void addNewLine();
        void removeLine();

        void moveCursor(int x, int y);

        void setCursorPosition(int lineIndex, int nodeIndex);

        void startSelection();
        void updateSelection();
        void endSelection();
        void deleteSelection();
        string getSelectedText();
        Selection getSelectionDetails();
        bool hasSelection();

        string getText();
        int getLineIndex();
        int getNodeIndex();
};