/****************************************************************************
** Meta object code from reading C++ file 'ssRequests.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../Shared/Source/API/Models/ssRequests.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ssRequests.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_API__ARequests_t {
    QByteArrayData data[10];
    char stringdata0[98];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_API__ARequests_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_API__ARequests_t qt_meta_stringdata_API__ARequests = {
    {
QT_MOC_LITERAL(0, 0, 14), // "API::ARequests"
QT_MOC_LITERAL(1, 15, 10), // "getChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 3), // "get"
QT_MOC_LITERAL(4, 31, 17), // "getDetailsChanged"
QT_MOC_LITERAL(5, 49, 10), // "getDetails"
QT_MOC_LITERAL(6, 60, 6), // "setGet"
QT_MOC_LITERAL(7, 67, 13), // "setGetDetails"
QT_MOC_LITERAL(8, 81, 9), // "ARequests"
QT_MOC_LITERAL(9, 91, 6) // "parent"

    },
    "API::ARequests\0getChanged\0\0get\0"
    "getDetailsChanged\0getDetails\0setGet\0"
    "setGetDetails\0ARequests\0parent"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_API__ARequests[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       2,   50, // properties
       0,    0, // enums/sets
       2,   58, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       4,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   40,    2, 0x0a /* Public */,
       7,    1,   43,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // constructors: parameters
    0x80000000 | 2, QMetaType::QObjectStar,    9,
    0x80000000 | 2,

 // properties: name, type, flags
       3, QMetaType::QString, 0x00495103,
       5, QMetaType::QString, 0x00495103,

 // properties: notify_signal_id
       0,
       1,

 // constructors: name, argc, parameters, tag, flags
       8,    1,   46,    2, 0x0e /* Public */,
       8,    0,   49,    2, 0x2e /* Public | MethodCloned */,

       0        // eod
};

void API::ARequests::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::CreateInstance) {
        switch (_id) {
        case 0: { ARequests *_r = new ARequests((*reinterpret_cast< QObject*(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        case 1: { ARequests *_r = new ARequests();
            if (_a[0]) *reinterpret_cast<QObject**>(_a[0]) = _r; } break;
        default: break;
        }
    } else if (_c == QMetaObject::InvokeMetaMethod) {
        ARequests *_t = static_cast<ARequests *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->getChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->getDetailsChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->setGet((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->setGetDetails((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ARequests::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ARequests::getChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ARequests::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ARequests::getDetailsChanged)) {
                *result = 1;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        ARequests *_t = static_cast<ARequests *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->get(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getDetails(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        ARequests *_t = static_cast<ARequests *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setGet(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setGetDetails(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject API::ARequests::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_API__ARequests.data,
      qt_meta_data_API__ARequests,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *API::ARequests::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *API::ARequests::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_API__ARequests.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int API::ARequests::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void API::ARequests::getChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void API::ARequests::getDetailsChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
