/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file MONOCHROME2ToRGB.cpp
    \brief Implementation of the class MONOCHROME2ToRGB.

*/

#include "exceptionImpl.h"
#include "MONOCHROME2ToRGBImpl.h"
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
std::string MONOCHROME2ToRGB::getInitialColorSpace() const
{
    return "MONOCHROME2";
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
std::string MONOCHROME2ToRGB::getFinalColorSpace() const
{
    return "RGB";
}

} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace dicomhero

