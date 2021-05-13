#include "SonosWidget.h"
#include "ui_SonosWidget.h"

SonosWidget::SonosWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::SonosWidget)
{
	ui->setupUi(this);
}

SonosWidget::~SonosWidget()
{
	delete ui;
}
