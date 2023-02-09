#include "TestQtJson.h"
#include "TestEnv.h"

#include "testutils.h"

testing::AssertionResult processJson(const QList<QByteArray> &_data, const QVariantList &_validData)
{
    QVariantList parsedArr;
    JsonStreamParser parser;
    QObject::connect(&parser, &JsonStreamParser::objectReceived, [&](const QVariant &_v)
    {
        parsedArr << _v;
    });

    for(auto &it : _data)
    {
        parser.processData(it);
    }

    return TestUtils::compareArr(_validData, parsedArr);
}


TEST(TestJsonStreamReader, test1)
{
    QByteArray jsonData = R"foo(
    {
        "endTime": 2,
        "guid": "Key-50c8cde5-6616-4ac1-b7c3-a55cc8a4f06d1",
        "id": 1,
        "instructorId": [
            2
        ],
        "isExam": false,
        "operatorId": [
            1
        ],
        "programmType2Id": 6,
        "startTime": 0
    }
    {
        "endTime": 3,
        "guid": "Key-50c8cde5-6616-4ac1-b7c3-a55cc8a4f06d2",
        "id": 2,
        "instructorId": [
            2
        ],
        "isExam": false,
        "operatorId": [
            1
        ],
        "programmType2Id": 6,
        "startTime": 0
    }
    )foo";


    QVariantList dataArr = {
        QVariantMap {
            { "endTime", 2 },
            { "guid", "Key-50c8cde5-6616-4ac1-b7c3-a55cc8a4f06d1" },
            { "id", 1 },
            { "instructorId", QVariantList { 2 } },
            { "isExam", false },
            { "operatorId", QVariantList { 1 } },
            { "programmType2Id", 6 },
            { "startTime", 0 },
        },
        QVariantMap {
            { "endTime", 3 },
            { "guid", "Key-50c8cde5-6616-4ac1-b7c3-a55cc8a4f06d2" },
            { "id", 2 },
            { "instructorId", QVariantList { 2 } },
            { "isExam", false },
            { "operatorId", QVariantList { 1 } },
            { "programmType2Id", 6 },
            { "startTime", 0 },
        },
    };

    ASSERT_TRUE(processJson({ jsonData }, dataArr));
    ASSERT_TRUE(processJson({ jsonData.mid(0, 10), jsonData.mid(10) }, dataArr));
    ASSERT_TRUE(processJson({ jsonData.mid(0, 100), jsonData.mid(100) }, dataArr));
    ASSERT_TRUE(processJson({ jsonData.mid(0, 10), jsonData.mid(10, 20), jsonData.mid(30) }, dataArr));
}

