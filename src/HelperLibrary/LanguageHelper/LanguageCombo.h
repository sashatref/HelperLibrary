#pragma once

#include <QWidget>
#include <QComboBox>

#include "../export.h"

class LanguageHelper;

class HELPERLIBRARY_EXPORT LanguageCombo : public QComboBox
{
    Q_OBJECT
    Q_PROPERTY(bool textVisible READ getTextVisible WRITE setTextVisible)
    Q_PROPERTY(bool iconsVisible READ getIconsVisible WRITE setIconsVisible)
public:
    LanguageCombo(QWidget *parent = 0);

    void initFromHelper(const LanguageHelper *const _helper, const QString &_defaultShortLang);

    void addItem(const QString &_fullName, const QString &_shortName, const QString &_icon);

    void setTextVisible(bool _textVisible);
    bool getTextVisible() const;

    bool getIconsVisible() const;
    void setIconsVisible(bool _isVisible);

signals:
    void currentLangChanged(const QString &_shortName, const QString &_fullName);
    void currentShortLangChanged(const QString &_shortName);
    void currentFullLangChanged(const QString &_fullName);

private slots:
    void onItemChanged(int _index);

private:
    bool m_textVisible;
    bool m_iconsVisible;
};
