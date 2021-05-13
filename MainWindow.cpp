#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <sys/time.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
	homeWidget(new HomeWidget(this)),
	tfcWidget(new TFCWidget(this)),
	sonosWidget(new SonosWidget(this))
{
    ui->setupUi(this);
	QMainWindow::showFullScreen();
	
	ui->stackedWidget->insertWidget(0, homeWidget);
	ui->stackedWidget->insertWidget(1, tfcWidget);
	ui->stackedWidget->insertWidget(2, sonosWidget);
	
	ui->stackedWidget->setCurrentIndex((int)widget::home);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::HomeClicked()
{
	ui->stackedWidget->setCurrentIndex((int)widget::home);
}

void MainWindow::TfcClicked()
{
	ui->stackedWidget->setCurrentIndex((int)widget::tfc);
}

void MainWindow::SonosClicked()
{
    ui->stackedWidget->setCurrentIndex((int)widget::sonos);
}

void MainWindow::ExitClicked()
{
    ui->stackedWidget->setCurrentIndex((int)widget::exit);
}

