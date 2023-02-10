/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_image.h"
#import "../include/imebraobjc/imebra_readingDataHandler.h"
#import "../include/imebraobjc/imebra_readingDataHandlerNumeric.h"
#import "../include/imebraobjc/imebra_writingDataHandler.h"
#import "../include/imebraobjc/imebra_writingDataHandlerNumeric.h"

#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"
#include "imebra_strings.h"
#include <imebra/image.h>
#include <imebra/readingDataHandler.h>
#include <imebra/readingDataHandlerNumeric.h>
#include <imebra/writingDataHandler.h>
#include <imebra/writingDataHandlerNumeric.h>

@implementation ImebraImage

-(id)initWithImebraImage:define_imebra_parameter(Image)
{
    reset_imebra_object_holder(Image);
    self =  [super init];
    if(self)
    {
        set_imebra_object_holder(Image, get_imebra_parameter(Image));
    }
    else
    {
        delete get_imebra_parameter(Image);
    }
    return self;
}

///
/// \ Destructor
///
///////////////////////////////////////////////////////////////////////////////
-(void)dealloc
{
    delete_imebra_object_holder(Image);
}

-(ImebraReadingDataHandlerNumeric*) getReadingDataHandler:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraReadingDataHandlerNumeric alloc] initWithImebraReadingDataHandler:new imebra::ReadingDataHandler(get_imebra_object_holder(Image)->getReadingDataHandler())];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(unsigned int) width
{
    return get_imebra_object_holder(Image)->getWidth();
}

-(unsigned int) height
{
    return get_imebra_object_holder(Image)->getHeight();
}

-(NSString*) colorSpace
{
    return imebra::stringToNSString(get_imebra_object_holder(Image)->getColorSpace());
}

-(unsigned int) channelsNumber
{
    return get_imebra_object_holder(Image)->getChannelsNumber();
}

-(ImebraBitDepth) depth
{
    return (ImebraBitDepth)get_imebra_object_holder(Image)->getDepth();
}

-(unsigned int) highBit
{
    return get_imebra_object_holder(Image)->getHighBit();
}

@end


@implementation ImebraMutableImage


-(id)initWithWidth:(unsigned int)width height:(unsigned int)height depth:(ImebraBitDepth)depth colorSpace:(NSString*)colorSpace highBit:(unsigned int)highBit
{
    self =  [super init];
    if(self)
    {
        set_imebra_object_holder(Image, new imebra::MutableImage(
                                     width,
                                     height,
                                     (imebra::bitDepth_t)depth,
                                     imebra::NSStringToString(colorSpace),
                                     highBit));
    }
    return self;
}

-(ImebraWritingDataHandlerNumeric*) getWritingDataHandler:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraWritingDataHandlerNumeric alloc] initWithImebraWritingDataHandler:new imebra::WritingDataHandler(((imebra::MutableImage*)get_imebra_object_holder(Image))->getWritingDataHandler())];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

@end
