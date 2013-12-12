#ifndef QT_EXTENSIONS_H
#define QT_EXTENSIONS_H

#include <QString>


#define trNoop( text )  QString( QT_TR_NOOP( text ) )

#define trMaybe( text, needTranslate )  ( needTranslate ? QObject::tr( text ) : trNoop( text ) )


template< typename T >
QString toQString( const T& v )
{
    return QString( v );
}

template<>
inline QString toQString< int >( const int& v )
{
    return QString::number( v );
}

template<>
inline QString toQString< double >( const double& v )
{
    return QString::number( v );
}

template< typename... Values >
QString args( const QString& format, Values... values )
{
    return format.arg( toQString( values )... );
}

#endif // QT_EXTENSIONS_H
