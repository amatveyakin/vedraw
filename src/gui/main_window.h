#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QAction>
#include <QMainWindow>

class Drawing;
class DrawingView;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    virtual ~MainWindow();

private:
    QScopedPointer<Drawing> m_drawing;

    QAction* m_openAction;
    QAction* m_exitAction;
    QAction* m_aboutAction;

    DrawingView* m_canvasWidget;

private:
    void setDrawing( QScopedPointer< Drawing >& drawing );
    QString buildImageFormatsFilter( bool write ) const;

private slots:
    void openFile();
    void showAbout();
    void updateWindowTitle();
};

#endif // MAIN_WINDOW_H
