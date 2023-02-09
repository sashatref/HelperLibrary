#include "../LanguageHelper/LanguageCombo.h"
#include "LanguageComboPlugin.h"

namespace HelperLibraryNS
{

LanguageComboPlugin::LanguageComboPlugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void LanguageComboPlugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool LanguageComboPlugin::isInitialized() const
{
    return initialized;
}

QWidget *LanguageComboPlugin::createWidget(QWidget *parent)
{
    LanguageCombo *widget = new LanguageCombo(parent);
    return widget;
}

QString LanguageComboPlugin::name() const
{
    return "LanguageCombo";
}

QString LanguageComboPlugin::group() const
{
    return "Custom widgets";
}

QIcon LanguageComboPlugin::icon() const
{
    return QIcon();
}

QString LanguageComboPlugin::toolTip() const
{
    return "";
}

QString LanguageComboPlugin::whatsThis() const
{
    return "";
}

bool LanguageComboPlugin::isContainer() const
{
    return false;
}

QString LanguageComboPlugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"LanguageCombo\" name=\"languageCombo\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>350</width>\n"
           "    <height>500</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString LanguageComboPlugin::includeFile() const
{
    return "HelperLibrary/LanguageHelper/languagecombo.h";
}

}
