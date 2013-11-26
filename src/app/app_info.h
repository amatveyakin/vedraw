#ifndef APP_INFO_H
#define APP_INFO_H

class QString;
class QStringList;
template< typename T > class QList;


QString applicationName( bool translate = true );
QList< int > applicationVersion();
QString applicationVersionString();
QString makeWindowTitle( const QString& subtitle );
QString makeWindowTitle( const QStringList& subtitleList );
QString aboutText();

#endif // APP_INFO_H
