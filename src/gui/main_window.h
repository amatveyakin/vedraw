#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <memory>

#include <QAction>
#include <QMainWindow>

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

    QAction* m_openAction;
    QAction* m_exitAction;
    QAction* m_invertColorAction;
    QAction* m_invertLightnessAction;
    QAction* m_aboutAction;

private:
    void setDrawing( std::unique_ptr< Drawing > drawing );
    QString buildImageFormatsFilter( bool write ) const;

private slots:
    void openFile();
    void showAbout();
    void updateWindowTitle();
};

#endif // MAIN_WINDOW_H
