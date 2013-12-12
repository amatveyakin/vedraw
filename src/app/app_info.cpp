#include <QObject>
#include <QStringList>

#include "app_info.h"

#include "utils/qt_extensions.h"


static const QChar emDash( 0x2014 );
static const QString paddedEmDash = ' ' + emDash + ' ';


QString applicationName( bool translate )
{
    const char* name = QT_TR_NOOP( "Vedraw" );
    return translate ? QObject::tr( name ) : name;
}

QList< int > applicationVersion()
{
    return { 0, 1 };
}

QString applicationVersionString()
{
  auto intVersion = applicationVersion();
  QStringList strVersion;
  for ( int x : intVersion )
    strVersion << QString::number( x );
  return strVersion.join( '.' );
}

QString makeWindowTitle( const QString& subtitle )
{
    return makeWindowTitle( subtitle.isEmpty() ? QStringList() : QStringList( subtitle ) );
}

QString makeWindowTitle( const QStringList& subtitleList )
{
    return ( QStringList() << subtitleList << applicationName() ).join( paddedEmDash );
}

QString aboutText()
{
    return args( QObject::tr( "%1 %2.\n\n"
                              "Author - Andrey Matveyakin, a.matveyakin@gmail.com\n\n"
                              "The program is free.\n\n"
                              "The program is distributed AS IS with NO WARRANTY OF ANY KIND.\n\n"
                              "The program is written in C++/Qt." ),
                 applicationName(), applicationVersionString() );
}
