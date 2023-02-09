#pragma once

#include <QDialog>
#include "../export.h"

namespace Ui {
class AboutDialog;
}

namespace HelperLibraryNS
{

class HELPERLIBRARY_EXPORT AboutDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AboutDialog(QWidget *parent = nullptr);
    ~AboutDialog();

    void setInfo(const QString &_appName, const QString &_appVer, const QString &_buildTime);

    void setAppName(const QString &_name);
    void setAppVer(const QString &_ver);
    void setAppBuildTime(const QString &_buildTime);

private:
    Ui::AboutDialog *ui;
};

}
