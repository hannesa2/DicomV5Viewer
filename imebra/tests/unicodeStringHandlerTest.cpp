#include <imebra/imebra.h>
#include <gtest/gtest.h>
#include <locale>
#include <codecvt>

namespace imebra
{

namespace tests
{

TEST(unicodeStringHandlerTest, unicodeTest)
{
    // Try a cyrillic/arabic patient name
    std::wstring patientName0 = L"??\x0628\x062a\x062b\x062f^\0x400\0x410\0x420";
    std::wstring patientName1 = L"\0x420\x062a\x062b^\0x400\0x410\x0628\x062a";

    MutableMemory streamMemory;
    {
        charsetsList_t charsets;
        charsets.push_back("ISO_IR 6");
        charsets.push_back("ISO 2022 IR 127");

        MutableDataSet testDataSet("1.2.840.10008.1.2.1", charsets);

        {
            WritingDataHandler handler = testDataSet.getWritingDataHandler(TagId(0x10, 0x10), 0);

            handler.setUnicodeString(0, patientName0);
            handler.setUnicodeString(1, patientName1);
        }

        MemoryStreamOutput writeStream(streamMemory);
        StreamWriter writer(writeStream);
        CodecFactory::save(testDataSet, writer, codecType_t::dicom);
    }

    {
        MemoryStreamInput readStream(streamMemory);
        StreamReader reader(readStream);
        DataSet testDataSet = CodecFactory::load(reader);

        EXPECT_EQ(patientName0, testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 0));
        EXPECT_EQ(patientName1, testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 1));
        EXPECT_THROW(testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 2), MissingItemError);
        EXPECT_THROW(testDataSet.getString(TagId(0x0010, 0x0010), 2), MissingItemError);
        EXPECT_THROW(testDataSet.getInt32(TagId(0x0010, 0x0010), 2), MissingItemError);
        EXPECT_THROW(testDataSet.getUint32(TagId(0x0010, 0x0010), 2), MissingItemError);
        EXPECT_THROW(testDataSet.getDouble(TagId(0x0010, 0x0010), 2), MissingItemError);
    }
}


TEST(unicodeStringHandlerTest, japaneseTest)
{
    try
    {
        std::string patientName = "\xd4\xcf\xc0\xde\x5e\xc0\xdb\xb3\x3d\x1b\x24\x42\x3b\x33\x45\x44\x1b\x28\x4a\x5e\x1b\x24\x42\x42"
                                  "\x40\x4f\x3a\x1b\x28\x4a\x3d\x1b\x24\x42\x24\x64\x24\x5e\x24\x40\x1b\x28\x4a\x5e";

        MutableMemory streamMemory;
        {
            charsetsList_t charsets;
            charsets.push_back("ISO 2022 IR 13");
            charsets.push_back("ISO 2022 IR 87");

            MutableDataSet testDataSet("1.2.840.10008.1.2.1", charsets);

            {
                WritingDataHandlerNumeric handler = testDataSet.getWritingDataHandlerRaw(TagId(0x10, 0x10), 0);
                handler.assign(patientName.c_str(), patientName.size());
            }

            MemoryStreamOutput writeStream(streamMemory);
            StreamWriter writer(writeStream);
            CodecFactory::save(testDataSet, writer, codecType_t::dicom);
        }

        {
            MemoryStreamInput readStream(streamMemory);
            StreamReader reader(readStream);
            DataSet testDataSet = CodecFactory::load(reader);

            std::wstring unicodeString = testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 0);
            std::cout << std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>{}.to_bytes(unicodeString) << std::endl;
        }
    }
    catch (const CharsetConversionNoSupportedTableError& e)
    {
        std::cout << e.what() << std::endl;
    }
}


TEST(unicodeStringHandlerTest, iso2022Test)
{
    // Try a cyrillic /greek/latin patient name

    std::wstring patientName0 = L"???\x0430\x0402\x0403\x00c9^\x00d0\x0410\x00d5";
    std::wstring patientName1 = L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072";
    std::wstring patientName2 = L"??\x0628\x062a\x062b\x062f^\0x400\0x410\0x420\0x00c6\0x0104\0x00c6";

    MutableMemory streamMemory;
    {
        charsetsList_t charsets;
        charsets.push_back("ISO_IR 6");
        charsets.push_back("ISO 2022 IR 144");
        charsets.push_back("ISO 2022 IR 100");
        charsets.push_back("ISO 2022 IR 126");
        charsets.push_back("ISO 2022 IR 127");

        MutableDataSet testDataSet("1.2.840.10008.1.2.1", charsets);

        {
            WritingDataHandler handler = testDataSet.getWritingDataHandler(TagId(0x10, 0x10), 0);

            handler.setUnicodeString(0, patientName0);
            handler.setUnicodeString(1, patientName1);
            handler.setUnicodeString(2, patientName2);
        }

        MemoryStreamOutput writeStream(streamMemory);
        StreamWriter writer(writeStream);
        CodecFactory::save(testDataSet, writer, codecType_t::dicom);
    }

    {
        MemoryStreamInput readStream(streamMemory);
        StreamReader reader(readStream);
        DataSet testDataSet = CodecFactory::load(reader);

        EXPECT_EQ(patientName0, testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 0));
        EXPECT_EQ(patientName1, testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 1));
        EXPECT_EQ(patientName2, testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 2));
    }
}

#if !defined(_WIN32) && !defined(__CYGWIN__)
TEST(unicodeStringHandlerTest, supplementaryUnicodeChars)
{
    // Try supplementary chars
    std::wstring patientName0 = L"\x2070e\x20731\x20779\x20c53^\x00d0\x0410\x00d5";
    std::wstring patientName1 = L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072";

    MutableMemory streamMemory;
    {
        charsetsList_t charsets;
        charsets.push_back("ISO_IR 192");
        MutableDataSet testDataSet("1.2.840.10008.1.2.1", charsets);

        {
            WritingDataHandler handler = testDataSet.getWritingDataHandler(TagId(0x10, 0x10), 0);

            handler.setUnicodeString(0, patientName0);
            handler.setUnicodeString(1, patientName1);
        }

        MemoryStreamOutput writeStream(streamMemory);
        StreamWriter writer(writeStream);
        CodecFactory::save(testDataSet, writer, codecType_t::dicom);
    }

    {
        MemoryStreamInput readStream(streamMemory);
        StreamReader reader(readStream);
        DataSet testDataSet = CodecFactory::load(reader);

        EXPECT_EQ(patientName0, testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 0));
        EXPECT_EQ(patientName1, testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 1));
    }
}
#endif

TEST(unicodeStringHandlerTest, unicodeNumericConversion)
{

    MutableMemory streamMemory;
    {
        charsetsList_t charsets;
        charsets.push_back("ISO_IR 6");
        MutableDataSet testDataSet("1.2.840.10008.1.2.1", charsets);

        {
            WritingDataHandler handler = testDataSet.getWritingDataHandler(TagId(0x10, 0x10), 0);

            handler.setDouble(0, 1000);
            handler.setUint32(1, 2000);
            handler.setInt32(2, 3000);
        }

        MemoryStreamOutput writeStream(streamMemory);
        StreamWriter writer(writeStream);
        CodecFactory::save(testDataSet, writer, codecType_t::dicom);
    }

    {
        MemoryStreamInput readStream(streamMemory);
        StreamReader reader(readStream);
        DataSet testDataSet = CodecFactory::load(reader);

        ASSERT_DOUBLE_EQ(std::stod(L"1000"), std::stod(testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 0)));
        EXPECT_EQ(1000, testDataSet.getInt32(TagId(0x0010, 0x0010), 0));
        EXPECT_EQ(1000u, testDataSet.getUint32(TagId(0x0010, 0x0010), 0));
        ASSERT_DOUBLE_EQ(1000.0, testDataSet.getDouble(TagId(0x0010, 0x0010), 0));
        EXPECT_EQ(2000, testDataSet.getInt32(TagId(0x0010, 0x0010), 1));
        EXPECT_EQ(2000u, testDataSet.getUint32(TagId(0x0010, 0x0010), 1));
        ASSERT_DOUBLE_EQ(2000.0, testDataSet.getDouble(TagId(0x0010, 0x0010), 1));
        EXPECT_EQ(3000, testDataSet.getInt32(TagId(0x0010, 0x0010), 2));
        EXPECT_EQ(3000u, testDataSet.getUint32(TagId(0x0010, 0x0010), 2));
        ASSERT_DOUBLE_EQ(3000.0, testDataSet.getDouble(TagId(0x0010, 0x0010), 2));
        EXPECT_THROW(testDataSet.getDate(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
        EXPECT_THROW(testDataSet.getAge(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
    }
}


TEST(unicodeStringHandlerTest, PNTest)
{
    charsetsList_t charsets;
    charsets.push_back("ISO_IR 192");
    MutableDataSet testDataSet("1.2.840.10008.1.2.1", charsets);

    {
        UnicodePatientName patientName(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation", L"", L"");
        UnicodePatientName checkPatientName= testDataSet.getUnicodePatientName(TagId(tagId_t::PatientName_0010_0010), 0, patientName);
        ASSERT_EQ(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation", checkPatientName.getAlphabeticRepresentation());
        ASSERT_EQ(L"", checkPatientName.getIdeographicRepresentation());
        ASSERT_EQ(L"", checkPatientName.getPhoneticRepresentation());
    }

    {
        testDataSet.setUnicodeString(TagId(0x0010, 0x0010), L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072", tagVR_t::PN);
        ASSERT_EQ(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072", testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 0));
        ASSERT_THROW(testDataSet.getDate(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);
        ASSERT_THROW(testDataSet.getAge(TagId(0x0010, 0x0010), 0), DataHandlerConversionError);

        {
            WritingDataHandler pnHandler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0, tagVR_t::PN);
            pnHandler.setUnicodeString(0, L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^0=Patient^1=Patient^2");
            pnHandler.setUnicodeString(1, L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^3=Patient^4");
        }

        {
            ASSERT_EQ(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^0=Patient^1=Patient^2", testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 0));
            ASSERT_EQ(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^3=Patient^4", testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 1));

            UnicodePatientName patientName0 = testDataSet.getUnicodePatientName(TagId(0x0010, 0x0010), 0);
            ASSERT_EQ(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^0", patientName0.getAlphabeticRepresentation());
            ASSERT_EQ(L"Patient^1", patientName0.getIdeographicRepresentation());
            ASSERT_EQ(L"Patient^2", patientName0.getPhoneticRepresentation());
            UnicodePatientName patientName1 = testDataSet.getUnicodePatientName(TagId(0x0010, 0x0010), 1);
            ASSERT_EQ(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^3", patientName1.getAlphabeticRepresentation());
            ASSERT_EQ(L"Patient^4", patientName1.getIdeographicRepresentation());
            ASSERT_EQ(L"", patientName1.getPhoneticRepresentation());
        }

        {
            ReadingDataHandler patientDataHandler = testDataSet.getReadingDataHandler(TagId(0x0010, 0x0010), 0);
            UnicodePatientName patientName0 = patientDataHandler.getUnicodePatientName(0);
            ASSERT_EQ(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^0", patientName0.getAlphabeticRepresentation());
            ASSERT_EQ(L"Patient^1", patientName0.getIdeographicRepresentation());
            ASSERT_EQ(L"Patient^2", patientName0.getPhoneticRepresentation());
            UnicodePatientName patientName1 = patientDataHandler.getUnicodePatientName(1);
            ASSERT_EQ(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^3", patientName1.getAlphabeticRepresentation());
            ASSERT_EQ(L"Patient^4", patientName1.getIdeographicRepresentation());
            ASSERT_EQ(L"", patientName1.getPhoneticRepresentation());
        }

    }

    {
        UnicodePatientName writePatient(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation", L"", L"");
        testDataSet.setUnicodePatientName(TagId(0x0010, 0x0010), writePatient);

        UnicodePatientName checkPatient(testDataSet.getUnicodePatientName(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(writePatient.getAlphabeticRepresentation(), checkPatient.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient.getIdeographicRepresentation(), checkPatient.getIdeographicRepresentation());
        ASSERT_EQ(writePatient.getPhoneticRepresentation(), checkPatient.getPhoneticRepresentation());
        ASSERT_EQ(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation", testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 0));

        ReadingDataHandler handler = testDataSet.getReadingDataHandler(TagId(0x0010, 0x0010), 0);
        ASSERT_EQ(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation", handler.getUnicodeString(0));
    }

    {
        UnicodePatientName writePatient(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation", L"ideographic^representation", L"phonetic^representation");
        testDataSet.setUnicodePatientName(TagId(0x0010, 0x0010), writePatient);

        UnicodePatientName checkPatient(testDataSet.getUnicodePatientName(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(writePatient.getAlphabeticRepresentation(), checkPatient.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient.getIdeographicRepresentation(), checkPatient.getIdeographicRepresentation());
        ASSERT_EQ(writePatient.getPhoneticRepresentation(), checkPatient.getPhoneticRepresentation());
        ASSERT_EQ(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation=ideographic^representation=phonetic^representation", testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 0));
    }

    {
        UnicodePatientName writePatient(L"", L"ideographic^representation", L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation");
        testDataSet.setUnicodePatientName(TagId(0x0010, 0x0010), writePatient);

        UnicodePatientName checkPatient(testDataSet.getUnicodePatientName(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(writePatient.getAlphabeticRepresentation(), checkPatient.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient.getIdeographicRepresentation(), checkPatient.getIdeographicRepresentation());
        ASSERT_EQ(writePatient.getPhoneticRepresentation(), checkPatient.getPhoneticRepresentation());
        ASSERT_EQ(L"=ideographic^representation=\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation", testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 0));
    }

    {
        UnicodePatientName writePatient(L"", L"", L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation");
        testDataSet.setUnicodePatientName(TagId(0x0010, 0x0010), writePatient);

        UnicodePatientName checkPatient(testDataSet.getUnicodePatientName(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(writePatient.getAlphabeticRepresentation(), checkPatient.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient.getIdeographicRepresentation(), checkPatient.getIdeographicRepresentation());
        ASSERT_EQ(writePatient.getPhoneticRepresentation(), checkPatient.getPhoneticRepresentation());
        ASSERT_EQ(L"==\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation", testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 0));
    }

    {
        UnicodePatientName writePatient(L"", L"", L"");
        testDataSet.setUnicodePatientName(TagId(0x0010, 0x0010), writePatient);

        UnicodePatientName checkPatient(testDataSet.getUnicodePatientName(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(writePatient.getAlphabeticRepresentation(), checkPatient.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient.getIdeographicRepresentation(), checkPatient.getIdeographicRepresentation());
        ASSERT_EQ(writePatient.getPhoneticRepresentation(), checkPatient.getPhoneticRepresentation());
        ASSERT_EQ("", testDataSet.getString(TagId(0x0010, 0x0010), 0));
    }

    {
        UnicodePatientName writePatient(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation", L"", L"phonetic^representation");
        testDataSet.setUnicodePatientName(TagId(0x0010, 0x0010), writePatient);

        UnicodePatientName checkPatient(testDataSet.getUnicodePatientName(TagId(0x0010, 0x0010), 0));
        ASSERT_EQ(writePatient.getAlphabeticRepresentation(), checkPatient.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient.getIdeographicRepresentation(), checkPatient.getIdeographicRepresentation());
        ASSERT_EQ(writePatient.getPhoneticRepresentation(), checkPatient.getPhoneticRepresentation());
        ASSERT_EQ(L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation==phonetic^representation", testDataSet.getUnicodeString(TagId(0x0010, 0x0010), 0));
    }

    {
        UnicodePatientName writePatient0(L"", L"", L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation");
        UnicodePatientName writePatient1(L"alphabetic^representation", L"", L"\x0420\x00df\x0062^\x0394\x0410\x00d7\x0072^representation");

        {
            WritingDataHandler handler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0, tagVR_t::PN);
            handler.setUnicodePatientName(0, writePatient0);
            handler.setUnicodePatientName(1, writePatient1);
        }

        UnicodePatientName checkPatient0(testDataSet.getUnicodePatientName(TagId(0x0010, 0x0010), 0));
        UnicodePatientName checkPatient1(testDataSet.getUnicodePatientName(TagId(0x0010, 0x0010), 1));
        ASSERT_EQ(writePatient0.getAlphabeticRepresentation(), checkPatient0.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient0.getIdeographicRepresentation(), checkPatient0.getIdeographicRepresentation());
        ASSERT_EQ(writePatient0.getPhoneticRepresentation(), checkPatient0.getPhoneticRepresentation());

        ASSERT_EQ(writePatient1.getAlphabeticRepresentation(), checkPatient1.getAlphabeticRepresentation());
        ASSERT_EQ(writePatient1.getIdeographicRepresentation(), checkPatient1.getIdeographicRepresentation());
        ASSERT_EQ(writePatient1.getPhoneticRepresentation(), checkPatient1.getPhoneticRepresentation());
    }
}


TEST(unicodeStringHandlerTest, unknownDICOMCharset)
{
    charsetsList_t charsets;
    charsets.push_back("UNKNOWN CHARSET");
    MutableDataSet testDataSet("1.2.840.10008.1.2.1", charsets);

    ASSERT_THROW(testDataSet.setUnicodeString(TagId(tagId_t::PatientName_0010_0010), L"Test patient"), CharsetConversionNoTableError);

}


TEST(unicodeStringHandlerTest, normalizeCharset)
{
    charsetsList_t charsets;
    charsets.push_back("iso_ir 192");
    MutableDataSet testDataSet("1.2.840.10008.1.2.1", charsets);

    testDataSet.setUnicodeString(TagId(tagId_t::PatientName_0010_0010), L"Test patient");
    EXPECT_EQ(L"Test patient", testDataSet.getUnicodeString(TagId(tagId_t::PatientName_0010_0010), 0));

}


} // namespace tests

} // namespace imebra

