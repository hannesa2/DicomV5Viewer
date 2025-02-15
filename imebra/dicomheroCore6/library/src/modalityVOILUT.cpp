/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file modalityVOILUT.cpp
    \brief Implementation of the ModalityVOILUT class..

*/


#include "../include/dicomhero6/modalityVOILUT.h"
#include "../implementation/modalityVOILUTImpl.h"

namespace dicomhero
{

ModalityVOILUT::ModalityVOILUT(const DataSet& dataset):
    Transform(std::make_shared<dicomhero::implementation::transforms::modalityVOILUT>(getDataSetImplementation(dataset)))
{
}

ModalityVOILUT::ModalityVOILUT(const ModalityVOILUT& source): Transform(source)
{
}

ModalityVOILUT::~ModalityVOILUT()
{
}

}
