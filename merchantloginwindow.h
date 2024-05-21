#ifndef MERCHANTLOGINWINDOW_H
#define MERCHANTLOGINWINDOW_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlError>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QDebug>
#include <QPainter>
#include <QStyleOption>


namespace Ui {
class MerchantLoginWindow;
}

class MerchantLoginWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MerchantLoginWindow(QWidget *parent = nullptr);
    ~MerchantLoginWindow();
    void showMerchantWidget(); // 显示主界面
    void connectsql();
    int id;
    void paintEvent(QPaintEvent *e);

private slots:
    void on_loginButton_clicked();
    void on_exitButton_clicked();

signals:
    void loginSucceeded();

private:
    Ui::MerchantLoginWindow *ui;
    QSqlDatabase db;
};

#endif // MERCHANTLOGINWINDOW_H
