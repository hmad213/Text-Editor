#include <iostream>
#include "TextEditor.h"
#include "mainwindow.h"
using namespace std;

class TextEditorManager{
    private:
        TextEditor* textEditor;
        MainWindow* mainWindow;
    public:
        TextEditorManager();
        ~TextEditorManager();
        
        void insertChar(char c, int line, int pos);
        
        void deleteChar(int line, int pos);
        
        std::string getText();
        
        void run();
};