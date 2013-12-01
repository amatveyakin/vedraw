#ifndef COMMIT_HISTORY_H
#define COMMIT_HISTORY_H

#include <memory>
#include <vector>

#include <QObject>

class Commit;
class Modifier;


class CommitHistory : public QObject
{
    Q_OBJECT

public:
    CommitHistory();
    ~CommitHistory();

    // TODO: Use some other iteration method. May be, return iterator to HEAD with getParent function.
    const Commit* at( int index ) const     { return m_commits.at( index ).get(); }
    int commitCount() const                 { return m_commits.size(); }

    void addCommit( std::unique_ptr< Modifier > modifier );

signals:
    void commitAdded();
    void changed();

private:
    // TODO: It should be a tree actually
    std::vector< std::unique_ptr< Commit > > m_commits;
};

#endif // COMMIT_HISTORY_H
