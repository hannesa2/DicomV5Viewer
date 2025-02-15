/*
Copyright 2005 - 2019 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file overlay.cpp
    \brief Implementation of the class Overlay.

*/

#include "../include/dicomhero6/definitions.h"
#include "../include/dicomhero6/overlay.h"
#include "../include/dicomhero6/image.h"
#include "../include/dicomhero6/exceptions.h"
#include "../implementation/overlayImpl.h"
#include "../implementation/exceptionImpl.h"
#include <string>

namespace dicomhero
{

Overlay::Overlay(const Overlay& source): m_pOverlay(getOverlayImplementation(source))
{
}

Overlay::~Overlay()
{
}

std::uint32_t Overlay::getFirstFrame() const
{
    return m_pOverlay->getFirstFrame();
}

std::uint32_t Overlay::getFramesCount() const
{
    return m_pOverlay->getFramesCount();
}

std::int32_t Overlay::getZeroBasedOriginX() const
{
    return m_pOverlay->getZeroBasedOriginX();
}

std::int32_t Overlay::getZeroBasedOriginY() const
{
    return m_pOverlay->getZeroBasedOriginY();
}

std::int32_t Overlay::getOneBasedOriginX() const
{
    return m_pOverlay->getOneBasedOriginX();
}

std::int32_t Overlay::getOneBasedOriginY() const
{
    return m_pOverlay->getOneBasedOriginY();
}

overlayType_t Overlay::getType() const
{
    return m_pOverlay->getType();
}

std::string Overlay::getSubType() const
{
    return m_pOverlay->getSubType();
}

std::wstring Overlay::getUnicodeLabel() const
{
    return m_pOverlay->getUnicodeLabel();
}

std::string Overlay::getLabel() const
{
    return m_pOverlay->getLabel();
}

std::wstring Overlay::getUnicodeDescription() const
{
    return m_pOverlay->getUnicodeDescription();
}

std::string Overlay::getDescription() const
{
    return m_pOverlay->getDescription();
}

std::uint32_t Overlay::getROIArea() const
{
    DICOMHERO_FUNCTION_START();

    if(m_pOverlay->getROIAreaPresent())
    {
        return m_pOverlay->getROIArea();
    }
    else
    {
        DICOMHERO_THROW(MissingTagError, "ROI Area not present");
    }

    DICOMHERO_FUNCTION_END();
}

double Overlay::getROIMean() const
{
    DICOMHERO_FUNCTION_START();

    if(m_pOverlay->getROIMeanPresent())
    {
        return m_pOverlay->getROIMean();
    }
    else
    {
        DICOMHERO_THROW(MissingTagError, "ROI Mean not present");
    }

    DICOMHERO_FUNCTION_END();
}

double Overlay::getROIStandardDeviation()
{
    DICOMHERO_FUNCTION_START();

    if(m_pOverlay->getROIStandardDeviationPresent())
    {
        return m_pOverlay->getROIStandardDeviation();
    }
    else
    {
        DICOMHERO_THROW(MissingTagError, "ROI Standard Deviation not present");
    }

    DICOMHERO_FUNCTION_END();
}


Image Overlay::getImage(std::uint32_t frame) const
{
    DICOMHERO_FUNCTION_START();

    return Image(m_pOverlay->getImage(frame));

    DICOMHERO_FUNCTION_END();
}

Overlay::Overlay(const std::shared_ptr<dicomhero::implementation::overlay>& pOverlay): m_pOverlay(pOverlay)
{
}

const std::shared_ptr<implementation::overlay>& getOverlayImplementation(const Overlay& overlay)
{
    return overlay.m_pOverlay;
}


Overlay::Overlay(
        overlayType_t overlayType,
        const std::string& overlaySubType,
        std::uint32_t firstFrame,
        std::int32_t zeroBasedOriginX, std::int32_t zeroBasedOriginY,
        const std::wstring& label,
        const std::wstring& description):
    Overlay(std::make_shared<implementation::overlay>(
                overlayType, overlaySubType,
                firstFrame,
                zeroBasedOriginX,
                zeroBasedOriginY,
                label,
                description))
{
}


Overlay::Overlay(
        overlayType_t overlayType,
        const std::string& overlaySubType,
        std::uint32_t firstFrame,
        std::int32_t zeroBasedOriginX, std::int32_t zeroBasedOriginY,
        const std::string& label,
        const std::string& description):
    Overlay(std::make_shared<implementation::overlay>(
                overlayType, overlaySubType,
                firstFrame,
                zeroBasedOriginX,
                zeroBasedOriginY,
                label,
                description))
{
}


void Overlay::setROIArea(std::uint32_t pixels)
{
    getOverlayImplementation(*this)->setROIArea(pixels);
}

void Overlay::setROIMean(double mean)
{
    getOverlayImplementation(*this)->setROIMean(mean);
}

void Overlay::setROIStandardDeviation(double standardDeviation)
{
    getOverlayImplementation(*this)->setROIStandardDeviation(standardDeviation);
}

void Overlay::setImage(std::uint32_t frame, const Image& image)
{
    DICOMHERO_FUNCTION_START();

    getOverlayImplementation(*this)->setImage(frame, getImageImplementation(image));

    DICOMHERO_FUNCTION_END();
}

}

