#include <imebra/imebra.h>
#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <functional>

namespace imebra
{

namespace tests
{

void feedDataThread(PipeStream& source, size_t maxBlockBytes, unsigned int delayMs, unsigned int closeWait)
{
    {
        StreamWriter writer(source.getStreamOutput());
        for(size_t blockBytes(1); blockBytes != maxBlockBytes; ++blockBytes)
        {

            std::vector<std::uint8_t> values(blockBytes);
            for(size_t resetBlock(0); resetBlock != blockBytes; ++resetBlock)
            {
                values[resetBlock] = (std::uint8_t)(resetBlock & 0xff);
            }
            Memory block((char*)values.data(), blockBytes);
            writer.write(block);
            if(delayMs != 0)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(delayMs));
            }
        }
    }
    source.close(closeWait);
}

TEST(pipeTest, sendReceive)
{
    PipeStream source(1024);

    size_t maxBlockBytes(3000);
    std::thread feedData(imebra::tests::feedDataThread, std::ref(source), maxBlockBytes, 0, 1000);

    std::string buffer;

    StreamReader reader(source.getStreamInput());

    for(size_t blockBytes(1); blockBytes != maxBlockBytes; ++blockBytes)
    {
        while(buffer.size() < blockBytes)
        {
            Memory block = reader.readSome(blockBytes);
            size_t blockSize;
            const char* pData(block.data(&blockSize));
            buffer.append(pData, blockSize);

        }
        for(size_t checkBlock(0); checkBlock != blockBytes; ++checkBlock)
        {
            ASSERT_EQ((std::uint8_t)(checkBlock & 0xff), (std::uint8_t)(buffer[checkBlock]));
        }
        buffer.erase(0, blockBytes);
    }
    feedData.join();
}


void feedDataThreadAligned(PipeStream& source, size_t blockBytes, unsigned int closeWait)
{
    {
        StreamWriter writer(source.getStreamOutput());

        std::vector<std::uint8_t> values(blockBytes);
        for(size_t resetBlock(0); resetBlock != blockBytes; ++resetBlock)
        {
            values[resetBlock] = (std::uint8_t)(resetBlock & 0xff);
        }
        Memory block((char*)values.data(), blockBytes);
        writer.write(block);
    }
    source.close(closeWait);
}

TEST(pipeTest, sendReceiveAligned)
{
    PipeStream source(20);

    std::thread feedData(imebra::tests::feedDataThreadAligned, std::ref(source), 20, 20);

    std::string buffer;

    StreamReader reader(source.getStreamInput());

    Memory block = reader.readSome(20);
    size_t blockSize;
    const char* pData(block.data(&blockSize));
    buffer.append(pData, blockSize);
    ASSERT_EQ(20u, blockSize);

    for(size_t checkBlock(0); checkBlock != 20; ++checkBlock)
    {
        ASSERT_EQ((std::uint8_t)(checkBlock & 0xff), (std::uint8_t)(buffer[checkBlock]));
    }

    try
    {
        Memory blockEof = reader.readSome(20);
        EXPECT_TRUE(false);
    }
    catch (const StreamClosedError& e)
    {
        EXPECT_TRUE(false);
    }
    catch (const StreamEOFError& e)
    {
        EXPECT_TRUE(true);
    }
    catch(...)
    {
        EXPECT_TRUE(false);
    }

    feedData.join();
}

TEST(pipeTest, sendReceiveCloseAndWait)
{
    PipeStream source(1024);

    size_t maxBlockBytes(5);
    std::thread feedData(imebra::tests::feedDataThread, std::ref(source), maxBlockBytes, 0, 10000);

    std::string buffer;

    StreamReader reader(source.getStreamInput());

    for(size_t blockBytes(1); blockBytes != maxBlockBytes; ++blockBytes)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        while(buffer.size() < blockBytes)
        {
            Memory block = reader.read(maxBlockBytes);
            size_t blockSize;
            const char* pData(block.data(&blockSize));
            buffer.append(pData, blockSize);

        }
        for(size_t checkBlock(0); checkBlock != blockBytes; ++checkBlock)
        {
            ASSERT_EQ((std::uint8_t)(checkBlock & 0xff), (std::uint8_t)(buffer[checkBlock]));
        }
        buffer.erase(0, blockBytes);
    }
    feedData.join();
}


TEST(pipeTest, sendReceiveCloseNoWait)
{
    PipeStream source(1024);

    size_t maxBlockBytes(5);
    std::thread feedData(imebra::tests::feedDataThread, std::ref(source), maxBlockBytes, 0, 0);

    std::string buffer;

    StreamReader reader(source.getStreamInput());

    try
    {
        for(size_t blockBytes(1); blockBytes != maxBlockBytes; ++blockBytes)
        {
            std::this_thread::sleep_for(std::chrono::seconds(5));
            while(buffer.size() < blockBytes)
            {
                Memory block = reader.read(maxBlockBytes);
                size_t blockSize;
                const char* pData(block.data(&blockSize));
                buffer.append(pData, blockSize);

            }
            for(size_t checkBlock(0); checkBlock != blockBytes; ++checkBlock)
            {
                ASSERT_EQ((std::uint8_t)(checkBlock & 0xff), (std::uint8_t)(buffer[checkBlock]));
            }
            buffer.erase(0, blockBytes);
        }
        EXPECT_TRUE(false);
    }
    catch(const imebra::StreamClosedError&)
    {
        EXPECT_TRUE(true);
    }
    catch(...)
    {
        EXPECT_TRUE(false);
    }

    feedData.join();
}


void feedDatasetThread(PipeStream& source, DataSet& dataSet, unsigned int closeWait)
{
    StreamWriter writer(source.getStreamOutput());

    CodecFactory::save(dataSet, writer, codecType_t::dicom);

    source.close(closeWait);
}


TEST(pipeTest, sendReceiveDataSet)
{
    PipeStream source(1024);

    MutableDataSet testDataSet;

    testDataSet.setString(TagId(tagId_t::PatientName_0010_0010), "TEST PATIENT");

    std::thread feedData(imebra::tests::feedDatasetThread, std::ref(source), std::ref(testDataSet), 5000);


    StreamReader reader(source.getStreamInput());

    DataSet receivedDataSet(CodecFactory::load(reader));

    ASSERT_EQ(testDataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0), receivedDataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0));

    feedData.join();
}

} // namespace tests

} // namespace imebra
