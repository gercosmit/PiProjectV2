#ifndef RAINDATACHART_H
#define RAINDATACHART_H

#include <QWidget>

class RainDataChart : public QWidget
{
	Q_OBJECT
    
	public :
	    explicit RainDataChart(QWidget *parent = 0);
	~RainDataChart();
	
	void SetRainData(QStringList rainData)
	{

		this->rainData = rainData;
	}
	
protected:
	void paintEvent(QPaintEvent *e);
	
private:
	QStringList rainData;
};

#endif // RAINDATACHART_H
