#pragma once

#include <QVariant>
#include <functional>

#include "../export.h"
#include "layoutsaver.h"

/*!
 * \brief The ISaveWidget class
 * интерфейс для удобного сохранения внутреннего состояния виджета,
 * расположения окон, сплиттеров и пр.
 *
 * После создания виджета, для него выполнить loadWidgetState, куда передать QVariant с настройками
 * Если это диалог, то после exec() можно сохранить настройки выполнив saveWidgetState
 * В ином случае нужно передать callback - функцию в setOnSaveCallback
 *
 * В самом виджете реализовать виртуальные методы loadWidgetState, saveWidgetState, getWidgetUniqueName
 * В методе closeEvent - выполнить функцию emitSaveFunc
 *
 * @example
 *  QVariant saveWidgetState() const
    {
        QVariantMap m;
        m["geometry"] = this->geometry();
        m["propertyTable"] = ui->propertyTable->saveWidgetState();
        return m;
    }

    void loadWidgetState(const QVariant &_state)
    {
        QVariantMap m = _state.toMap();

        if(m.contains("geometry"))
        {
            QRect geometry = m["geometry"].toRect();
            this->resize(geometry.width(), geometry.height());
            this->move(geometry.x() - 8, geometry.y() - 30);
        }

        ui->propertyTable->loadWidgetState(m["propertyTable"]);
    }

    QString editTableForm::getWidgetUniqueName() const
    {
        return QString("EditTableForm_%1").arg(m_formType);
    }

    void closeEvent(QCloseEvent *event)
    {
        emitSaveFunc();
    }
 */


class HELPERLIBRARY_EXPORT ISaveWidget
{
public:
    ISaveWidget() {}
    virtual ~ISaveWidget() {}
    virtual QVariant saveWidgetState() const;
    virtual void loadWidgetState(const QVariant &_state);
    virtual QString getWidgetUniqueName() const = 0;

    virtual void loadState(const LayoutSaver &_saver);
    virtual void saveState(LayoutSaver &_saver) const;

    void setOnSaveCallback(const std::function<void(const QVariant&)> &_saveStateFunc);

protected:
    void emitSaveFunc();

    std::function<void(const QVariant &_state)> m_saveStateFunc;
};

QVariant HELPERLIBRARY_EXPORT saveWidgetState(const ISaveWidget *_sw);
void HELPERLIBRARY_EXPORT loadWidgetState(ISaveWidget *_sw, const QVariant &_val);

