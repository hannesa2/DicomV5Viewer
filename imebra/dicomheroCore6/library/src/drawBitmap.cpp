/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file drawBitmap.cpp
    \brief Implementation of the class DrawBitmap.

*/

#include "../include/dicomhero6/drawBitmap.h"
#include "../implementation/drawBitmapImpl.h"
#include "../include/dicomhero6/image.h"
#include "../include/dicomhero6/transform.h"

namespace dicomhero
{

DrawBitmap::DrawBitmap():
    m_pDrawBitmap(std::make_shared<implementation::drawBitmap>(std::shared_ptr<implementation::transforms::transform>()))
{
}

DrawBitmap::DrawBitmap(const Transform& transform):
    m_pDrawBitmap(std::make_shared<implementation::drawBitmap>(transform.m_pTransform))
{
}

DrawBitmap::DrawBitmap(const DrawBitmap& source): m_pDrawBitmap(getDrawBitmapImplementation(source))
{
}

const std::shared_ptr<implementation::drawBitmap>& getDrawBitmapImplementation(const DrawBitmap& drawBitmap)
{
    return drawBitmap.m_pDrawBitmap;
}

DrawBitmap::~DrawBitmap()
{
}

size_t DrawBitmap::getBitmap(const Image& image, drawBitmapType_t drawBitmapType, std::uint32_t rowAlignBytes, char* buffer, size_t bufferSize)
{
    DICOMHERO_FUNCTION_START();

    return m_pDrawBitmap->getBitmap(getImageImplementation(image), drawBitmapType, rowAlignBytes, (std::uint8_t*)buffer, bufferSize);

    DICOMHERO_FUNCTION_END_LOG();
}

Memory DrawBitmap::getBitmap(const Image& image, drawBitmapType_t drawBitmapType, std::uint32_t rowAlignBytes)
{
    DICOMHERO_FUNCTION_START();

    return Memory(m_pDrawBitmap->getBitmap(getImageImplementation(image), drawBitmapType, rowAlignBytes));

    DICOMHERO_FUNCTION_END_LOG();
}

}
