#include "HomeWidget.h"
#include "ui_HomeWidget.h"


HomeWidget::HomeWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::HomeWidget),
	rainDataChart(new RainDataChart(this))
{
	ui->setupUi(this);

	UpdateTime();
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(UpdateTime()));
	timer->start(500);
	
	manager = new QNetworkAccessManager(this);
	connect(manager, &QNetworkAccessManager::finished, this, &HomeWidget::ReplyFinished);
	UpdateRain();
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(UpdateRain()));
	timer->start(60000);
	
	ui->weatherDataLayout->addWidget(rainDataChart);
	
	rainDataChart->update();
}

HomeWidget::~HomeWidget()
{
	delete ui;
}

void HomeWidget::UpdateTime()
{
	ui->lbl_time->setText(QTime::currentTime().toString());
	ui->lbl_date->setText(QDate::currentDate().toString());
}



void HomeWidget::UpdateRain()
{
    replyRaindata = manager->get(QNetworkRequest(QUrl("https://gpsgadget.buienradar.nl/data/raintext/?lat=52.29&lon=5.63")));
}

void HomeWidget::ReplyFinished()
{
	if (replyRaindata)
	{
		if (replyRaindata->error() == QNetworkReply::NoError)
		{
			QString RainValuesRaw(replyRaindata->readAll());
			QStringList RainValues = RainValuesRaw.split(QRegExp("\\n"));
//					RainValues.clear(); // replace list with testdata on dry days
//					RainValues.append("020|18:05");
//					RainValues.append("030|18:05");
//					RainValues.append("040|18:05");
//					RainValues.append("050|18:05");
//					RainValues.append("100|18:05");
//					RainValues.append("150|18:05");
//					RainValues.append("200|18:05");
//					RainValues.append("255|18:05");
//					RainValues.append("500|18:05");
//					RainValues.append("180|18:05");
//					RainValues.append("166|18:05");
//					RainValues.append("120|18:05");
//					RainValues.append("080|18:05");
//					RainValues.append("075|18:05");
//					RainValues.append("075|18:05");
//					RainValues.append("075|18:05");
//					RainValues.append("075|18:05");
//					RainValues.append("065|18:05");
//					RainValues.append("050|18:05");
//					RainValues.append("040|18:05");
//					RainValues.append("020|18:05");
//					RainValues.append("-99|18:05");
//					RainValues.append("000|18:05");
//					RainValues.append("040|18:05");
					rainDataChart->SetRainData(RainValues);
			rainDataChart->update();
        }
		replyRaindata->deleteLater();
    }
}
