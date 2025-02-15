/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file tcpAddress.cpp
    \brief Implementation of the TCPAddress class.

*/

#include "../include/dicomhero6/tcpAddress.h"
#include "../implementation/tcpSequenceStreamImpl.h"

namespace dicomhero
{

TCPAddress::TCPAddress(const std::shared_ptr<implementation::tcpAddress>& pAddress):
    m_pAddress(pAddress)
{
}

TCPAddress::TCPAddress(const TCPAddress& source): m_pAddress(getTCPAddressImplementation(source))
{
}

const std::shared_ptr<dicomhero::implementation::tcpAddress>& getTCPAddressImplementation(const TCPAddress& tcpAddress)
{
    return tcpAddress.m_pAddress;
}

std::string TCPAddress::getNode() const
{
    DICOMHERO_FUNCTION_START();

    return m_pAddress->getNode();

    DICOMHERO_FUNCTION_END_LOG();
}

std::string TCPAddress::getService() const
{
    DICOMHERO_FUNCTION_START();

    return m_pAddress->getService();

    DICOMHERO_FUNCTION_END_LOG();
}

TCPAddress::~TCPAddress()
{
}


TCPActiveAddress::TCPActiveAddress(const std::string& node, const std::string& service):
    TCPAddress(std::make_shared<implementation::tcpAddress>(node, service, implementation::tcpAddress::passiveSocket_t::active))
{
}

TCPActiveAddress::TCPActiveAddress(const TCPActiveAddress &source): TCPAddress(getTCPAddressImplementation(source))
{
}

TCPActiveAddress::~TCPActiveAddress()
{
}

TCPPassiveAddress::TCPPassiveAddress(const std::string& node, const std::string& service):
    TCPAddress(std::make_shared<implementation::tcpAddress>(node, service, implementation::tcpAddress::passiveSocket_t::passive))
{
}

TCPPassiveAddress::TCPPassiveAddress(const TCPPassiveAddress &source): TCPAddress(getTCPAddressImplementation(source))
{
}

TCPPassiveAddress::~TCPPassiveAddress()
{
}

}
