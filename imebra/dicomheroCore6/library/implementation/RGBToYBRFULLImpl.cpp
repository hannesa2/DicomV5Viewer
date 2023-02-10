/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file RGBToYBRFULL.cpp
    \brief Implementation of the class RGBToYBRFULL.

*/

#include "exceptionImpl.h"
#include "RGBToYBRFULLImpl.h"
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
std::string RGBToYBRFULL::getInitialColorSpace() const
{
    return "RGB";
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the final color space (YBR_FULL)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string RGBToYBRFULL::getFinalColorSpace() const
{
    return "YBR_FULL";
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Return the final color space (YBR_ICT)
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::string RGBToYBRICT::getFinalColorSpace() const
{
    return "YBR_ICT";
}

} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace dicomhero

