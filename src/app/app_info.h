#ifndef APP_INFO_H
#define APP_INFO_H

class QString;
template< typename T > class QList;


QString applicationName( bool translate = true );
QList< int > applicationVersion();
QString applicationVersionString();

#endif // APP_INFO_H
