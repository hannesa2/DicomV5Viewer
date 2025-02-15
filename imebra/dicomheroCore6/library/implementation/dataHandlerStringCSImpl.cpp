/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file dataHandlerStringCS.cpp
    \brief Implementation of the class dataHandlerStringCS.

*/

#include "dataHandlerStringCSImpl.h"

namespace dicomhero
{

namespace implementation
{

namespace handlers
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
//
// dataHandlerStringCS
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringCS::readingDataHandlerStringCS(const memory &parseMemory):
    readingDataHandlerStringNumbers(parseMemory, tagVR_t::CS, '\\', 0x20)
{
}

writingDataHandlerStringCS::writingDataHandlerStringCS(const std::shared_ptr<buffer> pBuffer):
    writingDataHandlerStringNumbers(pBuffer, tagVR_t::CS, '\\', 0, 16)
{
}

} // namespace handlers

} // namespace implementation

} // namespace dicomhero
