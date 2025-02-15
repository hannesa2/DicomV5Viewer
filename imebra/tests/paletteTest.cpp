#include <imebra/imebra.h>
#include <gtest/gtest.h>

namespace imebra
{

namespace tests
{


// A buffer initialized to a default data type should use the data type OB
TEST(paletteTest, testPalette)
{
    MutableDataSet testDataSet("1.2.840.10008.1.2.1");

    {
        WritingDataHandlerNumeric redDescriptor = testDataSet.getWritingDataHandlerNumeric(TagId(tagId_t::RedPaletteColorLookupTableDescriptor_0028_1101), 0, tagVR_t::US);
        WritingDataHandlerNumeric redData = testDataSet.getWritingDataHandlerNumeric(TagId(tagId_t::RedPaletteColorLookupTableData_0028_1201), 0, tagVR_t::US);
        redDescriptor.setUint32(0, 256);
        redDescriptor.setUint32(1, 0);
        redDescriptor.setUint32(2, 8);

        WritingDataHandlerNumeric greenDescriptor = testDataSet.getWritingDataHandlerNumeric(TagId(tagId_t::GreenPaletteColorLookupTableDescriptor_0028_1102), 0, tagVR_t::US);
        WritingDataHandlerNumeric greenData = testDataSet.getWritingDataHandlerNumeric(TagId(tagId_t::GreenPaletteColorLookupTableData_0028_1202), 0, tagVR_t::US);
        greenDescriptor.setUint32(0, 256);
        greenDescriptor.setUint32(1, 0);
        greenDescriptor.setUint32(2, 8);

        WritingDataHandlerNumeric blueDescriptor = testDataSet.getWritingDataHandlerNumeric(TagId(tagId_t::BluePaletteColorLookupTableDescriptor_0028_1103), 0, tagVR_t::US);
        WritingDataHandlerNumeric blueData = testDataSet.getWritingDataHandlerNumeric(TagId(tagId_t::BluePaletteColorLookupTableData_0028_1203), 0, tagVR_t::US);
        blueDescriptor.setUint32(0, 256);
        blueDescriptor.setUint32(1, 0);
        blueDescriptor.setUint32(2, 8);

        for(std::uint32_t fillPalette(0); fillPalette != 256; fillPalette += 2)
        {
            redData.setUint32(fillPalette / 2, ((fillPalette + 10) & 0xff) | (((fillPalette + 11) & 0xff) << 8));
            greenData.setUint32(fillPalette / 2, ((fillPalette + 21) & 0xff) | (((fillPalette + 22) & 0xff) << 8));
            blueData.setUint32(fillPalette / 2, ((fillPalette + 32) & 0xff) | (((fillPalette + 33) & 0xff) << 8));
        }
    }

    std::uint32_t sizeX(300), sizeY(300);
    MutableImage paletteImage(sizeX, sizeY, bitDepth_t::depthU8, "MONOCHROME2", 7);

    {
        WritingDataHandlerNumeric imageHandler = paletteImage.getWritingDataHandler();

        std::uint32_t pointer(0);

        // Make 3 bands (RGB)
        for(std::uint32_t y=0; y<sizeY; ++y)
        {
            for(std::uint32_t x=0; x<sizeX; ++x)
            {
                imageHandler.setUint32(pointer, pointer & 0xff);
                ++pointer;
            }
        }
    }

    testDataSet.setImage(0, paletteImage, imageQuality_t::veryHigh);
    testDataSet.setString(TagId(tagId_t::PhotometricInterpretation_0028_0004), "PALETTE COLOR");

    Transform colorTransform = ColorTransformsFactory::getTransform("PALETTE COLOR", "RGB");
    Image storedImage = testDataSet.getImage(0);
    MutableImage rgbImage = colorTransform.allocateOutputImage(storedImage, sizeX, sizeY);

    colorTransform.runTransform(storedImage, 0, 0, sizeX, sizeY, rgbImage, 0, 0);

    ASSERT_EQ(sizeX, rgbImage.getWidth());
    ASSERT_EQ(sizeY, rgbImage.getHeight());

    ReadingDataHandlerNumeric rgbHandler = rgbImage.getReadingDataHandler();

    std::uint32_t pointer = 0;
    size_t rgbPointer = 0;
    for(std::uint32_t checkY = 0; checkY < sizeY; ++checkY)
    {
        for(std::uint32_t checkX = 0; checkX < sizeX; ++checkX)
        {
            std::uint32_t r = rgbHandler.getUint32(rgbPointer++);
            std::uint32_t g = rgbHandler.getUint32(rgbPointer++);
            std::uint32_t b = rgbHandler.getUint32(rgbPointer++);

            ASSERT_EQ(((pointer & 0xff) + 10) & 0xff, r);
            ASSERT_EQ(((pointer & 0xff) + 21) & 0xff, g);
            ASSERT_EQ(((pointer & 0xff) + 32) & 0xff, b);

            ++pointer;
        }
    }
}


// A buffer initialized to a default data type should use the data type OB
TEST(paletteTest, testPalette16bit)
{
    MutableDataSet testDataSet("1.2.840.10008.1.2.1");

    {
        WritingDataHandlerNumeric redDescriptor = testDataSet.getWritingDataHandlerNumeric(TagId(tagId_t::RedPaletteColorLookupTableDescriptor_0028_1101), 0, tagVR_t::US);
        WritingDataHandlerNumeric redData = testDataSet.getWritingDataHandlerNumeric(TagId(tagId_t::RedPaletteColorLookupTableData_0028_1201), 0, tagVR_t::US);
        redDescriptor.setUint32(0, 256);
        redDescriptor.setUint32(1, 0);
        redDescriptor.setUint32(2, 16);

        WritingDataHandlerNumeric greenDescriptor = testDataSet.getWritingDataHandlerNumeric(TagId(tagId_t::GreenPaletteColorLookupTableDescriptor_0028_1102), 0, tagVR_t::US);
        WritingDataHandlerNumeric greenData = testDataSet.getWritingDataHandlerNumeric(TagId(tagId_t::GreenPaletteColorLookupTableData_0028_1202), 0, tagVR_t::US);
        greenDescriptor.setUint32(0, 256);
        greenDescriptor.setUint32(1, 0);
        greenDescriptor.setUint32(2, 16);

        WritingDataHandlerNumeric blueDescriptor = testDataSet.getWritingDataHandlerNumeric(TagId(tagId_t::BluePaletteColorLookupTableDescriptor_0028_1103), 0, tagVR_t::US);
        WritingDataHandlerNumeric blueData = testDataSet.getWritingDataHandlerNumeric(TagId(tagId_t::BluePaletteColorLookupTableData_0028_1203), 0, tagVR_t::US);
        blueDescriptor.setUint32(0, 256);
        blueDescriptor.setUint32(1, 0);
        blueDescriptor.setUint32(2, 16);

        for(std::uint32_t fillPalette(0); fillPalette != 256; fillPalette++)
        {
            redData.setUint32(fillPalette, (fillPalette + 10) & 0xff);
            greenData.setUint32(fillPalette, (fillPalette + 21) & 0xff);
            blueData.setUint32(fillPalette, (fillPalette + 32) & 0xff);
        }
    }

    std::uint32_t sizeX(300), sizeY(300);
    MutableImage paletteImage(sizeX, sizeY, bitDepth_t::depthU8, "MONOCHROME2", 7);

    {
        WritingDataHandlerNumeric imageHandler = paletteImage.getWritingDataHandler();

        std::uint32_t pointer(0);

        // Make 3 bands (RGB)
        for(std::uint32_t y=0; y<sizeY; ++y)
        {
            for(std::uint32_t x=0; x<sizeX; ++x)
            {
                imageHandler.setUint32(pointer, pointer & 0xff);
                ++pointer;
            }
        }
    }

    testDataSet.setImage(0, paletteImage, imageQuality_t::veryHigh);
    testDataSet.setString(TagId(tagId_t::PhotometricInterpretation_0028_0004), "PALETTE COLOR");

    Transform colorTransform = ColorTransformsFactory::getTransform("PALETTE COLOR", "RGB");
    Image storedImage = testDataSet.getImage(0);
    MutableImage rgbImage = colorTransform.allocateOutputImage(storedImage, sizeX, sizeY);

    colorTransform.runTransform(storedImage, 0, 0, sizeX, sizeY, rgbImage, 0, 0);

    ASSERT_EQ(sizeX, rgbImage.getWidth());
    ASSERT_EQ(sizeY, rgbImage.getHeight());

    ReadingDataHandlerNumeric rgbHandler = rgbImage.getReadingDataHandler();

    std::uint32_t pointer = 0;
    size_t rgbPointer = 0;
    for(std::uint32_t checkY = 0; checkY < sizeY; ++checkY)
    {
        for(std::uint32_t checkX = 0; checkX < sizeX; ++checkX)
        {
            std::uint32_t r = rgbHandler.getUint32(rgbPointer++);
            std::uint32_t g = rgbHandler.getUint32(rgbPointer++);
            std::uint32_t b = rgbHandler.getUint32(rgbPointer++);

            ASSERT_EQ(((pointer & 0xff) + 10) & 0xff, r);
            ASSERT_EQ(((pointer & 0xff) + 21) & 0xff, g);
            ASSERT_EQ(((pointer & 0xff) + 32) & 0xff, b);

            ++pointer;
        }
    }
}


} // namespace tests

} // namespace imebra
