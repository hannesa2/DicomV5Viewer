/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Dicomhero is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Dicomhero from the Dicomhero’s website (https://dicomhero.com).
*/

#import "../include/dicomhero6_objc/dicomhero_dataset.h"
#import "../include/dicomhero6_objc/dicomhero_lut.h"
#import "../include/dicomhero6_objc/dicomhero_tag.h"
#import "../include/dicomhero6_objc/dicomhero_tagId.h"
#import "../include/dicomhero6_objc/dicomhero_image.h"
#import "../include/dicomhero6_objc/dicomhero_overlay.h"
#import "../include/dicomhero6_objc/dicomhero_lut.h"
#import "../include/dicomhero6_objc/dicomhero_readingDataHandler.h"
#import "../include/dicomhero6_objc/dicomhero_readingDataHandlerNumeric.h"
#import "../include/dicomhero6_objc/dicomhero_writingDataHandler.h"
#import "../include/dicomhero6_objc/dicomhero_writingDataHandlerNumeric.h"
#import "../include/dicomhero6_objc/dicomhero_dateAge.h"
#import "../include/dicomhero6_objc/dicomhero_patientName.h"
#import "../include/dicomhero6_objc/dicomhero_VOIDescription.h"
#import "../include/dicomhero6_objc/dicomhero_streamReader.h"
#import "../include/dicomhero6_objc/dicomhero_streamWriter.h"

#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"
#include "dicomhero_strings.h"
#include <dicomhero6/dataSet.h>
#include <dicomhero6/tag.h>
#include <dicomhero6/image.h>
#include <dicomhero6/overlay.h>
#include <dicomhero6/lut.h>
#include <dicomhero6/readingDataHandler.h>
#include <dicomhero6/readingDataHandlerNumeric.h>
#include <dicomhero6/writingDataHandler.h>
#include <dicomhero6/writingDataHandlerNumeric.h>
#include <dicomhero6/definitions.h>
#include <dicomhero6/age.h>
#include <dicomhero6/date.h>
#include <dicomhero6/patientName.h>
#include <dicomhero6/VOIDescription.h>
#include <dicomhero6/streamReader.h>
#include <dicomhero6/streamWriter.h>

#import <Foundation/NSString.h>


@implementation DicomheroDataSet

-(id)initWithDicomheroDataSet:define_dicomhero_parameter(DataSet)
{
    reset_dicomhero_object_holder(DataSet);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DataSet, get_dicomhero_parameter(DataSet));
    }
    else
    {
        delete get_dicomhero_parameter(DataSet);
    }
    return self;
}

-(id)init
{
    reset_dicomhero_object_holder(DataSet);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DataSet, new dicomhero::DataSet);
    }
    return self;
}

-(id)initWithTransferSyntax:(NSString*)transferSyntax
{
    reset_dicomhero_object_holder(DataSet);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DataSet, new dicomhero::DataSet(dicomhero::NSStringToString(transferSyntax)));
    }
    return self;
}

-(id)initWithTransferSyntax:(NSString*)transferSyntax charsets:(NSArray*)pCharsets
{
    reset_dicomhero_object_holder(DataSet);
    self = [super init];
    if(self)
    {
        dicomhero::charsetsList_t charsets;

        size_t charsetsCount = [pCharsets count];
        for(size_t scanCharsets(0); scanCharsets != charsetsCount; ++scanCharsets)
        {
            charsets.push_back(dicomhero::NSStringToString([pCharsets objectAtIndex:scanCharsets]));
        }

        set_dicomhero_object_holder(DataSet, new dicomhero::DataSet(dicomhero::NSStringToString(transferSyntax), charsets));
    }
    return self;
}

-(void)dealloc
{
    delete_dicomhero_object_holder(DataSet);
}

-(NSArray*)getTags
{
    NSMutableArray* pIds = [[NSMutableArray alloc] init];
    dicomhero::tagsIds_t ids = get_dicomhero_object_holder(DataSet)->getTags();
    for(const dicomhero::TagId& tagId: ids)
    {
        [pIds addObject: [[DicomheroTagId alloc] initWithGroup:tagId.getGroupId() groupOrder:tagId.getGroupOrder() tag:tagId.getTagId()] ];
    }

    return pIds;
}

-(DicomheroTag*) getTag:(DicomheroTagId*)tagId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroTag alloc] initWithDicomheroTag:new dicomhero::Tag(get_dicomhero_object_holder(DataSet)->getTag(*get_other_dicomhero_object_holder(tagId, TagId)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroImage*) getImage:(unsigned int) frameNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroImage alloc] initWithDicomheroImage:new dicomhero::Image(get_dicomhero_object_holder(DataSet)->getImage(frameNumber))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroOverlay*) getOverlay:(unsigned int) overlayNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroOverlay alloc] initWithDicomheroOverlay:new dicomhero::Overlay(get_dicomhero_object_holder(DataSet)->getOverlay(overlayNumber))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroImage*) getImageApplyModalityTransform:(unsigned int) frameNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroImage alloc] initWithDicomheroImage:new dicomhero::Image(get_dicomhero_object_holder(DataSet)->getImageApplyModalityTransform(frameNumber))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(NSArray*) getVOIs:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    NSMutableArray* pVOIs = [[NSMutableArray alloc] init];
    dicomhero::vois_t vois = get_dicomhero_object_holder(DataSet)->getVOIs();
    for(const dicomhero::VOIDescription& description: vois)
    {
        [pVOIs addObject:
            [[DicomheroVOIDescription alloc] initWithDicomheroVOIDescription:new dicomhero::VOIDescription(description)] ];
    }

    return pVOIs;

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


-(DicomheroDataSet*) getFunctionalGroupDataSet:(unsigned int)frameNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:
            new dicomhero::DataSet(get_dicomhero_object_holder(DataSet)->getFunctionalGroupDataSet((size_t)frameNumber))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


-(DicomheroStreamReader*) getStreamReader:(DicomheroTagId*)pTagId bufferId:(unsigned int)bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroStreamReader alloc] initWithDicomheroStreamReader:new dicomhero::StreamReader(get_dicomhero_object_holder(DataSet)->getStreamReader(dicomhero::TagId((std::uint16_t)pTagId.groupId, (std::uint32_t)pTagId.groupOrder, (std::uint16_t)pTagId.tagId), (size_t)bufferId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroDataSet*) getSequenceItem:(DicomheroTagId*)pTagId item:(unsigned int)itemId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:
            new dicomhero::DataSet(get_dicomhero_object_holder(DataSet)->getSequenceItem(dicomhero::TagId((std::uint16_t)pTagId.groupId, (std::uint32_t)pTagId.groupOrder, (std::uint16_t)pTagId.tagId), (size_t)itemId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroLUT*) getLUT:(DicomheroTagId*)pTagId item:(unsigned int)itemId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroLUT alloc] initWithDicomheroLut:
            new dicomhero::LUT(get_dicomhero_object_holder(DataSet)->getLUT(dicomhero::TagId((std::uint16_t)pTagId.groupId, (std::uint32_t)pTagId.groupOrder, (std::uint16_t)pTagId.tagId), (size_t)itemId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroReadingDataHandler*) getReadingDataHandler:(DicomheroTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroReadingDataHandler alloc] initWithDicomheroReadingDataHandler:
            new dicomhero::ReadingDataHandler(get_dicomhero_object_holder(DataSet)->getReadingDataHandler(*get_other_dicomhero_object_holder(tagId, TagId), bufferId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroReadingDataHandlerNumeric*) getReadingDataHandlerNumeric:(DicomheroTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroReadingDataHandlerNumeric alloc] initWithDicomheroReadingDataHandler:
            new dicomhero::ReadingDataHandlerNumeric(get_dicomhero_object_holder(DataSet)->getReadingDataHandlerNumeric(*get_other_dicomhero_object_holder(tagId, TagId), bufferId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroReadingDataHandlerNumeric*) getReadingDataHandlerRaw:(DicomheroTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroReadingDataHandlerNumeric alloc] initWithDicomheroReadingDataHandler:
            new dicomhero::ReadingDataHandlerNumeric(get_dicomhero_object_holder(DataSet)->getReadingDataHandlerRaw(*get_other_dicomhero_object_holder(tagId, TagId), bufferId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(signed int)getInt32:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getInt32(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(signed long long)getInt64:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getInt64(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(signed int)getSignedLong:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getInt32(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(signed short)getInt16:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getInt16(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(signed char)getInt8:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getInt8(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(signed int)getInt32:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed int)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getInt32(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(signed long long)getInt64:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed long long)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getInt64(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(signed int)getSignedLong:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed int)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getInt32(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(signed short)getInt16:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed short)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getInt16(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(signed char)getInt8:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed char)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getInt8(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned int)getUint32:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getUint32(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned long long)getUint64:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getUint64(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned int)getUnsignedLong:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getUint32(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned short)getUint16:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getUint16(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned char)getUint8:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getUint8(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned int)getUint32:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned int)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getUint32(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned long long)getUint64:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned long long)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getUint64(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned int)getUnsignedLong:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned int)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getUint32(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned short)getUint16:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned short)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getUint16(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned char)getUint8:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned char)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getUint8(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(double)getDouble:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getDouble(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0.0f);
}

-(float)getFloat:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getFloat(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0.0f);
}

-(double)getDouble:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(double)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getDouble(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0.0f);
}

-(float)getFloat:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(float)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return get_dicomhero_object_holder(DataSet)->getFloat(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0.0f);
}

-(NSString*)getString:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return dicomhero::stringToNSString(get_dicomhero_object_holder(DataSet)->getString(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber));

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(NSString*)getString:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(NSString*)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return dicomhero::stringToNSString(get_dicomhero_object_holder(DataSet)->getString(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, dicomhero::NSStringToString(defaultValue)));

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroAge*)getAge:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    const dicomhero::Age age = get_dicomhero_object_holder(DataSet)->getAge(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);
    return [[DicomheroAge alloc] initWithDicomheroAge: new dicomhero::Age(age)];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroAge*)getAge:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(DicomheroAge*)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    const dicomhero::Age age = get_dicomhero_object_holder(DataSet)->getAge(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, *get_other_dicomhero_object_holder(defaultValue,Age));
    return [[DicomheroAge alloc] initWithDicomheroAge: new dicomhero::Age(age)];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroDate*)getDate:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    const dicomhero::Date date = get_dicomhero_object_holder(DataSet)->getDate(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);
    return [[DicomheroDate alloc] initWithDicomheroDate: new dicomhero::Date(date)];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroDate*)getDate:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(DicomheroDate*)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    const dicomhero::Date date = get_dicomhero_object_holder(DataSet)->getDate(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, *get_other_dicomhero_object_holder(defaultValue, Date));
    return [[DicomheroDate alloc] initWithDicomheroDate: new dicomhero::Date(date)];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroPatientName*)getPatientName:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    const dicomhero::PatientName patientName = get_dicomhero_object_holder(DataSet)->getPatientName(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber);
    return [[DicomheroPatientName alloc] initWithDicomheroPatientName: new dicomhero::PatientName(patientName)];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroPatientName*)getPatientName:(DicomheroTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(DicomheroPatientName*)defaultValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    const dicomhero::PatientName patientName = get_dicomhero_object_holder(DataSet)->getPatientName(*get_other_dicomhero_object_holder(tagId, TagId), elementNumber, *get_other_dicomhero_object_holder(defaultValue, PatientName));
    return [[DicomheroPatientName alloc] initWithDicomheroPatientName: new dicomhero::PatientName(patientName)];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroTagType)getDataType:(DicomheroTagId*)tagId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return (DicomheroTagType)(get_dicomhero_object_holder(DataSet)->getDataType(*get_other_dicomhero_object_holder(tagId, TagId)));

    OBJC_DICOMHERO_FUNCTION_END_RETURN(DicomheroTagTypeAE);
}

-(DicomheroTag*) getTagCreate:(DicomheroTagId*)tagId tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroTag alloc] initWithDicomheroTag:
            new dicomhero::Tag(get_dicomhero_object_holder(DataSet)->getTagCreate(*get_other_dicomhero_object_holder(tagId, TagId), (dicomhero::tagVR_t)tagVR))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroTag*) getTagCreate:(DicomheroTagId*)tagId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroTag alloc] initWithDicomheroTag:
            new dicomhero::Tag(get_dicomhero_object_holder(DataSet)->getTagCreate(*get_other_dicomhero_object_holder(tagId, TagId)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(void) setImage:(unsigned int)frameNumber image:(DicomheroImage*)image quality:(DicomheroImageQuality)quality error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setImage(frameNumber, *get_other_dicomhero_object_holder(image, Image), (dicomhero::imageQuality_t)quality);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void) setOverlay:(unsigned int)overlayNumber overlay:(DicomheroOverlay*)overlay error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setOverlay(overlayNumber, *get_other_dicomhero_object_holder(overlay, Overlay));

    OBJC_DICOMHERO_FUNCTION_END();
}

-(DicomheroStreamWriter*) getStreamWriter:(DicomheroTagId*)pTagId bufferId:(unsigned int)bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroStreamWriter alloc] initWithDicomheroStreamWriter:
        new dicomhero::StreamWriter(
            get_dicomhero_object_holder(DataSet)->getStreamWriter(dicomhero::TagId((std::uint16_t)pTagId.groupId, (std::uint32_t)pTagId.groupOrder, (std::uint16_t)pTagId.tagId), bufferId)) ];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroStreamWriter*) getStreamWriter:(DicomheroTagId*)pTagId bufferId:(unsigned int)bufferId tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroStreamWriter alloc] initWithDicomheroStreamWriter:
        new dicomhero::StreamWriter(
            get_dicomhero_object_holder(DataSet)->getStreamWriter(dicomhero::TagId((std::uint16_t)pTagId.groupId, (std::uint32_t)pTagId.groupOrder, (std::uint16_t)pTagId.tagId), bufferId, (dicomhero::tagVR_t)tagVR)) ];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroDataSet*) appendSequenceItem:(DicomheroTagId*)pTagId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:
        new dicomhero::DataSet(
            get_dicomhero_object_holder(DataSet)->appendSequenceItem(dicomhero::TagId((std::uint16_t)pTagId.groupId, (std::uint32_t)pTagId.groupOrder, (std::uint16_t)pTagId.tagId))) ];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroWritingDataHandler*) getWritingDataHandler:(DicomheroTagId*)tagId bufferId:(unsigned int)bufferId tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroWritingDataHandler alloc] initWithDicomheroWritingDataHandler:
            new dicomhero::WritingDataHandler(get_dicomhero_object_holder(DataSet)->getWritingDataHandler(*get_other_dicomhero_object_holder(tagId, TagId), bufferId, (dicomhero::tagVR_t)tagVR))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroWritingDataHandler*) getWritingDataHandler:(DicomheroTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroWritingDataHandler alloc] initWithDicomheroWritingDataHandler:
            new dicomhero::WritingDataHandler(get_dicomhero_object_holder(DataSet)->getWritingDataHandler(*get_other_dicomhero_object_holder(tagId, TagId), bufferId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroWritingDataHandlerNumeric*) getWritingDataHandlerNumeric:(DicomheroTagId*)tagId bufferId:(unsigned long)bufferId tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroWritingDataHandlerNumeric alloc] initWithDicomheroWritingDataHandler:
            new dicomhero::WritingDataHandlerNumeric(get_dicomhero_object_holder(DataSet)->getWritingDataHandlerNumeric(*get_other_dicomhero_object_holder(tagId, TagId), bufferId, (dicomhero::tagVR_t)tagVR))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroWritingDataHandlerNumeric*) getWritingDataHandlerNumeric:(DicomheroTagId*)tagId bufferId:(unsigned long)bufferId error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroWritingDataHandlerNumeric alloc] initWithDicomheroWritingDataHandler:
            new dicomhero::WritingDataHandlerNumeric(get_dicomhero_object_holder(DataSet)->getWritingDataHandlerNumeric(*get_other_dicomhero_object_holder(tagId, TagId), bufferId))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(void)setInt64:(DicomheroTagId*)tagId newValue:(signed long long)newValue tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setInt64(*get_other_dicomhero_object_holder(tagId, TagId), newValue, (dicomhero::tagVR_t)tagVR);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setInt32:(DicomheroTagId*)tagId newValue:(signed int)newValue tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setInt32(*get_other_dicomhero_object_holder(tagId, TagId), newValue, (dicomhero::tagVR_t)tagVR);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setSignedLong:(DicomheroTagId*)tagId newValue:(signed int)newValue tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setInt32(*get_other_dicomhero_object_holder(tagId, TagId), newValue, (dicomhero::tagVR_t)tagVR);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setInt16:(DicomheroTagId*)tagId newValue:(signed short)newValue tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setInt16(*get_other_dicomhero_object_holder(tagId, TagId), newValue, (dicomhero::tagVR_t)tagVR);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setInt8:(DicomheroTagId*)tagId newValue:(signed char)newValue tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setInt8(*get_other_dicomhero_object_holder(tagId, TagId), newValue, (dicomhero::tagVR_t)tagVR);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setInt64:(DicomheroTagId*)tagId newValue:(signed long long)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setInt64(*get_other_dicomhero_object_holder(tagId, TagId), newValue);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setInt32:(DicomheroTagId*)tagId newValue:(signed int)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setInt32(*get_other_dicomhero_object_holder(tagId, TagId), newValue);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setSignedLong:(DicomheroTagId*)tagId newValue:(signed int)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setInt32(*get_other_dicomhero_object_holder(tagId, TagId), newValue);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setInt16:(DicomheroTagId*)tagId newValue:(signed short)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setInt16(*get_other_dicomhero_object_holder(tagId, TagId), newValue);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setInt8:(DicomheroTagId*)tagId newValue:(signed char)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setInt8(*get_other_dicomhero_object_holder(tagId, TagId), newValue);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setUint64:(DicomheroTagId*)tagId newValue:(unsigned long long)newValue tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setUint64(*get_other_dicomhero_object_holder(tagId, TagId), newValue, (dicomhero::tagVR_t)tagVR);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setUint32:(DicomheroTagId*)tagId newValue:(unsigned int)newValue tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setUint32(*get_other_dicomhero_object_holder(tagId, TagId), newValue, (dicomhero::tagVR_t)tagVR);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setUnsignedLong:(DicomheroTagId*)tagId newValue:(unsigned int)newValue tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setUint32(*get_other_dicomhero_object_holder(tagId, TagId), newValue, (dicomhero::tagVR_t)tagVR);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setUint16:(DicomheroTagId*)tagId newValue:(unsigned short)newValue tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setUint16(*get_other_dicomhero_object_holder(tagId, TagId), newValue, (dicomhero::tagVR_t)tagVR);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setUint8:(DicomheroTagId*)tagId newValue:(unsigned char)newValue tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setUint8(*get_other_dicomhero_object_holder(tagId, TagId), newValue, (dicomhero::tagVR_t)tagVR);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setUint64:(DicomheroTagId*)tagId newValue:(unsigned long long)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setUint64(*get_other_dicomhero_object_holder(tagId, TagId), newValue);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setUint32:(DicomheroTagId*)tagId newValue:(unsigned int)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setUint32(*get_other_dicomhero_object_holder(tagId, TagId), newValue);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setUnsignedLong:(DicomheroTagId*)tagId newValue:(unsigned int)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setUint32(*get_other_dicomhero_object_holder(tagId, TagId), newValue);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setUint16:(DicomheroTagId*)tagId newValue:(unsigned short)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setUint16(*get_other_dicomhero_object_holder(tagId, TagId), newValue);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setUint8:(DicomheroTagId*)tagId newValue:(unsigned char)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setUint8(*get_other_dicomhero_object_holder(tagId, TagId), newValue);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setDouble:(DicomheroTagId*)tagId newValue:(double)newValue tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setDouble(*get_other_dicomhero_object_holder(tagId, TagId), newValue, (dicomhero::tagVR_t)tagVR);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setFloat:(DicomheroTagId*)tagId newValue:(float)newValue tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setFloat(*get_other_dicomhero_object_holder(tagId, TagId), newValue, (dicomhero::tagVR_t)tagVR);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setDouble:(DicomheroTagId*)tagId newValue:(double)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setDouble(*get_other_dicomhero_object_holder(tagId, TagId), newValue);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setFloat:(DicomheroTagId*)tagId newValue:(float)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setFloat(*get_other_dicomhero_object_holder(tagId, TagId), newValue);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setString:(DicomheroTagId*)tagId newValue:(NSString*)newValue tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setString(*get_other_dicomhero_object_holder(tagId, TagId), dicomhero::NSStringToString(newValue), (dicomhero::tagVR_t)tagVR);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setString:(DicomheroTagId*)tagId newValue:(NSString*)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setString(*get_other_dicomhero_object_holder(tagId, TagId), dicomhero::NSStringToString(newValue));

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setAge:(DicomheroTagId*)tagId newValue:(DicomheroAge*)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setAge(*get_other_dicomhero_object_holder(tagId, TagId), *get_other_dicomhero_object_holder(newValue, Age));

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setDate:(DicomheroTagId*)tagId newValue:(DicomheroDate*)newValue tagVR:(DicomheroTagType)tagVR error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setDate(*get_other_dicomhero_object_holder(tagId, TagId), *get_other_dicomhero_object_holder(newValue, Date), (dicomhero::tagVR_t)tagVR);

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setDate:(DicomheroTagId*)tagId newValue:(DicomheroDate*)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setDate(*get_other_dicomhero_object_holder(tagId, TagId), *get_other_dicomhero_object_holder(newValue, Date));

    OBJC_DICOMHERO_FUNCTION_END();
}

-(void)setPatientName:(DicomheroTagId*)tagId newValue:(DicomheroPatientName*)newValue error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DataSet)->setPatientName(*get_other_dicomhero_object_holder(tagId, TagId), *get_other_dicomhero_object_holder(newValue, PatientName));

    OBJC_DICOMHERO_FUNCTION_END();
}

@end
