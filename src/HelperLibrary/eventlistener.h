#pragma once

#include <QObject>
#include <QEvent>
#include <functional>

#include "export.h"

/*!
 * \brief The EventListener class
 * Класс для выполнения _callback-функции при нажатие любой клавиши из _keyList
 * так же срабатывает событие onKeyPressed, в котором указывается код нажатой клавиши.
 *
 * Класс создан для того чтоб не городить installEventFilter, eventFilter на каждую мелкую операцию
 *
 * _callback и onKeyPressed - по сути одно и тоже, просто чтоб программист выбрал как
 * ему удобней подписываться на события
 *
 * @param[in] _keyList  Список кодов кнопок, на которые должны срабатывать
 * события _callback и onKeyPressed
 * @param[in] _object   объект для которого ловить эти события
 * @param[in] _callback функция, которая срабатывает по нажатию одной из кнопок, можно оставить 0
 * @param[in] _parent   родитель, чтоб при удаление родителя удалился и EventListener
 */

class HELPERLIBRARY_EXPORT EventListener : public QObject
{
    Q_OBJECT
public:
    EventListener(QList<int> _keyList,
                  QObject* _object,
                  std::function<void(int _key)> _callback = 0,
                  QObject *_parent = 0,
                  QEvent::Type _type = QEvent::KeyPress);

    virtual bool eventFilter(QObject *watched, QEvent *event) override;
signals:
    void onKeyPressed(int _key);

private:
    std::function<void(int _key)> m_callback;
    QList<int> m_keyList;
    QObject *m_object;

    int m_eventType;
};

