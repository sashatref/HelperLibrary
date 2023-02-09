#include "TestQtJson.h"
#include "TestEnv.h"

#include "models/myclass.h"
#include "models/testobject.h"
#include "testutils.h"

#include "models/ByteArrayWrapper.h"

TEST_F(TestQtJson, testBuildInTypes)
{
    ASSERT_TRUE(TestUtils::serialization<QRect>());
    ASSERT_TRUE(TestUtils::serialization<QSize>());
    ASSERT_TRUE(TestUtils::serialization<QPoint>());
    ASSERT_TRUE(TestUtils::serialization<ByteArrayWrapper>());
}

TEST_F(TestQtJson, MyClass)
{
    ASSERT_TRUE(TestUtils::serialization<MyClass>());
}

TEST_F(TestQtJson, MyClassList)
{
    ASSERT_TRUE(TestUtils::serialization<QList<MyClass>>());
}

TEST_F(TestQtJson, MyClassVector)
{
    ASSERT_TRUE(TestUtils::serialization<QVector<MyClass>>());
}

TEST_F(TestQtJson, MyClass_stdvector)
{
    ASSERT_TRUE(TestUtils::serialization<std::vector<MyClass>>());
}

TEST_F(TestQtJson, StdMapStdStringInt)
{
    using MyClassIntMap = std::map<QString, int>;

    ASSERT_TRUE(TestUtils::serialization<MyClassIntMap>());
}

TEST_F(TestQtJson, StdMapIntInt)
{
    using MyClassIntMap = std::map<int, int>;

    ASSERT_TRUE(TestUtils::serialization<MyClassIntMap>());
}

TEST_F(TestQtJson, StdMapIntQString)
{
    using MyClassIntMap = std::map<int, QString>;

    ASSERT_TRUE(TestUtils::serialization<MyClassIntMap>());
}

TEST_F(TestQtJson, StdMapStdStringQString)
{
    using MyClassIntMap = std::map<QString, QString>;

    ASSERT_TRUE(TestUtils::serialization<MyClassIntMap>());
}

TEST_F(TestQtJson, StdMapStdStringMyClass)
{
    using MyClassIntMap = std::map<QString, MyClass>;

    ASSERT_TRUE(TestUtils::serialization<MyClassIntMap>());
}

TEST_F(TestQtJson, StdMapQString)
{
    using MyClassIntMap = std::map<QString, QString>;
    ASSERT_TRUE(TestUtils::serialization<MyClassIntMap>());
}

TEST_F(TestQtJson, StdMapQStringMyClass)
{
    using MyClassIntMap = std::map<QString, MyClass>;
    ASSERT_TRUE(TestUtils::serialization<MyClassIntMap>());
}

TEST_F(TestQtJson, QMapMapQStringQString)
{
    using MyClassIntMap = QMap<QString, QString>;
    ASSERT_TRUE(TestUtils::serialization<MyClassIntMap>());
}

TEST_F(TestQtJson, QMapQStringMyClass)
{
    using MyClassIntMap = QMap<QString, MyClass>;
    ASSERT_TRUE(TestUtils::serialization<MyClassIntMap>());
}


TEST_F(TestQtJson, TestObject)
{
    ASSERT_TRUE(TestUtils::serialization<TestObject>());
}

TEST_F(TestQtJson, TestObjectList)
{
    ASSERT_TRUE(TestUtils::serialization<QList<TestObject>>());
}

