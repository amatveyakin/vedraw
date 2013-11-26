#ifndef DRAWING_H
#define DRAWING_H

#include <QImage>
#include <QString>


class Drawing
{
public:
    struct LoadFromFileCtor {};
    struct CreateNewFromFileCtor {};

    Drawing();
//    drawing( LoadFromFileCtor, const QString &fileName );
    Drawing( CreateNewFromFileCtor, const QString &fileName );

    QString sourceImageFileName() const         { return m_sourceImageFileName; }
    QString drawingFileName() const             { return m_drawingFileName; }
    bool isValid() const                        { return m_isValid; }

    QImage sourceImage() const                  { return m_sourceImage; }
    QImage currentImage() const                 { return m_currentImage; }

//    bool saveToFile( const QString &fileName ) const;

private:
    QString m_sourceImageFileName;
    QString m_drawingFileName;
    bool m_isValid;

    QImage m_sourceImage;
    QImage m_currentImage;
    // TODO: Store commit history
};

#endif // DRAWING_H
