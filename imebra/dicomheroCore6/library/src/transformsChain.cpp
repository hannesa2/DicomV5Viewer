/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file transformsChain.cpp
    \brief Implementation of the TransformsChain class.

*/

#include "../include/dicomhero6/transformsChain.h"
#include "../implementation/transformsChainImpl.h"

namespace dicomhero
{

TransformsChain::TransformsChain(): Transform(std::make_shared<dicomhero::implementation::transforms::transformsChain>())
{
}

TransformsChain::TransformsChain(const TransformsChain& source): Transform(source)
{
}

TransformsChain::~TransformsChain()
{
}

void TransformsChain::addTransform(const Transform& transform)
{
    DICOMHERO_FUNCTION_START();

    ((dicomhero::implementation::transforms::transformsChain*)m_pTransform.get())->addTransform(getTransformImplementation(transform));

    DICOMHERO_FUNCTION_END_LOG();
}

}
