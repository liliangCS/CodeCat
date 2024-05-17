#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextEdit>
#include <QLabel>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QLabel* countLabel;
    QTextEdit* textEdit;

    MainWindow(QWidget *parent = nullptr);

    //计算输入字符数
    void calcInputCount();

    //清空输入字符
    void clearInput();

    //保存输入字符
    void saveInput();

    ~MainWindow();
};
#endif // MAINWINDOW_H
