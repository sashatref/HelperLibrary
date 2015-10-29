#pragma once

class QString;
class QMainWindow;

#include <QFile>
#include <QVariant>


namespace SaveLoad
{
    template<typename T>
    bool loadLayout(const QString &_path, T *_mainWindow)
    {
        QFile file(_path);
        if (!file.open(QFile::ReadOnly))
        {
            return false;
        }

        uchar geo_size;
        QByteArray geo_data;
        QByteArray layout_data;

        bool ok = file.getChar((char*)&geo_size);
        if (ok) {
            geo_data = file.read(geo_size);
            ok = geo_data.size() == geo_size;
        }
        if (ok) {
            layout_data = file.readAll();
            ok = layout_data.size() > 0;
        }

        if (ok)
            ok = _mainWindow->restoreGeometry(geo_data);
        if (ok)
            ok = _mainWindow->restoreState(layout_data);

        if (!ok) {
            return false;
        }
        return true;
    }

    template<typename T>
    bool saveLayout(const QString &_path, T *_mainWindow)
    {
        QFile file(_path);
        if (!file.open(QFile::WriteOnly))
        {
            return false;
        }

        QByteArray geo_data = _mainWindow->saveGeometry();
        QByteArray layout_data = _mainWindow->saveState();

        bool ok = file.putChar((uchar)geo_data.size());
        if (ok)
            ok = file.write(geo_data) == geo_data.size();
        if (ok)
            ok = file.write(layout_data) == layout_data.size();

        if (!ok) {
            return false;
        }
        return true;
    }

    template<typename T>
    bool loadSettings(const QString &_path, T &_settings)
    {
        QFile file(_path);

        if(file.open(QIODevice::ReadOnly))
        {
            QDataStream stream(&file);
            stream >> _settings;
            file.close();
        }

        return true;
    }

    template<typename T>
    bool saveSettings(const QString &_path, const T &_settings)
    {
        QFile file(_path);

        if(file.open(QIODevice::WriteOnly))
        {
            QDataStream stream(&file);
            stream << _settings;
            file.close();
        }

        return true;
    }

    template<typename T>
    QVariantList toVariantList(const QList<T> &_inputList)
    {
        QVariantList resultList;

        for(int i = 0 ; i < _inputList.count(); i++)
        {
            resultList.append(QVariant::fromValue(_inputList[i]));
        }

        return resultList;
    }
}

namespace Text
{
    bool writeToFile(const QString &_path, const QString &_text, bool _append = true);
    QString readFromFile(const QString &_path);

    QString textWithTimeStamp(const QString &_text);
    QString textWithDateTimeStamp(const QString &_text);
}



