#include <imebra/imebra.h>
#include <stdlib.h>
#include <memory.h>
#include <algorithm>
#include <gtest/gtest.h>
#include "buildImageForTest.h"

namespace imebra
{

namespace tests
{


imebra::Image buildImageForTest(
    std::uint32_t pixelsX,
    std::uint32_t pixelsY,
    imebra::bitDepth_t depth,
    std::uint32_t highBit,
    const std::string& colorSpace,
    std::uint32_t continuity)
{
    MutableImage newImage(pixelsX, pixelsY, depth, colorSpace, highBit);
    WritingDataHandler handler = newImage.getWritingDataHandler();
    std::uint32_t channelsNumber = newImage.getChannelsNumber();

    std::int64_t range = (std::int64_t)1 << (highBit + 1);
    std::int64_t minValue = 0;
    if(depth == bitDepth_t::depthS32 || depth == bitDepth_t::depthS16 || depth == bitDepth_t::depthS8)
    {
        minValue = (std::int64_t)-1 * ((std::int64_t)1 << (highBit));
    }
    std::int64_t maxValue(minValue + range);

    std::uint32_t index(0);
    for(std::uint32_t scanY(0); scanY != pixelsY; ++scanY)
    {
        for(std::uint32_t scanX(0); scanX != pixelsX; ++scanX)
        {
            for(std::uint32_t scanChannels = 0; scanChannels != channelsNumber; ++scanChannels)
            {
                std::int64_t value = (std::int64_t)((scanX + scanY) % continuity) * (std::int64_t)range / (std::int64_t)(continuity - 1) + minValue;
                if(value < minValue)
                {
                    value = minValue;
                }
                if(value >= maxValue)
                {
                    value = maxValue - 1;
                }
                if(depth == bitDepth_t::depthS32 || depth == bitDepth_t::depthS16 || depth == bitDepth_t::depthS8)
                {
                    handler.setInt32(index++, (std::int32_t)value);
                }
                else
                {
                    handler.setUint32(index++, (std::uint32_t)value);
                }
            }
        }
    }

    return newImage;
}

TEST(buildImage, testBuildImage)
{
    Image testImage = buildImageForTest(
        400,
        300,
        imebra::bitDepth_t::depthU8,
        7,
        "RGB",
        50);

    std::uint32_t r, g, b, maxR, maxG, maxB, minR, minG, minB, midR;

    ReadingDataHandlerNumeric handler = testImage.getReadingDataHandler();
    size_t index(0);

    for(size_t scanY(0); scanY != 300; ++scanY)
    {
        for(size_t scanX(0); scanX != 400; ++scanX)
        {
            if(index == 0)
            {
                midR = maxR = minR = handler.getUint32(index++);
                maxG = minG = handler.getUint32(index++);
                maxB = minB = handler.getUint32(index++);
            }
            else
            {
                r = handler.getUint32(index++);
                g = handler.getUint32(index++);
                b = handler.getUint32(index++);
                maxR = std::max(maxR, r);
                maxG = std::max(maxG, g);
                maxB = std::max(maxB, b);
                minR = std::min(minR, r);
                minG = std::min(minG, g);
                minB = std::min(minB, b);

                if(r != maxR && r != minR)
                {
                    midR = r;
                }
            }
        }
    }
    EXPECT_EQ((std::uint32_t)0, minR);
    EXPECT_EQ((std::uint32_t)0, minG);
    EXPECT_EQ((std::uint32_t)0, minB);
    EXPECT_EQ((std::uint32_t)255, maxR);
    EXPECT_EQ((std::uint32_t)255, maxG);
    EXPECT_EQ((std::uint32_t)255, maxB);
    EXPECT_GT(midR, minR);
    EXPECT_LT(midR, maxR);
}


TEST(buildImage, testCompareImage)
{
    Image testImage0 = buildImageForTest(
        400,
        300,
        imebra::bitDepth_t::depthU8,
        7,
        "RGB",
        50);

    Image testImage1 = buildImageForTest(
        400,
        300,
        imebra::bitDepth_t::depthU8,
        7,
        "RGB",
        10);

    EXPECT_DOUBLE_EQ(0.0, compareImages(testImage0, testImage0));
    EXPECT_GT(compareImages(testImage0, testImage1), 10.0);

}


imebra::Image buildSubsampledImage(
    std::uint32_t pixelsX,
    std::uint32_t pixelsY,
    imebra::bitDepth_t depth,
    std::uint32_t highBit,
    const std::string& colorSpace)
{
    MutableImage newImage(pixelsX, pixelsY, depth, colorSpace, highBit);

    {
        WritingDataHandler handler = newImage.getWritingDataHandler();
        std::uint32_t channelsNumber = newImage.getChannelsNumber();


        std::uint32_t index(0);

        std::vector<std::int32_t> previousRow(channelsNumber * pixelsX);

        std::int32_t highValue ((1 << highBit) - 1);
        std::int32_t lowValue (0);
        if(depth == imebra::bitDepth_t::depthS16 || depth == imebra::bitDepth_t::depthS8 || depth == imebra::bitDepth_t::depthS32)
        {
            highValue = ((1 << (highBit - 1)) - 1);
            lowValue = -highValue - 1;
        }
        std::vector<std::int32_t> values(channelsNumber);
        values[0] = lowValue;
        for(std::uint32_t subsampledChannels(1); subsampledChannels < channelsNumber; ++subsampledChannels)
        {
            values[subsampledChannels] = lowValue + 4 * static_cast<std::int32_t>(subsampledChannels);
        }
        for(std::uint32_t scanY(0); scanY != pixelsY; ++scanY)
        {
            for(std::uint32_t scanX(0); scanX != pixelsX; ++scanX)
            {
                for(std::uint32_t scanChannels = 0; scanChannels != channelsNumber; ++scanChannels)
                {
                    if(scanChannels == 0)
                    {
                        handler.setInt32(index++, values[scanChannels]);
                        if(++values[scanChannels] > highValue)
                        {
                            values[scanChannels] = lowValue;
                        }
                    }
                    else
                    {
                        if((scanY & 1u) == 1u)
                        {
                            handler.setInt32(index++, previousRow[scanX * channelsNumber + scanChannels]);
                        }
                        else if((scanX & 1u) == 1u)
                        {
                            previousRow[scanX * channelsNumber + scanChannels] = previousRow[scanX * channelsNumber + scanChannels - channelsNumber];
                            handler.setInt32(index++, previousRow[scanX * channelsNumber + scanChannels]);
                        }
                        else
                        {
                            previousRow[scanX * channelsNumber + scanChannels] = values[scanChannels];
                            handler.setInt32(index++, values[scanChannels]);
                            if(++values[scanChannels] > highValue)
                            {
                                values[scanChannels] = lowValue;
                            }
                        }
                    }

                }
            }
        }
    }
    return newImage;
}


double compareImages(const imebra::Image& image0, const imebra::Image& image1)
{
    size_t width0(image0.getWidth()), height0(image0.getHeight());
    size_t width1(image1.getWidth()), height1(image1.getHeight());

    if(width0 != width1 || height0 != height1)
    {
        return 1000;
    }

    std::uint32_t channelsNumber0(image0.getChannelsNumber());
    std::uint32_t channelsNumber1(image1.getChannelsNumber());
    if(channelsNumber0 != channelsNumber1)
    {
        return 1000;
    }

    ReadingDataHandler hImage0 = image0.getReadingDataHandler();
    ReadingDataHandler hImage1 = image1.getReadingDataHandler();

    std::uint32_t highBit0 = image0.getHighBit();
    std::uint32_t highBit1 = image1.getHighBit();
    if(highBit0 != highBit1)
    {
        return 1000;
    }

    bitDepth_t depth0 = image0.getDepth();
    bitDepth_t depth1 = image1.getDepth();
    if(depth0 != depth1)
    {
        return 1000;
    }

    if(width0 == 0 || height0 == 0)
    {
        return 0;
    }

    size_t valuesNum = width0 * height0 * channelsNumber0;
    std::uint64_t divisor = valuesNum;
    std::uint64_t range = (std::int64_t)1 << image0.getHighBit();
    std::uint64_t difference(0);
    size_t index(0);
    std::uint64_t total(0);
    for(size_t y(0); y != height0; ++y)
    {
        for(size_t x(0); x != width0; ++x)
        {
            for(size_t ch(0); ch != channelsNumber0; ++ch)
            {
                if(depth0 == bitDepth_t::depthS32 || depth0 == bitDepth_t::depthS16 || depth0 == bitDepth_t::depthS8)
                {
                    std::int32_t p0 = hImage0.getInt32(index);
                    std::int32_t p1 = hImage1.getInt32(index);
                    if(p0 > p1)
                    {
                        difference += (1000 * (std::uint64_t)(p0 - p1)) / range;
                    }
                    else
                    {
                        difference += (1000 * (std::uint64_t)(p1 - p0)) / range;
                    }
                    total += difference;
                }
                else
                {
                    std::uint32_t p0 = hImage0.getUint32(index);
                    std::uint32_t p1 = hImage1.getUint32(index);
                    if(p0 > p1)
                    {
                        difference += (1000 * (std::uint64_t)(p0 - p1)) / range;
                    }
                    else
                    {
                        difference += (1000 * (std::uint64_t)(p1 - p0)) / range;
                    }
                    total += difference;

                }
                ++index;
            }
        }
    }

    return (double)difference / (double)divisor;
}

bool identicalImages(const imebra::Image& image0, const imebra::Image& image1)
{
    size_t width0(image0.getWidth()), height0(image0.getHeight());
    size_t width1(image1.getWidth()), height1(image1.getHeight());

    if(width0 != width1 || height0 != height1)
    {
        return false;
    }

    std::uint32_t channelsNumber0(image0.getChannelsNumber());
    std::uint32_t channelsNumber1(image1.getChannelsNumber());
    if(channelsNumber0 != channelsNumber1)
    {
        return false;
    }

    ReadingDataHandlerNumeric hImage0 = image0.getReadingDataHandler();
    ReadingDataHandlerNumeric hImage1 = image1.getReadingDataHandler();

    std::uint32_t highBit0 = image0.getHighBit();
    std::uint32_t highBit1 = image1.getHighBit();
    if(highBit0 != highBit1)
    {
        return false;
    }

    bitDepth_t depth0 = image0.getDepth();
    bitDepth_t depth1 = image1.getDepth();
    if(depth0 != depth1)
    {
        return false;
    }

    if(width0 == 0 || height0 == 0)
    {
        return true;
    }

    Memory memory0(hImage0.getMemory());
    Memory memory1(hImage1.getMemory());
    size_t dataSize0, dataSize1;
    const char* pData0(memory0.data(&dataSize0));
    const char* pData1(memory1.data(&dataSize1));

    for(size_t scan(0); scan != dataSize0; ++scan)
    {
        if(pData0[scan] != pData1[scan])
        {
            return false;
        }
    }

    return ::memcmp(pData0, pData1, dataSize0) == 0;
}

} // namespace tests

} // namespace imebra
