#include "project_pch.h"
#include "extendapp.h"
#include "releaseassert.h"

#include "Exceptions/userexception.h"
#include "Events/settingchangeevent.h"
#include "Perfomance/scopetimer.h"
#include "Logger/logger.h"
#include "Serialization/serializer.h"

#include "Widgets/showiconsform.h"
#include "Widgets/layoutsaver.h"
#include "singleapplicationprivate.h"
#include "../LanguageHelper/languagehelper.h"
#include "appconfig.h"
#include "appsettings.h"
#include "../buildversion.h"
#include "AppLocker.h"

#include <ZipManager/zipwriter.h>

#include "../Security/SecurityPluginManager.h"
#include "../Security/ISecurityPlugin.h"

#include <QCommandLineParser>

namespace {
const QString mainSettingsNode = "MainSettings";
const QString appConfigNode = "appConfig";

void createPathForFile(const QString &_filePath)
{
    QDir().mkpath(QFileInfo(_filePath).absolutePath());
}

}



struct ExtendAppP
{
    ExtendAppP():
        lSaver              (),
        saveLayoutOnAppQuit (true)
    {

    }

    LoggerQt::Logger logger;
    LayoutSaver lSaver;
    HelperLibrary::AppConfig appConfig;
    HelperLibraryNS::AppSettings appSettings;

    bool saveLayoutOnAppQuit;
    QCommandLineParser m_cmdParser;
    LanguageHelper m_languageHelper;

    QList<HelperLibrary::UILangInfo> m_uiLangList;

    QString defaultSettingsPath = "settings.xml";
    QString defaultLayoutPath = "layout.bin";

    //если количество файлов превышает 15, то удаляем файлы старше 15 дней.
    void removeFilesOlderThan(const QString &_path)
    {
        const int days = 15;
        const int filesCount = 15;

        //получаем список существующих бэкапов
        QFileInfoList fInfoList = QDir(_path).entryInfoList(QStringList("*.zip"), QDir::Files | QDir::NoDotAndDotDot);

        //если количество бэкапов мало, то ничего не делаем
        if(fInfoList.size() < filesCount)
        {
            return;
        }

        QDate dt = QDate::currentDate();

        //удаляем файлы старше определенного возраста (15 дней)
        for(auto &fInfo : fInfoList)
        {
            if(fInfo.lastModified().date().daysTo(dt) > days)
            {
                QFile::remove(fInfo.filePath());
                qCInfo(extendApp) << QString("Remove old backup file [%1]").arg(fInfo.filePath());
            }
        }
    }

    void backupPrevLayout(const QString &_path)
    {
        const QString backupPath = QFileInfo(appSettings.m_layoutPath).absolutePath() + "/backup";
        if(!QDir().exists(backupPath))
        {
            QDir().mkpath(backupPath);
        }

        removeFilesOlderThan(backupPath);

        QFile sourceFile(_path);
        if(!sourceFile.open(QIODevice::ReadOnly))
        {
            return;
        }

        const QString backupFileName = QString("%1/layout_%2.zip")
                .arg(backupPath)
                .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss"));

        ZipWriter writer(backupFileName);
        writer.setCompressionPolicy(ZipWriter::AlwaysCompress);
        writer.addFile("layout.bin", &sourceFile);
        writer.close();
    }
};

//LoggerQt::Logger ExtendAppP::logger;

ExtendApp::ExtendApp(int &argc, char **argv, const QString &_uniqueName, int flags):
    QApplication(argc, argv, flags),
    saP(new SingleApplicationPrivate(this, _uniqueName))
{
    p = new ExtendAppP();
    HelperLibrary::UILangInfo::registerType();
    HelperLibrary::AppConfig::registerType();
    HelperLibraryNS::AppSettings::registerType();

    connect(this, &ExtendApp::aboutToQuit, [this]
    {
        if(p->saveLayoutOnAppQuit)
        {
            saveLayout();
        }
    });

    saP->initSingleApplication();

    setApplicationVersion(BuildVersion::getCurrentAppVersion().toString());
}

ExtendApp::~ExtendApp()
{
    delete p;
    delete saP;
}

bool ExtendApp::notify(QObject *o, QEvent *e)
{
    try
    {
        return QApplication::notify(o, e);
    }catch(HelperLibrary::UserExceptions::BaseException &e)
    {
        emit onExceptionMsg(e.getText() + "\n" + e.getStackTraceList().join("\n"));
    }
    catch(std::exception &e)
    {
        emit onExceptionMsg(e.what());
    }catch(...)
    {
        emit onExceptionMsg("Unknown exception");
    }

    return false;
}

void ExtendApp::emitSettingChangeEvent()
{
    QWidgetList widgets = QApplication::allWidgets();
    for(int i = 0 ; i < widgets.size(); i++)
    {
        QEvent *ev = new SettingChangeEvent();
        QApplication::postEvent(widgets.at(i), ev);
    }
}

bool ExtendApp::checkLicense(const QList<QPair<QString, QVariant> > &_config)
{
    using namespace HelperLibraryNS;

    SecurityPluginManager plMng;
    plMng.loadPlugins(QDir(qApp->applicationDirPath() + "/security"), "avia.ExtendApp.SecurityPlugin");

    for(auto &it : _config)
    {
        QScopedPointer<AbstractPlugin> pl(plMng.createPlugin(it.first));
        if(pl == nullptr)
        {
            qCCritical(extendApp) << QString("Can't create security plugin [%1]").arg(it.first);
            return false;
        }

        ISecurityPlugin *securityPlugin = qobject_cast<ISecurityPlugin*>(pl.data());
        if(securityPlugin == nullptr)
        {
            qCCritical(extendApp) << QString("Can't cast plugin [%1] to security plugin").arg(it.first);
            return false;
        }

        securityPlugin->setConfig(it.second);

        try
        {
            securityPlugin->makeCheck();
        } catch (std::exception &e)
        {
            qCCritical(extendApp) << QString("Error while check security plugin [%1] - [%2]")
                                     .arg(it.first).arg(e.what());
            return false;
        }
    }

    return true;
}

bool ExtendApp::checkLicense(const QStringList &_config)
{
    QList<QPair<QString, QVariant>> c;

    for(auto &it : _config)
    {
        c << qMakePair(it, QVariant());
    }

    return checkLicense(c);
}

void ExtendApp::setDefaultSettingsPath(const QString &_path)
{
    p->defaultSettingsPath = _path;
}

void ExtendApp::setDefaultLayoutPath(const QString &_path)
{
    p->defaultLayoutPath = _path;
}

void ExtendApp::setSaveLayoutOnAppQuit(bool _isEnable)
{
    p->saveLayoutOnAppQuit = _isEnable;
}

bool ExtendApp::getSaveLayoutOnAppQuit() const
{
    return p->saveLayoutOnAppQuit;
}

LayoutSaver *ExtendApp::getLayoutSaver()
{
    return &p->lSaver;
}

const HelperLibrary::AppConfig *ExtendApp::getAppConfig() const
{
    return &p->appConfig;
}

const HelperLibraryNS::AppSettings *ExtendApp::getAppSettings() const
{
    return &p->appSettings;
}

QString ExtendApp::getSettingsPath() const
{
    return p->appSettings.m_settingsPath;
}


QString ExtendApp::getLayoutFilePath() const
{
    return p->appSettings.m_layoutPath;
}

QString ExtendApp::getAppConfigFilePath() const
{
    return p->appSettings.m_appConfigPath;
}

void ExtendApp::loadLayout()
{
    ScopeTimer timer("Load main layout");
    p->lSaver.loadFromFile(p->appSettings.m_layoutPath);
}

void ExtendApp::saveLayout()
{
    ScopeTimer timer("Save main layout");

    createPathForFile(p->appSettings.m_layoutPath);
    p->backupPrevLayout(p->appSettings.m_layoutPath);
    p->lSaver.saveToFile(p->appSettings.m_layoutPath);
}

bool ExtendApp::isRunning()
{
    return saP->m_isRunning;
}

QCommandLineParser *ExtendApp::getCmdParser()
{
    return &p->m_cmdParser;
}

void ExtendApp::initCommandLineParser(QCommandLineParser &_parser) const
{
    _parser.addHelpOption();
    _parser.addVersionOption();

    QList<QCommandLineOption> opts;
    opts << QCommandLineOption(QStringList() << "s" << "setting-file",
                               tr("Path to setting file"),
                               "path",
                               p->defaultSettingsPath);

    opts << QCommandLineOption(QStringList() << "l" << "layout-file",
                               tr("Path to layout file"),
                               "path",
                               p->defaultLayoutPath);

    opts << QCommandLineOption(QStringList() << "ac" << "appConfig",
                               tr("Path to application configuration file"),
                               "path",
                               "appConfig.xml");

    opts << QCommandLineOption("showIcons",
                               tr("Show ListWidget with all icons in current style"));

    opts << QCommandLineOption("printAppConfig",
                               tr("Print loaded application config"));

    opts << QCommandLineOption("writeAppConfig",
                               tr("Write application config to file"),
                               "path",
                               "appConfig.xml");


    _parser.addOptions(opts);
}



void ExtendApp::parseCommandLine()
{
    initCommandLineParser(p->m_cmdParser);

    p->m_cmdParser.process(*this);

    p->appSettings.m_layoutPath = makePathAbsolute(p->m_cmdParser.value("l"));
    p->appSettings.m_settingsPath = makePathAbsolute(p->m_cmdParser.value("s"));
    p->appSettings.m_appConfigPath = makePathAbsolute(p->m_cmdParser.value("ac"));

    qCInfo(extendApp) << QString("Command line options | Layout <%1> | Settings <%2> | AppConfig <%3>")
               .arg(p->appSettings.m_layoutPath)
               .arg(p->appSettings.m_settingsPath)
               .arg(p->appSettings.m_appConfigPath);

    if(p->m_cmdParser.isSet("showIcons"))
    {
        ShowIconsForm *form = new ShowIconsForm();
        form->setAttribute(Qt::WA_DeleteOnClose);
        form->show();
    }
}

LanguageHelper *ExtendApp::langugeHelper()
{
    return &p->m_languageHelper;
}

void ExtendApp::loadSettings(QVariant &_settings)
{
    try
    {
        ScopeTimer timer("Load settings");
        SerializerQt::Serializer::load(_settings, QDir(getSettingsPath()), mainSettingsNode,
                                       SerializerQt::Serializer::IgnoreErrors);

        const bool appConfigExists = QFile::exists(getAppConfigFilePath());

        qCDebug(extendApp) << "Load app config:" << appConfigExists << " | " << getAppConfigFilePath();

        p->m_languageHelper.setUseProgramLocale(true);
        if(appConfigExists)
        {
            SerializerQt::Serializer::load(p->appConfig, QDir(getAppConfigFilePath()), appConfigNode,
                                           SerializerQt::Serializer::IgnoreErrors);
            QLocale::setDefault(p->appConfig.m_useSystemLocale ?
                                    QLocale::system() :
                                    QLocale(p->appConfig.m_localeName));
            p->m_languageHelper.setUseProgramLocale(p->appConfig.m_useProgramLocale);
        }

        p->m_languageHelper.registerLanguageList(p->appConfig.m_uiLangList);

        if(p->m_cmdParser.isSet("printAppConfig"))
        {
            qCInfo(extendApp) << "Application config:";
            qCInfo(extendApp) << p->appConfig;
        }

        if(p->m_cmdParser.isSet("writeAppConfig"))
        {
            const QString fileName = p->m_cmdParser.value("writeAppConfig");
            SerializerQt::Serializer::save(p->appConfig, QDir(fileName), appConfigNode);
            qCInfo(extendApp) << QString("Application config written to file <%1>").arg(fileName);
        }

        ExtendApp::emitSettingChangeEvent();
    }catch(std::exception &e)
    {
        qCWarning(extendApp) << QString("Exception while parse application config [%1] - [%2]")
                      .arg(getAppConfigFilePath())
                      .arg(e.what());
    }
}

void ExtendApp::saveSettings(const QVariant &_settings)
{
    try
    {
        createPathForFile(getSettingsPath());
        ScopeTimer timer("Save settings");
        SerializerQt::Serializer::append(_settings, QDir(getSettingsPath()), mainSettingsNode,
                                         SerializerQt::Serializer::IgnoreErrors);
    }catch(std::exception &e)
    {
        qCWarning(extendApp) << QString("Exception while save application config [%1] - [%2]")
                          .arg(getAppConfigFilePath())
                          .arg(e.what());
    }
}


