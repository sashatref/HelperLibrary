#pragma once

#include <QString>
#include <QVariant>
#include <QObject>
#include "../export.h"
#include "../Widgets/layoutsaver.h"

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT AbstractPlugin : public QObject
{
    Q_OBJECT
public:
    virtual ~AbstractPlugin() {}

    /*!
     * \brief имя плагина, будет отображена в окне списка плагинов,
     * используется для названия док виджета с виджетом плагина.
     * \return
     */
    Q_INVOKABLE virtual QString getName() const = 0;

    /*!
     * \brief версия плагина, будет отображена в окне списка плагинов
     * \return
     */
    Q_INVOKABLE virtual QString getVersion() const = 0;

    /*!
     * \brief описение плагина, будет отображена в окне списка плагинов
     * \return
     */
    Q_INVOKABLE virtual QString getDescription() const = 0;

    /*!
     * \brief загрузка настроек в плагин после запуска программы
     * \return
     */
    virtual void onSettingsLoad(const QVariant &_settings) { Q_UNUSED(_settings); }

    /*!
     * \brief сохранение настроек плагина перед закрытием программы
     * \return
     */
    virtual QVariant onSettingsSave() const { return QVariant(); }

    virtual void saveLayout(LayoutSaver &_saver) { Q_UNUSED(_saver); }
    virtual void loadLayout(const LayoutSaver &_saver) { Q_UNUSED(_saver); }

    bool m_isLoaded = false;
    bool m_isEnabled = true;
    QString m_uniqueName;

    QString getUniquePluginName() const
    {
        return m_uniqueName;
    }

    virtual void turnOn() = 0;
    virtual void turnOff() = 0;

signals:
    /*!
     * \brief оправка сообщения, которое нужно записать в окно лога
     * \param _text текст
     */
    void logMessage(const QString &_text, QtMsgType _msgType);
};



}

Q_DECLARE_METATYPE(HelperLibraryNS::AbstractPlugin*)

