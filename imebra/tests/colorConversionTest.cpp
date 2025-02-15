#include <imebra/imebra.h>
#include "buildImageForTest.h"
#include <gtest/gtest.h>


namespace imebra
{

namespace tests
{

TEST(colorConversion, RGB2YBRFULL)
{
    for(int ict(0); ict != 2; ++ict)
    {
        MutableImage rgb(1, 1, bitDepth_t::depthU8, "RGB", 7);

        {
            WritingDataHandler rgbHandler = rgb.getWritingDataHandler();
            rgbHandler.setUint32(0, 255);
            rgbHandler.setUint32(1, 255);
            rgbHandler.setUint32(2, 255);
        }

        std::string destinationColorSpace(ict == 0 ? "YBR_FULL" : "YBR_ICT");
        Transform rgb2ybr = ColorTransformsFactory::getTransform("RGB", destinationColorSpace);

        MutableImage ybr(1, 1, bitDepth_t::depthU8, destinationColorSpace, 7);
        rgb2ybr.runTransform(rgb, 0, 0, 1, 1, ybr, 0, 0);

        ReadingDataHandler ybr1Handler = ybr.getReadingDataHandler();
        ASSERT_EQ(255, ybr1Handler.getInt32(0));
        ASSERT_EQ(128, ybr1Handler.getInt32(1));
        ASSERT_EQ(128, ybr1Handler.getInt32(2));
    }
}


TEST(colorConversion, RGB2YBRRCT)
{
    MutableImage rgb(255, 255, bitDepth_t::depthU8, "RGB", 7);

    {
        WritingDataHandler rgbHandler = rgb.getWritingDataHandler();
        for(std::uint32_t y = 0; y != 255u; ++y)
        {
            for(std::uint32_t x = 0; x != 255u; ++x)
            {
                rgbHandler.setUint32((x + y * 50u) * 3u, x);
                rgbHandler.setUint32((x + y * 50u) * 3u + 1u, y);
                rgbHandler.setUint32((x + y * 50u) * 3u + 2u, (y + x) / 2u);
            }
        }
    }


    Transform rgb2ybr = ColorTransformsFactory::getTransform("RGB", "YBR_RCT");
    MutableImage ybr = rgb2ybr.allocateOutputImage(rgb, 255, 255);
    rgb2ybr.runTransform(rgb, 0, 0, 255, 255, ybr, 0, 0);

    Transform ybr2rgb = ColorTransformsFactory::getTransform("YBR_RCT", "RGB");
    MutableImage rgb1 = ybr2rgb.allocateOutputImage(ybr, 255, 255);
    ybr2rgb.runTransform(ybr, 0, 0, 255, 255, rgb1, 0, 0);

    ASSERT_GE(1.0, compareImages(rgb, rgb1)); // Account for ceiling/floor adjustment
}


TEST(colorConversion, RGB2YBRPARTIAL)
{
    MutableImage rgb(3, 1, bitDepth_t::depthU8, "RGB", 7);

    {
        WritingDataHandler rgbHandler = rgb.getWritingDataHandler();
        rgbHandler.setUint32(0, 255u);
        rgbHandler.setUint32(1, 255u);
        rgbHandler.setUint32(2, 255u);
        rgbHandler.setUint32(3, 0u);
        rgbHandler.setUint32(4, 0u);
        rgbHandler.setUint32(5, 0u);
        rgbHandler.setUint32(6, 255u);
        rgbHandler.setUint32(7, 0u);
        rgbHandler.setUint32(8, 0u);
    }

    Transform rgb2ybr = ColorTransformsFactory::getTransform("RGB", "YBR_PARTIAL");

    MutableImage ybr(3, 1, bitDepth_t::depthU8, "YBR_PARTIAL", 7);
    rgb2ybr.runTransform(rgb, 0, 0, 3, 1, ybr, 0, 0);

    ReadingDataHandler ybr1Handler = ybr.getReadingDataHandler();
    ASSERT_EQ(235, ybr1Handler.getInt32(0));
    ASSERT_EQ(128, ybr1Handler.getInt32(1));
    ASSERT_EQ(128, ybr1Handler.getInt32(2));
    ASSERT_EQ(16, ybr1Handler.getInt32(3));
    ASSERT_EQ(128, ybr1Handler.getInt32(4));
    ASSERT_EQ(128, ybr1Handler.getInt32(5));
    ASSERT_EQ(81, ybr1Handler.getInt32(6));
    ASSERT_EQ(91, ybr1Handler.getInt32(7));
    ASSERT_EQ(240, ybr1Handler.getInt32(8));
}


TEST(colorConversion, RGB2MONOCHROME2)
{
    MutableImage rgb(2, 1, bitDepth_t::depthU8, "RGB", 7);

    {
        WritingDataHandler rgbHandler = rgb.getWritingDataHandler();
        rgbHandler.setUint32(0, 255);
        rgbHandler.setUint32(1, 255);
        rgbHandler.setUint32(2, 255);
        rgbHandler.setUint32(3, 0);
        rgbHandler.setUint32(4, 0);
        rgbHandler.setUint32(5, 0);
    }

    Transform toMonochrome2 = ColorTransformsFactory::getTransform("RGB", "MONOCHROME2");

    MutableImage monochrome2(2, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);
    toMonochrome2.runTransform(rgb, 0, 0, 2, 1, monochrome2, 0, 0);

    ReadingDataHandler monochromeHandler = monochrome2.getReadingDataHandler();
    ASSERT_EQ(255, monochromeHandler.getInt32(0));
    ASSERT_EQ(0, monochromeHandler.getInt32(1));
}


TEST(colorConversion, RGB2MONOCHROME1)
{
    MutableImage rgb(2, 1, bitDepth_t::depthU8, "RGB", 7);

    {
        WritingDataHandler rgbHandler = rgb.getWritingDataHandler();
        rgbHandler.setUint32(0, 255u);
        rgbHandler.setUint32(1, 255u);
        rgbHandler.setUint32(2, 255u);
        rgbHandler.setUint32(3, 0u);
        rgbHandler.setUint32(4, 0u);
        rgbHandler.setUint32(5, 0u);
    }

    Transform toMonochrome1 = ColorTransformsFactory::getTransform("RGB", "MONOCHROME1");

    MutableImage monochrome1(2, 1, bitDepth_t::depthU8, "MONOCHROME1", 7);
    toMonochrome1.runTransform(rgb, 0, 0, 2, 1, monochrome1, 0, 0);

    ReadingDataHandler monochromeHandler = monochrome1.getReadingDataHandler();
    ASSERT_EQ(0, monochromeHandler.getInt32(0));
    ASSERT_EQ(255, monochromeHandler.getInt32(1));
}


TEST(colorConversion, MONOCHROME12MONOCHROME2)
{
    MutableImage monochrome1(3, 1, bitDepth_t::depthU8, "MONOCHROME1", 7);

    {
        WritingDataHandler monochrome1Handler = monochrome1.getWritingDataHandler();
        monochrome1Handler.setUint32(0, 255);
        monochrome1Handler.setUint32(1, 254);
        monochrome1Handler.setUint32(2, 253);
    }

    Transform toMonochrome2 = ColorTransformsFactory::getTransform("MONOCHROME1", "MONOCHROME2");

    MutableImage monochrome2(3, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);
    toMonochrome2.runTransform(monochrome1, 0, 0, 3, 1, monochrome2, 0, 0);

    ReadingDataHandler monochrome2Handler = monochrome2.getReadingDataHandler();
    ASSERT_EQ(0, monochrome2Handler.getInt32(0));
    ASSERT_EQ(1, monochrome2Handler.getInt32(1));
    ASSERT_EQ(2, monochrome2Handler.getInt32(2));
}


TEST(colorConversion, MONOCHROME12RGB)
{
    MutableImage monochrome1(3, 1, bitDepth_t::depthU8, "MONOCHROME1", 7);

    {
        WritingDataHandler monochrome1Handler = monochrome1.getWritingDataHandler();
        monochrome1Handler.setUint32(0, 255u);
        monochrome1Handler.setUint32(1, 254u);
        monochrome1Handler.setUint32(2, 253u);
    }

    Transform toRGB = ColorTransformsFactory::getTransform("MONOCHROME1", "RGB");

    MutableImage rgb(3, 1, bitDepth_t::depthU8, "RGB", 7);
    toRGB.runTransform(monochrome1, 0, 0, 3, 1, rgb, 0, 0);

    ReadingDataHandler rgbHandler(rgb.getReadingDataHandler());
    ASSERT_EQ(0, rgbHandler.getInt32(0));
    ASSERT_EQ(0, rgbHandler.getInt32(1));
    ASSERT_EQ(0, rgbHandler.getInt32(2));
    ASSERT_EQ(1, rgbHandler.getInt32(3));
    ASSERT_EQ(1, rgbHandler.getInt32(4));
    ASSERT_EQ(1, rgbHandler.getInt32(5));
    ASSERT_EQ(2, rgbHandler.getInt32(6));
    ASSERT_EQ(2, rgbHandler.getInt32(7));
    ASSERT_EQ(2, rgbHandler.getInt32(8));
}


TEST(colorConversion, MONOCHROME22RGB)
{
    MutableImage monochrome2(3, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);

    {
        WritingDataHandler monochrome2Handler = monochrome2.getWritingDataHandler();
        monochrome2Handler.setUint32(0, 255);
        monochrome2Handler.setUint32(1, 254);
        monochrome2Handler.setUint32(2, 253);
    }

    Transform toRGB = ColorTransformsFactory::getTransform("MONOCHROME2", "RGB");

    MutableImage rgb(3, 1, bitDepth_t::depthU8, "RGB", 7);
    toRGB.runTransform(monochrome2, 0, 0, 3, 1, rgb, 0, 0);

    ReadingDataHandler rgbHandler = rgb.getReadingDataHandler();
    ASSERT_EQ(255, rgbHandler.getInt32(0));
    ASSERT_EQ(255, rgbHandler.getInt32(1));
    ASSERT_EQ(255, rgbHandler.getInt32(2));
    ASSERT_EQ(254, rgbHandler.getInt32(3));
    ASSERT_EQ(254, rgbHandler.getInt32(4));
    ASSERT_EQ(254, rgbHandler.getInt32(5));
    ASSERT_EQ(253, rgbHandler.getInt32(6));
    ASSERT_EQ(253, rgbHandler.getInt32(7));
    ASSERT_EQ(253, rgbHandler.getInt32(8));
}


TEST(colorConversion, MONOCHROME2YBRFULL)
{
    for(int ict(0); ict != 2; ++ict)
    {
        MutableImage monochrome2(3, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);

        {
            WritingDataHandler monochrome2Handler = monochrome2.getWritingDataHandler();
            monochrome2Handler.setUint32(0, 255);
            monochrome2Handler.setUint32(1, 254);
            monochrome2Handler.setUint32(2, 253);
        }

        std::string destinationColorSpace(ict == 0 ? "YBR_FULL" : "YBR_ICT");
        Transform toYBR = ColorTransformsFactory::getTransform("MONOCHROME2", destinationColorSpace);

        MutableImage ybr(3, 1, bitDepth_t::depthU8, destinationColorSpace, 7);
        toYBR.runTransform(monochrome2, 0, 0, 3, 1, ybr, 0, 0);

        ReadingDataHandler ybrHandler = ybr.getReadingDataHandler();
        ASSERT_EQ(255, ybrHandler.getInt32(0));
        ASSERT_EQ(128, ybrHandler.getInt32(1));
        ASSERT_EQ(128, ybrHandler.getInt32(2));
        ASSERT_EQ(254, ybrHandler.getInt32(3));
        ASSERT_EQ(128, ybrHandler.getInt32(4));
        ASSERT_EQ(128, ybrHandler.getInt32(5));
        ASSERT_EQ(253, ybrHandler.getInt32(6));
        ASSERT_EQ(128, ybrHandler.getInt32(7));
        ASSERT_EQ(128, ybrHandler.getInt32(8));
    }
}


TEST(colorConversion, YBRFULL2MONOCHROME2)
{
    for(int ict(0); ict != 2; ++ict)
    {
        std::string sourceColorSpace(ict == 0 ? "YBR_FULL" : "YBR_ICT");
        MutableImage ybr(3, 1, bitDepth_t::depthU8, sourceColorSpace, 7);

        {
            WritingDataHandler ybrHandler = ybr.getWritingDataHandler();
            ybrHandler.setUint32(0, 255u);
            ybrHandler.setUint32(1, 128u);
            ybrHandler.setUint32(2, 128u);
            ybrHandler.setUint32(3, 254u);
            ybrHandler.setUint32(4, 128u);
            ybrHandler.setUint32(5, 128u);
            ybrHandler.setUint32(6, 253u);
            ybrHandler.setUint32(7, 128u);
            ybrHandler.setUint32(8, 128u);
        }

        Transform toMonochrome2 = ColorTransformsFactory::getTransform(sourceColorSpace, "MONOCHROME2");

        MutableImage monochrome2(3, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);
        toMonochrome2.runTransform(ybr, 0, 0, 3, 1, monochrome2, 0, 0);

        ReadingDataHandler monochromeHandler = monochrome2.getReadingDataHandler();
        ASSERT_EQ(255, monochromeHandler.getInt32(0));
        ASSERT_EQ(254, monochromeHandler.getInt32(1));
        ASSERT_EQ(253, monochromeHandler.getInt32(2));
    }
}


TEST(colorConversion, YBRFULL2RGB)
{
    for(int ict(0); ict != 2; ++ict)
    {
        std::string sourceColorSpace(ict == 0 ? "YBR_FULL" : "YBR_ICT");
        MutableImage ybr(1, 1, bitDepth_t::depthU8, sourceColorSpace, 7);

        {
            WritingDataHandler ybrHandler(ybr.getWritingDataHandler());
            ybrHandler.setUint32(0, 255);
            ybrHandler.setUint32(1, 128);
            ybrHandler.setUint32(2, 128);
        }

        Transform ybr2rgb(ColorTransformsFactory::getTransform(sourceColorSpace, "RGB"));

        MutableImage rgb1(1, 1, bitDepth_t::depthU8, "RGB", 7);
        ybr2rgb.runTransform(ybr, 0, 0, 1, 1, rgb1, 0, 0);
        ReadingDataHandler rgb1Handler = rgb1.getReadingDataHandler();

        ASSERT_EQ(255, rgb1Handler.getInt32(0));
        ASSERT_EQ(255, rgb1Handler.getInt32(1));
        ASSERT_EQ(255, rgb1Handler.getInt32(2));
    }
}


TEST(colorConversion, YBRPARTIAL2RGB)
{
    MutableImage ybr(5, 1, bitDepth_t::depthU8, "YBR_PARTIAL", 7);

    {
        WritingDataHandler ybrHandler = ybr.getWritingDataHandler();
        ybrHandler.setUint32(0, 235u);
        ybrHandler.setUint32(1, 128u);
        ybrHandler.setUint32(2, 128u);
        ybrHandler.setUint32(3, 255u);
        ybrHandler.setUint32(4, 128u);
        ybrHandler.setUint32(5, 128u);
        ybrHandler.setUint32(6, 16u);
        ybrHandler.setUint32(7, 128u);
        ybrHandler.setUint32(8, 128u);
        ybrHandler.setUint32(9, 0u);
        ybrHandler.setUint32(10, 128u);
        ybrHandler.setUint32(11, 128u);
        ybrHandler.setUint32(12, 81u);
        ybrHandler.setUint32(13, 91u);
        ybrHandler.setUint32(14, 240u);
    }

    Transform ybr2rgb(ColorTransformsFactory::getTransform("YBR_PARTIAL", "RGB"));

    MutableImage rgb1(5, 1, bitDepth_t::depthU8, "RGB", 7);
    ybr2rgb.runTransform(ybr, 0, 0, 5, 1, rgb1, 0, 0);
    ReadingDataHandler rgb1Handler = rgb1.getReadingDataHandler();

    ASSERT_EQ(255, rgb1Handler.getInt32(0));
    ASSERT_EQ(255, rgb1Handler.getInt32(1));
    ASSERT_EQ(255, rgb1Handler.getInt32(2));
    ASSERT_EQ(255, rgb1Handler.getInt32(3));
    ASSERT_EQ(255, rgb1Handler.getInt32(4));
    ASSERT_EQ(255, rgb1Handler.getInt32(5));
    ASSERT_EQ(0, rgb1Handler.getInt32(6));
    ASSERT_EQ(0, rgb1Handler.getInt32(7));
    ASSERT_EQ(0, rgb1Handler.getInt32(8));
    ASSERT_EQ(0, rgb1Handler.getInt32(9));
    ASSERT_EQ(0, rgb1Handler.getInt32(10));
    ASSERT_EQ(0, rgb1Handler.getInt32(11));
    ASSERT_EQ(254, rgb1Handler.getInt32(12));
    ASSERT_EQ(0, rgb1Handler.getInt32(13));
    ASSERT_EQ(1, rgb1Handler.getInt32(14));
}

TEST(colorConversion, factoryTest)
{
    ASSERT_FALSE(ColorTransformsFactory::canSubsample("RGB"));
    ASSERT_FALSE(ColorTransformsFactory::canSubsample("MONOCHROME2"));
    ASSERT_FALSE(ColorTransformsFactory::canSubsample("MONOCHROME1"));
    ASSERT_FALSE(ColorTransformsFactory::canSubsample("PALETTE COLOR"));
    ASSERT_TRUE(ColorTransformsFactory::canSubsample("YBR_FULL"));
    ASSERT_TRUE(ColorTransformsFactory::canSubsample("YBR_PARTIAL"));

    ASSERT_FALSE(ColorTransformsFactory::isMonochrome("RGB"));
    ASSERT_TRUE(ColorTransformsFactory::isMonochrome("MONOCHROME2"));
    ASSERT_TRUE(ColorTransformsFactory::isMonochrome("MONOCHROME1"));
    ASSERT_FALSE(ColorTransformsFactory::isMonochrome("PALETTE COLOR"));
    ASSERT_FALSE(ColorTransformsFactory::isMonochrome("YBR_FULL"));
    ASSERT_FALSE(ColorTransformsFactory::isMonochrome("YBR_PARTIAL"));

    ASSERT_EQ(3u, ColorTransformsFactory::getNumberOfChannels("RGB"));
    ASSERT_EQ(1u, ColorTransformsFactory::getNumberOfChannels("MONOCHROME2"));
    ASSERT_EQ(1u, ColorTransformsFactory::getNumberOfChannels("MONOCHROME1"));
    ASSERT_EQ(1u, ColorTransformsFactory::getNumberOfChannels("PALETTE COLOR"));
    ASSERT_EQ(3u, ColorTransformsFactory::getNumberOfChannels("YBR_FULL"));
    ASSERT_EQ(3u, ColorTransformsFactory::getNumberOfChannels("YBR_PARTIAL"));

    ASSERT_EQ("YBR_PARTIAL_422", ColorTransformsFactory::makeSubsampled("YBR_PARTIAL", true, false));
    ASSERT_EQ("YBR_PARTIAL_420", ColorTransformsFactory::makeSubsampled("YBR_PARTIAL", true, true));
    ASSERT_EQ("YBR_PARTIAL", ColorTransformsFactory::makeSubsampled("YBR_PARTIAL", false, false));

    ASSERT_EQ("YBR_FULL", ColorTransformsFactory::normalizeColorSpace("YBR_FULL_422"));
    ASSERT_TRUE(ColorTransformsFactory::isSubsampledX("YBR_FULL_422"));
    ASSERT_FALSE(ColorTransformsFactory::isSubsampledY("YBR_FULL_422"));
    ASSERT_TRUE(ColorTransformsFactory::isSubsampledY("YBR_FULL_420"));
    ASSERT_EQ("PALETTE COLOR", ColorTransformsFactory::normalizeColorSpace("PALETTE COLOR"));
}

}

}

