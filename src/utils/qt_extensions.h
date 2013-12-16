#ifndef QT_EXTENSIONS_H
#define QT_EXTENSIONS_H

#include <QPointerBase>
#include <QString>
#include <QTextStream>


#define trNoop( text )  QString( QT_TR_NOOP( text ) )

#define trMaybe( text, needTranslate )  ( needTranslate ? QObject::tr( text ) : trNoop( text ) )


// TODO: Optimize: specialize for most common classes
template< typename T >
QString toQString( const T& v )
{
    QString out;
    QTextStream stream(&out);
    stream << v;
    return out;
}

template< typename... Values >
QString args( const QString& format, Values... values )
{
    return format.arg( toQString( values )... );
}



// TODO: Isn't there really a way to create a const QPointer?

QT_BEGIN_NAMESPACE

class QVariant;

template <class T>
class QConstPointer : private QPointerBase
{
public:
    inline QConstPointer() { }
    inline QConstPointer(const T *p) : QPointerBase(const_cast<T*>(p)) { }
    // compiler-generated copy/move ctor/assignment operators are fine!
    inline ~QConstPointer() { }

    inline QConstPointer<T> &operator=(const T* p)
    { QPointerBase::assign(const_cast<T*>(p)); return *this; }

    inline const T* data() const
    { return static_cast<const T*>(QPointerBase::data()); }
    inline const T* operator->() const
    { return data(); }
    inline const T& operator*() const
    { return *data(); }
    inline operator const T*() const
    { return data(); }

    using QPointerBase::isNull;
    using QPointerBase::clear;
};
template <class T> Q_DECLARE_TYPEINFO_BODY(QConstPointer<T>, Q_MOVABLE_TYPE);

template <class T>
inline bool operator==(const T *o, const QConstPointer<T> &p)
{ return o == p.operator->(); }

template<class T>
inline bool operator==(const QConstPointer<T> &p, const T *o)
{ return p.operator->() == o; }

template <class T>
inline bool operator==(T *o, const QConstPointer<T> &p)
{ return o == p.operator->(); }

template<class T>
inline bool operator==(const QConstPointer<T> &p, T *o)
{ return p.operator->() == o; }

template<class T>
inline bool operator==(const QConstPointer<T> &p1, const QConstPointer<T> &p2)
{ return p1.operator->() == p2.operator->(); }

template <class T>
inline bool operator!=(const T *o, const QConstPointer<T> &p)
{ return o != p.operator->(); }

template<class T>
inline bool operator!= (const QConstPointer<T> &p, const T *o)
{ return p.operator->() != o; }

template <class T>
inline bool operator!=(T *o, const QConstPointer<T> &p)
{ return o != p.operator->(); }

template<class T>
inline bool operator!= (const QConstPointer<T> &p, T *o)
{ return p.operator->() != o; }

template<class T>
inline bool operator!= (const QConstPointer<T> &p1, const QConstPointer<T> &p2)
{ return p1.operator->() != p2.operator->() ; }

template<typename T>
QConstPointer<T>
qPointerFromVariant(const QVariant &variant)
{
    return QConstPointer<T>(qobject_cast<const T*>(QtSharedPointer::weakPointerFromVariant_internal(variant).data()));
}

QT_END_NAMESPACE

#endif // QT_EXTENSIONS_H
