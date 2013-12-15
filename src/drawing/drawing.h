#ifndef DRAWING_H
#define DRAWING_H

#include <memory>

#include <QImage>

class CommitHistory;
class Modifier;


class Drawing : public QObject
{
    Q_OBJECT

public:
    struct LoadFromFileCtor {};
    struct CreateNewFromFileCtor {};

    Drawing();
//    drawing( LoadFromFileCtor, const QString &fileName );
    Drawing( CreateNewFromFileCtor, const QString &fileName );
    ~Drawing();

    QString sourceImageFileName() const         { return m_sourceImageFileName; }
    QString drawingFileName() const             { return m_drawingFileName; }
    bool isValid() const                        { return m_isValid; }

    QImage sourceImage() const                  { return m_sourceImage; }
    QImage currentImage() const                 { return m_currentImage; }

    bool isModified() const;
    bool addModifier( std::unique_ptr< Modifier > modifier );

    CommitHistory* commitHistory()              { return m_changes.get(); }
    const CommitHistory* commitHistory() const  { return m_changes.get(); }

//    bool saveToFile( const QString &fileName ) const;

signals:
    void changed();

private:
    QString m_sourceImageFileName;
    QString m_drawingFileName;
    bool m_isValid = false;
    bool m_isModified = false;

    QImage m_sourceImage;
    QImage m_currentImage;
    std::unique_ptr< CommitHistory > m_changes;
    // TODO: Store commit history
};

#endif // DRAWING_H
