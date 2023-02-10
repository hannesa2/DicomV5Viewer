#include <imebra/imebra.h>

#include "buildImageForTest.h"
#include <list>
#include <string.h>
#include <memory>
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

using namespace imebra;

TEST(dataSetTest, testFragmentation)
{
    // Add two images to a dataset, then fragment the first image
    Image testImage0 = buildImageForTest(
        400,
        300,
        imebra::bitDepth_t::depthU8,
        7,
        "RGB",
        50);

    Image testImage1 = buildImageForTest(
        400,
        300,
        imebra::bitDepth_t::depthU8,
        7,
        "RGB",
        20);

    MutableDataSet testDataSet("1.2.840.10008.1.2.4.70");
    testDataSet.setImage(0, testImage0, imageQuality_t::high);
    testDataSet.setImage(1, testImage1, imageQuality_t::high);

    // Verify the two images (must save first to adjust offsets)
    {
        MutableMemory saveDataSet;
        MemoryStreamOutput memoryStreamOutput(saveDataSet);
        StreamWriter streamWriter(memoryStreamOutput);
        CodecFactory::save(testDataSet, streamWriter, codecType_t::dicom);

        MemoryStreamInput memoryStreamInput(saveDataSet);
        StreamReader streamReader(memoryStreamInput);
        DataSet checkDataSet = CodecFactory::load(streamReader);
        Image verifyImage0 = checkDataSet.getImage(0);
        ASSERT_TRUE(compareImages(testImage0, verifyImage0) < 0.000001);
        Image verifyImage1(checkDataSet.getImage(1));
        ASSERT_TRUE(compareImages(testImage1, verifyImage1) < 0.000001);
    }

    // We are going to divide the 1st buffer into 2 buffers
    // The second offset increases by 8 (header for additional buffer).
    {
        ReadingDataHandlerNumeric handler0 = testDataSet.getReadingDataHandlerRaw(TagId(imebra::tagId_t::PixelData_7FE0_0010), 0);
        ReadingDataHandlerNumeric handler1 = testDataSet.getReadingDataHandlerRaw(TagId(imebra::tagId_t::PixelData_7FE0_0010), 1);
        ReadingDataHandlerNumeric handler2 = testDataSet.getReadingDataHandlerRaw(TagId(imebra::tagId_t::PixelData_7FE0_0010), 2);
        Memory memory0 = handler0.getMemory();
        Memory memory1 = handler1.getMemory();
        Memory memory2 = handler2.getMemory();

        size_t dummy(0);
        WritingDataHandlerNumeric write0 = testDataSet.getWritingDataHandlerRaw(TagId(imebra::tagId_t::PixelData_7FE0_0010), 0);
        WritingDataHandlerNumeric write1 = testDataSet.getWritingDataHandlerRaw(TagId(imebra::tagId_t::PixelData_7FE0_0010), 1);
        WritingDataHandlerNumeric write2 = testDataSet.getWritingDataHandlerRaw(TagId(imebra::tagId_t::PixelData_7FE0_0010), 2);
        WritingDataHandlerNumeric write3 = testDataSet.getWritingDataHandlerRaw(TagId(imebra::tagId_t::PixelData_7FE0_0010), 3);

        write0.setSize(8); // 8 bytes (offset for 2 images)
        write1.setSize(((memory1.size() / 2) + 1) & 0xfffffffc);
        write2.setSize(memory1.size() - write1.getSize());
        write3.setSize(memory2.size());

        memcpy(write0.data(&dummy), memory0.data(&dummy), write0.getSize());
        std::uint32_t* pOffsets = reinterpret_cast<std::uint32_t*>(write0.data(&dummy));
        pOffsets[1] += 8;

        // Copy first image into fragmented buffers
        memcpy(write1.data(&dummy), memory1.data(&dummy), write1.getSize());
        memcpy(write2.data(&dummy), memory1.data(&dummy) + write1.getSize(), memory1.size() - write1.getSize());

        // Copy second image into the last buffer
        memcpy(write3.data(&dummy), memory2.data(&dummy), memory2.size());
    }

    // Verify the two images (must save first to adjust offsets)
    {
        MutableMemory saveDataSet;
        MemoryStreamOutput memoryStreamOutput(saveDataSet);
        StreamWriter streamWriter(memoryStreamOutput);
        CodecFactory::save(testDataSet, streamWriter, codecType_t::dicom);

        MemoryStreamInput memoryStreamInput(saveDataSet);
        StreamReader streamReader(memoryStreamInput);
        DataSet checkDataSet = CodecFactory::load(streamReader);

        Image compareImage0 = checkDataSet.getImage(0);
        ASSERT_TRUE(compareImages(testImage0, compareImage0) < 0.000001);

        Image compareImage1 = checkDataSet.getImage(1);
        ASSERT_TRUE(compareImages(testImage1, compareImage1) < 0.000001);
        ASSERT_TRUE(compareImages(testImage0, compareImage1) > 30);
    }
}


TEST(dataSetTest, testVOIs)
{
    MutableDataSet testDataSet;

    vois_t vois0 = testDataSet.getVOIs();
    ASSERT_TRUE(vois0.empty());

    {
        WritingDataHandler centerHandler = testDataSet.getWritingDataHandler(TagId(0x0028, 0x1050), 0);
        centerHandler.setDouble(0, 10.4);
        centerHandler.setDouble(1, 20.4);

        WritingDataHandler widthHandler = testDataSet.getWritingDataHandler(TagId(0x0028, 0x1051), 0);
        widthHandler.setDouble(0, 12.5);
        widthHandler.setDouble(1, 22.5);

        WritingDataHandler descriptionHandler = testDataSet.getWritingDataHandler(TagId(0x0028, 0x1055), 0);
        descriptionHandler.setUnicodeString(0, L"Test1");
        descriptionHandler.setUnicodeString(1, L"Test2");
    }

    vois_t vois1 = testDataSet.getVOIs();
    ASSERT_EQ(2u, vois1.size());
    ASSERT_DOUBLE_EQ(10.4, vois1.at(0).getCenter());
    ASSERT_DOUBLE_EQ(12.5, vois1.at(0).getWidth());
    ASSERT_EQ(L"Test1", vois1.at(0).getUnicodeDescription());
    ASSERT_EQ("Test1", vois1.at(0).getDescription());

    ASSERT_DOUBLE_EQ(20.4, vois1.at(1).getCenter());
    ASSERT_DOUBLE_EQ(22.5, vois1.at(1).getWidth());
    ASSERT_EQ(L"Test2", vois1.at(1).getUnicodeDescription());
    ASSERT_EQ("Test2", vois1.at(1).getDescription());
}

TEST(dataSetTest, testGetTags)
{
    MutableDataSet testDataSet;

    testDataSet.setString(TagId(tagId_t::PatientName_0010_0010), "Test patient");
    testDataSet.setAge(TagId(tagId_t::PatientAge_0010_1010), Age(3, ageUnit_t::years));

    tagsIds_t tags = testDataSet.getTags();
    bool bPatientName(false);
    bool bPatientAge(false);
    for(tagsIds_t::const_iterator scanTags(tags.begin()), endTags(tags.end()); scanTags != endTags; ++scanTags)
    {
        bPatientName |= (scanTags->getGroupId() == 0x0010 && scanTags->getTagId() == 0x0010);
        bPatientAge |= (scanTags->getGroupId() == 0x0010 && scanTags->getTagId() == 0x1010);
    }
    ASSERT_TRUE(bPatientName);
    ASSERT_TRUE(bPatientAge);
}

TEST(dataSetTest, testCreateTags)
{
    MutableDataSet testDataSet;

    {
        MutableTag patientTag = testDataSet.getTagCreate(TagId(tagId_t::PatientName_0010_0010), tagVR_t::PN);
        WritingDataHandler patientHandler = patientTag.getWritingDataHandler(0);
        patientHandler.setString(0, "test0");
        patientHandler.setString(1, "test1");
    }

    Tag patientTag = testDataSet.getTag(TagId(tagId_t::PatientName_0010_0010));
    ReadingDataHandler patientHandler = patientTag.getReadingDataHandler(0);
    ASSERT_EQ("test0", patientHandler.getString(0));
    ASSERT_EQ("test1", patientHandler.getString(1));
}


TEST(dataSetTest, testSetGetTags)
{
    MutableDataSet testDataSet;

    testDataSet.setAge(TagId(tagId_t::PatientAge_0010_1010), Age(3, ageUnit_t::months));
    testDataSet.setDate(TagId(tagId_t::AcquisitionDateTime_0008_002A), Date(2014, 2, 1, 12, 20, 30, 0, 0, 0));
    testDataSet.setDate(TagId(tagId_t::PatientBirthDate_0010_0030), Date(2000, 1, 2, 13, 30, 40, 0, 0, 0), tagVR_t::DT);
    testDataSet.setString(TagId(tagId_t::PatientName_0010_0010), "Test patient");
    testDataSet.setDouble(TagId(0x20, 0x20), 45.6, tagVR_t::OD);
    testDataSet.setInt32(TagId(0x20, 0x21), 50, tagVR_t::SL);
    testDataSet.setUint32(TagId(0x20, 0x22), 60, tagVR_t::UL);

    Age age0 = testDataSet.getAge(TagId(tagId_t::PatientAge_0010_1010), 0);
    ASSERT_EQ(3u, age0.getAgeValue());
    ASSERT_EQ(ageUnit_t::months, age0.getAgeUnits());
    ASSERT_EQ("003M", testDataSet.getString(TagId(tagId_t::PatientAge_0010_1010), 0));
    ASSERT_THROW(testDataSet.getInt32(TagId(tagId_t::PatientAge_0010_1010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getUint32(TagId(tagId_t::PatientAge_0010_1010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getDouble(TagId(tagId_t::PatientAge_0010_1010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getDouble(TagId(tagId_t::PatientAge_0010_1010), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getDate(TagId(tagId_t::PatientAge_0010_1010), 0), DataHandlerConversionError);

    Date date0 = testDataSet.getDate(TagId(tagId_t::AcquisitionDateTime_0008_002A), 0);
    ASSERT_EQ(2014u, date0.getYear());
    ASSERT_EQ(2u, date0.getMonth());
    ASSERT_EQ(1u, date0.getDay());
    ASSERT_THROW(testDataSet.getInt32(TagId(tagId_t::AcquisitionDateTime_0008_002A), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getUint32(TagId(tagId_t::AcquisitionDateTime_0008_002A), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getDouble(TagId(tagId_t::AcquisitionDateTime_0008_002A), 0), DataHandlerConversionError);
    ASSERT_THROW(testDataSet.getAge(TagId(tagId_t::AcquisitionDateTime_0008_002A), 0), DataHandlerConversionError);

    Date date1 = testDataSet.getDate(TagId(tagId_t::PatientBirthDate_0010_0030), 0);
    ASSERT_EQ(2000u, date1.getYear());
    ASSERT_EQ(1u, date1.getMonth());
    ASSERT_EQ(2u, date1.getDay());

    ASSERT_EQ("Test patient", testDataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0));
    ASSERT_DOUBLE_EQ(45.6, testDataSet.getDouble(TagId(0x20, 0x20), 0));
    ASSERT_EQ(50, testDataSet.getInt32(TagId(0x20, 0x21), 0));
    ASSERT_EQ(60u, testDataSet.getUint32(TagId(0x20, 0x22), 0));

}

TEST(dataSetTest, defaults)
{
    Age defaultAge(5, ageUnit_t::years);
    Date defaultDate(2015, 3, 2, 12, 0, 0, 0, 0, 0);
    std::uint32_t defaultUnsigned(150);
    std::int32_t defaultSigned(-10);
    double defaultDouble(10.0);
    std::string defaultString("defaultstring");
    std::wstring defaultUnicodeString(L"defaultUnicodeString");

    MutableDataSet testDataSet;

    Age getDefaultAge = testDataSet.getAge(TagId(20, 20), 0, defaultAge);
    ASSERT_EQ(defaultAge.getAgeValue(), getDefaultAge.getAgeValue());
    ASSERT_EQ(defaultAge.getAgeUnits(), getDefaultAge.getAgeUnits());

    Date getDefaultDate = testDataSet.getDate(TagId(20, 20), 0, defaultDate);
    ASSERT_EQ(defaultDate.getYear(), getDefaultDate.getYear());
    ASSERT_EQ(defaultDate.getMonth(), getDefaultDate.getMonth());
    ASSERT_EQ(defaultDate.getDay(), getDefaultDate.getDay());
    ASSERT_EQ(defaultDate.getHour(), getDefaultDate.getHour());
    ASSERT_EQ(defaultDate.getMinutes(), getDefaultDate.getMinutes());
    ASSERT_EQ(defaultDate.getSeconds(), getDefaultDate.getSeconds());
    ASSERT_EQ(defaultDate.getNanoseconds(), getDefaultDate.getNanoseconds());
    ASSERT_EQ(defaultDate.getOffsetHours(), getDefaultDate.getOffsetHours());
    ASSERT_EQ(defaultDate.getOffsetMinutes(), getDefaultDate.getOffsetMinutes());

    ASSERT_EQ(defaultUnsigned, testDataSet.getUint32(TagId(20, 20), 0, defaultUnsigned));
    ASSERT_EQ(defaultSigned, testDataSet.getInt32(TagId(20, 20), 0, defaultSigned));
    ASSERT_DOUBLE_EQ(defaultDouble, testDataSet.getDouble(TagId(20, 20), 0, defaultDouble));
    ASSERT_EQ(defaultString, testDataSet.getString(TagId(20, 20), 0, defaultString));
    ASSERT_EQ(defaultUnicodeString, testDataSet.getUnicodeString(TagId(20, 20), 0, defaultUnicodeString));
}

TEST(dataSetTest, testSequence)
{
    for(int transferSyntaxId(0); transferSyntaxId != 4; ++transferSyntaxId)
    {
        std::string transferSyntax;
        switch(transferSyntaxId)
        {
        case 0:
            transferSyntax = "1.2.840.10008.1.2";
            break;
        case 1:
            transferSyntax = "1.2.840.10008.1.2.1";
            break;
        case 2:
            transferSyntax = "1.2.840.10008.1.2.2";
            break;
        case 3:
            transferSyntax = "1.2.840.10008.1.2.5";
            break;
        }

        std::cout << "Sequence test. Transfer syntax: " << transferSyntax << std::endl;

        MutableDataSet testDataSet(transferSyntax);

        {
            MutableDataSet sequence0 = testDataSet.appendSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111));
            MutableDataSet sequence1 = testDataSet.appendSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111));

            sequence0.setString(TagId(0x10, 0x10), "Test0");
            sequence1.setString(TagId(0x10, 0x10), "Test1");
        }

        {
            DataSet sequence0 = testDataSet.getSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111), 0);
            DataSet sequence1 = testDataSet.getSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111), 1);
            ASSERT_EQ("Test0", sequence0.getString(TagId(0x10, 0x10), 0));
            ASSERT_EQ("Test1", sequence1.getString(TagId(0x10, 0x10), 0));
        }

        MutableMemory encodedDataSet;
        MemoryStreamOutput outputStream(encodedDataSet);
        StreamWriter outputWriter(outputStream);
        CodecFactory::save(testDataSet, outputWriter, codecType_t::dicom);

        MemoryStreamInput inputStream(encodedDataSet);
        StreamReader inputReader(inputStream);
        DataSet readDataSet = CodecFactory::load(inputReader);
        {
            DataSet sequence0 = readDataSet.getSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111), 0);
            DataSet sequence1 = readDataSet.getSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111), 1);
            ASSERT_EQ("Test0", sequence0.getString(TagId(0x10, 0x10), 0));
            ASSERT_EQ("Test1", sequence1.getString(TagId(0x10, 0x10), 0));
        }
    }
}

TEST(dataSetTest, dataHandler)
{
    {
        MutableDataSet testDataSet;
        {
            WritingDataHandler handler = testDataSet.getWritingDataHandler(TagId(tagId_t::PatientName_0010_0010), 0, tagVR_t::UL);
            handler.setSize(10);
            ASSERT_EQ(tagVR_t::UL, handler.getDataType());
            ASSERT_EQ(10u, handler.getSize());
        }
        ReadingDataHandler handler = testDataSet.getReadingDataHandler(TagId(tagId_t::PatientName_0010_0010), 0);
        ReadingDataHandler raw = testDataSet.getReadingDataHandlerRaw(TagId(tagId_t::PatientName_0010_0010), 0);
        ASSERT_EQ(tagVR_t::UL, handler.getDataType());
        ASSERT_EQ(10u, handler.getSize());
        ASSERT_EQ(40u, raw.getSize());
    }

    {
        MutableDataSet testDataSet;
        {
            WritingDataHandlerNumeric handler = testDataSet.getWritingDataHandlerNumeric(TagId(tagId_t::RegionLocationMinX0_0018_6018), 0);
            handler.setInt32(0, 100);
            handler.setSize(10);
            ASSERT_EQ(tagVR_t::UL, handler.getDataType());
            ASSERT_EQ(10u, handler.getSize());
        }
        ReadingDataHandlerNumeric handler = testDataSet.getReadingDataHandlerNumeric(TagId(tagId_t::RegionLocationMinX0_0018_6018), 0);
        ReadingDataHandler raw = testDataSet.getReadingDataHandlerRaw(TagId(tagId_t::RegionLocationMinX0_0018_6018), 0);
        ASSERT_EQ(100, handler.getInt32(0));
        ASSERT_EQ(tagVR_t::UL, handler.getDataType());
        ASSERT_EQ(10u, handler.getSize());
        ASSERT_EQ(40u, raw.getSize());
    }

    {
        MutableDataSet testDataSet;
        {
            WritingDataHandlerNumeric handler = testDataSet.getWritingDataHandlerRaw(TagId(tagId_t::RegionLocationMinX0_0018_6018), 0);
            handler.setSize(16);
            ASSERT_EQ(tagVR_t::UL, handler.getDataType());
            ASSERT_EQ(16u, handler.getSize());
        }
        ReadingDataHandlerNumeric handler = testDataSet.getReadingDataHandlerNumeric(TagId(tagId_t::RegionLocationMinX0_0018_6018), 0);
        ReadingDataHandler raw = testDataSet.getReadingDataHandlerRaw(TagId(tagId_t::RegionLocationMinX0_0018_6018), 0);
        ASSERT_EQ(tagVR_t::UL, handler.getDataType());
        ASSERT_EQ(4u, handler.getSize());
        ASSERT_EQ(16u, raw.getSize());
    }

    {
        MutableDataSet testDataSet;
        {
            WritingDataHandler handler = testDataSet.getWritingDataHandler(TagId(tagId_t::PatientName_0010_0010), 0);
            handler.setSize(2);
            ASSERT_EQ(tagVR_t::PN, handler.getDataType());
            ASSERT_EQ(2u, handler.getSize());
        }
        ReadingDataHandler handler = testDataSet.getReadingDataHandler(TagId(tagId_t::PatientName_0010_0010), 0);
        ASSERT_EQ(tagVR_t::PN, handler.getDataType());
        ASSERT_EQ(2u, handler.getSize());
    }

    {
        MutableDataSet testDataSet;
        {
            WritingDataHandlerNumeric handler = testDataSet.getWritingDataHandlerRaw(TagId(tagId_t::PixelData_7FE0_0010), 0, tagVR_t::OW);
            handler.setSize(20);
            ASSERT_EQ(tagVR_t::OW, handler.getDataType());
            ASSERT_EQ(20u, handler.getSize());
        }
        ReadingDataHandlerNumeric handler = testDataSet.getReadingDataHandlerNumeric(TagId(tagId_t::PixelData_7FE0_0010), 0);
        ASSERT_EQ(tagVR_t::OW, handler.getDataType());
        ASSERT_EQ(10u, handler.getSize());
    }
}


TEST(dataSetTest, testEmptySequence)
{
    for(int transferSyntaxId(0); transferSyntaxId != 4; ++transferSyntaxId)
    {
        std::string transferSyntax;
        switch(transferSyntaxId)
        {
        case 0:
            transferSyntax = "1.2.840.10008.1.2";
            break;
        case 1:
            transferSyntax = "1.2.840.10008.1.2.1";
            break;
        case 2:
            transferSyntax = "1.2.840.10008.1.2.2";
            break;
        case 3:
            transferSyntax = "1.2.840.10008.1.2.5";
            break;
        }

        std::cout << "Sequence test. Transfer syntax: " << transferSyntax << std::endl;

        MutableDataSet testDataSet(transferSyntax);

        {
            testDataSet.appendSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111));
            testDataSet.appendSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111));
        }

        {
            DataSet sequence0 = testDataSet.getSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111), 0);
            DataSet sequence1 = testDataSet.getSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111), 1);
        }

        MutableMemory encodedDataSet;
        MemoryStreamOutput outputStream(encodedDataSet);
        StreamWriter outputWriter(outputStream);
        CodecFactory::save(testDataSet, outputWriter, codecType_t::dicom);

        MemoryStreamInput inputStream(encodedDataSet);
        StreamReader inputReader(inputStream);
        DataSet readDataSet = CodecFactory::load(inputReader);
        {
            Tag sequenceTag = readDataSet.getTag(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111));
            ASSERT_EQ(tagVR_t::SQ, sequenceTag.getDataType());
            ASSERT_THROW(sequenceTag.getSequenceItem(0), MissingItemError);
            ASSERT_THROW(sequenceTag.getSequenceItem(1), MissingItemError);
            ASSERT_THROW(readDataSet.getSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111), 0), MissingItemError);
            ASSERT_THROW(readDataSet.getSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111), 1), MissingItemError);
        }
    }
}


TEST(dataSetTest, charsetNotNecessaryTest)
{

    MutableMemory streamMemory;

    charsetsList_t charsets;
    MutableDataSet testDataSet(uidExplicitVRLittleEndian_1_2_840_10008_1_2_1, charsets);
    EXPECT_EQ("1.2.840.10008.1.2.1", testDataSet.getString(TagId(tagId_t::TransferSyntaxUID_0002_0010), 0));

    testDataSet.setString(TagId(tagId_t::PatientAge_0010_1010), "012Y");
    testDataSet.setString(TagId(tagId_t::SOPInstanceUID_0008_0018), "1.2.3.4.5");

    MemoryStreamOutput writeStream(streamMemory);
    StreamWriter writer(writeStream);
    CodecFactory::save(testDataSet, writer, codecType_t::dicom);

    MemoryStreamInput readStream(streamMemory);
    StreamReader reader(readStream);
    DataSet loadedDataSet = CodecFactory::load(reader);

    EXPECT_THROW(loadedDataSet.getTag(TagId(tagId_t::SpecificCharacterSet_0008_0005)), MissingDataElementError);
}


TEST(dataSetTest, sequenceNoCharsetTest)
{
    std::wstring patientName0 = L"??\x0628\x062a\x062b\x062f^\0x400\0x410\0x420";
    std::wstring patientName1 = L"\0x420\x062a\x062b^\0x400\0x410\x0628\x062a";

    MutableMemory streamMemory;

    charsetsList_t charsets;
    charsets.push_back("ISO_IR 192");
    MutableDataSet testDataSet("1.2.840.10008.1.2.1", charsets);

    testDataSet.setString(TagId(tagId_t::PatientAge_0010_1010), "012Y");
    testDataSet.setString(TagId(tagId_t::SOPInstanceUID_0008_0018), "1.2.3.4.5");

    {
        MutableDataSet sequence0 = testDataSet.appendSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111));
        MutableDataSet sequence1 = testDataSet.appendSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111));

        sequence0.setUnicodeString(TagId(0x10, 0x10), patientName0);
        sequence1.setUnicodeString(TagId(0x10, 0x10), patientName1);
    }

    MemoryStreamOutput writeStream(streamMemory);
    StreamWriter writer(writeStream);
    CodecFactory::save(testDataSet, writer, codecType_t::dicom);

    MemoryStreamInput readStream(streamMemory);
    StreamReader reader(readStream);
    DataSet loadedDataSet = CodecFactory::load(reader);

    EXPECT_NO_THROW(loadedDataSet.getTag(TagId(tagId_t::SpecificCharacterSet_0008_0005)));

    DataSet sequence0 = loadedDataSet.getSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111), 0);
    DataSet sequence1 = loadedDataSet.getSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111), 1);
    EXPECT_THROW(sequence0.getTag(TagId(tagId_t::SpecificCharacterSet_0008_0005)), MissingDataElementError);
    EXPECT_THROW(sequence1.getTag(TagId(tagId_t::SpecificCharacterSet_0008_0005)), MissingDataElementError);
    ASSERT_EQ(patientName0, sequence0.getUnicodeString(TagId(0x10, 0x10), 0));
    ASSERT_EQ(patientName1, sequence1.getUnicodeString(TagId(0x10, 0x10), 0));
}


TEST(dataSetTest, functionalGroupPerFrame)
{
    MutableDataSet testDataSet;

    MutableDataSet frame0 = testDataSet.appendSequenceItem(TagId(tagId_t::PerFrameFunctionalGroupsSequence_5200_9230));
    frame0.setDouble(TagId(tagId_t::WindowCenter_0028_1050), 100);
    frame0.setDouble(TagId(tagId_t::WindowWidth_0028_1051), 150);

    MutableDataSet frame1 = testDataSet.appendSequenceItem(TagId(tagId_t::PerFrameFunctionalGroupsSequence_5200_9230));
    frame1.setDouble(TagId(tagId_t::WindowCenter_0028_1050), 200);
    frame1.setDouble(TagId(tagId_t::WindowWidth_0028_1051), 250);

    MutableDataSet frame2 = testDataSet.appendSequenceItem(TagId(tagId_t::PerFrameFunctionalGroupsSequence_5200_9230));
    frame2.setDouble(TagId(tagId_t::WindowCenter_0028_1050), 300);
    frame2.setDouble(TagId(tagId_t::WindowWidth_0028_1051), 350);

    DataSet checkFrame0 = testDataSet.getFunctionalGroupDataSet(0);
    EXPECT_DOUBLE_EQ(100, checkFrame0.getDouble(TagId(tagId_t::WindowCenter_0028_1050), 0));
    EXPECT_DOUBLE_EQ(150, checkFrame0.getDouble(TagId(tagId_t::WindowWidth_0028_1051), 0));

    DataSet checkFrame1 = testDataSet.getFunctionalGroupDataSet(1);
    EXPECT_DOUBLE_EQ(200, checkFrame1.getDouble(TagId(tagId_t::WindowCenter_0028_1050), 0));
    EXPECT_DOUBLE_EQ(250, checkFrame1.getDouble(TagId(tagId_t::WindowWidth_0028_1051), 0));

    DataSet checkFrame2 = testDataSet.getFunctionalGroupDataSet(2);
    EXPECT_DOUBLE_EQ(300, checkFrame2.getDouble(TagId(tagId_t::WindowCenter_0028_1050), 0));
    EXPECT_DOUBLE_EQ(350, checkFrame2.getDouble(TagId(tagId_t::WindowWidth_0028_1051), 0));

    EXPECT_THROW(testDataSet.getFunctionalGroupDataSet(3), MissingTagError);

}


TEST(dataSetTest, functionalGroupCommon)
{
    MutableDataSet testDataSet;

    MutableDataSet frame = testDataSet.appendSequenceItem(TagId(tagId_t::SharedFunctionalGroupsSequence_5200_9229));
    frame.setDouble(TagId(tagId_t::WindowCenter_0028_1050), 100);
    frame.setDouble(TagId(tagId_t::WindowWidth_0028_1051), 150);

    DataSet checkFrame0 = testDataSet.getFunctionalGroupDataSet(0);
    EXPECT_DOUBLE_EQ(100, checkFrame0.getDouble(TagId(tagId_t::WindowCenter_0028_1050), 0));
    EXPECT_DOUBLE_EQ(150, checkFrame0.getDouble(TagId(tagId_t::WindowWidth_0028_1051), 0));

    DataSet checkFrame1 = testDataSet.getFunctionalGroupDataSet(1);
    EXPECT_DOUBLE_EQ(100, checkFrame1.getDouble(TagId(tagId_t::WindowCenter_0028_1050), 0));
    EXPECT_DOUBLE_EQ(150, checkFrame1.getDouble(TagId(tagId_t::WindowWidth_0028_1051), 0));

    DataSet checkFrame2 = testDataSet.getFunctionalGroupDataSet(2);
    EXPECT_DOUBLE_EQ(100, checkFrame2.getDouble(TagId(tagId_t::WindowCenter_0028_1050), 0));
    EXPECT_DOUBLE_EQ(150, checkFrame2.getDouble(TagId(tagId_t::WindowWidth_0028_1051), 0));
}


TEST(dataSetTest, streamWriterAndReader)
{
    {
        MutableDataSet testDataSet;

        {
            StreamWriter writer = testDataSet.getStreamWriter(TagId(tagId_t::PatientName_0010_0010), 0);
            writer.write("TEST", 4);
        }
        StreamReader reader = testDataSet.getStreamReader(TagId(tagId_t::PatientName_0010_0010), 0);
        char destination[10];
        size_t readSize = reader.readSome(destination, sizeof(destination));
        ASSERT_EQ(4u, readSize);
        ASSERT_EQ(std::string("TEST"), std::string(destination, 4));

        PatientName patientName = testDataSet.getPatientName(TagId(tagId_t::PatientName_0010_0010), 0);
        ASSERT_EQ("TEST", patientName.getAlphabeticRepresentation());
    }

    {
        MutableDataSet testDataSet;
        {
            StreamWriter writer = testDataSet.getStreamWriter(TagId(tagId_t::PatientName_0010_0010), 0, tagVR_t::UI);
            writer.write("10.0.1", 6);
        }

        ASSERT_EQ(tagVR_t::UI, testDataSet.getDataType(TagId(tagId_t::PatientName_0010_0010)));
        ASSERT_EQ("10.0.1", testDataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0));
    }
}

} // namespace tests

} // namespace imebra
