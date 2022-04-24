#include "RainDataChart.h"
#include <QPainter>

const QColor backgroundColor(80, 80, 80);
const QColor barColor(0, 200, 255);
const int margin = 5;

RainDataChart::RainDataChart(QWidget *parent)
	: QWidget(parent)
{
}

RainDataChart::~RainDataChart()
{
	
}

void RainDataChart::paintEvent(QPaintEvent *e)
{
	QPainter painter(this);
	
	painter.fillRect(margin, margin, width() - 2 * margin, height() - 2 * margin, backgroundColor);
	
	if (rainData.count() > 0)
	{
		int barWidth = (width() - 2 * margin) / rainData.count();
		int alignShift = ((width() - 2 * margin) % rainData.count()) / 2;
		int barIndex = 0;
	
		for (QString &dataLine : rainData)
		{
			dataLine = dataLine.simplified();
			QStringList rainDataPoint = dataLine.split('|');
			if (rainDataPoint.count() == 2) {
				int rainValue = rainDataPoint.at(0).toInt();
				if (rainValue > 255)
				{
					rainValue = 255;
				}
				if (rainValue < 0)
				{
					rainValue = 0;
				}
				auto timeValue = rainDataPoint.at(1);
				int barHeight = (height() - 2 * margin) * rainValue / 255;
                painter.fillRect(margin + alignShift + barWidth * barIndex, height() - margin - barHeight, barWidth - 2, barHeight, QColor (0, 255-rainValue, 255));
				painter.fillRect(margin + alignShift + barWidth * barIndex, margin, barWidth - 2, height() - 2 * margin - barHeight, QColor(100,100,100));
				barIndex++;
			}
		}
	}
}
