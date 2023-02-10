/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/dicomhero6_objc/dicomhero_tag.h"
#import "../include/dicomhero6_objc/dicomhero_dataset.h"
#import "../include/dicomhero6_objc/dicomhero_readingDataHandler.h"
#import "../include/dicomhero6_objc/dicomhero_readingDataHandlerNumeric.h"
#import "../include/dicomhero6_objc/dicomhero_writingDataHandler.h"
#import "../include/dicomhero6_objc/dicomhero_writingDataHandlerNumeric.h"
#import "../include/dicomhero6_objc/dicomhero_streamReader.h"
#import "../include/dicomhero6_objc/dicomhero_streamWriter.h"
#import "../include/dicomhero6_objc/dicomhero_fileStreamInput.h"

#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"

#include <dicomhero6/tag.h>
#include <dicomhero6/readingDataHandler.h>
#include <dicomhero6/readingDataHandlerNumeric.h>
#include <dicomhero6/streamReader.h>
#include <dicomhero6/streamWriter.h>
#include <dicomhero6/dataSet.h>
#include <dicomhero6/fileStreamInput.h>

@implementation DicomheroTag

-(id)initWithDicomheroTag:define_dicomhero_parameter(Tag)
{
    reset_dicomhero_object_holder(Tag);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(Tag, get_dicomhero_parameter(Tag));
    }
    else
    {
        delete get_dicomhero_parameter(Tag);
    }
    return self;
}

-(void)dealloc
{
    delete_dicomhero_object_holder(Tag);
}

-(unsigned int) getBuffersCount
{
    return (unsigned int)get_dicomhero_object_holder(Tag)->getBuffersCount();
}


-(BOOL) bufferExists:(unsigned int) bufferId
{
    return (BOOL)get_dicomhero_object_holder(Tag)->bufferExists((size_t)bufferId);
}


-(unsigned int) getBufferSize:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return (unsigned int)get_dicomhero_object_holder(Tag)->getBufferSize((size_t)bufferId);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}


-(DicomheroReadingDataHandler*) getReadingDataHandler:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroReadingDataHandler alloc] initWithDicomheroReadingDataHandler:new dicomhero::ReadingDataHandler(get_dicomhero_object_holder(Tag)->getReadingDataHandler((size_t)bufferId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


-(DicomheroReadingDataHandlerNumeric*) getReadingDataHandlerNumeric:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroReadingDataHandlerNumeric alloc] initWithDicomheroReadingDataHandler:new dicomhero::ReadingDataHandlerNumeric(get_dicomhero_object_holder(Tag)->getReadingDataHandlerNumeric((size_t)bufferId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


-(DicomheroReadingDataHandlerNumeric*) getReadingDataHandlerRaw:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroReadingDataHandlerNumeric alloc] initWithDicomheroReadingDataHandler:new dicomhero::ReadingDataHandlerNumeric(get_dicomhero_object_holder(Tag)->getReadingDataHandlerRaw((size_t)bufferId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


-(DicomheroStreamReader*) getStreamReader:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroStreamReader alloc] initWithDicomheroStreamReader:new dicomhero::StreamReader(get_dicomhero_object_holder(Tag)->getStreamReader((size_t)bufferId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


-(DicomheroDataSet*) getSequenceItem:(unsigned int) dataSetId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:new dicomhero::DataSet(get_dicomhero_object_holder(Tag)->getSequenceItem((size_t)dataSetId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


-(BOOL)sequenceItemExists:(unsigned int) dataSetId
{
    return (BOOL)(get_dicomhero_object_holder(Tag)->sequenceItemExists((size_t)dataSetId));
}


-(DicomheroTagType) dataType
{
    return (DicomheroTagType)get_dicomhero_object_holder(Tag)->getDataType();
}


-(DicomheroWritingDataHandler*) getWritingDataHandler:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroWritingDataHandler alloc] initWithDicomheroWritingDataHandler:new dicomhero::WritingDataHandler(get_dicomhero_object_holder(Tag)->getWritingDataHandler((size_t)bufferId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


-(DicomheroWritingDataHandlerNumeric*) getWritingDataHandlerNumeric:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroWritingDataHandlerNumeric alloc] initWithDicomheroWritingDataHandler:new dicomhero::WritingDataHandlerNumeric(get_dicomhero_object_holder(Tag)->getWritingDataHandlerNumeric((size_t)bufferId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


-(DicomheroWritingDataHandlerNumeric*) getWritingDataHandlerRaw:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroWritingDataHandlerNumeric alloc] initWithDicomheroWritingDataHandler:new dicomhero::WritingDataHandlerNumeric(get_dicomhero_object_holder(Tag)->getWritingDataHandlerRaw((size_t)bufferId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


-(DicomheroStreamWriter*) getStreamWriter:(unsigned int) bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroStreamWriter alloc] initWithDicomheroStreamWriter:new dicomhero::StreamWriter(get_dicomhero_object_holder(Tag)->getStreamWriter((size_t)bufferId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroDataSet*) appendSequenceItem:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:new dicomhero::DataSet(
            get_dicomhero_object_holder(Tag)->appendSequenceItem())];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


-(void) setStream:(unsigned int) bufferId stream:(DicomheroFileStreamInput*)pStream error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(Tag)->setStream((size_t)bufferId, *(dicomhero::FileStreamInput*)(get_other_dicomhero_object_holder(pStream, BaseStreamInput)));

    OBJC_DICOMHERO_FUNCTION_END();

}

@end

