#include <QFileDialog>
#include <QImageReader>
#include <QImageWriter>
#include <QMenuBar>
#include <QSet>

#include "main_window.h"

#include "app/app_info.h"


MainWindow::MainWindow()
{
    setWindowTitle( applicationName() );

    QMenu *fileMenu = menuBar()->addMenu( tr( "&File" ) );
    m_openAction = new QAction( tr( "&Open..." ), this );
    m_exitAction = new QAction( tr( "&Exit..." ), this );
    fileMenu->addAction( m_openAction );
    fileMenu->addSeparator();
    fileMenu->addAction( m_exitAction );

    m_canvasWidget = new QWidget;
    setCentralWidget( m_canvasWidget );

    connect( m_openAction, &QAction::triggered, this, &MainWindow::openFile );
    connect( m_exitAction, &QAction::triggered, this, &MainWindow::close );
}

MainWindow::~MainWindow()
{
}


void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName( this, applicationName(), QString(), buildImageFormatsFilter( false ) );
}

QString MainWindow::buildImageFormatsFilter( bool write ) const
{
    QList< QByteArray > supportedFormatsRawList = write ? QImageWriter::supportedImageFormats() : QImageReader::supportedImageFormats();
    QSet< QString > supportedFormatsSet;
    for ( auto& format : supportedFormatsRawList )
        supportedFormatsSet.insert( QString( format ).toLower() );
    QStringList supportedFormatsList( supportedFormatsSet.toList() );
    qSort( supportedFormatsList );
    QString allFormatsString;
    QStringList singleFormatsList;
    for ( auto& lowerFormat : supportedFormatsList ) {
        QString upperFormat = lowerFormat.toUpper();
        allFormatsString += QString( "*.%1 " ).arg( lowerFormat );
        if ( upperFormat == "JPEG" )
            singleFormatsList += tr( "JPEG images (*.jpeg *.jpg)" );
        else if ( upperFormat != "JPG" )
            singleFormatsList += tr( "%1 images (*.%2)" ).arg( upperFormat ).arg( lowerFormat );
    }
    allFormatsString = allFormatsString.trimmed();
    return tr( "All images (%1);;" ).arg( allFormatsString ) + singleFormatsList.join( ";;" );
}


 #include "main_window.moc"
