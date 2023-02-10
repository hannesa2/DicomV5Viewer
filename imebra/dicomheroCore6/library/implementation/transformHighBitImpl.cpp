/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file transformHighBit.cpp
    \brief Implementation of the class transformHighBit.

*/

#include "exceptionImpl.h"
#include "transformHighBitImpl.h"
#include "dataSetImpl.h"
#include "imageImpl.h"


namespace dicomhero
{

namespace implementation
{

namespace transforms
{

std::shared_ptr<image> transformHighBit::allocateOutputImage(
        bitDepth_t inputDepth,
        const std::string& inputColorSpace,
        std::uint32_t inputHighBit,
        std::shared_ptr<palette> /* inputPalette */,
        std::uint32_t outputWidth, std::uint32_t outputHeight) const
{
    DICOMHERO_FUNCTION_START();

    return std::make_shared<image>(outputWidth, outputHeight, inputDepth, inputColorSpace, inputHighBit);

    DICOMHERO_FUNCTION_END();
}

} // namespace transforms

} // namespace implementation

} // namespace dicomhero
