#pragma once

#include <QDialog>

#include "../../export.h"

namespace Ui {
class PluginDetails;
}


namespace HelperLibraryNS
{

/*!
 * \brief The PluginDetails class
 * виджет для отображения некоторой информации о плагине:
 * название, версия, уникальное название, включен, загружен, описание
 */

class PluginDetails : public QDialog
{
    Q_OBJECT

public:
    explicit PluginDetails(QWidget *parent = 0);

    /*!
     * \brief initValues устанавливает значения  всоответствующие поля
     * \param _name
     * \param _isEnable
     * \param _isLoaded
     * \param _version
     * \param _uniqueName
     * \param _description
     */
    void initValues(const QString &_name,
                    bool _isEnable,
                    bool _isLoaded,
                    const QString &_version,
                    const QString &_uniqueName,
                    const QString &_description);
    ~PluginDetails();

private slots:
    void on_closeButton_clicked();

private:
    Ui::PluginDetails *ui;
};

}

