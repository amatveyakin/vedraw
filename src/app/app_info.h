#pragma once

#include <QString>


QString applicationName( bool translate = true );
QList< int > applicationVersion();
QString applicationVersionString();
QString makeWindowTitle( const QString& subtitle = QString() );
QString makeWindowTitle( const QStringList& subtitleList );
QString aboutText();
