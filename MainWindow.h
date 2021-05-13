#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "HomeWidget.h"
#include "TFCWidget.h"
#include "SonosWidget.h"

namespace Ui {
class MainWindow;
}

enum class widget {
    home,
    tfc,
    sonos,
    exit
};

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected slots:
    void HomeClicked();
    void SonosClicked();
    void TfcClicked();
    void ExitClicked();

private:
    Ui::MainWindow *ui;
	HomeWidget* homeWidget;
	TFCWidget* tfcWidget;
	SonosWidget* sonosWidget;
};

#endif // MAINWINDOW_H
