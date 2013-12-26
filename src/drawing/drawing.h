#pragma once

#include <memory>

#include <QImage>

class CommitHistory;
class Image;
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
    bool isValid() const;

    const Image* sourceImage() const            { return m_sourceImage.get(); }
    const Image* currentImage() const           { return m_currentImage.get(); }

    bool isModified() const;
    bool addModifier( std::unique_ptr< Modifier > modifier );

    const CommitHistory* commitHistory() const  { return m_changes.get(); }

//    bool saveToFile( const QString &fileName ) const;

signals:
    void changed();

private:
    QString m_sourceImageFileName;
    QString m_drawingFileName;
    bool m_isValid = false;
    bool m_isModified = false;

    std::unique_ptr< Image > m_sourceImage;
    std::unique_ptr< Image > m_currentImage;
    std::unique_ptr< CommitHistory > m_changes;
    // TODO: Store commit history

private:
    void cloneCurrentImageFromSource();
};
