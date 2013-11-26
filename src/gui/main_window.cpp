#include <QFileDialog>
#include <QEvent>
#include <QImageReader>
#include <QImageWriter>
#include <QMenuBar>
#include <QMessageBox>
#include <QSet>

#include "drawing_view.h"
#include "main_window.h"

#include "app/app_info.h"
#include "drawing/drawing.h"


MainWindow::MainWindow()
{
    QMenu* fileMenu = menuBar()->addMenu( tr( "&File" ) );
    m_openAction = new QAction( tr( "&Open..." ), this );
    m_exitAction = new QAction( tr( "&Exit..." ), this );
    fileMenu->addAction( m_openAction );
    fileMenu->addSeparator();
    fileMenu->addAction( m_exitAction );

    QMenu* helpMenu = menuBar()->addMenu( tr( "&Help" ) );
    m_aboutAction = new QAction( tr( "&About..." ), this );
    helpMenu->addAction( m_aboutAction );

    m_canvasWidget = 0;

    QScopedPointer< Drawing > emptyDrawing( new Drawing );
    setDrawing( emptyDrawing );

    connect( m_openAction,    &QAction::triggered, this, &MainWindow::openFile );
    connect( m_exitAction,    &QAction::triggered, this, &MainWindow::close );
    connect( m_aboutAction,   &QAction::triggered, this, &MainWindow::showAbout );
}

MainWindow::~MainWindow()
{
}

void MainWindow::setDrawing( QScopedPointer< Drawing >& drawing )
{
    delete m_canvasWidget;
    m_drawing.reset( drawing.take() );
    m_canvasWidget = new DrawingView( m_drawing.data() );
    setCentralWidget( m_canvasWidget );
    updateWindowTitle();
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

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName( this, applicationName(), QString(), buildImageFormatsFilter( false ) );
    if ( fileName.isEmpty() )
        return;
    QScopedPointer< Drawing > newDrawing( new Drawing( Drawing::CreateNewFromFileCtor(), fileName ) );
    if ( !newDrawing->isValid() ) {
        QMessageBox::warning( this, makeWindowTitle( tr( "Error" ) ), tr( "Cannot open file \"%1\"" ).arg( fileName ) );
        return;
    }
    setDrawing( newDrawing );
}

void MainWindow::showAbout ()
{
    QMessageBox::about( this, windowTitle(), aboutText() );
}

void MainWindow::updateWindowTitle()
{
    QString drawingName = m_drawing->drawingFileName();
    if ( drawingName.isEmpty() )
        drawingName = m_drawing->sourceImageFileName();
    setWindowTitle( makeWindowTitle( drawingName ) );
}


#include "main_window.moc"
