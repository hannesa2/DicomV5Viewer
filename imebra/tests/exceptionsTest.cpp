#include <gtest/gtest.h>
#include <imebra/imebra.h>
#include <array>
#include <thread>
#include <chrono>

namespace imebra
{

namespace tests
{

void exceptionsThread(size_t exceptionType)
{
    try
    {
        switch(exceptionType)
        {
        case 0:
            CodecFactory::load("\\nonExistentFile___##$$$", 2);
            break;
        case 1:
            MutableDataSet test;
            test.getString(TagId(16, 16), 0);
        }
    }
    catch(...)
    {
        std::this_thread::sleep_for(std::chrono::seconds(2));
        switch(exceptionType)
        {
        case 0:
            {
                std::string trace = ExceptionsManager::getExceptionTrace();
                EXPECT_TRUE(trace.find("StreamOpenError") != std::string::npos);
                EXPECT_TRUE(trace.find("CodecFactory") != std::string::npos);
                EXPECT_TRUE(trace.find("MissingBufferError") == std::string::npos);
                EXPECT_TRUE(trace.find("getString") == std::string::npos);
                break;
            }
        case 1:
            {
                std::string trace = ExceptionsManager::getExceptionTrace();
                EXPECT_TRUE(trace.find("StreamOpenError") == std::string::npos);
                EXPECT_TRUE(trace.find("CodecFactory") == std::string::npos);
                EXPECT_TRUE(trace.find("MissingGroupError") != std::string::npos);
                EXPECT_TRUE(trace.find("getString") != std::string::npos);
                break;
            }
        }

    }

    try
    {
        CodecFactory::load("\\nonExistentFile___##$$$", 2);
    }
    catch(...)
    {
        std::string trace = ExceptionsManager::getExceptionTrace();
        EXPECT_TRUE(trace.find("StreamOpenError") != std::string::npos);
        EXPECT_TRUE(trace.find("CodecFactory") != std::string::npos);
    }

}

// A buffer initialized to a default data type should use the data type OB
TEST(exceptionsTest, testExceptions)
{
    std::array<std::unique_ptr<std::thread>, 2> threads;
    for(size_t initializeThreads(0); initializeThreads != threads.size(); ++initializeThreads)
    {
        threads[initializeThreads].reset(new std::thread(exceptionsThread, initializeThreads));
    }

    for(size_t joinThreads(0); joinThreads != threads.size(); ++joinThreads)
    {
        threads[joinThreads]->join();
    }
}


TEST(exceptionsTest, testAutomaticClear)
{
    try
    {
        CodecFactory::load("\\nonExistentFile___##$$$", 2);
    }
    catch(...)
    {
    }

    try
    {
        MutableDataSet test;
        test.getString(TagId(16, 16), 0);
    }
    catch(...)
    {
        std::string trace = ExceptionsManager::getExceptionTrace();
        EXPECT_TRUE(trace.find("StreamOpenError") == std::string::npos);
        EXPECT_TRUE(trace.find("CodecFactory") == std::string::npos);
        EXPECT_TRUE(trace.find("MissingGroupError") != std::string::npos);
        EXPECT_TRUE(trace.find("getString") != std::string::npos);
    }
}


} // namespace tests

} // namespace imebra

