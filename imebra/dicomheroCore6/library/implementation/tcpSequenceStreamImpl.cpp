/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file tcpSequenceStreamImpl.cpp
    \brief Implementation of the the TCP stream used by the dicomhero library.

*/

#include "tcpSequenceStreamImpl.h"
#include "../include/dicomhero6/exceptions.h"
#include <string.h>

#ifdef DICOMHERO_WINDOWS

#include <Ws2tcpip.h>

#else

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <poll.h>
#include <netinet/in.h>

#endif

namespace dicomhero
{

namespace implementation
{


#ifdef DICOMHERO_WINDOWS

initWinsock::initWinsock()
{
    DICOMHERO_FUNCTION_START();

    WSADATA wsaData;

    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        DICOMHERO_THROW(std::runtime_error, "WSA socket initialization failure");
    }
    DICOMHERO_FUNCTION_END();
}

initWinsock::~initWinsock()
{
    WSACleanup();
}

std::shared_ptr<initWinsock> initWinsock::getWinsockInitialization()
{
    DICOMHERO_FUNCTION_START();

    static std::shared_ptr<initWinsock> m_initWinsock(std::make_shared<initWinsock>());

    return m_initWinsock;

    DICOMHERO_FUNCTION_END();
}

#endif


///////////////////////////////////////////////////////////
//
// SocketTimeout is used only internally when a TCP
//  timeout is detected
//
///////////////////////////////////////////////////////////
class SocketTimeout: public  std::runtime_error
{
public:
    SocketTimeout(const std::string& message):
        std::runtime_error(message)
    {
    }
};


///////////////////////////////////////////////////////////
//
// Throw an exception according to the result of a socket
//  operation and the content of errno
//
///////////////////////////////////////////////////////////
long throwTcpException(long socketOperationResult)
{
    DICOMHERO_FUNCTION_START();

    if(socketOperationResult >= 0)
    {
        return socketOperationResult;
    }

#ifdef DICOMHERO_WINDOWS
    int error(WSAGetLastError());
    switch(error)
    {
    case WSAETIMEDOUT:
        DICOMHERO_THROW(SocketTimeout, "Timed out");
    case WSAEHOSTDOWN:
        DICOMHERO_THROW(SocketTimeout, "Host is down");
    case WSAECONNREFUSED:
        DICOMHERO_THROW(TCPConnectionRefused, "Connection refused");
    case WSAENOBUFS:
    case WSAEMFILE:
        throw std::bad_alloc();
    case WSAEINPROGRESS:
        return socketOperationResult;
    case WSAEFAULT:
        DICOMHERO_THROW(std::logic_error, "Invalid address space");
    case WSAEACCES:
        DICOMHERO_THROW(PermissionDeniedError, "Permission denied");
    case WSAEINVAL:
        DICOMHERO_THROW(std::logic_error, "Invalid argument");
    case WSAENOTSOCK:
        DICOMHERO_THROW(std::logic_error, "Operation on invalid socket");
    case WSAEWOULDBLOCK:
        DICOMHERO_THROW(SocketTimeout, "Timed out");
    case EPIPE:
    case WSAECONNRESET:
    case WSAENOTCONN:
    case WSAECONNABORTED:
    case WSAENETRESET:
        DICOMHERO_THROW(StreamClosedError, "Socket closed");
    case WSAEADDRINUSE:
        DICOMHERO_THROW(TCPAddressAlreadyInUse, "The specified address is already in use.");

    }
#else
    int error = errno;
    switch(error)
    {
    case ECONNREFUSED:
        DICOMHERO_THROW(TCPConnectionRefused, "Connection refused")
    case EHOSTDOWN:
        DICOMHERO_THROW(TCPConnectionRefused, "The host is down")
    case ENOBUFS:
    case ENOMEM:
    case EMFILE:
        throw std::bad_alloc();
    case EINPROGRESS:
        return socketOperationResult;
    case EFAULT:
        DICOMHERO_THROW(std::logic_error, "Invalid address space");
    case EACCES:
        DICOMHERO_THROW(PermissionDeniedError, "Permission denied");
    case EINVAL:
        DICOMHERO_THROW(std::logic_error, "Invalid argument");
    case ENOTSOCK:
        DICOMHERO_THROW(std::logic_error, "Operation on invalid socket");
    case ENOTCONN:
    case EWOULDBLOCK:
    case EINTR:
        DICOMHERO_THROW(SocketTimeout, "Timed out");
    case EPIPE:
    case ECONNRESET:
    case ECONNABORTED:
        DICOMHERO_THROW(StreamClosedError, "Socket closed");
    case EADDRINUSE:
        DICOMHERO_THROW(TCPAddressAlreadyInUse, "The specified address is already in use.")
    }
#endif
    DICOMHERO_THROW(StreamError, "Unexpected TCP error (code " << error << ")");

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Throw an exception based on the result of a tcp
//  addr operation
//
///////////////////////////////////////////////////////////
void throwAddrException(int addrOperationResult)
{
    DICOMHERO_FUNCTION_START();

    if(addrOperationResult == 0)
    {
        return;
    }

    const char* errorDescription = gai_strerror(addrOperationResult);

    switch(addrOperationResult)
    {
    case EAI_AGAIN:
        DICOMHERO_THROW(AddressTryAgainError, errorDescription);
    case EAI_FAIL:
        DICOMHERO_THROW(AddressError, errorDescription);
    case EAI_MEMORY:
        throw std::bad_alloc();
    case EAI_NONAME:
        DICOMHERO_THROW(AddressNoNameError, errorDescription);
    case EAI_SERVICE:
        DICOMHERO_THROW(AddressServiceNotSupportedError, errorDescription);
#ifndef DICOMHERO_WINDOWS
    case EAI_SYSTEM:
        throwTcpException(-1);
        break;
#endif
    default:
        DICOMHERO_THROW(AddressError, "Unexpected TCP Address error " << errorDescription << " code: " << addrOperationResult);
    }

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// tcpAddress constructors
//
///////////////////////////////////////////////////////////
tcpAddress::tcpAddress(const std::string& node, const std::string& service, passiveSocket_t passiveSocket):
    m_node(node),
    m_service(service)
{
    DICOMHERO_FUNCTION_START();

    INIT_WINSOCK;

    addrinfo hints = {};
    hints.ai_flags = (passiveSocket == passiveSocket_t::passive ? AI_PASSIVE : 0);

    const char* pNode(node.empty() ? nullptr : node.c_str());
    const char* pService(service.empty() ? nullptr : service.c_str());
    addrinfo* address(0);
    throwAddrException(getaddrinfo(pNode, pService, &hints, &address));

    m_sockAddr.resize(address->ai_addrlen);
    ::memcpy(&(m_sockAddr[0]), address->ai_addr, address->ai_addrlen);
    freeaddrinfo(address);

    DICOMHERO_FUNCTION_END_LOG();
}

tcpAddress::tcpAddress(const sockaddr& address, socklen_t addressLength)
{
    DICOMHERO_FUNCTION_START();

    INIT_WINSOCK;

    char host[NI_MAXHOST];
    char service[NI_MAXSERV];
    throwAddrException(getnameinfo(&address, addressLength, host, sizeof(host), service, sizeof(service), NI_NUMERICHOST | NI_NUMERICSERV));

    m_sockAddr.resize(addressLength);
    ::memcpy(&(m_sockAddr[0]), &address, addressLength);
    m_node = host;
    m_service = service;

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
tcpAddress::~tcpAddress()
{
}


///////////////////////////////////////////////////////////
//
// Return the node part of the address
//
///////////////////////////////////////////////////////////
std::string tcpAddress::getNode() const
{
    return m_node;
}


///////////////////////////////////////////////////////////
//
// Return the service part of the address
//
///////////////////////////////////////////////////////////
std::string tcpAddress::getService() const
{
    return m_service;
}


///////////////////////////////////////////////////////////
//
// Return a sockaddr structure representing the address
// The structure is owned by tcpAddress.
//
///////////////////////////////////////////////////////////
const sockaddr* tcpAddress::getSockAddr() const
{
    return reinterpret_cast<const sockaddr*>(m_sockAddr.data());
}


///////////////////////////////////////////////////////////
//
// Return the length of the structure returned by
//  getSockAddr().
//
///////////////////////////////////////////////////////////
socklen_t tcpAddress::getSockAddrLen() const
{
    return (socklen_t)m_sockAddr.size();
}


///////////////////////////////////////////////////////////
//
// Return the address' family.
//
///////////////////////////////////////////////////////////
int tcpAddress::getFamily() const
{
    return getSockAddr()->sa_family;
}


///////////////////////////////////////////////////////////
//
// Return the address' type
//
///////////////////////////////////////////////////////////
int tcpAddress::getType() const
{
    return SOCK_STREAM;
}


///////////////////////////////////////////////////////////
//
// Return the address' protocol
//
///////////////////////////////////////////////////////////
int tcpAddress::getProtocol() const
{
    return IPPROTO_TCP;
}


///////////////////////////////////////////////////////////
//
// Class used to coordinate a graceful termination of
// long running functions (listen read and write)
//
///////////////////////////////////////////////////////////
tcpBaseSocket::tcpTerminateWaiting::tcpTerminateWaiting(tcpBaseSocket& terminateObject):
    m_terminateObject(terminateObject)
{
    DICOMHERO_FUNCTION_START();

    INIT_WINSOCK;

    std::unique_lock<std::mutex> lock(m_terminateObject.m_waitingMutex);
    if(m_terminateObject.m_bTerminate)
    {
        DICOMHERO_THROW(StreamClosedError, "The socket has been closed");
    }
    m_terminateObject.m_waiting++;

    DICOMHERO_FUNCTION_END();
}


tcpBaseSocket::tcpTerminateWaiting::~tcpTerminateWaiting()
{
    std::unique_lock<std::mutex> lock(m_terminateObject.m_waitingMutex);
    m_terminateObject.m_waiting--;
    m_terminateObject.m_waitingCondition.notify_all();
}


///////////////////////////////////////////////////////////
///
/// Base class for tcpSequenceStream and tcpListener
///
///////////////////////////////////////////////////////////
tcpBaseSocket::tcpBaseSocket(int socket):
    m_socket(socket), m_bTerminate(false), m_waiting(0)
{
    // Set timeout
#ifdef DICOMHERO_WINDOWS

    INIT_WINSOCK;
    std::uint32_t timeout(DICOMHERO_TCP_TIMEOUT_MS);
    setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&timeout, sizeof(timeout));
    setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, (const char*)&timeout, sizeof(timeout));

#else
    timeval timeout;
    timeout.tv_sec = (time_t)DICOMHERO_TCP_TIMEOUT_MS / (time_t)1000;
    timeout.tv_usec = (suseconds_t)DICOMHERO_TCP_TIMEOUT_MS * (suseconds_t)1000 - (suseconds_t)(timeout.tv_sec * (suseconds_t)1000000);
    setsockopt(m_socket, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    setsockopt(m_socket, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));
#endif
}


tcpBaseSocket::~tcpBaseSocket()
{
    if(m_socket >= 0)
    {
#ifdef DICOMHERO_WINDOWS
        ::closesocket(m_socket);
#else
        ::close(m_socket);
#endif
    }
}


void tcpBaseSocket::setBlockingMode(bool bBlocking)
{
#ifdef DICOMHERO_WINDOWS
    unsigned long block(bBlocking ? 0 : 1);
    throwTcpException(ioctlsocket(m_socket, FIONBIO, &block));
#else
    // Enable blocking mode
    int flags = (int)throwTcpException(fcntl(m_socket, F_GETFL, 0));
    if(bBlocking)
    {
        throwTcpException(fcntl(m_socket, F_SETFL, flags & ~O_NONBLOCK));
    }
    else
    {
        throwTcpException(fcntl(m_socket, F_SETFL, flags | O_NONBLOCK));
    }
#endif
}


void tcpBaseSocket::terminate()
{
    std::unique_lock<std::mutex> lock(m_waitingMutex);
    m_bTerminate = true;
    m_waitingCondition.wait(lock, [&]{return m_waiting == 0;});
}

void tcpBaseSocket::isTerminating()
{
    DICOMHERO_FUNCTION_START();

    std::unique_lock<std::mutex> lock(m_waitingMutex);
    if(m_bTerminate)
    {
        DICOMHERO_THROW(StreamClosedError, "The socket has been closed");
    }

    DICOMHERO_FUNCTION_END();
}


void tcpBaseSocket::poll(pollType_t pollType, std::chrono::milliseconds timeout)
{
    DICOMHERO_FUNCTION_START();

#ifdef DICOMHERO_WINDOWS
    fd_set readSockets;
    fd_set writeSockets;
    fd_set errorSockets;
    FD_ZERO(&readSockets);
    FD_ZERO(&writeSockets);
    FD_ZERO(&errorSockets);
    if(pollType == pollType_t::read)
    {
        FD_SET(m_socket, &readSockets);
    }
    else
    {
        FD_SET(m_socket, &writeSockets);
    }
    FD_SET(m_socket, &errorSockets);
    timeval timeoutVal;
    timeoutVal.tv_sec = static_cast<long>(timeout.count() / 1000);
    timeoutVal.tv_usec = static_cast<long>((timeout.count() - timeoutVal.tv_sec * 1000) * 1000);
    int numSockets = throwTcpException(::select(m_socket + 1, &readSockets, &writeSockets, &errorSockets, &timeoutVal));
    if(numSockets == 0)
    {
        DICOMHERO_THROW(SocketTimeout, "Timed out");
    }
    if(FD_ISSET(m_socket, &errorSockets))
    {
        DICOMHERO_THROW(StreamClosedError, "Stream closed");
    }
#else
    short flags = pollType == pollType_t::read ? POLLIN : POLLOUT;
    pollfd fds[1];
    fds[0].fd = m_socket;
    fds[0].events = flags | POLLHUP | POLLERR;
    fds[0].revents = 0;
    long pollResult = throwTcpException(::poll(fds, 1, static_cast<int>(timeout.count())));

    if(pollResult == 0)
    {
        throw SocketTimeout("Timeout during poll");
    }

    if((fds[0].revents & flags) != 0)
    {
        return;
    }

    if((fds[0].revents & POLLHUP) != 0)
    {
        DICOMHERO_THROW(StreamClosedError, "Stream closed");
    }

    if((fds[0].revents & POLLERR) != 0)
    {
        DICOMHERO_THROW(TCPConnectionRefused, "Stream closed");
    }

#endif

    DICOMHERO_FUNCTION_END();

}
///////////////////////////////////////////////////////////
//
// TCP I/O class constructors
//
///////////////////////////////////////////////////////////
tcpSequenceStream::tcpSequenceStream(int tcpSocket, std::shared_ptr<tcpAddress> pAddress):
    tcpBaseSocket(tcpSocket),
    m_pAddress(pAddress)
{
}

tcpSequenceStream::tcpSequenceStream(std::shared_ptr<tcpAddress> pAddress):
    tcpBaseSocket((int)throwTcpException(socket(pAddress->getFamily(), pAddress->getType(), pAddress->getProtocol()))),
    m_pAddress(pAddress)
{
    DICOMHERO_FUNCTION_START();

#if !defined(DICOMHERO_WINDOWS) && (__linux__ != 1)
    // Disable SIGPIPE
    int sigpipe = 1;
    setsockopt(m_socket, SOL_SOCKET, SO_NOSIGPIPE, (void *)&sigpipe, sizeof(sigpipe));
#endif

    // Connect in non-blocking mode, then enable blocking
    setBlockingMode(false);

#ifdef DICOMHERO_WINDOWS
    int connectReturn(connect(m_socket, pAddress->getSockAddr(), pAddress->getSockAddrLen()));
    if (connectReturn < 0 && WSAGetLastError() != WSAEWOULDBLOCK)
    {
        throwTcpException(connectReturn);
    }
#else
    throwTcpException(connect(m_socket, pAddress->getSockAddr(), pAddress->getSockAddrLen()));
#endif

    setBlockingMode(true);

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
tcpSequenceStream::~tcpSequenceStream()
{
    terminate();

#ifdef DICOMHERO_WINDOWS
    shutdown(m_socket, SD_BOTH);
#else
    shutdown(m_socket, SHUT_RDWR);
#endif
}


///////////////////////////////////////////////////////////
//
// Read from TCP stream
//
///////////////////////////////////////////////////////////
size_t tcpSequenceStream::read(std::uint8_t* pBuffer, size_t bufferLength)
{
    DICOMHERO_FUNCTION_START();

    tcpTerminateWaiting waiting(*this);

    if(bufferLength == 0)
    {
        isTerminating();
        return 0;
    }

    // Wait for data. Exit only when data arrives or the
    // termination is triggered
    ///////////////////////////////////////////////////////////
    for(;;)
    {
        isTerminating();

        try
        {
            poll(pollType_t::read, std::chrono::milliseconds(DICOMHERO_TCP_TIMEOUT_MS));

            // Read anyway. (windows may not signal an error on the
            // socket via poll, so we will get it via read)
            ///////////////////////////////////////////////////////////
            long receivedBytes(throwTcpException(recv(m_socket, (char*)pBuffer, bufferLength, 0)));
            if(receivedBytes == 0)
            {
                return 0;
            }
            else
            {
                return (size_t)receivedBytes;
            }
        }
        catch(const SocketTimeout&)
        {
            // Ignore timeout
        }
    }

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Write into the TCP stream
//
///////////////////////////////////////////////////////////
void tcpSequenceStream::write(const std::uint8_t* pBuffer, size_t bufferLength)
{
    DICOMHERO_FUNCTION_START();

    tcpTerminateWaiting waiting(*this);

    // Don't send zero bytes buffer (this is done via shutdown)
    ///////////////////////////////////////////////////////////
    if(bufferLength == 0)
    {
        return;
    }

    // Loop until the data is sent or the termination is
    // triggered
    ///////////////////////////////////////////////////////////
    for(size_t totalSentBytes(0); totalSentBytes != bufferLength; /* incremented in the loop */)
    {
        isTerminating();
        try
        {
            poll(pollType_t::write, std::chrono::milliseconds(DICOMHERO_TCP_TIMEOUT_MS));

            // Write anyway. (windows may not signal an error on the
            // socket via poll, so we will get it via write)
            ///////////////////////////////////////////////////////////
#if (__linux__ == 1)
            long sentBytes = throwTcpException((long)send(m_socket, (const char*)(pBuffer + totalSentBytes), bufferLength - totalSentBytes, MSG_NOSIGNAL));
#else
            long sentBytes = throwTcpException((long)send(m_socket, (const char*)(pBuffer + totalSentBytes), bufferLength - totalSentBytes, 0));
#endif

            totalSentBytes += (size_t)sentBytes;
        }
        catch(const SocketTimeout&)
        {
            // Ignore timeout
        }
    }

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Get the address of the connected peer
//
///////////////////////////////////////////////////////////
std::shared_ptr<tcpAddress> tcpSequenceStream::getPeerAddress() const
{
    return m_pAddress;
}


void tcpSequenceStream::terminate()
{
    tcpBaseSocket::terminate();
}


tcpSequenceStreamInput::tcpSequenceStreamInput(std::shared_ptr<tcpSequenceStream> pTcpStream):
    m_pTcpStream(pTcpStream)
{
}

size_t tcpSequenceStreamInput::read(std::uint8_t* pBuffer, size_t bufferLength)
{
    return m_pTcpStream->read(pBuffer, bufferLength);
}

void tcpSequenceStreamInput::terminate()
{
    m_pTcpStream->terminate();
}

tcpSequenceStreamOutput::tcpSequenceStreamOutput(std::shared_ptr<tcpSequenceStream> pTcpStream):
    m_pTcpStream(pTcpStream)
{
}

void tcpSequenceStreamOutput::write(const std::uint8_t* pBuffer, size_t bufferLength)
{
    m_pTcpStream->write(pBuffer, bufferLength);
}



///////////////////////////////////////////////////////////
//
// TCP listener constructor
//
///////////////////////////////////////////////////////////
tcpListener::tcpListener(std::shared_ptr<tcpAddress> pAddress):
    tcpBaseSocket((int)throwTcpException(socket(pAddress->getFamily(), pAddress->getType(), pAddress->getProtocol())))
{
    DICOMHERO_FUNCTION_START();

    const int optval = 1;
    #ifdef DICOMHERO_WINDOWS
        throwTcpException(setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&optval), sizeof(optval)));
    #else
        throwTcpException(setsockopt(m_socket, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)));
    #endif


    // Connect in non-blocking mode, then enable blocking
    setBlockingMode(false);

    throwTcpException(bind(m_socket, pAddress->getSockAddr(), pAddress->getSockAddrLen()));
    throwTcpException(listen(m_socket, SOMAXCONN));

    setBlockingMode(true);

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
//
// Destructor
//
///////////////////////////////////////////////////////////
tcpListener::~tcpListener()
{
    terminate();
}


///////////////////////////////////////////////////////////
//
// Listen for incoming connections and accepts them
//
///////////////////////////////////////////////////////////
std::shared_ptr<tcpSequenceStream> tcpListener::waitForConnection()
{
    DICOMHERO_FUNCTION_START();

    tcpTerminateWaiting waiting(*this);

    // Wait for connections until terminated
    ///////////////////////////////////////////////////////////
    for(;;)
    {
        isTerminating();

        sockaddr_in addr;
        socklen_t sockaddrLen(sizeof(addr));
        try
        {
            poll(pollType_t::read, std::chrono::milliseconds(DICOMHERO_TCP_TIMEOUT_MS));
            int acceptedSocket = (int)throwTcpException(accept(m_socket, (sockaddr*)&addr, &sockaddrLen));
            std::shared_ptr<tcpAddress> pPeerAddress(std::make_shared<tcpAddress>(*((sockaddr*)&addr), sockaddrLen));
            return std::make_shared<tcpSequenceStream>(acceptedSocket, pPeerAddress);
        }
        catch(const SocketTimeout&)
        {
            // Timed out. retry
        }
    }

    DICOMHERO_FUNCTION_END();
}


} // namespace implementation

} // namespace dicomhero


