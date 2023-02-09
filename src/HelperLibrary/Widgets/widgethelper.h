#pragma once

class QWidget;
class QDockWidget;
class QAction;
class QToolBar;
class QMenu;
class QString;
class QTreeWidgetItem;
class QTreeWidget;
class QByteArray;
class QPixmap;
class QListWidget;
class QListWidgetItem;
class QImage;

#include <QMap>
#include <QVariant>

#include "../export.h"

namespace WidgetHelper
{

    bool HELPERLIBRARY_EXPORT getBoolValue(const QString &_title,
                                           const QString &_label,
                                           bool _default = true,
                                           bool *_ok = 0);

    /*!
     * \brief createStyleActions к указанному _menu добавляет список из всех доступных стилей,
     * при выборе стиля всем виджетам будет отправло событие QEvent::StyleChanged
     * \param _menu меню к которому нужно добавить элементы
     * \param _current текущий стиль, будет в списке отмечен выбранным,
     * в данную переменню будет записано имя нового стиля, при выборе элемента меню, так что
     * переменная должна существовать все время работы gui части программы
     */
    void HELPERLIBRARY_EXPORT createStyleActions(QMenu *_menu, QString *_current);

    //разворачивает окно и переводит его на передний план
    void HELPERLIBRARY_EXPORT showWindow(QWidget * const _widget);


    /*!
     * \brief setWidgetOnScreenCenter устанавливает виджет по центру экрана, где находится _parentWidget
     * \param _widgetToSet виджет, который нужно разместить
     * \param _parentWidget виджет по которому определяется экран для размещения
     */
    void HELPERLIBRARY_EXPORT setWidgetOnScreenCenter(QWidget *_widgetToSet, const QWidget *_parentWidget, int _width = -1, int _height = -1);

    bool HELPERLIBRARY_EXPORT saveGeometry(const QString &_path, QWidget *_widget);
    bool HELPERLIBRARY_EXPORT loadGeometry(const QString &_path, QWidget *_widget);

    void HELPERLIBRARY_EXPORT hideMenuIsEmpty(QMenu *_menu);

    void setWidgetFontPx(QWidget *_w, int _px);

    void HELPERLIBRARY_EXPORT switchEnabledState(const QList<QWidget*> &_widgets);
    void HELPERLIBRARY_EXPORT setEnabledState(bool _enabled, const QList<QWidget*> &_widgets);
    void HELPERLIBRARY_EXPORT setVisibility(bool _visible, const QList<QWidget *> &_widgets);
}

namespace TreeWidgetUtils
{
    QTreeWidgetItem HELPERLIBRARY_EXPORT *nextItem(QTreeWidgetItem *_item);
    QTreeWidgetItem HELPERLIBRARY_EXPORT *prevItem(QTreeWidgetItem *_item);

    QTreeWidgetItem HELPERLIBRARY_EXPORT *findByName(QTreeWidgetItem *_parent, const QString &_text, int _column);
    int HELPERLIBRARY_EXPORT treeItemCount(QTreeWidgetItem *_parentItem);

    void HELPERLIBRARY_EXPORT foreachWithChildren(QTreeWidgetItem *_item,
                                                  std::function<void(QTreeWidgetItem*)> _func);

    QList<QTreeWidgetItem*> HELPERLIBRARY_EXPORT getAllSubItems(QTreeWidgetItem *_topLevelItem);
    QTreeWidgetItem HELPERLIBRARY_EXPORT *getTopLevelItem(QTreeWidgetItem *_item);
}

namespace ListWidgetUtils
{

    /*!
     * \brief setItemsCheckedState устанавливает Qt::CheckStateRole для всех элементов списка
     * \param _lw
     * \param _checkedState
     */
    void HELPERLIBRARY_EXPORT setItemsCheckedState(QListWidget *_lw, int _checkedState);

    /*!
     * \brief setItemCheckBoxVisible прячет или показывает чекбоксы рядом с элементом списка
     * \param _item
     * \param _isVisible
     */
    void HELPERLIBRARY_EXPORT setItemCheckBoxVisible(QListWidgetItem *_item, bool _isVisible);

    /*!
     * \brief setListCheckBoxVisible прячет или показывает чекбоксы рядом со всеми элементами списка
     * \param _lw
     * \param _isVisible
     */
    void HELPERLIBRARY_EXPORT setListCheckBoxVisible(QListWidget *_lw, bool _isVisible);

    /*!
    * \brief saveCheckedState сохраняет состояние отмеченных элементов списка
    * \param _lw - QListWidget для сохранения
    * \param _role - откуда брать уникальные названия строк
    * \return
    */
    QMap<QVariant, int> HELPERLIBRARY_EXPORT saveCheckedState(const QListWidget *const _lw,
                                                             int _role);

    /*!
     * \brief restoreCheckedState загружает состояние отмеченных элементов списка
     * \param _lw - QListWidget для загрузки
     * \param _state - карта отмеченных значений
     * \param _role - откуда брать уникальные названия строк
     */
    void HELPERLIBRARY_EXPORT restoreCheckedState(QListWidget *const _lw,
                                                  const QMap<QVariant, int> &_state,
                                                  int _role);


}

namespace ImageUtils
{
    QByteArray HELPERLIBRARY_EXPORT imageToByteArray(const QPixmap &_photo, const char *format = "PNG", int quality = -1);
    QByteArray HELPERLIBRARY_EXPORT imageToByteArray(const QImage &_image, const char *format = "PNG", int quality = -1);
}
