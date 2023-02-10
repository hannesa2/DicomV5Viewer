#include <dicomhero6/dicomhero.h>
#include "buildImageForTest.h"
#include "testsSettings.h"
#include <gtest/gtest.h>
#include <limits>
#include <thread>
#include "testsSettings.h"

#ifndef DISABLE_DCMTK_INTEROPERABILITY_TEST

    #include <dcmtk/dcmdata/dcdatset.h>
    #include <dcmtk/dcmdata/dcfilefo.h>
    #include <dcmtk/dcmdata/dcistrmb.h>
    #include <dcmtk/dcmdata/dcrledrg.h>
    #include <dcmtk/dcmimgle/dcmimage.h>
    #include <dcmtk/dcmimage/diregist.h>
    #include <dcmtk/dcmdata/dcovlay.h>

#endif

namespace dicomhero
{

namespace tests
{


TEST(dicomCodecTest, testGroupLength)
{
    DataSet dataset(uidExplicitVRLittleEndian_1_2_840_10008_1_2_1);

    MutableMemory memory;
    MemoryStreamOutput outputMemory(memory);
    StreamWriter memoryWriter(outputMemory);
    CodecFactory::save(dataset, memoryWriter, codecType_t::dicom);

    MemoryStreamInput inputMemory(memory);
    StreamReader memoryReader(inputMemory);
    DataSet readDataset(CodecFactory::load(memoryReader));

    size_t groupSize = readDataset.getUint32(TagId(tagId_t::FileMetaInformationGroupLength_0002_0000), 0);

    // size - preamble(128), signature(4), groupId(2), tagId(2), vr(2), length(2), value length (4)
    ASSERT_EQ(memory.size() - 128 - 4 - 2 - 2 - 2 - 2 - 4, groupSize);
}


TEST(dicomCodecTest, testDicom)
{
    const bool bFastMode = !::tests::settings::getSettings().get("--fast").empty();

    const char* const colorSpaces[] = {"MONOCHROME2", "RGB", "YBR_FULL", "YBR_FULL_422", "YBR_FULL_420"};

    std::uint32_t highBitStep = bFastMode ? 8 : 1;
    std::uint32_t sizeStep = bFastMode ? 8 : 1;
    std::uint32_t interleavedStart = 0;
    std::uint32_t signStep = 1;

    for(std::uint32_t sizeX(201); sizeX < 203u; sizeX += sizeStep)
    {
        for(std::uint32_t sizeY(151); sizeY < 153u; sizeY += sizeStep)
        {
            for(int transferSyntaxId(0); transferSyntaxId != 4; ++transferSyntaxId)
            {
                for(std::uint32_t interleaved(interleavedStart); interleaved < 2u; ++interleaved)
                {
                    for(std::uint32_t sign=0; sign != 2; sign += signStep)
                    {
                        for(std::uint32_t highBit(0); highBit != 32; highBit += highBitStep)
                        {
                            for(unsigned int colorSpaceIndex(0); colorSpaceIndex != sizeof(colorSpaces)/sizeof(colorSpaces[0]); ++colorSpaceIndex)
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

                                const std::string colorSpace(colorSpaces[colorSpaceIndex]);
                                const bool bSubsampledX(ColorTransformsFactory::isSubsampledY(colorSpace));
                                const bool bSubsampledY(ColorTransformsFactory::isSubsampledX(colorSpace));

                                if((highBit < 7 || highBit > 24 || transferSyntax == "1.2.840.10008.1.2.5") &&
                                        (bSubsampledX || bSubsampledY))
                                {
                                    continue;
                                }

                                if(transferSyntax == "1.2.840.10008.1.2.5" && (interleaved == 1 || highBit == 0))
                                {
                                    continue;
                                }

                                bitDepth_t depth(sign == 0 ? bitDepth_t::depthU8 : bitDepth_t::depthS8);
                                if(highBit > 7)
                                {
                                    depth = (sign == 0 ? bitDepth_t::depthU16 : bitDepth_t::depthS16);
                                }
                                if(highBit > 15)
                                {
                                    depth = (sign == 0 ? bitDepth_t::depthU32 : bitDepth_t::depthS32);
                                }

                                std::vector<Image> images;

                                if(bSubsampledX || bSubsampledY)
                                {
                                    images.push_back(buildSubsampledImage(
                                            sizeX,
                                            sizeY,
                                            depth,
                                            highBit,
                                            colorSpace));
                                    images.push_back(buildSubsampledImage(
                                            sizeX,
                                            sizeY,
                                            depth,
                                            highBit,
                                            colorSpace));
                                    images.push_back(buildSubsampledImage(
                                            sizeX,
                                            sizeY,
                                            depth,
                                            highBit,
                                            colorSpace));
                                }
                                else
                                {
                                    images.push_back(buildImageForTest(
                                            sizeX,
                                            sizeY,
                                            depth,
                                            highBit,
                                            colorSpace,
                                            2));
                                    images.push_back(buildImageForTest(
                                            sizeX,
                                            sizeY,
                                            depth,
                                            highBit,
                                            colorSpace,
                                            100));
                                    images.push_back(buildImageForTest(
                                            sizeX,
                                            sizeY,
                                            depth,
                                            highBit,
                                            colorSpace,
                                            150));

                                }

                                EXPECT_EQ(highBit, images[0].getHighBit());
                                EXPECT_EQ(highBit, images[1].getHighBit());
                                EXPECT_EQ(highBit, images[2].getHighBit());

                                std::cout << "Dicom test. Transfer syntax: " << transferSyntax;
                                std::cout << " interleaved: " << interleaved;
                                std::cout << " sign: " << sign;
                                std::cout << " highBit: " << highBit << std::endl;
                                std::cout << " colorSpace: " << colorSpace << std::endl;
                                std::cout << " size: " << sizeX << " X " << sizeY << std::endl;

                                imageQuality_t quality = imageQuality_t::veryHigh;
                                if(bSubsampledY)
                                {
                                    quality = imageQuality_t::belowMedium;
                                }
                                else if(bSubsampledX)
                                {
                                    quality = imageQuality_t::medium;
                                }

                                MutableMemory streamMemory;
                                {
                                    DataSet testDataSet(transferSyntax);
                                    {
                                        WritingDataHandler writingDataHandler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0);
                                        writingDataHandler.setString(0, "AAAaa");
                                        writingDataHandler.setString(1, "BBBbbb");
                                        writingDataHandler.setString(2, "");
                                    }
                                    testDataSet.setDouble(TagId(tagId_t::TimeRange_0008_1163), 50.6);
                                    if(ColorTransformsFactory::getNumberOfChannels(colorSpace) > 1)
                                    {
                                        testDataSet.setUint32(TagId(dicomhero::tagId_t::PlanarConfiguration_0028_0006), 1 - interleaved);
                                    }
                                    testDataSet.setImage(0, images[0], quality);
                                    testDataSet.setImage(1, images[1], quality);
                                    testDataSet.setImage(2, images[2], quality);

                                    DataSet sequenceItem = testDataSet.appendSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111));
                                    sequenceItem.setString(TagId(tagId_t::PatientName_0010_0010), "test test");

                                    DataSet sequenceItem1 = sequenceItem.appendSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111));
                                    sequenceItem1.setString(TagId(tagId_t::PatientName_0010_0010), "test test1");

                                    MemoryStreamOutput writeStream(streamMemory);
                                    StreamWriter writer(writeStream);
                                    CodecFactory::save(testDataSet, writer, codecType_t::dicom);
                                }

                                for(unsigned int lazyLoad(0); lazyLoad != 2; ++lazyLoad)
                                {
                                    MemoryStreamInput readStream(streamMemory);
                                    StreamReader reader(readStream);
                                    DataSet testDataSet = CodecFactory::load(reader, lazyLoad == 0 ? std::numeric_limits<size_t>::max() : 1);

                                    EXPECT_EQ(std::string(DICOMHERO_IMPLEMENTATION_CLASS_UID), testDataSet.getString(TagId(tagId_t::ImplementationClassUID_0002_0012), 0));
                                    EXPECT_EQ(std::string(DICOMHERO_IMPLEMENTATION_NAME), testDataSet.getString(TagId(tagId_t::ImplementationVersionName_0002_0013), 0));

                                    EXPECT_EQ(0u, testDataSet.getUint32(TagId(tagId_t::FileMetaInformationVersion_0002_0001), 0));
                                    EXPECT_EQ(1u, testDataSet.getUint32(TagId(tagId_t::FileMetaInformationVersion_0002_0001), 1));
                                    EXPECT_THROW(testDataSet.getUint32(TagId(tagId_t::FileMetaInformationVersion_0002_0001), 2), MissingItemError);
                                    EXPECT_EQ(tagVR_t::OB, testDataSet.getDataType(TagId(tagId_t::FileMetaInformationVersion_0002_0001)));

                                    EXPECT_EQ(std::string("AAAaa"), testDataSet.getString(TagId(dicomhero::tagId_t::PatientName_0010_0010), 0));
                                    EXPECT_EQ(std::string("BBBbbb"), testDataSet.getString(TagId(dicomhero::tagId_t::PatientName_0010_0010), 1));
                                    EXPECT_EQ(std::string(""), testDataSet.getString(TagId(dicomhero::tagId_t::PatientName_0010_0010), 2));
                                    EXPECT_DOUBLE_EQ(50.6, testDataSet.getDouble(TagId(tagId_t::TimeRange_0008_1163), 0));

                                    DataSet sequenceItem = testDataSet.getSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111), 0);
                                    EXPECT_EQ("test test", sequenceItem.getString(TagId(tagId_t::PatientName_0010_0010), 0));
                                    EXPECT_THROW(sequenceItem.getUint32(TagId(tagId_t::FileMetaInformationVersion_0002_0001), 0), MissingGroupError);

                                    DataSet sequenceItem1 = sequenceItem.getSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111), 0);
                                    EXPECT_EQ("test test1", sequenceItem1.getString(TagId(tagId_t::PatientName_0010_0010), 0));
                                    EXPECT_THROW(sequenceItem1.getUint32(TagId(tagId_t::FileMetaInformationVersion_0002_0001), 0), MissingGroupError);

                                    for(unsigned int repeatLazyLoad(0); repeatLazyLoad != lazyLoad + 1; ++ repeatLazyLoad)
                                    {
                                        Image checkImage0 = testDataSet.getImage(0);
                                        ASSERT_TRUE(identicalImages(checkImage0, images[0]));

                                        Image checkImage1 = testDataSet.getImage(1);
                                        ASSERT_TRUE(identicalImages(checkImage1, images[1]));

                                        Image checkImage2 = testDataSet.getImage(2);
                                        ASSERT_TRUE(identicalImages(checkImage2, images[2]));

                                        if(checkImage0.getChannelsNumber() == 1)
                                        {
                                            ASSERT_THROW(testDataSet.getTag(TagId(tagId_t::PlanarConfiguration_0028_0006)), MissingDataElementError);
                                        }
                                        else
                                        {
                                            EXPECT_EQ((std::int32_t)(1 - interleaved), testDataSet.getInt32(TagId(dicomhero::tagId_t::PlanarConfiguration_0028_0006), 0));
                                        }

                                    }

                                    if(transferSyntax != "1.2.840.10008.1.2.5")
                                    {
                                        std::uint32_t checkHighBit(testDataSet.getUint32(TagId(tagId_t::HighBit_0028_0102), 0));
                                        std::uint32_t checkAllocatedBits(testDataSet.getUint32(TagId(tagId_t::BitsAllocated_0028_0100), 0));
                                        if(checkHighBit == 0)
                                        {
                                            EXPECT_EQ(1u, checkAllocatedBits);
                                        }
                                        else if(checkHighBit < 8)
                                        {
                                            EXPECT_EQ(8u, checkAllocatedBits);
                                        }
                                        else if(checkHighBit < 16)
                                        {
                                            EXPECT_EQ(16u, checkAllocatedBits);
                                        }
                                        else if(checkHighBit < 24)
                                        {
                                            EXPECT_EQ(24u, checkAllocatedBits);
                                        }
                                        else
                                        {
                                            EXPECT_EQ(32u, checkAllocatedBits);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            } // transferSyntaxId
        }
    }
}


TEST(dicomCodecTest, testNEMA)
{
    std::string nemaTags("\x02\x00\x02\x00\x55\x49\x1a\x00\x31\x2e\x32\x2e\x38\x34\x30\x2e\x31\x30\x30\x30\x38\x2e\x35\x2e"
                         "\x31\x2e\x34\x2e\x31\x2e\x31\x2e\x37\x00\x02\x00\x10\x00\x55\x49\x14\x00\x31\x2e\x32\x2e\x38\x34"
                         "\x30\x2e\x31\x30\x30\x30\x38\x2e\x31\x2e\x32\x2e\x31\x00\x08\x00\x16\x00\x55\x49\x1a\x00\x31\x2e"
                         "\x32\x2e\x38\x34\x30\x2e\x31\x30\x30\x30\x38\x2e\x35\x2e\x31\x2e\x34\x2e\x31\x2e\x31\x2e\x37\x00"
                         "\x08\x00\x18\x00\x55\x49\x2a\x00\x33\x2e\x31\x2e\x32\x2e\x30\x32\x38\x32\x30\x31\x33\x31\x30\x31"
                         "\x30\x31\x30\x32\x2e\x31\x2e\x32\x2e\x35\x2e\x31\x30\x30\x30\x30\x30\x32\x2e\x30\x31\x34\x2e\x32"
                         "\x2e\x31\x08\x00\x20\x00\x44\x41\x08\x00\x32\x30\x32\x32\x30\x31\x31\x30\x08\x00\x21\x00\x44\x41"
                         "\x08\x00\x32\x30\x32\x32\x30\x31\x31\x30\x08\x00\x23\x00\x44\x41\x08\x00\x32\x30\x32\x32\x30\x31"
                         "\x31\x30\x08\x00\x30\x00\x54\x4d\x06\x00\x31\x30\x32\x38\x32\x30\x08\x00\x31\x00\x54\x4d\x00\x00"
                         "\x08\x00\x33\x00\x54\x4d\x06\x00\x31\x30\x33\x30\x30\x30\x08\x00\x50\x00\x53\x48\x0a\x00\x30\x31"
                         "\x2f\x31\x30\x2f\x32\x30\x32\x32", 248);

    MemoryStreamInput readStream(Memory(nemaTags.data(), nemaTags.size()));
    StreamReader reader(readStream);
    DataSet testDataSet = CodecFactory::load(reader);

    ASSERT_EQ(testDataSet.getString(TagId(2, 2), 0), "1.2.840.10008.5.1.4.1.1.7");
    ASSERT_EQ(testDataSet.getString(TagId(2, 16), 0), "1.2.840.10008.1.2.1");
    ASSERT_EQ(testDataSet.getString(TagId(8, 32), 0), "20220110");
}


TEST(dicomCodecTest, testDicom32bit)
{
    for(int transferSyntaxId(3); transferSyntaxId != 4; ++transferSyntaxId)
    {
        std::string colorSpace("MONOCHROME2");

        Image dicomImage(3, 1, bitDepth_t::depthU32, colorSpace, 31);
        {
            WritingDataHandlerNumeric write = dicomImage.getWritingDataHandler();
            write.setUint32(0, std::numeric_limits<std::uint32_t>::max());
            write.setUint32(1, std::numeric_limits<std::uint32_t>::max() / 2);
            write.setUint32(2, 0);
        }

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

        std::cout << "Dicom test. Transfer syntax: " << transferSyntax;

        MutableMemory streamMemory;
        {
            DataSet testDataSet(transferSyntax);
            testDataSet.setImage(0, dicomImage, imageQuality_t::veryHigh);

            MemoryStreamOutput writeStream(streamMemory);
            StreamWriter writer(writeStream);
            CodecFactory::save(testDataSet, writer, codecType_t::dicom);
        }

        MemoryStreamInput readStream(streamMemory);
        StreamReader reader(readStream);
        DataSet testDataSet = CodecFactory::load(reader, std::numeric_limits<size_t>::max());

        Image checkImage = testDataSet.getImage(0);

        ReadingDataHandlerNumeric read = checkImage.getReadingDataHandler();
        EXPECT_EQ(std::numeric_limits<std::uint32_t>::max(), read.getUint32(0));
        EXPECT_EQ(std::numeric_limits<std::uint32_t>::max() / 2, read.getUint32(1));
        EXPECT_EQ(0u, read.getUint32(2));
    }
}


TEST(dicomCodecTest, testImplicitPrivateTags)
{
    MutableMemory streamMemory;
    {
        DataSet testDataSet("1.2.840.10008.1.2");
        testDataSet.setString(TagId(tagId_t::PatientName_0010_0010), "Patient name");
        testDataSet.setString(TagId(std::uint16_t(11), std::uint16_t(2)), "Private tag", tagVR_t::ST);

        MemoryStreamOutput writeStream(streamMemory);
        StreamWriter writer(writeStream);
        CodecFactory::save(testDataSet, writer, codecType_t::dicom);
    }

    MemoryStreamInput readStream(streamMemory);
    StreamReader reader(readStream);
    DataSet testDataSet = CodecFactory::load(reader, std::numeric_limits<size_t>::max());

    EXPECT_EQ("Patient name", testDataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0));

    ReadingDataHandlerNumeric privateHandler = testDataSet.getReadingDataHandlerNumeric(TagId(std::uint16_t(11), std::uint16_t(2)), 0);
    EXPECT_EQ(tagVR_t::UN, privateHandler.getDataType());

    size_t length;
    std::string privateString(privateHandler.data(&length));
    EXPECT_EQ("Private tag ", privateString); // Even length
}


void feedDataThread(PipeStream& source, DataSet& dataSet)
{
    StreamWriter writer(source.getStreamOutput());

    CodecFactory::save(dataSet, writer, codecType_t::dicom);

    source.close(5000);
}


TEST(dicomCodecTest, codecFactoryPipe)
{
    DataSet testDataSet("1.2.840.10008.1.2");
    testDataSet.setString(TagId(tagId_t::PatientName_0010_0010), "Patient name");
    testDataSet.setString(TagId(std::uint16_t(11), std::uint16_t(2)), "Private tag", tagVR_t::ST);

    PipeStream source(1024);

    std::thread feedData(dicomhero::tests::feedDataThread, std::ref(source), std::ref(testDataSet));

    StreamReader reader(source.getStreamInput());
    DataSet loadedDataSet(CodecFactory::load(reader));

    feedData.join();

    EXPECT_EQ("Patient name", loadedDataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0));

    ReadingDataHandlerNumeric privateHandler(loadedDataSet.getReadingDataHandlerNumeric(TagId(std::uint16_t(11), std::uint16_t(2)), 0));
    EXPECT_EQ(tagVR_t::UN, privateHandler.getDataType());

    size_t length;
    std::string privateString(privateHandler.data(&length));
    EXPECT_EQ("Private tag ", privateString); // Even length
}


TEST(dicomCodecTest, testExternalStream)
{
    // Save a big file
    const std::string fileName(::tests::settings::getSettings().getTempFileName());
    {
        FileStreamOutput writeFile(fileName);
        char buffer[1024];
        for(size_t resetBuffer(0); resetBuffer != sizeof(buffer); ++resetBuffer)
        {
            buffer[resetBuffer] = (char)(resetBuffer & 0xffu);
        }

        StreamWriter writer(writeFile);

        for(size_t writeKb(0); writeKb != 1024; ++writeKb)
        {
            writer.write(buffer, sizeof(buffer));
        }
    }

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

        std::cout << "Dicom test. Transfer syntax: " << transferSyntax << std::endl;

        const std::string dataSetFileName(::tests::settings::getSettings().getTempFileName());
        {

            DataSet testDataSet(transferSyntax);
            Tag streamTag = testDataSet.getTagCreate(TagId(0x20, 0x20), tagVR_t::OB);
            FileStreamInput input(fileName);
            streamTag.setStream(0, input);

            CodecFactory::save(testDataSet, dataSetFileName, codecType_t::dicom);
        }

        DataSet testDataSet = CodecFactory::load(dataSetFileName);

        EXPECT_EQ(1024u * 1024u, testDataSet.getTag(TagId(0x20, 0x20)).getBufferSize(0));

        StreamReader reader = testDataSet.getTag(TagId(0x20, 0x20)).getStreamReader(0);
        size_t totalSize = 0;
        char buffer[1024];
        try
        {
            for(size_t readBytes = reader.readSome(buffer, sizeof(buffer)); readBytes != 0; readBytes = reader.readSome(buffer, sizeof(buffer)))
            {
                for(size_t scanBuffer(0); scanBuffer != readBytes; ++scanBuffer)
                {
                    EXPECT_EQ((char)(totalSize & 0xffu), buffer[scanBuffer]);
                    ++totalSize;
                }
            }
        }
        catch(const StreamEOFError&)
        {
        }
        EXPECT_EQ(1024u * 1024u, totalSize);
    }
}


TEST(dicomCodecTest, testExternalStreamOddSize)
{
    // Save a big file
    const std::string fileName(::tests::settings::getSettings().getTempFileName());
    {
        FileStreamOutput writeFile(fileName);
        char buffer[1024];
        for(size_t resetBuffer(0); resetBuffer != sizeof(buffer); ++resetBuffer)
        {
            buffer[resetBuffer] = (char)(resetBuffer & 0xffu);
        }

        StreamWriter writer(writeFile);

        writer.write(buffer, sizeof(buffer));

        static char oddByte(30);
        writer.write(&oddByte, 1);
    }

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

        std::cout << "Dicom test. Transfer syntax: " << transferSyntax << std::endl;

        std::string dataSetFileName(::tests::settings::getSettings().getTempFileName());
        {

            DataSet testDataSet(transferSyntax);
            Tag streamTag = testDataSet.getTagCreate(TagId(0x20, 0x20), tagVR_t::OB);
            FileStreamInput input(fileName);
            streamTag.setStream(0, input);

            CodecFactory::save(testDataSet, dataSetFileName, codecType_t::dicom);
        }

        DataSet testDataSet = CodecFactory::load(dataSetFileName);

        EXPECT_EQ(1026u, testDataSet.getTag(TagId(0x20, 0x20)).getBufferSize(0));

        StreamReader reader = testDataSet.getTag(TagId(0x20, 0x20)).getStreamReader(0);
        char buffer[1026];

        reader.read(buffer, sizeof(buffer));

        for(size_t scanBuffer(0); scanBuffer != 1024; ++scanBuffer)
        {
            EXPECT_EQ((char)(scanBuffer & 0xffu), buffer[scanBuffer]);
        }
        EXPECT_EQ(30, buffer[1024]);
        EXPECT_EQ(0, buffer[1025]);
    }
}


TEST(dicomCodecTest, testOverlay)
{
    for(std::uint32_t sizeX(201); sizeX != 203; ++sizeX)
    {
        for(std::uint32_t sizeY(151); sizeY != 153; ++sizeY)
        {
            for(int transferSyntaxId(3); transferSyntaxId != 4; ++transferSyntaxId)
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

                std::vector<Image> images;

                images.push_back(buildImageForTest(
                        sizeX,
                        sizeY,
                        bitDepth_t::depthU8,
                        0,
                        "MONOCHROME2", 2));
                images.push_back(buildImageForTest(
                        sizeX,
                        sizeY,
                        bitDepth_t::depthU8,
                        0,
                        "MONOCHROME2", 100));
                images.push_back(buildImageForTest(
                        sizeX,
                        sizeY,
                        bitDepth_t::depthU8,
                        0,
                        "MONOCHROME2", 150));

                Overlay overlay0(overlayType_t::graphic, "SUBTYPE0", 2, 5, 6, "LABEL0", "Description0");
                overlay0.setImage(0, images[0]);
                overlay0.setImage(1, images[1]);
                overlay0.setROIArea(120);

                Overlay overlay1(overlayType_t::ROI, "SUBTYPE1", 0, 5, 6, L"LABEL1", L"Description1");
                overlay1.setImage(0, images[2]);
                overlay1.setROIMean(3.0);
                overlay1.setROIStandardDeviation(1.0);

                std::cout << "Dicom test. Transfer syntax: " << transferSyntax;
                std::cout << " size: " << sizeX << " X " << sizeY << std::endl;

                MutableMemory streamMemory;
                {
                    DataSet testDataSet(transferSyntax);
                    {
                        WritingDataHandler writingDataHandler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0);
                        writingDataHandler.setString(0, "AAAaa");
                        writingDataHandler.setString(1, "BBBbbb");
                        writingDataHandler.setString(2, "");
                    }
                    testDataSet.setOverlay(0, overlay0);
                    testDataSet.setOverlay(1, overlay1);

                    MemoryStreamOutput memoryOutput(streamMemory);
                    StreamWriter writer(memoryOutput);
                    CodecFactory::save(testDataSet, writer, codecType_t::dicom);
                }

                for(unsigned int lazyLoad(0); lazyLoad != 2; ++lazyLoad)
                {
                    MemoryStreamInput readStream(streamMemory);
                    StreamReader reader(readStream);
                    DataSet testDataSet = CodecFactory::load(reader, lazyLoad == 0 ? std::numeric_limits<size_t>::max() : 1);

                    EXPECT_EQ(std::string(DICOMHERO_IMPLEMENTATION_CLASS_UID), testDataSet.getString(TagId(tagId_t::ImplementationClassUID_0002_0012), 0));
                    EXPECT_EQ(std::string(DICOMHERO_IMPLEMENTATION_NAME), testDataSet.getString(TagId(tagId_t::ImplementationVersionName_0002_0013), 0));

                    EXPECT_EQ(0u, testDataSet.getUint32(TagId(tagId_t::FileMetaInformationVersion_0002_0001), 0));
                    EXPECT_EQ(1u, testDataSet.getUint32(TagId(tagId_t::FileMetaInformationVersion_0002_0001), 1));
                    EXPECT_THROW(testDataSet.getUint32(TagId(tagId_t::FileMetaInformationVersion_0002_0001), 2), MissingItemError);
                    EXPECT_EQ(tagVR_t::OB, testDataSet.getDataType(TagId(tagId_t::FileMetaInformationVersion_0002_0001)));

                    EXPECT_EQ(std::string("AAAaa"), testDataSet.getString(TagId(dicomhero::tagId_t::PatientName_0010_0010), 0));
                    EXPECT_EQ(std::string("BBBbbb"), testDataSet.getString(TagId(dicomhero::tagId_t::PatientName_0010_0010), 1));
                    EXPECT_EQ(std::string(""), testDataSet.getString(TagId(dicomhero::tagId_t::PatientName_0010_0010), 2));

                    for(unsigned int repeatLazyLoad(0); repeatLazyLoad != lazyLoad + 1; ++ repeatLazyLoad)
                    {
                        Overlay checkOverlay0 = testDataSet.getOverlay(0);
                        ASSERT_TRUE(identicalImages(images[0], checkOverlay0.getImage(0)));
                        ASSERT_TRUE(identicalImages(images[1], checkOverlay0.getImage(1)));
                        ASSERT_EQ(overlayType_t::graphic, checkOverlay0.getType());
                        ASSERT_EQ("SUBTYPE0", checkOverlay0.getSubType());
                        ASSERT_EQ(2u, checkOverlay0.getFirstFrame());
                        ASSERT_EQ(120u, checkOverlay0.getROIArea());
                        ASSERT_THROW(checkOverlay0.getROIMean(), MissingTagError);
                        ASSERT_THROW(checkOverlay0.getROIStandardDeviation(), MissingTagError);
                        ASSERT_EQ("LABEL0", overlay0.getLabel());
                        ASSERT_EQ(L"LABEL0", overlay0.getUnicodeLabel());
                        ASSERT_EQ("Description0", overlay0.getDescription());
                        ASSERT_EQ(L"Description0", overlay0.getUnicodeDescription());
                        ASSERT_EQ(5, overlay0.getZeroBasedOriginX());
                        ASSERT_EQ(6, overlay0.getZeroBasedOriginY());
                        ASSERT_EQ(6, overlay0.getOneBasedOriginX());
                        ASSERT_EQ(7, overlay0.getOneBasedOriginY());

                        Overlay checkOverlay1 = testDataSet.getOverlay(1);
                        ASSERT_TRUE(identicalImages(images[2], checkOverlay1.getImage(0)));
                        ASSERT_EQ(overlayType_t::ROI, checkOverlay1.getType());
                        ASSERT_EQ("SUBTYPE1", checkOverlay1.getSubType());
                        ASSERT_THROW(checkOverlay1.getROIArea(), MissingTagError);
                        ASSERT_DOUBLE_EQ(3.0, checkOverlay1.getROIMean());
                        ASSERT_DOUBLE_EQ(1.0, checkOverlay1.getROIStandardDeviation());
                        ASSERT_EQ("LABEL1", overlay1.getLabel());
                        ASSERT_EQ(L"LABEL1", overlay1.getUnicodeLabel());
                        ASSERT_EQ("Description1", overlay1.getDescription());
                        ASSERT_EQ(L"Description1", overlay1.getUnicodeDescription());
                        ASSERT_EQ(5, overlay1.getZeroBasedOriginX());
                        ASSERT_EQ(6, overlay1.getZeroBasedOriginY());
                        ASSERT_EQ(6, overlay1.getOneBasedOriginX());
                        ASSERT_EQ(7, overlay1.getOneBasedOriginY());

                        ASSERT_THROW(testDataSet.getOverlay(2), MissingGroupError);

                    }
                }
            } // transferSyntaxId
        }
    }
}


TEST(dicomCodecTest, unrecognizedTagExplicitVR)
{
    DataSet dataset(uidExplicitVRLittleEndian_1_2_840_10008_1_2_1);

    dataset.setString(TagId(tagId_t::PatientName_0010_0010), "Test Patient Name");
    dataset.setString(TagId(tagId_t::PatientAddress_0010_1040), "Test Patient Address");

    {
        DataSet sequence = dataset.appendSequenceItem(TagId(tagId_t::OtherPatientIDsSequence_0010_1002));
        sequence.setString(TagId(tagId_t::PatientName_0010_0010), "Test Patient Name 1");
        sequence.setString(TagId(tagId_t::PatientAddress_0010_1040), "Test Patient Address 1");
    }

    MutableMemory memory;
    MemoryStreamOutput outputMemory(memory);
    StreamWriter memoryWriter(outputMemory);
    CodecFactory::save(dataset, memoryWriter, codecType_t::dicom);

    // Replace LO with AA (unrecognized VR)
    size_t dataSize;
    std::string modifiedFile(reinterpret_cast<const char*>(memory.data(&dataSize)), memory.size());
    for(size_t loPosition = modifiedFile.find("LO"); loPosition != std::string::npos; loPosition = modifiedFile.find("LO"))
    {
        modifiedFile.replace(loPosition, 2, "AA");
    }

    Memory modifiedFileMemory(modifiedFile.data(), modifiedFile.size());
    MemoryStreamInput inputMemory(modifiedFileMemory);
    StreamReader memoryReader(inputMemory);
    DataSet readDataset(CodecFactory::load(memoryReader));

    {
        ASSERT_EQ("Test Patient Name", readDataset.getString(TagId(tagId_t::PatientName_0010_0010), 0));
        ReadingDataHandlerNumeric unknownTagHandler = readDataset.getReadingDataHandlerNumeric(TagId(tagId_t::PatientAddress_0010_1040), 0);
        std::string testContent(20u, ' ');
        unknownTagHandler.data(&(testContent[0]), testContent.size());
        ASSERT_EQ(tagVR_t::UN, unknownTagHandler.getDataType());
        ASSERT_EQ("Test Patient Address", testContent);
    }

    {
        ASSERT_EQ("Test Patient Name 1", readDataset.getSequenceItem(TagId(tagId_t::OtherPatientIDsSequence_0010_1002), 0).getString(TagId(tagId_t::PatientName_0010_0010), 0));
        ReadingDataHandlerNumeric unknownTagHandler = readDataset.
                getSequenceItem(TagId(tagId_t::OtherPatientIDsSequence_0010_1002), 0).
                getReadingDataHandlerNumeric(TagId(tagId_t::PatientAddress_0010_1040), 0);
        std::string testContent(22u, ' ');
        unknownTagHandler.data(&(testContent[0]), testContent.size());
        ASSERT_EQ(tagVR_t::UN, unknownTagHandler.getDataType());
        ASSERT_EQ("Test Patient Address 1", testContent);
    }
}


#ifndef DISABLE_DCMTK_INTEROPERABILITY_TEST

TEST(dicomCodecInteroperabilityTest, dcmtkDicomImage)
{
    DcmRLEDecoderRegistration::registerCodecs();

    const char* const colorSpaces[] = {"MONOCHROME2", "RGB", "YBR_FULL", "YBR_FULL_422"};


    for(int transferSyntaxId(0); transferSyntaxId != 4; ++transferSyntaxId)
    {
        for(std::uint32_t interleaved(0); interleaved != 2; ++interleaved)
        {
            for(std::uint32_t highBit(0); highBit != 32; ++highBit)
            {
                for(unsigned int colorSpaceIndex(0); colorSpaceIndex != sizeof(colorSpaces)/sizeof(colorSpaces[0]); ++colorSpaceIndex)
                {
                    const std::string colorSpace(colorSpaces[colorSpaceIndex]);

                    const bool bSubsampledX(ColorTransformsFactory::isSubsampledX(colorSpace));
                    const bool bSubsampledY(ColorTransformsFactory::isSubsampledY(colorSpace));
                    if((highBit < 7 || highBit > 24 || interleaved == 0) &&
                            (bSubsampledX || bSubsampledY))
                    {
                        continue;
                    }

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

                    if(transferSyntax == "1.2.840.10008.1.2.5" && (interleaved == 1 || bSubsampledX || bSubsampledY || highBit < 7))
                    {
                        continue;
                    }

                    const std::uint32_t sizeX(bSubsampledX ? 202 : 201);
                    const std::uint32_t sizeY(bSubsampledY ? 152 : 151);

                    bitDepth_t depth(bitDepth_t::depthU8);
                    if(highBit > 7)
                    {
                        depth = bitDepth_t::depthU16;
                    }
                    if(highBit > 15)
                    {
                        depth = bitDepth_t::depthU32;
                    }

                    std::vector<Image> images;

                    if(bSubsampledY || bSubsampledX)
                    {
                        images.push_back(buildSubsampledImage(
                                sizeX,
                                sizeY,
                                depth,
                                highBit,
                                colorSpace));
                        images.push_back(buildSubsampledImage(
                                sizeX,
                                sizeY,
                                depth,
                                highBit,
                                colorSpace));
                        images.push_back(buildSubsampledImage(
                                sizeX,
                                sizeY,
                                depth,
                                highBit,
                                colorSpace));
                    }
                    else
                    {
                        images.push_back(buildImageForTest(
                                sizeX,
                                sizeY,
                                depth,
                                highBit,
                                colorSpace,
                                2));
                        images.push_back(buildImageForTest(
                                sizeX,
                                sizeY,
                                depth,
                                highBit,
                                colorSpace,
                                100));
                        images.push_back(buildImageForTest(
                                sizeX,
                                sizeY,
                                depth,
                                highBit,
                                colorSpace,
                                150));
                    }

                    EXPECT_EQ(highBit, images[0].getHighBit());
                    EXPECT_EQ(highBit, images[1].getHighBit());
                    EXPECT_EQ(highBit, images[2].getHighBit());

                    std::cout << "Transfer syntax: " << transferSyntax << std::endl;
                    std::cout << " size: " << sizeX << " by " << sizeY << std::endl;
                    std::cout << " interleaved: " << interleaved;
                    std::cout << " highBit: " << highBit << std::endl;
                    std::cout << " colorSpace: " << colorSpace << std::endl;

                    imageQuality_t quality = imageQuality_t::veryHigh;
                    if(bSubsampledY)
                    {
                        quality = imageQuality_t::belowMedium;
                    }
                    else if(bSubsampledX)
                    {
                        quality = imageQuality_t::medium;
                    }

                    MutableMemory streamMemory;
                    {
                        DataSet testDataSet(transferSyntax);
                        {
                            WritingDataHandler writingDataHandler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0);
                            writingDataHandler.setString(0, "AAAaa");
                            writingDataHandler.setString(1, "BBBbbb");
                            writingDataHandler.setString(2, "");
                        }
                        testDataSet.setDouble(TagId(tagId_t::TimeRange_0008_1163), 50.6);
                        if(ColorTransformsFactory::getNumberOfChannels(colorSpace) > 1)
                        {
                            testDataSet.setUint32(TagId(dicomhero::tagId_t::PlanarConfiguration_0028_0006), 1 - interleaved);
                        }
                        testDataSet.setImage(0, images[0], quality);
                        testDataSet.setImage(1, images[1], quality);
                        testDataSet.setImage(2, images[2], quality);

                        tagVR_t vr = testDataSet.getDataType(TagId(tagId_t::PixelData_7FE0_0010));
                        ASSERT_TRUE(vr == tagVR_t::OB || vr == tagVR_t::OW);

                        DataSet sequenceItem = testDataSet.appendSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111));
                        sequenceItem.setString(TagId(tagId_t::PatientName_0010_0010), "test test");

                        DataSet sequenceItem1 = sequenceItem.appendSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111));
                        sequenceItem1.setString(TagId(tagId_t::PatientName_0010_0010), "test test1");

                        if(highBit == 0)
                        {
                            ASSERT_EQ(1u, testDataSet.getUint32(TagId(tagId_t::BitsAllocated_0028_0100), 0));
                        }

                        MemoryStreamOutput writeStream(streamMemory);
                        StreamWriter writer(writeStream);
                        CodecFactory::save(testDataSet, writer, codecType_t::dicom);

                        std::cout << " bits allocated: " << testDataSet.getUint32(TagId(tagId_t::BitsAllocated_0028_0100), 0) << std::endl;

                    }

                    // Read with DCMTK
                    DcmInputBufferStream dcmtkStream;
                    size_t dataSize(0);
                    char* data = streamMemory.data(&dataSize);
                    dcmtkStream.setBuffer(data, (offile_off_t)dataSize);
                    dcmtkStream.setEos();

                    DcmFileFormat dcmtkDataSet;
                    dcmtkDataSet.transferInit();
                    const OFCondition cond = dcmtkDataSet.read(dcmtkStream, EXS_Unknown);
                    dcmtkDataSet.transferEnd();

                    DicomImage dcmtkImages(&dcmtkDataSet, EXS_Unknown, CIF_KeepYCbCrColorModel);

                    Image checkImage0(sizeX, sizeY, depth, colorSpace, highBit);
                    {
                        size_t checkImageSize(0);
                        WritingDataHandlerNumeric writingHandler(checkImage0.getWritingDataHandler());
                        char* checkImageData(writingHandler.data(&checkImageSize));
                        dcmtkImages.getOutputData(checkImageData, checkImageSize, 0, 0, 0);

                    }
                    EXPECT_TRUE(identicalImages(checkImage0, images[0]));

                    Image checkImage1(sizeX, sizeY, depth, colorSpace, highBit);
                    {
                        size_t checkImageSize(0);
                        WritingDataHandlerNumeric writingHandler(checkImage1.getWritingDataHandler());
                        char* checkImageData(writingHandler.data(&checkImageSize));
                        dcmtkImages.getOutputData(checkImageData, checkImageSize, 0, 1, 0);
                    }
                    EXPECT_TRUE(identicalImages(checkImage1, images[1]));

                    Image checkImage2(sizeX, sizeY, depth, colorSpace, highBit);
                    {
                        size_t checkImageSize(0);
                        WritingDataHandlerNumeric writingHandler(checkImage2.getWritingDataHandler());
                        char* checkImageData(writingHandler.data(&checkImageSize));
                        dcmtkImages.getOutputData(checkImageData, checkImageSize, 0, 2, 0);
                    }
                    EXPECT_TRUE(identicalImages(checkImage2, images[2]));
                }
            }
        }
    } // transferSyntaxId
}


TEST(dicomCodecInteroperabilityTest, dcmtkDicomOverlay)
{
    DcmRLEDecoderRegistration::registerCodecs();

    std::uint32_t sizeX(151);
    std::uint32_t sizeY(101);
    for(int transferSyntaxId(0); transferSyntaxId != 4; ++transferSyntaxId)
    {
        std::uint32_t highBit(7);
        const std::string colorSpace("MONOCHROME2");

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

        Image image(sizeX, sizeY, bitDepth_t::depthU8, colorSpace, 7);
        {
            // The writing handler allocates the memory
            image.getWritingDataHandler();
        }

        Image overlayImage0 = buildImageForTest(
                sizeX,
                sizeY,
                bitDepth_t::depthU8,
                0,
                "MONOCHROME2", 100);
        Image overlayImage1 = buildImageForTest(
                    sizeX,
                    sizeY,
                bitDepth_t::depthU8,
                0,
                "MONOCHROME2", 150);

        std::cout << "Transfer syntax: " << transferSyntax << std::endl;
        std::cout << " size: " << sizeX << " by " << sizeY << std::endl;

        imageQuality_t quality = imageQuality_t::veryHigh;

        MutableMemory streamMemory;
        {
            DataSet testDataSet(transferSyntax);
            {
                WritingDataHandler writingDataHandler = testDataSet.getWritingDataHandler(TagId(0x0010, 0x0010), 0);
                writingDataHandler.setString(0, "AAAaa");
                writingDataHandler.setString(1, "BBBbbb");
                writingDataHandler.setString(2, "");
            }
            testDataSet.setDouble(TagId(tagId_t::TimeRange_0008_1163), 50.6);
            if(ColorTransformsFactory::getNumberOfChannels(colorSpace) > 1)
            {
                testDataSet.setUint32(TagId(dicomhero::tagId_t::PlanarConfiguration_0028_0006), 1);
            }
            testDataSet.setImage(0, image, quality);

            tagVR_t vr = testDataSet.getDataType(TagId(tagId_t::PixelData_7FE0_0010));
            ASSERT_TRUE(vr == tagVR_t::OB || vr == tagVR_t::OW);

            DataSet sequenceItem = testDataSet.appendSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111));
            sequenceItem.setString(TagId(tagId_t::PatientName_0010_0010), "test test");

            DataSet sequenceItem1 = sequenceItem.appendSequenceItem(TagId(tagId_t::ReferencedPerformedProcedureStepSequence_0008_1111));
            sequenceItem1.setString(TagId(tagId_t::PatientName_0010_0010), "test test1");

            if(highBit == 0)
            {
                ASSERT_EQ(1u, testDataSet.getUint32(TagId(tagId_t::BitsAllocated_0028_0100), 0));
            }

            Overlay overlay(overlayType_t::graphic, "SUBTYPE0", 0, 0, 0, "LABEL0", "Description0");
            overlay.setImage(0, overlayImage0);
            overlay.setImage(1, overlayImage1);
            overlay.setROIArea(120);
            testDataSet.setOverlay(0, overlay);

            MemoryStreamOutput writeStream(streamMemory);
            StreamWriter writer(writeStream);
            CodecFactory::save(testDataSet, writer, codecType_t::dicom);

            std::cout << " bits allocated: " << testDataSet.getUint32(TagId(tagId_t::BitsAllocated_0028_0100), 0) << std::endl;

        }

        // Read with DCMTK
        DcmInputBufferStream dcmtkStream;
        size_t dataSize(0);
        char* data = streamMemory.data(&dataSize);
        dcmtkStream.setBuffer(data, (offile_off_t)dataSize);
        dcmtkStream.setEos();

        DcmFileFormat dcmtkDataSet;
        dcmtkDataSet.transferInit();
        const OFCondition cond = dcmtkDataSet.read(dcmtkStream, EXS_Unknown);
        dcmtkDataSet.transferEnd();

        DicomImage dcmtkImages(&dcmtkDataSet, EXS_Unknown, CIF_KeepYCbCrColorModel);

        unsigned int posX, posY;
        unsigned int overlayWidth, overlayHeight;
        EM_Overlay overlayMode;
        const void* checkOverlay0Data = dcmtkImages.getOverlayData(0, posX, posY, overlayWidth, overlayHeight, overlayMode, 0, 8u, 1u, 0);
        EXPECT_EQ(sizeX, overlayWidth);
        EXPECT_EQ(sizeY, overlayHeight);
        Image checkOverlayImage0(overlayWidth, overlayHeight, bitDepth_t::depthU8, "MONOCHROME2", 0);
        {
            WritingDataHandlerNumeric writingHandler(checkOverlayImage0.getWritingDataHandler());
            size_t dataSize(0);
            char* imageData = writingHandler.data(&dataSize);
            ::memcpy(imageData, checkOverlay0Data, writingHandler.getSize());
        }
        EXPECT_TRUE(identicalImages(overlayImage0, checkOverlayImage0));

        const void* checkOverlay1Data = dcmtkImages.getOverlayData(0, posX, posY, overlayWidth, overlayHeight, overlayMode, 1, 8u, 1u, 0);
        Image checkOverlayImage1(overlayWidth, overlayHeight, bitDepth_t::depthU8, "MONOCHROME2", 0);
        {
            WritingDataHandlerNumeric writingHandler(checkOverlayImage1.getWritingDataHandler());
            size_t dataSize(0);
            char* imageData = writingHandler.data(&dataSize);
            ::memcpy(imageData, checkOverlay1Data, writingHandler.getSize());
        }
        EXPECT_TRUE(identicalImages(overlayImage1, checkOverlayImage1));

    } // transferSyntaxId
}

#endif // DISABLE_DCMTK_INTEROPERABILITY_TEST


} // namespace tests

} // namespace dicomhero

