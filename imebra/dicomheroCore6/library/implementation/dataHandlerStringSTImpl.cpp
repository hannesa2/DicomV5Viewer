/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file dataHandlerStringST.cpp
    \brief Implementation of the class dataHandlerStringST.

*/

#include "dataHandlerStringSTImpl.h"

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
// imebraDataHandlerStringST
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

readingDataHandlerStringST::readingDataHandlerStringST(const memory& parseMemory, const std::shared_ptr<const charsetsList_t>& pCharsets):
    readingDataHandlerStringUnicode(parseMemory, pCharsets, tagVR_t::ST, 0x0, 0x20)
{
}

writingDataHandlerStringST::writingDataHandlerStringST(const std::shared_ptr<buffer> &pBuffer, const std::shared_ptr<const charsetsList_t>& pCharsets):
    writingDataHandlerStringUnicode(pBuffer, pCharsets, tagVR_t::ST, 0x0, 0, 1024)
{
}


} // namespace handlers

} // namespace implementation

} // namespace dicomhero
