/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_drawBitmap.h"
#import "../include/dicomhero6_objc/dicomhero_readWriteMemory.h"
#import "../include/dicomhero6_objc/dicomhero_transform.h"
#import "../include/dicomhero6_objc/dicomhero_image.h"

#include <dicomhero6/drawBitmap.h>
#include <dicomhero6/mutableMemory.h>
#include <dicomhero6/image.h>
#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"

void CGDataProviderCallbackFunc(void *info, const void* /* data */, size_t /* size */)
{
    // Release the shared pointer holding the memory
    ////////////////////////////////////////////////
    delete (dicomhero::Memory*)info;
}


@implementation DicomheroDrawBitmap

-(id)init
{
    reset_dicomhero_object_holder(DrawBitmap);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DrawBitmap, new dicomhero::DrawBitmap());
    }
    return self;
}

-(id)initWithTransform:(DicomheroTransform*)pTransform
{
    reset_dicomhero_object_holder(DrawBitmap);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DrawBitmap, new dicomhero::DrawBitmap(*get_other_dicomhero_object_holder(pTransform, Transform)));
    }
    return self;
}

-(void)dealloc
{
    delete_dicomhero_object_holder(DrawBitmap);
}


-(DicomheroMemory*) getBitmap:(DicomheroImage*)pImage bitmapType:(DicomheroDrawBitmapType)drawBitmapType rowAlignBytes:(unsigned int)rowAlignBytes error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroMemory alloc] initWithDicomheroMemory:new dicomhero::Memory(get_dicomhero_object_holder(DrawBitmap)->getBitmap(*get_other_dicomhero_object_holder(pImage, Image), (dicomhero::drawBitmapType_t)drawBitmapType, (std::uint32_t)rowAlignBytes))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


#if defined(__APPLE__)

#if TARGET_OS_IPHONE
-(UIImage*)getDicomheroImage:(DicomheroImage*)pImage error:(NSError**)pError
#else
-(NSImage*)getDicomheroImage:(DicomheroImage*)pImage error:(NSError**)pError
#endif
{
    OBJC_DICOMHERO_FUNCTION_START();

    // Get the amount of memory needed for the conversion
    /////////////////////////////////////////////////////
    std::uint32_t width(get_other_dicomhero_object_holder(pImage, Image)->getWidth());
    std::uint32_t height(get_other_dicomhero_object_holder(pImage, Image)->getHeight());

    // Get the result raw data
    //////////////////////////
    std::unique_ptr<dicomhero::Memory> pMemory(new dicomhero::Memory(get_dicomhero_object_holder(DrawBitmap)->getBitmap(*get_other_dicomhero_object_holder(pImage, Image), dicomhero::drawBitmapType_t::drawBitmapRGBA, 4)));
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

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

#endif

@end
