#pragma once

#include "../export.h"
#include <QApplication>

struct ExtendAppP;
class LayoutSaver;
class SingleApplicationPrivate;
class QCommandLineParser;
class LanguageHelper;

namespace HelperLibrary
{
    class AppConfig;
}

namespace HelperLibraryNS
{
    class AppSettings;
}



#if defined(qApp)
#undef qApp
#endif
#define qApp (static_cast<ExtendApp *>(QCoreApplication::instance()))

class HELPERLIBRARY_EXPORT ExtendApp : public QApplication
{
    Q_OBJECT
public:
    ExtendApp(int &argc, char **argv, const QString &_uniqueName = "", int flags = ApplicationFlags);
    ~ExtendApp();

    virtual bool notify(QObject *o, QEvent *e) override;

    /*!
     * \brief emitSettingChangeEvent отправляет всем виджетам событие (QEvent) SettingsChanged
     * используется после изменения настроек программы, для применения новый параметров.
     */
    static void emitSettingChangeEvent();

    // map <check name, check config>
    bool checkLicense(const QList<QPair<QString, QVariant>> &_config);
    bool checkLicense(const QStringList &_config);

    void setDefaultSettingsPath(const QString &_path);
    void setDefaultLayoutPath(const QString &_path);

    /*!
     * \brief setSaveLayoutOnAppQuit устанавливает флаг, будет ли при завершение программы сохранен
     * LayouSaver
     * \param _isEnable
     */
    void setSaveLayoutOnAppQuit(bool _isEnable);

    /*!
     * \brief getSaveLayoutOnAppQuit возвращает флаг, будет ли при завершение программы
     * сохранен LayoutSaver
     * \return
     */
    bool getSaveLayoutOnAppQuit() const;


    /*!
     * \brief getLayoutSaver возвращает указательно на LayoutSaver программы
     * \return
     */
    LayoutSaver *getLayoutSaver();

    const HelperLibrary::AppConfig *getAppConfig() const;
    const HelperLibraryNS::AppSettings *getAppSettings() const;

    /*!
     * \brief getSettingsPath возвращает путь к файлу настроек программы
     * \return
     */
    QString getSettingsPath() const;

    /*!
     * \brief getLayoutFilePath возвращает путь к файлу, из/в который будет сохранено/загружено
     * расположение окон и состояние виджетов.
     * \return
     */
    QString getLayoutFilePath() const;

    QString getAppConfigFilePath() const;

    /*!
     * \brief loadLayout загружает состояние LayoutSaver из файла getLayoutFilePath()
     */
    void loadLayout();

    /*!
     * \brief saveLayout сохраняет состояние LayoutSaver в файл getLayoutFilePath()
     */
    void saveLayout();



    template <class Type>
    void loadSettings(Type *_settings)
    {
        QVariant val = QVariant::fromValue(*_settings);
        loadSettings(val);
        *_settings = val.value<Type>();
    }

    /*!
     *  Загрузка настроек из xml файла по адресу <getSettingsPath()>
     */

    void loadSettings(QVariant &_settings);

    template<class Type>
    void saveSettings(const Type *_settings)
    {
        saveSettings(QVariant::fromValue(*_settings));
    }

    /*!
     *  Сохранение настроек в xml файл по адресу <getSettingsPath()>
     */

    void saveSettings(const QVariant &_settings);


    /*!
     * \brief isRunning показывает, была ли уже запущена другая копия этого приложения
     * \return
     */
    bool isRunning();


    /*!
     * \brief getCmdParser возвращает указатель на парсер параметров запуска
     * \return
     */
    QCommandLineParser *getCmdParser();

    /*!
     * \brief parseCommandLine выполняет разбор параметров запуска и инициализирует нужные переменные
     */
    void parseCommandLine();

    LanguageHelper *langugeHelper();

signals:
    /*!
     * \brief onExceptionMsg сигнал срабатывает при получение исключения в gui потоке
     * \param _msg
     */
    void onExceptionMsg(const QString &_msg);

    /*!
     * \brief onAnotherInstanceLaunch срабатывает при попытке запуска другого экземпляра программы
     */
    void onAnotherInstanceLaunch();

private:
    ExtendAppP *p;
    SingleApplicationPrivate *saP;

    void initCommandLineParser(QCommandLineParser &_parser) const;

};
