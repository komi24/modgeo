/****************************************************************************
** Meta object code from reading C++ file 'window_mesh_debug.hpp'
**
** Created by: The Qt Meta Object Compiler version 63 (Qt 4.8.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../local/window_mesh_debug.hpp"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'window_mesh_debug.hpp' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 63
#error "This file was generated using the moc from 4.8.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_window_mesh_debug[] = {

 // content:
       6,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      19,   18,   18,   18, 0x08,
      28,   18,   18,   18, 0x08,
      48,   37,   18,   18, 0x08,
      80,   37,   18,   18, 0x08,
     114,   37,   18,   18, 0x08,
     146,   37,   18,   18, 0x08,
     183,   37,   18,   18, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_window_mesh_debug[] = {
    "window_mesh_debug\0\0accept()\0reject()\0"
    "is_clicked\0debug_mode_button_clicked(bool)\0"
    "vertex_index_button_clicked(bool)\0"
    "face_index_button_clicked(bool)\0"
    "inverted_normal_button_clicked(bool)\0"
    "vertex_show_button_clicked(bool)\0"
};

void window_mesh_debug::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Q_ASSERT(staticMetaObject.cast(_o));
        window_mesh_debug *_t = static_cast<window_mesh_debug *>(_o);
        switch (_id) {
        case 0: _t->accept(); break;
        case 1: _t->reject(); break;
        case 2: _t->debug_mode_button_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->vertex_index_button_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->face_index_button_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->inverted_normal_button_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->vertex_show_button_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObjectExtraData window_mesh_debug::staticMetaObjectExtraData = {
    0,  qt_static_metacall 
};

const QMetaObject window_mesh_debug::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_window_mesh_debug,
      qt_meta_data_window_mesh_debug, &staticMetaObjectExtraData }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &window_mesh_debug::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *window_mesh_debug::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *window_mesh_debug::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_window_mesh_debug))
        return static_cast<void*>(const_cast< window_mesh_debug*>(this));
    return QDialog::qt_metacast(_clname);
}

int window_mesh_debug::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
