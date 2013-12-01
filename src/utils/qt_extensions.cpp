#include <QString>

#include "qt_extensions.h"


QString trNoop( const char* text )
{
    return QString( QT_TR_NOOP( text ) );
}
