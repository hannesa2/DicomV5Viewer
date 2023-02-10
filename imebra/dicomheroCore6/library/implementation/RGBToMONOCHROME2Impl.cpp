/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file RGBToMONOCHROME2.cpp
    \brief Implementation of the class RGBToMONOCHROME2.

*/

#include "exceptionImpl.h"
#include "RGBToMONOCHROME2Impl.h"
#include "dataHandlerImpl.h"
#include "dataSetImpl.h"
#include "imageImpl.h"

namespace dicomhero
{

namespace implementation
{

namespace transforms
{

namespace colorTransforms
{

///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the initial color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string RGBToMONOCHROME2::getInitialColorSpace() const
{
    return "RGB";
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the final color space
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string RGBToMONOCHROME2::getFinalColorSpace() const
{
    return "MONOCHROME2";
}

} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace dicomhero

