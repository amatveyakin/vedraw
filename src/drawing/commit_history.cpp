#include "commit.h"
#include "commit_history.h"

#include "modifiers/modifier.h"


CommitHistory::CommitHistory()
    : QObject()
{
}

CommitHistory::~CommitHistory()
{
}

void CommitHistory::addCommit( std::unique_ptr< Modifier > modifier )
{
    m_commits.push_back( std::make_unique< Commit >( std::move( modifier ) ) );
    emit commitAdded();
    emit changed();
}
