/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file tcpListener.cpp
    \brief Implementation of the TCPListener class.

*/

#include "../include/dicomhero6/tcpListener.h"
#include "../include/dicomhero6/tcpAddress.h"
#include "../include/dicomhero6/tcpStream.h"
#include "../implementation/tcpSequenceStreamImpl.h"

namespace dicomhero
{

TCPListener::TCPListener(const TCPPassiveAddress& address):
    m_pListener(std::make_shared<implementation::tcpListener>(address.m_pAddress))
{
}

TCPListener::TCPListener(const TCPListener &source): m_pListener(getTCPListenerImplementation(source))
{
}

TCPListener::~TCPListener()
{
}

const std::shared_ptr<implementation::tcpListener>& getTCPListenerImplementation(const TCPListener& source)
{
    return source.m_pListener;
}

void TCPListener::terminate()
{
    DICOMHERO_FUNCTION_START();

    m_pListener->terminate();

    DICOMHERO_FUNCTION_END_LOG();
}

TCPStream TCPListener::waitForConnection()
{
    DICOMHERO_FUNCTION_START();

    return TCPStream(m_pListener->waitForConnection());

    DICOMHERO_FUNCTION_END_LOG();
}


}

