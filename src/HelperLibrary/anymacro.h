#pragma once


#define TO_VARIANT_CONVERTER(className)     \
    inline className(const QVariant &_val)  \
    {                                       \
        *this = _val.value<className>();    \
    }                                       \
                                            \
    inline operator QVariant() const        \
    {                                       \
        return QVariant::fromValue(*this);  \
    }


#ifdef PERFORMANCE_CHECK
    #define PERFORMANCE(expression) expression
#else
    #define PERFORMANCE(expression)
#endif


namespace FuncInvokers
{
    struct InvokeAsConstructor
    {
        InvokeAsConstructor(void func())
        {
            func();
        }
    };

    struct InvokeAsDestructor
    {
        typedef void(*Func)();

        InvokeAsDestructor(Func _func):
            m_func(_func)
        {}

        ~InvokeAsDestructor()
        {
            m_func();
        }

        Func m_func;
    };
}


#ifndef PS_CONCAT_
    #define PS_CONCAT_(x,y) x##y
#endif

#ifndef PS_CONCAT
    #define PS_CONCAT(x,y) PS_CONCAT_(x,y)
#endif

#ifndef PS_STRINGIZE
    #define PS_STRINGIZE(x) PS_STRINGIZE2(x)
#endif

#ifndef PS_STRINGIZE2
    #define PS_STRINGIZE2(x) #x
#endif


#ifndef PS_UNIQUE_NAME2
    #define PS_UNIQUE_NAME2(base) PS_CONCAT(base, __COUNTER__)
#endif


#ifndef PS_REGISTER_CONSTRUCTOR_FUNC
    #define PS_REGISTER_CONSTRUCTOR_FUNC(_func)                             \
    namespace                                                               \
    {                                                                       \
        static const FuncInvokers::InvokeAsConstructor                      \
            PS_UNIQUE_NAME2(InvokeAsConstructorClassInstance_)(_func);      \
    }
#endif

#ifndef PS_REGISTER_DESTRUCTOR_FUNC
    #define PS_REGISTER_DESTRUCTOR_FUNC(_func)                              \
    namespace                                                               \
    {                                                                       \
        static const FuncInvokers::InvokeAsDestructor                      \
            PS_UNIQUE_NAME2(InvokeAsDestructorClassInstance_)(_func);      \
    }
#endif


#ifndef PS_DECLARE_METATYPE
    #define PS_DECLARE_METATYPE(ClassName)                                  \
    namespace                                                               \
    {                                                                       \
        static const PropertySystemNS::MetaTypeRegistrator<ClassName>       \
            PS_UNIQUE_NAME2(MetaTypeRegistratorClassInstance_)(#ClassName); \
    }
#endif


