/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file image_swig.h
    \brief Implementation of the class Image for SWIG.

*/

#include "../include/dicomhero6/image.h"
#include "../implementation/imageImpl.h"
#include "../implementation/dataHandlerImpl.h"
#include "../implementation/dataHandlerNumericImpl.h"

namespace dicomhero
{

Image::Image(const std::shared_ptr<implementation::image>& pImage): m_pImage(pImage)
{
}

Image::Image(const Image &source): m_pImage(getImageImplementation(source))
{
}

Image::~Image()
{
}

const std::shared_ptr<implementation::image>& getImageImplementation(const Image& source)
{
    return source.m_pImage;
}

std::uint32_t Image::getWidth() const
{
    std::uint32_t width, height;
    m_pImage->getSize(&width, &height);
    return width;
}

std::uint32_t Image::getHeight() const
{
    std::uint32_t width, height;
    m_pImage->getSize(&width, &height);
    return height;
}

ReadingDataHandlerNumeric Image::getReadingDataHandler() const
{
    return ReadingDataHandlerNumeric(m_pImage->getReadingDataHandler());
}

std::string Image::getColorSpace() const
{
    return m_pImage->getColorSpace();
}

std::uint32_t Image::getChannelsNumber() const
{
    return m_pImage->getChannelsNumber();
}

bitDepth_t Image::getDepth() const
{
    return m_pImage->getDepth();
}

std::uint32_t Image::getHighBit() const
{
    return m_pImage->getHighBit();
}

Image::Image(
        std::uint32_t width,
        std::uint32_t height,
        bitDepth_t depth,
        const std::string& colorSpace,
        std::uint32_t highBit):
    Image(std::make_shared<implementation::image>(width, height, depth, colorSpace, highBit))
{
}

WritingDataHandlerNumeric Image::getWritingDataHandler()
{
    DICOMHERO_FUNCTION_START();

    return WritingDataHandlerNumeric(getImageImplementation(*this)->getWritingDataHandler());

    DICOMHERO_FUNCTION_END_LOG();
}

}
