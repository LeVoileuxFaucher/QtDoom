/****************************************************************************
** Meta object code from reading C++ file 'levelpage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../levelpage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'levelpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 69
#error "This file was generated using the moc from 6.11.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

#ifndef Q_CONSTINIT
#define Q_CONSTINIT
#endif

QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
QT_WARNING_DISABLE_GCC("-Wuseless-cast")
namespace {
struct qt_meta_tag_ZN9LevelPageE_t {};
} // unnamed namespace

template <> constexpr inline auto LevelPage::qt_create_metaobjectdata<qt_meta_tag_ZN9LevelPageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "LevelPage",
        "0$Ahuc5pqMCBJ70LnvWu4YIitq6Fs",
        "level_1ClickedSig",
        "",
        "level_2ClickedSig",
        "level_3ClickedSig",
        "level_quitClickedSig",
        "changeButtons",
        "setupNextSelect",
        "updateHighlight",
        "activateSelectedButton"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'level_1ClickedSig'
        QtMocHelpers::SignalData<void()>(2, 3, QMC::AccessPublic, QMetaType::Void),
        // Signal 'level_2ClickedSig'
        QtMocHelpers::SignalData<void()>(4, 3, QMC::AccessPublic, QMetaType::Void),
        // Signal 'level_3ClickedSig'
        QtMocHelpers::SignalData<void()>(5, 3, QMC::AccessPublic, QMetaType::Void),
        // Signal 'level_quitClickedSig'
        QtMocHelpers::SignalData<void()>(6, 3, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeButtons'
        QtMocHelpers::SlotData<void()>(7, 3, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setupNextSelect'
        QtMocHelpers::SlotData<void()>(8, 3, QMC::AccessPublic, QMetaType::Void),
        // Slot 'updateHighlight'
        QtMocHelpers::SlotData<void()>(9, 3, QMC::AccessPublic, QMetaType::Void),
        // Slot 'activateSelectedButton'
        QtMocHelpers::SlotData<void()>(10, 3, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    uint qt_metaObjectHashIndex = 1;
    return QtMocHelpers::metaObjectData<LevelPage, qt_meta_tag_ZN9LevelPageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_metaObjectHashIndex);
}
Q_CONSTINIT const QMetaObject LevelPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9LevelPageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9LevelPageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN9LevelPageE_t>.metaTypes,
    nullptr
} };

void LevelPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<LevelPage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->level_1ClickedSig(); break;
        case 1: _t->level_2ClickedSig(); break;
        case 2: _t->level_3ClickedSig(); break;
        case 3: _t->level_quitClickedSig(); break;
        case 4: _t->changeButtons(); break;
        case 5: _t->setupNextSelect(); break;
        case 6: _t->updateHighlight(); break;
        case 7: _t->activateSelectedButton(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (LevelPage::*)()>(_a, &LevelPage::level_1ClickedSig, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (LevelPage::*)()>(_a, &LevelPage::level_2ClickedSig, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (LevelPage::*)()>(_a, &LevelPage::level_3ClickedSig, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (LevelPage::*)()>(_a, &LevelPage::level_quitClickedSig, 3))
            return;
    }
}

const QMetaObject *LevelPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LevelPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN9LevelPageE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int LevelPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void LevelPage::level_1ClickedSig()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void LevelPage::level_2ClickedSig()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void LevelPage::level_3ClickedSig()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void LevelPage::level_quitClickedSig()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
