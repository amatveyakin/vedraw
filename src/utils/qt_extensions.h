#pragma once

#include <exception>

#include <QString>
#include <QTextStream>


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
QString args( const QString& format, Values&&... values )
{
    return format.arg( toQString( std::forward< Values >( values ) )... );
}

// TODO: rename
template< typename Exception, typename... Values >
Exception qMakeException( const QString& format, Values&&... values )
{
    return Exception( args( format, std::forward< Values >( values )... ).toUtf8().constData() );
}
