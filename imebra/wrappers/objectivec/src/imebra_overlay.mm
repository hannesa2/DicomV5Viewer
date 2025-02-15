/*
Copyright 2005 - 2019 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_overlay.h"
#import "../include/imebraobjc/imebra_image.h"

#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"
#include "imebra_strings.h"
#include <imebra/image.h>
#include <imebra/overlay.h>

@implementation ImebraOverlay

-(id)initWithImebraOverlay:define_imebra_parameter(Overlay)
{
    reset_imebra_object_holder(Overlay);
    self =  [super init];
    if(self)
    {
        set_imebra_object_holder(Overlay, get_imebra_parameter(Overlay));
    }
    else
    {
        delete get_imebra_parameter(Overlay);
    }
    return self;
}

-(void)dealloc
{
    delete_imebra_object_holder(Overlay);
}

-(ImebraOverlayType) type
{
    return (ImebraOverlayType)get_imebra_object_holder(Overlay)->getType();
}

-(NSString*) subType
{
    return imebra::stringToNSString(get_imebra_object_holder(Overlay)->getSubType());
}

-(NSString*) label
{
    return imebra::stringToNSString(get_imebra_object_holder(Overlay)->getLabel());
}

-(NSString*) description
{
    return imebra::stringToNSString(get_imebra_object_holder(Overlay)->getDescription());
}

-(unsigned int) firstFrame
{
    return get_imebra_object_holder(Overlay)->getFirstFrame();
}

-(unsigned int) framesCount
{
    return get_imebra_object_holder(Overlay)->getFramesCount();
}

-(int) zeroBasedOriginX
{
    return get_imebra_object_holder(Overlay)->getZeroBasedOriginX();
}

-(int) zeroBasedOriginY
{
    return get_imebra_object_holder(Overlay)->getZeroBasedOriginY();
}

-(unsigned int) getROIArea:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(Overlay)->getROIArea();

    OBJC_IMEBRA_FUNCTION_END_RETURN(0u);
}

-(double) getROIMean:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(Overlay)->getROIMean();

    OBJC_IMEBRA_FUNCTION_END_RETURN(0.0);
}

-(double) getROIStandardDeviation:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(Overlay)->getROIStandardDeviation();

    OBJC_IMEBRA_FUNCTION_END_RETURN(0.0);
}

-(ImebraImage*) getImage:(unsigned int)frameNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraImage alloc] initWithImebraImage:new imebra::Image(get_imebra_object_holder(Overlay)->getImage(frameNumber))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

@end


@implementation ImebraMutableOverlay

-(id)initWithType:(ImebraOverlayType)type subType:(NSString*)subType firstFrame:(unsigned int)firstFrame zeroBasedOriginX:(int)zeroBasedOriginX zeroBasedOriginY:(int)zeroBasedOriginY label:(NSString*)label description:(NSString*)description
{
    reset_imebra_object_holder(Overlay);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(Overlay, new imebra::MutableOverlay(
            imebra::overlayType_t(type),
            imebra::NSStringToString(subType),
            firstFrame,
            zeroBasedOriginX,
            zeroBasedOriginY,
            imebra::NSStringToString(label),
            imebra::NSStringToString(description)));
    }
    return self;
}

-(void) setROIArea:(unsigned int)roiArea
{
    ((imebra::MutableOverlay*)get_imebra_object_holder(Overlay))->setROIArea(roiArea);
}

-(void) setROIMean:(double)roiMean
{
    ((imebra::MutableOverlay*)get_imebra_object_holder(Overlay))->setROIMean(roiMean);
}

-(void) setROIStandardDeviation:(double)standardDeviation
{
    ((imebra::MutableOverlay*)get_imebra_object_holder(Overlay))->setROIStandardDeviation(standardDeviation);
}

-(void) setImage:(unsigned int)frameNumber image:(ImebraImage*)image error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableOverlay*)get_imebra_object_holder(Overlay))->setImage(frameNumber, *get_other_imebra_object_holder(image, Image));

    OBJC_IMEBRA_FUNCTION_END();
}

@end
