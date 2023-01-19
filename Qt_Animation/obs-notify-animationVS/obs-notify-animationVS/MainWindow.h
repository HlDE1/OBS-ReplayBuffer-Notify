#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
//#include <qsharedmemory.h>


class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget* parent = nullptr);
	~MainWindow();
	void TestMemory();

private:
	Ui::MainWindowClass ui;
	//QSharedMemory* sharedMemory;

};
