#ifndef MODIFIER_H
#define MODIFIER_H

class QImage;
class QString;
class QJsonObject;


class Modifier
{
public:
    virtual ~Modifier() {}

    virtual bool affectsColors() const = 0;
    virtual bool affectsGeometry() const = 0;

    virtual bool apply( QImage& image ) const = 0;

    virtual QString name() const = 0;

    //virtual QJsonObject saveToJson() const = 0;
};

#endif
