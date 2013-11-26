#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QAction>
#include <QMainWindow>


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow();
    ~MainWindow();

private:
    QAction *m_openAction;
    QAction *m_exitAction;

    QWidget *m_canvasWidget;

private slots:
    void openFile();
    QString buildImageFormatsFilter( bool write ) const;
};

#endif // MAIN_WINDOW_H
