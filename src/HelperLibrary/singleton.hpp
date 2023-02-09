#pragma once

template <class T>
class Singleton
{
public:
    static T* instance()
    {
        return &ins();
    }

    static T &ins()
    {
        static T instanse;
        m_pInstance = &instanse;
        return instanse;
    }

protected:
    Singleton();
    ~Singleton();
private:
    Singleton(Singleton const&);
    Singleton& operator=(Singleton const&);
    static T* m_pInstance;
};

template <class T> T* Singleton<T>::m_pInstance = nullptr;

