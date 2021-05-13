#include "TFCWidget.h"
#include "ui_TFCWidget.h"

TFCWidget::TFCWidget(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::TFCWidget)
{
	ui->setupUi(this);

	manager = new QNetworkAccessManager(this);
	connect(manager, &QNetworkAccessManager::finished, this, &TFCWidget::ReplyFinished);
	UpdateTFC();
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(UpdateTFC()));
	timer->start(60000);
}

TFCWidget::~TFCWidget()
{
	delete ui;
}

void TFCWidget::UpdateTFC()
{
	reply = manager->get(QNetworkRequest(QUrl("https://discordapp.com/api/guilds/728951156927365222/widget.json")));
}

void TFCWidget::ReplyFinished()
{
	if (!reply)
		return;

	if (reply->error() == QNetworkReply::NoError)
	{
		QString discordInfo(reply->readAll());

	}
	reply->deleteLater();
}