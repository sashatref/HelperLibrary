#include "xmlutils.h"

#include "releaseassert.h"
#include "Exceptions/userexception.h"


namespace XmlUtils
{

void setDocContent(QDomDocument &_doc, const QString &_text)
{
    using namespace HelperLibrary;

    QString errStr;
    int errLine;
    int errColumn;
    bool result = _doc.setContent(_text, &errStr, &errLine, &errColumn);
    if(!result)
    {
        throw UserExceptions::BaseException(QString("Xml parsing error: %1\nLine: %2 Column: %3")
                                            .arg(errStr)
                                            .arg(errLine)
                                            .arg(errColumn));
    }
}

void iterateChildren(const QDomElement &el, std::function<void (const QDomElement &)> _functor)
{
    for(QDomNode n = el.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        QDomElement t = n.toElement();
        if (!t.isNull())
        {
            _functor(t);
        }
    }
}

QDomDocument loadFromFile(const QString &_filePath)
{
    QDomDocument doc;

    QFile f(_filePath);
    if(f.open(QIODevice::ReadOnly))
    {
        doc.setContent(&f);
    }

    return doc;
}

void iterateChildren(const QDomElement &el, const QString &_tagName, std::function<void (const QDomElement &)> _functor)
{
    for(QDomNode n = el.firstChild(); !n.isNull(); n = n.nextSibling())
    {
        QDomElement t = n.toElement();
        if (!t.isNull() && t.tagName() == _tagName)
        {
            _functor(t);
        }
    }
}

void loadText(const QString &_xml, std::function<void (const QDomElement &)> _func)
{
    R_ASSERT(_func);
    QDomDocument doc;
    doc.setContent(_xml);
    QDomElement root = doc.documentElement();
    if(!root.isNull())
    {
        _func(root);
    }
}

void loadFile(const QString &_filePath, std::function<void (const QDomElement &)> _func)
{
    R_ASSERT(_func);
    QDomDocument doc = loadFromFile(_filePath);
    QDomElement root = doc.documentElement();
    if(!root.isNull())
    {
        _func(root);
    }
}

void loadText(const QString &_xml, std::function<void (DomElementWrapper &)> _func)
{
    R_ASSERT(_func);
    loadText(_xml, [&](const QDomElement &el)
    {
        DomElementWrapper wr(el);
        _func(wr);
    });
}

void iterateChildren(const QString &_xml, std::function<void (const QDomElement &)> _functor)
{
    QDomDocument doc;
    doc.setContent(_xml);
    if(!doc.isNull())
    {
        iterateChildren(doc.documentElement(), _functor);
    }
}

void iterateChildren(const QString &_xml, const QString &_tagName, std::function<void (const QDomElement &)> _functor)
{
    QDomDocument doc;
    doc.setContent(_xml);
    if(!doc.isNull())
    {
        iterateChildren(doc.documentElement(), _tagName, _functor);
    }
}

AttributeMap extractAttributes(const QDomElement &_el, const ReplaceMap &_replaceAttr)
{
    AttributeMap out;

    QDomNamedNodeMap attrMap = _el.attributes();

    for(int i = 0 ; i < attrMap.count(); i++)
    {
        QDomAttr attr = attrMap.item(i).toAttr();
        QString key = attr.name();
        const QString value = attr.value();

        auto it = _replaceAttr.find(key);
        if (it != _replaceAttr.end())
        {
            key = it.value();
        }

        out[key] = value;
    }

    return out;
}

}
