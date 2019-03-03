#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 

#include "Header\QfeMainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

//	_crtBreakAlloc = 0;

	QApplication a(argc, argv);
	QfeMainWindow w;
	qDebug("back to main");
	return a.exec();
}
