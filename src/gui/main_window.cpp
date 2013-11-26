#include <QFileDialog>
#include <QEvent>
#include <QImageReader>
#include <QImageWriter>
#include <QMenuBar>
#include <QMessageBox>
#include <QSet>

#include "drawing_view.h"
#include "main_window.h"
#include "modifiers_applier.h"

#include "utils/cpp_extensions.h"
#include "app/app_info.h"
#include "drawing/drawing.h"


MainWindow::MainWindow()
{
    resize( 800, 600 );

    QMenu* fileMenu = menuBar()->addMenu( tr( "&File" ) );
    m_openAction = new QAction( tr( "&Open..." ), this );
    m_exitAction = new QAction( tr( "&Exit..." ), this );
    fileMenu->addAction( m_openAction );
    fileMenu->addSeparator();
    fileMenu->addAction( m_exitAction );

    QMenu* filtersMenu = menuBar()->addMenu( tr( "Filte&rs" ) );
    m_invertColorAction = new QAction( tr( "&Invert colors" ), this );
    m_invertLightnessAction = new QAction( tr( "Invert lightness" ), this );
    filtersMenu->addAction( m_invertColorAction );
    filtersMenu->addAction( m_invertLightnessAction );

    QMenu* helpMenu = menuBar()->addMenu( tr( "&Help" ) );
    m_aboutAction = new QAction( tr( "&About..." ), this );
    helpMenu->addAction( m_aboutAction );

    setDrawing( std::make_unique< Drawing >() );

    connect( m_openAction,    &QAction::triggered, this, &MainWindow::openFile );
    connect( m_exitAction,    &QAction::triggered, this, &MainWindow::close );
    connect( m_aboutAction,   &QAction::triggered, this, &MainWindow::showAbout );
}

MainWindow::~MainWindow()
{
}

void MainWindow::setDrawing( std::unique_ptr< Drawing > drawing )
{
    m_drawing.swap( drawing );
    m_canvasWidget.reset( new DrawingView( m_drawing.get() ) );
    m_modifiersApplier.reset( new ModifiersApplier( m_drawing.get(), m_canvasWidget.get() ) );
    setCentralWidget( m_canvasWidget.get() );
    updateWindowTitle();

    connect( m_invertColorAction,       &QAction::triggered, m_modifiersApplier.get(), &ModifiersApplier::invertColors );
    connect( m_invertLightnessAction,   &QAction::triggered, m_modifiersApplier.get(), &ModifiersApplier::invertLightness );
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
    auto newDrawing = std::make_unique< Drawing >( Drawing::CreateNewFromFileCtor(), fileName );
    if ( !newDrawing->isValid() ) {
        QMessageBox::warning( this, makeWindowTitle( tr( "Error" ) ), tr( "Cannot open file \"%1\"" ).arg( fileName ) );
        return;
    }
    setDrawing( std::move( newDrawing ) );
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


// #include "main_window.moc"  // TODO: What is this for?
