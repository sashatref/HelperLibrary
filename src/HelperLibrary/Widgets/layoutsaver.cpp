#include "project_pch.h"
#include "layoutsaver.h"
#include "setgetMacro.h"
#include "isavewidget.h"
#include "extendedmainwindow.h"
#include "anymacro.h"

#include <QHeaderView>
#include <QComboBox>
#include <QSplitter>
#include <QSpinBox>
#include <QRadioButton>

#include "../SimpleTextFilter.h"

PS_REGISTER_CONSTRUCTOR_FUNC(&LayoutSaver::registerType)

QVariant saveWidgetState1(const QWidget *_sw);
void loadWidgetState1(QWidget *_sw, const QVariant &_val);

LayoutSaver::LayoutSaver(const QVariantMap &_map):
    map(_map)
{

}

LayoutSaver::LayoutSaver()
{
    qRegisterMetaTypeStreamOperators<QList<QMap<int, QVariant>>>();
}

LayoutSaver::~LayoutSaver()
{

}

QVariant &LayoutSaver::operator[](const QString &key)
{
    return map.operator [](key);
}

const QVariant LayoutSaver::operator[](const QString &key) const
{
    return map.operator [](key);
}

QVariantMap::iterator LayoutSaver::insert(const QString &key, const QVariant &value)
{
    return map.insert(key, value);
}

bool LayoutSaver::contains(const QString &_key) const
{
    return map.contains(_key);
}

QVariant LayoutSaver::value(const QString &key, const QVariant &defaultValue) const
{
    return map.value(key, defaultValue);
}

void LayoutSaver::registerType()
{
    qRegisterMetaType<LayoutSaver>("LayoutSaver");
    qRegisterMetaTypeStreamOperators<LayoutSaver>("LayoutSaver");
}

bool LayoutSaver::saveToFile(const QString &_fileName)
{
    QFile file(_fileName);
    if(!file.open(QIODevice::WriteOnly))
    {
        return false;
    }

    saveToFile(&file);

    return true;
}

void LayoutSaver::saveToFile(QFile *_f)
{
    QDataStream stream(_f);
    stream.setVersion(QDataStream::Qt_5_5);
    stream << map;
}

QDataStream &operator <<(QDataStream &s, const LayoutSaver &_v)
{
    s << _v.map;
    return s;
}

QDataStream &operator >>(QDataStream &s, LayoutSaver &_v)
{
    s >> _v.map;
    return s;
}

bool LayoutSaver::loadFromFile(const QString &_fileName)
{
    QFile file(_fileName);
    if(!file.open(QIODevice::ReadOnly))
    {
        return false;
    }

    QDataStream stream(&file);
    stream.setVersion(QDataStream::Qt_5_5);
    stream >> map;

    return true;
}

void LayoutSaver::save(const bool &_value, const QString &_str)
{
    insert(_str, _value);
}

void LayoutSaver::save(const double &_value, const QString &_str)
{
    insert(_str, _value);
}

void LayoutSaver::save(const int &_value, const QString &_str)
{
    insert(_str, _value);
}

void LayoutSaver::save(const QString &_value, const QString &_str)
{
    insert(_str, _value);
}

void LayoutSaver::save(const QStringList &_value, const QString &_str)
{
    insert(_str, _value);
}

void LayoutSaver::save(const QVariant &_value, const QString &_str)
{
    insert(_str, _value);
}

void LayoutSaver::save(const QByteArray &_value, const QString &_str)
{
    insert(_str, _value);
}

void LayoutSaver::save(const QFont &_value, const QString &_str)
{
    insert(_str, _value);
}

void LayoutSaver::save(const QVariantMap &_value, const QString &_str)
{
    insert(_str, _value);
}

void LayoutSaver::save(const QVariantList &_value, const QString &_str)
{
    insert(_str, _value);
}

void LayoutSaver::save(const QRect &_value, const QString &_str)
{
    insert(_str, _value);
}

void LayoutSaver::saveGeometry(const QWidget *_value, const QString &_str)
{
    insert(_str, saveWidgetState1(_value));
}

void LayoutSaver::saveMainWindow(const QMainWindow *_value, const QString &_str)
{
    insert(_str, saveWidgetState(_value));
}

bool LayoutSaver::load(bool &_value, const QString &_str) const
{
    if(contains(_str))
    {
        _value = value(_str).toBool();
        return true;
    }
    return false;
}

bool LayoutSaver::load(double &_value, const QString &_str) const
{
    if(contains(_str))
    {
        _value = value(_str).toDouble();
        return true;
    }
    return false;
}

bool LayoutSaver::load(int &_value, const QString &_str) const
{
    if(contains(_str))
    {
        _value = value(_str).toInt();
        return true;
    }
    return false;
}

bool LayoutSaver::load(QString &_value, const QString &_str) const
{
    if(contains(_str))
    {
        _value = value(_str).toString();
        return true;
    }
    return false;
}

bool LayoutSaver::load(QStringList &_value, const QString &_str) const
{
    if(contains(_str))
    {
        _value = value(_str).toStringList();
        return true;
    }
    return false;
}

bool LayoutSaver::load(QVariant &_value, const QString &_str) const
{
    if(contains(_str))
    {
        _value = value(_str);
        return true;
    }
    return false;
}

bool LayoutSaver::load(QByteArray &_value, const QString &_str) const
{
    if(contains(_str))
    {
        _value = value(_str).toByteArray();
        return true;
    }
    return false;
}

bool LayoutSaver::load(QFont &_value, const QString &_str) const
{
    if(contains(_str))
    {
        _value = value(_str).value<QFont>();
        return true;
    }
    return false;
}

bool LayoutSaver::load(QRect &_value, const QString &_str) const
{
    if(contains(_str))
    {
        _value = value(_str).toRect();
        return true;
    }
    return false;
}

bool LayoutSaver::load(QVariantMap &_value, const QString &_str) const
{
    if(contains(_str))
    {
        _value = value(_str).toMap();
        return true;
    }
    return false;
}

bool LayoutSaver::load(QVariantList &_value, const QString &_str) const
{
    if(contains(_str))
    {
        _value = value(_str).toList();
        return true;
    }
    return false;
}

bool LayoutSaver::loadGeometry(QWidget *_value, const QString &_str) const
{
    if(contains(_str))
    {
        loadWidgetState1(_value, value(_str));
        return true;
    }
    return false;
}

bool LayoutSaver::loadMainWindow(QMainWindow *_value, const QString &_str) const
{
    if(contains(_str))
    {
        loadWidgetState(_value, value(_str));
        return true;
    }
    return false;
}


QVariant saveWidgetState(const QMainWindow *_mw)
{
    LayoutSaver m;
    m.save(_mw->saveState(), "state");
    m.save(_mw->saveGeometry(), "geometry");

    return m.m();
}

void loadWidgetState(QMainWindow *_mw, const QVariant &_val)
{
    LayoutSaver saver = _val.toMap();
    QByteArray state, geometry;

    if(saver.load(geometry, "geometry"))
    {
        _mw->restoreGeometry(geometry);
    }
    if(saver.load(state, "state"))
    {
        _mw->restoreState(state);
    }
}




QVariant saveWidgetState(const QSplitter *_sp)
{
    return QVariant::fromValue(_sp->sizes());
}

void loadWidgetState(QSplitter *_sp, const QVariant &_val)
{
    _sp->setSizes(_val.value<QList<int>>());
}

QVariant saveWidgetState1(const QWidget *_sw)
{
    LayoutSaver m;
    m.save(_sw->saveGeometry(), "geometry");
    return m.m();
}

void loadWidgetState1(QWidget *_sw, const QVariant &_val)
{
    LayoutSaver saver = _val.toMap();
    QByteArray geometry;

    if(saver.load(geometry, "geometry"))
    {
        _sw->restoreGeometry(geometry);
    }
}



QVariant saveWidgetState(const QHeaderView *_hv)
{
    return _hv->saveState();
}

void loadWidgetState(QHeaderView *_hv, const QVariant &_val)
{
    _hv->restoreState(_val.toByteArray());
}

QVariant saveWidgetState(const QCheckBox *_w)
{
    return _w->isChecked();
}

void loadWidgetState(QCheckBox *_w, const QVariant &_val)
{
    _w->setChecked(_val.toBool());
}

QVariant saveWidgetState(const QToolButton *_w)
{
    return _w->isChecked();
}

void loadWidgetState(QToolButton *_w, const QVariant &_val)
{
    _w->setChecked(_val.toBool());
}

QVariant saveWidgetState(const QComboBox *_w)
{
    QVariantMap out;

    out["currentText"] = _w->currentText();

    QList<QMap<int, QVariant>> items;

    QList<int> roles = { Qt::DisplayRole, Qt::UserRole, Qt::UserRole + 1, Qt::UserRole + 2 };

    for(int i = 0 ; i < _w->count(); i++)
    {
        QMap<int, QVariant> tempMap;

        for(int j = 0 ; j < roles.size(); j++)
        {
            QVariant v = _w->itemData(i, roles[j]);
            if(v.isValid())
            {
                tempMap[roles[j]] = v;
            }
        }

        items << tempMap;
    }

    out["data"] = QVariant::fromValue(items);

    return out;
}

void loadWidgetState(QComboBox *_w, const QVariant &_val)
{
    const QVariantMap map = _val.toMap();

    _w->clear();

    QList<QMap<int, QVariant>> items = map["data"].value<QList<QMap<int, QVariant>>>();

    for(int i = 0 ; i < items.size(); i++)
    {
        QMap<int, QVariant> curr = items.at(i);

        _w->addItem(curr[Qt::DisplayRole].toString());

        for(auto it = curr.begin(); it != curr.end(); ++it)
        {
            _w->setItemData(i, it.value(), it.key());
        }
    }

    _w->setCurrentText(map["currentText"].toString());
}

QVariant saveWidgetState(const QSpinBox *_w)
{
    return _w->value();
}

void loadWidgetState(QSpinBox *_w, const QVariant &_val)
{
    _w->setValue(_val.toInt());
}

QVariant saveWidgetState(const QRadioButton *_w)
{
    return _w->isChecked();
}

void loadWidgetState(QRadioButton *_w, const QVariant &_val)
{
    _w->setChecked(_val.toBool());
}

QVariant saveWidgetState(const HelperLibraryNS::SimpleTextFilter *_w)
{
    return _w->save();
}

void loadWidgetState(HelperLibraryNS::SimpleTextFilter *_w, const QVariant &_val)
{
    _w->load(_val);
}
