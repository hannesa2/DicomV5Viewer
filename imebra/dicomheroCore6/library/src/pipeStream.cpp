/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file pipe.cpp
    \brief Implementation of the DataSink and DataSource classes.

*/

#include "../include/dicomhero6/pipeStream.h"
#include "../include/dicomhero6/baseStreamInput.h"
#include "../include/dicomhero6/baseStreamOutput.h"
#include "../implementation/pipeImpl.h"
#include "../implementation/baseStreamImpl.h"
#include "../implementation/exceptionImpl.h"

namespace dicomhero
{

PipeStream::PipeStream(size_t circularBufferSize):
    m_pStream(std::make_shared<implementation::pipeSequenceStream>(circularBufferSize))
{
}

PipeStream::PipeStream(const PipeStream& source):
    m_pStream(getPipeStreamImplementation(source))
{
}

PipeStream::~PipeStream()
{
}

void PipeStream::close(unsigned int timeoutMilliseconds)
{
    DICOMHERO_FUNCTION_START();

    m_pStream->close(timeoutMilliseconds);

    DICOMHERO_FUNCTION_END_LOG();
}

const std::shared_ptr<implementation::pipeSequenceStream>& getPipeStreamImplementation(const PipeStream& stream)
{
    return stream.m_pStream;
}

BaseStreamInput PipeStream::getStreamInput()
{
    DICOMHERO_FUNCTION_START();

    return BaseStreamInput(std::make_shared<implementation::pipeSequenceStreamInput>(m_pStream));

    DICOMHERO_FUNCTION_END_LOG();
}

BaseStreamOutput PipeStream::getStreamOutput()
{
    DICOMHERO_FUNCTION_START();

    return BaseStreamOutput(std::make_shared<implementation::pipeSequenceStreamOutput>(m_pStream));

    DICOMHERO_FUNCTION_END_LOG();
}

}

