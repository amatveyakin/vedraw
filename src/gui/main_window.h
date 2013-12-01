#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <memory>

#include <QMainWindow>

class QAction;

class CommitHistoryWidget;
class Drawing;
class DrawingView;
class ModifiersApplier;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow();

private:
    std::unique_ptr< Drawing > m_drawing;
    std::unique_ptr< DrawingView > m_canvasWidget;
    std::unique_ptr< ModifiersApplier > m_modifiersApplier;

    QAction* m_openAction = 0;
    QAction* m_exitAction = 0;
    QAction* m_invertColorAction = 0;
    QAction* m_invertLightnessAction = 0;
    QAction* m_aboutAction = 0;

    CommitHistoryWidget* m_commitHistoryWidget = 0;

private:
    void createActions();
    void createDockWidgets();
    void setUpMainMenu();
    void setUpUi();
    void setDrawing( std::unique_ptr< Drawing > drawing );
    QString buildImageFormatsFilter( bool write ) const;

private slots:
    void openFile();
    void showAbout();
    void updateWindowTitle();
};

#endif // MAIN_WINDOW_H
