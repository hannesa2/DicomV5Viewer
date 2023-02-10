/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file transformsHighBit.cpp
    \brief Implementation of the TransformsHighBit class.

*/

#include "../include/dicomhero6/transformHighBit.h"
#include "../implementation/transformHighBitImpl.h"


namespace dicomhero
{

TransformHighBit::TransformHighBit(): Transform(std::make_shared<dicomhero::implementation::transforms::transformHighBit>())
{
}

TransformHighBit::TransformHighBit(const TransformHighBit& source): Transform(source)
{
}

TransformHighBit::~TransformHighBit()
{
}

}
