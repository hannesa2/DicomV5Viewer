/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_image.h"
#import "../include/dicomhero6_objc/dicomhero_readingDataHandler.h"
#import "../include/dicomhero6_objc/dicomhero_readingDataHandlerNumeric.h"
#import "../include/dicomhero6_objc/dicomhero_writingDataHandler.h"
#import "../include/dicomhero6_objc/dicomhero_writingDataHandlerNumeric.h"

#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"
#include "dicomhero_strings.h"
#include <dicomhero6/image.h>
#include <dicomhero6/readingDataHandler.h>
#include <dicomhero6/readingDataHandlerNumeric.h>
#include <dicomhero6/writingDataHandler.h>
#include <dicomhero6/writingDataHandlerNumeric.h>

@implementation DicomheroImage

-(id)initWithDicomheroImage:define_dicomhero_parameter(Image)
{
    reset_dicomhero_object_holder(Image);
    self =  [super init];
    if(self)
    {
        set_dicomhero_object_holder(Image, get_dicomhero_parameter(Image));
    }
    else
    {
        delete get_dicomhero_parameter(Image);
    }
    return self;
}

-(id)initWithWidth:(unsigned int)width height:(unsigned int)height depth:(DicomheroBitDepth)depth colorSpace:(NSString*)colorSpace highBit:(unsigned int)highBit
{
    self =  [super init];
    if(self)
    {
        set_dicomhero_object_holder(Image, new dicomhero::Image(
                                     width,
                                     height,
                                     (dicomhero::bitDepth_t)depth,
                                     dicomhero::NSStringToString(colorSpace),
                                     highBit));
    }
    return self;
}

///
/// \ Destructor
///
///////////////////////////////////////////////////////////////////////////////
-(void)dealloc
{
    delete_dicomhero_object_holder(Image);
}

-(DicomheroReadingDataHandlerNumeric*) getReadingDataHandler:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroReadingDataHandlerNumeric alloc] initWithDicomheroReadingDataHandler:new dicomhero::ReadingDataHandler(get_dicomhero_object_holder(Image)->getReadingDataHandler())];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(unsigned int) width
{
    return get_dicomhero_object_holder(Image)->getWidth();
}

-(unsigned int) height
{
    return get_dicomhero_object_holder(Image)->getHeight();
}

-(NSString*) colorSpace
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(Image)->getColorSpace());
}

-(unsigned int) channelsNumber
{
    return get_dicomhero_object_holder(Image)->getChannelsNumber();
}

-(DicomheroBitDepth) depth
{
    return (DicomheroBitDepth)get_dicomhero_object_holder(Image)->getDepth();
}

-(unsigned int) highBit
{
    return get_dicomhero_object_holder(Image)->getHighBit();
}

-(DicomheroWritingDataHandlerNumeric*) getWritingDataHandler:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroWritingDataHandlerNumeric alloc] initWithDicomheroWritingDataHandler:new dicomhero::WritingDataHandler(((dicomhero::Image*)get_dicomhero_object_holder(Image))->getWritingDataHandler())];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

@end
