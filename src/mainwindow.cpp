#include "mainwindow.h"

TextDisplayWidget::TextDisplayWidget(QWidget *parent) 
    : QWidget(parent)
{
    setFocusPolicy(Qt::StrongFocus);
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

void TextDisplayWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    painter.fillRect(rect(), Qt::white);
    
    painter.setPen(Qt::gray);
    painter.drawRect(rect().adjusted(0, 0, -1, -1));

    painter.setPen(Qt::black);
    painter.drawText(rect().adjusted(5, 5, -5, -5), Qt::TextWordWrap, m_text);
}

void TextDisplayWidget::keyPressEvent(QKeyEvent *event)
{
    QKeyEvent* newEvent = new QKeyEvent(
        QEvent::KeyPress,
        event->key(),
        event->modifiers(),
        event->text(),
        event->isAutoRepeat(),
        event->count()
    );
    QCoreApplication::postEvent(parent(), newEvent);
}

void TextDisplayWidget::mousePressEvent(QMouseEvent *event)
{
    setFocus();
    QWidget::mousePressEvent(event);
}

// MainWindow implementation
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TextEditor)
    , textDisplayWidget(nullptr)
    , currentText("")
{
    ui->setupUi(this);
    
    textDisplayWidget = new TextDisplayWidget();
    ui->verticalLayout->replaceWidget(ui->textArea, textDisplayWidget);
    delete ui->textArea;
    ui->textArea = textDisplayWidget;

    textDisplayWidget->setFocus();
    
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

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    emit keyPressed(event);
    
    QMainWindow::keyPressEvent(event);
}