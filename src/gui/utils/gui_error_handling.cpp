#include <QMessageBox>

#include "gui_error_handling.h"

#include "app/app_info.h"


void ShowError( const Exception& e ) {
    QMessageBox message_box( QMessageBox::Warning, makeWindowTitle( QObject::tr( "Error" ) ), e.errorStory(), QMessageBox::Ok );
    message_box.setDefaultButton( QMessageBox::Ok );
    message_box.setDetailedText( e.errorStoryDebugInfo() );
    message_box.exec();
}
