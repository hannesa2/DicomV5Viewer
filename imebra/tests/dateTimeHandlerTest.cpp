#include <imebra/imebra.h>
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

TEST(dateTimeHandlerTest, dateTest)
{
    MutableDataSet testDataSet;

    testDataSet.setDate(TagId(0x0008, 0x0012), Date(2004, 11, 5, 9, 20, 30, 5000, 1, 2));
    Date checkDate = testDataSet.getDate(TagId(0x0008, 0x0012), 0);
    std::string checkString = testDataSet.getString(TagId(0x0008, 0x0012), 0);
    EXPECT_EQ("20041105", checkString);
    EXPECT_EQ(2004u, checkDate.getYear());
    EXPECT_EQ(11u, checkDate.getMonth());
    EXPECT_EQ(5u, checkDate.getDay());
    EXPECT_EQ(0u, checkDate.getHour());
    EXPECT_EQ(0u, checkDate.getMinutes());
    EXPECT_EQ(0u, checkDate.getSeconds());
    EXPECT_EQ(0u, checkDate.getNanoseconds());
    EXPECT_EQ(0, checkDate.getOffsetHours());
    EXPECT_EQ(0, checkDate.getOffsetMinutes());
    EXPECT_EQ(tagVR_t::DA, testDataSet.getDataType(TagId(0x0008, 0x0012)));


    testDataSet.setString(TagId(0x0008, 0x0012), "20120910");
    Date checkDate1 = testDataSet.getDate(TagId(0x0008, 0x0012), 0);
    EXPECT_EQ(2012u, checkDate1.getYear());
    EXPECT_EQ(9u, checkDate1.getMonth());
    EXPECT_EQ(10u, checkDate1.getDay());
    EXPECT_EQ(0u, checkDate1.getHour());
    EXPECT_EQ(0u, checkDate1.getMinutes());
    EXPECT_EQ(0u, checkDate1.getSeconds());
    EXPECT_EQ(0u, checkDate1.getNanoseconds());
    EXPECT_EQ(0, checkDate1.getOffsetHours());
    EXPECT_EQ(0, checkDate1.getOffsetMinutes());
}

TEST(dateTimeHandlerTest, timeTest)
{
    MutableDataSet testDataSet;

    {
        testDataSet.setDate(TagId(0x0008, 0x0013), Date(2004, 11, 5, 9, 20, 30, 5000, 1, 2));
        Date checkDate = testDataSet.getDate(TagId(0x0008, 0x0013), 0);
        std::string checkString = testDataSet.getString(TagId(0x0008, 0x0013), 0);
        EXPECT_EQ("092030.005000", checkString);
        EXPECT_EQ(0u, checkDate.getYear());
        EXPECT_EQ(0u, checkDate.getMonth());
        EXPECT_EQ(0u, checkDate.getDay());
        EXPECT_EQ(9u, checkDate.getHour());
        EXPECT_EQ(20u, checkDate.getMinutes());
        EXPECT_EQ(30u, checkDate.getSeconds());
        EXPECT_EQ(5000u, checkDate.getNanoseconds());
        EXPECT_EQ(0, checkDate.getOffsetHours());
        EXPECT_EQ(0, checkDate.getOffsetMinutes());
        EXPECT_EQ(tagVR_t::TM, testDataSet.getDataType(TagId(0x0008, 0x0013)));
    }

    {
        testDataSet.setString(TagId(0x0008, 0x0013), "101502");
        Date checkDate = testDataSet.getDate(TagId(0x0008, 0x0013), 0);
        EXPECT_EQ(0u, checkDate.getYear());
        EXPECT_EQ(0u, checkDate.getMonth());
        EXPECT_EQ(0u, checkDate.getDay());
        EXPECT_EQ(10u, checkDate.getHour());
        EXPECT_EQ(15u, checkDate.getMinutes());
        EXPECT_EQ(2u, checkDate.getSeconds());
        EXPECT_EQ(0u, checkDate.getNanoseconds());
        EXPECT_EQ(0, checkDate.getOffsetHours());
        EXPECT_EQ(0, checkDate.getOffsetMinutes());
    }

    {
        testDataSet.setString(TagId(0x0008, 0x0013), "1015");
        Date checkDate = testDataSet.getDate(TagId(0x0008, 0x0013), 0);
        EXPECT_EQ(0u, checkDate.getYear());
        EXPECT_EQ(0u, checkDate.getMonth());
        EXPECT_EQ(0u, checkDate.getDay());
        EXPECT_EQ(10u, checkDate.getHour());
        EXPECT_EQ(15u, checkDate.getMinutes());
        EXPECT_EQ(0u, checkDate.getSeconds());
        EXPECT_EQ(0u, checkDate.getNanoseconds());
        EXPECT_EQ(0, checkDate.getOffsetHours());
        EXPECT_EQ(0, checkDate.getOffsetMinutes());
    }
}

TEST(dateTimeHandlerTest, dateTimeTest)
{
    MutableDataSet testDataSet;

    Date testDate(2004, 11, 5, 9, 20, 40, 5000, 1, 2);
    testDataSet.setDate(TagId(0x0008, 0x002A), testDate);

    Date checkDate = testDataSet.getDate(TagId(0x0008, 0x002A), 0);

    EXPECT_EQ(2004u, checkDate.getYear());
    EXPECT_EQ(11u, checkDate.getMonth());
    EXPECT_EQ(5u, checkDate.getDay());
    EXPECT_EQ(9u, checkDate.getHour());
    EXPECT_EQ(20u, checkDate.getMinutes());
    EXPECT_EQ(40u, checkDate.getSeconds());
    EXPECT_EQ(5000u, checkDate.getNanoseconds());
    EXPECT_EQ(1, checkDate.getOffsetHours());
    EXPECT_EQ(2, checkDate.getOffsetMinutes());

    EXPECT_EQ("20041105092040.005000+0102", testDataSet.getString(TagId(0x0008, 0x002A), 0));
}


TEST(dateTimeHandlerTest, incompleteDateTimeTest)
{
    MutableDataSet testDataSet;

    testDataSet.setString(TagId(0x0008, 0x002A), "19990120");
    {
        Date checkDate = testDataSet.getDate(TagId(0x0008, 0x002A), 0);

        EXPECT_EQ(1999u, checkDate.getYear());
        EXPECT_EQ(1u, checkDate.getMonth());
        EXPECT_EQ(20u, checkDate.getDay());
        EXPECT_EQ(0u, checkDate.getHour());
        EXPECT_EQ(0u, checkDate.getMinutes());
        EXPECT_EQ(0u, checkDate.getSeconds());
        EXPECT_EQ(0u, checkDate.getNanoseconds());
        EXPECT_EQ(0, checkDate.getOffsetHours());
        EXPECT_EQ(0, checkDate.getOffsetMinutes());
    }

    testDataSet.setString(TagId(0x0008, 0x002A), "1999012012");
    {
        Date checkDate = testDataSet.getDate(TagId(0x0008, 0x002A), 0);

        EXPECT_EQ(1999u, checkDate.getYear());
        EXPECT_EQ(1u, checkDate.getMonth());
        EXPECT_EQ(20u, checkDate.getDay());
        EXPECT_EQ(12u, checkDate.getHour());
        EXPECT_EQ(0u, checkDate.getMinutes());
        EXPECT_EQ(0u, checkDate.getSeconds());
        EXPECT_EQ(0u, checkDate.getNanoseconds());
        EXPECT_EQ(0, checkDate.getOffsetHours());
        EXPECT_EQ(0, checkDate.getOffsetMinutes());
    }
}

} // namespace tests

} // namespace imebra

