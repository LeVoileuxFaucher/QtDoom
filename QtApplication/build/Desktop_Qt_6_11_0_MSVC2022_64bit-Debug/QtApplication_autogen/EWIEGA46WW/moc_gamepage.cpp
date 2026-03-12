/****************************************************************************
** Meta object code from reading C++ file 'gamepage.h'
**
** Created by: The Qt Meta Object Compiler version 69 (Qt 6.11.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../gamepage.h"
#include <QtGui/qtextcursor.h>
#include <QtCore/qmetatype.h>

#include <QtCore/qtmochelpers.h>

#include <memory>


#include <QtCore/qxptype_traits.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'gamepage.h' doesn't include <QObject>."
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
struct qt_meta_tag_ZN8GamePageE_t {};
} // unnamed namespace

template <> constexpr inline auto GamePage::qt_create_metaobjectdata<qt_meta_tag_ZN8GamePageE_t>()
{
    namespace QMC = QtMocConstants;
    QtMocHelpers::StringRefStorage qt_stringData {
        "GamePage",
        "0$IbgaXA+5gZRapg8jD8bAK1Aq3Eo",
        "menu_quitClickedSig",
        "",
        "menu_retryClickedSig",
        "menu_continueClickedSig",
        "over_quitClickedSig",
        "over_retryClickedSig",
        "changeButtons",
        "setupNextSelect",
        "updateHighlight",
        "activateSelectedButton",
        "showMenuPopup"
    };

    QtMocHelpers::UintData qt_methods {
        // Signal 'menu_quitClickedSig'
        QtMocHelpers::SignalData<void()>(2, 3, QMC::AccessPublic, QMetaType::Void),
        // Signal 'menu_retryClickedSig'
        QtMocHelpers::SignalData<void()>(4, 3, QMC::AccessPublic, QMetaType::Void),
        // Signal 'menu_continueClickedSig'
        QtMocHelpers::SignalData<void()>(5, 3, QMC::AccessPublic, QMetaType::Void),
        // Signal 'over_quitClickedSig'
        QtMocHelpers::SignalData<void()>(6, 3, QMC::AccessPublic, QMetaType::Void),
        // Signal 'over_retryClickedSig'
        QtMocHelpers::SignalData<void()>(7, 3, QMC::AccessPublic, QMetaType::Void),
        // Slot 'changeButtons'
        QtMocHelpers::SlotData<void()>(8, 3, QMC::AccessPublic, QMetaType::Void),
        // Slot 'setupNextSelect'
        QtMocHelpers::SlotData<void()>(9, 3, QMC::AccessPublic, QMetaType::Void),
        // Slot 'updateHighlight'
        QtMocHelpers::SlotData<void()>(10, 3, QMC::AccessPublic, QMetaType::Void),
        // Slot 'activateSelectedButton'
        QtMocHelpers::SlotData<void()>(11, 3, QMC::AccessPublic, QMetaType::Void),
        // Slot 'showMenuPopup'
        QtMocHelpers::SlotData<void()>(12, 3, QMC::AccessPublic, QMetaType::Void),
    };
    QtMocHelpers::UintData qt_properties {
    };
    QtMocHelpers::UintData qt_enums {
    };
    uint qt_metaObjectHashIndex = 1;
    return QtMocHelpers::metaObjectData<GamePage, qt_meta_tag_ZN8GamePageE_t>(QMC::MetaObjectFlag{}, qt_stringData,
            qt_methods, qt_properties, qt_enums, qt_metaObjectHashIndex);
}
Q_CONSTINIT const QMetaObject GamePage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8GamePageE_t>.stringdata,
    qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8GamePageE_t>.data,
    qt_static_metacall,
    nullptr,
    qt_staticMetaObjectRelocatingContent<qt_meta_tag_ZN8GamePageE_t>.metaTypes,
    nullptr
} };

void GamePage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    auto *_t = static_cast<GamePage *>(_o);
    if (_c == QMetaObject::InvokeMetaMethod) {
        switch (_id) {
        case 0: _t->menu_quitClickedSig(); break;
        case 1: _t->menu_retryClickedSig(); break;
        case 2: _t->menu_continueClickedSig(); break;
        case 3: _t->over_quitClickedSig(); break;
        case 4: _t->over_retryClickedSig(); break;
        case 5: _t->changeButtons(); break;
        case 6: _t->setupNextSelect(); break;
        case 7: _t->updateHighlight(); break;
        case 8: _t->activateSelectedButton(); break;
        case 9: _t->showMenuPopup(); break;
        default: ;
        }
    }
    if (_c == QMetaObject::IndexOfMethod) {
        if (QtMocHelpers::indexOfMethod<void (GamePage::*)()>(_a, &GamePage::menu_quitClickedSig, 0))
            return;
        if (QtMocHelpers::indexOfMethod<void (GamePage::*)()>(_a, &GamePage::menu_retryClickedSig, 1))
            return;
        if (QtMocHelpers::indexOfMethod<void (GamePage::*)()>(_a, &GamePage::menu_continueClickedSig, 2))
            return;
        if (QtMocHelpers::indexOfMethod<void (GamePage::*)()>(_a, &GamePage::over_quitClickedSig, 3))
            return;
        if (QtMocHelpers::indexOfMethod<void (GamePage::*)()>(_a, &GamePage::over_retryClickedSig, 4))
            return;
    }
}

const QMetaObject *GamePage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GamePage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_staticMetaObjectStaticContent<qt_meta_tag_ZN8GamePageE_t>.strings))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int GamePage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    }
    if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<QMetaType *>(_a[0]) = QMetaType();
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void GamePage::menu_quitClickedSig()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void GamePage::menu_retryClickedSig()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void GamePage::menu_continueClickedSig()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void GamePage::over_quitClickedSig()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void GamePage::over_retryClickedSig()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
