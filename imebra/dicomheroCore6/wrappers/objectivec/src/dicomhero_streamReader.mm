/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_streamReader.h"
#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"
#include <dicomhero6/streamReader.h>


@implementation DicomheroStreamReader

-(id)initWithDicomheroStreamReader:define_dicomhero_parameter(StreamReader)
{
    reset_dicomhero_object_holder(StreamReader);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(StreamReader, get_dicomhero_parameter(StreamReader));
    }
    else
    {
        delete get_dicomhero_parameter(StreamReader);
    }
    return self;

}

-(id)initWithInputStream:(DicomheroBaseStreamInput*)pInput
{
    reset_dicomhero_object_holder(StreamReader);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(StreamReader, new dicomhero::StreamReader(*get_other_dicomhero_object_holder(pInput, BaseStreamInput)));
    }
    return self;

}

-(id)initWithInputStream:(DicomheroBaseStreamInput*)pInput virtualStart:(unsigned int)virtualStart virtualEnd:(unsigned int)virtualEnd
{
    reset_dicomhero_object_holder(StreamReader);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(StreamReader, new dicomhero::StreamReader(*get_other_dicomhero_object_holder(pInput, BaseStreamInput), virtualStart, virtualEnd));
    }
    return self;

}

-(void)dealloc
{
    delete_dicomhero_object_holder(StreamReader);
}

-(DicomheroStreamReader*)getVirtualStream:(unsigned int)virtualSize error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroStreamReader alloc] initWithDicomheroStreamReader:new dicomhero::StreamReader(get_dicomhero_object_holder(StreamReader)->getVirtualStream(virtualSize))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(void)terminate
{
    get_dicomhero_object_holder(StreamReader)->terminate();
}

@end
