/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_colorTransformsFactory.h"
#import "../include/dicomhero6_objc/dicomhero_transform.h"
#include "dicomhero_implementation_macros.h"
#include "dicomhero_strings.h"
#include "dicomhero_nserror.h"
#include <dicomhero6/colorTransformsFactory.h>
#include <dicomhero6/transform.h>


@implementation DicomheroColorTransformsFactory

+(NSString*) normalizeColorSpace:(NSString*)colorSpace
{
    return dicomhero::stringToNSString(dicomhero::ColorTransformsFactory::normalizeColorSpace(dicomhero::NSStringToString(colorSpace)));
}


+(BOOL)isMonochrome:(NSString*)colorSpace
{
    return (BOOL)dicomhero::ColorTransformsFactory::isMonochrome(dicomhero::NSStringToString(colorSpace));
}


+(BOOL)isSubsampledX:(NSString*)colorSpace
{
    return (BOOL)dicomhero::ColorTransformsFactory::isSubsampledX(dicomhero::NSStringToString(colorSpace));
}


+(BOOL)isSubsampledY:(NSString*)colorSpace
{
    return (BOOL)dicomhero::ColorTransformsFactory::isSubsampledY(dicomhero::NSStringToString(colorSpace));
}


+(BOOL)canSubsample:(NSString*)colorSpace
{
    return (BOOL)dicomhero::ColorTransformsFactory::canSubsample(dicomhero::NSStringToString(colorSpace));
}


+(NSString*)makeSubsampled:(NSString*)colorSpace subSampleX:(BOOL)bSubSampleX subSampleY:(BOOL)bSubSampleY
{
    return dicomhero::stringToNSString(dicomhero::ColorTransformsFactory::makeSubsampled(dicomhero::NSStringToString(colorSpace), bSubSampleX != 0, bSubSampleY != 0));
}


+(unsigned int)getNumberOfChannels:(NSString*)colorSpace
{
    return (unsigned int)dicomhero::ColorTransformsFactory::getNumberOfChannels(dicomhero::NSStringToString(colorSpace));
}


+(DicomheroTransform*)getTransform:(NSString*)startColorSpace finalColorSpace:(NSString*)endColorSpace error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroTransform alloc] initWithDicomheroTransform:
        new dicomhero::Transform(dicomhero::ColorTransformsFactory::getTransform(dicomhero::NSStringToString(startColorSpace), dicomhero::NSStringToString(endColorSpace)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

@end

