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
    \brief Implementation of the base class for the data handlers.

*/

#include "../include/dicomhero6/exceptions.h"
#include "exceptionImpl.h"
#include "dataHandlerImpl.h"
#include "memoryImpl.h"
#include "dicomDictImpl.h"
#include "dateImpl.h"
#include "ageImpl.h"

namespace dicomhero
{

namespace implementation
{

namespace handlers
{


readingDataHandler::readingDataHandler(tagVR_t dataType): m_dataType(dataType)
{
}

readingDataHandler::~readingDataHandler()
{
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the data 's type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
tagVR_t readingDataHandler::getDataType() const
{
    return m_dataType;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the date
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<date> readingDataHandler::getDate(const size_t /* index */) const
{
    DICOMHERO_FUNCTION_START();

    DICOMHERO_THROW(DataHandlerConversionError, "Cannot convert VR "<< dicomDictionary::getDicomDictionary()->enumDataTypeToString(getDataType()) << " to Date");

    DICOMHERO_FUNCTION_END();
}

std::shared_ptr<age> readingDataHandler::getAge(const size_t /* index */) const
{
    DICOMHERO_FUNCTION_START();

    DICOMHERO_THROW(DataHandlerConversionError, "Cannot convert VR "<< dicomDictionary::getDicomDictionary()->enumDataTypeToString(getDataType()) << " to Age");

    DICOMHERO_FUNCTION_END();
}

std::shared_ptr<patientName> readingDataHandler::getPatientName(const size_t /* index */) const
{
    DICOMHERO_FUNCTION_START();

    DICOMHERO_THROW(DataHandlerConversionError, "Cannot convert VR "<< dicomDictionary::getDicomDictionary()->enumDataTypeToString(getDataType()) << " to Patient Name");

    DICOMHERO_FUNCTION_END();
}

std::shared_ptr<unicodePatientName> readingDataHandler::getUnicodePatientName(const size_t /* index */) const
{
    DICOMHERO_FUNCTION_START();

    DICOMHERO_THROW(DataHandlerConversionError, "Cannot convert VR "<< dicomDictionary::getDicomDictionary()->enumDataTypeToString(getDataType()) << " to Patient Name");

    DICOMHERO_FUNCTION_END();
}




writingDataHandler::writingDataHandler(const std::shared_ptr<buffer> &pBuffer, tagVR_t dataType):
    m_dataType(dataType), m_buffer(pBuffer)
{
}

writingDataHandler::~writingDataHandler()
{
}

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Retrieve the data 's type
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
tagVR_t writingDataHandler::getDataType() const
{
    return m_dataType;
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Set the date
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void writingDataHandler::setDate(const size_t /* index */, const std::shared_ptr<const date>& /* pDate */)
{
    DICOMHERO_FUNCTION_START();

    DICOMHERO_THROW(DataHandlerConversionError, "Cannot convert Date to VR "<< dicomDictionary::getDicomDictionary()->enumDataTypeToString(getDataType()));

    DICOMHERO_FUNCTION_END();
}

void writingDataHandler::setAge(const size_t /* index */, const std::shared_ptr<const age>& /* pAge */)
{
    DICOMHERO_FUNCTION_START();

    DICOMHERO_THROW(DataHandlerConversionError, "Cannot convert Age to VR "<< dicomDictionary::getDicomDictionary()->enumDataTypeToString(getDataType()));

    DICOMHERO_FUNCTION_END();
}

void writingDataHandler::setPatientName(const size_t /* index */, const std::shared_ptr<const patientName>& /* pPatientName */)
{
    DICOMHERO_FUNCTION_START();

    DICOMHERO_THROW(DataHandlerConversionError, "Cannot convert Patient Name to VR "<< dicomDictionary::getDicomDictionary()->enumDataTypeToString(getDataType()));

    DICOMHERO_FUNCTION_END();
}

void writingDataHandler::setUnicodePatientName(const size_t /* index */, const std::shared_ptr<const unicodePatientName>& /* pPatientName */)
{
    DICOMHERO_FUNCTION_START();

    DICOMHERO_THROW(DataHandlerConversionError, "Cannot convert Patient Name to VR "<< dicomDictionary::getDicomDictionary()->enumDataTypeToString(getDataType()));

    DICOMHERO_FUNCTION_END();
}

} // namespace handlers

} // namespace implementation

} // namespace dicomhero
