#pragma once

namespace TestUtils
{
    template<class Type>
    ::testing::AssertionResult compareArr(const QList<Type>& a1,  const QList<Type> &a2)
    {
        if(a1.size() != a2.size())
        {
            return ::testing::AssertionFailure() << "Array size not equals. Array1 size: "
                << a1.size() << " | Array2 size:" << a2.size();
        }

        for(int i = 0 ; i < a1.size(); i++)
        {
            if(a1.at(i) == a2.at(i))
            {
                // continue
            } else
            {
                QString info1 = JsonUtils::toString(a1.at(i));
                QString info2 = JsonUtils::toString(a2.at(i));

                return ::testing::AssertionFailure() << "Elements not eq at index [" << i << "] |\n"
                    << "El1: " << qUtf8Printable(info1)
                    << " |\n\nEl2: " << qUtf8Printable(info2);
            }
        }

        return ::testing::AssertionSuccess();
    }

    template<class Type>
    ::testing::AssertionResult serialization()
    {
        Type v = Randomizer::createRand<Type>();
        QString data = JsonUtils::toString(v);

        Type newValue;
        JsonUtils::fromString(data, newValue);

        if(v != newValue)
        {
            return ::testing::AssertionFailure() << "Data not eq. Json | " << qUtf8Printable(data);
        }

//        qDebug() << qUtf8Printable(data);

        return ::testing::AssertionSuccess();
    }
}

