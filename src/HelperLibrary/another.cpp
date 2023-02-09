#include "project_pch.h"

Q_LOGGING_CATEGORY(helperCat, "avia.HL")
Q_LOGGING_CATEGORY(extendApp, "avia.HL.ExtendApp")
Q_LOGGING_CATEGORY(loggerCat, "avia.HL.Logger")

QString getAppPath()
{
    QString path;

#ifdef Q_OS_WIN
    TCHAR szFileName[MAX_PATH + 1] = {};
    GetModuleFileName(NULL, szFileName, MAX_PATH + 1);
    path = QString::fromWCharArray(szFileName, MAX_PATH);
#endif

    QStringList tokens = path.split("\\");
    path = tokens.mid(0, tokens.size() - 1)
            .join("/" );

    return path;
}

QString makePathAbsolute(const QString &_path)
{
    QString outPath = _path;
    QFileInfo sFi(_path);
    if(!sFi.isAbsolute())
    {
        const QString appPath = getAppPath();

        if(appPath.isEmpty())
        {
            outPath = _path;
        } else
        {
            outPath = getAppPath() + "/" + _path;
        }
    }

    return QDir::toNativeSeparators(outPath);
}
