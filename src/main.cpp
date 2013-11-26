// TODO: May be, use QSharedData instead of unique_ptr's for all my classes?
// TODO: May be, we'll need double-precision color images (e.g. array of QColors)

#include <QApplication>

#include "gui/main_window.h"


int main( int argc, char* argv[] )
{
    QApplication app( argc, argv );

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
