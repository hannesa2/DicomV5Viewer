/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_transform.h"
#import "../include/dicomhero6_objc/dicomhero_image.h"

#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"

#include <dicomhero6/transform.h>
#include <dicomhero6/image.h>

@implementation DicomheroTransform


-(id)initWithDicomheroTransform:define_dicomhero_parameter(Transform)
{
    reset_dicomhero_object_holder(Transform);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(Transform, get_dicomhero_parameter(Transform));
    }
    else
    {
        delete get_dicomhero_parameter(Transform);
    }
    return self;
}


-(void)dealloc
{
    delete_dicomhero_object_holder(Transform);
}


-(DicomheroImage*) allocateOutputImage:
    (DicomheroImage*)pInputImage
    width:(unsigned int)width
    height:(unsigned int)height
    error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroImage alloc] initWithDicomheroImage:new dicomhero::Image(get_dicomhero_object_holder(Transform)->allocateOutputImage(*get_other_dicomhero_object_holder(pInputImage, Image), (std::uint32_t)width, (std::uint32_t)height))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


-(void) runTransform:
    (DicomheroImage*)pInputImage
    inputTopLeftX:(unsigned int)inputTopLeftX
    inputTopLeftY:(unsigned int)inputTopLeftY
    inputWidth:(unsigned int)inputWidth
    inputHeight:(unsigned int)inputHeight
    outputImage:(DicomheroImage*)pOutputImage
    outputTopLeftX:(unsigned int)outputTopLeftX
    outputTopLeftY:(unsigned int)outputTopLeftY
    error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(Transform)->runTransform(
                *get_other_dicomhero_object_holder(pInputImage, Image),
                (std::uint32_t)inputTopLeftX,
                (std::uint32_t)inputTopLeftY,
                (std::uint32_t)inputWidth,
                (std::uint32_t)inputHeight,
                *(dicomhero::Image*)get_other_dicomhero_object_holder(pOutputImage, Image),
                (std::uint32_t)outputTopLeftX,
                (std::uint32_t)outputTopLeftY);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(BOOL)isEmpty
{
    return (BOOL)(get_dicomhero_object_holder(Transform)->isEmpty());
}

@end


