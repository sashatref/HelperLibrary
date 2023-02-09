#pragma once

#ifdef _DEBUG
    #ifdef USE_VLD
        #include <vld.h>
    #endif
#endif

#include <QAction>
#include <QObject>
#include <QMenu>
#include <QCoreApplication>
#include <QDebug>
#include <QProcess>
#include <QDate>
#include <QListWidget>
#include <QKeyEvent>
#include <QMetaMethod>
#include <QTimer>
#include <QMessageBox>
#include <QInputDialog>
#include <QDirIterator>
#include <QFileDialog>
#include <QCheckBox>
#include <QToolButton>
#include <QDomDocument>
#include <QDomElement>
#include <QLoggingCategory>
#include <QSettings>
#include <QJsonDocument>
#include <QClipboard>
#include <QToolTip>


#ifdef Q_OS_WIN
    #define PSAPI_VERSION 1

    #include <Windows.h>
    #include <tlhelp32.h>
    #include <Psapi.h>
    #include <iphlpapi.h>
#endif

QString getAppPath();
QString makePathAbsolute(const QString &_path);

Q_DECLARE_LOGGING_CATEGORY(helperCat)
Q_DECLARE_LOGGING_CATEGORY(extendApp)
Q_DECLARE_LOGGING_CATEGORY(loggerCat)
