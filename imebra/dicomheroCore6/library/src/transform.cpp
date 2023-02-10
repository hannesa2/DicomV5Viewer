/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file transform.cpp
    \brief Implementation of the Transform class.

*/

#include "../include/dicomhero6/transform.h"
#include "../include/dicomhero6/image.h"
#include "../implementation/transformImpl.h"

namespace dicomhero
{

Transform::~Transform()
{
}

Transform::Transform(const std::shared_ptr<dicomhero::implementation::transforms::transform>& pTransform): m_pTransform(pTransform)
{}

Transform::Transform(const Transform &source): m_pTransform(getTransformImplementation(source))
{
}

const std::shared_ptr<dicomhero::implementation::transforms::transform>& getTransformImplementation(const Transform& transform)
{
    return transform.m_pTransform;
}

bool Transform::isEmpty() const
{
    DICOMHERO_FUNCTION_START();

    return m_pTransform == 0 || m_pTransform->isEmpty();

    DICOMHERO_FUNCTION_END_LOG();
}

Image Transform::allocateOutputImage(const Image& inputImage, std::uint32_t width, std::uint32_t height) const
{
    DICOMHERO_FUNCTION_START();

    const std::shared_ptr<implementation::image> pImage(getImageImplementation(inputImage));
    return Image(m_pTransform->allocateOutputImage(pImage->getDepth(),
                                                   pImage->getColorSpace(),
                                                   pImage->getHighBit(),
                                                   pImage->getPalette(),
                                                   width, height));

    DICOMHERO_FUNCTION_END_LOG();
}

void Transform::runTransform(
            const Image& inputImage,
            std::uint32_t inputTopLeftX, std::uint32_t inputTopLeftY, std::uint32_t inputWidth, std::uint32_t inputHeight,
            Image& outputImage,
            std::uint32_t outputTopLeftX, std::uint32_t outputTopLeftY) const
{
    DICOMHERO_FUNCTION_START();

    m_pTransform->runTransform(getImageImplementation(inputImage),
        inputTopLeftX,
        inputTopLeftY,
        inputWidth,
        inputHeight,
        getImageImplementation(outputImage),
        outputTopLeftX,
        outputTopLeftY);

    DICOMHERO_FUNCTION_END_LOG();
}

}
