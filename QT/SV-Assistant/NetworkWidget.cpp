#include "NetworkWidget.h"

NetworkWidget::NetworkWidget()
{
	QPalette pal(this->palette());
	//���ñ���whiteɫ
	pal.setColor(QPalette::Background, Qt::white);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	this->Init();
}

NetworkWidget::NetworkWidget(QWidget *parent)
	: QWidget(parent)
{
	QPalette pal(this->palette());
	//���ñ���whiteɫ
	pal.setColor(QPalette::Background, Qt::white);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	this->Init();
}

void NetworkWidget::Init()
{

}

NetworkWidget::~NetworkWidget()
{
}
