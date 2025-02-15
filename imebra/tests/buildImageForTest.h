#if !defined(imebraBuildImageForTest_13D4DE03_AD80_4e0a_A01A_54D77C9AF0E8__INCLUDED_)
#define imebraBuildImageForTest_13D4DE03_AD80_4e0a_A01A_54D77C9AF0E8__INCLUDED_

#include <imebra/imebra.h>

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
        std::uint32_t continuity);

    imebra::Image buildSubsampledImage(
        std::uint32_t pixelsX,
        std::uint32_t pixelsY,
        imebra::bitDepth_t depth,
        std::uint32_t highBit,
        const std::string& colorSpace);

    double compareImages(const Image& image0, const Image& image1);

    bool identicalImages(const imebra::Image& image0, const imebra::Image& image1);


} // namespace tests

} // namespace imebra


#endif // #if !defined(imebraBuildImageForTest_13D4DE03_AD80_4e0a_A01A_54D77C9AF0E8__INCLUDED_)
