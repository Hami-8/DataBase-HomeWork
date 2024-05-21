#include "merchantloginwindow.h"
#include "ui_merchantloginwindow.h"
#include <QMessageBox> // 弹出消息框的头文件
#include "merchantwidget.h"

MerchantLoginWindow::MerchantLoginWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MerchantLoginWindow)
{
    ui->setupUi(this);
    connectsql();
    // 连接退出按钮的点击事件到槽函数
    connect(ui->exitButton, &QPushButton::clicked, this, &MerchantLoginWindow::on_exitButton_clicked);
    //将登录成功信号连接至商户主界面
    connect(this, &MerchantLoginWindow::loginSucceeded, this,&MerchantLoginWindow::showMerchantWidget);

}

void MerchantLoginWindow::paintEvent(QPaintEvent *e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void MerchantLoginWindow::connectsql()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setHostName("127.0.0.1");
    db.setPort(3306);
    db.setDatabaseName("Mixue_64");
    db.setUserName("root");
    db.setPassword("abc000000");
    db.open();
    bool ok=db.open();
    if(ok)
    {
        qDebug()<<"数据库连接成功！";
    }
    else
    {
       QMessageBox::information(this,"infor", "link failed");
       qDebug()<<"error open database because"<<db.lastError().text();
    }
}

void MerchantLoginWindow::on_loginButton_clicked()
{
    // 获取商家用户名和密码
    QString username = ui->usernameLineEdit->text();
    QString password = ui->passwordLineEdit->text();

    //数据库中查找用户名和密码
    QSqlQuery query(db);
    query.exec(QString("select * from Merchant where username='%1' and password='%2'").arg(ui->usernameLineEdit->text()).arg(ui->passwordLineEdit->text()));  //建立查询
     if(query.next())
       {
        id=query.value(0).toString().toInt();
        qDebug() <<id;
        QMessageBox::information(this, "登录成功", "欢迎商家登录！");
        emit loginSucceeded();
       }
    else {
        QMessageBox::information(this,"infor", "登录失败，用户名或密码错误！");
    }
}

void MerchantLoginWindow::on_exitButton_clicked()
{
    // 点击退出按钮时，关闭窗口
    close();
}

void MerchantLoginWindow::showMerchantWidget()
{
    MerchantWidget *merchantWidget =new MerchantWidget(id);
    merchantWidget->show();
    this->close();
}


MerchantLoginWindow::~MerchantLoginWindow()
{
    delete ui;
}
