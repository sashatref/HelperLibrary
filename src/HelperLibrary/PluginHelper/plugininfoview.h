#pragma once

#include <QDialog>

#include "../export.h"
#include "pluginliststate.h"

namespace Ui {
class PluginInfoView;
}

namespace HelperLibraryNS
{

class AbstractPlugin;

/*!
 * \brief The PluginInfoView class
 * виджет для отображения списка плагинов
 * Отображает такие данные как: названия плагина, унивкальное имя плагина, версия, включе/загружен
 * дает возможность редактирония настроек плагина
 */

class HELPERLIBRARY_EXPORT PluginInfoView : public QDialog
{
    Q_OBJECT
public:
    explicit PluginInfoView(QWidget *parent = 0);
    ~PluginInfoView();

    /*!
     * \brief setPluginList устанавливает список плагинов, которые будут отображены в дереве
     * \param _pluginList
     */
    void setPluginList(const QVector<AbstractPlugin *> &_pluginList);

    PluginEnableMap getEnableMap() const;

protected:
    void closeEvent(QCloseEvent *e) override;

signals:
    void showSettingsForPlugin(AbstractPlugin *_plugin);


    /*!
     * \brief onClose вызывает перед закрытием окна.
     */
    void onClose();

public slots:
    void on_closeButton_clicked();
    void on_detailsButton_clicked();
    void treeViewItemChanged();

private:
    Ui::PluginInfoView *ui;
    QVector<AbstractPlugin*> m_pluginList;
};

}
