#ifndef QT_EXTENSIONS_H
#define QT_EXTENSIONS_H

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
QString args( const QString& format, Values... values )
{
    return format.arg( toQString( values )... );
}

#endif // QT_EXTENSIONS_H
