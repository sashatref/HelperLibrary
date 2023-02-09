#include "widgethelper.h"

#include <QStyleFactory>
#include <QDesktopWidget>
#include <QApplication>
#include <QTreeWidgetItem>
#include <QBuffer>

void WidgetHelper::setWidgetOnScreenCenter(QWidget *_widgetToSet, const QWidget *_parentWidget, int _width, int _height)
{
    QDesktopWidget dWidget;
    int screenNum = dWidget.screenNumber(_parentWidget);
    if(_width != -1 && _height != -1)
    {
        _widgetToSet->setGeometry(0,0,_width, _height);
    }
    _widgetToSet->move(dWidget.availableGeometry(screenNum).center() - _widgetToSet->rect().center());
}

bool WidgetHelper::saveGeometry(const QString &_path, QWidget *_widget)
{
    QString mypath = _path;

    mypath.replace("\\", "/");
    if(mypath.contains("/"))
    {
        QString dir = mypath.left(mypath.lastIndexOf("/"));
        QDir().mkpath(dir);
    }

    QFile file(_path);
    if (!file.open(QFile::WriteOnly))
    {
        return false;
    }

    QByteArray geo_data = _widget->saveGeometry();

    bool ok = file.putChar((uchar)geo_data.size());
    if (ok)
        ok = file.write(geo_data) == geo_data.size();

    if (!ok) {
        return false;
    }
    return true;
}

bool WidgetHelper::loadGeometry(const QString &_path, QWidget *_widget)
{
    QFile file(_path);
    if (!file.open(QFile::ReadOnly))
    {
        return false;
    }

    uchar geo_size;
    QByteArray geo_data;
    QByteArray layout_data;

    bool ok = file.getChar((char*)&geo_size);
    if (ok) {
        geo_data = file.read(geo_size);
        ok = geo_data.size() == geo_size;
    }
    if (ok) {
        layout_data = file.readAll();
        ok = layout_data.size() > 0;
    }

    if (ok)
        ok = _widget->restoreGeometry(geo_data);

    if (!ok) {
        return false;
    }
    return true;
}

QTreeWidgetItem *TreeWidgetUtils::nextItem(QTreeWidgetItem *_item)
{
    QTreeWidget *view = _item->treeWidget();
    if(!view) return 0;

    QTreeWidgetItem *parentNode = _item->parent();
    if(!parentNode) return 0;

    int index = parentNode->indexOfChild(_item);
    return parentNode->child(index + 1);
}

QTreeWidgetItem *TreeWidgetUtils::prevItem(QTreeWidgetItem *_item)
{
    QTreeWidget *view = _item->treeWidget();
    if(!view) return 0;

    QTreeWidgetItem *parentNode = _item->parent();
    if(!parentNode) return 0;

    int index = parentNode->indexOfChild(_item);
    return parentNode->child(index - 1);
}

QTreeWidgetItem *TreeWidgetUtils::findByName(QTreeWidgetItem *_parent, const QString &_text, int _column)
{
    if(_parent == 0) return 0;

    for(int i = 0 ; i < _parent->childCount(); i++)
    {
        if(_parent->child(i)->text(_column) == _text)
        {
            return _parent->child(i);
        }
    }

    return 0;
}



int TreeWidgetUtils::treeItemCount(QTreeWidgetItem *_parentItem)
{
    int result = _parentItem->childCount();
    for(int i = 0 ; i < _parentItem->childCount(); i++)
    {
        result += treeItemCount(_parentItem->child(i));
    }
    return result;
}

QByteArray ImageUtils::imageToByteArray(const QPixmap &_photo, const char *format, int quality)
{
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    _photo.save(&buffer, format, quality);
    return bArray;
}

QByteArray ImageUtils::imageToByteArray(const QImage &_image, const char *format, int quality)
{
    QByteArray bArray;
    QBuffer buffer(&bArray);
    buffer.open(QIODevice::WriteOnly);
    _image.save(&buffer, format, quality);
    return bArray;
}

void WidgetHelper::showWindow(QWidget * const _widget)
{
    if(!_widget) return;

#ifdef _WIN32
    SetForegroundWindow((HWND)_widget->winId());
#endif

    if(_widget->isMinimized())
    {
        _widget->setWindowState(_widget->windowState() & (~Qt::WindowMinimized | Qt::WindowActive));
    }
}

void ListWidgetUtils::setItemsCheckedState(QListWidget *_lw, int _checkedState)
{
    for(int i = 0, count = _lw->count(); i < count; i++)
    {
        _lw->item(i)->setCheckState(static_cast<Qt::CheckState>(_checkedState));
    }
}

void ListWidgetUtils::setItemCheckBoxVisible(QListWidgetItem *_item, bool _isVisible)
{
    _item->setData(Qt::CheckStateRole, _isVisible ? Qt::Checked : Qt::Unchecked);
}

void ListWidgetUtils::setListCheckBoxVisible(QListWidget *_lw, bool _isVisible)
{
    for(int i = 0, count = _lw->count(); i < count; i++)
    {
        setItemCheckBoxVisible(_lw->item(i), _isVisible);
    }
}

QMap<QVariant, int> ListWidgetUtils::saveCheckedState(const QListWidget * const _lw, int _role)
{
    QMap<QVariant, int> result;

    for(int i = 0, count = _lw->count(); i < count; i++)
    {
        QListWidgetItem *item = _lw->item(i);
        QVariant propName = item->data(_role);
        result[propName] = item->checkState();
    }

    return result;
}

void ListWidgetUtils::restoreCheckedState(QListWidget * const _lw,
                                          const QMap<QVariant, int> &_state,
                                          int _role)
{
    for(int i = 0, count = _lw->count(); i < count; i++)
    {
        QListWidgetItem *item = _lw->item(i);
        QVariant propName = item->data(_role);

        if(_state.contains(propName))
        {
            item->setCheckState(static_cast<Qt::CheckState>(_state[propName]));
        }
    }
}


static void getAllItemsRec(QTreeWidgetItem *_item, QList<QTreeWidgetItem *> &_arr)
{
    if(_item)
    {
        _arr.append(_item);

        for(int i = 0 ; i < _item->childCount(); i++)
        {
            getAllItemsRec(_item->child(i), _arr);
        }
    }
}

QList<QTreeWidgetItem *> TreeWidgetUtils::getAllSubItems(QTreeWidgetItem *_topLevelItem)
{
    QList<QTreeWidgetItem *> itemList;
    if(_topLevelItem)
    {
        getAllItemsRec(_topLevelItem, itemList);
    }

    return itemList;
}

QTreeWidgetItem *TreeWidgetUtils::getTopLevelItem(QTreeWidgetItem *_item)
{
    QTreeWidgetItem *topLevelItem = _item;

    while(topLevelItem->parent())
    {
        topLevelItem = topLevelItem->parent();
    }

    return topLevelItem;
}

void WidgetHelper::createStyleActions(QMenu *_menu, QString *_current)
{
    QStringList styles = QStyleFactory::keys();
    for(int i = 0 ; i < styles.size(); i++)
    {
        const QString styleName = styles.at(i);

        QAction *act = new QAction(styleName, _menu);
        _menu->addAction(act);
        act->setObjectName("styleAction_" + QString::number(i));
        act->setData(styleName);
        act->setCheckable(true);

        auto func = [_menu, act, _current]()
        {
//            for(int j = 0 ; j < _menu->actions().size(); j++)
//            {
//                _menu->actions().at(j)->setChecked(act == _menu->actions().at(j) ? true : false);
//            }

            for(auto it : _menu->actions())
            {
                it->setChecked(act == it ? true : false);
            }

            const QString styleName = act->data().toString();
            QApplication::setStyle(QStyleFactory::create(styleName));
            *_current = styleName;
        };

        QObject::connect(act, &QAction::triggered, func);

        if(styleName == *_current)
        {
            func();
            act->setChecked(true);
        }
    }
}

bool WidgetHelper::getBoolValue(const QString &_title,
                                const QString &_label,
                                bool _default,
                                bool *_ok)
{
    return QVariant(QInputDialog::getItem(0,
                                          _title,
                                          _label,
                                          QStringList() << "true" << "false",
                                          _default ? 0 : 1,
                                          false,
                                          _ok)).toBool();
}

void WidgetHelper::hideMenuIsEmpty(QMenu *_menu)
{
    if(_menu->actions().size() == 0)
    {
        _menu->menuAction()->setVisible(false);
    }
}

void WidgetHelper::setWidgetFontPx(QWidget *_w, int _px)
{
    QFont f = _w->font();
    f.setPixelSize(_px);
    _w->setFont(f);
}

void WidgetHelper::setEnabledState(bool _enabled, const QList<QWidget *> &_widgets)
{
    for(auto *w : _widgets)
    {
        w->setEnabled(_enabled);
    }
}

void WidgetHelper::setVisibility(bool _visible, const QList<QWidget *> &_widgets)
{
    for(auto *w : _widgets)
    {
        w->setVisible(_visible);
    }
}

void WidgetHelper::switchEnabledState(const QList<QWidget *> &_widgets)
{
    for(auto *w : _widgets)
    {
        w->setEnabled(!w->isEnabled());
    }
}

void TreeWidgetUtils::foreachWithChildren(QTreeWidgetItem *_item, std::function<void (QTreeWidgetItem *)> _func)
{
    if(_item == nullptr)
    {
        return;
    }

    auto items = getAllSubItems(_item);

    for(auto &it : items)
    {
        _func(it);
    }
}
