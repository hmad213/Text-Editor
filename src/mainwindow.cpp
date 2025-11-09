#include "mainwindow.h"

// TextDisplayWidget implementation
TextDisplayWidget::TextDisplayWidget(TextEditorManager* manager, QWidget *parent) 
    : QWidget(parent)
    , editorManager(manager)
    , m_cursorLine(0)
    , m_cursorColumn(0)
    , m_cursorVisible(true)
    , m_font("Consolas", 14)
{
    setFocusPolicy(Qt::StrongFocus);
    m_font.setStyleHint(QFont::TypeWriter);
    setFont(m_font);
    setCursor(Qt::IBeamCursor);
    
    // Setup cursor blink timer
    connect(&m_cursorTimer, &QTimer::timeout, this, &TextDisplayWidget::blinkCursor);
    m_cursorTimer.start(500); // Blink every 500ms
}

void TextDisplayWidget::setText(const QString &text)
{
    m_text = text;
    update();
}

QString TextDisplayWidget::getText() const
{
    return m_text;
}

void TextDisplayWidget::setCursorPosition(int line, int column)
{
    m_cursorLine = line;
    m_cursorColumn = column;
    m_cursorVisible = true;
    m_cursorTimer.start(500); // Reset blink timer
    update();
}

void TextDisplayWidget::getCursorPosition(int &line, int &column) const
{
    line = m_cursorLine;
    column = m_cursorColumn;
}

void TextDisplayWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Set font
    painter.setFont(m_font);
    QFontMetrics fm(m_font);
    
    // Draw background
    painter.fillRect(rect(), Qt::white);
    
    // Draw border
    painter.setPen(Qt::gray);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));
    
    // Draw text
    painter.setPen(Qt::black);
    
    // Split text into lines and draw with cursor
    QStringList lines = m_text.split('\n');
    int y = 5 + fm.ascent();
    
    for (int i = 0; i < lines.size(); ++i) {
        QString line = lines[i];
        
        // Draw the line text
        painter.drawText(5, y, line);
        
        // Draw cursor if this is the current line and cursor is visible
        if (i == m_cursorLine && m_cursorVisible) {
            // Calculate cursor x position based on text width
            QString textBeforeCursor = line.left(m_cursorColumn);
            int cursorX = 5 + fm.horizontalAdvance(textBeforeCursor);
            
            // Draw cursor as a vertical line
            painter.setPen(QPen(Qt::black, 2));
            painter.drawLine(cursorX, y - fm.ascent(), cursorX, y + fm.descent());
            painter.setPen(Qt::black); // Reset pen for text
        }
        
        y += fm.height();
    }
    
    // Draw cursor at end if no text
    if (lines.isEmpty() && m_cursorLine == 0 && m_cursorColumn == 0 && m_cursorVisible) {
        painter.setPen(QPen(Qt::black, 2));
        painter.drawLine(5, 5, 5, 5 + fm.height());
    }
}

QPoint TextDisplayWidget::getCursorCoordinates() const
{
    QFontMetrics fm(m_font);
    QStringList lines = m_text.split('\n');
    
    int x = 5;
    int y = 5;
    
    if (m_cursorLine < lines.size()) {
        QString line = lines[m_cursorLine];
        QString textBeforeCursor = line.left(m_cursorColumn);
        x += fm.horizontalAdvance(textBeforeCursor);
    }
    
    y += m_cursorLine * fm.height() + fm.ascent();
    
    return QPoint(x, y);
}

void TextDisplayWidget::blinkCursor()
{
    m_cursorVisible = !m_cursorVisible;
    update();
}

void TextDisplayWidget::keyPressEvent(QKeyEvent *event)
{
    if (!editorManager) {
        QWidget::keyPressEvent(event);
        return;
    }

    // Handle key events directly with the manager
    if (event->modifiers() & (Qt::ControlModifier | Qt::AltModifier | Qt::MetaModifier)) {
        QWidget::keyPressEvent(event);
        return;
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

void TextDisplayWidget::mousePressEvent(QMouseEvent *event)
{
    if (!editorManager) {
        QWidget::mousePressEvent(event);
        return;
    }

    // Calculate cursor position from mouse click
    QFontMetrics fm(m_font);
    QStringList lines = m_text.split('\n');
    
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
    
    // Update cursor position through the text editor
    editorManager->setCursorPosition(line, column);
    setFocus();
    QWidget::mousePressEvent(event);
}

// MainWindow implementation
MainWindow::MainWindow(TextEditorManager* manager, QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TextEditor)
    , textDisplayWidget(nullptr)
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

void MainWindow::setText(const std::string &text)
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);
    QMainWindow::keyPressEvent(event);
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