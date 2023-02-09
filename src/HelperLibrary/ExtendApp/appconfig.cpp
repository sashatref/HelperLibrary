#include "appconfig.h"
#include "../anymacro.h"
#include "../converterfunctions.h"

namespace HelperLibrary
{

AppConfig::AppConfig()
{
    m_uiLangList
            << UILangInfo("English", "en")
            << UILangInfo("Русский", "ru");
}

void AppConfig::registerType()
{
    GadgetHelper::registerToIGadgetConverter<AppConfig>();
    Converters::registerToListConverter<UILangInfo>();
}

const QMetaObject *AppConfig::getMetaObject() const
{
    return &staticMetaObject;
}

QDebug operator<<(QDebug _debug, const AppConfig &_value)
{
    _debug.noquote();

    _debug
            << "UI Lang list:\n";
    for(auto &item : _value.m_uiLangList)
    {
        _debug << "UI Lang item (" << item << ")\n";
    }

    _debug << "Locale (";

    QLocale currL;

    _debug
            << "Country <" << QLocale::countryToString(currL.country()).toUtf8()
            << "> | Language <" << QLocale::languageToString(currL.language()).toUtf8()
            << "> | Script <" << QLocale::scriptToString(currL.script()).toUtf8();
    _debug << ">)\n";

    _debug << "Custom properties:";

    for(auto it = _value.m_customProps.begin(); it != _value.m_customProps.end(); it++)
    {
        _debug << QString("Key <%1> | Value <").arg(it.key()) << it.value() << ">";
    }

    return _debug;
}

}
