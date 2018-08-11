#include "GPUWidget.h"
#include "lib\Hardware\SV_Hardware.h"

GPUWidget::GPUWidget()
{
	QPalette pal(this->palette());
	//���ñ���whiteɫ
	pal.setColor(QPalette::Background, Qt::white);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	this->Init();
}

GPUWidget::GPUWidget(QWidget *parent)
	: QWidget(parent)
{
	QPalette pal(this->palette());
	//���ñ���whiteɫ
	pal.setColor(QPalette::Background, Qt::white);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	this->Init();
}

void GPUWidget::Init()
{

}

GPUWidget::~GPUWidget()
{
}
