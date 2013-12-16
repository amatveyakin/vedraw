#include <QAction>
#include <QDockWidget>
#include <QEvent>
#include <QFileDialog>
#include <QImageReader>
#include <QImageWriter>
#include <QMenuBar>
#include <QMessageBox>
#include <QSet>

#include "commit_history_widget.h"
#include "drawing_view.h"
#include "main_window.h"
#include "modifiers_applier.h"

#include "app/app_info.h"
#include "drawing/drawing.h"
#include "utils/cpp_extensions.h"
#include "utils/qt_extensions.h"


MainWindow::MainWindow()
{
    resize( 800, 600 );
    createActions();
    createDockWidgets();
    setUpMainMenu();
    setUpUi();
    setDrawing( std::make_unique< Drawing >() );
}

MainWindow::~MainWindow()
{
}

void MainWindow::createActions()
{
    m_openAction = new QAction( tr( "&Open..." ), this );
    connect( m_openAction, &QAction::triggered, this, &MainWindow::openFile );

    m_exitAction = new QAction( tr( "&Exit..." ), this );
    connect( m_exitAction, &QAction::triggered, this, &MainWindow::close );

    m_invertColorAction = new QAction( tr( "&Invert colors" ), this );

    m_invertLightnessAction = new QAction( tr( "Invert lightness" ), this );

    m_aboutAction = new QAction( tr( "&About..." ), this );
    connect( m_aboutAction, &QAction::triggered, this, &MainWindow::showAbout );
}

void MainWindow::createDockWidgets()
{
    m_commitHistoryWidget = new CommitHistoryWidget();
}

void MainWindow::setUpMainMenu()
{
    QMenu* fileMenu = menuBar()->addMenu( tr( "&File" ) );
    fileMenu->addAction( m_openAction );
    fileMenu->addSeparator();
    fileMenu->addAction( m_exitAction );

    QMenu* filtersMenu = menuBar()->addMenu( tr( "Filte&rs" ) );
    filtersMenu->addAction( m_invertColorAction );
    filtersMenu->addAction( m_invertLightnessAction );

    QMenu* helpMenu = menuBar()->addMenu( tr( "&Help" ) );
    helpMenu->addAction( m_aboutAction );
}

void MainWindow::setUpUi()
{
    addDockWidget( Qt::RightDockWidgetArea, m_commitHistoryWidget );
}

void MainWindow::setDrawing( std::unique_ptr< Drawing > drawing )
{
    m_drawing = std::move( drawing );
    m_canvasWidget.reset( new DrawingView( m_drawing.get() ) );
    m_modifiersApplier.reset( new ModifiersApplier( m_drawing.get() ) );
    setCentralWidget( m_canvasWidget.get() );
    m_commitHistoryWidget->setModel( m_drawing->commitHistory() );
    updateWindowTitle();

    connect( m_drawing.get(), &Drawing::changed, this, &MainWindow::onDrawingChanged );

    connect( m_invertColorAction,       &QAction::triggered, m_modifiersApplier.get(), &ModifiersApplier::invertColors );
    connect( m_invertLightnessAction,   &QAction::triggered, m_modifiersApplier.get(), &ModifiersApplier::invertLightness );
}


QString MainWindow::buildImageFormatsFilter( bool write ) const
{
    // TODO: Get OpenCV formats
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
        allFormatsString += args( "*.%1 ", lowerFormat );
        if ( upperFormat == "JPEG" )
            singleFormatsList += tr( "JPEG images (*.jpeg *.jpg)" );
        else if ( upperFormat != "JPG" )
            singleFormatsList += args( tr( "%1 images (*.%2)" ), upperFormat, lowerFormat );
    }
    allFormatsString = allFormatsString.trimmed();
    return args( tr( "All images (%1);;" ), allFormatsString ) + singleFormatsList.join( ";;" );
}

void MainWindow::onDrawingChanged()
{
    setWindowModified( m_drawing->isModified() );
}

void MainWindow::openFile()
{
    QString fileName = QFileDialog::getOpenFileName( this, applicationName(), QString(), buildImageFormatsFilter( false ) );
    if ( fileName.isEmpty() )
        return;
    auto newDrawing = std::make_unique< Drawing >( Drawing::CreateNewFromFileCtor(), fileName );
    if ( !newDrawing->isValid() ) {
        QMessageBox::warning( this, makeWindowTitle( tr( "Error" ) ), args( tr( "Cannot open file \"%1\"" ), fileName ) );
        return;
    }
    setDrawing( std::move( newDrawing ) );
}

void MainWindow::showAbout ()
{
    QMessageBox::about( this, makeWindowTitle(), aboutText() );
}

void MainWindow::updateWindowTitle()
{
    QString drawingName = m_drawing->drawingFileName();
    if ( drawingName.isEmpty() )
        drawingName = m_drawing->sourceImageFileName();
    if ( !drawingName.isEmpty() )
        drawingName = args( "%1[*]", drawingName );  // add `modified' flag
    setWindowTitle( makeWindowTitle( drawingName ) );
}


// #include "main_window.moc"  // TODO: What is this for?
