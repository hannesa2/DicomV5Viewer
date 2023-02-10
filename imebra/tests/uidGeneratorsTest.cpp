#include <imebra/imebra.h>
#include <gtest/gtest.h>
#include <thread>
#include <chrono>
#include <functional>

namespace imebra
{

namespace tests
{


TEST(uidGenerators, uidGeneratorsFactory)
{
    {
        RandomUIDGenerator firstGenerator("1.2.3", 4, 5);
        SerialNumberUIDGenerator secondGenerator("1.2.4", 1, 2, 3);

        UIDGeneratorFactory::registerUIDGenerator("zzz", firstGenerator);
        UIDGeneratorFactory::registerUIDGenerator("aaa", secondGenerator);
    }

    {
        BaseUIDGenerator firstGenerator = UIDGeneratorFactory::getUIDGenerator("zzz");
        EXPECT_TRUE(firstGenerator.getUID().find("1.2.3.") == 0);

        BaseUIDGenerator secondGenerator = UIDGeneratorFactory::getUIDGenerator("aaa");
        EXPECT_TRUE(secondGenerator.getUID().find("1.2.4.") == 0);

        BaseUIDGenerator defaultGenerator = UIDGeneratorFactory::getDefaultUIDGenerator();
        EXPECT_TRUE(defaultGenerator.getUID().find("1.2.3.") == 0);

    }

    EXPECT_THROW(UIDGeneratorFactory::getUIDGenerator("ccc"), NonRegisteredUIDGenerator);
}


TEST(uidGenerators, randomUIDGenerator)
{
    RandomUIDGenerator randomGenerator0("1.2.3", 4, 5);
    RandomUIDGenerator randomGenerator1("1.2.3", 4, 5);

    std::set<std::string> generatedUids;

    size_t numberOfUIDs(1000000);

    for(size_t index(0); index != numberOfUIDs; ++index)
    {
        std::string uid0 = randomGenerator0.getUID();
        std::string uid1 = randomGenerator1.getUID();

        ASSERT_TRUE(uid0.find("1.2.3.4.5.") == 0);
        ASSERT_TRUE(uid1.find("1.2.3.4.5.") == 0);

        ASSERT_TRUE(generatedUids.find(uid0) == generatedUids.end());
        ASSERT_TRUE(generatedUids.find(uid1) == generatedUids.end());

        generatedUids.insert(uid0);
        generatedUids.insert(uid1);
    }

    ASSERT_EQ(numberOfUIDs * 2, generatedUids.size());
}


TEST(uidGenerators, serialNumberUIDGenerator)
{
    SerialNumberUIDGenerator serialNumberGenerator("1.2.3", 4, 5, 5000);

    std::set<std::string> generatedUids;

    size_t numberOfUIDs(1000000);

    for(size_t index(0); index != numberOfUIDs; ++index)
    {
        std::string uid = serialNumberGenerator.getUID();

        ASSERT_TRUE(uid.find("1.2.3.4.5.5000.") == 0);

        ASSERT_TRUE(generatedUids.find(uid) == generatedUids.end());

        generatedUids.insert(uid);
    }

    ASSERT_EQ(numberOfUIDs, generatedUids.size());
}



} // namespace tests

} // namespace imebra
