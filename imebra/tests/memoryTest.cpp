#include <gtest/gtest.h>
#include <imebra/imebra.h>
#include <thread>
#include <array>
#include <chrono>

namespace imebra
{

namespace tests
{

void memoryThread(size_t minSize, size_t maxSize)
{
    MemoryPool::setMemoryPoolSize(minSize, maxSize);

    // Wait for the other threads to settle. This is done to
    // check that every thread is using its own private MemoryPool
    // object
    //////////////////////////////////////////////////////////////
    std::this_thread::sleep_for(std::chrono::seconds(2));


    // Small memory chuncks should not go in the memory pool
    ////////////////////////////////////////////////////////
    {
        MutableMemory memory(1);
        size_t dataSize;
        *memory.data(&dataSize) = 2;
        EXPECT_EQ(1u, dataSize);
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_EQ(0u, MemoryPool::getUnusedMemorySize());

    // Check that released memory goes into the memory pool
    ///////////////////////////////////////////////////////
    {
        MutableMemory memory(minSize);
        size_t dataSize;
        char* pData = memory.data(&dataSize);
        for(size_t writeMemory(0); writeMemory != dataSize; ++writeMemory)
        {
            *pData = 3;
        }
    }
    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_EQ(minSize, MemoryPool::getUnusedMemorySize());
    MemoryPool::flush();
    EXPECT_EQ(0u, MemoryPool::getUnusedMemorySize());

    // Release memory and reallocate the same size: it should retrieve
    //  it from the memory pool
    //////////////////////////////////////////////////////////////////
    {
        MutableMemory memory(minSize);
        size_t dataSize;
        char* pData = memory.data(&dataSize);
        for(size_t writeMemory(0); writeMemory != dataSize; ++writeMemory)
        {
            *pData = 3;
        }
    }

    std::this_thread::sleep_for(std::chrono::seconds(2));
    EXPECT_EQ(minSize, MemoryPool::getUnusedMemorySize());
    {
        MutableMemory retrieveMemory(minSize);
        EXPECT_EQ(0u, MemoryPool::getUnusedMemorySize());
    }
    MemoryPool::flush();
    EXPECT_EQ(0u, MemoryPool::getUnusedMemorySize());

    // Release more memory than the memory pool can hold. Check how
    // much memory it keeps
    ///////////////////////////////////////////////////////////////
    for(size_t memorySize(minSize), totalAllocated(0); totalAllocated < maxSize + 100; ++memorySize)
    {
        MutableMemory memory(memorySize);
        totalAllocated += memorySize;
    }
    EXPECT_GT(MemoryPool::getUnusedMemorySize(), minSize);
    EXPECT_LE(MemoryPool::getUnusedMemorySize(), maxSize);
}

// Launch several threads each one testing its own MemoryPool object
TEST(memoryTest, testMemoryPool)
{
    std::array<std::unique_ptr<std::thread>, 3> threads;
    for(size_t initializeThreads(0); initializeThreads != threads.size(); ++initializeThreads)
    {
        threads[initializeThreads].reset(new std::thread(memoryThread, 100, 500));
    }

    for(size_t joinThreads(0); joinThreads != threads.size(); ++joinThreads)
    {
        threads[joinThreads]->join();
    }
}

TEST(memoryTest, readMemory)
{
    std::string testString("Test string");
    Memory readMemory(testString.c_str(), testString.size());
    ASSERT_EQ(testString.size(), readMemory.size());
    ASSERT_FALSE(readMemory.empty());

    size_t storedSize;
    const char* storedData(readMemory.data(&storedSize));
    ASSERT_EQ(testString.size(), storedSize);
    ASSERT_EQ(testString, std::string(storedData, storedSize));

    std::string getRegion("aa");
    ASSERT_THROW(readMemory.regionData(&(getRegion.at(0)), 2, testString.size() - 1), MemorySizeError);
    readMemory.regionData(&(getRegion.at(0)), 2, 2);
    ASSERT_EQ("st", getRegion);
}

TEST(memoryTest, readWriteMemory)
{
    std::string testString("Test string");
    MutableMemory readWriteMemory(testString.c_str(), testString.size());

    ASSERT_EQ(testString.size(), readWriteMemory.size());
    ASSERT_FALSE(readWriteMemory.empty());

    size_t storedSize;
    const char* storedData(readWriteMemory.data(&storedSize));
    ASSERT_EQ(testString.size(), storedSize);
    ASSERT_EQ(testString, std::string(storedData, storedSize));

    std::string regionString("aa");
    ASSERT_THROW(readWriteMemory.assignRegion(regionString.data(), 2, testString.size() - 1), MemorySizeError);
    ASSERT_THROW(readWriteMemory.assignRegion(regionString.data(), 2, testString.size()), MemorySizeError);
    readWriteMemory.assignRegion(regionString.data(), 2, 2);

    storedData = readWriteMemory.data(&storedSize);
    ASSERT_EQ(testString.size(), storedSize);
    ASSERT_EQ("Teaa string", std::string(storedData, storedSize));
}


TEST(memoryTest, readWriteMemoryCopy)
{
    std::string testString("Test string");
    Memory readOnlyMemory(testString.c_str(), testString.size());

    MutableMemory readWriteMemory(readOnlyMemory);

    ASSERT_EQ(testString.size(), readWriteMemory.size());
    ASSERT_FALSE(readWriteMemory.empty());

    size_t storedSize;
    const char* storedData(readWriteMemory.data(&storedSize));
    ASSERT_EQ(testString.size(), storedSize);
    ASSERT_EQ(testString, std::string(storedData, storedSize));

    readWriteMemory.resize(4);
    storedData = readWriteMemory.data(&storedSize);
    ASSERT_EQ(4u, storedSize);
    ASSERT_EQ("Test", std::string(storedData, storedSize));

    readWriteMemory.clear();
    ASSERT_TRUE(readWriteMemory.empty());
    storedData = readWriteMemory.data(&storedSize);
    ASSERT_EQ(0u, storedSize);
    ASSERT_EQ("", std::string(storedData, storedSize));

}


} // namespace tests

} // namespace imebra

