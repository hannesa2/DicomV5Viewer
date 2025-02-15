#include <imebra/imebra.h>
#include "buildImageForTest.h"
#include <gtest/gtest.h>


namespace imebra
{

namespace tests
{

TEST(transformsChain, emptyChain)
{
    TransformsChain chain;

    ASSERT_TRUE(chain.isEmpty());

    MutableImage rgb(100, 100, bitDepth_t::depthU8, "RGB", 7);

    {
        WritingDataHandler rgbHandler= rgb.getWritingDataHandler();
        size_t pointer(0);
        for(std::uint32_t y(0); y != 100; ++y)
        {
            for(std::uint32_t x(0); x != 100; ++x)
            {
                rgbHandler.setUint32(pointer++, y);
                rgbHandler.setUint32(pointer++, x);
                rgbHandler.setUint32(pointer++, 255);
            }
        }
    }

    MutableImage outputImage = chain.allocateOutputImage(rgb, 100, 100);

    chain.runTransform(rgb, 0, 0, 100, 100, outputImage, 0, 0);

    identicalImages(rgb, outputImage);
}


TEST(transformsChain, oneTransform)
{
    TransformsChain chain;

    ASSERT_TRUE(chain.isEmpty());

    TransformHighBit highBit;

    chain.addTransform(highBit);

    ASSERT_FALSE(chain.isEmpty());

    MutableImage rgb(100, 100, bitDepth_t::depthU8, "RGB", 7);

    {
        WritingDataHandler rgbHandler = rgb.getWritingDataHandler();
        size_t pointer(0);
        for(std::uint32_t y(0); y != 100; ++y)
        {
            for(std::uint32_t x(0); x != 100; ++x)
            {
                rgbHandler.setUint32(pointer++, y);
                rgbHandler.setUint32(pointer++, x);
                rgbHandler.setUint32(pointer++, 255);
            }
        }
    }

    MutableImage outputImage = chain.allocateOutputImage(rgb, 100, 100);

    chain.runTransform(rgb, 0, 0, 100, 100, outputImage, 0, 0);

    identicalImages(rgb, outputImage);
}


TEST(transformsChain, twoTransform)
{
    TransformsChain chain;

    ASSERT_TRUE(chain.isEmpty());

    Transform monochromeToRgb = ColorTransformsFactory::getTransform("MONOCHROME2", "RGB");
    Transform rgbToMonochrome = ColorTransformsFactory::getTransform("RGB", "MONOCHROME2");

    chain.addTransform(monochromeToRgb);
    chain.addTransform(rgbToMonochrome);

    ASSERT_FALSE(chain.isEmpty());

    MutableImage monochrome(100, 100, bitDepth_t::depthU8, "MONOCHROME2", 7);

    {
        WritingDataHandler rgbHandler = monochrome.getWritingDataHandler();
        size_t pointer(0);
        for(std::uint32_t y(0); y != 100; ++y)
        {
            for(std::uint32_t x(0); x != 100; ++x)
            {
                rgbHandler.setUint32(pointer++, y);
            }
        }
    }

    MutableImage outputImage = chain.allocateOutputImage(monochrome, 100, 100);

    chain.runTransform(monochrome, 0, 0, 100, 100, outputImage, 0, 0);

    identicalImages(monochrome, outputImage);
}

}

}

