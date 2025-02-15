/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#include "../include/dicomhero6/memory.h"
#include "../implementation/memoryImpl.h"
#include "../implementation/exceptionImpl.h"
#include "../include/dicomhero6/exceptions.h"
#include <memory.h>

namespace dicomhero
{

Memory::Memory(): m_pMemory(std::make_shared<const implementation::memory>())
{
}

Memory::Memory(const char* buffer, size_t bufferSize):
    m_pMemory(std::make_shared<implementation::memory>(new implementation::stringUint8((const std::uint8_t*)buffer, bufferSize)))
{
}

Memory::Memory(const std::shared_ptr<const implementation::memory>& pMemory): m_pMemory(pMemory)
{
}

Memory::Memory(const Memory& source): m_pMemory(getMemoryImplementation(source))
{
}

const std::shared_ptr<const implementation::memory>& getMemoryImplementation(const Memory& memory)
{
    return memory.m_pMemory;
}

Memory::~Memory()
{
}

size_t Memory::size() const
{
    DICOMHERO_FUNCTION_START();

    return m_pMemory->size();

    DICOMHERO_FUNCTION_END_LOG();
}

const char* Memory::data(size_t* pDataSize) const
{
    DICOMHERO_FUNCTION_START();

    *pDataSize = m_pMemory->size();
    return (char*)m_pMemory->data();

    DICOMHERO_FUNCTION_END_LOG();
}

size_t Memory::data(char* destination, size_t destinationSize) const
{
    DICOMHERO_FUNCTION_START();

    size_t memorySize = m_pMemory->size();
    if(destination != 0 && destinationSize >= memorySize && memorySize != 0)
    {
        ::memcpy(destination, m_pMemory->data(), memorySize);
    }
    return memorySize;

    DICOMHERO_FUNCTION_END_LOG();
}

void Memory::regionData(char* destination, size_t destinationSize, size_t sourceOffset) const
{
    DICOMHERO_FUNCTION_START();

    size_t memorySize = m_pMemory->size();
    if(m_pMemory->size() < sourceOffset + destinationSize)
    {
        DICOMHERO_THROW(MemorySizeError, "The source memory region exceedes the memory size");
    }
    ::memcpy(destination, m_pMemory->data() + sourceOffset, memorySize);

    DICOMHERO_FUNCTION_END_LOG();
}


bool Memory::empty() const
{
    DICOMHERO_FUNCTION_START();

    return m_pMemory->empty();

    DICOMHERO_FUNCTION_END_LOG();
}

}
