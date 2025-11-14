#include "mainwindow.h"

MainWindow::MainWindow(TextEditorManager* manager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TextEditor)
    , editorManager(manager)
    , currentText("")
    , cursorLine(0)
    , cursorColumn(0)
{
    ui->setupUi(this);
    
    textDisplayWidget = new TextDisplayWidget(editorManager);
    ui->verticalLayout->replaceWidget(ui->textArea, textDisplayWidget);
    delete ui->textArea;
    ui->textArea = textDisplayWidget;

    textDisplayWidget->setFocus();
    
    connect(ui->actionNew, &QAction::triggered, this, &MainWindow::onNewFile);
    connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::onOpenFile);
    connect(ui->actionSave_As, &QAction::triggered, this, &MainWindow::onSaveFile);
    connect(ui->actionExit, &QAction::triggered, this, &QMainWindow::close);
    connect(ui->actionAbout, &QAction::triggered, this, [this]() {
        QMessageBox::about(this, tr("About Application"),
                          tr("This is a text editor application made by:\nMuhammad Hammad 24k-0602\nAliyan Masood 24k-1007"));
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setText(const string &text)
{
    currentText = QString::fromStdString(text);
    if (textDisplayWidget) {
        textDisplayWidget->setText(currentText);
    }
}

QString MainWindow::getText() const
{
    if (textDisplayWidget) {
        return textDisplayWidget->getText();
    }
    return currentText;
}

void MainWindow::setCursorPosition(int line, int column)
{
    cursorLine = line;
    cursorColumn = column;
    if (textDisplayWidget) {
        textDisplayWidget->setCursorPosition(line, column);
    }
}

void MainWindow::getCursorPosition(int &line, int &column) const
{
    line = cursorLine;
    column = cursorColumn;
}

void MainWindow::onSaveFile(){
    QString filePath = QFileDialog::getSaveFileName(
        this,
        "Save Text File",
        QDir::homePath(),
        "Text Files (*.txt);;All Files (*)"
    );
    
    if (!filePath.isEmpty()) {
        if (!filePath.endsWith(".txt", Qt::CaseInsensitive)) {
            filePath += ".txt";
        }
        
        if (editorManager) {
            editorManager->saveToFile(filePath.toStdString());
        }
    }
}

void MainWindow::onOpenFile(){
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "Open Text File",
        QDir::homePath(),
        "Text Files (*.txt);;All Files (*)"
    );
    
    if (!filePath.isEmpty()) {
        if (editorManager) {
            editorManager->loadFromFile(filePath.toStdString());
        }
    }
}

void MainWindow::onNewFile(){
    if(editorManager){
        editorManager->initializeEditor();
    }
}

TextDisplayWidget::TextDisplayWidget(TextEditorManager* manager, QWidget *parent) 
    : QWidget(parent)
    , editorManager(manager)
    , cursorLine(0)
    , cursorColumn(0)
    , cursorVisible(true)
    , selecting(false)
    , font("Consolas", 14)
{
    setFocusPolicy(Qt::StrongFocus);
    font.setStyleHint(QFont::TypeWriter);
    setCursor(Qt::IBeamCursor);

    setMouseTracking(true);
    
    // Setup cursor blink timer
    connect(&cursorTimer, &QTimer::timeout, this, &TextDisplayWidget::blinkCursor);
    cursorTimer.start(500); // Blink every 500ms 
}

void TextDisplayWidget::setText(const QString &text)
{
    this->text = text;
    update();
}

QString TextDisplayWidget::getText() const
{
    return text;
}

void TextDisplayWidget::setCursorPosition(int line, int column)
{
    cursorLine = line;
    cursorColumn = column;
    cursorVisible = true;
    cursorTimer.start(500); // Reset blink timer
    update();
}

void TextDisplayWidget::getCursorPosition(int &line, int &column) const
{
    line = cursorLine;
    column = cursorColumn;
}

void TextDisplayWidget::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Set font
    painter.setFont(font);
    QFontMetrics fm(font);
    
    // Draw background
    painter.fillRect(rect(), Qt::white);
    
    // Draw border
    painter.setPen(Qt::gray);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
    
    // Draw text and selection
    QStringList lines = text.split('\n');
    int y = 5 + fm.ascent();
    
    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines[i];
        int x = 5;
        
        int startLine, startCol, endLine, endCol;
        getSelectionBounds(startLine, startCol, endLine, endCol);
        // Draw selection background and text for this line
        if (editorManager && editorManager->hasSelection() && i >= startLine && i <= endLine) {      
            int selStart = (i == startLine) ? startCol : 0;
            int selEnd = (i == endLine) ? endCol : line.length();
            if(endCol == 0 && i == endLine || startCol == line.size()){
                painter.setPen(Qt::black);
                painter.drawText(x, y, line);
            }
            else if (selStart < selEnd) {
                QString beforeSelection = line.left(selStart);
                QString selectionText = line.mid(selStart, selEnd - selStart);
                QString afterSelection = line.mid(selEnd);
                
                int selX = x + fm.horizontalAdvance(beforeSelection);
                int selWidth = fm.horizontalAdvance(selectionText);
                
                // Draw blue background for selection
                painter.fillRect(selX, y - fm.ascent(), selWidth, fm.height(), 
                                QColor(51, 103, 209)); // Light blue background
                
                painter.setPen(Qt::black);
                painter.drawText(x, y, beforeSelection);
                
                painter.setPen(Qt::white);
                painter.drawText(selX, y, selectionText);
                
                // Draw text after selection (black)
                painter.setPen(Qt::black);
                int afterX = selX + selWidth;
                painter.drawText(afterX, y, afterSelection);
            }
        }else{
            painter.setPen(Qt::black);
            painter.drawText(x, y, line);
        }


        // Draw cursor
        if (i == cursorLine && cursorVisible) {
            QString textBeforeCursor = line.left(cursorColumn);
            int cursorX = x + fm.horizontalAdvance(textBeforeCursor);
            
            painter.setPen(QPen(Qt::black, 2));
            painter.drawLine(cursorX, y - fm.ascent(), cursorX, y + fm.descent());
        }
        
        y += fm.height();
    }
    
    // Draw cursor at end if no text
    if (lines.isEmpty() && cursorLine == 0 && cursorColumn == 0 && cursorVisible) {
        painter.setPen(QPen(Qt::black, 2));
        painter.drawLine(5, 5, 5, 5 + fm.height());
    }
}

QPoint TextDisplayWidget::getCursorCoordinates() const
{
    QFontMetrics fm(font);
    QStringList lines = text.split('\n');
    
    int x = 5;
    int y = 5;
    
    if (cursorLine < lines.size()) {
        QString line = lines[cursorLine];
        QString textBeforeCursor = line.left(cursorColumn);
        x += fm.horizontalAdvance(textBeforeCursor);
    }
    
    y += cursorLine * fm.height() + fm.ascent();
    
    return QPoint(x, y);
}

void TextDisplayWidget::blinkCursor()
{
    cursorVisible = !cursorVisible;
    update();
}

void TextDisplayWidget::keyPressEvent(QKeyEvent *event)
{
    if (!editorManager) {
        QWidget::keyPressEvent(event);
        return;
    }

    if (event->modifiers() & (Qt::AltModifier | Qt::MetaModifier)) {
        QWidget::keyPressEvent(event);
        return;
    }

    if (event->modifiers() & Qt::ControlModifier) {
        switch (event->key()) {
            case Qt::Key_C:
                editorManager->copyToClipboard();
                return;
            case Qt::Key_V:
                editorManager->pasteFromClipboard();
                return;
            case Qt::Key_X:
                editorManager->cutToClipboard();
                return;
        }
    }

    switch (event->key()) {
        case Qt::Key_Backspace:
            editorManager->deleteChar();
            break;
        case Qt::Key_Left:
            editorManager->moveCursor(-1, 0);
            break;
        case Qt::Key_Up:
            editorManager->moveCursor(0, -1);
            break;
        case Qt::Key_Down:
            editorManager->moveCursor(0, 1);
            break;
        case Qt::Key_Right:
            editorManager->moveCursor(1, 0);
            break;
        case Qt::Key_Return:
            editorManager->insertChar('\n');
            break;
        case Qt::Key_Enter:
            editorManager->insertChar('\n');
            break;
        case Qt::Key_Tab:
            editorManager->insertChar('\t');
            break;
        case Qt::Key_Delete:
            editorManager->deleteCharFront();
            break;
        default:
            if (!event->text().isEmpty() && event->text().at(0).isPrint()) {
                editorManager->insertChar(event->text().at(0).toLatin1());
            }
            break;
    }
}

void TextDisplayWidget::mousePressEvent(QMouseEvent *event){
    if (!editorManager) {
        QWidget::mousePressEvent(event);
        return;
    }

    if (event->button() == Qt::LeftButton) {
        // Calculate click position
        QFontMetrics fm(font);
        QStringList lines = text.split('\n');
        
        int clickY = event->pos().y();
        int line = qBound(0, (clickY - 5) / fm.height(), lines.size() - 1);
        
        int clickX = event->pos().x() - 5;
        QString lineText = lines.value(line, "");
        
        int column = 0;
        int currentWidth = 0;
        for (int i = 0; i < lineText.length(); ++i) {
            int charWidth = fm.horizontalAdvance(lineText[i]);
            if (currentWidth + charWidth / 2 > clickX) {
                break;
            }
            currentWidth += charWidth;
            column++;
        }
        
        // Start selection
        editorManager->setCursorPosition(line, column);
        editorManager->startSelection();
        selecting = true;
        selectionStart = event->pos();
        
        setFocus();
        update();
    }
    
    QWidget::mousePressEvent(event);
}



void TextDisplayWidget::mouseMoveEvent(QMouseEvent *event){
    if (selecting && editorManager) {
        selectionEnd = event->pos();
        
        // Calculate current mouse position
        QFontMetrics fm(font);
        QStringList lines = text.split('\n');
        
        int clickY = event->pos().y();
        int line = qBound(0, (clickY - 5) / fm.height(), lines.size() - 1);
        
        int clickX = event->pos().x() - 5;
        QString lineText = lines.value(line, "");
        
        int column = 0;
        int currentWidth = 0;
        for (int i = 0; i < lineText.length(); ++i) {
            int charWidth = fm.horizontalAdvance(lineText[i]);
            if (currentWidth + charWidth / 2 > clickX) {
                break;
            }
            currentWidth += charWidth;
            column++;
        }
        
        // Update selection and cursor
        editorManager->setCursorPosition(line, column);
        editorManager->updateSelection();
        update();
    }
    
    QWidget::mouseMoveEvent(event);
}

void TextDisplayWidget::mouseReleaseEvent(QMouseEvent *event){
    if (event->button() == Qt::LeftButton && selecting) {
        selecting = false;
    }
    
    QWidget::mouseReleaseEvent(event);
}

void TextDisplayWidget::getSelectionBounds(int &startLine, int &startCol, int &endLine, int &endCol) const {
    Selection s = editorManager->getSelectionDetails();

    if(s.startLine > s.endLine || (s.startLine == s.endLine && s.startNode > s.endNode)){
        swap(s.startLine, s.endLine);
        swap(s.startNode, s.endNode);
    }

    startLine = s.startLine;
    startCol = s.startNode;
    endLine = s.endLine;
    endCol = s.endNode;
}