#include "TextEditorManger.h"

TextEditorManager::TextEditorManager() {
    textEditor = new TextEditor();
    mainWindow = new MainWindow();

    connect(mainWindow, &MainWindow::keyPressed, this, &TextEditorManager::handleKeyPress);

    if (mainWindow->getTextDisplayWidget()) {
        mainWindow->getTextDisplayWidget()->installEventFilter(this);
        mainWindow->getTextDisplayWidget()->setFocus();
    }
}

TextEditorManager::~TextEditorManager() {
    delete textEditor;
    delete mainWindow;
}

void TextEditorManager::insertChar(char c) {
    textEditor->insertChar(c);
    mainWindow->setText(textEditor->getText());
}

void TextEditorManager::deleteChar() {
    textEditor->removeChar();
    mainWindow->setText(textEditor->getText());
}

string TextEditorManager::getText() {
    return textEditor->getText();
}

void TextEditorManager::run() {
    mainWindow->show();
}

void TextEditorManager::handleKeyPress(QKeyEvent *event) {
    if (event->text().isEmpty()) {
        return;
    } else {
        switch (event->key()) {
            case Qt::Key_Backspace:
                deleteChar();
                return;
                break;
            case Qt::Key_Return:
                insertChar('\n');
                return;
            case Qt::Key_Enter:
                insertChar('\n');
                return;
                break;
            case Qt::Key_Tab:
                insertChar('\t');
                return;
                break;
        }

        QString text = event->text();
        if (!text.isEmpty()) {
            insertChar(text.at(0).toLatin1());
        }
    }
}

bool TextEditorManager::eventFilter(QObject *obj, QEvent *event) {
    if (event->type() == QEvent::KeyPress) {
        QKeyEvent *keyEvent = static_cast<QKeyEvent*>(event);
        handleKeyPress(keyEvent);
        return true;
    }
    return QObject::eventFilter(obj, event);
}