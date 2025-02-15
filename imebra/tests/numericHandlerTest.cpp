#include <imebra/imebra.h>
#include <string.h>
#include <memory>

#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

tagVR_t integerTags[] = {tagVR_t::OB, tagVR_t::OL, tagVR_t::SB, tagVR_t::UN, tagVR_t::OW, tagVR_t::SL, tagVR_t::SS, tagVR_t::UL, tagVR_t::US, tagVR_t::OV, tagVR_t::SV, tagVR_t::UV};
tagVR_t floatTags[] = {tagVR_t::FL, tagVR_t::OF, tagVR_t::FD, tagVR_t::OD};
tagVR_t allTags[] = {
    tagVR_t::AT,
    tagVR_t::OB,
    tagVR_t::OL,
    tagVR_t::OV,
    tagVR_t::SB,
    tagVR_t::UN,
    tagVR_t::OW,
    tagVR_t::SL,
    tagVR_t::SS,
    tagVR_t::SV,
    tagVR_t::UL,
    tagVR_t::US,
    tagVR_t::UV,
    tagVR_t::FL,
    tagVR_t::OF,
    tagVR_t::FD,
    tagVR_t::OD};

TEST(numericHandlerTest, testDouble)
{
    for(size_t scanVR(0); scanVR != sizeof(floatTags) / sizeof(tagVR_t); ++scanVR)
    {
        MutableDataSet testDataSet;

        {
            WritingDataHandlerNumeric handler = testDataSet.getWritingDataHandlerNumeric(TagId(10, 10), 0, floatTags[scanVR]);
            handler.setDouble(0, 5.6);
            handler.setDouble(1, 3.6);
            handler.setDouble(3, 2.6);
            handler.setInt32(4, 10);
            handler.setUint32(5, 20);
            handler.setString(6, "123.7");
            handler.setUnicodeString(7, L"124.9");
            ASSERT_THROW(handler.setDate(8, Date(2000, 1, 1, 0, 0, 0, 0, 0, 0)), DataHandlerConversionError);
            ASSERT_THROW(handler.setAge(8, Age(3, ageUnit_t::days)), DataHandlerConversionError);
            ASSERT_THROW(handler.setString(8, "test"), DataHandlerConversionError);

            ASSERT_EQ(floatTags[scanVR], handler.getDataType());

            ASSERT_TRUE(handler.isSigned());
            ASSERT_TRUE(handler.isFloat());

            // Write a negative value
            handler.setFloat(9, -1);

            // Write values valid only for double
            if(handler.getUnitSize() == sizeof(double))
            {
                handler.setDouble(10, static_cast<double>(std::numeric_limits<double>::max()) + 1.0);
                handler.setDouble(11, static_cast<double>(std::numeric_limits<double>::lowest()) - 1.0);
            }
            else
            {
                ASSERT_THROW(handler.setDouble(10, static_cast<double>(std::numeric_limits<double>::max()) + 1.0), DataHandlerConversionError);
                ASSERT_THROW(handler.setDouble(11, static_cast<double>(std::numeric_limits<double>::lowest()) - 1.0), DataHandlerConversionError);
            }
        }

        ReadingDataHandlerNumeric readingHandler = testDataSet.getReadingDataHandlerNumeric(TagId(10, 10), 0);
        ASSERT_TRUE(readingHandler.isFloat());

        ASSERT_FLOAT_EQ(5.6f, testDataSet.getFloat(TagId(10, 10), 0));
        ASSERT_FLOAT_EQ(3.6f, testDataSet.getFloat(TagId(10, 10), 1));
        ASSERT_FLOAT_EQ(2.6f, testDataSet.getFloat(TagId(10, 10), 3));
        ASSERT_FLOAT_EQ(10.0f, testDataSet.getFloat(TagId(10, 10), 4));
        ASSERT_FLOAT_EQ(20.0f, testDataSet.getFloat(TagId(10, 10), 5));
        ASSERT_FLOAT_EQ(123.7f, testDataSet.getFloat(TagId(10, 10), 6));
        ASSERT_FLOAT_EQ(124.9f, testDataSet.getFloat(TagId(10, 10), 7));
        ASSERT_FLOAT_EQ(-1.0f, testDataSet.getFloat(TagId(10, 10), 9));
        ASSERT_THROW(testDataSet.getUint64(TagId(10, 10), 9), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint32(TagId(10, 10), 9), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint16(TagId(10, 10), 9), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint8(TagId(10, 10), 9), DataHandlerConversionError);

        if(readingHandler.getUnitSize() == sizeof(double))
        {
            ASSERT_DOUBLE_EQ(5.6, testDataSet.getDouble(TagId(10, 10), 0));
            ASSERT_DOUBLE_EQ(3.6, testDataSet.getDouble(TagId(10, 10), 1));
            ASSERT_DOUBLE_EQ(2.6, testDataSet.getDouble(TagId(10, 10), 3));
            ASSERT_DOUBLE_EQ(10.0, testDataSet.getDouble(TagId(10, 10), 4));
            ASSERT_DOUBLE_EQ(20.0, testDataSet.getDouble(TagId(10, 10), 5));
            ASSERT_DOUBLE_EQ(123.7, testDataSet.getDouble(TagId(10, 10), 6));
            ASSERT_DOUBLE_EQ(124.9, testDataSet.getDouble(TagId(10, 10), 7));
            ASSERT_DOUBLE_EQ(-1.0, testDataSet.getDouble(TagId(10, 10), 9));
        }

        ASSERT_THROW(testDataSet.getDouble(TagId(10, 10), 20), MissingItemError);
        ASSERT_THROW(testDataSet.getDate(TagId(10, 10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getAge(TagId(10, 10), 0), DataHandlerConversionError);

        ASSERT_EQ(5, testDataSet.getInt32(TagId(10, 10), 0));
        ASSERT_EQ(3, testDataSet.getInt32(TagId(10, 10), 1));
        ASSERT_EQ(2, testDataSet.getInt32(TagId(10, 10), 3));
        ASSERT_EQ(10, testDataSet.getInt32(TagId(10, 10), 4));
        ASSERT_EQ(20, testDataSet.getInt32(TagId(10, 10), 5));
        ASSERT_EQ(123, testDataSet.getInt32(TagId(10, 10), 6));
        ASSERT_EQ(124, testDataSet.getInt32(TagId(10, 10), 7));
        ASSERT_THROW(testDataSet.getInt32(TagId(10, 10), 20), MissingItemError);

        ASSERT_EQ(5u, testDataSet.getUint32(TagId(10, 10), 0));
        ASSERT_EQ(3u, testDataSet.getUint32(TagId(10, 10), 1));
        ASSERT_EQ(2u, testDataSet.getUint32(TagId(10, 10), 3));
        ASSERT_EQ(10u, testDataSet.getUint32(TagId(10, 10), 4));
        ASSERT_EQ(20u, testDataSet.getUint32(TagId(10, 10), 5));
        ASSERT_EQ(123u, testDataSet.getUint32(TagId(10, 10), 6));
        ASSERT_EQ(124u, testDataSet.getUint32(TagId(10, 10), 7));
        ASSERT_THROW(testDataSet.getUint32(TagId(10, 10), 20), MissingItemError);

        if(readingHandler.getUnitSize() == sizeof(double))
        {
            ASSERT_DOUBLE_EQ(5.6, std::stod(testDataSet.getString(TagId(10, 10), 0).c_str()));
            ASSERT_DOUBLE_EQ(3.6, std::stod(testDataSet.getString(TagId(10, 10), 1).c_str()));
            ASSERT_DOUBLE_EQ(2.6, std::stod(testDataSet.getString(TagId(10, 10), 3).c_str()));
            ASSERT_DOUBLE_EQ(10.0, std::stod(testDataSet.getString(TagId(10, 10), 4).c_str()));
            ASSERT_DOUBLE_EQ(20.0, std::stod(testDataSet.getString(TagId(10, 10), 5).c_str()));
            ASSERT_DOUBLE_EQ(123.7, std::stod(testDataSet.getString(TagId(10, 10), 6).c_str()));
            ASSERT_DOUBLE_EQ(124.9, std::stod(testDataSet.getString(TagId(10, 10), 7).c_str()));

            ASSERT_DOUBLE_EQ(5.6, std::stod(testDataSet.getUnicodeString(TagId(10, 10), 0).c_str()));
            ASSERT_DOUBLE_EQ(3.6, std::stod(testDataSet.getUnicodeString(TagId(10, 10), 1).c_str()));
            ASSERT_DOUBLE_EQ(2.6, std::stod(testDataSet.getUnicodeString(TagId(10, 10), 3).c_str()));
            ASSERT_DOUBLE_EQ(10.0, std::stod(testDataSet.getUnicodeString(TagId(10, 10), 4).c_str()));
            ASSERT_DOUBLE_EQ(20.0, std::stod(testDataSet.getUnicodeString(TagId(10, 10), 5).c_str()));
            ASSERT_DOUBLE_EQ(123.7, std::stod(testDataSet.getUnicodeString(TagId(10, 10), 6).c_str()));
            ASSERT_DOUBLE_EQ(124.9, std::stod(testDataSet.getUnicodeString(TagId(10, 10), 7).c_str()));
        }
        else
        {
            ASSERT_FLOAT_EQ(5.6f, std::stof(testDataSet.getString(TagId(10, 10), 0).c_str()));
            ASSERT_FLOAT_EQ(3.6f, std::stof(testDataSet.getString(TagId(10, 10), 1).c_str()));
            ASSERT_FLOAT_EQ(2.6f, std::stof(testDataSet.getString(TagId(10, 10), 3).c_str()));
            ASSERT_FLOAT_EQ(10.0f, std::stof(testDataSet.getString(TagId(10, 10), 4).c_str()));
            ASSERT_FLOAT_EQ(20.0f, std::stof(testDataSet.getString(TagId(10, 10), 5).c_str()));
            ASSERT_FLOAT_EQ(123.7f, std::stof(testDataSet.getString(TagId(10, 10), 6).c_str()));
            ASSERT_FLOAT_EQ(124.9f, std::stof(testDataSet.getString(TagId(10, 10), 7).c_str()));

            ASSERT_FLOAT_EQ(5.6f, std::stof(testDataSet.getUnicodeString(TagId(10, 10), 0).c_str()));
            ASSERT_FLOAT_EQ(3.6f, std::stof(testDataSet.getUnicodeString(TagId(10, 10), 1).c_str()));
            ASSERT_FLOAT_EQ(2.6f, std::stof(testDataSet.getUnicodeString(TagId(10, 10), 3).c_str()));
            ASSERT_FLOAT_EQ(10.0f, std::stof(testDataSet.getUnicodeString(TagId(10, 10), 4).c_str()));
            ASSERT_FLOAT_EQ(20.0f, std::stof(testDataSet.getUnicodeString(TagId(10, 10), 5).c_str()));
            ASSERT_FLOAT_EQ(123.7f, std::stof(testDataSet.getUnicodeString(TagId(10, 10), 6).c_str()));
            ASSERT_FLOAT_EQ(124.9f, std::stof(testDataSet.getUnicodeString(TagId(10, 10), 7).c_str()));

        }
        ASSERT_THROW(testDataSet.getString(TagId(10, 10), 20), MissingItemError);
        ASSERT_THROW(testDataSet.getString(TagId(10, 10), 20), MissingItemError);
    }
}


TEST(numericHandlerTest, testInteger)
{
    for(size_t scanVR(0); scanVR != sizeof(integerTags) / sizeof(tagVR_t); ++scanVR)
    {
        MutableDataSet testDataSet;

        {
            WritingDataHandlerNumeric handler = testDataSet.getWritingDataHandlerNumeric(TagId(10, 10), 0, integerTags[scanVR]);
            handler.setDouble(0, 5.6);
            handler.setDouble(1, 3.6);
            handler.setDouble(3, 2.6);
            handler.setInt32(4, 10);
            handler.setUint32(5, 20);
            handler.setString(6, "123.7");
            handler.setUnicodeString(7, L"124.9");
            ASSERT_THROW(handler.setDate(8, Date(2000, 1, 1, 0, 0, 0, 0, 0, 0)), DataHandlerConversionError);
            ASSERT_THROW(handler.setAge(8, Age(3, ageUnit_t::days)), DataHandlerConversionError);
            ASSERT_THROW(handler.setString(8, "test"), DataHandlerConversionError);

            ASSERT_EQ(integerTags[scanVR], handler.getDataType());

            ASSERT_EQ(integerTags[scanVR] == tagVR_t::OL ||
                      integerTags[scanVR] == tagVR_t::SB ||
                      integerTags[scanVR] == tagVR_t::SL ||
                      integerTags[scanVR] == tagVR_t::SS ||
                      integerTags[scanVR] == tagVR_t::SV,
                      handler.isSigned());

            ASSERT_FALSE(handler.isFloat());
        }

        ReadingDataHandlerNumeric readingHandler = testDataSet.getReadingDataHandlerNumeric(TagId(10, 10), 0);
        ASSERT_FALSE(readingHandler.isFloat());

        ASSERT_DOUBLE_EQ(5.0, testDataSet.getDouble(TagId(10, 10), 0));
        ASSERT_DOUBLE_EQ(3.0, testDataSet.getDouble(TagId(10, 10), 1));
        ASSERT_DOUBLE_EQ(2.0, testDataSet.getDouble(TagId(10, 10), 3));
        ASSERT_DOUBLE_EQ(10.0, testDataSet.getDouble(TagId(10, 10), 4));
        ASSERT_DOUBLE_EQ(20.0, testDataSet.getDouble(TagId(10, 10), 5));
        ASSERT_DOUBLE_EQ(123.0, testDataSet.getDouble(TagId(10, 10), 6));
        ASSERT_DOUBLE_EQ(124.0, testDataSet.getDouble(TagId(10, 10), 7));
        ASSERT_THROW(testDataSet.getDouble(TagId(10, 10), 8), MissingItemError);

        ASSERT_THROW(testDataSet.getDate(TagId(10, 10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getAge(TagId(10, 10), 0), DataHandlerConversionError);

        ASSERT_EQ(5, testDataSet.getInt32(TagId(10, 10), 0));
        ASSERT_EQ(3, testDataSet.getInt32(TagId(10, 10), 1));
        ASSERT_EQ(2, testDataSet.getInt32(TagId(10, 10), 3));
        ASSERT_EQ(10, testDataSet.getInt32(TagId(10, 10), 4));
        ASSERT_EQ(20, testDataSet.getInt32(TagId(10, 10), 5));
        ASSERT_EQ(123, testDataSet.getInt32(TagId(10, 10), 6));
        ASSERT_EQ(124, testDataSet.getInt32(TagId(10, 10), 7));
        ASSERT_THROW(testDataSet.getInt32(TagId(10, 10), 8), MissingItemError);

        ASSERT_EQ(5u, testDataSet.getUint32(TagId(10, 10), 0));
        ASSERT_EQ(3u, testDataSet.getUint32(TagId(10, 10), 1));
        ASSERT_EQ(2u, testDataSet.getUint32(TagId(10, 10), 3));
        ASSERT_EQ(10u, testDataSet.getUint32(TagId(10, 10), 4));
        ASSERT_EQ(20u, testDataSet.getUint32(TagId(10, 10), 5));
        ASSERT_EQ(123u, testDataSet.getUint32(TagId(10, 10), 6));
        ASSERT_EQ(124u, testDataSet.getUint32(TagId(10, 10), 7));
        ASSERT_THROW(testDataSet.getUint32(TagId(10, 10), 8), MissingItemError);

        ASSERT_EQ(5, std::stol(testDataSet.getString(TagId(10, 10), 0).c_str()));
        ASSERT_EQ(3, std::stol(testDataSet.getString(TagId(10, 10), 1).c_str()));
        ASSERT_EQ(2, std::stol(testDataSet.getString(TagId(10, 10), 3).c_str()));
        ASSERT_EQ(10, std::stol(testDataSet.getString(TagId(10, 10), 4).c_str()));
        ASSERT_EQ(20, std::stol(testDataSet.getString(TagId(10, 10), 5).c_str()));
        ASSERT_EQ(123, std::stol(testDataSet.getString(TagId(10, 10), 6).c_str()));
        ASSERT_EQ(124, std::stol(testDataSet.getString(TagId(10, 10), 7).c_str()));
        ASSERT_THROW(testDataSet.getString(TagId(10, 10), 8), MissingItemError);

        ASSERT_EQ(5, std::stol(testDataSet.getUnicodeString(TagId(10, 10), 0).c_str()));
        ASSERT_EQ(3, std::stol(testDataSet.getUnicodeString(TagId(10, 10), 1).c_str()));
        ASSERT_EQ(2, std::stol(testDataSet.getUnicodeString(TagId(10, 10), 3).c_str()));
        ASSERT_EQ(10, std::stol(testDataSet.getUnicodeString(TagId(10, 10), 4).c_str()));
        ASSERT_EQ(20, std::stol(testDataSet.getUnicodeString(TagId(10, 10), 5).c_str()));
        ASSERT_EQ(123, std::stol(testDataSet.getUnicodeString(TagId(10, 10), 6).c_str()));
        ASSERT_EQ(124, std::stol(testDataSet.getUnicodeString(TagId(10, 10), 7).c_str()));
        ASSERT_THROW(testDataSet.getString(TagId(10, 10), 8), MissingItemError);

        testDataSet.setUint32(TagId(tagId_t::DimensionIndexPointer_0020_9165), (std::uint32_t)tagId_t::PatientName_0010_0010);
        ASSERT_EQ(tagId_t::PatientName_0010_0010, (tagId_t)testDataSet.getUint32(TagId(tagId_t::DimensionIndexPointer_0020_9165), 0));
    }
}


TEST(numericHandlerTest, testCopyFrom)
{
    for(size_t destVR(0); destVR != sizeof(allTags) / sizeof(tagVR_t); ++destVR)
    {

        for(size_t sourceVR(0); sourceVR != sizeof(allTags) / sizeof(tagVR_t); ++sourceVR)
        {
            if(
                    (allTags[destVR] == tagVR_t::AT && allTags[sourceVR] != tagVR_t::AT) ||
                    (allTags[destVR] != tagVR_t::AT && allTags[sourceVR] == tagVR_t::AT)
                    )
            {
                continue;
            }

            MutableDataSet testDataSet;

            {
                WritingDataHandlerNumeric handler = testDataSet.getWritingDataHandlerNumeric(TagId(10, 11), 0, allTags[sourceVR]);
                for(std::uint32_t fillData(0); fillData != 10; ++fillData)
                {
                    handler.setUint32(fillData, fillData);
                }
            }

            {
                WritingDataHandlerNumeric handler = testDataSet.getWritingDataHandlerNumeric(TagId(10, 10), 0, allTags[destVR]);
                ReadingDataHandlerNumeric source = testDataSet.getReadingDataHandlerNumeric(TagId(10, 11), 0);

                handler.copyFrom(source);
            }

            ReadingDataHandlerNumeric source = testDataSet.getReadingDataHandlerNumeric(TagId(10, 11), 0);
            ReadingDataHandlerNumeric dest = testDataSet.getReadingDataHandlerNumeric(TagId(10, 10), 0);

            ASSERT_EQ(10u, dest.getSize());
            ASSERT_EQ(10u, source.getSize());

            for(size_t checkData(0); checkData != 10; ++checkData)
            {
                ASSERT_EQ(checkData, dest.getUint32(checkData));
                ASSERT_EQ(checkData, source.getUint32(checkData));
            }

        }

    }
}


TEST(numericHandlerTest, testCopyTo)
{
    for(size_t destVR(0); destVR != sizeof(allTags) / sizeof(tagVR_t); ++destVR)
    {

        for(size_t sourceVR(0); sourceVR != sizeof(allTags) / sizeof(tagVR_t); ++sourceVR)
        {
            if(
                    (allTags[destVR] == tagVR_t::AT && allTags[sourceVR] != tagVR_t::AT) ||
                    (allTags[destVR] != tagVR_t::AT && allTags[sourceVR] == tagVR_t::AT)
                    )
            {
                continue;
            }

            MutableDataSet testDataSet;

            {
                WritingDataHandlerNumeric handler = testDataSet.getWritingDataHandlerNumeric(TagId(10, 11), 0, allTags[sourceVR]);
                for(std::uint32_t fillData(0); fillData != 10; ++fillData)
                {
                    handler.setUint32(fillData, fillData);
                }
            }

            {
                WritingDataHandlerNumeric handler = testDataSet.getWritingDataHandlerNumeric(TagId(10, 10), 0, allTags[destVR]);
                handler.setSize(12);
                ReadingDataHandlerNumeric source = testDataSet.getReadingDataHandlerNumeric(TagId(10, 11), 0);

                source.copyTo(handler);
            }

            ReadingDataHandlerNumeric source = testDataSet.getReadingDataHandlerNumeric(TagId(10, 11), 0);
            ReadingDataHandlerNumeric dest = testDataSet.getReadingDataHandlerNumeric(TagId(10, 10), 0);

            ASSERT_EQ(12u, dest.getSize());
            ASSERT_EQ(10u, source.getSize());

            for(size_t checkData(0); checkData != 10; ++checkData)
            {
                ASSERT_EQ(checkData, dest.getUint32(checkData));
                ASSERT_EQ(checkData, source.getUint32(checkData));
            }

        }

    }
}


TEST(numericHandlerTest, testLimits)
{
    {
        // OB (uint8)
        MutableDataSet testDataSet;
        testDataSet.setUint8(TagId(0x10, 0x10), std::numeric_limits<std::uint8_t>::max(), tagVR_t::OB);
        ASSERT_EQ(std::numeric_limits<std::uint8_t>::max(), testDataSet.getUint8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(std::numeric_limits<std::uint8_t>::max(), testDataSet.getUint16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(std::numeric_limits<std::uint8_t>::max(), testDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(static_cast<float>(std::numeric_limits<std::uint8_t>::max()), testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<std::uint8_t>::max()), testDataSet.getDouble(TagId(0x10, 0x10), 0));
        ASSERT_THROW(testDataSet.getInt8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::uint8_t>::max(), testDataSet.getInt16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(std::numeric_limits<std::uint8_t>::max(), testDataSet.getInt32(TagId(0x10, 0x10), 0));
        ASSERT_THROW(testDataSet.setUint16(TagId(0x10, 0x10), std::numeric_limits<std::uint8_t>::max() + 1, tagVR_t::OB), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setUint32(TagId(0x10, 0x10), std::numeric_limits<std::uint8_t>::max() + 1, tagVR_t::OB), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<std::uint8_t>::max()) + 1.0, tagVR_t::OB), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<std::uint8_t>::lowest()) - 1.0, tagVR_t::OB), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), static_cast<float>(std::numeric_limits<std::uint8_t>::max()) + 1.0f, tagVR_t::OB), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), static_cast<float>(std::numeric_limits<std::uint8_t>::lowest()) - 1.0f, tagVR_t::OB), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setString(TagId(0x10, 0x10), "256", tagVR_t::OB), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setString(TagId(0x10, 0x10), "-1", tagVR_t::OB), DataHandlerConversionError);

        testDataSet.setUint8(TagId(0x10, 0x10), 1, tagVR_t::OB);
        ASSERT_EQ(1u, testDataSet.getUint8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt32(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(1.0f, testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(1.0, testDataSet.getDouble(TagId(0x10, 0x10), 0));
    }

    {
        // OW (uint16)
        MutableDataSet testDataSet;
        testDataSet.setUint16(TagId(0x10, 0x10), std::numeric_limits<std::uint16_t>::max(), tagVR_t::OW);
        ASSERT_THROW(testDataSet.getUint8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::uint16_t>::max(), testDataSet.getUint16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(std::numeric_limits<std::uint16_t>::max(), testDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(static_cast<float>(std::numeric_limits<std::uint16_t>::max()), testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<std::uint16_t>::max()), testDataSet.getDouble(TagId(0x10, 0x10), 0));
        ASSERT_THROW(testDataSet.getInt8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::uint16_t>::max(), testDataSet.getInt32(TagId(0x10, 0x10), 0));
        ASSERT_THROW(testDataSet.setUint32(TagId(0x10, 0x10), std::numeric_limits<std::uint16_t>::max() + 1, tagVR_t::OW), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<std::uint16_t>::max()) + 1.0, tagVR_t::US), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<std::uint16_t>::lowest()) - 1.0, tagVR_t::US), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), static_cast<float>(std::numeric_limits<std::uint16_t>::max()) + 1.0f, tagVR_t::US), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), static_cast<float>(std::numeric_limits<std::uint16_t>::lowest()) - 1.0f, tagVR_t::US), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setString(TagId(0x10, 0x10), "65536", tagVR_t::OB), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setString(TagId(0x10, 0x10), "-1", tagVR_t::OB), DataHandlerConversionError);

        testDataSet.setUint16(TagId(0x10, 0x10), 1, tagVR_t::OW);
        ASSERT_EQ(1u, testDataSet.getUint8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt32(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(1.0f, testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(1.0, testDataSet.getDouble(TagId(0x10, 0x10), 0));
    }

    {
        // SS (int16)
        MutableDataSet testDataSet;
        testDataSet.setInt16(TagId(0x10, 0x10), std::numeric_limits<std::int16_t>::max(), tagVR_t::SS);
        ASSERT_THROW(testDataSet.getUint8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::int16_t>::max(), testDataSet.getUint16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(static_cast<std::uint16_t>(std::numeric_limits<std::int16_t>::max()), testDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(static_cast<float>(std::numeric_limits<std::int16_t>::max()), testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<std::int16_t>::max()), testDataSet.getDouble(TagId(0x10, 0x10), 0));
        ASSERT_THROW(testDataSet.getInt8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::int16_t>::max(), testDataSet.getInt16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(std::numeric_limits<std::int16_t>::max(), testDataSet.getInt32(TagId(0x10, 0x10), 0));
        ASSERT_THROW(testDataSet.setUint32(TagId(0x10, 0x10), std::numeric_limits<std::int16_t>::max() + 1, tagVR_t::SS), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<std::int16_t>::max()) + 1.0, tagVR_t::SS), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<std::int16_t>::lowest()) - 1.0, tagVR_t::SS), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), static_cast<float>(std::numeric_limits<std::int16_t>::max()) + 1.0f, tagVR_t::SS), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), static_cast<float>(std::numeric_limits<std::int16_t>::lowest()) - 1.0f, tagVR_t::SS), DataHandlerConversionError);

        testDataSet.setUint16(TagId(0x10, 0x10), 1, tagVR_t::SS);
        ASSERT_EQ(1u, testDataSet.getUint8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt32(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(1.0f, testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(1.0, testDataSet.getDouble(TagId(0x10, 0x10), 0));
    }

    {
        // UL (uint32)
        MutableDataSet testDataSet;
        testDataSet.setUint32(TagId(0x10, 0x10), std::numeric_limits<std::uint32_t>::max(), tagVR_t::UL);
        ASSERT_THROW(testDataSet.getUint8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::uint32_t>::max(), testDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(static_cast<float>(std::numeric_limits<std::uint32_t>::max()), testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<std::uint32_t>::max()), testDataSet.getDouble(TagId(0x10, 0x10), 0));
        ASSERT_THROW(testDataSet.getInt8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt32(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<std::uint32_t>::max()) + 1.0, tagVR_t::UL), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<std::uint32_t>::lowest()) - 1.0, tagVR_t::UL), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), static_cast<float>(std::numeric_limits<std::uint32_t>::max()) + 1000.0f, tagVR_t::UL), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), static_cast<float>(std::numeric_limits<std::uint32_t>::lowest()) - 1000.0f, tagVR_t::UL), DataHandlerConversionError);

        testDataSet.setUint32(TagId(0x10, 0x10), 1, tagVR_t::UL);
        ASSERT_EQ(1u, testDataSet.getUint8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt32(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(1.0f, testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(1.0, testDataSet.getDouble(TagId(0x10, 0x10), 0));
    }

    {
        // UV (uint64)
        MutableDataSet testDataSet;
        testDataSet.setUint64(TagId(0x10, 0x10), std::numeric_limits<std::uint64_t>::max(), tagVR_t::UV);
        ASSERT_THROW(testDataSet.getUint8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::uint64_t>::max(), testDataSet.getUint64(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(static_cast<float>(std::numeric_limits<std::uint64_t>::max()), testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<std::uint64_t>::max()), testDataSet.getDouble(TagId(0x10, 0x10), 0));
        ASSERT_THROW(testDataSet.getInt8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt32(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<std::uint64_t>::max()) * 10.0, tagVR_t::UL), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<std::uint64_t>::lowest()) - 1.0, tagVR_t::UL), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), static_cast<float>(std::numeric_limits<std::uint64_t>::max()) * 10.0f, tagVR_t::UL), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), static_cast<float>(std::numeric_limits<std::uint64_t>::lowest()) - 1000.0f, tagVR_t::UL), DataHandlerConversionError);

        testDataSet.setUint64(TagId(0x10, 0x10), 1, tagVR_t::UL);
        ASSERT_EQ(1u, testDataSet.getUint8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint64(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt32(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt64(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(1.0f, testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(1.0, testDataSet.getDouble(TagId(0x10, 0x10), 0));
    }

    {
        // SL (int32)
        MutableDataSet testDataSet;
        testDataSet.setInt32(TagId(0x10, 0x10), std::numeric_limits<std::int32_t>::max(), tagVR_t::SL);
        ASSERT_THROW(testDataSet.getUint8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_EQ(static_cast<std::uint32_t>(std::numeric_limits<std::int32_t>::max()), testDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(static_cast<float>(std::numeric_limits<std::int32_t>::max()), testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<std::int32_t>::max()), testDataSet.getDouble(TagId(0x10, 0x10), 0));
        ASSERT_THROW(testDataSet.getInt8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::int32_t>::max(), testDataSet.getInt32(TagId(0x10, 0x10), 0));
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<std::int32_t>::max()) + 1.0, tagVR_t::SL), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<std::int32_t>::lowest()) - 1.0, tagVR_t::SL), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), static_cast<float>(std::numeric_limits<std::int32_t>::max()) + 1000.0f, tagVR_t::SL), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), static_cast<float>(std::numeric_limits<std::int32_t>::lowest()) - 1000.0f, tagVR_t::SL), DataHandlerConversionError);

        testDataSet.setUint32(TagId(0x10, 0x10), 1, tagVR_t::SL);
        ASSERT_EQ(1u, testDataSet.getUint8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt32(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(1.0f, testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(1.0, testDataSet.getDouble(TagId(0x10, 0x10), 0));
    }

    {
        // SV (int64)
        MutableDataSet testDataSet;
        testDataSet.setInt64(TagId(0x10, 0x10), std::numeric_limits<std::int64_t>::max(), tagVR_t::SV);
        ASSERT_THROW(testDataSet.getUint8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint32(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_EQ(static_cast<std::uint64_t>(std::numeric_limits<std::int64_t>::max()), testDataSet.getUint64(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(static_cast<float>(std::numeric_limits<std::int64_t>::max()), testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<std::int64_t>::max()), testDataSet.getDouble(TagId(0x10, 0x10), 0));
        ASSERT_THROW(testDataSet.getInt8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt32(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_EQ(std::numeric_limits<std::int64_t>::max(), testDataSet.getInt64(TagId(0x10, 0x10), 0));
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<std::int64_t>::max()) * 1000.0, tagVR_t::SL), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<std::int64_t>::lowest()) * 1000.0, tagVR_t::SL), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), static_cast<float>(std::numeric_limits<std::int64_t>::max()) * 1000.0f, tagVR_t::SL), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), static_cast<float>(std::numeric_limits<std::int64_t>::lowest()) * 1000.0f, tagVR_t::SL), DataHandlerConversionError);

        testDataSet.setUint64(TagId(0x10, 0x10), 1, tagVR_t::SL);
        ASSERT_EQ(1u, testDataSet.getUint8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint64(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt32(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt64(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(1.0f, testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(1.0, testDataSet.getDouble(TagId(0x10, 0x10), 0));
    }

    {
        // FL (float)
        MutableDataSet testDataSet;
        testDataSet.setFloat(TagId(0x10, 0x10), std::numeric_limits<float>::max(), tagVR_t::FL);
        ASSERT_THROW(testDataSet.getUint8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint32(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_FLOAT_EQ(static_cast<float>(std::numeric_limits<float>::max()), testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<float>::max()), testDataSet.getDouble(TagId(0x10, 0x10), 0));
        ASSERT_THROW(testDataSet.getInt8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt32(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<double>::max()) + 1.0, tagVR_t::FL), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), static_cast<double>(std::numeric_limits<double>::lowest()) - 1.0, tagVR_t::FL), DataHandlerConversionError);

        testDataSet.setUint8(TagId(0x10, 0x10), 1, tagVR_t::FL);
        ASSERT_EQ(1u, testDataSet.getUint8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt32(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(1.0f, testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(1.0, testDataSet.getDouble(TagId(0x10, 0x10), 0));
    }

    {
        // DL (double)
        MutableDataSet testDataSet;
        testDataSet.setDouble(TagId(0x10, 0x10), std::numeric_limits<double>::max(), tagVR_t::FD);
        ASSERT_THROW(testDataSet.getUint8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint32(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getFloat(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_DOUBLE_EQ(static_cast<double>(std::numeric_limits<double>::max()), testDataSet.getDouble(TagId(0x10, 0x10), 0));
        ASSERT_THROW(testDataSet.getInt8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt32(TagId(0x10, 0x10), 0), DataHandlerConversionError);

        testDataSet.setUint8(TagId(0x10, 0x10), 1, tagVR_t::FL);
        ASSERT_EQ(1u, testDataSet.getUint8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1u, testDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt8(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt16(TagId(0x10, 0x10), 0));
        ASSERT_EQ(1, testDataSet.getInt32(TagId(0x10, 0x10), 0));
        ASSERT_FLOAT_EQ(1.0f, testDataSet.getFloat(TagId(0x10, 0x10), 0));
        ASSERT_DOUBLE_EQ(1.0, testDataSet.getDouble(TagId(0x10, 0x10), 0));
    }
}

TEST(numericHandlerTest, testAT)
{
    {
        // AT little endian size 1
        MutableDataSet testDataSet(uidExplicitVRLittleEndian_1_2_840_10008_1_2_1);
        ASSERT_THROW(testDataSet.setInt32(TagId(0x10, 0x10), 1, tagVR_t::AT), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setUint16(TagId(0x10, 0x10), 1u, tagVR_t::AT), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setInt16(TagId(0x10, 0x10), 1, tagVR_t::AT), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setUint8(TagId(0x10, 0x10), 1u, tagVR_t::AT), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setInt8(TagId(0x10, 0x10), 1, tagVR_t::AT), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setDouble(TagId(0x10, 0x10), 1.0, tagVR_t::AT), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.setFloat(TagId(0x10, 0x10), 1.0f, tagVR_t::AT), DataHandlerConversionError);
        testDataSet.setUint32(TagId(0x10, 0x10), 0x001800ffu, tagVR_t::AT);

        MutableMemory dataSetMemory;
        {
            MemoryStreamOutput output(dataSetMemory);
            StreamWriter writer(output);
            CodecFactory::save(testDataSet, writer, codecType_t::dicom);
        }
        MemoryStreamInput input(dataSetMemory);
        StreamReader reader(input);
        DataSet loadedDataSet = CodecFactory::load(reader);

        ASSERT_EQ(0x001800ffu, loadedDataSet.getUint32(TagId(0x10, 0x10), 0));

        ASSERT_THROW(testDataSet.getInt32(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt16(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getUint8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getInt8(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getDouble(TagId(0x10, 0x10), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getFloat(TagId(0x10, 0x10), 0), DataHandlerConversionError);

        size_t memorySize;
        std::string memoryString(dataSetMemory.data(&memorySize), dataSetMemory.size());
        ASSERT_TRUE(memoryString.find(std::string("\x18\x00\xff\x00", 4u)) != std::string::npos);

    }

    {
        // AT little endian size 2
        MutableDataSet testDataSet(uidExplicitVRLittleEndian_1_2_840_10008_1_2_1);
        {
            WritingDataHandlerNumeric writeAT(testDataSet.getWritingDataHandlerNumeric(TagId(0x10, 0x10), 0, tagVR_t::AT));
            writeAT.setUint32(0, 0x001800ffu);
            writeAT.setUint32(1, 0x001900feu);
        }

        MutableMemory dataSetMemory;
        {
            MemoryStreamOutput output(dataSetMemory);
            StreamWriter writer(output);
            CodecFactory::save(testDataSet, writer, codecType_t::dicom);
        }
        MemoryStreamInput input(dataSetMemory);
        StreamReader reader(input);
        DataSet loadedDataSet = CodecFactory::load(reader);

        ReadingDataHandlerNumeric readAT = loadedDataSet.getReadingDataHandlerNumeric(TagId(0x10, 0x10), 0);
        ASSERT_EQ(2u, readAT.getSize());
        ASSERT_EQ(4u, readAT.getUnitSize());

        ASSERT_EQ(0x001800ffu, loadedDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_EQ(0x001900feu, loadedDataSet.getUint32(TagId(0x10, 0x10), 1));

        size_t memorySize;
        std::string memoryString(dataSetMemory.data(&memorySize), dataSetMemory.size());
        ASSERT_TRUE(memoryString.find(std::string("\x18\x00\xff\x00\x19\x00\xfe\x00", 8u)) != std::string::npos);
    }

    {
        // AT big endian
        MutableDataSet testDataSet(uidExplicitVRBigEndian_1_2_840_10008_1_2_2);
        testDataSet.setUint32(TagId(0x10, 0x10), 0x001800ffu, tagVR_t::AT);

        MutableMemory dataSetMemory;
        {
            MemoryStreamOutput output(dataSetMemory);
            StreamWriter writer(output);
            CodecFactory::save(testDataSet, writer, codecType_t::dicom);
        }
        MemoryStreamInput input(dataSetMemory);
        StreamReader reader(input);
        DataSet loadedDataSet = CodecFactory::load(reader);

        ASSERT_EQ(0x001800ffu, loadedDataSet.getUint32(TagId(0x10, 0x10), 0));
        ReadingDataHandlerNumeric readAT = loadedDataSet.getReadingDataHandlerNumeric(TagId(0x10, 0x10), 0);
        ASSERT_EQ(1u, readAT.getSize());
        ASSERT_EQ(4u, readAT.getUnitSize());

        size_t memorySize;
        std::string memoryString(dataSetMemory.data(&memorySize), dataSetMemory.size());
        ASSERT_TRUE(memoryString.find(std::string("\x00\x18\x00\xff", 4u)) != std::string::npos);
    }

    {
        // AT big endian size 2
        MutableDataSet testDataSet(uidExplicitVRBigEndian_1_2_840_10008_1_2_2);
        {
            WritingDataHandlerNumeric writeAT(testDataSet.getWritingDataHandlerNumeric(TagId(0x10, 0x10), 0, tagVR_t::AT));
            writeAT.setUint32(0, 0x001800ffu);
            writeAT.setUint32(1, 0x001900feu);
        }

        MutableMemory dataSetMemory;
        {
            MemoryStreamOutput output(dataSetMemory);
            StreamWriter writer(output);
            CodecFactory::save(testDataSet, writer, codecType_t::dicom);
        }
        MemoryStreamInput input(dataSetMemory);
        StreamReader reader(input);
        DataSet loadedDataSet = CodecFactory::load(reader);

        ASSERT_EQ(0x001800ffu, loadedDataSet.getUint32(TagId(0x10, 0x10), 0));
        ASSERT_EQ(0x001900feu, loadedDataSet.getUint32(TagId(0x10, 0x10), 1));

        ReadingDataHandlerNumeric readAT = loadedDataSet.getReadingDataHandlerNumeric(TagId(0x10, 0x10), 0);
        ASSERT_EQ(2u, readAT.getSize());
        ASSERT_EQ(4u, readAT.getUnitSize());

        size_t memorySize;
        std::string memoryString(dataSetMemory.data(&memorySize), dataSetMemory.size());
        ASSERT_TRUE(memoryString.find(std::string("\x00\x18\x00\xff\x00\x19\x00\xfe", 8u)) != std::string::npos);
    }

}



} // namespace tests

} // namespace imebra

