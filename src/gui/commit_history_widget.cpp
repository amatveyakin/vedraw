#include <QListView>
#include <QStandardItemModel>

#include "commit_history_widget.h"
#include "drawing/commit.h"
#include "drawing/commit_history.h"
#include "utils/error_handling.h"


CommitHistoryWidget::CommitHistoryWidget()
    : m_qmodel( new QStandardItemModel( this ) )
    , m_view ( new QListView( this ) )
{
    m_view->setModel( m_qmodel );
    m_view->setEditTriggers( QAbstractItemView::NoEditTriggers );
    setWidget( m_view );
}

CommitHistoryWidget::~CommitHistoryWidget()
{
}

void CommitHistoryWidget::setModel( const CommitHistory* commitHistory )
{
    if ( m_commitHistory )
        disconnect( m_commitHistory, 0, this, 0 );
    m_commitHistory = commitHistory;
    if ( m_commitHistory )
        connect( m_commitHistory.data(), &CommitHistory::changed, this, &CommitHistoryWidget::updateData );
    updateData();
}

const CommitHistory* CommitHistoryWidget::model() const
{
    return m_commitHistory.data();
}

void CommitHistoryWidget::updateData()
{
    if ( !m_commitHistory )
        return;
    m_qmodel->clear();
    for ( int i = 0; i < m_commitHistory->commitCount(); ++i )
        m_qmodel->appendRow( new QStandardItem( m_commitHistory->at( i )->description() ) );
}
