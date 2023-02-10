/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

/*! \file codecFactory.cpp
    \brief Implementation of the class used to retrieve the codec able to
        handle the requested transfer syntax.

*/

#include "../include/dicomhero6/fileStreamInput.h"
#include "../include/dicomhero6/fileStreamOutput.h"
#include "../include/dicomhero6/codecFactory.h"
#include "../include/dicomhero6/definitions.h"
#include "../implementation/codecFactoryImpl.h"
#include "../implementation/streamCodecImpl.h"
#include "../implementation/imageCodecImpl.h"
#include "../implementation/exceptionImpl.h"

namespace dicomhero
{

DataSet CodecFactory::load(StreamReader& reader, size_t maxSizeBufferLoad /*  = std::numeric_limits<size_t>::max()) */)
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<dicomhero::implementation::codecs::codecFactory> factory(dicomhero::implementation::codecs::codecFactory::getCodecFactory());
    return DataSet(factory->load(reader.m_pReader, (std::uint32_t)maxSizeBufferLoad));

    DICOMHERO_FUNCTION_END_LOG();
}

DataSet CodecFactory::load(const std::wstring& fileName, size_t maxSizeBufferLoad)
{
    DICOMHERO_FUNCTION_START();

    FileStreamInput file(fileName);

    StreamReader reader(file);
    return load(reader, maxSizeBufferLoad);

    DICOMHERO_FUNCTION_END_LOG();
}

DataSet CodecFactory::load(const std::string& fileName, size_t maxSizeBufferLoad)
{
    DICOMHERO_FUNCTION_START();

    FileStreamInput file(fileName);

    StreamReader reader(file);
    return load(reader, maxSizeBufferLoad);

    DICOMHERO_FUNCTION_END_LOG();
}

void CodecFactory::saveImage(
        StreamWriter& destStream,
        const Image& sourceImage,
        const std::string& transferSyntax,
        imageQuality_t imageQuality,
        std::uint32_t allocatedBits,
        bool bSubSampledX,
        bool bSubSampledY,
        bool bInterleaved,
        bool b2Complement)
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<dicomhero::implementation::codecs::codecFactory> factory(dicomhero::implementation::codecs::codecFactory::getCodecFactory());
    std::shared_ptr<const implementation::codecs::imageCodec> pCodec = factory->getImageCodec(transferSyntax);
    pCodec->setImage(destStream.m_pWriter, getImageImplementation(sourceImage), transferSyntax, imageQuality, allocatedBits, bSubSampledX, bSubSampledY, bInterleaved, b2Complement);

    DICOMHERO_FUNCTION_END_LOG();
}

void CodecFactory::setMaximumImageSize(const std::uint32_t maximumWidth, const std::uint32_t maximumHeight)
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<dicomhero::implementation::codecs::codecFactory> factory(dicomhero::implementation::codecs::codecFactory::getCodecFactory());
    factory->setMaximumImageSize(maximumWidth, maximumHeight);

    DICOMHERO_FUNCTION_END_LOG();

}


void CodecFactory::save(const DataSet& dataSet, StreamWriter& writer, codecType_t codecType)
{
    DICOMHERO_FUNCTION_START();

    std::shared_ptr<dicomhero::implementation::codecs::codecFactory> factory(dicomhero::implementation::codecs::codecFactory::getCodecFactory());
    std::shared_ptr<const implementation::codecs::streamCodec> pCodec = factory->getStreamCodec(codecType);

    pCodec->write(writer.m_pWriter, getDataSetImplementation(dataSet));

    DICOMHERO_FUNCTION_END_LOG();
}

void CodecFactory::save(const DataSet &dataSet, const std::wstring& fileName, codecType_t codecType)
{
    DICOMHERO_FUNCTION_START();

    FileStreamOutput file(fileName);

    StreamWriter writer(file);
    CodecFactory::save(dataSet, writer, codecType);

    DICOMHERO_FUNCTION_END_LOG();
}

void CodecFactory::save(const DataSet &dataSet, const std::string& fileName, codecType_t codecType)
{
    DICOMHERO_FUNCTION_START();

    FileStreamOutput file(fileName);

    StreamWriter writer(file);
    CodecFactory::save(dataSet, writer, codecType);

    DICOMHERO_FUNCTION_END_LOG();
}


}
