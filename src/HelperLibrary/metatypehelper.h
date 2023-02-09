#ifndef METATYPEHELPER_H
#define METATYPEHELPER_H

#include "export.h"

class HELPERLIBRARY_EXPORT MetaTypeHelper
{
public:
    template<class Type>
    static void registerArrayType()
    {
        registerArrayType(qMetaTypeId<Type>(), qMetaTypeId<Type::value_type>());
    }

    template<class Type>
    static void registerMapType()
    {
        registerMapType(qMetaTypeId<Type>(), qMetaTypeId<Type::key_type>(), qMetaTypeId<Type::mapped_type>());
    }

    static void registerArrayType(int _containerType, int _itemType);
    static int getArrayElementType(int _containerType);
    static bool isRegisteredArrayType(int _containerType);

    static void registerMapType(int _contanerType, int _keyType, int _valueType);
    static int getMapKeyType(int _containerType);
    static int getMapElementType(int _containerType);
    static bool isRegesteredMapType(int _containerType);
};

#endif // METATYPEHELPER_H
