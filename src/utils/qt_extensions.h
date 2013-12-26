#pragma once

#include <QString>
#include <QTextStream>

// TODO: Isn't there really a way to create a const QPointer?
#include "q_const_pointer.h"


#define trNoop( text )  QString( QT_TR_NOOP( text ) )

#define trMaybe( text, needTranslate )  ( needTranslate ? QObject::tr( text ) : trNoop( text ) )


// TODO: Optimize: specialize for most common classes
template< typename T >
QString toQString( const T& v )
{
    QString out;
    QTextStream stream(&out);
    stream << v;
    return out;
}

template< typename... Values >
QString args( const QString& format, Values... values )
{
    return format.arg( toQString( values )... );
}
