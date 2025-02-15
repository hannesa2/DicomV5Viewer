#include <dicomhero6/dicomhero.h>
#include "buildImageForTest.h"
#include <gtest/gtest.h>


namespace dicomhero
{

namespace tests
{

TEST(voilut, voilutUnsigned8)
{
    Image unsigned8(7, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);
    {
        WritingDataHandler unsigned8Handler = unsigned8.getWritingDataHandler();
        unsigned8Handler.setUint32(0, 0);
        unsigned8Handler.setUint32(1, 10);
        unsigned8Handler.setUint32(2, 20);
        unsigned8Handler.setUint32(3, 30);
        unsigned8Handler.setUint32(4, 40);
        unsigned8Handler.setUint32(5, 50);
        unsigned8Handler.setUint32(6, 60);
    }

    {
        VOILUT voilut(VOIDescription(0, 50, dicomVOIFunction_t::linear, ""));

        Image unsigned8Out = voilut.allocateOutputImage(unsigned8, 7, 1);
        voilut.runTransform(unsigned8, 0, 0, 7, 1, unsigned8Out, 0, 0);

        ReadingDataHandler unsigned8Handler = unsigned8Out.getReadingDataHandler();

        EXPECT_LE(129u, unsigned8Handler.getUint32(0));
        EXPECT_GE(131u, unsigned8Handler.getUint32(0));

        EXPECT_LE(181u, unsigned8Handler.getUint32(1));
        EXPECT_GE(183u, unsigned8Handler.getUint32(1));

        EXPECT_LE(233u, unsigned8Handler.getUint32(2));
        EXPECT_GE(235u, unsigned8Handler.getUint32(2));

        EXPECT_EQ(255u, unsigned8Handler.getUint32(3));
        EXPECT_EQ(255u, unsigned8Handler.getUint32(4));
        EXPECT_EQ(255u, unsigned8Handler.getUint32(5));
        EXPECT_EQ(255u, unsigned8Handler.getUint32(6));
    }

    {
        VOILUT voilut(VOIDescription(15, 1, dicomVOIFunction_t::linear, ""));

        Image unsigned8Out = voilut.allocateOutputImage(unsigned8, 7, 1);
        voilut.runTransform(unsigned8, 0, 0, 7, 1, unsigned8Out, 0, 0);

        ReadingDataHandler unsigned8Handler = unsigned8Out.getReadingDataHandler();

        EXPECT_EQ(0u, unsigned8Handler.getUint32(0));
        EXPECT_EQ(0u, unsigned8Handler.getUint32(1));
        EXPECT_EQ(255u, unsigned8Handler.getUint32(2));
        EXPECT_EQ(255u, unsigned8Handler.getUint32(3));
        EXPECT_EQ(255u, unsigned8Handler.getUint32(4));
        EXPECT_EQ(255u, unsigned8Handler.getUint32(5));
        EXPECT_EQ(255u, unsigned8Handler.getUint32(6));
    }

    {
        VOILUT voilut(VOIDescription(70, 50, dicomVOIFunction_t::linear, ""));

        Image signed16Out(7, 1, bitDepth_t::depthS16, "MONOCHROME2", 15);
        voilut.runTransform(unsigned8, 0, 0, 7, 1, signed16Out, 0, 0);

        ReadingDataHandler signed16Handler = signed16Out.getReadingDataHandler();

        EXPECT_EQ(-32768, signed16Handler.getInt32(0));
        EXPECT_EQ(-32768, signed16Handler.getInt32(1));
        EXPECT_EQ(-32768, signed16Handler.getInt32(2));
        EXPECT_EQ(-32768, signed16Handler.getInt32(3));
        EXPECT_EQ(-32768, signed16Handler.getInt32(4));

        EXPECT_LE(-26081, signed16Handler.getInt32(5));
        EXPECT_GE(-26079, signed16Handler.getInt32(5));

        EXPECT_LE(-12707, signed16Handler.getInt32(6));
        EXPECT_GE(-12705, signed16Handler.getInt32(6));
    }

    {
        VOILUT voilut(VOIDescription(0, 50, dicomVOIFunction_t::linearExact, ""));

        Image unsigned8Out = voilut.allocateOutputImage(unsigned8, 7, 1);
        voilut.runTransform(unsigned8, 0, 0, 7, 1, unsigned8Out, 0, 0);

        ReadingDataHandler unsigned8Handler = unsigned8Out.getReadingDataHandler();

        EXPECT_EQ(0u, unsigned8Handler.getUint32(0));

        EXPECT_LE(50u, unsigned8Handler.getUint32(1));
        EXPECT_GE(52u, unsigned8Handler.getUint32(1));

        EXPECT_LE(101u, unsigned8Handler.getUint32(2));
        EXPECT_GE(103u, unsigned8Handler.getUint32(2));

        EXPECT_LE(152u, unsigned8Handler.getUint32(3));
        EXPECT_GE(154u, unsigned8Handler.getUint32(3));

        EXPECT_LE(203u, unsigned8Handler.getUint32(4));
        EXPECT_GE(205u, unsigned8Handler.getUint32(4));

        EXPECT_EQ(255u, unsigned8Handler.getUint32(5));
        EXPECT_EQ(255u, unsigned8Handler.getUint32(6));
    }

    {
        VOILUT voilut(VOIDescription(70, 50, dicomVOIFunction_t::linearExact, ""));

        Image signed16Out(7, 1, bitDepth_t::depthS16, "MONOCHROME2", 15);
        voilut.runTransform(unsigned8, 0, 0, 7, 1, signed16Out, 0, 0);

        ReadingDataHandler signed16Handler = signed16Out.getReadingDataHandler();

        EXPECT_EQ(-32768, signed16Handler.getInt32(0));
        EXPECT_EQ(-32768, signed16Handler.getInt32(1));
        EXPECT_EQ(-32768, signed16Handler.getInt32(2));
        EXPECT_EQ(-32768, signed16Handler.getInt32(3));
        EXPECT_EQ(-32768, signed16Handler.getInt32(4));
        EXPECT_EQ(-32768, signed16Handler.getInt32(5));
        EXPECT_EQ(-32768, signed16Handler.getInt32(6));
    }

    {
        VOILUT voilut(VOIDescription(0, 50, dicomVOIFunction_t::sigmoid, ""));

        Image unsigned8Out = voilut.allocateOutputImage(unsigned8, 7, 1);
        voilut.runTransform(unsigned8, 0, 0, 7, 1, unsigned8Out, 0, 0);

        ReadingDataHandler unsigned8Handler = unsigned8Out.getReadingDataHandler();

        EXPECT_LE(126u, unsigned8Handler.getUint32(0));
        EXPECT_GE(128u, unsigned8Handler.getUint32(0));

        EXPECT_LE(174u, unsigned8Handler.getUint32(1));
        EXPECT_GE(176u, unsigned8Handler.getUint32(1));

        EXPECT_LE(211u, unsigned8Handler.getUint32(2));
        EXPECT_GE(213u, unsigned8Handler.getUint32(2));

        EXPECT_LE(232u, unsigned8Handler.getUint32(3));
        EXPECT_GE(234u, unsigned8Handler.getUint32(3));

        EXPECT_LE(244u, unsigned8Handler.getUint32(4));
        EXPECT_GE(246u, unsigned8Handler.getUint32(4));

        EXPECT_LE(249u, unsigned8Handler.getUint32(5));
        EXPECT_GE(251u, unsigned8Handler.getUint32(5));

        EXPECT_LE(251u, unsigned8Handler.getUint32(6));
        EXPECT_GE(253u, unsigned8Handler.getUint32(6));
    }

    {
        VOILUT voilut(VOIDescription(70, 50, dicomVOIFunction_t::sigmoid, ""));

        Image signed16Out(7, 1, bitDepth_t::depthS16, "MONOCHROME2", 15);
        voilut.runTransform(unsigned8, 0, 0, 7, 1, signed16Out, 0, 0);

        ReadingDataHandler signed16Handler = signed16Out.getReadingDataHandler();

        EXPECT_LE(240, signed16Handler.getInt32(0));
        EXPECT_GE(242, signed16Handler.getInt32(0));

        EXPECT_LE(533, signed16Handler.getInt32(1));
        EXPECT_GE(535, signed16Handler.getInt32(1));

        EXPECT_LE(1177, signed16Handler.getInt32(2));
        EXPECT_GE(1179, signed16Handler.getInt32(2));

        EXPECT_LE(2565, signed16Handler.getInt32(3));
        EXPECT_GE(2567, signed16Handler.getInt32(3));

        EXPECT_LE(5449, signed16Handler.getInt32(4));
        EXPECT_GE(5451, signed16Handler.getInt32(4));

        EXPECT_LE(11007, signed16Handler.getInt32(5));
        EXPECT_GE(11009, signed16Handler.getInt32(5));

        EXPECT_LE(20316, signed16Handler.getInt32(6));
        EXPECT_GE(20318, signed16Handler.getInt32(6));
    }
}


TEST(voilut, voilutUnsigned8OptimalVOI)
{
    Image unsigned8(6, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);
    {
        WritingDataHandler unsigned8Handler = unsigned8.getWritingDataHandler();
        unsigned8Handler.setUint32(0, 10);
        unsigned8Handler.setUint32(1, 0);
        unsigned8Handler.setUint32(2, 20);
        unsigned8Handler.setUint32(3, 30);
        unsigned8Handler.setUint32(4, 40);
        unsigned8Handler.setUint32(5, 50);
    }

    VOIDescription voiDescription = VOILUT::getOptimalVOI(unsigned8, 0, 0, 6, 1);
    VOILUT voilut(voiDescription);

    Image unsigned8Out = voilut.allocateOutputImage(unsigned8, 6, 1);
    voilut.runTransform(unsigned8, 0, 0, 6, 1, unsigned8Out, 0, 0);

    ReadingDataHandler unsigned8Handler = unsigned8Out.getReadingDataHandler();

    EXPECT_LE(51u, unsigned8Handler.getUint32(0));
    EXPECT_GE(53u, unsigned8Handler.getUint32(0));

    EXPECT_LE(0u, unsigned8Handler.getUint32(1));
    EXPECT_GE(1u, unsigned8Handler.getUint32(1));

    EXPECT_LE(103u, unsigned8Handler.getUint32(2));
    EXPECT_GE(105u, unsigned8Handler.getUint32(2));

    EXPECT_LE(155u, unsigned8Handler.getUint32(3));
    EXPECT_GE(157u, unsigned8Handler.getUint32(3));

    EXPECT_LE(207u, unsigned8Handler.getUint32(4));
    EXPECT_GE(209u, unsigned8Handler.getUint32(4));

    EXPECT_LE(254u, unsigned8Handler.getUint32(5));
    EXPECT_GE(255u, unsigned8Handler.getUint32(5));

    Image signed16Out(6, 1, bitDepth_t::depthS16, "MONOCHROME2", 15);
    voilut.runTransform(unsigned8, 0, 0, 6, 1, signed16Out, 0, 0);

    ReadingDataHandler signed16Handler = signed16Out.getReadingDataHandler();

    std::cout << voiDescription.getCenter() << " " << voiDescription.getWidth() << " " << signed16Handler.getInt32(0) << std::endl;

    EXPECT_LE(-19394, signed16Handler.getInt32(0));
    EXPECT_GE(-19392, signed16Handler.getInt32(0));

    EXPECT_LE(-32768, signed16Handler.getInt32(1));
    EXPECT_GE(-32767, signed16Handler.getInt32(1));

    EXPECT_LE(-6020, signed16Handler.getInt32(2));
    EXPECT_GE(-6018, signed16Handler.getInt32(2));

    EXPECT_LE(7354, signed16Handler.getInt32(3));
    EXPECT_GE(7356, signed16Handler.getInt32(3));

    EXPECT_LE(20728, signed16Handler.getInt32(4));
    EXPECT_GE(20730, signed16Handler.getInt32(4));

    EXPECT_LE(32766, signed16Handler.getInt32(5));
    EXPECT_GE(32768, signed16Handler.getInt32(5));
}


TEST(voilut, voilutUnsigned8LUT)
{
    Image unsigned8(6, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);
    {
        WritingDataHandler unsigned8Handler = unsigned8.getWritingDataHandler();
        unsigned8Handler.setUint32(0, 0);
        unsigned8Handler.setUint32(1, 1);
        unsigned8Handler.setUint32(2, 2);
        unsigned8Handler.setUint32(3, 3);
        unsigned8Handler.setUint32(4, 4);
        unsigned8Handler.setUint32(5, 5);
    }

    DataSet testDataSet;
    Tag sequenceTag = testDataSet.getTagCreate(TagId(tagId_t::VOILUTSequence_0028_3010));
    DataSet lutItem = sequenceTag.appendSequenceItem();
    {
        WritingDataHandlerNumeric descriptor = lutItem.getWritingDataHandlerNumeric(TagId(tagId_t::LUTDescriptor_0028_3002), 0, tagVR_t::US);
        WritingDataHandlerNumeric data = lutItem.getWritingDataHandlerNumeric(TagId(tagId_t::LUTData_0028_3006), 0, tagVR_t::US);
        descriptor.setUint32(0, 3);
        descriptor.setUint32(1, 2);
        descriptor.setUint32(2, 16);

        data.setUint32(0, 100);
        data.setUint32(1, 200);
        data.setUint32(2, 300);
    }
    LUT lut = testDataSet.getLUT(TagId(tagId_t::VOILUTSequence_0028_3010), 0);

    VOILUT voilut(lut);

    Image paletteOut = voilut.allocateOutputImage(unsigned8, 6, 1);
    voilut.runTransform(unsigned8, 0, 0, 6, 1, paletteOut, 0, 0);

    ReadingDataHandler paletteHandler = paletteOut.getReadingDataHandler();

    EXPECT_EQ(100u, paletteHandler.getUint32(0));
    EXPECT_EQ(100u, paletteHandler.getUint32(1));
    EXPECT_EQ(100u, paletteHandler.getUint32(2));
    EXPECT_EQ(200u, paletteHandler.getUint32(3));
    EXPECT_EQ(300u, paletteHandler.getUint32(4));
    EXPECT_EQ(300u, paletteHandler.getUint32(5));

}

}

}

