#include "mainwindow.h"
#include <QStatusBar>
#include <QFont>
#include <QToolBar>
#include <QDebug>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //字体
    QFont font;
    font.setFamily("Consolas");
    font.setStyleHint(QFont::Monospace);
    font.setFixedPitch(true);
    font.setPointSize(10);

    //窗口设置
    setWindowTitle("编程猫");
    setWindowIcon(QIcon(":/Image/favicon.ico"));
    resize(300, 200);
    setMinimumSize(300, 200);

    //工具栏
    QToolBar* toolBar = new QToolBar();
    toolBar->setMovable(false);
    addToolBar(Qt::TopToolBarArea, toolBar);
    //1.保存
    QAction* saveBtn = toolBar->addAction("保存");
    QAction* clearBtn = toolBar->addAction("清空");


    //状态栏
    QStatusBar* statusList = statusBar();
    setStatusBar(statusList);
    //1.字符计算
    this->countLabel = new QLabel("字符：0",this);
    statusList->addWidget(countLabel);

    //中心控件
    this->textEdit = new QTextEdit(this);
    setCentralWidget(textEdit);
    textEdit->setFont(font);

    //键盘输入
    connect(textEdit,&QTextEdit::textChanged,this,&MainWindow::calcInputCount);

    //点击保存
    connect(saveBtn,&QAction::triggered,this,&MainWindow::saveInput);

    //点击清空
    connect(clearBtn,&QAction::triggered,this,&MainWindow::clearInput);
}

void MainWindow::calcInputCount()
{
     int count = this->textEdit->toPlainText().length();
     this->countLabel->setText("字符：" + QString::number(count));
}

void MainWindow::clearInput()
{
     this->textEdit->clear();
}

void MainWindow::saveInput()
{
    QString fileName = QFileDialog::getSaveFileName(this, "保存文件", "/", "文本文件 (*.txt);;所有文件 (*)");
    if (fileName.isEmpty())
    {
        return;
    }
    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this, "提示", "无法保存文件: " + file.errorString());
        return;
    }
    QTextStream out(&file);
    out << this->textEdit->toPlainText();
    file.close();

    qDebug() << "文件保存到：" << fileName;
    QMessageBox::information(this, "提示", "文件已保存");
    this->clearInput();
}


MainWindow::~MainWindow()
{
}

