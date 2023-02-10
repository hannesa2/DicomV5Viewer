#include <imebra/imebra.h>
#include <gtest/gtest.h>
#include <iostream>
#include <thread>

#if defined(_WIN32)
#pragma comment(lib, "Ws2_32.lib")
#include <Winsock2.h>
#include <WS2tcpip.h>
#else
#include <netdb.h>
#endif


namespace imebra
{

namespace tests
{

void sendDataThread(unsigned long maxConnections, std::string port)
{
    TCPActiveAddress connectToAddress("", port);

    try
    {
        for(unsigned int connectionNumber(0); connectionNumber != maxConnections; ++connectionNumber)
        {
            TCPStream newStream(connectToAddress);

            MutableDataSet dataSet("1.2.840.10008.1.2.1");
            dataSet.setUint32(TagId(11, 11), connectionNumber, tagVR_t::UL);

            StreamWriter writer(newStream.getStreamOutput());
            CodecFactory::save(dataSet, writer, codecType_t::dicom);
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "Error in sending thread" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << imebra::ExceptionsManager::getExceptionTrace() << std::endl;
    }
}

TEST(tcpTest, sendReceive)
{
    const std::string listeningPort("20000");

    TCPPassiveAddress listeningAddress("", listeningPort);

    TCPListener listener(listeningAddress);

    unsigned long maxConnections(10);

    std::thread sendDataThread(imebra::tests::sendDataThread, maxConnections, listeningPort);

    try
    {
        for(unsigned int connectionNumber(0); connectionNumber != maxConnections; ++connectionNumber)
        {
            TCPStream newStream = listener.waitForConnection();

            StreamReader reader(newStream.getStreamInput());
            DataSet dataSet = CodecFactory::load(reader);

            ASSERT_EQ(connectionNumber, dataSet.getUint32(TagId(11, 11), 0));
        }
    }
    catch(const std::exception& e)
    {
        std::cout << "Error in sending sendreceive test" << std::endl;
        std::cout << e.what() << std::endl;
        std::cout << imebra::ExceptionsManager::getExceptionTrace() << std::endl;
        EXPECT_TRUE(false);
    }

    sendDataThread.join();
}

void AcceptConnectionAndCloseThread(std::string port)
{
    TCPPassiveAddress listeningAddress("", port);

    TCPListener listener(listeningAddress);

    TCPStream newStream = listener.waitForConnection();

    StreamReader reader(newStream.getStreamInput());
    char buffer[5];
    reader.readSome(buffer, sizeof(buffer));

}

TEST(tcpTest, prematureClose)
{
    const std::string listeningPort("20000");

    std::thread acceptConnectionAndCloseThread(imebra::tests::AcceptConnectionAndCloseThread, listeningPort);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    TCPActiveAddress connectToAddress("", listeningPort);

    TCPStream newStream(connectToAddress);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    MutableDataSet dataSet("1.2.840.10008.1.2.1");
    dataSet.setUint32(TagId(11, 11), 1, tagVR_t::UL);

    StreamWriter writer(newStream.getStreamOutput());

    try
    {
        for(int iterations(0); iterations != 100; ++iterations)
        {
            CodecFactory::save(dataSet, writer, codecType_t::dicom);
        }
        EXPECT_TRUE(false);
    }
    catch(const StreamClosedError&)
    {
        EXPECT_TRUE(true);
    }
    catch(...)
    {
        EXPECT_TRUE(false);
    }

    acceptConnectionAndCloseThread.join();
}


void WaitForNoConnectionAndReturn(TCPListener& listener, bool& bTerminated)
{
    try
    {
        TCPStream newStream = listener.waitForConnection();
    }
    catch(StreamClosedError&)
    {

    }
    bTerminated = true;
}


TEST(tcpTest, noConnectionToListener)
{
    const std::string listeningPort("20001");
    TCPPassiveAddress listeningAddress("", listeningPort);
    TCPListener listener(listeningAddress);
    bool bTerminated(false);

    std::thread noConnectionAndCloseThread(imebra::tests::WaitForNoConnectionAndReturn, std::ref(listener), std::ref(bTerminated));
    noConnectionAndCloseThread.detach();

    std::this_thread::sleep_for(std::chrono::seconds(5));
    listener.terminate();
    std::this_thread::sleep_for(std::chrono::seconds(5));

    ASSERT_TRUE(bTerminated);
}



TEST(tcpTest, refusedConnection)
{
    TCPActiveAddress connectToAddress("", "20000");

    TCPStream newStream(connectToAddress);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    MutableDataSet dataSet("1.2.840.10008.1.2.1");
    dataSet.setUint32(TagId(11, 11), 1, tagVR_t::UL);

    StreamWriter writer(newStream.getStreamOutput());

    try
    {
        CodecFactory::save(dataSet, writer, codecType_t::dicom);
        EXPECT_TRUE(false);
    }
    catch(const StreamClosedError&)
    {
        EXPECT_TRUE(true);
    }
    catch(const TCPConnectionRefused&)
    {
        EXPECT_TRUE(true);
    }
    catch(const StreamError& e)
    {
        std::cout << "Caught wrong exception: " << e.what();
        EXPECT_TRUE(false);
    }

}


void DelayConnectionThread(std::string port)
{
    TCPPassiveAddress listeningAddress("", port);

    TCPListener listener(listeningAddress);

    std::this_thread::sleep_for(std::chrono::seconds(10));

    TCPStream stream(listener.waitForConnection());

    StreamReader reader(stream.getStreamInput());

    char buffer[5];
    for(size_t totalReceivedBytes(0); totalReceivedBytes < 100; )
    {
        size_t receivedBytes(reader.readSome(buffer, sizeof(buffer)));
        if(receivedBytes > 0)
        {
            totalReceivedBytes += (size_t)receivedBytes;
        }
        else
        {
            break;
        }
    }

}


TEST(tcpTest, delayedConnection)
{
    const std::string listeningPort("20001");

    std::thread delayConnection(imebra::tests::DelayConnectionThread, listeningPort);

    std::this_thread::sleep_for(std::chrono::seconds(1));

    TCPActiveAddress connectToAddress("", listeningPort);

    TCPStream newStream(connectToAddress);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    MutableDataSet dataSet("1.2.840.10008.1.2.1");
    dataSet.setUint32(TagId(11, 11), 1, tagVR_t::UL);

    StreamWriter writer(newStream.getStreamOutput());

    try
    {
        for(int iterations(0); iterations != 100000; ++iterations)
        {
            CodecFactory::save(dataSet, writer, codecType_t::dicom);
        }
        EXPECT_TRUE(false);
    }
    catch(const StreamClosedError&)
    {
        EXPECT_TRUE(true);
    }
    catch(std::runtime_error& e)
    {
        std::cout << "Caught wrong exception: " << e.what() << std::endl;
        EXPECT_TRUE(false);
    }

    delayConnection.join();
}


TEST(tcpTest, nonExistentAddress)
{
    EXPECT_THROW(TCPActiveAddress("gfsdgf.bbbgfdgfasd.netdasfsdf", "20000"), AddressError);
}



TEST(tcpTest, noService)
{
    EXPECT_THROW(TCPActiveAddress("localhost", "abcdzy"), AddressError);
}
} // namespace tests

} // namespace imebra
