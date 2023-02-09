#include "DomElementWrapper.h"

DomElementWrapper::DomElementWrapper(const QDomElement &el):
    m_el(el)
{

}

DomElementWrapper &DomElementWrapper::read(QString &_v, const QString &_attr, const QString &_default)
{
    _v = m_el.attribute(_attr, _default);
    return *this;
}

DomElementWrapper &DomElementWrapper::read(int &_v, const QString &_attr, const int &_default)
{
    _v = m_el.attribute(_attr, QString::number(_default)).toInt();
    return *this;
}

DomElementWrapper &DomElementWrapper::read(double &_v, const QString &_attr, const double &_default)
{
    _v = m_el.attribute(_attr, QString::number(_default)).toDouble();
    return *this;
}

DomElementWrapper &DomElementWrapper::read(bool &_v, const QString &_attr, const bool &_default)
{
    _v = m_el.attribute(_attr, QString::number(_default)).toInt();
    return *this;
}
