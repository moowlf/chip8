
#include <QApplication>
#include "QtGui.hpp"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
	QtGui gui;
	gui.show();

    return app.exec();
}
