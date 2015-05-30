// TODO: May be, use QSharedData instead of unique_ptr's for all my classes?
// TODO: May be, we'll need double-precision color images (e.g. array of QColors)

#include <QApplication>

#include <csignal>

#include "gui/main_window.h"


void noopSignalHandler( int sig )
{
    signal( sig, noopSignalHandler );
}

int main( int argc, char* argv[] )
{
    // Stop program from crashing after ERROR()
    signal( SIGTRAP, noopSignalHandler );

    QApplication app( argc, argv );

    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}
