#include "../project_pch.h"
#include "plugininfoview.h"
#include "ui_plugininfoview.h"
#include "abstractplugin.h"
#include "priv/plugindetails.h"
#include "../Styles/iconsenum.h"

namespace HelperLibraryNS
{

PluginInfoView::PluginInfoView(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PluginInfoView)
{
    ui->setupUi(this);
    connect(ui->pluginTreeWidget, &QTreeWidget::itemSelectionChanged, this, &PluginInfoView::treeViewItemChanged);
    connect(ui->pluginTreeWidget, &QTreeWidget::itemDoubleClicked, this, &PluginInfoView::on_detailsButton_clicked);
}

void PluginInfoView::setPluginList(const QVector<AbstractPlugin *> &_pluginList)
{
    m_pluginList = _pluginList;

    QTreeWidgetItem *topItem = new QTreeWidgetItem(QStringList() << tr("Плагины"));

    ui->pluginTreeWidget->addTopLevelItem(topItem);

    for(int i = 0 ; i < m_pluginList.size(); i++)
    {
        AbstractPlugin *plugin = m_pluginList.at(i);

        QTreeWidgetItem *item = new QTreeWidgetItem(topItem);

        //для каждого плагина создаем Item, в колонки 0, 3 устанавливает данные - название и версию плагина
        //в 1,2 устанавливает чекбоксы, Включен, Загружен
        //в 4 устанавливаем кнопку для оторажения настроек плагина
        //если плагин не загружен, то делаем кнопку неактивной
        //по нажатию кнопки будет вызван сигнал у слушателя onPluginSettingsEdit(AbstractPlugin *_plugin)
        //c указателем на данный плагин
        //в зависимости от состояния загружен/не загружен, устанавливаем иконку

        item->setText(0, plugin->getName());
        item->setText(3, plugin->getVersion());

        QCheckBox *enableCheckBox = new QCheckBox(this);
        enableCheckBox->setChecked(plugin->m_isEnabled);
        connect(enableCheckBox, &QCheckBox::clicked, this, [plugin](bool isChecked)
        {
            plugin->m_isEnabled = isChecked;
        });

        QCheckBox *loadCheckBox = new QCheckBox(this);
        loadCheckBox->setEnabled(false);
        loadCheckBox->setChecked(plugin->m_isLoaded);

        QToolButton *settingsButton = new QToolButton(this);
        settingsButton->setIcon(IconsEnum::getIcon(IconsEnum::SP_Setting2));
        connect(settingsButton, &QToolButton::clicked, this, [this, plugin]()
        {
            emit showSettingsForPlugin(plugin);
        });

        ui->pluginTreeWidget->setItemWidget(item, 1, enableCheckBox);
        ui->pluginTreeWidget->setItemWidget(item, 2, loadCheckBox);
        ui->pluginTreeWidget->setItemWidget(item, 4, settingsButton);
        item->setData(0, Qt::UserRole, QVariant::fromValue(plugin));

        if(!plugin->m_isLoaded) settingsButton->setEnabled(false);

        QIcon ico = IconsEnum::getIcon(plugin->m_isLoaded ? QStyle::SP_DialogApplyButton : QStyle::SP_DialogCancelButton);
        item->setIcon(0, ico);
    }
    topItem->setExpanded(true);

    for(int i = 0 ; i < 5; i++)
    {
        ui->pluginTreeWidget->resizeColumnToContents(i);
    }
}

PluginEnableMap PluginInfoView::getEnableMap() const
{
    PluginEnableMap out;

    for(auto *item : m_pluginList)
    {
        QString pluginName = item->getUniquePluginName();
        bool isEnable = item->m_isEnabled;
        out[pluginName] = isEnable;
    }

    return out;
}

void PluginInfoView::closeEvent(QCloseEvent *e)
{
    QDialog::closeEvent(e);
    emit onClose();
}

PluginInfoView::~PluginInfoView()
{
    delete ui;
}


void PluginInfoView::on_closeButton_clicked()
{
    close();
}

void PluginInfoView::on_detailsButton_clicked()
{
    //по нажатию на кнопку или по двойному клику по плагину, вызывается окно отображения более подробной
    //информации о данном плагине.
    AbstractPlugin *plugin = ui->pluginTreeWidget->currentItem()->data(0, Qt::UserRole).value<AbstractPlugin*>();
    if(!plugin) return;

    PluginDetails wnd(this);
    wnd.initValues(plugin->getName(),
                   plugin->m_isEnabled,
                   plugin->m_isLoaded,
                   plugin->getVersion(),
                   plugin->getUniquePluginName(),
                   plugin->getDescription());
    wnd.exec();
}

void PluginInfoView::treeViewItemChanged()
{
    //если выбран плагин из списка, то активируем кнопку "Подробнее", иначе деактивируем
    if(ui->pluginTreeWidget->currentItem() && ui->pluginTreeWidget->currentItem() != ui->pluginTreeWidget->topLevelItem(0))
    {
        ui->detailsButton->setEnabled(true);
    } else
    {
        ui->detailsButton->setEnabled(false);
    }
}

}
