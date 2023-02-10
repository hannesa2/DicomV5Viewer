/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#include "../include/dicomhero6/memoryStreamOutput.h"
#include "../include/dicomhero6/mutableMemory.h"
#include "../implementation/memoryStreamImpl.h"
#include <memory>

namespace dicomhero
{

MemoryStreamOutput::MemoryStreamOutput(const MutableMemory& memory):
    BaseStreamOutput(std::make_shared<implementation::memoryStreamOutput>(std::const_pointer_cast<implementation::memory>(getMemoryImplementation(memory))))
{
}

MemoryStreamOutput::MemoryStreamOutput(const MemoryStreamOutput& source): BaseStreamOutput(source)
{
}

MemoryStreamOutput::~MemoryStreamOutput()
{
}

}
