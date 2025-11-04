#include "main.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);  // Create QApplication first
    
    TextEditorManager manager;
    manager.run();
    
    return app.exec();  // Start the event loop
}