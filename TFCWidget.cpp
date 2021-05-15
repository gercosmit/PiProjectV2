#include "TFCWidget.h"
#include "ui_TFCWidget.h"
#include <QGraphicsEllipseItem>


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
    timer->start(10000);

    ui->tsViewer->setFont(QFont("Arial", 16));
}

TFCWidget::~TFCWidget()
{
	delete ui;
}

void TFCWidget::UpdateTFC()
{
    //JohnAlert();
    //CoastClear();
    reply = manager->get(QNetworkRequest(QUrl("https://discord.com/api/guilds/728951156927365222/widget.json")));
}

void TFCWidget::ReplyFinished()
{
    if (reply)
    {
        if (reply->error() == QNetworkReply::NoError)
        {
            QString discordInfoRawString(reply->readAll());
            QJsonObject discordInfo;
            QJsonDocument doc = QJsonDocument::fromJson(discordInfoRawString.toUtf8());
            if(!doc.isNull())
            {
                if(doc.isObject())
                {
                    ui->tsViewer->clear();
                    discordInfo = doc.object();
                    int amountOfShitters = discordInfo.value("presence_count").toInt(0);
                    ui->tsViewer->append(QString("There are %1 shitters online").arg(amountOfShitters));

                    QJsonArray memberArray = discordInfo["members"].toArray();
                    PrintOutShitters(memberArray);
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
}

void TFCWidget::PrintOutShitters(QJsonArray memberArray)
{
    bool johnDetected = false;
    for (int memberIndex = 0; memberIndex < memberArray.size(); ++memberIndex)
    {
        QJsonObject member = memberArray[memberIndex].toObject();
        auto username = member["username"].toString();
        ui->tsViewer->append(username);
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
