#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <QTimer>
#include <QMovie>
#include <QBuffer>
#include "RainDataChart.h"

namespace Ui {
	class HomeWidget;
}

class HomeWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit HomeWidget(QWidget *parent = 0);
	~HomeWidget();
	
private:
	Ui::HomeWidget *ui;
	QTimer *timer;
	QNetworkAccessManager *manager;
	QNetworkReply *replyRaindata;
	QNetworkReply *replyRadar;
	RainDataChart *rainDataChart;
	QByteArray *ba;
	QBuffer *data;
	QMovie *gif;
	
private slots:
    void UpdateTime();
	void UpdateRain();
	void ReplyFinished();
	
};

#endif // HOMEWIDGET_H