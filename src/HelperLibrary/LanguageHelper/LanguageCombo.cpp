#include "LanguageCombo.h"
#include "languagehelper.h"

#include "../ExtendApp/uilanginfo.h"

enum ComboRole
{
    FullNameRole = Qt::UserRole + 1,
    ShorNameRole = Qt::UserRole + 2
};

LanguageCombo::LanguageCombo(QWidget *parent):
    QComboBox(parent),
    m_textVisible(true),
    m_iconsVisible(true)
{
    connect(this,
            static_cast<void(QComboBox::*)(int)>(&LanguageCombo::currentIndexChanged),
            this,
            &LanguageCombo::onItemChanged);
}

void LanguageCombo::initFromHelper(const LanguageHelper * const _helper, const QString &_defaultShortLang)
{
    connect(this, &LanguageCombo::currentShortLangChanged, _helper, &LanguageHelper::updateUiByShortName);

    QMap<QString, HelperLibrary::UILangInfo> langs = _helper->getLanguages();
    QComboBox::clear();

    int i = 0;
    for(auto it = langs.begin(); it != langs.end(); ++it)
    {
        const HelperLibrary::UILangInfo &langInfo = it.value();

        addItem(langInfo.m_fullName, langInfo.m_shortName, langInfo.m_iconPath);

        if(langInfo.m_shortName == _defaultShortLang)
        {
            QComboBox::setCurrentIndex(i);
        }
        i++;
    }
}

void LanguageCombo::addItem(const QString &_fullName, const QString &_shortName, const QString &_icon)
{
    const int count = QComboBox::count();

    QIcon icon(_icon);
    QComboBox::insertItem(count,  m_textVisible ? _fullName : "");
    QComboBox::setItemData(count, _fullName, FullNameRole);
    QComboBox::setItemData(count, _shortName, ShorNameRole);
    QComboBox::setItemIcon(count, m_iconsVisible ? icon : QIcon());
}

void LanguageCombo::setTextVisible(bool _textVisible)
{
    m_textVisible = _textVisible;
}

bool LanguageCombo::getTextVisible() const
{
    return m_textVisible;
}

bool LanguageCombo::getIconsVisible() const
{
    return m_iconsVisible;
}

void LanguageCombo::setIconsVisible(bool _isVisible)
{
    m_iconsVisible = _isVisible;
}

void LanguageCombo::onItemChanged(int _index)
{
    emit currentLangChanged(itemData(_index, ShorNameRole).toString(),
                            itemData(_index, FullNameRole).toString());
    emit currentFullLangChanged(itemData(_index, FullNameRole).toString());
    emit currentShortLangChanged(itemData(_index, ShorNameRole).toString());
}
