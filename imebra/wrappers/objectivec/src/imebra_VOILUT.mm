/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_VOILUT.h"
#import "../include/imebraobjc/imebra_image.h"
#import "../include/imebraobjc/imebra_lut.h"
#import "../include/imebraobjc/imebra_VOIDescription.h"
#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"
#include <imebra/VOILUT.h>
#include <imebra/VOIDescription.h>

@implementation ImebraVOILUT

-(id)initWithLUT:(ImebraLUT*)lut
{
    reset_imebra_object_holder(Transform);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(Transform, new imebra::VOILUT(*get_other_imebra_object_holder(lut, LUT)));
    }
    return self;
}

-(id)initWithVOIDescription:(ImebraVOIDescription*)voiDescription
{
    reset_imebra_object_holder(Transform);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(Transform, new imebra::VOILUT(*get_other_imebra_object_holder(voiDescription, VOIDescription)));
    }
    return self;
}

+(ImebraVOIDescription*)getOptimalVOI:
    (ImebraImage*)pInputImage
    inputTopLeftX:(unsigned int)inputTopLeftX
    inputTopLeftY:(unsigned int)inputTopLeftY
    inputWidth:(unsigned int)inputWidth
    inputHeight:(unsigned int)inputHeight
    error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraVOIDescription alloc] initWithImebraVOIDescription:new imebra::VOIDescription(
        imebra::VOILUT::getOptimalVOI(
                *get_other_imebra_object_holder(pInputImage, Image),
                (std::uint32_t)inputTopLeftX,
                (std::uint32_t)inputTopLeftY,
                (std::uint32_t)inputWidth,
                (std::uint32_t)inputHeight)) ];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

@end


