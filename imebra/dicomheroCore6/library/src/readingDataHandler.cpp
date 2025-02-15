/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file dataHandler.cpp
    \brief Implementation of the classes ReadingDataHandler & WritingDataHandler.
*/

#include "../include/dicomhero6/readingDataHandler.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include "../implementation/exceptionImpl.h"
#include "../include/dicomhero6/age.h"
#include "../include/dicomhero6/patientName.h"
#include <cstring>

namespace dicomhero
{

ReadingDataHandler::ReadingDataHandler(const std::shared_ptr<implementation::handlers::readingDataHandler>& pDataHandler): m_pDataHandler(pDataHandler)
{
}

ReadingDataHandler::ReadingDataHandler(const ReadingDataHandler& source): m_pDataHandler(getReadingDataHandlerImplementation(source))
{
}

ReadingDataHandler::~ReadingDataHandler()
{
}

const std::shared_ptr<implementation::handlers::readingDataHandler>& getReadingDataHandlerImplementation(const ReadingDataHandler& readingDataHandler)
{
    return readingDataHandler.m_pDataHandler;
}

size_t ReadingDataHandler::getSize() const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getSize();

    DICOMHERO_FUNCTION_END_LOG();
}

tagVR_t ReadingDataHandler::getDataType() const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getDataType();

    DICOMHERO_FUNCTION_END_LOG();
}

std::int64_t ReadingDataHandler::getInt64(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getInt64(index);

    DICOMHERO_FUNCTION_END_LOG();
}

std::int32_t ReadingDataHandler::getInt32(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getInt32(index);

    DICOMHERO_FUNCTION_END_LOG();
}

std::int32_t ReadingDataHandler::getSignedLong(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getInt32(index);

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint64_t ReadingDataHandler::getUint64(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getUint64(index);

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint32_t ReadingDataHandler::getUint32(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getUint32(index);

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint32_t ReadingDataHandler::getUnsignedLong(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getUint32(index);

    DICOMHERO_FUNCTION_END_LOG();
}

std::int16_t ReadingDataHandler::getInt16(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getInt16(index);

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint16_t ReadingDataHandler::getUint16(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getUint16(index);

    DICOMHERO_FUNCTION_END_LOG();
}

std::int8_t ReadingDataHandler::getInt8(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getInt8(index);

    DICOMHERO_FUNCTION_END_LOG();
}

std::uint8_t ReadingDataHandler::getUint8(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getUint8(index);

    DICOMHERO_FUNCTION_END_LOG();
}

double ReadingDataHandler::getDouble(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getDouble(index);

    DICOMHERO_FUNCTION_END_LOG();
}

float ReadingDataHandler::getFloat(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getFloat(index);

    DICOMHERO_FUNCTION_END_LOG();
}

std::string ReadingDataHandler::getString(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getString(index);

    DICOMHERO_FUNCTION_END_LOG();
}

std::wstring ReadingDataHandler::getUnicodeString(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return m_pDataHandler->getUnicodeString(index);

    DICOMHERO_FUNCTION_END_LOG();
}

Date ReadingDataHandler::getDate(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return Date(m_pDataHandler->getDate(index));

    DICOMHERO_FUNCTION_END_LOG();
}

Age ReadingDataHandler::getAge(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return Age(m_pDataHandler->getAge(index));

    DICOMHERO_FUNCTION_END_LOG();
}

PatientName ReadingDataHandler::getPatientName(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return PatientName(m_pDataHandler->getPatientName(index));

    DICOMHERO_FUNCTION_END_LOG();
}

UnicodePatientName ReadingDataHandler::getUnicodePatientName(size_t index) const
{
    DICOMHERO_FUNCTION_START();

    return UnicodePatientName(m_pDataHandler->getUnicodePatientName(index));

    DICOMHERO_FUNCTION_END_LOG();
}



}
