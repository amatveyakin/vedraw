#include "commit.h"

#include "modifiers/modifier.h"


Commit::Commit( std::unique_ptr< const Modifier > modifier_ )
    : m_modifier( std::move( modifier_ ) )
    , m_commitTime( QDateTime::currentDateTime() )
{
}

Commit::~Commit()
{
}

QString Commit::description() const
{
    return m_modifier->name();
}
