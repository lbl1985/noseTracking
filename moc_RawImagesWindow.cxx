/****************************************************************************
** Meta object code from reading C++ file 'RawImagesWindow.h'
**
** Created: Tue May 3 14:16:34 2011
**      by: The Qt Meta Object Compiler version 62 (Qt 4.7.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../viewer/RawImagesWindow.h"
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'RawImagesWindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 62
#error "This file was generated using the moc from 4.7.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
static const uint qt_meta_data_RawImagesWindow[] = {

 // content:
       5,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: signature, parameters, type, tag, flags
      23,   17,   16,   16, 0x0a,
      48,   16,   16,   16, 0x08,
      97,   16,   16,   16, 0x08,
     129,   16,   16,   16, 0x08,
     166,  158,   16,   16, 0x08,
     192,   16,   16,   16, 0x08,
     227,   16,   16,   16, 0x08,
     271,   16,   16,   16, 0x08,
     303,   16,   16,   16, 0x08,
     335,   16,   16,   16, 0x08,
     380,   16,   16,   16, 0x08,
     407,   16,   16,   16, 0x08,
     442,   16,   16,   16, 0x08,
     479,  477,   16,   16, 0x08,
     510,  477,   16,   16, 0x08,

       0        // eod
};

static const char qt_meta_stringdata_RawImagesWindow[] = {
    "RawImagesWindow\0\0event\0closeEvent(QCloseEvent*)\0"
    "on_actionSave_calibration_parameters_triggered()\0"
    "on_actionNext_frame_triggered()\0"
    "on_actionPause_toggled(bool)\0checked\0"
    "on_syncMode_toggled(bool)\0"
    "on_action_GrabFrames_toggled(bool)\0"
    "on_action_Screen_capture_mode_toggled(bool)\0"
    "on_action_Filters_toggled(bool)\0"
    "on_action_3D_View_toggled(bool)\0"
    "on_action_Show_Object_Detector_toggled(bool)\0"
    "on_action_Quit_triggered()\0"
    "on_action_GrabOneFrame_triggered()\0"
    "on_outputDirText_editingFinished()\0v\0"
    "on_actionShow_IR_toggled(bool)\0"
    "on_actionDual_RGB_IR_mode_toggled(bool)\0"
};

const QMetaObject RawImagesWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_RawImagesWindow,
      qt_meta_data_RawImagesWindow, 0 }
};

#ifdef Q_NO_DATA_RELOCATION
const QMetaObject &RawImagesWindow::getStaticMetaObject() { return staticMetaObject; }
#endif //Q_NO_DATA_RELOCATION

const QMetaObject *RawImagesWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->metaObject : &staticMetaObject;
}

void *RawImagesWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_RawImagesWindow))
        return static_cast<void*>(const_cast< RawImagesWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int RawImagesWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 1: on_actionSave_calibration_parameters_triggered(); break;
        case 2: on_actionNext_frame_triggered(); break;
        case 3: on_actionPause_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: on_syncMode_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: on_action_GrabFrames_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: on_action_Screen_capture_mode_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: on_action_Filters_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: on_action_3D_View_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 9: on_action_Show_Object_Detector_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: on_action_Quit_triggered(); break;
        case 11: on_action_GrabOneFrame_triggered(); break;
        case 12: on_outputDirText_editingFinished(); break;
        case 13: on_actionShow_IR_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 14: on_actionDual_RGB_IR_mode_toggled((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
        _id -= 15;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
