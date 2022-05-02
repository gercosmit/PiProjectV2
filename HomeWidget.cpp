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
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(UpdateTime()));
	timer->start(500);

    GetRainData();
	timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(GetRainData()));
	timer->start(60000);
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
    networkReplyMutex.lock();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("https://br-gpsgadget.azurewebsites.net/data/raintext/?lat=52.29&lon=5.63")));
    connect(reply, &QNetworkReply::finished, this, &HomeWidget::ReplyFinished);
    networkReplyMutex.unlock();
}

void HomeWidget::ReplyFinished()
{
    networkReplyMutex.lock();
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (reply)
	{
        if (reply->error() == QNetworkReply::NoError)
		{
            //QString RainValuesRaw(replyRaindata->readAll());

            QString RainValuesRaw;
            while (!reply->atEnd())
            {
                RainValuesRaw.append(reply->read(1024));
            }

            QStringList RainValues = RainValuesRaw.split(QRegExp("\\n"));
            if (RainValues.size() > 0)
            {
                rainDataChart->SetRainData(RainValues);
                rainDataChart->update();
            }
        }
        reply->deleteLater();
    }
    networkReplyMutex.unlock();
}
