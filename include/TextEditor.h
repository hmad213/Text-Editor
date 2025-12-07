#pragma once

#include <iostream>
#include <algorithm>
#include "DynamicArray.hpp"
#include "Stack.hpp"
#include "DoublyLinkedList.hpp"
#include "Autocomplete.h"
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

        Autocomplete* autocomplete;

        Selection selection;
        Stack<Operation> undo;
    public:
        TextEditor();
        ~TextEditor();
        void initialize();
        //my functions
        void unchardel(Node<char>* ptr);
        void undooperation();

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

        DynamicArray<string> getAutocompleteSuggestions();
        void autocompleteText(string word);

        string getText();
        
        int getLineIndex();
        int getNodeIndex();
        string getPrefix();
};