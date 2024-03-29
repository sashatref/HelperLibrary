set(PROJECT_NAME HelperLibrary)

project(${PROJECT_NAME})

set(SOURCES
    Decorator/basedecorator.cpp
    Decorator/basedecorator.h
    DomElementWrapper.cpp
    DomElementWrapper.h
    Events/settingchangeevent.cpp
    Events/settingchangeevent.h
    Exceptions/userexception.cpp
    Exceptions/userexception.h
    ExtendApp/AppLocker.cpp
    ExtendApp/AppLocker.h
    ExtendApp/appconfig.cpp
    ExtendApp/appconfig.h
    ExtendApp/appsettings.cpp
    ExtendApp/appsettings.h
    ExtendApp/extendapp.cpp
    ExtendApp/extendapp.h
    ExtendApp/singleapplicationprivate.cpp
    ExtendApp/singleapplicationprivate.h
    ExtendApp/uilanginfo.cpp
    ExtendApp/uilanginfo.h
    FileBasedProject/FileBasedProject.cpp
    FileBasedProject/FileBasedProject.h
    FileBasedProject/filebasedprojectp.cpp
    FileBasedProject/filebasedprojectp.h
    IGadget/VariantMapHelper.cpp
    IGadget/VariantMapHelper.h
    IGadget/igadget.cpp
    IGadget/igadget.h
    Json/JsonStreamParser.cpp
    Json/JsonStreamParser.h
    Json/JsonUtils.cpp
    Json/JsonUtils.h
    JsonProtocol/datatransfer.cpp
    JsonProtocol/datatransfer.h
    JsonProtocol/jsonmessage.cpp
    JsonProtocol/jsonmessage.h
    JsonProtocol/jsonprotocolhelper.cpp
    JsonProtocol/jsonprotocolhelper.h
    LanguageHelper/LanguageCombo.cpp
    LanguageHelper/LanguageCombo.h
    LanguageHelper/languagehelper.cpp
    LanguageHelper/languagehelper.h
    MultiPart/multipartfile.cpp
    MultiPart/multipartfile.h
    MultiPart/multipartparser.cpp
    MultiPart/multipartparser.h
    PluginHelper/abstractplugin.h
    PluginHelper/baseplugincreatormanager.cpp
    PluginHelper/baseplugincreatormanager.h
    PluginHelper/basepluginmanager.cpp
    PluginHelper/basepluginmanager.h
    PluginHelper/iplugincreator.cpp
    PluginHelper/iplugincreator.h
    PluginHelper/plugininfoview.cpp
    PluginHelper/plugininfoview.h
    PluginHelper/plugininfoview.ui
    PluginHelper/pluginliststate.cpp
    PluginHelper/pluginliststate.h
    PluginHelper/preloadplugininfo.cpp
    PluginHelper/preloadplugininfo.h
    PluginHelper/priv/plugindetails.cpp
    PluginHelper/priv/plugindetails.h
    PluginHelper/priv/plugindetails.ui
    Randomizer.cpp
    Randomizer.h
    Resources/rcc.cpp
    Resources/rcc.h
    Resources/resourcecompilier.cpp
    Resources/resourcecompilier.h
    Resources/resourceexplorer.cpp
    Resources/resourceexplorer.h
    Resources/resourceexplorer.ui
    Resources/resourceexplorerdialog.cpp
    Resources/resourceexplorerdialog.h
    Resources/resourceexplorerdialog.ui
    Security/ISecurityPlugin.cpp
    Security/ISecurityPlugin.h
    Security/SecurityList.cpp
    Security/SecurityList.h
    Security/SecurityPluginManager.cpp
    Security/SecurityPluginManager.h
    SimpleTextFilter.cpp
    SimpleTextFilter.h
    Styles/iconsenum.cpp
    Styles/iconsenum.h
    Styles/stylefilewatcher.cpp
    Styles/stylefilewatcher.h
    Widgets/Actions/statusaction.cpp
    Widgets/Actions/statusaction.h
    Widgets/EnumEditor/enumeditorform.cpp
    Widgets/EnumEditor/enumeditorform.h
    Widgets/EnumEditor/enumeditorform.ui
    Widgets/FilterWidget/filterwidget.cpp
    Widgets/FilterWidget/filterwidget.h
    Widgets/FilterWidget/filterwidget.ui
    Widgets/FilterWidget/priv/filterwidgetconf.cpp
    Widgets/FilterWidget/priv/filterwidgetconf.h
    Widgets/FilterWidget/priv/filterwidgetconfigdialog.cpp
    Widgets/FilterWidget/priv/filterwidgetconfigdialog.h
    Widgets/FilterWidget/priv/filterwidgetconfigdialog.ui
    Widgets/ListWidgets/extlist.cpp
    Widgets/ListWidgets/extlist.h
    Widgets/ListWidgets/extlist.ui
    Widgets/ListWidgets/presetslist.cpp
    Widgets/ListWidgets/presetslist.h
    Widgets/ListWidgets/presetslist.ui
    Widgets/PresetController/presetcontrollerform.cpp
    Widgets/PresetController/presetcontrollerform.h
    Widgets/PresetController/presetcontrollerform.ui
    Widgets/PresetController/priv/presetcontrollerp.cpp
    Widgets/PresetController/priv/presetcontrollerp.h
    Widgets/SearchForm/isearcher.cpp
    Widgets/SearchForm/isearcher.h
    Widgets/SearchForm/listwidgetsearcher.cpp
    Widgets/SearchForm/listwidgetsearcher.h
    Widgets/SearchForm/priv/searchformp.cpp
    Widgets/SearchForm/priv/searchformp.h
    Widgets/SearchForm/searchform.cpp
    Widgets/SearchForm/searchform.h
    Widgets/SearchForm/searchform.ui
    Widgets/SearchLineEdit/searchlineedit.cpp
    Widgets/SearchLineEdit/searchlineedit.h
    Widgets/SearchLineEdit/searchlineedit.ui
    Widgets/SimplePresetCombo/SimplePresetCombo.cpp
    Widgets/SimplePresetCombo/SimplePresetCombo.h
    Widgets/SimplePresetCombo/SimplePresetCombo.ui
    Widgets/SimpleTextFilter/SimpleTextFilterDialog.cpp
    Widgets/SimpleTextFilter/SimpleTextFilterDialog.h
    Widgets/SimpleTextFilter/SimpleTextFilterDialog.ui
    Widgets/Text/complextextdialog.cpp
    Widgets/Text/complextextdialog.h
    Widgets/Text/complextextdialog.ui
    Widgets/Text/complextexteditor.cpp
    Widgets/Text/complextexteditor.h
    Widgets/Text/complextexteditor.ui
    Widgets/Text/priv/complextexteditorp.cpp
    Widgets/Text/priv/complextexteditorp.h
    Widgets/Text/priv/isyntax.cpp
    Widgets/Text/priv/isyntax.h
    Widgets/Text/priv/jsonsyntax.cpp
    Widgets/Text/priv/jsonsyntax.h
    Widgets/Text/priv/xmlsyntax.cpp
    Widgets/Text/priv/xmlsyntax.h
    Widgets/TrayMenu/traymenu.cpp
    Widgets/TrayMenu/traymenu.h
    Widgets/VariantMapEditor/priv/variantmapmodel.cpp
    Widgets/VariantMapEditor/priv/variantmapmodel.h
    Widgets/VariantMapEditor/variantmapeditor.cpp
    Widgets/VariantMapEditor/VariantMapEditor.h
    Widgets/VariantMapEditor/variantmapeditor.ui
    Widgets/aboutdialog.cpp
    Widgets/aboutdialog.h
    Widgets/aboutdialog.ui
    Widgets/dialogwrapper.cpp
    Widgets/dialogwrapper.h
    Widgets/dialogwrapper.ui
    Widgets/extendeddialog.cpp
    Widgets/extendeddialog.h
    Widgets/extendedmainwindow.cpp
    Widgets/extendedmainwindow.h
    Widgets/extendedwidget.cpp
    Widgets/extendedwidget.h
    Widgets/flowlayout.cpp
    Widgets/flowlayout.h
    Widgets/imagelistwidget.cpp
    Widgets/imagelistwidget.h
    Widgets/imagewidget.cpp
    Widgets/imagewidget.h
    Widgets/independentwidgetholder.cpp
    Widgets/independentwidgetholder.h
    Widgets/infowindow.cpp
    Widgets/infowindow.h
    Widgets/infowindow.ui
    Widgets/isavewidget.cpp
    Widgets/isavewidget.h
    Widgets/keyboardlayoutviewer.cpp
    Widgets/keyboardlayoutviewer.h
    Widgets/layoutsaver.cpp
    Widgets/layoutsaver.h
    Widgets/makepasswordform.cpp
    Widgets/makepasswordform.h
    Widgets/makepasswordform.ui
    Widgets/myprogressdialog.cpp
    Widgets/myprogressdialog.h
    Widgets/progressdialog.cpp
    Widgets/progressdialog.h
    Widgets/progressdialog.ui
    Widgets/selectlistdialog/selectlistdialog.cpp
    Widgets/selectlistdialog/selectlistdialog.h
    Widgets/selectlistdialog/selectlistdialog.ui
    Widgets/showiconsform.cpp
    Widgets/showiconsform.h
    Widgets/showiconsform.ui
    Widgets/singlewidget.cpp
    Widgets/singlewidget.h
    Widgets/waitdialog.cpp
    Widgets/waitdialog.h
    Widgets/waitdialog.ui
    Widgets/whatiisthistoolbutton.cpp
    Widgets/whatiisthistoolbutton.h
    Widgets/widgetanimation.cpp
    Widgets/widgetanimation.h
    Widgets/widgethelper.cpp
    Widgets/widgethelper.h
    another.cpp
    anymacro.h
    buildversion.cpp
    buildversion.h
    cistring.cpp
    cistring.h
    cmdargs.cpp
    cmdargs.h
    converterfunctions.cpp
    converterfunctions.h
    eventlistener.cpp
    eventlistener.h
    export.h
    functions.cpp
    functions.h
    helperscontainter.h
    iobject.cpp
    iobject.h
    ivariant.cpp
    ivariant.h
    objectfactory.cpp
    objectfactory.h
    pdf/PdfExporter.cpp
    pdf/PdfExporter.h
    programlauncher.cpp
    programlauncher.h
    project_pch.h
    releaseassert.h
    setgetMacro.h
    signalwaiter.cpp
    signalwaiter.h
    simplecrypt.cpp
    simplecrypt.h
    singleton.hpp
    xmlutils.cpp
    xmlutils.h
    scopetimer.h
    scopetimer.cpp
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

if(NOT APPLE)
    #ZipManager
    list(APPEND SOURCES
        ZipManager/gzipwrapper.h
        ZipManager/zipreader.h
        ZipManager/zipwriter.h
        ZipManager/gzipwrapper.cpp
        ZipManager/qzip.cpp
    )

    add_subdirectory(zlib)
endif()

if(WIN32)
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

if(NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE zlib)
endif()

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




