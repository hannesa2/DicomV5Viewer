/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file colorTransformsFactory.cpp
    \brief Implementation of the class ColorTransformsFactory.
*/

#include "../include/dicomhero6/colorTransformsFactory.h"
#include "../implementation/colorTransformsFactoryImpl.h"
#include "../include/dicomhero6/exceptions.h"
namespace dicomhero
{

std::string ColorTransformsFactory::normalizeColorSpace(const std::string& colorSpace)
{
    return dicomhero::implementation::transforms::colorTransforms::colorTransformsFactory::normalizeColorSpace(colorSpace);
}

bool ColorTransformsFactory::isMonochrome(const std::string& colorSpace)
{
    return dicomhero::implementation::transforms::colorTransforms::colorTransformsFactory::isMonochrome(colorSpace);
}

bool ColorTransformsFactory::isSubsampledX(const std::string& colorSpace)
{
    return dicomhero::implementation::transforms::colorTransforms::colorTransformsFactory::isSubsampledX(colorSpace);
}

bool ColorTransformsFactory::isSubsampledY(const std::string& colorSpace)
{
    return dicomhero::implementation::transforms::colorTransforms::colorTransformsFactory::isSubsampledY(colorSpace);
}

bool ColorTransformsFactory::canSubsample(const std::string& colorSpace)
{
    return dicomhero::implementation::transforms::colorTransforms::colorTransformsFactory::canSubsample(colorSpace);
}

std::string ColorTransformsFactory::makeSubsampled(const std::string& colorSpace, bool bSubsampleX, bool bSubsampleY)
{
    return dicomhero::implementation::transforms::colorTransforms::colorTransformsFactory::makeSubsampled(colorSpace, bSubsampleX, bSubsampleY);
}

std::uint32_t ColorTransformsFactory::getNumberOfChannels(const std::string& colorSpace)
{
    return dicomhero::implementation::transforms::colorTransforms::colorTransformsFactory::getNumberOfChannels(colorSpace);
}

Transform ColorTransformsFactory::getTransform(const std::string& startColorSpace, const std::string& endColorSpace)
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<dicomhero::implementation::transforms::colorTransforms::colorTransformsFactory> factory(dicomhero::implementation::transforms::colorTransforms::colorTransformsFactory::getColorTransformsFactory());
    Transform transform(factory->getTransform(startColorSpace, endColorSpace));
    if(transform.m_pTransform == 0)
    {
        DICOMHERO_THROW(ColorTransformsFactoryNoTransformError, "There is no color transform that can convert between the specified color spaces " << startColorSpace << " and " << endColorSpace);
    }
    return transform;

    DICOMHERO_FUNCTION_END_LOG();
}

}
