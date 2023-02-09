#include "metatypehelper.h"



static class MetaTypeHelperP
{
public:
    struct MapHolder
    {
        MapHolder(int _key = -1, int _value = -1):
            key(_key), value(_value)
        {

        }

        int key;
        int value;
    };

    MetaTypeHelperP()
    {
        MetaTypeHelper::registerArrayType<QStringList>();
        MetaTypeHelper::registerArrayType<QList<int>>();
        MetaTypeHelper::registerMapType<QMap<QString, QString>>();
    }

    QMap<int, int> arrayHolder;
    QMap<int, MapHolder> mapHolder;

} metaHelper;

void MetaTypeHelper::registerArrayType(int _containerType, int _itemType)
{
    metaHelper.arrayHolder[_containerType] = _itemType;
}

int MetaTypeHelper::getArrayElementType(int _containerType)
{
    return metaHelper.arrayHolder.value(_containerType, -1);
}

bool MetaTypeHelper::isRegisteredArrayType(int _containerType)
{
    return getArrayElementType(_containerType) != -1;
}

void MetaTypeHelper::registerMapType(int _contanerType, int _keyType, int _valueType)
{
    metaHelper.mapHolder[_contanerType] = MetaTypeHelperP::MapHolder(_keyType, _valueType);
}

int MetaTypeHelper::getMapKeyType(int _containerType)
{
    auto it = metaHelper.mapHolder.find(_containerType);
    if(it == metaHelper.mapHolder.end())
    {
        return -1;
    }

    return it.value().key;
}

int MetaTypeHelper::getMapElementType(int _containerType)
{
    auto it = metaHelper.mapHolder.find(_containerType);
    if(it == metaHelper.mapHolder.end())
    {
        return -1;
    }

    return it.value().value;
}

bool MetaTypeHelper::isRegesteredMapType(int _containerType)
{
    return metaHelper.mapHolder.contains(_containerType);
}
