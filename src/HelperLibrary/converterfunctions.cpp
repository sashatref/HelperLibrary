#include "converterfunctions.h"

#include <QMutexLocker>

ContainerTypes &ContainerTypes::ins()
{
    static ContainerTypes v;
    return v;
}

void ContainerTypes::registerArray(int _containerType, int _elementType)
{
    QMutexLocker locker(&m_mutex);

    if(!m_arrayTypes.contains(_containerType))
    {
        qCDebug(helperCat) << __FUNCTION__ << QString("%1 => %2")
                    .arg(QMetaType::typeName(_containerType))
                    .arg(QMetaType::typeName(_elementType));

        m_arrayTypes[_containerType] = _elementType;
    }
}

void ContainerTypes::registerMap(int _containerType, int _keyType, int _elementType)
{
    QMutexLocker locker(&m_mutex);

    if(!m_mapTypes.contains(_containerType))
    {
        qCDebug(helperCat) << __FUNCTION__ << QString("%1 => <%2, %3>")
                    .arg(QMetaType::typeName(_containerType))
                    .arg(QMetaType::typeName(_keyType))
                    .arg(QMetaType::typeName(_elementType));

        m_mapTypes[_containerType] = qMakePair(_keyType, _elementType);
    }
}

int ContainerTypes::getElementTypeForContainer(int _containerType) const
{
    QMutexLocker locker(&m_mutex);
    return m_arrayTypes.value(_containerType, 0);
}

QPair<int, int> ContainerTypes::getTypesForMap(int _containerType) const
{
    QMutexLocker locker(&m_mutex);
    return m_mapTypes.value(_containerType, {0,0});
}


namespace Converters
{

void registerVariantMapToQStringBoolMapConverter()
{
    ContainerTypes::ins().registerMap<QMap<QString, bool>, QString, bool>();

    if(!QMetaType::hasRegisteredConverterFunction<QVariantMap, QMap<QString, bool>>())
    {
        QMetaType::registerConverter<QVariantMap, QMap<QString, bool>>(&variantMapToMap<QString, bool>);
    }
}

QStringList convertToStringList(const QList<int> &_list)
{
    QStringList out;
    for(int i = 0 ; i < _list.size(); i++)
    {
        out << QString::number(_list.at(i));
    }
    return out;
}

}

