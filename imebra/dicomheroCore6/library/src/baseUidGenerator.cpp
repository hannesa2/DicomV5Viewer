/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file baseUidGenerator.cpp
    \brief Implementation of the base class used by the UID generators.

*/


#include "../include/dicomhero6/baseUidGenerator.h"
#include "../implementation/baseUidGeneratorImpl.h"

namespace dicomhero
{

BaseUIDGenerator::BaseUIDGenerator(const BaseUIDGenerator& source):
    m_pUidGenerator(source.m_pUidGenerator)
{
}

BaseUIDGenerator::BaseUIDGenerator(const std::shared_ptr<implementation::uidGenerators::baseUidGenerator>& pUidGenerator):
    m_pUidGenerator(pUidGenerator)
{
}

BaseUIDGenerator::~BaseUIDGenerator()
{
}

std::string BaseUIDGenerator::getUID()
{
    return m_pUidGenerator->getUid();
}



const std::shared_ptr<implementation::uidGenerators::baseUidGenerator>& getBaseUidGeneratorImplementation(const BaseUIDGenerator& baseUidGenerator)
{
    return baseUidGenerator.m_pUidGenerator;
}

} // namespace dicomhero
