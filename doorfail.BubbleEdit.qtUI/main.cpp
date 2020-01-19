#include "Editor.h"
#include "dragwidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	DragWidget dragWindow;
	Editor w;
	w.show();
	dragWindow.show();
	return a.exec();
}
