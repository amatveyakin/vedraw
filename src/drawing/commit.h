#ifndef COMMIT_H
#define COMMIT_H

#include <memory>

#include <QDateTime>

class Modifier;


class Commit
{
public:
    Commit( std::unique_ptr< const Modifier > modifier_ );
    ~Commit();

    const Modifier* modifier() const          { return m_modifier.get(); }
    QString description() const;

private:
    std::unique_ptr< const Modifier > m_modifier;
    QDateTime m_commitTime;
};

#endif // COMMIT_H
