#ifndef TFCWIDGET_H
#define TFCWIDGET_H

#include <QWidget>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMutex>
#include "discordserver.h"

namespace Ui {
	class TFCWidget;
}

class TFCWidget : public QWidget
{
	Q_OBJECT
    
public :
    explicit TFCWidget(QNetworkAccessManager* manager, QWidget *parent = 0);
	~TFCWidget();
	
private:
	Ui::TFCWidget *ui;
	QTimer *timer;
    QNetworkAccessManager* manager;
    QMutex networkReplyMutex;
	
private slots :
	void UpdateTFC();
    void ReplyFinished();
    void CheckForJohn(QJsonArray memberArray);
    void PrintOutChannels(DiscordServer discordServer);
    void JohnAlert();
    void CoastClear();
};

#endif // TFCWIDGET_H
