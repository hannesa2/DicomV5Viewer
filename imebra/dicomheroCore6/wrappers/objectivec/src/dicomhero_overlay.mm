/*
Copyright 2005 - 2019 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_overlay.h"
#import "../include/dicomhero6_objc/dicomhero_image.h"

#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"
#include "dicomhero_strings.h"
#include <dicomhero6/image.h>
#include <dicomhero6/overlay.h>

@implementation DicomheroOverlay

-(id)initWithDicomheroOverlay:define_dicomhero_parameter(Overlay)
{
    reset_dicomhero_object_holder(Overlay);
    self =  [super init];
    if(self)
    {
        set_dicomhero_object_holder(Overlay, get_dicomhero_parameter(Overlay));
    }
    else
    {
        delete get_dicomhero_parameter(Overlay);
    }
    return self;
}

-(id)initWithType:(DicomheroOverlayType)type subType:(NSString*)subType firstFrame:(unsigned int)firstFrame zeroBasedOriginX:(int)zeroBasedOriginX zeroBasedOriginY:(int)zeroBasedOriginY label:(NSString*)label description:(NSString*)description
{
    reset_dicomhero_object_holder(Overlay);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(Overlay, new dicomhero::Overlay(
            dicomhero::overlayType_t(type),
            dicomhero::NSStringToString(subType),
            firstFrame,
            zeroBasedOriginX,
            zeroBasedOriginY,
            dicomhero::NSStringToString(label),
            dicomhero::NSStringToString(description)));
    }
    return self;
}

-(void)dealloc
{
    delete_dicomhero_object_holder(Overlay);
}

-(DicomheroOverlayType) type
{
    return (DicomheroOverlayType)get_dicomhero_object_holder(Overlay)->getType();
}

-(NSString*) subType
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(Overlay)->getSubType());
}

-(NSString*) label
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(Overlay)->getLabel());
}

-(NSString*) description
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(Overlay)->getDescription());
}

-(unsigned int) firstFrame
{
    return get_dicomhero_object_holder(Overlay)->getFirstFrame();
}

-(unsigned int) framesCount
{
    return get_dicomhero_object_holder(Overlay)->getFramesCount();
}

-(int) zeroBasedOriginX
{
    return get_dicomhero_object_holder(Overlay)->getZeroBasedOriginX();
}

-(int) zeroBasedOriginY
{
    return get_dicomhero_object_holder(Overlay)->getZeroBasedOriginY();
}

-(unsigned int) getROIArea:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(Overlay)->getROIArea();

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0u);
}

-(double) getROIMean:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(Overlay)->getROIMean();

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0.0);
}

-(double) getROIStandardDeviation:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(Overlay)->getROIStandardDeviation();

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0.0);
}

-(DicomheroImage*) getImage:(unsigned int)frameNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroImage alloc] initWithDicomheroImage:new dicomhero::Image(get_dicomhero_object_holder(Overlay)->getImage(frameNumber))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(void) setROIArea:(unsigned int)roiArea
{
    get_dicomhero_object_holder(Overlay)->setROIArea(roiArea);
}

-(void) setROIMean:(double)roiMean
{
    get_dicomhero_object_holder(Overlay)->setROIMean(roiMean);
}

-(void) setROIStandardDeviation:(double)standardDeviation
{
    get_dicomhero_object_holder(Overlay)->setROIStandardDeviation(standardDeviation);
}

-(void) setImage:(unsigned int)frameNumber image:(DicomheroImage*)image error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(Overlay)->setImage(frameNumber, *get_other_dicomhero_object_holder(image, Image));

    OBJC_DICOMHERO_FUNCTION_END();
}

@end
