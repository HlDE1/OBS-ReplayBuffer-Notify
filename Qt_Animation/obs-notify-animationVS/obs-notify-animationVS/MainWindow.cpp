#include "MainWindow.h"
//#include <qsharedmemory.h>
#include <qdebug.h>

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	//sharedMemory = new QSharedMemory("MemoryInstance", this);
	//sharedMemory->create(1);
	//sharedMemory->setKey("Test");
	
	//if (sharedMemory->isAttached())
	//	sharedMemory->detach();
}

MainWindow::~MainWindow()
{

}

void MainWindow::TestMemory()
{

	//sharedMemory->attach();
	//qDebug("TestMemory: %B", sharedMemory->attach());
}
