#ifndef TFCWIDGET_H
#define TFCWIDGET_H

#include <QWidget>
#include <QtNetwork/qnetworkaccessmanager.h>
#include <QtNetwork/qnetworkreply.h>
#include <QTimer>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

namespace Ui {
	class TFCWidget;
}

class TFCWidget : public QWidget
{
	Q_OBJECT
    
public :
	explicit TFCWidget(QWidget *parent = 0);
	~TFCWidget();
	
private:
	Ui::TFCWidget *ui;
	QTimer *timer;
	QNetworkAccessManager* manager;
	QNetworkReply* reply;
	
private slots :
	void UpdateTFC();
	void ReplyFinished();
    void PrintOutShitters(QJsonArray memberArray);
    void JohnAlert();
    void CoastClear();
};

#endif // TFCWIDGET_H
