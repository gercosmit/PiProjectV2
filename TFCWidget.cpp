#include "TFCWidget.h"
#include "ui_TFCWidget.h"
#include <QGraphicsEllipseItem>


TFCWidget::TFCWidget(QNetworkAccessManager* manager, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TFCWidget),
    manager(manager)
{
	ui->setupUi(this);
    ui->tsViewer->setFont(QFont("Arial", 16));

	UpdateTFC();
	timer = new QTimer(this);
	connect(timer, SIGNAL(timeout()), this, SLOT(UpdateTFC()));
    timer->start(10000);
}

TFCWidget::~TFCWidget()
{
	delete ui;
}

void TFCWidget::UpdateTFC()
{
    networkReplyMutex.lock();
    QNetworkReply *reply = manager->get(QNetworkRequest(QUrl("https://discord.com/api/guilds/728951156927365222/widget.json")));
    connect(reply, &QNetworkReply::finished, this, &TFCWidget::ReplyFinished);
    networkReplyMutex.unlock();
}

void TFCWidget::ReplyFinished()
{
    networkReplyMutex.lock();
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (reply)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            //QString discordInfoRawString(reply->readAll());

            QString discordInfoRawString;
            while (!reply->atEnd())
            {
                discordInfoRawString.append(reply->read(1024));
            }

            if (!discordInfoRawString.isEmpty())
            {
                QJsonObject discordInfo;
                QJsonDocument doc = QJsonDocument::fromJson(discordInfoRawString.toUtf8());
                if(!doc.isNull())
                {
                    if(doc.isObject())
                    {
                        ui->tsViewer->clear();
                        discordInfo = doc.object();

                        if (!discordInfo["channels"].isNull() && !discordInfo["members"].isNull())
                        {
                            auto discordServer = DiscordServer(discordInfo["channels"].toArray(), discordInfo["members"].toArray());
                            PrintOutChannels(discordServer);
                            CheckForJohn(discordInfo["members"].toArray());
                        }
                    }
                }
            }

        }
        else
        {
            auto networkerror = static_cast<int>(reply->error());
            ui->tsViewer->clear();
            ui->tsViewer->append(QString("NetworkError %1").arg(networkerror));
        }
        reply->deleteLater();
    }
    networkReplyMutex.unlock();
}

void TFCWidget::CheckForJohn(QJsonArray memberArray)
{
    bool johnDetected = false;
    for (auto member : memberArray)
    {
        auto username = member.toObject()["username"].toString();

        if (username.compare("SlackAlice") == 0)
        {
          johnDetected = true;
        }
    }
    if (johnDetected)
    {
        JohnAlert();
    }
    else
    {
        CoastClear();
    }
}

void TFCWidget::PrintOutChannels(DiscordServer discordServer)
{
    for (auto &channel : discordServer.channels)
    {
        if (channel.Size() > 0)
        {
            ui->tsViewer->setFontPointSize(32);
            ui->tsViewer->append(channel.name);
            ui->tsViewer->setFontPointSize(16);
            for (auto &user : channel.users)
            {
                ui->tsViewer->append(user.username);
            }
        }
    }
}

void TFCWidget::JohnAlert()
{
    auto scene = new QGraphicsScene();

    const int DIAMETER = 300;
    auto circle = new QGraphicsEllipseItem(0, 0, DIAMETER, DIAMETER);
    circle->setBrush(Qt::red);

    auto text = new QGraphicsTextItem("JOHN ALERT!", circle);
    text->setFont(QFont("Arial", 32));
    text->setPos(QPoint(5.0,120.0));

    scene->addItem(circle);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}

void TFCWidget::CoastClear()
{
    auto scene = new QGraphicsScene();

    const int DIAMETER = 300;
    auto circle = new QGraphicsEllipseItem(0, 0, DIAMETER, DIAMETER);
    circle->setBrush(Qt::green);

    auto text = new QGraphicsTextItem("All ok", circle);
    text->setFont(QFont("Arial", 32));
    text->setPos(QPoint(85.0,120.0));

    scene->addItem(circle);

    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
}
