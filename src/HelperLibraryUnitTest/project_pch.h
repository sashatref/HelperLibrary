#pragma once

#include <gtest/gtest.h>

#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QProcess>
#include <QDebug>
#include <QThread>
#include <QCommandLineParser>
#include <QCommandLineOption>
#include <QSqlQuery>
#include <QSqlError>
#include <QStringList>
#include <QJsonDocument>

#include <HelperLibrary/ZipManager/zipreader.h>
#include <HelperLibrary/Exceptions/userexception.h>
#include <HelperLibrary/signalwaiter.h>
#include <HelperLibrary/Randomizer.h>
#include <HelperLibrary/ExtendApp/extendapp.h>
#include <HelperLibrary/setgetMacro.h>
#include <HelperLibrary/igadget.h>
#include <HelperLibrary/anymacro.h>
#include <HelperLibrary/Randomizer.h>
#include <HelperLibrary/converterfunctions.h>
#include <HelperLibrary/SimpleTextFilter.h>

#include <HelperLibrary/Json/JsonUtils.h>
#include <HelperLibrary/Json/JsonStreamParser.h>

using HelperLibrary::UserExceptions::BaseException;
