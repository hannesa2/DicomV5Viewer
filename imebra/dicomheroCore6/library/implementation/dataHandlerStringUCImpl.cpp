/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file dataHandlerStringUC.cpp
    \brief Implementation of the class dataHandlerStringUC.

*/

#include "dataHandlerStringUCImpl.h"

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
// dataHandlerStringUC
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringUC::readingDataHandlerStringUC(const memory &parseMemory, const std::shared_ptr<const charsetsList_t>& pCharsets):
    readingDataHandlerStringUnicode(parseMemory, pCharsets, tagVR_t::UC, L'\\', 0x20)
{
}

writingDataHandlerStringUC::writingDataHandlerStringUC(const std::shared_ptr<buffer> &pBuffer, const std::shared_ptr<const charsetsList_t>& pCharsets):
    writingDataHandlerStringUnicode(pBuffer, pCharsets, tagVR_t::UC, L'\\', 0, 4294967294)
{
}

} // namespace handlers

} // namespace implementation

} // namespace dicomhero
