#include <imebra/imebra.h>
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

TEST(stringHandlerTest, DSTest)
{
    {
        MutableDataSet testDataSet;
        testDataSet.setDouble(TagId(0x0028, 0x1051), 0.000001, tagVR_t::DS);
        std::string decimalString = testDataSet.getString(TagId(0x0028, 0x1051), 0);
        ASSERT_TRUE(decimalString == "1e-006" || decimalString == "1e-06" || decimalString == "1e-6");
        double decimalValue = testDataSet.getDouble(TagId(0x0028, 0x1051), 0);
        ASSERT_DOUBLE_EQ(0.000001, decimalValue);
        ASSERT_EQ(tagVR_t::DS, testDataSet.getDataType(TagId(0x0028, 0x1051)));
        ASSERT_THROW(testDataSet.getDate(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getAge(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        EXPECT_THROW(testDataSet.getUnicodeString(TagId(0x0028, 0x1051), 1), MissingItemError);
        EXPECT_THROW(testDataSet.getString(TagId(0x0028, 0x1051), 1), MissingItemError);
        EXPECT_THROW(testDataSet.getInt32(TagId(0x0028, 0x1051), 1), MissingItemError);
        EXPECT_THROW(testDataSet.getUint32(TagId(0x0028, 0x1051), 1), MissingItemError);
        EXPECT_THROW(testDataSet.getDouble(TagId(0x0028, 0x1051), 1), MissingItemError);
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setString(TagId(0x0028, 0x1051), "-2e-8", tagVR_t::DS);
        ASSERT_DOUBLE_EQ(-0.00000002, testDataSet.getDouble(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getInt32(TagId(0x0028, 0x1051), 1), MissingItemError);
        ASSERT_EQ(tagVR_t::DS, testDataSet.getDataType(TagId(0x0028, 0x1051)));
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setString(TagId(0x0028, 0x1051), "20", tagVR_t::DS);
        ASSERT_DOUBLE_EQ(20.0, testDataSet.getDouble(TagId(0x0028, 0x1051), 0));
        ASSERT_FLOAT_EQ(20.0f, testDataSet.getFloat(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(20, testDataSet.getInt32(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(20u, testDataSet.getUint32(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(20, testDataSet.getInt16(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(20u, testDataSet.getUint16(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(20, testDataSet.getInt8(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(20u, testDataSet.getUint8(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(tagVR_t::DS, testDataSet.getDataType(TagId(0x0028, 0x1051)));
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setInt32(TagId(0x0028, 0x1051), 40, tagVR_t::DS);
        ASSERT_EQ("40", testDataSet.getString(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(40, testDataSet.getInt32(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(40u, testDataSet.getUint32(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(tagVR_t::DS, testDataSet.getDataType(TagId(0x0028, 0x1051)));
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setUint32(TagId(0x0028, 0x1051), 50, tagVR_t::DS);
        ASSERT_EQ("50", testDataSet.getString(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(50, testDataSet.getInt32(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(50u, testDataSet.getUint32(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(tagVR_t::DS, testDataSet.getDataType(TagId(0x0028, 0x1051)));
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setString(TagId(0x0028, 0x1051), "Hello", tagVR_t::DS);
        ASSERT_THROW(testDataSet.getInt32(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint32(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt16(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint16(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getDouble(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getFloat(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
    }
}


TEST(stringHandlerTest, ISTest)
{
    {
        MutableDataSet testDataSet;
        testDataSet.setDouble(TagId(0x0028, 0x1051), 12.004, tagVR_t::IS);
        ASSERT_EQ("12", testDataSet.getString(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(12, testDataSet.getInt32(TagId(0x0028, 0x1051), 0));
        ASSERT_DOUBLE_EQ(12.0, testDataSet.getDouble(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(tagVR_t::IS, testDataSet.getDataType(TagId(0x0028, 0x1051)));
        ASSERT_THROW(testDataSet.getDate(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getAge(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setInt32(TagId(0x0028, 0x1051), 20, tagVR_t::IS);
        ASSERT_EQ("20", testDataSet.getString(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(20, testDataSet.getInt32(TagId(0x0028, 0x1051), 0));
        ASSERT_DOUBLE_EQ(20.0, testDataSet.getDouble(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(tagVR_t::IS, testDataSet.getDataType(TagId(0x0028, 0x1051)));
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setString(TagId(0x0028, 0x1051), "123456789012", tagVR_t::IS);
        ASSERT_THROW(testDataSet.setString(TagId(0x0028, 0x1051), "1234567890123", tagVR_t::IS), DataHandlerInvalidDataError);
    }

}


TEST(stringHandlerTest, AETest)
{
    MutableDataSet testDataSet;

    testDataSet.setString(TagId(0x0010, 0x0010), "0123456789012345", tagVR_t::AE);
    ASSERT_EQ("0123456789012345", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    ASSERT_THROW(testDataSet.getDate(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getAge(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);

    testDataSet.setString(TagId(0x0010, 0x0010), "012345678901234", tagVR_t::AE);
    ASSERT_EQ("012345678901234", testDataSet.getString(TagId(0x0010, 0x0010), 0));

    ASSERT_EQ(tagVR_t::AE, testDataSet.getDataType(TagId(0x0010, 0x0010)));

    ASSERT_THROW(testDataSet.setString(TagId(0x0010, 0x0010), "01234567890123456", tagVR_t::AE), DataHandlerInvalidDataError);
}


TEST(stringHandlerTest, zeroPad)
{
    MutableDataSet testDataSet;

    testDataSet.setString(TagId(0x0010, 0x0010), "0\000", tagVR_t::AE);
    ASSERT_EQ("0", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    ASSERT_EQ(1u, testDataSet.getString(TagId(0x0010, 0x0010), 0).length());
}


TEST(stringHandlerTest, URTest)
{
    MutableDataSet testDataSet;

    std::string longString(size_t(40000u), 'a');
    testDataSet.setString(TagId(0x0010, 0x0010), longString, tagVR_t::UR);
    ASSERT_EQ(longString, testDataSet.getString(TagId(0x0010, 0x0010), 0));

    ASSERT_THROW(testDataSet.getDate(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getAge(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getUint32(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getInt32(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getDouble(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);

    ASSERT_EQ(tagVR_t::UR, testDataSet.getDataType(TagId(0x0010, 0x0010)));

    {
        WritingDataHandler dataHandler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0, tagVR_t::LT);
        dataHandler.setString(0, "test");
        ASSERT_THROW(dataHandler.setString(1, "test");, DataHandlerInvalidDataError);
    }
}


TEST(stringHandlerTest, LOTest)
{
    MutableDataSet testDataSet;

    testDataSet.setString(TagId(0x0010, 0x0010), "0123456789012345", tagVR_t::LO);
    ASSERT_EQ("0123456789012345", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    ASSERT_THROW(testDataSet.getDate(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getAge(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);

    {
        std::string longString(size_t(63u), 'a');
        testDataSet.setString(TagId(0x0010, 0x0010), longString, tagVR_t::LO);
        ASSERT_EQ(longString, testDataSet.getString(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(tagVR_t::LO, testDataSet.getDataType(TagId(0x0010, 0x0010)));
    }

    {
        std::string longString(size_t(64u), 'a');
        testDataSet.setString(TagId(0x0010, 0x0010), longString, tagVR_t::LO);
        ASSERT_EQ(longString, testDataSet.getString(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(tagVR_t::LO, testDataSet.getDataType(TagId(0x0010, 0x0010)));
    }

    {
        std::string longString(size_t(65u), 'a');
        ASSERT_THROW(testDataSet.setString(TagId(0x0010, 0x0010), longString, tagVR_t::LO), DataHandlerInvalidDataError);
    }
}


TEST(stringHandlerTest, LTTest)
{
    MutableDataSet testDataSet;

    testDataSet.setString(TagId(0x0010, 0x0010), "0123456789012345\\0123", tagVR_t::LT);
    ASSERT_EQ("0123456789012345\\0123", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    ASSERT_THROW(testDataSet.getDate(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getAge(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);

    {
        WritingDataHandler dataHandler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0, tagVR_t::LT);
        dataHandler.setString(0, "test\\test1");
        ASSERT_THROW(dataHandler.setString(1, "test");, DataHandlerInvalidDataError);
    }

    {
        std::string longString(size_t(63u), 'a');
        testDataSet.setString(TagId(0x0010, 0x0010), longString, tagVR_t::LT);
        ASSERT_EQ(longString, testDataSet.getString(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(tagVR_t::LT, testDataSet.getDataType(TagId(0x0010, 0x0010)));
    }

    {
        std::string longString(size_t(10240u), 'a');
        testDataSet.setString(TagId(0x0010, 0x0010), longString, tagVR_t::LT);
        ASSERT_EQ(longString, testDataSet.getString(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(tagVR_t::LT, testDataSet.getDataType(TagId(0x0010, 0x0010)));
    }

    {
        std::string longString(size_t(10241u), 'a');
        ASSERT_THROW(testDataSet.setString(TagId(0x0010, 0x0010), longString, tagVR_t::LT), DataHandlerInvalidDataError);
    }
}


TEST(stringHandlerTest, SHTest)
{
    MutableDataSet testDataSet;

    testDataSet.setString(TagId(0x0010, 0x0010), "0123456789012345", tagVR_t::SH);
    ASSERT_EQ("0123456789012345", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    ASSERT_THROW(testDataSet.getDate(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getAge(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);

    {
        WritingDataHandler shHandler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0, tagVR_t::SH);
        shHandler.setString(0, "item 0");
        shHandler.setString(1, "item 1");
        shHandler.setString(2, "item 2");
        ASSERT_EQ(tagVR_t::SH, shHandler.getDataType());
    }
    ASSERT_EQ("item 0", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    ASSERT_EQ("item 1", testDataSet.getString(TagId(0x0010, 0x0010), 1));
    ASSERT_EQ("item 2", testDataSet.getString(TagId(0x0010, 0x0010), 2));
    ReadingDataHandlerNumeric rawHandler = testDataSet.getReadingDataHandlerRaw(TagId(0x0010, 0x0010), 0);
    size_t dataSize;
    const char* data = rawHandler.data(&dataSize);
    std::string fullString(data, dataSize);
    ASSERT_EQ("item 0\\item 1\\item 2", fullString);

    ASSERT_THROW(testDataSet.setString(TagId(0x0010, 0x0010), "01234567890123456", tagVR_t::LT), DataHandlerInvalidDataError);
}


TEST(stringHandlerTest, STTest)
{
    MutableDataSet testDataSet;

    testDataSet.setString(TagId(0x0010, 0x0010), "0123456789012345", tagVR_t::ST);
    ASSERT_EQ("0123456789012345", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    ASSERT_THROW(testDataSet.getDate(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getAge(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);

    {
        WritingDataHandler dataHandler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0, tagVR_t::ST);
        dataHandler.setString(0, "test");
        ASSERT_THROW(dataHandler.setString(1, "test");, DataHandlerInvalidDataError);
    }

    {
        std::string longString(size_t(1024u), 'a');
        testDataSet.setString(TagId(0x0010, 0x0010), longString, tagVR_t::ST);
        ASSERT_EQ(longString, testDataSet.getString(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(tagVR_t::ST, testDataSet.getDataType(TagId(0x0010, 0x0010)));

    }

    {
        std::string longString(size_t(1025u), 'a');
        ASSERT_THROW(testDataSet.setString(TagId(0x0010, 0x0010), longString, tagVR_t::ST), DataHandlerInvalidDataError);
    }
}


TEST(stringHandlerTest, UITest)
{
    MutableDataSet testDataSet;

    testDataSet.setString(TagId(0x0010, 0x0010), "0123456789012345", tagVR_t::UI);
    ASSERT_EQ("123456789012345", testDataSet.getString(TagId(0x0010, 0x0010), 0));

    testDataSet.setString(TagId(0x0010, 0x0010), "012345.6789.012345", tagVR_t::UI);
    ASSERT_EQ("12345.6789.12345", testDataSet.getString(TagId(0x0010, 0x0010), 0));

    testDataSet.setString(TagId(0x0010, 0x0010), "12345.6789.012345", tagVR_t::UI);
    ASSERT_EQ("12345.6789.12345", testDataSet.getString(TagId(0x0010, 0x0010), 0));

    testDataSet.setString(TagId(0x0010, 0x0010), "12345.6789..00012345", tagVR_t::UI);
    ASSERT_EQ("12345.6789.0.12345", testDataSet.getString(TagId(0x0010, 0x0010), 0));

    testDataSet.setString(TagId(0x0010, 0x0010), "12345.6789.0.00012345", tagVR_t::UI);
    ASSERT_EQ("12345.6789.0.12345", testDataSet.getString(TagId(0x0010, 0x0010), 0));

    testDataSet.setString(TagId(0x0010, 0x0010), "12345.6789.0.00012345.", tagVR_t::UI);
    ASSERT_EQ("12345.6789.0.12345.0", testDataSet.getString(TagId(0x0010, 0x0010), 0));

    testDataSet.setString(TagId(0x0010, 0x0010), ".12345.6789.0.00012345.", tagVR_t::UI);
    ASSERT_EQ("0.12345.6789.0.12345.0", testDataSet.getString(TagId(0x0010, 0x0010), 0));

    ASSERT_THROW(testDataSet.setString(TagId(0x0010, 0x0010), "1.3.r"), DataHandlerInvalidDataError);
    ASSERT_THROW(testDataSet.getDate(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getAge(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getUint32(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getInt32(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);

    {
        WritingDataHandler dataHandler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0, tagVR_t::UI);
        dataHandler.setString(0, "1");
        ASSERT_THROW(dataHandler.setString(1, "1");, DataHandlerInvalidDataError);
    }
    ASSERT_EQ("1", testDataSet.getString(TagId(0x0010, 0x0010), 0));

    {
        std::string longString(size_t(64u), '1');
        testDataSet.setString(TagId(0x0010, 0x0010), longString, tagVR_t::UI);
        ASSERT_EQ(longString, testDataSet.getString(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(tagVR_t::UI, testDataSet.getDataType(TagId(0x0010, 0x0010)));
    }

    {
        std::string longString(size_t(65u), '1');
        ASSERT_THROW(testDataSet.setString(TagId(0x0010, 0x0010), longString, tagVR_t::UI), DataHandlerInvalidDataError);
    }
}


TEST(stringHandlerTest, UCTest)
{
    MutableDataSet testDataSet;

    testDataSet.setUnicodeString(TagId(0x0010, 0x0010), L"0123456789012345", tagVR_t::UC);
    ASSERT_EQ("0123456789012345", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    ASSERT_EQ(L"0123456789012345", testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 0));
    ASSERT_THROW(testDataSet.getDate(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getAge(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);

    {
        {
            WritingDataHandler dataHandler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0, tagVR_t::UC);
            dataHandler.setUnicodeString(0, L"test0");
            dataHandler.setUnicodeString(1, L"test1");
        }
        ASSERT_EQ(L"test0", testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(L"test1", testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 1));
    }

    {
        std::string longString(size_t(100000u), 'a');
        testDataSet.setString(TagId(0x0010, 0x0010), longString, tagVR_t::UC);
        ASSERT_EQ(longString, testDataSet.getString(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(tagVR_t::UC, testDataSet.getDataType(TagId(0x0010, 0x0010)));
    }

}


TEST(stringHandlerTest, UTTest)
{
    MutableDataSet testDataSet;

    testDataSet.setString(TagId(0x0010, 0x0010), "0123456789012345", tagVR_t::UT);
    ASSERT_EQ("0123456789012345", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    ASSERT_THROW(testDataSet.getDate(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getAge(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);

    {
        WritingDataHandler dataHandler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0, tagVR_t::UT);
        dataHandler.setString(0, "test");
        ASSERT_THROW(dataHandler.setString(1, "test");, DataHandlerInvalidDataError);
    }

    {
        std::string longString(size_t(100000u), 'a');
        testDataSet.setString(TagId(0x0010, 0x0010), longString, tagVR_t::UT);
        ASSERT_EQ(longString, testDataSet.getString(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(tagVR_t::UT, testDataSet.getDataType(TagId(0x0010, 0x0010)));
    }

}


TEST(stringHandlerTest, PNTest)
{
    MutableDataSet testDataSet;

    {
        PatientName defaultValue("alphabetic", "ideographic", "phonetic");
        PatientName checkPatientName0 = testDataSet.getPatientName(TagId(0x0010, 0x0010), 0, defaultValue);
        ASSERT_EQ("alphabetic", checkPatientName0.getAlphabeticRepresentation());
        ASSERT_EQ("ideographic", checkPatientName0.getIdeographicRepresentation());
        ASSERT_EQ("phonetic", checkPatientName0.getPhoneticRepresentation());
    }

    {
        testDataSet.setString(TagId(0x0010, 0x0010), "PatientName", tagVR_t::PN);
        ASSERT_EQ("PatientName", testDataSet.getString(TagId(0x0010, 0x0010), 0));
        ASSERT_THROW(testDataSet.getDate(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getAge(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);

        {
            WritingDataHandler pnHandler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0, tagVR_t::PN);
            pnHandler.setString(0, "Patient^0=Patient^1=Patient^2");
            pnHandler.setString(1, "Patient^3=Patient^4");
        }

        {
            ASSERT_EQ("Patient^0=Patient^1=Patient^2", testDataSet.getString(TagId(0x0010, 0x0010), 0));
            ASSERT_EQ("Patient^3=Patient^4", testDataSet.getString(TagId(0x0010, 0x0010), 1));
            PatientName patientName0 = testDataSet.getPatientName(TagId(0x0010, 0x0010), 0);
            ASSERT_EQ("Patient^0", patientName0.getAlphabeticRepresentation());
            ASSERT_EQ("Patient^1", patientName0.getIdeographicRepresentation());
            ASSERT_EQ("Patient^2", patientName0.getPhoneticRepresentation());
            PatientName patientName1 = testDataSet.getPatientName(TagId(0x0010, 0x0010), 1);
            ASSERT_EQ("Patient^3", patientName1.getAlphabeticRepresentation());
            ASSERT_EQ("Patient^4", patientName1.getIdeographicRepresentation());
            ASSERT_EQ("", patientName1.getPhoneticRepresentation());
        }

        {
            ReadingDataHandler patientDataHandler = testDataSet.getReadingDataHandler(TagId(0x0010, 0x0010), 0);
            PatientName patientName0 = patientDataHandler.getPatientName(0);
            ASSERT_EQ("Patient^0", patientName0.getAlphabeticRepresentation());
            ASSERT_EQ("Patient^1", patientName0.getIdeographicRepresentation());
            ASSERT_EQ("Patient^2", patientName0.getPhoneticRepresentation());
            PatientName patientName1 = patientDataHandler.getPatientName(1);
            ASSERT_EQ("Patient^3", patientName1.getAlphabeticRepresentation());
            ASSERT_EQ("Patient^4", patientName1.getIdeographicRepresentation());
            ASSERT_EQ("", patientName1.getPhoneticRepresentation());
        }

        ASSERT_THROW(testDataSet.getUint32(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt32(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getDouble(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);

        MutableMemory savedDicom;
        MemoryStreamOutput writeDicom(savedDicom);
        StreamWriter writer(writeDicom);
        CodecFactory::save(testDataSet, writer, codecType_t::dicom);

        MemoryStreamInput readDicom(savedDicom);
        StreamReader reader(readDicom);
        DataSet checkDataSet = CodecFactory::load(reader);

        ReadingDataHandlerNumeric rawHandler = checkDataSet.getReadingDataHandlerRaw(TagId(0x0010, 0x0010), 0);
        size_t dataSize;
        const char* data = rawHandler.data(&dataSize);
        std::string fullString(data, dataSize);
        ASSERT_EQ("Patient^0=Patient^1=Patient^2\\Patient^3=Patient^4 ", fullString);
        ASSERT_EQ("Patient^0=Patient^1=Patient^2", checkDataSet.getString(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ("Patient^3=Patient^4", checkDataSet.getString(TagId(0x0010, 0x0010), 1));
        PatientName patientName0(checkDataSet.getPatientName(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ("Patient^0", patientName0.getAlphabeticRepresentation());
        ASSERT_EQ("Patient^1", patientName0.getIdeographicRepresentation());
        ASSERT_EQ("Patient^2", patientName0.getPhoneticRepresentation());
        PatientName patientName1(checkDataSet.getPatientName(TagId(0x0010, 0x0010), 1));
        ASSERT_EQ("Patient^3", patientName1.getAlphabeticRepresentation());
        ASSERT_EQ("Patient^4", patientName1.getIdeographicRepresentation());
    }

    {
        PatientName writePatient("alphabetic^representation", "", "");
        testDataSet.setPatientName(TagId(0x0010, 0x0010), writePatient);

        PatientName checkPatient(testDataSet.getPatientName(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(writePatient.getAlphabeticRepresentation(), checkPatient.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient.getIdeographicRepresentation(), checkPatient.getIdeographicRepresentation());
        ASSERT_EQ(writePatient.getPhoneticRepresentation(), checkPatient.getPhoneticRepresentation());
        ASSERT_EQ("alphabetic^representation", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    }

    {
        PatientName writePatient("alphabetic^representation", "ideographic^representation", "phonetic^representation");
        testDataSet.setPatientName(TagId(0x0010, 0x0010), writePatient);

        PatientName checkPatient(testDataSet.getPatientName(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(writePatient.getAlphabeticRepresentation(), checkPatient.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient.getIdeographicRepresentation(), checkPatient.getIdeographicRepresentation());
        ASSERT_EQ(writePatient.getPhoneticRepresentation(), checkPatient.getPhoneticRepresentation());
        ASSERT_EQ("alphabetic^representation=ideographic^representation=phonetic^representation", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    }

    {
        PatientName writePatient("", "ideographic^representation", "phonetic^representation");
        testDataSet.setPatientName(TagId(0x0010, 0x0010), writePatient);

        PatientName checkPatient(testDataSet.getPatientName(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(writePatient.getAlphabeticRepresentation(), checkPatient.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient.getIdeographicRepresentation(), checkPatient.getIdeographicRepresentation());
        ASSERT_EQ(writePatient.getPhoneticRepresentation(), checkPatient.getPhoneticRepresentation());
        ASSERT_EQ("=ideographic^representation=phonetic^representation", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    }

    {
        PatientName writePatient("", "", "phonetic^representation");
        testDataSet.setPatientName(TagId(0x0010, 0x0010), writePatient);

        PatientName checkPatient(testDataSet.getPatientName(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(writePatient.getAlphabeticRepresentation(), checkPatient.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient.getIdeographicRepresentation(), checkPatient.getIdeographicRepresentation());
        ASSERT_EQ(writePatient.getPhoneticRepresentation(), checkPatient.getPhoneticRepresentation());
        ASSERT_EQ("==phonetic^representation", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    }

    {
        PatientName writePatient("", "", "");
        testDataSet.setPatientName(TagId(0x0010, 0x0010), writePatient);

        PatientName checkPatient(testDataSet.getPatientName(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(writePatient.getAlphabeticRepresentation(), checkPatient.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient.getIdeographicRepresentation(), checkPatient.getIdeographicRepresentation());
        ASSERT_EQ(writePatient.getPhoneticRepresentation(), checkPatient.getPhoneticRepresentation());
        ASSERT_EQ("", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    }

    {
        PatientName writePatient("alphabetic^representation", "", "phonetic^representation");
        testDataSet.setPatientName(TagId(0x0010, 0x0010), writePatient);

        PatientName checkPatient(testDataSet.getPatientName(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(writePatient.getAlphabeticRepresentation(), checkPatient.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient.getIdeographicRepresentation(), checkPatient.getIdeographicRepresentation());
        ASSERT_EQ(writePatient.getPhoneticRepresentation(), checkPatient.getPhoneticRepresentation());
        ASSERT_EQ("alphabetic^representation==phonetic^representation", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    }

    {
        PatientName writePatient0("", "", "phonetic^representation");
        PatientName writePatient1("alphabetic^representation", "", "phonetic^representation");

        {
            WritingDataHandler handler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0, tagVR_t::PN);
            handler.setPatientName(0, writePatient0);
            handler.setPatientName(1, writePatient1);
        }

        PatientName checkPatient0(testDataSet.getPatientName(TagId(0x0010, 0x0010), 0));
        PatientName checkPatient1(testDataSet.getPatientName(TagId(0x0010, 0x0010), 1));
        ASSERT_EQ(writePatient0.getAlphabeticRepresentation(), checkPatient0.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient0.getIdeographicRepresentation(), checkPatient0.getIdeographicRepresentation());
        ASSERT_EQ(writePatient0.getPhoneticRepresentation(), checkPatient0.getPhoneticRepresentation());

        ASSERT_EQ(writePatient1.getAlphabeticRepresentation(), checkPatient1.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient1.getIdeographicRepresentation(), checkPatient1.getIdeographicRepresentation());
        ASSERT_EQ(writePatient1.getPhoneticRepresentation(), checkPatient1.getPhoneticRepresentation());
    }
}


TEST(stringHandlerTest, CSTest)
{
    MutableDataSet testDataSet;

    testDataSet.setString(TagId(0x0010, 0x0010), "0123456789012345", tagVR_t::CS);
    ASSERT_EQ("0123456789012345", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    ASSERT_THROW(testDataSet.getDate(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getAge(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);

    testDataSet.setString(TagId(0x0010, 0x0010), "012345678901234", tagVR_t::CS);
    ASSERT_EQ("012345678901234", testDataSet.getString(TagId(0x0010, 0x0010), 0));

    ASSERT_THROW(testDataSet.setString(TagId(0x0010, 0x0010), "01234567890123456", tagVR_t::CS), DataHandlerInvalidDataError);

}


TEST(stringHandlerTest, ASTest)
{
    MutableDataSet dataSet;

    dataSet.setAge(TagId(0x0010, 0x1010), Age(3, imebra::ageUnit_t::days));
    {
        imebra::Age age = dataSet.getAge(TagId(imebra::tagId_t::PatientAge_0010_1010), 0);
        EXPECT_EQ(3u, age.getAgeValue());
        EXPECT_EQ(imebra::ageUnit_t::days, age.getAgeUnits());
        EXPECT_EQ("003D", dataSet.getString(TagId(imebra::tagId_t::PatientAge_0010_1010), 0));
        ASSERT_DOUBLE_EQ(0.00821917808219178, age.getYears());
    }

    ASSERT_THROW(dataSet.setDouble(TagId(imebra::tagId_t::PatientAge_0010_1010), .01), imebra::DataHandlerConversionError);

    ASSERT_THROW(dataSet.setUint32(TagId(imebra::tagId_t::PatientAge_0010_1010), 1), imebra::DataHandlerConversionError);

    ASSERT_THROW(dataSet.setInt32(TagId(imebra::tagId_t::PatientAge_0010_1010), 1), imebra::DataHandlerConversionError);

    ASSERT_THROW(dataSet.setDate(TagId(imebra::tagId_t::PatientAge_0010_1010), imebra::Date(2000, 1, 1, 0, 0, 0, 0, 0, 0)), imebra::DataHandlerConversionError);

    dataSet.setString(TagId(imebra::tagId_t::PatientAge_0010_1010), "005M");
    {
        imebra::Age age = dataSet.getAge(TagId(imebra::tagId_t::PatientAge_0010_1010), 0);
        EXPECT_EQ(5u, age.getAgeValue());
        EXPECT_EQ(imebra::ageUnit_t::months, age.getAgeUnits());
        EXPECT_DOUBLE_EQ(0.41666666666666669, age.getYears());
    }

    dataSet.setString(TagId(imebra::tagId_t::PatientAge_0010_1010), "018W");
    {
        imebra::Age age = dataSet.getAge(TagId(imebra::tagId_t::PatientAge_0010_1010), 0);
        EXPECT_EQ(18u, age.getAgeValue());
        EXPECT_EQ(imebra::ageUnit_t::weeks, age.getAgeUnits());
        EXPECT_DOUBLE_EQ(0.34520548039782323, age.getYears());
    }

    dataSet.setString(TagId(imebra::tagId_t::PatientAge_0010_1010), "090Y");
    {
        imebra::Age age = dataSet.getAge(TagId(imebra::tagId_t::PatientAge_0010_1010), 0);
        EXPECT_EQ(90u, age.getAgeValue());
        EXPECT_EQ(imebra::ageUnit_t::years, age.getAgeUnits());
        EXPECT_DOUBLE_EQ(90.0, age.getYears());
    }

    dataSet.setString(TagId(imebra::tagId_t::PatientAge_0010_1010), "018K");
    {
        ASSERT_THROW(imebra::Age age = dataSet.getAge(TagId(imebra::tagId_t::PatientAge_0010_1010), 0), DataHandlerCorruptedBufferError);
    }

    ASSERT_THROW(dataSet.setString(TagId(imebra::tagId_t::PatientAge_0010_1010), "18Y"), DataHandlerInvalidDataError);

}

TEST(stringHandlerTest, testLimits)
{
    {
        MutableDataSet testDataSet;
        testDataSet.setString(TagId(0x0028, 0x1051), "-1", tagVR_t::LT);
        ASSERT_DOUBLE_EQ(-1.0, testDataSet.getDouble(TagId(0x0028, 0x1051), 0));
        ASSERT_FLOAT_EQ(-1.0f, testDataSet.getFloat(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getUint32(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_EQ(-1, testDataSet.getInt32(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getUint16(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_EQ(-1, testDataSet.getInt16(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getUint8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_EQ(-1, testDataSet.getInt8(TagId(0x0028, 0x1051), 0));
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setDouble(TagId(0x0028, 0x1051), 10e+40, tagVR_t::DS);
        ASSERT_DOUBLE_EQ(10e+40, testDataSet.getDouble(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getFloat(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setString(TagId(0x0028, 0x1051), "100000000000000000000", tagVR_t::LT);
        ASSERT_DOUBLE_EQ(1e+20, testDataSet.getDouble(TagId(0x0028, 0x1051), 0));
        ASSERT_FLOAT_EQ(1e+20f, testDataSet.getFloat(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getUint32(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt32(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint16(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt16(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setUint32(TagId(0x0028, 0x1051), std::numeric_limits<std::uint32_t>::max(), tagVR_t::LT);
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<std::uint32_t>::max()), testDataSet.getDouble(TagId(0x0028, 0x1051), 0));
        ASSERT_FLOAT_EQ(static_cast<float>(std::numeric_limits<std::uint32_t>::max()), testDataSet.getFloat(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(std::numeric_limits<std::uint32_t>::max(), testDataSet.getUint32(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getInt32(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint16(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt16(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setUint16(TagId(0x0028, 0x1051), std::numeric_limits<std::uint16_t>::max(), tagVR_t::LT);
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<std::uint16_t>::max()), testDataSet.getDouble(TagId(0x0028, 0x1051), 0));
        ASSERT_FLOAT_EQ(static_cast<float>(std::numeric_limits<std::uint16_t>::max()), testDataSet.getFloat(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(std::numeric_limits<std::uint16_t>::max(), testDataSet.getUint32(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(std::numeric_limits<std::uint16_t>::max(), testDataSet.getInt32(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(std::numeric_limits<std::uint16_t>::max(), testDataSet.getUint16(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getInt16(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setUint8(TagId(0x0028, 0x1051), std::numeric_limits<std::uint8_t>::max(), tagVR_t::LT);
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<std::uint8_t>::max()), testDataSet.getDouble(TagId(0x0028, 0x1051), 0));
        ASSERT_FLOAT_EQ(static_cast<float>(std::numeric_limits<std::uint8_t>::max()), testDataSet.getFloat(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(std::numeric_limits<std::uint8_t>::max(), testDataSet.getUint32(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(std::numeric_limits<std::uint8_t>::max(), testDataSet.getInt32(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(std::numeric_limits<std::uint8_t>::max(), testDataSet.getUint16(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(std::numeric_limits<std::uint8_t>::max(), testDataSet.getInt16(TagId(0x0028, 0x1051), 0));
        ASSERT_EQ(std::numeric_limits<std::uint8_t>::max(), testDataSet.getUint8(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getInt8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setInt32(TagId(0x0028, 0x1051), std::numeric_limits<std::int32_t>::lowest(), tagVR_t::LT);
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<std::int32_t>::lowest()), testDataSet.getDouble(TagId(0x0028, 0x1051), 0));
        ASSERT_FLOAT_EQ(static_cast<float>(std::numeric_limits<std::int32_t>::lowest()), testDataSet.getFloat(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getUint32(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::int32_t>::lowest(), testDataSet.getInt32(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getUint16(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt16(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setInt32(TagId(0x0028, 0x1051), std::numeric_limits<std::int16_t>::lowest(), tagVR_t::LT);
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<std::int16_t>::lowest()), testDataSet.getDouble(TagId(0x0028, 0x1051), 0));
        ASSERT_FLOAT_EQ(static_cast<float>(std::numeric_limits<std::int16_t>::lowest()), testDataSet.getFloat(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getUint32(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::int16_t>::lowest(), testDataSet.getInt32(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getUint16(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::int16_t>::lowest(), testDataSet.getInt16(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getUint8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
    }

    {
        MutableDataSet testDataSet;
        testDataSet.setInt32(TagId(0x0028, 0x1051), std::numeric_limits<std::int8_t>::lowest(), tagVR_t::LT);
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<std::int8_t>::lowest()), testDataSet.getDouble(TagId(0x0028, 0x1051), 0));
        ASSERT_FLOAT_EQ(static_cast<float>(std::numeric_limits<std::int8_t>::lowest()), testDataSet.getFloat(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getUint32(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::int8_t>::lowest(), testDataSet.getInt32(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getUint16(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::int8_t>::lowest(), testDataSet.getInt16(TagId(0x0028, 0x1051), 0));
        ASSERT_THROW(testDataSet.getUint8(TagId(0x0028, 0x1051), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::int8_t>::lowest(), testDataSet.getInt8(TagId(0x0028, 0x1051), 0));
    }
}


} // namespace tests

} // namespace imebra
