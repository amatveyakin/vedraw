#ifndef Q_CONST_POINTER_H
#define Q_CONST_POINTER_H

#include <QPointerBase>

#ifndef QT_NO_QOBJECT

QT_BEGIN_HEADER

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
#ifdef Q_QDOC
    inline bool isNull() const;
    inline void clear();
#else
    using QPointerBase::isNull;
    using QPointerBase::clear;
#endif
};
template <class T> Q_DECLARE_TYPEINFO_BODY(QConstPointer<T>, Q_MOVABLE_TYPE);

#if (!defined(Q_CC_SUN) || (__SUNPRO_CC >= 0x580)) // ambiguity between const T * and T *

template <class T>
inline bool operator==(const T *o, const QConstPointer<T> &p)
{ return o == p.operator->(); }

template<class T>
inline bool operator==(const QConstPointer<T> &p, const T *o)
{ return p.operator->() == o; }

#else

template<class T>
inline bool operator==(const void *o, const QConstPointer<T> &p)
{ return o == p.operator->(); }

template<class T>
inline bool operator==(const QConstPointer<T> &p, const void *o)
{ return p.operator->() == o; }

#endif

template <class T>
inline bool operator==(T *o, const QConstPointer<T> &p)
{ return o == p.operator->(); }

template<class T>
inline bool operator==(const QConstPointer<T> &p, T *o)
{ return p.operator->() == o; }

template<class T>
inline bool operator==(const QConstPointer<T> &p1, const QConstPointer<T> &p2)
{ return p1.operator->() == p2.operator->(); }


#if (!defined(Q_CC_SUN) || (__SUNPRO_CC >= 0x580)) // ambiguity between const T * and T *

template <class T>
inline bool operator!=(const T *o, const QConstPointer<T> &p)
{ return o != p.operator->(); }

template<class T>
inline bool operator!= (const QConstPointer<T> &p, const T *o)
{ return p.operator->() != o; }

#else

template<class T>
inline bool operator!= (const void *o, const QConstPointer<T> &p)
{ return o != p.operator->(); }

template<class T>
inline bool operator!= (const QConstPointer<T> &p, const void *o)
{ return p.operator->() != o; }

#endif

template <class T>
inline bool operator!=(T *o, const QConstPointer<T> &p)
{ return o != p.operator->(); }

template<class T>
inline bool operator!= (const QConstPointer<T> &p, T *o)
{ return p.operator->() != o; }

template<class T>
inline bool operator!= (const QConstPointer<T> &p1, const QConstPointer<T> &p2)
{ return p1.operator->() != p2.operator->() ; }

// Make MSVC < 1400 (2005) handle "if (NULL == p)" syntax
#if defined(Q_CC_MSVC) && (_MSC_VER < 1400)
template<class T>
inline bool operator== (int i, const QConstPointer<T> &p)
{ Q_ASSERT(i == 0); return !i && p.isNull(); }

template<class T>
inline bool operator!= (int i, const QConstPointer<T> &p)
{ Q_ASSERT(i == 0); return !i && !p.isNull(); }
#endif

template<typename T>
QConstPointer<T>
qPointerFromVariant(const QVariant &variant)
{
    return QConstPointer<T>(qobject_cast<T*>(QtSharedPointer::weakPointerFromVariant_internal(variant).data()));
}

QT_END_NAMESPACE

QT_END_HEADER

#endif // QT_NO_QOBJECT

#endif // Q_CONST_POINTER_H
