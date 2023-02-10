/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#include "../include/dicomhero6/memoryStreamInput.h"
#include "../include/dicomhero6/memory.h"
#include "../include/dicomhero6/mutableMemory.h"
#include "../implementation/memoryStreamImpl.h"
#include <memory>

namespace dicomhero
{

MemoryStreamInput::MemoryStreamInput(const Memory& memory): BaseStreamInput(std::make_shared<implementation::memoryStreamInput>(getMemoryImplementation(memory)))
{
}

MemoryStreamInput::MemoryStreamInput(const MemoryStreamInput& source): BaseStreamInput(source)
{
}

MemoryStreamInput::~MemoryStreamInput()
{
}

}
