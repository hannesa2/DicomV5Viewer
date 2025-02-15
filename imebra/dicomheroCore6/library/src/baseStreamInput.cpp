/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file baseStreamInput.cpp
    \brief Implementation of the the base class for the input streams (memory, file, ...).
*/

#include "../include/dicomhero6/baseStreamInput.h"
#include "../implementation/baseStreamImpl.h"
#include "../implementation/exceptionImpl.h"

namespace dicomhero
{

//
// BaseStreamInput methods
//
///////////////////////////////////////////////////////////////////////////////

BaseStreamInput::BaseStreamInput(const BaseStreamInput& source):
    m_pInputStream(getBaseStreamInputImplementation(source))
{
}

BaseStreamInput::BaseStreamInput(const std::shared_ptr<implementation::baseStreamInput>& pInputStream): m_pInputStream(pInputStream)
{
}

BaseStreamInput::~BaseStreamInput()
{
}

const std::shared_ptr<implementation::baseStreamInput>& getBaseStreamInputImplementation(const BaseStreamInput& baseStreamInput)
{
    return baseStreamInput.m_pInputStream;
}


//
// StreamTimeout methods
//
///////////////////////////////////////////////////////////////////////////////

StreamTimeout::StreamTimeout(const StreamTimeout &source):
    m_pStreamTimeout(getStreamTimeoutImplementation(source))
{
}

StreamTimeout::StreamTimeout(BaseStreamInput& stream, std::uint32_t timeoutSeconds):
    m_pStreamTimeout(std::make_shared<implementation::streamTimeout>(getBaseStreamInputImplementation(stream), std::chrono::seconds(timeoutSeconds)))
{
}

StreamTimeout::~StreamTimeout()
{
}

const std::shared_ptr<implementation::streamTimeout>& getStreamTimeoutImplementation(const StreamTimeout& streamTimeout)
{
    return streamTimeout.m_pStreamTimeout;
}

}
