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

#include "../include/dicomhero6/readingDataHandlerNumeric.h"
#include "../include/dicomhero6/writingDataHandlerNumeric.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include "../implementation/exceptionImpl.h"
#include <cstring>

namespace dicomhero
{

ReadingDataHandlerNumeric::ReadingDataHandlerNumeric(const std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase>& pDataHandler):
    ReadingDataHandler(pDataHandler)
{
}

ReadingDataHandlerNumeric::ReadingDataHandlerNumeric(const ReadingDataHandlerNumeric& source): ReadingDataHandler(source)
{
}

ReadingDataHandlerNumeric::~ReadingDataHandlerNumeric()
{
}

Memory ReadingDataHandlerNumeric::getMemory() const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(*this));
    return Memory(numericDataHandler->getMemory());

    DICOMHERO_FUNCTION_END_LOG();
}

size_t ReadingDataHandlerNumeric::data(char* destination, size_t destinationSize) const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(*this));
    size_t memorySize = numericDataHandler->getMemorySize();
    if(destination != 0 && destinationSize >= memorySize && memorySize != 0)
    {
        ::memcpy(destination, numericDataHandler->getMemoryBuffer(), memorySize);
    }
    return memorySize;

    DICOMHERO_FUNCTION_END_LOG();
}

const char* ReadingDataHandlerNumeric::data(size_t* pDataSize) const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(*this));
    *pDataSize = numericDataHandler->getMemorySize();
    return (const char*)numericDataHandler->getMemoryBuffer();

    DICOMHERO_FUNCTION_END_LOG();
}

size_t ReadingDataHandlerNumeric::getUnitSize() const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(*this));
    return numericDataHandler->getUnitSize();

    DICOMHERO_FUNCTION_END_LOG();
}

bool ReadingDataHandlerNumeric::isSigned() const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(*this));
    return numericDataHandler->isSigned();

    DICOMHERO_FUNCTION_END_LOG();
}

bool ReadingDataHandlerNumeric::isFloat() const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(*this));
    return numericDataHandler->isFloat();

    DICOMHERO_FUNCTION_END_LOG();
}

void ReadingDataHandlerNumeric::copyTo(const WritingDataHandlerNumeric& destination)
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::readingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(*this));
    return numericDataHandler->copyTo(std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(destination)));

    DICOMHERO_FUNCTION_END_LOG();
}

}
