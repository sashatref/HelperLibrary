#pragma once

#include "export.h"

struct HELPERLIBRARY_EXPORT DomElementWrapper
{
    DomElementWrapper(const QDomElement &el);

    DomElementWrapper &read(QString &_v, const QString &_attr, const QString &_default);
    DomElementWrapper &read(int &_v, const QString &_attr, const int &_default = 0);
    DomElementWrapper &read(double &_v, const QString &_attr, const double &_default = 0);
    DomElementWrapper &read(bool &_v, const QString &_attr, const bool &_default = false);

private:
    const QDomElement &m_el;
};

