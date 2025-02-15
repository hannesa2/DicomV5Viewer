/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#include "../include/dicomhero6/memoryPool.h"
#include "../implementation/memoryImpl.h"
#include "../implementation/exceptionImpl.h"

namespace dicomhero
{

void MemoryPool::flush()
{
    DICOMHERO_FUNCTION_START();

    implementation::memoryPoolGetter::getMemoryPoolGetter().getMemoryPoolLocal().flush();

    DICOMHERO_FUNCTION_END_LOG();
}

size_t MemoryPool::getUnusedMemorySize()
{
    DICOMHERO_FUNCTION_START();

    return implementation::memoryPoolGetter::getMemoryPoolGetter().getMemoryPoolLocal().getUnusedMemorySize();

    DICOMHERO_FUNCTION_END_LOG();
}

void MemoryPool::setMemoryPoolSize(size_t minMemoryBlockSize, size_t maxMemoryPoolSize)
{
    DICOMHERO_FUNCTION_START();

    implementation::memoryPoolGetter::getMemoryPoolGetter().getMemoryPoolLocal().setMinMaxMemory(minMemoryBlockSize, maxMemoryPoolSize);

    DICOMHERO_FUNCTION_END_LOG();
}

}
