#include "HomeWidget.h"
#include "ui_HomeWidget.h"


HomeWidget::HomeWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::HomeWidget),
	rainDataChart(new RainDataChart(this))
{
	ui->setupUi(this);
    ui->weatherDataLayout->addWidget(rainDataChart);

	UpdateTime();
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(UpdateTime()));
	timer->start(500);
	
	manager = new QNetworkAccessManager(this);
	connect(manager, &QNetworkAccessManager::finished, this, &HomeWidget::ReplyFinished);
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
    replyRaindata = manager->get(QNetworkRequest(QUrl("https://br-gpsgadget.azurewebsites.net/data/raintext/?lat=52.29&lon=5.63")));
    networkReplyMutex.unlock();
}

void HomeWidget::ReplyFinished()
{
    networkReplyMutex.lock();
	if (replyRaindata)
	{
		if (replyRaindata->error() == QNetworkReply::NoError)
		{
            //QString RainValuesRaw(replyRaindata->readAll());

            QString RainValuesRaw;
            while (!replyRaindata->atEnd())
            {
                RainValuesRaw.append(replyRaindata->read(1024));
            }

            QStringList RainValues = RainValuesRaw.split(QRegExp("\\n"));
            if (RainValues.size() > 0)
            {
                rainDataChart->SetRainData(RainValues);
                rainDataChart->update();
            }
        }
		replyRaindata->deleteLater();
    }
    networkReplyMutex.unlock();
}
