#ifndef MODIFIER_H
#define MODIFIER_H

class QString;
class QJsonObject;

class Image;


class Modifier
{
public:
    virtual ~Modifier() {}

    virtual bool affectsColors() const = 0;
    virtual bool affectsGeometry() const = 0;

    virtual bool apply( Image& image ) const = 0;

    virtual QString name( bool translate ) const = 0;

    //virtual QJsonObject saveToJson() const = 0;
};

#endif
