#ifndef RAINDATACHART_H
#define RAINDATACHART_H

#include <QWidget>
#include <QMutex>

class RainDataChart : public QWidget
{
	Q_OBJECT
    
	public :
	    explicit RainDataChart(QWidget *parent = 0);
	~RainDataChart();
	
	void SetRainData(QStringList rainData)
	{
        rainDataMutex.lock();
		this->rainData = rainData;
        rainDataMutex.unlock();
	}
	
protected:
	void paintEvent(QPaintEvent *e);
	
private:
	QStringList rainData;
    QMutex rainDataMutex;
};

#endif // RAINDATACHART_H
