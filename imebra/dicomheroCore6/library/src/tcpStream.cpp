/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file tcpStream.cpp
    \brief Implementation of the TCPStream class.

*/

#include "../include/dicomhero6/tcpStream.h"
#include "../include/dicomhero6/tcpAddress.h"
#include "../implementation/tcpSequenceStreamImpl.h"

namespace dicomhero
{

TCPStream::TCPStream(const TCPActiveAddress& address):
    m_pStream(std::make_shared<implementation::tcpSequenceStream>(address.m_pAddress))
{
}

TCPStream::TCPStream(const std::shared_ptr<implementation::tcpSequenceStream>& pTcpStream):
    m_pStream(pTcpStream)
{
}

TCPStream::TCPStream(const TCPStream &source):
    m_pStream(getTCPStreamImplementation(source))
{
}

TCPStream::~TCPStream()
{
}

const std::shared_ptr<implementation::tcpSequenceStream>& getTCPStreamImplementation(const TCPStream& stream)
{
    return stream.m_pStream;
}

TCPAddress TCPStream::getPeerAddress() const
{
    DICOMHERO_FUNCTION_START();

    return TCPAddress(m_pStream->getPeerAddress());

    DICOMHERO_FUNCTION_END_LOG();
}

BaseStreamInput TCPStream::getStreamInput()
{
    DICOMHERO_FUNCTION_START();

    return BaseStreamInput(std::make_shared<implementation::tcpSequenceStreamInput>(m_pStream));

    DICOMHERO_FUNCTION_END_LOG();
}

BaseStreamOutput TCPStream::getStreamOutput()
{
    DICOMHERO_FUNCTION_START();

    return BaseStreamOutput(std::make_shared<implementation::tcpSequenceStreamOutput>(m_pStream));

    DICOMHERO_FUNCTION_END_LOG();
}


}

