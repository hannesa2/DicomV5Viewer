/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#include "../include/dicomhero6/mutableMemory.h"
#include "../implementation/memoryImpl.h"
#include "../implementation/exceptionImpl.h"

namespace dicomhero
{

MutableMemory::MutableMemory(): Memory()
{
}

MutableMemory::MutableMemory(size_t initialSize): Memory(std::make_shared<implementation::memory>(initialSize))
{
}

MutableMemory::MutableMemory(const Memory &sourceMemory): Memory(std::make_shared<implementation::memory>(sourceMemory.size()))
{
    std::const_pointer_cast<implementation::memory>(getMemoryImplementation(*this))->copyFrom(getMemoryImplementation(sourceMemory));
}

MutableMemory::MutableMemory(const char* buffer, size_t bufferSize): Memory(std::make_shared<implementation::memory>(new implementation::stringUint8((const std::uint8_t*)buffer, bufferSize)))
{
}

MutableMemory::MutableMemory(std::shared_ptr<implementation::memory> pMemory): Memory(pMemory)
{
}

MutableMemory::MutableMemory(const MutableMemory& source): Memory(source)
{
}

MutableMemory::~MutableMemory()
{
}

void MutableMemory::copyFrom(const Memory& sourceMemory)
{
    DICOMHERO_FUNCTION_START();

    std::const_pointer_cast<implementation::memory>(getMemoryImplementation(*this))->copyFrom(getMemoryImplementation(sourceMemory));

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableMemory::clear()
{
    DICOMHERO_FUNCTION_START();

    std::const_pointer_cast<implementation::memory>(getMemoryImplementation(*this))->clear();

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableMemory::resize(size_t newSize)
{
    DICOMHERO_FUNCTION_START();

    std::const_pointer_cast<implementation::memory>(getMemoryImplementation(*this))->resize(newSize);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableMemory::reserve(size_t reserveSize)
{
    DICOMHERO_FUNCTION_START();

    std::const_pointer_cast<implementation::memory>(getMemoryImplementation(*this))->reserve(reserveSize);

    DICOMHERO_FUNCTION_END_LOG();
}

char* MutableMemory::data(size_t* pDataSize) const
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<implementation::memory> pMemory = std::const_pointer_cast<implementation::memory>(getMemoryImplementation(*this));
    *pDataSize = pMemory->size();
    return (char*)pMemory->data();

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableMemory::assign(const char* source, size_t sourceSize)
{
    DICOMHERO_FUNCTION_START();

    std::const_pointer_cast<implementation::memory>(getMemoryImplementation(*this))->assign((const std::uint8_t*)source, sourceSize);

    DICOMHERO_FUNCTION_END_LOG();
}

void MutableMemory::assignRegion(const char* source, size_t sourceSize, size_t destinationOffset)
{
    DICOMHERO_FUNCTION_START();

    std::const_pointer_cast<implementation::memory>(getMemoryImplementation(*this))->assignRegion((const std::uint8_t*)source, sourceSize, destinationOffset);

    DICOMHERO_FUNCTION_END_LOG();
}

}
