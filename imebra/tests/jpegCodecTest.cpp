#include <imebra/imebra.h>
#include <gtest/gtest.h>
#include <thread>
#include "buildImageForTest.h"

namespace imebra
{

namespace tests
{

// A buffer initialized to a default data type should use the data type OB
TEST(jpegCodecTest, testBaseline)
{
    for(int precision=0; precision != 2; ++precision)
    {
        std::uint32_t bits = precision == 0 ? 7 : 11;
        std::cout << "Testing baseline jpeg (" << (bits + 1) << " bits)"<< std::endl;

        std::string transferSyntax = precision == 0 ? "1.2.840.10008.1.2.4.50" : "1.2.840.10008.1.2.4.51";
        MutableDataSet dataset(transferSyntax);

        std::uint32_t width = 600;
        std::uint32_t height = 400;

        Image baselineImage = buildImageForTest(width, height, precision == 0 ? bitDepth_t::depthU8 : bitDepth_t::depthU16, bits, "RGB", 50);

        Transform transformToYBR = ColorTransformsFactory::getTransform("RGB", "YBR_FULL");
        MutableImage ybrImage = transformToYBR.allocateOutputImage(baselineImage, width, height);
        transformToYBR.runTransform(baselineImage, 0, 0, width, height, ybrImage, 0, 0);

        dataset.setImage(0, ybrImage, imageQuality_t::veryHigh);

        Image checkImage = dataset.getImage(0);

        std::uint32_t checkWidth(checkImage.getWidth()), checkHeight(checkImage.getHeight());
        Transform transformToRGB = ColorTransformsFactory::getTransform("YBR_FULL", "RGB");
        MutableImage rgbImage = transformToRGB.allocateOutputImage(checkImage, checkWidth, checkHeight);
        transformToRGB.runTransform(checkImage, 0, 0, checkWidth, checkHeight, rgbImage, 0, 0);

        // Compare the buffers. A little difference is allowed
        double differenceRGB = compareImages(baselineImage, rgbImage);
        double differenceYBR = compareImages(ybrImage, checkImage);
        ASSERT_LE(differenceRGB, 5);
        ASSERT_LE(differenceYBR, 1);

        // Save jpeg, reload jpeg and check
        MutableMemory memory;
        {
            MemoryStreamOutput streamOutput(memory);
            StreamWriter writer(streamOutput);
            CodecFactory::save(dataset, writer, codecType_t::jpeg);
        }
        MemoryStreamInput streamInput(memory);
        StreamReader reader(streamInput);
        DataSet checkDataSet(CodecFactory::load(reader));
        Image checkJpegImage(checkDataSet.getImage(0));
        double differenceJPG = compareImages(ybrImage, checkJpegImage);
        ASSERT_LE(differenceJPG, 1);

    }
}


TEST(jpegCodecTest, testBaselineSubsampled)
{
    for(int subsampledX = 0; subsampledX != 2; ++subsampledX)
    {
        for(int subsampledY = 0; subsampledY != 2; ++subsampledY)
        {
            for(int interleaved = 0; interleaved != 2; ++interleaved)
            {
                for(int prematureEoi(0); prematureEoi != 2; ++prematureEoi)
                {
                    std::uint32_t width = 300;
                    std::uint32_t height = 200;
                    Image baselineImage = buildSubsampledImage(width, height, bitDepth_t::depthU8, 7, "RGB");

                    Transform colorTransform = ColorTransformsFactory::getTransform("RGB", "YBR_FULL");
                    MutableImage ybrImage = colorTransform.allocateOutputImage(baselineImage, width, height);
                    colorTransform.runTransform(baselineImage, 0, 0, width, height, ybrImage, 0, 0);

                    MutableMemory savedJpeg;
                    {
                        MemoryStreamOutput saveStream(savedJpeg);
                        StreamWriter writer(saveStream);

                        CodecFactory::saveImage(writer, ybrImage, "1.2.840.10008.1.2.4.50", imageQuality_t::veryHigh, 8, subsampledX != 0, subsampledY != 0, interleaved != 0, false);
                    }
                    if(prematureEoi == 1)
                    {
                        // Insert a premature EOI tag
                        /////////////////////////////
                        size_t dataSize;
                        std::uint8_t* pData = reinterpret_cast<std::uint8_t*>(savedJpeg.data(&dataSize));
                        pData[dataSize - 10] = 0xff;
                        pData[dataSize - 9] = 0xd9;
                    }

                    // Insert an unknown tag immediately after the jpeg signature
                    MutableMemory savedJpegUnknownTag(savedJpeg.size() + 128);
                    size_t dummy;
                    ::memcpy(savedJpegUnknownTag.data(&dummy), savedJpeg.data(&dummy), 2);
                    ::memcpy(savedJpegUnknownTag.data(&dummy) + 130, savedJpeg.data(&dummy) + 2, savedJpeg.size() - 2);
                    savedJpegUnknownTag.data(&dummy)[2] = static_cast<char>(0xff);
                    savedJpegUnknownTag.data(&dummy)[3] = 0x10;
                    savedJpegUnknownTag.data(&dummy)[4] = 0;
                    savedJpegUnknownTag.data(&dummy)[5] = 124;

                    MemoryStreamInput loadStream(savedJpegUnknownTag);
                    StreamReader reader(loadStream);

                    DataSet readDataSet = CodecFactory::load(reader, 0xffff);

                    try
                    {
                        Image checkImage = readDataSet.getImage(0);
                        ASSERT_TRUE(prematureEoi == 0);

                        std::uint32_t checkWidth(checkImage.getWidth()), checkHeight(checkImage.getHeight());
                        Transform transformToRGB = ColorTransformsFactory::getTransform("YBR_FULL", "RGB");
                        MutableImage rgbImage = transformToRGB.allocateOutputImage(checkImage, checkWidth, checkHeight);
                        transformToRGB.runTransform(checkImage, 0, 0, checkWidth, checkHeight, rgbImage, 0, 0);

                        // Compare the buffers. A little difference is allowed
                        double differenceRGB = compareImages(baselineImage, rgbImage);
                        double differenceYBR = compareImages(ybrImage, checkImage);
                        ASSERT_LE(differenceRGB, (1 + subsampledX) * (1 + subsampledY) * 50);
                        ASSERT_LE(differenceYBR, (1 + subsampledX) * (1 + subsampledY) * 25);
                    }
                    catch(const CodecCorruptedFileError&)
                    {
                        ASSERT_TRUE(prematureEoi == 1);
                    }

                }
            }
        }
    }
}


TEST(jpegCodecTest, testLossless)
{
    for(int interleaved = 0; interleaved != 2; ++interleaved)
    {
        for(std::uint32_t bits = 8; bits <= 16; bits += 8)
        {
            for(int firstOrderPrediction = 0; firstOrderPrediction != 2; ++firstOrderPrediction)
            {
                for(int b2Complement = 0; b2Complement != 2; ++b2Complement)
                {
                    for(int colorSpace(0); colorSpace != 2; ++colorSpace)
                    {
                        std::cout <<
                                     "Testing lossless jpeg (" << (bits) <<
                                     " bits, interleaved=" << interleaved <<
                                     ", firstOrderPrediction=" << firstOrderPrediction <<
                                     ", 2complement=" << b2Complement <<
                                     ", colorSpace=" << (colorSpace == 0 ? "RGB" : "MONOCHROME2") <<
                                     ")"<< std::endl;

                        std::string transferSyntax = (firstOrderPrediction == 0) ? "1.2.840.10008.1.2.4.57" : "1.2.840.10008.1.2.4.70";

                        std::uint32_t width = 115;
                        std::uint32_t height = 400;

                        bitDepth_t depth;
                        if(bits <= 8)
                        {
                            depth = (b2Complement == 1) ? bitDepth_t::depthS8 : bitDepth_t::depthU8;
                        }
                        else
                        {
                            depth = (b2Complement == 1) ? bitDepth_t::depthS16 : bitDepth_t::depthU16;
                        }

                        Image image = buildImageForTest(width, height, depth, bits - 1, colorSpace == 0 ? "RGB" : "MONOCHROME2", 50);


                        MutableMemory savedJpeg;
                        {
                            MutableDataSet dataSet(transferSyntax);
                            dataSet.setImage(0, image, imageQuality_t::veryHigh);

                            MemoryStreamOutput saveStream(savedJpeg);
                            StreamWriter writer(saveStream);
                            CodecFactory::save(dataSet, writer, codecType_t::dicom);
                        }

                        MemoryStreamInput loadStream(savedJpeg);
                        StreamReader reader(loadStream);

                        DataSet readDataSet = CodecFactory::load(reader, 0xffff);

                        Image checkImage = readDataSet.getImage(0);

                        // Compare the buffers
                        double difference = compareImages(image, checkImage);
                        ASSERT_DOUBLE_EQ(0.0, difference);
                    }
                }
            }
        }
    }
}


void feedJpegDataThread(PipeStream& source, DataSet& dataSet)
{
    StreamWriter writer(source.getStreamOutput());

    CodecFactory::save(dataSet, writer, codecType_t::jpeg);

    source.close(5000);
}


TEST(jpegCodecTest, codecFactoryPipe)
{
    MutableDataSet testDataSet("1.2.840.10008.1.2.4.50");

    const std::uint32_t width = 600;
    const std::uint32_t height = 400;

    Image baselineImage(buildImageForTest(width, height, bitDepth_t::depthU8, 7, "RGB", 50));

    Transform transformToYBR(ColorTransformsFactory::getTransform("RGB", "YBR_FULL"));
    MutableImage ybrImage(transformToYBR.allocateOutputImage(baselineImage, width, height));
    transformToYBR.runTransform(baselineImage, 0, 0, width, height, ybrImage, 0, 0);
    testDataSet.setImage(0, ybrImage, imageQuality_t::veryHigh);

    PipeStream source(1024);

    std::thread feedData(imebra::tests::feedJpegDataThread, std::ref(source), std::ref(testDataSet));

    StreamReader reader(source.getStreamInput());
    DataSet loadedDataSet(CodecFactory::load(reader));

    feedData.join();

    Image checkImage(loadedDataSet.getImage(0));

    std::uint32_t checkWidth(checkImage.getWidth()), checkHeight(checkImage.getHeight());
    Transform transformToRGB(ColorTransformsFactory::getTransform("YBR_FULL", "RGB"));
    MutableImage rgbImage(transformToRGB.allocateOutputImage(checkImage, checkWidth, checkHeight));
    transformToRGB.runTransform(checkImage, 0, 0, checkWidth, checkHeight, rgbImage, 0, 0);

    // Compare the buffers. A little difference is allowed
    double differenceRGB = compareImages(baselineImage, rgbImage);
    double differenceYBR = compareImages(ybrImage, checkImage);
    ASSERT_LE(differenceRGB, 5);
    ASSERT_LE(differenceYBR, 1);
}

} // namespace tests

} // namespace imebra
