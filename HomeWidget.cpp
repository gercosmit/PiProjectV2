#include "HomeWidget.h"
#include "ui_HomeWidget.h"


HomeWidget::HomeWidget(QNetworkAccessManager* manager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWidget),
    manager(manager),
	rainDataChart(new RainDataChart(this))
{
	ui->setupUi(this);
    ui->weatherDataLayout->addWidget(rainDataChart);

	UpdateTime();
    timerTime = new QTimer(this);
    connect(timerTime, SIGNAL(timeout()), this, SLOT(UpdateTime()));
    timerTime->start(500);

    GetRainData();
    timerWeather = new QTimer(this);
    connect(timerWeather, SIGNAL(timeout()), this, SLOT(GetRainData()));
    timerWeather->start(60000);
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



void HomeWidget::GetRainData()
{
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("https://br-gpsgadget.azurewebsites.net/data/raintext/?lat=52.29&lon=5.63")));
    connect(reply, &QNetworkReply::finished, this, &HomeWidget::ReplyFinished);
}

void HomeWidget::ReplyFinished()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (reply)
	{
        if (reply->error() == QNetworkReply::NoError)
		{
            QString RainValuesRaw(reply->readAll());

            QStringList RainValues = RainValuesRaw.split(QRegExp("\\n"));
            if (RainValues.size() > 0)
            {
                rainDataChart->SetRainData(RainValues);
                rainDataChart->update();
            }
        }
        reply->deleteLater();
    }
}
