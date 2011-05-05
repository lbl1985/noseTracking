/****************************************************************************
** Meta object code from reading C++ file 'FiltersWindow.h'
**
** Created: Tue May 3 14:16:34 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../viewer/FiltersWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'FiltersWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_FiltersWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   15,   14,   14, 0x08,
      65,   15,   14,   14, 0x08,
     111,  105,   14,   14, 0x08,
     147,  105,   14,   14, 0x08,
     183,   15,   14,   14, 0x08,
     217,   15,   14,   14, 0x08,
     250,   15,   14,   14, 0x08,
     282,   15,   14,   14, 0x08,
     313,   15,   14,   14, 0x08,
     353,  105,   14,   14, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_FiltersWindow[] = {
    "FiltersWindow\0\0checked\0"
    "on_removeSmallStructuresBox_toggled(bool)\0"
    "on_fillSmallHolesCheckBox_toggled(bool)\0"
    "value\0on_maxDepthSlider_valueChanged(int)\0"
    "on_minDepthSlider_valueChanged(int)\0"
    "on_unstableCheckBox_toggled(bool)\0"
    "on_normalsCheckBox_toggled(bool)\0"
    "on_medianCheckBox_toggled(bool)\0"
    "on_edgesCheckBox_toggled(bool)\0"
    "on_depthThresholdCheckBox_toggled(bool)\0"
    "on_kinectTiltSlider_valueChanged(int)\0"
};

const QMetaObject FiltersWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_FiltersWindow,
      qt_meta_data_FiltersWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &FiltersWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *FiltersWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *FiltersWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_FiltersWindow))
        return static_cast<void*>(const_cast< FiltersWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int FiltersWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: on_removeSmallStructuresBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: on_fillSmallHolesCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: on_maxDepthSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: on_minDepthSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: on_unstableCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: on_normalsCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: on_medianCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: on_edgesCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: on_depthThresholdCheckBox_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: on_kinectTiltSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
