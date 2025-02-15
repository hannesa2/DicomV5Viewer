/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file dataHandlerStringUR.cpp
    \brief Implementation of the class dataHandlerStringUR.

*/

#include "dataHandlerStringURImpl.h"

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
// dataHandlerStringUR
//
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Constructor
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
readingDataHandlerStringUR::readingDataHandlerStringUR(const memory &parseMemory): readingDataHandlerString(parseMemory, tagVR_t::UR, 0, 0x20)
{
}

writingDataHandlerStringUR::writingDataHandlerStringUR(const std::shared_ptr<buffer> &pBuffer): writingDataHandlerString(pBuffer, tagVR_t::UR, 0, 0, 4294967294)
{
}

} // namespace handlers

} // namespace implementation

} // namespace dicomhero
