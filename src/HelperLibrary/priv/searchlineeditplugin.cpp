#include "searchlineeditplugin.h"
#include "Widgets/SearchLineEdit/searchlineedit.h"


namespace HelperLibraryNS
{

SearchLineEditPLugin::SearchLineEditPLugin(QObject *parent) : QObject(parent)
{
    initialized = false;
}

void SearchLineEditPLugin::initialize(QDesignerFormEditorInterface * /* core */)
{
    if (initialized)
        return;

    initialized = true;
}

bool SearchLineEditPLugin::isInitialized() const
{
    return initialized;
}

QWidget *SearchLineEditPLugin::createWidget(QWidget *parent)
{
    SearchLineEdit *widget = new SearchLineEdit(parent);
    return widget;
}

QString SearchLineEditPLugin::name() const
{
    return "HelperLibraryNS::SearchLineEdit";
}

QString SearchLineEditPLugin::group() const
{
    return "HelperLibrary_widgets";
}

QIcon SearchLineEditPLugin::icon() const
{
    return QIcon();
}

QString SearchLineEditPLugin::toolTip() const
{
    return "";
}

QString SearchLineEditPLugin::whatsThis() const
{
    return "";
}

bool SearchLineEditPLugin::isContainer() const
{
    return false;
}

QString SearchLineEditPLugin::domXml() const
{
    return "<ui language=\"c++\">\n"
           " <widget class=\"HelperLibraryNS::SearchLineEdit\" name=\"searchLineEdit\">\n"
           "  <property name=\"geometry\">\n"
           "   <rect>\n"
           "    <x>0</x>\n"
           "    <y>0</y>\n"
           "    <width>200</width>\n"
           "    <height>300</height>\n"
           "   </rect>\n"
           "  </property>\n"
           " </widget>\n"
           "</ui>\n";
}

QString SearchLineEditPLugin::includeFile() const
{
    return "HelperLibrary/Widgets/SearchLineEdit/SearchLineEdit.h";
}

}
