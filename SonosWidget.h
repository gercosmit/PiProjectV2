#ifndef SONOSWIDGET_H
#define SONOSWIDGET_H

#include <QWidget>

namespace Ui {
	class SonosWidget;
}

class SonosWidget : public QWidget
{
	Q_OBJECT
    
public :
	explicit SonosWidget(QWidget *parent = 0);
	~SonosWidget();
	
private:
	Ui::SonosWidget *ui;
	
};

#endif // SONOSWIDGET_H
