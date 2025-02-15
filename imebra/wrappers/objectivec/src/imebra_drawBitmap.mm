/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_drawBitmap.h"
#import "../include/imebraobjc/imebra_readWriteMemory.h"
#import "../include/imebraobjc/imebra_transform.h"
#import "../include/imebraobjc/imebra_image.h"

#include <imebra/drawBitmap.h>
#include <imebra/mutableMemory.h>
#include <imebra/image.h>
#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"

void CGDataProviderCallbackFunc(void *info, const void* /* data */, size_t /* size */)
{
    // Release the shared pointer holding the memory
    ////////////////////////////////////////////////
    delete (imebra::Memory*)info;
}


@implementation ImebraDrawBitmap

-(id)init
{
    reset_imebra_object_holder(DrawBitmap);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DrawBitmap, new imebra::DrawBitmap());
    }
    return self;
}

-(id)initWithTransform:(ImebraTransform*)pTransform
{
    reset_imebra_object_holder(DrawBitmap);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DrawBitmap, new imebra::DrawBitmap(*get_other_imebra_object_holder(pTransform, Transform)));
    }
    return self;
}

-(void)dealloc
{
    delete_imebra_object_holder(DrawBitmap);
}


-(ImebraMemory*) getBitmap:(ImebraImage*)pImage bitmapType:(ImebraDrawBitmapType)drawBitmapType rowAlignBytes:(unsigned int)rowAlignBytes error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraMemory alloc] initWithImebraMemory:new imebra::Memory(get_imebra_object_holder(DrawBitmap)->getBitmap(*get_other_imebra_object_holder(pImage, Image), (imebra::drawBitmapType_t)drawBitmapType, (std::uint32_t)rowAlignBytes))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


#if defined(__APPLE__)

#if TARGET_OS_IPHONE
-(UIImage*)getImebraImage:(ImebraImage*)pImage error:(NSError**)pError
#else
-(NSImage*)getImebraImage:(ImebraImage*)pImage error:(NSError**)pError
#endif
{
    OBJC_IMEBRA_FUNCTION_START();

    // Get the amount of memory needed for the conversion
    /////////////////////////////////////////////////////
    std::uint32_t width(get_other_imebra_object_holder(pImage, Image)->getWidth());
    std::uint32_t height(get_other_imebra_object_holder(pImage, Image)->getHeight());

    // Get the result raw data
    //////////////////////////
    std::unique_ptr<imebra::Memory> pMemory(new imebra::Memory(get_imebra_object_holder(DrawBitmap)->getBitmap(*get_other_imebra_object_holder(pImage, Image), imebra::drawBitmapType_t::drawBitmapRGBA, 4)));
    size_t dataSize;
    const char* pData = pMemory->data(&dataSize);

    // Create a CGImage, then convert it to NSImage or UIImage
    //////////////////////////////////////////////////////////
    CGDataProviderRef dataProviderRef = CGDataProviderCreateWithData(pMemory.release(),
                                                                pData,
                                                                dataSize,
                                                                CGDataProviderCallbackFunc);

    CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
    CGBitmapInfo bitmapInfo = kCGBitmapByteOrder32Big | kCGImageAlphaPremultipliedLast;
    CGColorRenderingIntent renderingIntent = kCGRenderingIntentDefault;

    CGImageRef imageRef = CGImageCreate(
                width, height,
                8, 32,
                width * 4,
                colorSpaceRef, bitmapInfo, dataProviderRef, NULL, YES, renderingIntent);


#if TARGET_OS_IPHONE
    UIImage* returnImage = [[UIImage alloc] initWithCGImage:imageRef];
#else
    NSImage* returnImage = [[NSImage alloc] initWithCGImage:imageRef size:NSZeroSize];
#endif
    CGDataProviderRelease(dataProviderRef);
    CGImageRelease(imageRef);
    CGColorSpaceRelease(colorSpaceRef);
    return returnImage;

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

#endif

@end
