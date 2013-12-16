#ifndef COMMIT_HISTORY_WIDGET_H
#define COMMIT_HISTORY_WIDGET_H

#include <QDockWidget>
#include <QPointer>

#include "utils/qt_extensions.h"

class QListView;
class QStandardItemModel;

class CommitHistory;
class Drawing;


class CommitHistoryWidget : public QDockWidget
{
public:
    CommitHistoryWidget();
    ~CommitHistoryWidget();

    void setModel( const CommitHistory* commitHistory );
    const CommitHistory* model() const;

public slots:
    void updateData();

private:
    QConstPointer< CommitHistory > m_commitHistory;
    QStandardItemModel* m_qmodel = 0;
    QListView* m_view = 0;
};

#endif // COMMIT_HISTORY_WIDGET_H
