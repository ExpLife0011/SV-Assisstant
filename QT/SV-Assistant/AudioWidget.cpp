#include "AudioWidget.h"

AudioWidget::AudioWidget()
{
	QPalette pal(this->palette());
	//���ñ���whiteɫ
	pal.setColor(QPalette::Background, Qt::white);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	this->Init();
}

AudioWidget::AudioWidget(QWidget *parent)
	: QWidget(parent)
{
	QPalette pal(this->palette());
	//���ñ���whiteɫ
	pal.setColor(QPalette::Background, Qt::white);
	this->setAutoFillBackground(true);
	this->setPalette(pal);
	this->Init();
}

void AudioWidget::Init()
{

}
AudioWidget::~AudioWidget()
{
}
