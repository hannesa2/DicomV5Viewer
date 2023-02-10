/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_VOILUT.h"
#import "../include/dicomhero6_objc/dicomhero_image.h"
#import "../include/dicomhero6_objc/dicomhero_lut.h"
#import "../include/dicomhero6_objc/dicomhero_VOIDescription.h"
#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"
#include <dicomhero6/VOILUT.h>
#include <dicomhero6/VOIDescription.h>

@implementation DicomheroVOILUT

-(id)initWithLUT:(DicomheroLUT*)lut
{
    reset_dicomhero_object_holder(Transform);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(Transform, new dicomhero::VOILUT(*get_other_dicomhero_object_holder(lut, LUT)));
    }
    return self;
}

-(id)initWithVOIDescription:(DicomheroVOIDescription*)voiDescription
{
    reset_dicomhero_object_holder(Transform);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(Transform, new dicomhero::VOILUT(*get_other_dicomhero_object_holder(voiDescription, VOIDescription)));
    }
    return self;
}

+(DicomheroVOIDescription*)getOptimalVOI:
    (DicomheroImage*)pInputImage
    inputTopLeftX:(unsigned int)inputTopLeftX
    inputTopLeftY:(unsigned int)inputTopLeftY
    inputWidth:(unsigned int)inputWidth
    inputHeight:(unsigned int)inputHeight
    error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroVOIDescription alloc] initWithDicomheroVOIDescription:new dicomhero::VOIDescription(
        dicomhero::VOILUT::getOptimalVOI(
                *get_other_dicomhero_object_holder(pInputImage, Image),
                (std::uint32_t)inputTopLeftX,
                (std::uint32_t)inputTopLeftY,
                (std::uint32_t)inputWidth,
                (std::uint32_t)inputHeight)) ];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

@end


