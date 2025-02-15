/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/



#include "../include/dicomhero6/serialNumberUidGenerator.h"
#include "../implementation/serialNumberUidGeneratorImpl.h"

namespace dicomhero
{

SerialNumberUIDGenerator::SerialNumberUIDGenerator(const std::string& root, std::uint32_t departmentId, std::uint32_t modelId, std::uint32_t serialNumber):
    BaseUIDGenerator(std::make_shared<implementation::uidGenerators::serialNumberUidGenerator>(root, departmentId, modelId, serialNumber))
{
}

SerialNumberUIDGenerator::SerialNumberUIDGenerator(const SerialNumberUIDGenerator& source):
    BaseUIDGenerator(source)
{
}

SerialNumberUIDGenerator::~SerialNumberUIDGenerator()
{
}


}
