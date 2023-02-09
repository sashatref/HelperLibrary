#pragma once

#include "../export.h"
#include <QVariantMap>
#include <QString>

class QByteArray;
class QString;
class QMainWindow;
class QSplitter;
class QHeaderView;
class QCheckBox;
class QToolButton;
class QComboBox;
class QFile;
class QSpinBox;
class QRadioButton;

namespace HelperLibraryNS
{
class SimpleTextFilter;
}

class HELPERLIBRARY_EXPORT LayoutSaver
{
    QVariantMap map;
public:
    LayoutSaver(const QVariantMap &_map);

    LayoutSaver();
    virtual ~LayoutSaver();

    QVariant &operator[](const QString &key);
    const QVariant operator[](const QString &key) const;

    QVariantMap::iterator insert(const QString &key, const QVariant &value);

    bool contains(const QString &_key) const;

    QVariant value(const QString &key, const QVariant &defaultValue = QVariant()) const;

    operator QVariantMap()
    {
        return map;
    }

    operator QVariant()
    {
        return map;
    }

    const QVariantMap &m() const
    {
        return map;
    }


    static void registerType();

    bool saveToFile(const QString &_fileName = "layout.bin");
    void saveToFile(QFile *_f);

    bool loadFromFile(const QString &_fileName = "layout.bin");

    template<class T>
    void save(const T _value, const QString &_str)
    {
        Q_STATIC_ASSERT_X(std::is_pointer<T>::value, "Type T is not a pointer");

        QVariant var = saveWidgetState(_value);
        insert(_str, var);
    }

    template<class T>
    bool load(T _value, const QString &_str) const
    {
        Q_STATIC_ASSERT_X(std::is_pointer<T>::value, "Type T is not a pointer");

        if(contains(_str))
        {
            loadWidgetState(_value, value(_str));
            return true;
        }
        return false;
    }


    template<class ArgumentType, class ClassType>
    void save(ClassType *_object, ArgumentType(ClassType::*_func)() const, const QString &_str)
    {
        auto it = (*_object.*_func)();
        save(QVariant::fromValue(it), _str);
    }


    template<class ArgumentType, class ClassType>
    bool load(ClassType *_object, void(ClassType::*_func)(ArgumentType), const QString &_str) const
    {
        QVariant val;
        if(load(val, _str))
        {
            (_object->*_func)(val.value<ArgumentType>());
            return true;
        }
        return false;
    }

    void save(const bool &_value, const QString &_str);
    void save(const double &_value, const QString &_str);
    void save(const int &_value, const QString &_str);
    void save(const QString &_value, const QString &_str);
    void save(const QStringList &_value, const QString &_str);
    void save(const QVariant &_value, const QString &_str);
    void save(const QByteArray &_value, const QString &_str);
    void save(const QFont &_value, const QString &_str);
    void save(const QVariantMap &_value, const QString &_str);
    void save(const QVariantList &_value, const QString &_str);
    void save(const QRect &_value, const QString &_str);
    void saveGeometry(const QWidget *_value, const QString &_str);
    void saveMainWindow(const QMainWindow *_value, const QString &_str);

    bool load(bool &_value, const QString &_str) const;
    bool load(double &_value, const QString &_str) const;
    bool load(int &_value, const QString &_str) const;
    bool load(QString &_value, const QString &_str) const;
    bool load(QStringList &_value, const QString &_str) const;
    bool load(QVariant &_value, const QString &_str) const;
    bool load(QByteArray &_value, const QString &_str) const;
    bool load(QFont &_value, const QString &_str) const;
    bool load(QRect &_value, const QString &_str) const;
    bool load(QVariantMap &_value, const QString &_str) const;
    bool load(QVariantList &_value, const QString &_str) const;

    bool loadGeometry(QWidget *_value, const QString &_str) const;
    bool loadMainWindow(QMainWindow *_value, const QString &_str) const;

    friend QDataStream &operator <<(QDataStream &s, const LayoutSaver &_v);
    friend QDataStream &operator >>(QDataStream &s, LayoutSaver &_v);
};

Q_DECLARE_METATYPE(LayoutSaver)

QVariant HELPERLIBRARY_EXPORT saveWidgetState(const QMainWindow *_mw);
void HELPERLIBRARY_EXPORT loadWidgetState(QMainWindow *_mw, const QVariant &_val);

QVariant HELPERLIBRARY_EXPORT saveWidgetState(const QSplitter *_sp);
void HELPERLIBRARY_EXPORT loadWidgetState(QSplitter *_sp, const QVariant &_val);

QVariant HELPERLIBRARY_EXPORT saveWidgetState(const QHeaderView *_hv);
void HELPERLIBRARY_EXPORT loadWidgetState(QHeaderView *_hv, const QVariant &_val);

QVariant HELPERLIBRARY_EXPORT saveWidgetState(const QCheckBox *_w);
void HELPERLIBRARY_EXPORT loadWidgetState(QCheckBox *_w, const QVariant &_val);

QVariant HELPERLIBRARY_EXPORT saveWidgetState(const QToolButton *_w);
void HELPERLIBRARY_EXPORT loadWidgetState(QToolButton *_w, const QVariant &_val);

QVariant HELPERLIBRARY_EXPORT saveWidgetState(const QComboBox *_w);
void HELPERLIBRARY_EXPORT loadWidgetState(QComboBox *_w, const QVariant &_val);

QVariant HELPERLIBRARY_EXPORT saveWidgetState(const QSpinBox *_w);
void HELPERLIBRARY_EXPORT loadWidgetState(QSpinBox *_w, const QVariant &_val);

QVariant HELPERLIBRARY_EXPORT saveWidgetState(const QRadioButton *_w);
void HELPERLIBRARY_EXPORT loadWidgetState(QRadioButton *_w, const QVariant &_val);

QVariant HELPERLIBRARY_EXPORT saveWidgetState(const HelperLibraryNS::SimpleTextFilter *_w);
void HELPERLIBRARY_EXPORT loadWidgetState(HelperLibraryNS::SimpleTextFilter *_w, const QVariant &_val);
