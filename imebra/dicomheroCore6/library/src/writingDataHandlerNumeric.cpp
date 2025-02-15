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

#include "../include/dicomhero6/writingDataHandlerNumeric.h"
#include "../include/dicomhero6/readingDataHandlerNumeric.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"
#include <cstring>

namespace dicomhero
{

WritingDataHandlerNumeric::WritingDataHandlerNumeric(const std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase>& pDataHandler):
    WritingDataHandler(pDataHandler)
{
}

WritingDataHandlerNumeric::WritingDataHandlerNumeric(const WritingDataHandlerNumeric& source): WritingDataHandler(source)
{
}

WritingDataHandlerNumeric::~WritingDataHandlerNumeric()
{
}

MutableMemory WritingDataHandlerNumeric::getMemory() const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    return MutableMemory(numericDataHandler->getMemory());

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandlerNumeric::assign(const char* source, size_t sourceSize)
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    numericDataHandler->getMemory()->assign((std::uint8_t*) source, sourceSize);

    DICOMHERO_FUNCTION_END_LOG();
}

char* WritingDataHandlerNumeric::data(size_t* pDataSize) const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    *pDataSize = numericDataHandler->getMemorySize();
    return (char*)numericDataHandler->getMemoryBuffer();

    DICOMHERO_FUNCTION_END_LOG();
}

size_t WritingDataHandlerNumeric::data(char* destination, size_t destinationSize) const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    size_t memorySize = numericDataHandler->getMemorySize();
    if(destination != 0 && destinationSize >= memorySize && memorySize != 0)
    {
        ::memcpy(destination, numericDataHandler->getMemoryBuffer(), memorySize);
    }
    return memorySize;

    DICOMHERO_FUNCTION_END_LOG();
}

size_t WritingDataHandlerNumeric::getUnitSize() const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    return numericDataHandler->getUnitSize();

    DICOMHERO_FUNCTION_END_LOG();
}

bool WritingDataHandlerNumeric::isSigned() const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    return numericDataHandler->isSigned();

    DICOMHERO_FUNCTION_END_LOG();
}

bool WritingDataHandlerNumeric::isFloat() const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    return numericDataHandler->isFloat();

    DICOMHERO_FUNCTION_END_LOG();
}

void WritingDataHandlerNumeric::copyFrom(const ReadingDataHandlerNumeric& source)
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::handlers::writingDataHandlerNumericBase> numericDataHandler =
            std::dynamic_pointer_cast<implementation::handlers::writingDataHandlerNumericBase>(getWritingDataHandlerImplementation(*this));
    return numericDataHandler->copyFrom(std::dynamic_pointer_cast<implementation::handlers::readingDataHandlerNumericBase>(getReadingDataHandlerImplementation(source)));

    DICOMHERO_FUNCTION_END_LOG();
}

}
