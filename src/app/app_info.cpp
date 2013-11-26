#include <QList>
#include <QObject>
#include <QString>

#include "app_info.h"


QString applicationName( bool translate )
{
    const char *name = QT_TR_NOOP( "Vedraw" );
    return translate ? QObject::tr( name ) : name;
}

QList< int > applicationVersion()
{
    return { 0 };
}

QString applicationVersionString()
{
  auto version = applicationVersion();
  QString versionString;
  for ( int x : version )
    versionString += QString::number(x) + '.';
  return versionString.left( versionString.length() - 1 );
}
