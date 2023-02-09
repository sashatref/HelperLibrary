set(PROJECT_NAME HelperLibrary)

project(${PROJECT_NAME} VERSION 1.0.1)

set(SOURCES
    DomElementWrapper.cpp
    DomElementWrapper.h
    Exceptions/userexception.cpp
    Exceptions/userexception.h
    ExtendApp/AppLocker.cpp
    ExtendApp/AppLocker.h
    Json/JsonStreamParser.cpp
    Json/JsonStreamParser.h
    Json/JsonUtils.cpp
    Json/JsonUtils.h
    LanguageHelper/LanguageCombo.cpp
    LanguageHelper/LanguageCombo.h
    PluginHelper/baseplugincreatormanager.cpp
    PluginHelper/baseplugincreatormanager.h
    PluginHelper/iplugincreator.cpp
    PluginHelper/iplugincreator.h
    PluginHelper/preloadplugininfo.cpp
    PluginHelper/preloadplugininfo.h
    Randomizer.cpp
    Randomizer.h
    Resources/rcc.cpp
    Resources/rcc.h
    Resources/resourcecompilier.cpp
    Resources/resourcecompilier.h
    Resources/resourceexplorer.cpp
    Resources/resourceexplorer.h
    Resources/resourceexplorerdialog.cpp
    Resources/resourceexplorerdialog.h
    Scenario/scenarioinvoker.cpp
    Security/ISecurityPlugin.cpp
    Security/SecurityList.cpp
    Security/SecurityPluginManager.cpp
    SimpleTextFilter.cpp
    TcpBrowserProtocol.cpp
    Widgets/EnumEditor/enumeditorform.cpp
    Widgets/FilterWidget/filterwidget.cpp
    Widgets/FilterWidget/priv/filterwidgetconf.cpp
    Widgets/FilterWidget/priv/filterwidgetconfigdialog.cpp
    Widgets/SimplePresetCombo/SimplePresetCombo.cpp
    Widgets/SimpleTextFilter/SimpleTextFilterDialog.cpp
    Widgets/TrayMenu/traymenu.cpp
    Widgets/flowlayout.cpp
    Widgets/independentwidgetholder.cpp
    Widgets/infowindow.cpp
    Widgets/makepasswordform.cpp
    Widgets/myprogressdialog.cpp
    Widgets/selectlistdialog/selectlistdialog.cpp
    Widgets/waitdialog.cpp
    Widgets/whatiisthistoolbutton.cpp
    Widgets/widgethelper.cpp
    Widgets/widgetanimation.cpp
    Widgets/imagewidget.cpp
    Widgets/imagelistwidget.cpp
    Widgets/keyboardlayoutviewer.cpp
    Widgets/showiconsform.cpp
    Widgets/extendedwidget.cpp
    Widgets/extendeddialog.cpp
    Widgets/singlewidget.cpp
    Widgets/extendedmainwindow.cpp
    Widgets/isavewidget.cpp
    converterfunctions.cpp
    Widgets/dialogwrapper.cpp
    filedownloader.cpp
    functions.cpp
    mathematics.cpp
    pdf/PdfExporter.cpp
    php.cpp
    programlauncher.cpp
    xmlutils.cpp
    eventlistener.cpp
    objectfactory.cpp
    iobject.cpp
    LanguageHelper/languagehelper.cpp
    ivariant.cpp
    buildversion.cpp
    simplecrypt.cpp
    Styles/iconsenum.cpp
    Perfomance/scopetimer.cpp
    Widgets/layoutsaver.cpp
    ExtendApp/extendapp.cpp
    ExtendApp/uilanginfo.cpp
    ExtendApp/appconfig.cpp
    ExtendApp/singleapplicationprivate.cpp
    Events/settingchangeevent.cpp
    signalwaiter.cpp
    Widgets/progressdialog.cpp
    IGadget/VariantMapHelper.cpp
    IGadget/igadget.cpp
    translithelper.cpp
    cmdargs.cpp
    ExtendApp/appsettings.cpp
    MultiPart/multipartparser.cpp
    MultiPart/multipartfile.cpp
    Decorator/basedecorator.cpp
    FileBasedProject/FileBasedProject.cpp
    FileBasedProject/filebasedprojectp.cpp
    Widgets/ListWidgets/extlist.cpp
    Widgets/VariantMapEditor/variantmapeditor.cpp
    Widgets/VariantMapEditor/priv/variantmapmodel.cpp
    Widgets/ListWidgets/presetslist.cpp
    Widgets/Text/complextexteditor.cpp
    Widgets/Text/complextextdialog.cpp
    Widgets/Text/priv/complextexteditorp.cpp
    Widgets/Text/priv/jsonsyntax.cpp
    Widgets/Text/priv/xmlsyntax.cpp
    cistring.cpp
    JsonProtocol/jsonprotocolhelper.cpp
    JsonProtocol/jsonmessage.cpp
    Widgets/SearchForm/searchform.cpp
    Widgets/SearchForm/priv/searchformp.cpp
    Widgets/SearchForm/listwidgetsearcher.cpp
    Widgets/SearchForm/isearcher.h
    Widgets/SearchForm/isearcher.cpp
    Widgets/SearchForm/searchform.h
    Widgets/SearchForm/priv/searchformp.h
    Widgets/SearchForm/listwidgetsearcher.h
    Widgets/SearchForm/searchform.ui
    Widgets/Actions/statusaction.cpp
    FunctionWrappper.cpp
    Widgets/PresetController/priv/presetcontrollerp.cpp
    Widgets/PresetController/presetcontrollerform.cpp
    Widgets/SearchLineEdit/searchlineedit.cpp
    Widgets/Text/priv/isyntax.cpp
    Widgets/aboutdialog.cpp
    JsonProtocol/datatransfer.cpp
    PluginHelper/priv/plugindetails.cpp
    PluginHelper/plugininfoview.cpp
    PluginHelper/basepluginmanager.cpp
    PluginHelper/pluginliststate.cpp
    Styles/stylefilewatcher.cpp
    Scenario/scenarioinvoker.h
    Security/ISecurityPlugin.h
    Security/SecurityList.h
    Security/SecurityPluginManager.h
    SimpleTextFilter.h
    TcpBrowserProtocol.h
    Widgets/EnumEditor/enumeditorform.h
    Widgets/FilterWidget/filterwidget.h
    Widgets/FilterWidget/priv/filterwidgetconf.h
    Widgets/FilterWidget/priv/filterwidgetconfigdialog.h
    Widgets/SimplePresetCombo/SimplePresetCombo.h
    Widgets/SimpleTextFilter/SimpleTextFilterDialog.h
    Widgets/TrayMenu/traymenu.h
    Widgets/flowlayout.h
    Widgets/independentwidgetholder.h
    Widgets/makepasswordform.h
    Widgets/myprogressdialog.h
    Widgets/selectlistdialog/selectlistdialog.h
    Widgets/waitdialog.h
    Widgets/whatiisthistoolbutton.h
    Widgets/widgetanimation.h
    Widgets/imagewidget.h
    Widgets/imagelistwidget.h
    Widgets/widgethelper.h
    Widgets/isavewidget.h
    Widgets/infowindow.h
    Widgets/keyboardlayoutviewer.h
    Widgets/layoutsaver.h
    Widgets/showiconsform.h
    Widgets/extendedwidget.h
    Widgets/singlewidget.h
    Widgets/extendedmainwindow.h
    Widgets/extendeddialog.h
    asyncfuture/asyncfuture.h
    converterfunctions.h
    DigToStrRus.h
    Widgets/dialogwrapper.h
    filedownloader.h
    functions.h
    helperscontainter.h
    mathematics.h
    mylist.hpp
    myvector.hpp
    pdf/PdfExporter.h
    php.h
    programlauncher.h
    setgetMacro.h
    singleton.hpp
    xmlutils.h
    export.h
    eventlistener.h
    objectfactory.h
    iobject.h
    LanguageHelper/languagehelper.h
    ivariant.h
    anymacro.h
    buildversion.h
    simplecrypt.h
    Styles/iconsenum.h
    releaseassert.h
    Perfomance/scopetimer.h
    ExtendApp/extendapp.h
    ExtendApp/singleapplicationprivate.h
    ExtendApp/uilanginfo.h
    ExtendApp/appconfig.h
    signalwaiter.h
    Events/settingchangeevent.h
    project_pch.h
    another.cpp
    Widgets/progressdialog.h
    IGadget/VariantMapHelper.h
    IGadget/igadget.h
    translithelper.h
    cmdargs.h
    ExtendApp/appsettings.h
    MultiPart/multipartparser.h
    MultiPart/multipartfile.h
    Decorator/basedecorator.h
    FileBasedProject/FileBasedProject.h
    FileBasedProject/filebasedprojectp.h
    Widgets/ListWidgets/extlist.h
    Widgets/VariantMapEditor/variantmapeditor.h
    Widgets/VariantMapEditor/priv/variantmapmodel.h
    Widgets/ListWidgets/presetslist.h
    Widgets/Text/complextexteditor.h
    Widgets/Text/complextextdialog.h
    Widgets/Text/priv/complextexteditorp.h
    Widgets/Text/priv/jsonsyntax.h
    Widgets/Text/priv/xmlsyntax.h
    cistring.h
    JsonProtocol/jsonprotocolhelper.h
    JsonProtocol/jsonmessage.h
    Widgets/Actions/statusaction.h
    FunctionWrappper.h
    Widgets/PresetController/priv/presetcontrollerp.h
    Widgets/PresetController/presetcontrollerform.h
    Widgets/SearchLineEdit/searchlineedit.h
    Widgets/Text/priv/isyntax.h
    Widgets/aboutdialog.h
    JsonProtocol/datatransfer.h
    PluginHelper/abstractplugin.h
    PluginHelper/priv/plugindetails.h
    PluginHelper/plugininfoview.h
    PluginHelper/basepluginmanager.h
    PluginHelper/pluginliststate.h
    Styles/stylefilewatcher.h
    Resources/resourceexplorer.ui
    Resources/resourceexplorerdialog.ui
    Widgets/EnumEditor/enumeditorform.ui
    Widgets/FilterWidget/filterwidget.ui
    Widgets/FilterWidget/priv/filterwidgetconfigdialog.ui
    Widgets/SimplePresetCombo/SimplePresetCombo.ui
    Widgets/SimpleTextFilter/SimpleTextFilterDialog.ui
    Widgets/infowindow.ui
    Widgets/makepasswordform.ui
    Widgets/selectlistdialog/selectlistdialog.ui
    Widgets/showiconsform.ui
    Widgets/progressdialog.ui
    Widgets/ListWidgets/extlist.ui
    Widgets/VariantMapEditor/variantmapeditor.ui
    Widgets/ListWidgets/presetslist.ui
    Widgets/Text/complextexteditor.ui
    Widgets/Text/complextextdialog.ui
    Widgets/PresetController/presetcontrollerform.ui
    Widgets/SearchLineEdit/searchlineedit.ui
    Widgets/aboutdialog.ui
    PluginHelper/priv/plugindetails.ui
    PluginHelper/plugininfoview.ui
    Widgets/dialogwrapper.ui
    Widgets/waitdialog.ui
)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    Widgets/SearchForm
    Widgets/PresetController
    Widgets/Text
)

#logger
list(APPEND SOURCES
    Logger/abstractappender.h
    Logger/consoleappender.h
    Logger/fileappender.h
    Logger/logger.h
    Logger/loggermacro.h
    Logger/loggersettings.h
    Logger/loggerhelper.h
    Logger/FileRotation/filerotation.h
    Logger/abstractappender.cpp
    Logger/consoleappender.cpp
    Logger/fileappender.cpp
    Logger/logger.cpp
    Logger/loggersettings.cpp
    Logger/loggerhelper.cpp
    Logger/FileRotation/filerotation.cpp
    Logger/loggertemplate.qrc
)

#serialization
list(APPEND SOURCES
    Serialization/impl/SimpleXmlSerializer.h
    Serialization/impl/binaryserializer.h
    Serialization/impl/jsonserializer.h
    Serialization/impl/simplejsonserializer.h
    Serialization/impl/xmlserializer.h
    Serialization/impl/SimpleXmlSerializer.cpp
    Serialization/impl/binaryserializer.cpp
    Serialization/impl/simplejsonserializer.cpp
    Serialization/impl/xmlserializer.cpp
    Serialization/impl/jsonserializer.cpp
    Serialization/converfuncimpl.h
    Serialization/iconverter.h
    Serialization/iserializebase.h
    Serialization/serializeconfig.h
    Serialization/serializer.h
    Serialization/serializerexception.h
    Serialization/serpropertyinfo.h
    Serialization/converfuncimpl.cpp
    Serialization/iconverter.cpp
    Serialization/serializeconfig.cpp
    Serialization/serializer.cpp
    Serialization/serializerexception.cpp
    Serialization/serpropertyinfo.cpp
)

#ZipManager
list(APPEND SOURCES
    ZipManager/gzipwrapper.h
    ZipManager/zipreader.h
    ZipManager/zipwriter.h
    ZipManager/gzipwrapper.cpp
    ZipManager/qzip.cpp
)

#qtservice

list(APPEND SOURCES
    qtservice/qtservicecontroller.h
    qtservice/qtservicebase.h
    qtservice/qtservicesysprivate.h
    qtservice/qtservicecontrollerhandler.h
    qtservice/handlerthread.h
    qtservice/qtservicebaseprivate.h
    qtservice/qtserviceappeventfilter.h
    qtservice/qtservicecontroller.cpp
    qtservice/qtservicebase.cpp
    qtservice/qtservicesysprivate.cpp
    qtservice/qtservicecontrollerhandler.cpp
    qtservice/handlerthread.cpp
    qtservice/qtservicebaseprivate.cpp
    qtservice/qtserviceappeventfilter.cpp
    qtservice/qtservice.h
    qtservice/qtservice.cpp
)

add_subdirectory(zlib)

if(WIN32)
#    add_subdirectory(qtservice)

    list(APPEND SOURCES
        Win/registry.cpp
        Win/ProcessInfo.cpp
        Win/winapihelper.cpp
        Win/shellhelper.cpp
        Win/serviceinfo.cpp
        Win/servicelist.cpp
        Win/handleptr.cpp
        Win/winapiqt.cpp
        Win/processinfomonitor.cpp
        Win/icmpprovider.cpp
        Win/Autostart/autostartaction.cpp
        Win/Autostart/autostartwrapper.cpp
        Win/bringtofront.cpp
        Win/registry.h
        Win/ProcessInfo.h
        Win/winapihelper.h
        Win/shellhelper.h
        Win/serviceinfo.h
        Win/servicelist.h
        Win/handleptr.h
        Win/winapiqt.h
        Win/processinfomonitor.h
        Win/icmpprovider.h
        Win/Autostart/autostartaction.h
        Win/Autostart/autostartwrapper.h
        Win/bringtofront.h
        Win/processinfomonitor.ui
        Exceptions/StackWalker.cpp
        Exceptions/StackWalker.h
        Exceptions/customstackwalker.cpp
        Exceptions/customstackwalker.h
    )
endif()

if(${PROJECT_NAME}_BUILD_STATIC)
    set(LIB_TYPE STATIC)
else()
    set(LIB_TYPE SHARED)
endif()

add_library(${PROJECT_NAME} ${LIB_TYPE} ${SOURCES})

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    Qt5::Widgets
    Qt5::Xml
    Qt5::Network
    Qt5::PrintSupport
)

target_include_directories(${PROJECT_NAME}
    INTERFACE ${CMAKE_BINARY_DIR}/include/${PROJECT_NAME}
)

target_link_libraries(${PROJECT_NAME} PRIVATE zlib)

if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        User32 Advapi32 Shlwapi ws2_32 iphlpapi Shell32 Psapi)
endif()

target_precompile_headers(${PROJECT_NAME} PRIVATE project_pch.h)
target_compile_definitions(${PROJECT_NAME} PRIVATE "HELPERLIBRARY;UNICODE;_UNICODE;_CRT_SECURE_NO_WARNINGS")

if(NOT ${PROJECT_NAME}_BUILD_STATIC)
    install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ".")
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC "${PROJECT_NAME}_BUILD_STATIC")
endif()

moveHeaders()
deployTr()
aviaNames()
makeAI()




