#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QTimer>
#include <QMovie>
#include <QBuffer>
#include <QMutex>
#include "RainDataChart.h"

namespace Ui {
	class HomeWidget;
}

class HomeWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit HomeWidget(QNetworkAccessManager* manager, QWidget *parent = 0);
	~HomeWidget();
	
private:
	Ui::HomeWidget *ui;
    QTimer *timerTime;
    QTimer *timerWeather;
    QNetworkAccessManager *manager;
    RainDataChart *rainDataChart;
	
private slots:
    void UpdateTime();
    void GetRainData();
    void ReplyFinished();
};

#endif // HOMEWIDGET_H
