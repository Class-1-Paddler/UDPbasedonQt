#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QByteArray>//进行网络传输时需要先全部转换为二进制

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sender=new QUdpSocket(this);
    receiver=new QUdpSocket(this);
    receiver->bind(45515,QUdpSocket::ShareAddress);
    //如果需要监听就需要绑定一个端口，绑定的内容就是端口，第二个是绑定主机，即绑定本机的45515端口
    connect(receiver, SIGNAL(readyRead()), this, SLOT(ReadMessage()));
    //SIGNAL是QUdpSocket中的信号，当有数据可供读取时会发射该信号
    //一旦有数据到达就会自动调用ReadMessage函数来处理接收到的数据
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SendMessage()
{
    text1=ui->textEdit->toPlainText();//将文本框中输入的内容传值给text1
    QByteArray datagram=text1.toUtf8();//将文本转换成二进制流再发出去，用Utf8编码可以实现中文的转换
    sender->writeDatagram(datagram.data(),datagram.size(),QHostAddress("192.168.0.116"),45515);
    //第一个参数是读数据内容，第二个是读取数据的大小，第三个是IP地址，第四个参数是目标端口
}

void MainWindow::ReadMessage()
{
    while(receiver->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(receiver->pendingDatagramSize());
        /*1.传文件时都需要先给大小再传文件
         * 2.为接收数据分配足够的空间（二进制流的空间）
         */
        receiver->readDatagram(datagram.data(),datagram.size());//接收数据

        //注意至此接收到的数据仍然为二进制数据，需要转换为文本
        text2.clear();
        text2.prepend(datagram);//添加内容（底层封装好转换为文本char的工具了）
        ui->label->setText(text2);//在UI上显示接收到的信息
    }
}

void MainWindow::on_sendButton_clicked()
{
    SendMessage();
}

