/********************************************************************
#	created:
#	filename: 	LanguageHelper.h LanguageHelper.cpp
#	author:		Aleksandr Neborak

#	Copyright (C) Avia Ltd. Ukraine. Kremenchug 2016
#	All Rights Reserved

#	class: Language Helper

#   Класс LanguageHelper предназначен для упрощения организации возможности
#   локализации программы
#   Имеет фукнцию для инициализации указнного QMenu элементами QAction, при нажатие на которые будут
#   загружены локализации, найденные в каталоге, указанном функцией setLanguagePath или занчение по-умолчанию "./translate"
#   Функцию для инициализации QComboBox необходимыми значениями и загрузкой локализаций при изменение.

#   Примерный алгоритм использования:
#   1.После запуска программы зарегестрировать все языки, с помощью функции registerLanguage, указав полное и короткое название
    например:
        LanguageHelper::registerLanguage("Русский", "ru");
        LanguageHelper::registerLanguage("English", "en");

    2.Если необходимо искать файлы переводов в каталоге отличном от "./translate", то выполнить функцию:
        LanguageHelper::setLanguagePath("путь/к/qm-файлам");

    3.Заполнить комбобокс или пункт меню функциями:
        LanguageHelper::initCombo(ui->languageComboBox, MainWndSettSingleton::ins().get_language());
        LanguageHelper::createActions(ui->menuLanguage, MainWndSettSingleton::ins().get_language());

    При смене языка(комбобокс или пункт меню) в каталоге, указанном функцией setLanguagePath будет
    произведен поиск и загружены все файлы <короткое обозначение языка>*.qm
        например:
            ru_accounting_lib.qm
            ru_AviaStudents.qm
            ru_protocolSupportPlugin.qm


    Для поддержки перевода, в каждой виджете неоходимо переопределить метод:
    void changeEvent(QEvent *event)
    {
        switch(event->type())
        {
        case QEvent::LanguageChange:
            ui->retranslateUi(this);
            //Перевести динамически созданные виджеты

            //сохранить текущее полное название языка в настройки, для возможности загрузки после перезапуска
            //программы: MainWndSettSingleton::ins().set_language(LanguageHelper::getCurrentLanguage());
            break;
        }

        QMainWindow::changeEvent(event);
    }

#*********************************************************************/

#pragma once

#include <QMap>
#include <QString>
#include <QIcon>

class QMenu;
class QTranslator;
class QComboBox;

#include "../export.h"
#include "../ExtendApp/uilanginfo.h"



class HELPERLIBRARY_EXPORT LanguageHelper : public QObject
{
    Q_OBJECT
public:
    LanguageHelper(QObject *_parent = 0);
    virtual ~LanguageHelper();

    QString getCurrentFullLanguageName();
    QString getCurrentShortLanguageName();

    void setUseProgramLocale(bool _use);

    void registerLanguageList(const QList<HelperLibrary::UILangInfo> &_langList);

    void registerLanguage(const QString &_fullName, const QString &_shortName, const QString &_icon = QString());

    void createActions(QMenu *const _menu, const QString &_defaultLanguage);
    void initCombo(QComboBox *const _combo, const QString &_defaultLanguage);

    QMap<QString, HelperLibrary::UILangInfo> getLanguages() const; //key - shortName

public slots:
    void setLanguagePath(const QString &_path);
    bool updateUiByFullName(const QString &_fullName);
    bool updateUiByShortName(const QString &_shortName);

    void deleteTr();

private:
    QList<QTranslator*> m_translatorList;       //список траслейтеров
    QMap<QString, HelperLibrary::UILangInfo> m_languages;        //список языков, key - короткое название
    QString m_translatePath;        //каталог локализаций
    QString m_currentShortLanguage; //короткое название языка
    bool m_useProgramLocale = false;
};

