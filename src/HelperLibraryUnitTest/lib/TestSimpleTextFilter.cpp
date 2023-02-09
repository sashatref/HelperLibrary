#include "TestSimpleTextFilter.h"
#include "TestEnv.h"

using namespace HelperLibraryNS;

TEST_F(TestSimpleTextFilter, testWhiteList)
{
    SimpleTextFilter filter;

    filter.rules.append({
        "*-KTV",
        "*-PTV"
    });

    filter.sensitivity = Qt::CaseInsensitive;
    filter.enabled = true;
    filter.checkType = SimpleTextFilter::WhiteList;

    ASSERT_TRUE(filter.checkText("INSTRUCTOR-KTV"));
    ASSERT_TRUE(filter.checkText("INSTRUCTOR-PTV"));
    ASSERT_FALSE(filter.checkText("INSTRUCTOR-LTV"));
    ASSERT_FALSE(filter.checkText("-LTV"));
    ASSERT_TRUE(filter.checkText("-KTV"));
    ASSERT_TRUE(filter.checkText("INSTRUCTOR-ktv"));
    ASSERT_FALSE(filter.checkText(""));
    ASSERT_FALSE(filter.checkText("INSTRUCTOR-KTV1"));
}

TEST_F(TestSimpleTextFilter, testBlackList)
{
    SimpleTextFilter filter;

    filter.rules.append({
        "*-KTV",
        "*-PTV"
    });

    filter.sensitivity = Qt::CaseInsensitive;
    filter.enabled = true;
    filter.checkType = SimpleTextFilter::BlackList;

    ASSERT_FALSE(filter.checkText("INSTRUCTOR-KTV"));
    ASSERT_FALSE(filter.checkText("INSTRUCTOR-PTV"));
    ASSERT_TRUE(filter.checkText("INSTRUCTOR-LTV"));
    ASSERT_TRUE(filter.checkText("-LTV"));
    ASSERT_FALSE(filter.checkText("-KTV"));
    ASSERT_FALSE(filter.checkText("INSTRUCTOR-ktv"));
    ASSERT_TRUE(filter.checkText(""));
    ASSERT_TRUE(filter.checkText("INSTRUCTOR-KTV1"));
}

TEST_F(TestSimpleTextFilter, testWhiteListCaseSensitive)
{
    SimpleTextFilter filter;

    filter.rules.append({
        "*-KTV",
        "*-PTV"
    });

    filter.sensitivity = Qt::CaseSensitive;
    filter.enabled = true;
    filter.checkType = SimpleTextFilter::WhiteList;

    ASSERT_TRUE(filter.checkText("INSTRUCTOR-KTV"));
    ASSERT_FALSE(filter.checkText("INSTRUCTOR-ktv"));
}

TEST_F(TestSimpleTextFilter, testDisabledFilter)
{
    SimpleTextFilter filter;

    filter.rules.append({
        "*-KTV",
        "*-PTV"
    });

    filter.sensitivity = Qt::CaseSensitive;
    filter.enabled = false;

    ASSERT_TRUE(filter.checkText("INSTRUCTOR-KTV"));
    ASSERT_TRUE(filter.checkText("INSTRUCTOR-PTV"));
    ASSERT_TRUE(filter.checkText("INSTRUCTOR-LTV"));
    ASSERT_TRUE(filter.checkText("-LTV"));
    ASSERT_TRUE(filter.checkText("-KTV"));
    ASSERT_TRUE(filter.checkText("INSTRUCTOR-ktv"));
    ASSERT_TRUE(filter.checkText(""));
    ASSERT_TRUE(filter.checkText("INSTRUCTOR-KTV1"));
}
