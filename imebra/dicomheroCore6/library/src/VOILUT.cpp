/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file VOILUT.cpp
    \brief Implementation of VOILUT.

*/


#include "../include/dicomhero6/VOILUT.h"
#include "../include/dicomhero6/dataSet.h"
#include "../include/dicomhero6/VOIDescription.h"
#include "../implementation/VOILUTImpl.h"
#include "../include/dicomhero6/lut.h"

namespace dicomhero
{

VOILUT::VOILUT(const VOILUT& source): Transform(source)
{
}

VOILUT::VOILUT(const VOIDescription &voiDescription):
    Transform(std::make_shared<dicomhero::implementation::transforms::VOILUT>(voiDescription.getCenter(), voiDescription.getWidth(), voiDescription.getFunction()))
{
}


VOILUT::VOILUT(const LUT &lut):
    Transform(std::make_shared<dicomhero::implementation::transforms::VOILUT>(getLUTImplementation(lut)))
{
}


VOILUT::~VOILUT()
{
}

VOIDescription VOILUT::getOptimalVOI(const Image& inputImage, std::uint32_t topLeftX, std::uint32_t topLeftY, std::uint32_t width, std::uint32_t height)
{
    DICOMHERO_FUNCTION_START();

    return VOIDescription(dicomhero::implementation::transforms::VOILUT::getOptimalVOI(getImageImplementation(inputImage), topLeftX, topLeftY, width, height));

    DICOMHERO_FUNCTION_END_LOG();
}

}
