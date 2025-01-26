#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtNetwork>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void SendMessage();


private slots://槽函数
    void on_sendButton_clicked();
    void ReadMessage();

private:
    Ui::MainWindow *ui;
    QString text1;//用一个数据存储发送的内容（发送的内容一般是以字符串的形式，故用QString）
    QString text2;//用于存储接受到的信息
    QUdpSocket *sender;//用于发送数据
    QUdpSocket *receiver;//用于存储接受数据
};
#endif // MAINWINDOW_H
