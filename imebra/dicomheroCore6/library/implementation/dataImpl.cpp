/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file data.cpp
    \brief Implementation of the data class.

*/

#include "exceptionImpl.h"
#include "streamReaderImpl.h"
#include "streamWriterImpl.h"
#include "fileStreamImpl.h"
#include "dataImpl.h"
#include "dataSetImpl.h"
#include "dicomDictImpl.h"
#include "bufferImpl.h"
#include "dataHandlerImpl.h"
#include "dataHandlerNumericImpl.h"
#include "../include/dicomhero6/exceptions.h"
#include <iostream>

namespace dicomhero
{

namespace implementation
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// data
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
data::data(tagVR_t tagVR, const std::shared_ptr<charsetsList_t> pCharsets):
    m_pCharsetsList(pCharsets), m_tagVR(tagVR)
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Destructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
data::~data()
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set a buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void data::setBuffer(size_t bufferId, const std::shared_ptr<buffer>& newBuffer)
{
    DICOMHERO_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    // Assign the new buffer
    ///////////////////////////////////////////////////////////
    if(bufferId >= m_buffers.size())
    {
        m_buffers.resize(bufferId + 1);
    }
    m_buffers[bufferId] = newBuffer;

    DICOMHERO_FUNCTION_END();
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the buffer's data type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
tagVR_t data::getDataType() const
{
    return m_tagVR;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the number of buffers in the tag
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
size_t data::getBuffersCount() const
{
    DICOMHERO_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    // Returns the number of buffers
    ///////////////////////////////////////////////////////////
    return m_buffers.size();

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return true if the specified buffer exists
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool data::bufferExists(size_t bufferId) const
{
    std::lock_guard<std::mutex> lock(m_mutex);

    return bufferId < m_buffers.size() && m_buffers.at(bufferId) != nullptr;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the size of a buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
size_t data::getBufferSize(size_t bufferId) const
{
    DICOMHERO_FUNCTION_START();

    return getBuffer(bufferId)->getBufferSizeBytes();

    DICOMHERO_FUNCTION_END();
}


std::shared_ptr<buffer> data::getBuffer(size_t bufferId) const
{
    DICOMHERO_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    // Retrieve the buffer
    ///////////////////////////////////////////////////////////
    if(bufferId >= m_buffers.size() || m_buffers.at(bufferId) == nullptr)
    {
        DICOMHERO_THROW(MissingBufferError, "The buffer with ID " << bufferId << " is missing");
    }
    return m_buffers.at(bufferId);

    DICOMHERO_FUNCTION_END();

}


std::shared_ptr<buffer> data::getBufferCreate(size_t bufferId)
{
    DICOMHERO_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    // Retrieve the buffer
    ///////////////////////////////////////////////////////////
    if(bufferId < m_buffers.size() && m_buffers.at(bufferId) != nullptr)
    {
        return m_buffers.at(bufferId);
    }

    std::shared_ptr<buffer> pNewBuffer(std::make_shared<buffer>(m_pCharsetsList));
    if(bufferId >= m_buffers.size())
    {
        m_buffers.resize(bufferId + 1);
    }
    m_buffers[bufferId] = pNewBuffer;

    return pNewBuffer;

    DICOMHERO_FUNCTION_END();
}


std::shared_ptr<buffer> data::getBufferCreate(size_t bufferId, streamController::tByteOrdering endianType)
{
    DICOMHERO_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    // Retrieve the buffer
    ///////////////////////////////////////////////////////////
    if(bufferId < m_buffers.size() && m_buffers.at(bufferId) != nullptr)
    {
        return m_buffers.at(bufferId);
    }

    std::shared_ptr<buffer> pNewBuffer(std::make_shared<buffer>(m_pCharsetsList, endianType));
    if(bufferId >= m_buffers.size())
    {
        m_buffers.resize(bufferId + 1);
    }
    m_buffers[bufferId] = pNewBuffer;

    return pNewBuffer;

    DICOMHERO_FUNCTION_END();
}


std::shared_ptr<buffer> data::getBufferCreate(size_t bufferId,
                                        const std::shared_ptr<baseStreamInput>& originalStream,
                                        size_t bufferPosition,
                                        size_t bufferLength,
                                        size_t wordLength,
                                        streamController::tByteOrdering endianType)
{
    DICOMHERO_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    std::shared_ptr<buffer> pNewBuffer(std::make_shared<buffer>(originalStream,
                                                                bufferPosition,
                                                                bufferLength,
                                                                wordLength,
                                                                endianType,
                                                                m_pCharsetsList));
    if(bufferId >= m_buffers.size())
    {
        m_buffers.resize(bufferId + 1);
    }
    m_buffers[bufferId] = pNewBuffer;

    return pNewBuffer;

    DICOMHERO_FUNCTION_END();
}



///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get an handler (normal or raw) for the buffer
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<handlers::readingDataHandler> data::getReadingDataHandler(size_t bufferId) const
{
    DICOMHERO_FUNCTION_START();

    return getBuffer(bufferId)->getReadingDataHandler(m_tagVR);

    DICOMHERO_FUNCTION_END();
}


std::shared_ptr<handlers::writingDataHandler> data::getWritingDataHandler(size_t bufferId)
{
    DICOMHERO_FUNCTION_START();

    return getBufferCreate(bufferId)->getWritingDataHandler(m_tagVR);

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a raw data handler
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<handlers::readingDataHandlerRaw> data::getReadingDataHandlerRaw(size_t bufferId) const
{
    DICOMHERO_FUNCTION_START();

    return getBuffer(bufferId)->getReadingDataHandlerRaw(m_tagVR);

    DICOMHERO_FUNCTION_END();
}


std::shared_ptr<handlers::writingDataHandlerRaw> data::getWritingDataHandlerRaw(size_t bufferId)
{
    DICOMHERO_FUNCTION_START();

    return getBufferCreate(bufferId)->getWritingDataHandlerRaw(m_tagVR);

    DICOMHERO_FUNCTION_END();
}


std::shared_ptr<handlers::readingDataHandlerNumericBase> data::getReadingDataHandlerNumeric(size_t bufferId) const
{
    DICOMHERO_FUNCTION_START();

    return getBuffer(bufferId)->getReadingDataHandlerNumeric(m_tagVR);

    DICOMHERO_FUNCTION_END();
}


std::shared_ptr<handlers::writingDataHandlerNumericBase> data::getWritingDataHandlerNumeric(size_t bufferId)
{
    DICOMHERO_FUNCTION_START();

    return getBufferCreate(bufferId)->getWritingDataHandlerNumeric(m_tagVR);

    DICOMHERO_FUNCTION_END();
}

std::uint8_t data::getPaddingByte() const
{
    DICOMHERO_FUNCTION_START();

    switch(m_tagVR)
    {
    case tagVR_t::AE:
        return 0x20u;

    case tagVR_t::AS:
        return 0x20u;

    case tagVR_t::CS:
        return 0x20u;

    case tagVR_t::DS:
        return 0x20u;

    case tagVR_t::IS:
        return 0x20u;

    case tagVR_t::UR:
        return 0x20u;

    case tagVR_t::LO:
        return 0x20u;

    case tagVR_t::LT:
        return 0x20u;

    case tagVR_t::PN:
        return 0x20u;

    case tagVR_t::SH:
        return 0x20u;

    case tagVR_t::ST:
        return 0x20;

    case tagVR_t::UC:
        return 0x20;

    case tagVR_t::UI:
        return 0x0;

    case tagVR_t::UT:
        return 0x20;

    case tagVR_t::OB:
        return 0x0;

    case tagVR_t::OL:
        return 0x0;

    case tagVR_t::OV:
        return 0x0;

    case tagVR_t::SB:
        return 0x0;

    case tagVR_t::UN:
        return 0x0;

    case tagVR_t::OW:
        return 0x0;

    case tagVR_t::AT:
        return 0x0;

    case tagVR_t::FL:
        return 0x0;

    case tagVR_t::OF:
        return 0x0;

    case tagVR_t::FD:
        return 0x0;

    case tagVR_t::OD:
        return 0x0;

    case tagVR_t::SL:
        return 0x0;

    case tagVR_t::SV:
        return 0x0;

    case tagVR_t::SS:
        return 0x0;

    case tagVR_t::UL:
        return 0x0;

    case tagVR_t::UV:
        return 0x0;

    case tagVR_t::US:
        return 0x0;

    case tagVR_t::DA:
        return 0x20u;

    case tagVR_t::DT:
        return 0x20u;

    case tagVR_t::TM:
        return 0x20u;

    case tagVR_t::SQ:
        return 0x20u;
    }

    DICOMHERO_THROW(std::logic_error, "The tag was created with an invalid buffer type");

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Check if the buffer has an external stream
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
bool data::hasExternalStream(size_t bufferId) const
{
    return getBuffer(bufferId)->hasExternalStream();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a stream reader that works on the buffer's data
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<streamReader> data::getStreamReader(size_t bufferId)
{
    DICOMHERO_FUNCTION_START();

    return getBuffer(bufferId)->getStreamReader();

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Get a stream writer that works on the buffer's data
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<streamWriter> data::getStreamWriter(size_t bufferId)
{
    DICOMHERO_FUNCTION_START();

    return getBufferCreate(bufferId)->getStreamWriter(m_tagVR);

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set a stream content as tag's content
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void data::setExternalStream(size_t bufferId, std::shared_ptr<fileStreamInput> pExternalStream)
{
    DICOMHERO_FUNCTION_START();

    setBuffer(bufferId, std::make_shared<buffer>(pExternalStream,
                                                 0,
                                                 pExternalStream->getSize(),
                                                 dicomDictionary::getDicomDictionary()->getWordSize(getDataType()),
                                                 streamController::getPlatformEndian(),
                                                 m_pCharsetsList));

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve an embedded data set.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<dataSet> data::getSequenceItem(size_t dataSetId) const
{
    DICOMHERO_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    if(m_embeddedDataSets.size() <= dataSetId)
    {
        DICOMHERO_THROW(MissingItemError, "The requested sequence item does not exist");
    }

    return m_embeddedDataSets[dataSetId];

    DICOMHERO_FUNCTION_END();
}

bool data::dataSetExists(size_t dataSetId) const
{
    DICOMHERO_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    return m_embeddedDataSets.size() > dataSetId;

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Append a data set
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<dataSet> data::appendSequenceItem()
{
    DICOMHERO_FUNCTION_START();

    std::lock_guard<std::mutex> lock(m_mutex);

    std::shared_ptr<dataSet> pDataSet(std::make_shared<dataSet>(m_pCharsetsList));
    m_embeddedDataSets.push_back(pDataSet);

    return pDataSet;

    DICOMHERO_FUNCTION_END();
}


} // namespace implementation

} // namespace dicomhero
