#include "languagehelper.h"

#include <QTranslator>
#include <QComboBox>

LanguageHelper::LanguageHelper(QObject *_parent):
    QObject                 (_parent),
    m_translatorList        (),
    m_languages             (),
    m_translatePath         ("./translate"),
    m_currentShortLanguage  ()
{

}

LanguageHelper::~LanguageHelper()
{
    deleteTr();
}

QString LanguageHelper::getCurrentFullLanguageName()
{
    if(m_languages.contains(m_currentShortLanguage))
    {
        return m_languages[m_currentShortLanguage].m_fullName;
    }
    return QString();
}


QString LanguageHelper::getCurrentShortLanguageName()
{
    return m_currentShortLanguage;
}

void LanguageHelper::setUseProgramLocale(bool _use)
{
    m_useProgramLocale = _use;
}

void LanguageHelper::registerLanguageList(const QList<HelperLibrary::UILangInfo> &_langList)
{
    for(auto &item : _langList)
    {
        registerLanguage(item.m_fullName, item.m_shortName, item.m_iconPath);
    }
}

void LanguageHelper::registerLanguage(const QString &_fullName,
                                      const QString &_shortName,
                                      const QString &_icon)
{
    HelperLibrary::UILangInfo info;
    info.m_iconPath = _icon;
    info.m_shortName = _shortName;
    info.m_fullName = _fullName;

    m_languages[_shortName] = info;
}

void LanguageHelper::createActions(QMenu * const _menu, const QString &_defaultLanguage)
{
    for(auto it = m_languages.begin(); it != m_languages.end(); ++it)
    {
        QString key = it.key();

        QAction *action = new QAction(_menu);
        action->setText(m_languages[key].m_fullName);
        action->setData(m_languages[key].m_shortName); //краткое имя
        action->setObjectName("action_" + key);

//        const QSize size = m_languages[key].m_icon.actualSize(QSize(200, 200));
//        QPixmap pix = m_languages[key].m_icon.pixmap(size);
//        m_languages[key].m_icon.addPixmap(pix.scaled(25,25, Qt::KeepAspectRatio), QIcon::Active, QIcon::On);
//        m_languages[key].m_icon.addPixmap(pix.scaled(20,20, Qt::KeepAspectRatio), QIcon::Active, QIcon::Off);

        if(!m_languages[key].m_iconPath.isEmpty())
        {
            action->setIcon(QIcon(m_languages[key].m_iconPath));
        }

        action->setCheckable(true);
        _menu->addAction(action);
        QObject::connect(action, &QAction::triggered, [this, _menu, action]()
        {
            for(int j = 0 ; j < _menu->actions().size(); j++)
            {
                _menu->actions().at(j)->setChecked(action == _menu->actions().at(j) ? true : false);
            }

            this->updateUiByShortName(action->data().toString());
        });

        if(_defaultLanguage == action->data().toString())
        {
            emit action->triggered(true);
        }
    }
}

void LanguageHelper::initCombo(QComboBox * const _combo, const QString &_defaultLanguage)
{
    _combo->clear();

    connect(_combo, &QComboBox::currentTextChanged, this, &LanguageHelper::updateUiByFullName);
    for(auto it = m_languages.begin(); it != m_languages.end(); ++it)
    {
        QString shortName = it.key();
        HelperLibrary::UILangInfo langInfo = m_languages[shortName];

        _combo->addItem(langInfo.m_fullName);

        if(shortName == _defaultLanguage)
        {
            _combo->setCurrentText(langInfo.m_fullName);
        }
    }
}

QMap<QString, HelperLibrary::UILangInfo> LanguageHelper::getLanguages() const
{
    return m_languages;
}

void LanguageHelper::setLanguagePath(const QString &_path)
{
    m_translatePath = _path;
}

bool LanguageHelper::updateUiByFullName(const QString &_fullName)
{
    for(auto it = m_languages.begin(); it != m_languages.end(); ++it)
    {
        const QString key = it.key();
        if(m_languages[key].m_fullName == _fullName)
        {
            return updateUiByShortName(m_languages[key].m_shortName);
        }
    }

    qWarning() << QString("Language <%1> not specified").arg(_fullName);
    return false;
}

bool LanguageHelper::updateUiByShortName(const QString &_shortName)
{
    if(m_languages.contains(_shortName))
    {
        m_currentShortLanguage = _shortName;
        //удаляем установленные ранее транслейтеры

        deleteTr();

        //загружаем новые и добавляем их в список
        {
            QDir trDir(m_translatePath);
            if(trDir.exists())
            {
                QStringList files = trDir.entryList(QStringList() << _shortName + "_" + "*.qm");

                for(auto &it : files)
                {
                    QTranslator *translator = new QTranslator();
                    translator->load(it, m_translatePath);
                    qApp->installTranslator(translator);
                    m_translatorList.append(translator);
                }
            }
        }

        //загрузка нового формата appName_lang.ts из каталога tranlsations

        {
#ifdef Q_OS_MACOS
            QDir trDir(qApp->applicationDirPath() + "/../Resources/translations");
#else
            QDir trDir(qApp->applicationDirPath() + "/translations");
#endif
            if(trDir.exists())
            {
                QStringList files = trDir.entryList(QStringList() << QString("*_%1.qm").arg(_shortName));

                for(auto &it : files)
                {
                    QTranslator *translator = new QTranslator();
                    translator->load(it, trDir.path());
                    qApp->installTranslator(translator);
                    m_translatorList.append(translator);
                }
            }
        }

        if(m_useProgramLocale)
        {
            QLocale::setDefault(_shortName);
        }

        return true;
    }

    qWarning() << QString("Language <%1> not specified").arg(_shortName);
    return false;
}

void LanguageHelper::deleteTr()
{
    qDeleteAll(m_translatorList);
    m_translatorList.clear();
}
