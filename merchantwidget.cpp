#include "merchantwidget.h"
#include "ui_merchantwidget.h"

#include<QDebug>
#include<QMessageBox>


MerchantWidget::MerchantWidget(int m_id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MerchantWidget)
{
    this->id = m_id;
    ui->setupUi(this);
    connectsql();
    getMenu();



}

MerchantWidget::~MerchantWidget()
{
    delete ui;
}

void MerchantWidget::connectsql()
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

void MerchantWidget::getMenu()
{
    //从数据库中获取当前店铺的菜单
    QSqlDatabase db = QSqlDatabase::database();
    QSqlQuery query(db);

    query.exec(QString("SELECT d.dish_id, d.name, d.price, d.category_id, d.quantity FROM DishInMerchant dm JOIN Dish d ON dm.dish_id = d.dish_id WHERE dm.merchant_id =%1").arg(id));

    while (query.next()) {
        // 创建菜品对象
        Food food;
        food.id = query.value("dish_id").toInt();
        food.name = query.value("name").toString();
        food.price = query.value("price").toDouble();
        food.category_id = query.value("category_id").toInt();
        food.quantity = query.value("quantity").toInt();

        // 将菜品对象添加到当前店铺的菜单列表中
        menu.push_back(food);

    }

    QStringList headtext;
    headtext<<"序号"<<"奶茶名"<<"价格"<<"库存"<<"操作";
    ui->milkTeaTableWidget->setColumnCount(headtext.count());     //列表设置为和headtext相等
    ui->milkTeaTableWidget->setHorizontalHeaderLabels(headtext);  //插入表头
    ui->milkTeaTableWidget->setRowCount(0);
    // 设置选择模式为整行选择
    ui->milkTeaTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->milkTeaTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    // 调整表头，使其适应内容
    ui->milkTeaTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // 获取表头
    QHeaderView *header = ui->milkTeaTableWidget->horizontalHeader();

    // 设置表头字体
    header->setFont(QFont("Arial", 12)); // 使用Arial字体，大小为12像素

    QStringList headtext1;
    headtext1<<"序号"<<"果茶名"<<"价格"<<"库存"<<"操作";
    ui->fruitTeaTableWidget->setColumnCount(headtext1.count());    //列表设置为和headtext相等
    ui->fruitTeaTableWidget->setHorizontalHeaderLabels(headtext1); //插入表头
    ui->fruitTeaTableWidget->setRowCount(0);
    // 设置选择模式为整行选择
    ui->fruitTeaTableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->fruitTeaTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    // 获取表头
    QHeaderView *header2 = ui->fruitTeaTableWidget->horizontalHeader();

    // 设置表头字体
    header2->setFont(QFont("Arial", 12)); // 使用Arial字体，大小为12像素

    // 调整表头，使其适应内容
    ui->fruitTeaTableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int j=0;j< menu.size();j++)
    {
        //QChar type = order->merchant.menu[j].number[0];    //A表示奶茶，B表示果茶

        if( menu[j].category_id==1)    //是奶茶
        {
            int rowcount = ui->milkTeaTableWidget->rowCount();
            ui->milkTeaTableWidget->insertRow(rowcount);
            QTableWidgetItem *column = new QTableWidgetItem(QString::number(menu[j].id));
            QTableWidgetItem *column1 = new QTableWidgetItem(menu[j].name);
            QTableWidgetItem *column2 = new QTableWidgetItem(QString::number(menu[j].price));
            QTableWidgetItem *column3 = new QTableWidgetItem(QString::number(menu[j].quantity));

            ui->milkTeaTableWidget->setItem(rowcount,0,column);
            ui->milkTeaTableWidget->setItem(rowcount,1,column1);
            ui->milkTeaTableWidget->setItem(rowcount,2,column2);
            ui->milkTeaTableWidget->setItem(rowcount,3,column3);
            //添加“添加至购物车”按钮
            QPushButton *addToCartButton = new QPushButton("添加至购物车");
//            connect(addToCartButton, &QPushButton::clicked, this, [=]() {
//                // 获取按钮所在的单元格
//                QPushButton* button = dynamic_cast<QPushButton*>(sender());
//                //                if (!button) {
//                //                    return; // 如果按钮无效，则退出槽函数
//                //                }

//                // 获取按钮所在的行号
//                int row = ui->milkTeaTableWidget->indexAt(button->pos()).row();
//                //qDebug()<<row;

//                addToCart(row,'A');
//                QMessageBox::information(this, "提示", "添加成功！");
//                // 更新总价钱显示
//                updateTotalPrice();
//            });// 调用槽函数，传入当前行号
            ui->milkTeaTableWidget->setCellWidget(rowcount,4,addToCartButton);
        }
        else
        {
            int rowcount = ui->fruitTeaTableWidget->rowCount();
            ui->fruitTeaTableWidget->insertRow(rowcount);
            QTableWidgetItem *column = new QTableWidgetItem(QString::number(menu[j].id));
            QTableWidgetItem *column1 = new QTableWidgetItem(menu[j].name);
            QTableWidgetItem *column2 = new QTableWidgetItem(QString::number(menu[j].price));
            QTableWidgetItem *column3 = new QTableWidgetItem(QString::number(menu[j].quantity));


            ui->fruitTeaTableWidget->setItem(rowcount,0,column);
            ui->fruitTeaTableWidget->setItem(rowcount,1,column1);
            ui->fruitTeaTableWidget->setItem(rowcount,2,column2);
            ui->fruitTeaTableWidget->setItem(rowcount,3,column3);
            //添加“添加至购物车”按钮
            QPushButton *addToCartButton = new QPushButton("添加至购物车");
//            connect(addToCartButton, &QPushButton::clicked, this, [=]() {
//                //qDebug()<<rowcount;
//                addToCart(rowcount,'B');
//                QMessageBox::information(this, "提示", "添加成功！");
//                // 更新总价钱显示
//                updateTotalPrice();
//            });// 调用槽函数，传入当前行号
            ui->fruitTeaTableWidget->setCellWidget(rowcount,4,addToCartButton);
        }
     }
}

