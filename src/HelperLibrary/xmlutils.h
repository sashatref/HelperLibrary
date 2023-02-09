#pragma once

#include <QDomDocument>
#include <QDomElement>
#include <QMap>

#include "export.h"

#include "DomElementWrapper.h"

namespace XmlUtils
{
    void HELPERLIBRARY_EXPORT setDocContent(QDomDocument &_doc, const QString &_text);

    void HELPERLIBRARY_EXPORT iterateChildren(const QDomElement &el, std::function<void(const QDomElement &el)> _functor);
    void HELPERLIBRARY_EXPORT iterateChildren(const QDomElement &el, const QString &_tagName, std::function<void(const QDomElement &el)> _functor);

    void HELPERLIBRARY_EXPORT iterateChildren(const QString &_xml, std::function<void(const QDomElement &el)> _functor);
    void HELPERLIBRARY_EXPORT iterateChildren(const QString &_xml, const QString &_tagName, std::function<void(const QDomElement &el)> _functor);


    void HELPERLIBRARY_EXPORT loadText(const QString &_xml, std::function<void(const QDomElement &)> _func);
    void HELPERLIBRARY_EXPORT loadText(const QString &_xml, std::function<void(DomElementWrapper &)> _func);
    void HELPERLIBRARY_EXPORT loadFile(const QString &_filePath, std::function<void(const QDomElement &)> _func);

    QDomDocument HELPERLIBRARY_EXPORT loadFromFile(const QString &_filePath);

    using AttributeMap = QMap<QString, QString>;
    using ReplaceMap = QMap<QString, QString>;

    AttributeMap HELPERLIBRARY_EXPORT extractAttributes(const QDomElement &_el, const ReplaceMap &_replaceAttr /*= ReplaceMap()*/);
}
