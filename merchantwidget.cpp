#include "merchantwidget.h"
#include "ui_merchantwidget.h"

MerchantWidget::MerchantWidget(int m_id,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MerchantWidget)
{
    this->id = m_id;
    ui->setupUi(this);

}

MerchantWidget::~MerchantWidget()
{
    delete ui;
}
