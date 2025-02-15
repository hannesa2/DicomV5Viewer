/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement 
 that your application must also be GPL), you may purchase a commercial 
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file colorTransform.cpp
    \brief Implementation of the base class for the color transforms.

*/

#include "exceptionImpl.h"
#include "colorTransformImpl.h"
#include "colorTransformsFactoryImpl.h"
#include "imageImpl.h"
#include "LUTImpl.h"
#include "../include/dicomhero6/exceptions.h"

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
///////////////////////////////////////////////////////////
//
//
//
// colorTransform
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
// Transformation
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void colorTransform::checkColorSpaces(const std::string& inputHandlerColorSpace, const std::string& outputHandlerColorSpace) const
{
    DICOMHERO_FUNCTION_START();

	if(inputHandlerColorSpace != getInitialColorSpace())
	{
        DICOMHERO_THROW(ColorTransformWrongColorSpaceError, "The image's color space cannot be handled by the transform");
	}

	if(outputHandlerColorSpace != getFinalColorSpace())
	{
        DICOMHERO_THROW(ColorTransformWrongColorSpaceError, "The image's color space cannot be handled by the transform");
	}

	DICOMHERO_FUNCTION_END();
}

void colorTransform::checkHighBit(std::uint32_t inputHighBit, std::uint32_t outputHighBit) const
{
    DICOMHERO_FUNCTION_START();

    if(inputHighBit != outputHighBit)
    {
        DICOMHERO_THROW(TransformDifferentHighBitError, "Different high bit (input = " << inputHighBit << ", output = " << outputHighBit << ")");
    }

    DICOMHERO_FUNCTION_END();
}


std::shared_ptr<image> colorTransform::allocateOutputImage(
        bitDepth_t inputDepth,
        const std::string& /* inputColorSpace */,
        std::uint32_t inputHighBit,
        std::shared_ptr<palette> inputPalette,
        std::uint32_t outputWidth, std::uint32_t outputHeight) const
{
    DICOMHERO_FUNCTION_START();

    if(inputPalette != 0)
    {
        std::uint8_t bits = inputPalette->getRed()->getBits();
        inputHighBit = bits - 1;
        if(bits > 8)
        {
            inputDepth = bitDepth_t::depthU16;
        }
        else
        {
            inputDepth = bitDepth_t::depthU8;
        }
    }

    return std::make_shared<image>(outputWidth, outputHeight, inputDepth, getFinalColorSpace(), inputHighBit);

    DICOMHERO_FUNCTION_END();
}

} // namespace colorTransforms

} // namespace transforms

} // namespace implementation

} // namespace dicomhero
