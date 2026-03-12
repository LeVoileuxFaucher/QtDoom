/****************************************************************************
** Meta object code from reading C++ file 'menupage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../menupage.h"
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'menupage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN8MenuPageE_t {};
} // unnamed namespace

template <> constexpr inline auto MenuPage::qt_create_metaobjectdata<qt_meta_tag_ZN8MenuPageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "MenuPage",
        "0$CsurmvmEPweSk388Jz2HWJaxfDo",
        "menu_levelClickedSig",
        "",
        "menu_playClickedSig",
        "changeButtons",
        "setupNextSelect",
        "updateHighlight",
        "activateSelectedButton"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'menu_levelClickedSig'
        QtMocHelpers::SignalData<void()>(2, 3, QMC::AccessPublic, QMetaType::Void),
        // Signal 'menu_playClickedSig'
        QtMocHelpers::SignalData<void()>(4, 3, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeButtons'
        QtMocHelpers::SlotData<void()>(5, 3, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setupNextSelect'
        QtMocHelpers::SlotData<void()>(6, 3, QMC::AccessPublic, QMetaType::Void),
        // Slot 'updateHighlight'
        QtMocHelpers::SlotData<void()>(7, 3, QMC::AccessPublic, QMetaType::Void),
        // Slot 'activateSelectedButton'
        QtMocHelpers::SlotData<void()>(8, 3, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    uint qt_metaObjectHashIndex = 1;
    return QtMocHelpers::metaObjectData<MenuPage, qt_meta_tag_ZN8MenuPageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_metaObjectHashIndex);
}
Q_CONSTINIT const QMetaObject MenuPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8MenuPageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8MenuPageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8MenuPageE_t>.metaTypes,
    nullptr
} };

void MenuPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<MenuPage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->menu_levelClickedSig(); break;
        case 1: _t->menu_playClickedSig(); break;
        case 2: _t->changeButtons(); break;
        case 3: _t->setupNextSelect(); break;
        case 4: _t->updateHighlight(); break;
        case 5: _t->activateSelectedButton(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (MenuPage::*)()>(_a, &MenuPage::menu_levelClickedSig, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (MenuPage::*)()>(_a, &MenuPage::menu_playClickedSig, 1))
            return;
    }
}

const QMetaObject *MenuPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MenuPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8MenuPageE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int MenuPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void MenuPage::menu_levelClickedSig()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void MenuPage::menu_playClickedSig()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
