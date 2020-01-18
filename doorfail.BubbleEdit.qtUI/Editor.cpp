#include "Editor.h"

Editor::Editor(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.centralWidget, SIGNAL(clicked()), this, SLOT(exit()));
}
