/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file streamCodecImpl.cpp
    \brief Implementation of the base class for the stream codecs.

*/

#include "exceptionImpl.h"
#include "streamReaderImpl.h"
#include "streamWriterImpl.h"
#include "streamCodecImpl.h"
#include "dataSetImpl.h"
#include "codecFactoryImpl.h"
#include "../include/dicomhero6/exceptions.h"
#include <string.h>


namespace dicomhero
{

namespace implementation
{

namespace codecs
{

streamCodec::~streamCodec()
{
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Read a stream and write it into a dataset.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
std::shared_ptr<dataSet> streamCodec::read(std::shared_ptr<streamReader> pSourceStream, std::uint32_t maxSizeBufferLoad /* = 0xffffffff */) const
{
    DICOMHERO_FUNCTION_START();

    // Create a new dataset
    ///////////////////////////////////////////////////////////
    std::shared_ptr<dataSet> pDestDataSet(std::make_shared<dataSet>("", charsetsList_t()));

    // Read the stream
    ///////////////////////////////////////////////////////////
    readStream(pSourceStream, pDestDataSet, maxSizeBufferLoad);

    return pDestDataSet;

    DICOMHERO_FUNCTION_END();
}


///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
//
//
// Write a dataset into a stream.
//
//
///////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////
void streamCodec::write(std::shared_ptr<streamWriter> pDestStream, std::shared_ptr<dataSet> pSourceDataSet) const
{
    DICOMHERO_FUNCTION_START();

    pDestStream->resetOutBitsBuffer();
    writeStream(pDestStream, pSourceDataSet);
    pDestStream->flushDataBuffer();

    DICOMHERO_FUNCTION_END();
}

} // namespace codecs

} // namespace implementation

} // namespace dicomhero

