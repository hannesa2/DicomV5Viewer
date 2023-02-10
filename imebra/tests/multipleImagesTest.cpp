/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include <imebra/imebra.h>
#include "buildImageForTest.h"
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{

TEST(multipleImagesTest, testLosslessImages)
{
    const size_t numImages(64);

    for(int transferSyntaxId(0); transferSyntaxId != 6; ++transferSyntaxId)
    {
        const std::uint32_t highBit(7);

        const std::string colorSpace("MONOCHROME2");

        const bitDepth_t depth(bitDepth_t::depthU8);

        Image dicomImage = buildImageForTest(
                    1024,
                    1024,
                    depth,
                    highBit,
                    colorSpace,
                    2);

        std::string transferSyntax;
        switch(transferSyntaxId)
        {
        case 0:
            transferSyntax = "1.2.840.10008.1.2.4.57";
            break;
        case 1:
            transferSyntax = "1.2.840.10008.1.2.4.70";
            break;
        case 2:
            transferSyntax = "1.2.840.10008.1.2";
            break;
        case 3:
            transferSyntax = "1.2.840.10008.1.2.1";
            break;
        case 4:
            transferSyntax = "1.2.840.10008.1.2.2";
            break;
        case 5:
            transferSyntax = "1.2.840.10008.1.2.5";
            break;
        }

        std::cout << "Multiple images dicom test. Transfer syntax: " << transferSyntax << std::endl;

        const imageQuality_t quality = imageQuality_t::veryHigh;

        MutableMemory streamMemory;
        {
            MutableDataSet testDataSet(transferSyntax);
            testDataSet.setDouble(TagId(tagId_t::TimeRange_0008_1163), 50.6);
            if(ColorTransformsFactory::getNumberOfChannels(colorSpace) > 1)
            {
                testDataSet.setUint32(TagId(imebra::tagId_t::PlanarConfiguration_0028_0006), 1);
            }

            for(size_t imageNumber(0); imageNumber != numImages; ++imageNumber)
            {
                std::cout << "Adding image: " << imageNumber << std::endl;
                testDataSet.setImage(imageNumber, dicomImage, quality);
            }

            MemoryStreamOutput writeStream(streamMemory);
            StreamWriter writer(writeStream);
            CodecFactory::save(testDataSet, writer, codecType_t::dicom);
        }

        for(unsigned int lazyLoad(0); lazyLoad != 2; ++lazyLoad)
        {
            MemoryStreamInput readStream(streamMemory);
            StreamReader reader(readStream);
            DataSet testDataSet = CodecFactory::load(reader, lazyLoad == 0 ? std::numeric_limits<size_t>::max() : 1);

            for(size_t imageNumber(0); imageNumber != numImages; ++imageNumber)
            {
                Image checkImage = testDataSet.getImage(imageNumber);
                ASSERT_TRUE(identicalImages(checkImage, dicomImage));
            }
        }
    } // transferSyntaxId
}

}

}
