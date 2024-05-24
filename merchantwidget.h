#ifndef MERCHANTWIDGET_H
#define MERCHANTWIDGET_H

#include <QWidget>
#include <QSqlQuery>
#include <QSqlError>
#include<QSqlDatabase>
#include<QMessageBox>
#include<QDebug>
#include "structural.h"
#include<vector>
using namespace std;

namespace Ui {
class MerchantWidget;
}

class MerchantWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MerchantWidget(int m_id,QWidget *parent = nullptr);
    ~MerchantWidget();
    void getMenu();
    void connectsql();
    QString name;    //店铺名字
    QString locate;    //位置
    QString time;    //营业时间
    double distance;    //距离，单位：千米
    vector<Food> menu;  //店铺菜单
    int id;

private:
    Ui::MerchantWidget *ui;
    QSqlDatabase db;
};

#endif // MERCHANTWIDGET_H
