#include <imebra/imebra.h>
#include "buildImageForTest.h"
#include <gtest/gtest.h>


namespace imebra
{

namespace tests
{

TEST(modalityVoilut, voilutUnsigned8)
{
    MutableImage unsigned8(6, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);
    {
        WritingDataHandler unsigned8Handler = unsigned8.getWritingDataHandler();
        unsigned8Handler.setUint32(0, 0);
        unsigned8Handler.setUint32(1, 10);
        unsigned8Handler.setUint32(2, 20);
        unsigned8Handler.setUint32(3, 30);
        unsigned8Handler.setUint32(4, 40);
        unsigned8Handler.setUint32(5, 50);
    }

    MutableDataSet testDataSet("1.2.840.10008.1.2.1");
    testDataSet.setDouble(TagId(tagId_t::RescaleSlope_0028_1053), 2);
    testDataSet.setDouble(TagId(tagId_t::RescaleIntercept_0028_1052), -1);
    testDataSet.setImage(0, unsigned8, imageQuality_t::veryHigh);

    {
        ModalityVOILUT voilut(testDataSet);

        MutableImage signed8Out = voilut.allocateOutputImage(unsigned8, 6, 1);
        voilut.runTransform(unsigned8, 0, 0, 6, 1, signed8Out, 0, 0);
        ASSERT_EQ(bitDepth_t::depthS16, signed8Out.getDepth());

        ReadingDataHandler signed8Handler = signed8Out.getReadingDataHandler();

        ASSERT_EQ(-1, signed8Handler.getInt32(0));
        ASSERT_EQ(19, signed8Handler.getInt32(1));
        ASSERT_EQ(39, signed8Handler.getInt32(2));
        ASSERT_EQ(59, signed8Handler.getInt32(3));
        ASSERT_EQ(79, signed8Handler.getInt32(4));
        ASSERT_EQ(99, signed8Handler.getInt32(5));
    }

    {
        Image signed8Out = testDataSet.getImageApplyModalityTransform(0);
        ASSERT_EQ(bitDepth_t::depthS16, signed8Out.getDepth());

        ReadingDataHandler signed8Handler = signed8Out.getReadingDataHandler();

        ASSERT_EQ(-1, signed8Handler.getInt32(0));
        ASSERT_EQ(19, signed8Handler.getInt32(1));
        ASSERT_EQ(39, signed8Handler.getInt32(2));
        ASSERT_EQ(59, signed8Handler.getInt32(3));
        ASSERT_EQ(79, signed8Handler.getInt32(4));
        ASSERT_EQ(99, signed8Handler.getInt32(5));
    }
}


TEST(modalityVoilut, voilutUnsigned8FunctionalGroupFrame)
{
    MutableDataSet testDataSet("1.2.840.10008.1.2.1");

    MutableDataSet allFrames = testDataSet.appendSequenceItem(TagId(tagId_t::SharedFunctionalGroupsSequence_5200_9229));
    allFrames.setDouble(TagId(tagId_t::RescaleSlope_0028_1053), 2);
    allFrames.setDouble(TagId(tagId_t::RescaleIntercept_0028_1052), -3);

    MutableDataSet frame0 = testDataSet.appendSequenceItem(TagId(tagId_t::PerFrameFunctionalGroupsSequence_5200_9230));
    frame0.setDouble(TagId(tagId_t::RescaleSlope_0028_1053), 2);
    frame0.setDouble(TagId(tagId_t::RescaleIntercept_0028_1052), -1);

    MutableDataSet frame1 = testDataSet.appendSequenceItem(TagId(tagId_t::PerFrameFunctionalGroupsSequence_5200_9230));
    frame1.setDouble(TagId(tagId_t::RescaleSlope_0028_1053), 2);
    frame1.setDouble(TagId(tagId_t::RescaleIntercept_0028_1052), -2);

    MutableDataSet frame2 = testDataSet.appendSequenceItem(TagId(tagId_t::PerFrameFunctionalGroupsSequence_5200_9230));
    MutableDataSet lutItem = frame2.appendSequenceItem(TagId(tagId_t::ModalityLUTSequence_0028_3000));
    {
        WritingDataHandlerNumeric descriptor = lutItem.getWritingDataHandlerNumeric(TagId(tagId_t::LUTDescriptor_0028_3002), 0, tagVR_t::US);
        WritingDataHandlerNumeric data = lutItem.getWritingDataHandlerNumeric(TagId(tagId_t::LUTData_0028_3006), 0, tagVR_t::US);
        descriptor.setUint32(0, 3u);
        descriptor.setUint32(1, 2u);
        descriptor.setUint32(2, 16u);
        data.setUint32(0, 100u);
        data.setUint32(1, 200u);
        data.setUint32(2, 300u);
    }

    MutableImage unsigned8(6, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);
    {
        WritingDataHandler unsigned8Handler = unsigned8.getWritingDataHandler();
        unsigned8Handler.setUint32(0, 0);
        unsigned8Handler.setUint32(1, 10);
        unsigned8Handler.setUint32(2, 20);
        unsigned8Handler.setUint32(3, 30);
        unsigned8Handler.setUint32(4, 40);
        unsigned8Handler.setUint32(5, 50);
    }
    testDataSet.setImage(0, unsigned8, imageQuality_t::veryHigh);
    testDataSet.setImage(1, unsigned8, imageQuality_t::veryHigh);
    testDataSet.setImage(2, unsigned8, imageQuality_t::veryHigh);
    testDataSet.setImage(3, unsigned8, imageQuality_t::veryHigh);

    {
        Image signed8Out = testDataSet.getImageApplyModalityTransform(0);
        ASSERT_EQ(bitDepth_t::depthS16, signed8Out.getDepth());

        ReadingDataHandler signed8Handler = signed8Out.getReadingDataHandler();

        ASSERT_EQ(-1, signed8Handler.getInt32(0));
        ASSERT_EQ(19, signed8Handler.getInt32(1));
        ASSERT_EQ(39, signed8Handler.getInt32(2));
        ASSERT_EQ(59, signed8Handler.getInt32(3));
        ASSERT_EQ(79, signed8Handler.getInt32(4));
        ASSERT_EQ(99, signed8Handler.getInt32(5));
    }

    {
        Image signed8Out = testDataSet.getImageApplyModalityTransform(1);
        ASSERT_EQ(bitDepth_t::depthS16, signed8Out.getDepth());

        ReadingDataHandler signed8Handler = signed8Out.getReadingDataHandler();

        ASSERT_EQ(-2, signed8Handler.getInt32(0));
        ASSERT_EQ(18, signed8Handler.getInt32(1));
        ASSERT_EQ(38, signed8Handler.getInt32(2));
        ASSERT_EQ(58, signed8Handler.getInt32(3));
        ASSERT_EQ(78, signed8Handler.getInt32(4));
        ASSERT_EQ(98, signed8Handler.getInt32(5));
    }

    {
        Image unsigned16Out = testDataSet.getImageApplyModalityTransform(2);
        ASSERT_EQ(bitDepth_t::depthU16, unsigned16Out.getDepth());

        ReadingDataHandler unsignedHandler = unsigned16Out.getReadingDataHandler();

        ASSERT_EQ(100u, unsignedHandler.getUint32(0));
        ASSERT_EQ(300u, unsignedHandler.getUint32(1));
        ASSERT_EQ(300u, unsignedHandler.getUint32(2));
        ASSERT_EQ(300u, unsignedHandler.getUint32(3));
        ASSERT_EQ(300u, unsignedHandler.getUint32(4));
        ASSERT_EQ(300u, unsignedHandler.getUint32(5));
    }

    {
        Image signed8Out = testDataSet.getImageApplyModalityTransform(3);
        ASSERT_EQ(bitDepth_t::depthS16, signed8Out.getDepth());

        ReadingDataHandler signed8Handler = signed8Out.getReadingDataHandler();

        ASSERT_EQ(-3, signed8Handler.getInt32(0));
        ASSERT_EQ(17, signed8Handler.getInt32(1));
        ASSERT_EQ(37, signed8Handler.getInt32(2));
        ASSERT_EQ(57, signed8Handler.getInt32(3));
        ASSERT_EQ(77, signed8Handler.getInt32(4));
        ASSERT_EQ(97, signed8Handler.getInt32(5));
    }

}






TEST(modalityVoilut, voilutSigned8)
{
    MutableImage unsigned8(6, 1, bitDepth_t::depthS8, "MONOCHROME2", 7);
    {
        WritingDataHandler unsigned8Handler = unsigned8.getWritingDataHandler();
        unsigned8Handler.setInt32(0, - 30);
        unsigned8Handler.setInt32(1, - 20);
        unsigned8Handler.setInt32(2, - 10);
        unsigned8Handler.setInt32(3, 0);
        unsigned8Handler.setInt32(4, 10);
        unsigned8Handler.setInt32(5, 20);
    }

    MutableDataSet testDataSet("1.2.840.10008.1.2.1");
    testDataSet.setDouble(TagId(tagId_t::RescaleSlope_0028_1053), 2);
    testDataSet.setDouble(TagId(tagId_t::RescaleIntercept_0028_1052), 40);
    testDataSet.setImage(0, unsigned8, imageQuality_t::veryHigh);

    {
        ModalityVOILUT voilut(testDataSet);

        MutableImage signed8Out = voilut.allocateOutputImage(unsigned8, 6, 1);
        voilut.runTransform(unsigned8, 0, 0, 6, 1, signed8Out, 0, 0);
        ASSERT_EQ(bitDepth_t::depthS16, signed8Out.getDepth());

        ReadingDataHandler signed8Handler = signed8Out.getReadingDataHandler();

        ASSERT_EQ(-20, signed8Handler.getInt32(0));
        ASSERT_EQ(0, signed8Handler.getInt32(1));
        ASSERT_EQ(20, signed8Handler.getInt32(2));
        ASSERT_EQ(40, signed8Handler.getInt32(3));
        ASSERT_EQ(60, signed8Handler.getInt32(4));
        ASSERT_EQ(80, signed8Handler.getInt32(5));
    }

    {
        Image signed8Out = testDataSet.getImageApplyModalityTransform(0);
        ASSERT_EQ(bitDepth_t::depthS16, signed8Out.getDepth());

        ReadingDataHandler signed8Handler = signed8Out.getReadingDataHandler();

        ASSERT_EQ(-20, signed8Handler.getInt32(0));
        ASSERT_EQ(0, signed8Handler.getInt32(1));
        ASSERT_EQ(20, signed8Handler.getInt32(2));
        ASSERT_EQ(40, signed8Handler.getInt32(3));
        ASSERT_EQ(60, signed8Handler.getInt32(4));
        ASSERT_EQ(80, signed8Handler.getInt32(5));
    }
}


TEST(modalityVoilut, voilutUnsigned8LUT)
{
    MutableImage unsigned8(6, 1, bitDepth_t::depthU8, "MONOCHROME2", 7);
    {
        WritingDataHandler unsigned8Handler = unsigned8.getWritingDataHandler();
        unsigned8Handler.setUint32(0, 0u);
        unsigned8Handler.setUint32(1, 1u);
        unsigned8Handler.setUint32(2, 2u);
        unsigned8Handler.setUint32(3, 3u);
        unsigned8Handler.setUint32(4, 4u);
        unsigned8Handler.setUint32(5, 5u);
    }

    MutableDataSet testDataSet("1.2.840.10008.1.2.1");
    testDataSet.setImage(0, unsigned8, imageQuality_t::veryHigh);
    MutableTag sequenceTag = testDataSet.getTagCreate(TagId(tagId_t::ModalityLUTSequence_0028_3000));
    MutableDataSet lutItem = sequenceTag.appendSequenceItem();
    {
        WritingDataHandlerNumeric descriptor = lutItem.getWritingDataHandlerNumeric(TagId(tagId_t::LUTDescriptor_0028_3002), 0, tagVR_t::US);
        WritingDataHandlerNumeric data = lutItem.getWritingDataHandlerNumeric(TagId(tagId_t::LUTData_0028_3006), 0, tagVR_t::US);
        descriptor.setUint32(0, 3u);
        descriptor.setUint32(1, 2u);
        descriptor.setUint32(2, 16u);

        data.setUint32(0, 100u);
        data.setUint32(1, 200u);
        data.setUint32(2, 300u);
    }

    {
        ModalityVOILUT voilut(testDataSet);

        MutableImage unsigned8Out = voilut.allocateOutputImage(unsigned8, 6, 1);
        voilut.runTransform(unsigned8, 0, 0, 6, 1, unsigned8Out, 0, 0);

        ReadingDataHandler unsignedHandler = unsigned8Out.getReadingDataHandler();

        ASSERT_EQ(100u, unsignedHandler.getUint32(0));
        ASSERT_EQ(100u, unsignedHandler.getUint32(1));
        ASSERT_EQ(100u, unsignedHandler.getUint32(2));
        ASSERT_EQ(200u, unsignedHandler.getUint32(3));
        ASSERT_EQ(300u, unsignedHandler.getUint32(4));
        ASSERT_EQ(300u, unsignedHandler.getUint32(5));
    }

    {
        Image unsigned8Out = testDataSet.getImageApplyModalityTransform(0);

        ReadingDataHandler unsignedHandler = unsigned8Out.getReadingDataHandler();

        ASSERT_EQ(100u, unsignedHandler.getUint32(0));
        ASSERT_EQ(100u, unsignedHandler.getUint32(1));
        ASSERT_EQ(100u, unsignedHandler.getUint32(2));
        ASSERT_EQ(200u, unsignedHandler.getUint32(3));
        ASSERT_EQ(300u, unsignedHandler.getUint32(4));
        ASSERT_EQ(300u, unsignedHandler.getUint32(5));
    }
}

}

}

