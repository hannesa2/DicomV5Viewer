/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_transform.h"
#import "../include/imebraobjc/imebra_image.h"

#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"

#include <imebra/transform.h>
#include <imebra/image.h>

@implementation ImebraTransform


-(id)initWithImebraTransform:define_imebra_parameter(Transform)
{
    reset_imebra_object_holder(Transform);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(Transform, get_imebra_parameter(Transform));
    }
    else
    {
        delete get_imebra_parameter(Transform);
    }
    return self;
}


-(void)dealloc
{
    delete_imebra_object_holder(Transform);
}


-(ImebraMutableImage*) allocateOutputImage:
    (ImebraImage*)pInputImage
    width:(unsigned int)width
    height:(unsigned int)height
    error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraMutableImage alloc] initWithImebraImage:new imebra::MutableImage(get_imebra_object_holder(Transform)->allocateOutputImage(*get_other_imebra_object_holder(pInputImage, Image), (std::uint32_t)width, (std::uint32_t)height))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


-(void) runTransform:
    (ImebraImage*)pInputImage
    inputTopLeftX:(unsigned int)inputTopLeftX
    inputTopLeftY:(unsigned int)inputTopLeftY
    inputWidth:(unsigned int)inputWidth
    inputHeight:(unsigned int)inputHeight
    outputImage:(ImebraMutableImage*)pOutputImage
    outputTopLeftX:(unsigned int)outputTopLeftX
    outputTopLeftY:(unsigned int)outputTopLeftY
    error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    get_imebra_object_holder(Transform)->runTransform(
                *get_other_imebra_object_holder(pInputImage, Image),
                (std::uint32_t)inputTopLeftX,
                (std::uint32_t)inputTopLeftY,
                (std::uint32_t)inputWidth,
                (std::uint32_t)inputHeight,
                *(imebra::MutableImage*)get_other_imebra_object_holder(pOutputImage, Image),
                (std::uint32_t)outputTopLeftX,
                (std::uint32_t)outputTopLeftY);

    OBJC_IMEBRA_FUNCTION_END();
}

-(BOOL)isEmpty
{
    return (BOOL)(get_imebra_object_holder(Transform)->isEmpty());
}

@end


