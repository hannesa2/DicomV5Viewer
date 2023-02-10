/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_tag.h"
#import "../include/imebraobjc/imebra_dataset.h"
#import "../include/imebraobjc/imebra_readingDataHandler.h"
#import "../include/imebraobjc/imebra_readingDataHandlerNumeric.h"
#import "../include/imebraobjc/imebra_writingDataHandler.h"
#import "../include/imebraobjc/imebra_writingDataHandlerNumeric.h"
#import "../include/imebraobjc/imebra_streamReader.h"
#import "../include/imebraobjc/imebra_streamWriter.h"
#import "../include/imebraobjc/imebra_fileStreamInput.h"

#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"

#include <imebra/tag.h>
#include <imebra/readingDataHandler.h>
#include <imebra/readingDataHandlerNumeric.h>
#include <imebra/streamReader.h>
#include <imebra/streamWriter.h>
#include <imebra/dataSet.h>
#include <imebra/fileStreamInput.h>

@implementation ImebraTag

-(id)initWithImebraTag:define_imebra_parameter(Tag)
{
    reset_imebra_object_holder(Tag);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(Tag, get_imebra_parameter(Tag));
    }
    else
    {
        delete get_imebra_parameter(Tag);
    }
    return self;
}

-(void)dealloc
{
    delete_imebra_object_holder(Tag);
}

-(unsigned int) getBuffersCount
{
    return (unsigned int)get_imebra_object_holder(Tag)->getBuffersCount();
}


-(BOOL) bufferExists:(unsigned int) bufferId
{
    return (BOOL)get_imebra_object_holder(Tag)->bufferExists((size_t)bufferId);
}


-(unsigned int) getBufferSize:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return (unsigned int)get_imebra_object_holder(Tag)->getBufferSize((size_t)bufferId);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}


-(ImebraReadingDataHandler*) getReadingDataHandler:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraReadingDataHandler alloc] initWithImebraReadingDataHandler:new imebra::ReadingDataHandler(get_imebra_object_holder(Tag)->getReadingDataHandler((size_t)bufferId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


-(ImebraReadingDataHandlerNumeric*) getReadingDataHandlerNumeric:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraReadingDataHandlerNumeric alloc] initWithImebraReadingDataHandler:new imebra::ReadingDataHandlerNumeric(get_imebra_object_holder(Tag)->getReadingDataHandlerNumeric((size_t)bufferId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


-(ImebraReadingDataHandlerNumeric*) getReadingDataHandlerRaw:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraReadingDataHandlerNumeric alloc] initWithImebraReadingDataHandler:new imebra::ReadingDataHandlerNumeric(get_imebra_object_holder(Tag)->getReadingDataHandlerRaw((size_t)bufferId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


-(ImebraStreamReader*) getStreamReader:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraStreamReader alloc] initWithImebraStreamReader:new imebra::StreamReader(get_imebra_object_holder(Tag)->getStreamReader((size_t)bufferId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


-(ImebraDataSet*) getSequenceItem:(unsigned int) dataSetId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraDataSet alloc] initWithImebraDataSet:new imebra::DataSet(get_imebra_object_holder(Tag)->getSequenceItem((size_t)dataSetId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


-(BOOL)sequenceItemExists:(unsigned int) dataSetId
{
    return (BOOL)(get_imebra_object_holder(Tag)->sequenceItemExists((size_t)dataSetId));
}


-(ImebraTagType) dataType
{
    return (ImebraTagType)get_imebra_object_holder(Tag)->getDataType();
}

@end


@implementation ImebraMutableTag

-(id)initWithImebraMutableTag:define_imebra_parameter(MutableTag)
{
    return [super initWithImebraTag:get_imebra_parameter(MutableTag)];
}

-(ImebraWritingDataHandler*) getWritingDataHandler:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraWritingDataHandler alloc] initWithImebraWritingDataHandler:new imebra::WritingDataHandler(((imebra::MutableTag*)get_imebra_object_holder(Tag))->getWritingDataHandler((size_t)bufferId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraWritingDataHandlerNumeric*) getWritingDataHandlerNumeric:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraWritingDataHandlerNumeric alloc] initWithImebraWritingDataHandler:new imebra::WritingDataHandlerNumeric(((imebra::MutableTag*)get_imebra_object_holder(Tag))->getWritingDataHandlerNumeric((size_t)bufferId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraWritingDataHandlerNumeric*) getWritingDataHandlerRaw:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraWritingDataHandlerNumeric alloc] initWithImebraWritingDataHandler:new imebra::WritingDataHandlerNumeric(((imebra::MutableTag*)get_imebra_object_holder(Tag))->getWritingDataHandlerRaw((size_t)bufferId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraStreamWriter*) getStreamWriter:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraStreamWriter alloc] initWithImebraStreamWriter:new imebra::StreamWriter(((imebra::MutableTag*)get_imebra_object_holder(Tag))->getStreamWriter((size_t)bufferId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraMutableDataSet*) appendSequenceItem:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraMutableDataSet alloc] initWithImebraDataSet:new imebra::MutableDataSet(
            ((imebra::MutableTag*)get_imebra_object_holder(Tag))->appendSequenceItem())];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(void) setStream:(unsigned int) bufferId stream:(ImebraFileStreamInput*)pStream error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableTag*)get_imebra_object_holder(Tag))->setStream((size_t)bufferId, *(imebra::FileStreamInput*)(get_other_imebra_object_holder(pStream, BaseStreamInput)));

    OBJC_IMEBRA_FUNCTION_END();

}

@end

