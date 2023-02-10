#include <gtest/gtest.h>
#include <imebra/imebra.h>

namespace imebra
{

namespace tests
{


// Test implementation of streamReader::readSome
TEST(streamTest, testReadSome)
{
    MutableMemory memory;
    MemoryStreamOutput memoryOutput(memory);

    {
        StreamWriter memoryWriter(memoryOutput);

        MutableDataSet testDataSet("1.2.840.10008.1.2.1");
        testDataSet.setString(TagId(tagId_t::PatientName_0010_0010), "Test Patient");

        CodecFactory::save(testDataSet, memoryWriter, codecType_t::dicom);
    }

    MemoryStreamInput memoryInput(memory);
    StreamReader memoryReader(memoryInput);
    DataSet dataSet = CodecFactory::load(memoryReader);
    ASSERT_EQ("Test Patient", dataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0));

    ASSERT_THROW(CodecFactory::load(memoryReader), StreamEOFError);
}


// Test implementation of streamReader::readSome
TEST(streamTest, testVirtualStream)
{
    MutableMemory memory;

    size_t size0, size1, size2;

    {
        MemoryStreamOutput memoryOutput(memory);
        StreamWriter memoryWriter(memoryOutput);
        {

            MutableDataSet testDataSet("1.2.840.10008.1.2.1");
            testDataSet.setString(TagId(tagId_t::PatientName_0010_0010), "Test Patient0");

            CodecFactory::save(testDataSet, memoryWriter, codecType_t::dicom);

            size0 = memory.size();
        }

        {
            MutableDataSet testDataSet("1.2.840.10008.1.2.1");
            testDataSet.setString(TagId(tagId_t::PatientName_0010_0010), "Test Patient1");

            CodecFactory::save(testDataSet, memoryWriter, codecType_t::dicom);

            size1 = memory.size() - size0;
        }

        {
            MutableDataSet testDataSet("1.2.840.10008.1.2.1");
            testDataSet.setString(TagId(tagId_t::PatientName_0010_0010), "Test Patient2");

            CodecFactory::save(testDataSet, memoryWriter, codecType_t::dicom);

            size2 = memory.size() - size1 - size0;
        }
    }

    MemoryStreamInput memoryInput(memory);
    StreamReader memoryReader(memoryInput);

    {
        StreamReader virtualReader = memoryReader.getVirtualStream(size0);
        DataSet dataSet = CodecFactory::load(virtualReader);
        ASSERT_EQ("Test Patient0", dataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0));
    }

    {
        StreamReader virtualReader = memoryReader.getVirtualStream(size1);
        DataSet dataSet = CodecFactory::load(virtualReader);
        ASSERT_EQ("Test Patient1", dataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0));
    }

    {
        StreamReader virtualReader = memoryReader.getVirtualStream(size2);
        DataSet dataSet = CodecFactory::load(virtualReader);
        ASSERT_EQ("Test Patient2", dataSet.getString(TagId(tagId_t::PatientName_0010_0010), 0));
    }
}


// Test the StreamTimeout class
TEST(streamTest, testTimeout)
{
    std::string string;
    try
    {
        PipeStream pipe(1024);

        BaseStreamInput input(pipe.getStreamInput());
        StreamReader reader(input);
        {
            StreamWriter writer(pipe.getStreamOutput());

            StreamTimeout timeout(input, 2);

            Memory input1("ABCD", 4);
            writer.write(input1);
            writer.flush();

            Memory readData = reader.read(input1.size());
            size_t dataSize;
            const char* data(readData.data(&dataSize));
            string += std::string(data, dataSize);
            reader.read(4);
        }
        EXPECT_TRUE(false);
    }
    catch(const StreamEOFError&)
    {
    }
    EXPECT_EQ("ABCD", string);
}


// Test the StreamTimeout class
TEST(streamTest, testTimeout1)
{
    std::string string;
    try
    {
        PipeStream pipe(1024);

        BaseStreamInput input(pipe.getStreamInput());
        StreamReader reader(input);
        {
            StreamWriter writer(pipe.getStreamOutput());
            StreamTimeout timeout(input, 20000000);

            Memory input1("ABCD", 4);
            writer.write(input1);
            writer.flush();

            Memory readData = reader.read(4);
            size_t dataSize;
            const char* data(readData.data(&dataSize));
            string += std::string(data, dataSize);
        }
    }
    catch(const StreamEOFError&)
    {
        EXPECT_TRUE(false);
    }
    EXPECT_EQ("ABCD", string);
}

} // namespace tests

} // namespace imebra

