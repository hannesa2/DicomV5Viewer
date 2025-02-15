/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#import "../include/imebraobjc/imebra_dataset.h"
#import "../include/imebraobjc/imebra_tag.h"
#import "../include/imebraobjc/imebra_tagId.h"
#import "../include/imebraobjc/imebra_image.h"
#import "../include/imebraobjc/imebra_overlay.h"
#import "../include/imebraobjc/imebra_lut.h"
#import "../include/imebraobjc/imebra_readingDataHandler.h"
#import "../include/imebraobjc/imebra_readingDataHandlerNumeric.h"
#import "../include/imebraobjc/imebra_writingDataHandler.h"
#import "../include/imebraobjc/imebra_writingDataHandlerNumeric.h"
#import "../include/imebraobjc/imebra_dateAge.h"
#import "../include/imebraobjc/imebra_patientName.h"
#import "../include/imebraobjc/imebra_VOIDescription.h"
#import "../include/imebraobjc/imebra_streamReader.h"
#import "../include/imebraobjc/imebra_streamWriter.h"

#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"
#include "imebra_strings.h"
#include <imebra/dataSet.h>
#include <imebra/tag.h>
#include <imebra/image.h>
#include <imebra/overlay.h>
#include <imebra/lut.h>
#include <imebra/readingDataHandler.h>
#include <imebra/readingDataHandlerNumeric.h>
#include <imebra/writingDataHandler.h>
#include <imebra/writingDataHandlerNumeric.h>
#include <imebra/definitions.h>
#include <imebra/age.h>
#include <imebra/date.h>
#include <imebra/patientName.h>
#include <imebra/VOIDescription.h>
#include <imebra/streamReader.h>
#include <imebra/streamWriter.h>

#import <Foundation/NSString.h>


@implementation ImebraDataSet

-(id)initWithImebraDataSet:define_imebra_parameter(DataSet)
{
    reset_imebra_object_holder(DataSet);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DataSet, get_imebra_parameter(DataSet));
    }
    else
    {
        delete get_imebra_parameter(DataSet);
    }
    return self;
}

-(void)dealloc
{
    delete_imebra_object_holder(DataSet);
}

-(NSArray*)getTags
{
    NSMutableArray* pIds = [[NSMutableArray alloc] init];
    imebra::tagsIds_t ids = get_imebra_object_holder(DataSet)->getTags();
    for(const imebra::TagId& tagId: ids)
    {
        [pIds addObject: [[ImebraTagId alloc] initWithGroup:tagId.getGroupId() groupOrder:tagId.getGroupOrder() tag:tagId.getTagId()] ];
    }

    return pIds;
}

-(ImebraTag*) getTag:(ImebraTagId*)tagId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraTag alloc] initWithImebraTag:new imebra::Tag(get_imebra_object_holder(DataSet)->getTag(*get_other_imebra_object_holder(tagId, TagId)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraImage*) getImage:(unsigned int) frameNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraImage alloc] initWithImebraImage:new imebra::Image(get_imebra_object_holder(DataSet)->getImage(frameNumber))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraOverlay*) getOverlay:(unsigned int) overlayNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraOverlay alloc] initWithImebraOverlay:new imebra::Overlay(get_imebra_object_holder(DataSet)->getOverlay(overlayNumber))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraImage*) getImageApplyModalityTransform:(unsigned int) frameNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraImage alloc] initWithImebraImage:new imebra::Image(get_imebra_object_holder(DataSet)->getImageApplyModalityTransform(frameNumber))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(NSArray*) getVOIs:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    NSMutableArray* pVOIs = [[NSMutableArray alloc] init];
    imebra::vois_t vois = get_imebra_object_holder(DataSet)->getVOIs();
    for(const imebra::VOIDescription& description: vois)
    {
        [pVOIs addObject:
            [[ImebraVOIDescription alloc] initWithImebraVOIDescription:new imebra::VOIDescription(description)] ];
    }

    return pVOIs;

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


-(ImebraDataSet*) getFunctionalGroupDataSet:(unsigned int)frameNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraDataSet alloc] initWithImebraDataSet:
            new imebra::DataSet(get_imebra_object_holder(DataSet)->getFunctionalGroupDataSet((size_t)frameNumber))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


-(ImebraStreamReader*) getStreamReader:(ImebraTagId*)pTagId bufferId:(unsigned int)bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraStreamReader alloc] initWithImebraStreamReader:new imebra::StreamReader(get_imebra_object_holder(DataSet)->getStreamReader(imebra::TagId((std::uint16_t)pTagId.groupId, (std::uint32_t)pTagId.groupOrder, (std::uint16_t)pTagId.tagId), (size_t)bufferId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraDataSet*) getSequenceItem:(ImebraTagId*)pTagId item:(unsigned int)itemId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraDataSet alloc] initWithImebraDataSet:
            new imebra::DataSet(get_imebra_object_holder(DataSet)->getSequenceItem(imebra::TagId((std::uint16_t)pTagId.groupId, (std::uint32_t)pTagId.groupOrder, (std::uint16_t)pTagId.tagId), (size_t)itemId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraLUT*) getLUT:(ImebraTagId*)pTagId item:(unsigned int)itemId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraLUT alloc] initWithImebraLut:
            new imebra::LUT(get_imebra_object_holder(DataSet)->getLUT(imebra::TagId((std::uint16_t)pTagId.groupId, (std::uint32_t)pTagId.groupOrder, (std::uint16_t)pTagId.tagId), (size_t)itemId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraReadingDataHandler*) getReadingDataHandler:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraReadingDataHandler alloc] initWithImebraReadingDataHandler:
            new imebra::ReadingDataHandler(get_imebra_object_holder(DataSet)->getReadingDataHandler(*get_other_imebra_object_holder(tagId, TagId), bufferId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraReadingDataHandlerNumeric*) getReadingDataHandlerNumeric:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraReadingDataHandlerNumeric alloc] initWithImebraReadingDataHandler:
            new imebra::ReadingDataHandlerNumeric(get_imebra_object_holder(DataSet)->getReadingDataHandlerNumeric(*get_other_imebra_object_holder(tagId, TagId), bufferId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraReadingDataHandlerNumeric*) getReadingDataHandlerRaw:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraReadingDataHandlerNumeric alloc] initWithImebraReadingDataHandler:
            new imebra::ReadingDataHandlerNumeric(get_imebra_object_holder(DataSet)->getReadingDataHandlerRaw(*get_other_imebra_object_holder(tagId, TagId), bufferId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(signed int)getInt32:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getInt32(*get_other_imebra_object_holder(tagId, TagId), elementNumber);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(signed long long)getInt64:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getInt64(*get_other_imebra_object_holder(tagId, TagId), elementNumber);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(signed int)getSignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getInt32(*get_other_imebra_object_holder(tagId, TagId), elementNumber);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(signed short)getInt16:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getInt16(*get_other_imebra_object_holder(tagId, TagId), elementNumber);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(signed char)getInt8:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getInt8(*get_other_imebra_object_holder(tagId, TagId), elementNumber);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(signed int)getInt32:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed int)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getInt32(*get_other_imebra_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(signed long long)getInt64:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed long long)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getInt64(*get_other_imebra_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(signed int)getSignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed int)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getInt32(*get_other_imebra_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(signed short)getInt16:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed short)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getInt16(*get_other_imebra_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(signed char)getInt8:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(signed char)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getInt8(*get_other_imebra_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned int)getUint32:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getUint32(*get_other_imebra_object_holder(tagId, TagId), elementNumber);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned long long)getUint64:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getUint64(*get_other_imebra_object_holder(tagId, TagId), elementNumber);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned int)getUnsignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getUint32(*get_other_imebra_object_holder(tagId, TagId), elementNumber);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned short)getUint16:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getUint16(*get_other_imebra_object_holder(tagId, TagId), elementNumber);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned char)getUint8:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getUint8(*get_other_imebra_object_holder(tagId, TagId), elementNumber);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned int)getUint32:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned int)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getUint32(*get_other_imebra_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned long long)getUint64:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned long long)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getUint64(*get_other_imebra_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned int)getUnsignedLong:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned int)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getUint32(*get_other_imebra_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned short)getUint16:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned short)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getUint16(*get_other_imebra_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned char)getUint8:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(unsigned char)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getUint8(*get_other_imebra_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(double)getDouble:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getDouble(*get_other_imebra_object_holder(tagId, TagId), elementNumber);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0.0f);
}

-(float)getFloat:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getFloat(*get_other_imebra_object_holder(tagId, TagId), elementNumber);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0.0f);
}

-(double)getDouble:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(double)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getDouble(*get_other_imebra_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0.0f);
}

-(float)getFloat:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(float)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return get_imebra_object_holder(DataSet)->getFloat(*get_other_imebra_object_holder(tagId, TagId), elementNumber, defaultValue);

    OBJC_IMEBRA_FUNCTION_END_RETURN(0.0f);
}

-(NSString*)getString:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return imebra::stringToNSString(get_imebra_object_holder(DataSet)->getString(*get_other_imebra_object_holder(tagId, TagId), elementNumber));

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(NSString*)getString:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(NSString*)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return imebra::stringToNSString(get_imebra_object_holder(DataSet)->getString(*get_other_imebra_object_holder(tagId, TagId), elementNumber, imebra::NSStringToString(defaultValue)));

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraAge*)getAge:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    const imebra::Age age = get_imebra_object_holder(DataSet)->getAge(*get_other_imebra_object_holder(tagId, TagId), elementNumber);
    return [[ImebraAge alloc] initWithImebraAge: new imebra::Age(age)];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraAge*)getAge:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(ImebraAge*)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    const imebra::Age age = get_imebra_object_holder(DataSet)->getAge(*get_other_imebra_object_holder(tagId, TagId), elementNumber, *get_other_imebra_object_holder(defaultValue,Age));
    return [[ImebraAge alloc] initWithImebraAge: new imebra::Age(age)];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraDate*)getDate:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    const imebra::Date date = get_imebra_object_holder(DataSet)->getDate(*get_other_imebra_object_holder(tagId, TagId), elementNumber);
    return [[ImebraDate alloc] initWithImebraDate: new imebra::Date(date)];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraDate*)getDate:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(ImebraDate*)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    const imebra::Date date = get_imebra_object_holder(DataSet)->getDate(*get_other_imebra_object_holder(tagId, TagId), elementNumber, *get_other_imebra_object_holder(defaultValue, Date));
    return [[ImebraDate alloc] initWithImebraDate: new imebra::Date(date)];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraPatientName*)getPatientName:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    const imebra::PatientName patientName = get_imebra_object_holder(DataSet)->getPatientName(*get_other_imebra_object_holder(tagId, TagId), elementNumber);
    return [[ImebraPatientName alloc] initWithImebraPatientName: new imebra::PatientName(patientName)];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraPatientName*)getPatientName:(ImebraTagId*)tagId elementNumber:(unsigned int)elementNumber defaultValue:(ImebraPatientName*)defaultValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    const imebra::PatientName patientName = get_imebra_object_holder(DataSet)->getPatientName(*get_other_imebra_object_holder(tagId, TagId), elementNumber, *get_other_imebra_object_holder(defaultValue, PatientName));
    return [[ImebraPatientName alloc] initWithImebraPatientName: new imebra::PatientName(patientName)];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraTagType)getDataType:(ImebraTagId*)tagId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return (ImebraTagType)(get_imebra_object_holder(DataSet)->getDataType(*get_other_imebra_object_holder(tagId, TagId)));

    OBJC_IMEBRA_FUNCTION_END_RETURN(ImebraTagTypeAE);
}

@end


@implementation ImebraMutableDataSet

-(id)init
{
    reset_imebra_object_holder(DataSet);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DataSet, new imebra::MutableDataSet);
    }
    return self;
}

-(id)initWithTransferSyntax:(NSString*)transferSyntax
{
    reset_imebra_object_holder(DataSet);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DataSet, new imebra::MutableDataSet(imebra::NSStringToString(transferSyntax)));
    }
    return self;
}

-(id)initWithTransferSyntax:(NSString*)transferSyntax charsets:(NSArray*)pCharsets
{
    reset_imebra_object_holder(DataSet);
    self = [super init];
    if(self)
    {
        imebra::charsetsList_t charsets;

        size_t charsetsCount = [pCharsets count];
        for(size_t scanCharsets(0); scanCharsets != charsetsCount; ++scanCharsets)
        {
            charsets.push_back(imebra::NSStringToString([pCharsets objectAtIndex:scanCharsets]));
        }

        set_imebra_object_holder(DataSet, new imebra::MutableDataSet(imebra::NSStringToString(transferSyntax), charsets));
    }
    return self;
}

-(ImebraMutableTag*) getTagCreate:(ImebraTagId*)tagId tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraMutableTag alloc] initWithImebraMutableTag:
            new imebra::MutableTag(((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->getTagCreate(*get_other_imebra_object_holder(tagId, TagId), (imebra::tagVR_t)tagVR))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraMutableTag*) getTagCreate:(ImebraTagId*)tagId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraMutableTag alloc] initWithImebraMutableTag:
            new imebra::MutableTag(((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->getTagCreate(*get_other_imebra_object_holder(tagId, TagId)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(void) setImage:(unsigned int)frameNumber image:(ImebraImage*)image quality:(ImebraImageQuality)quality error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setImage(frameNumber, *get_other_imebra_object_holder(image, Image), (imebra::imageQuality_t)quality);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void) setOverlay:(unsigned int)overlayNumber overlay:(ImebraOverlay*)overlay error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setOverlay(overlayNumber, *get_other_imebra_object_holder(overlay, Overlay));

    OBJC_IMEBRA_FUNCTION_END();
}

-(ImebraStreamWriter*) getStreamWriter:(ImebraTagId*)pTagId bufferId:(unsigned int)bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraStreamWriter alloc] initWithImebraStreamWriter:
        new imebra::StreamWriter(
            ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->getStreamWriter(imebra::TagId((std::uint16_t)pTagId.groupId, (std::uint32_t)pTagId.groupOrder, (std::uint16_t)pTagId.tagId), bufferId)) ];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraStreamWriter*) getStreamWriter:(ImebraTagId*)pTagId bufferId:(unsigned int)bufferId tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraStreamWriter alloc] initWithImebraStreamWriter:
        new imebra::StreamWriter(
            ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->getStreamWriter(imebra::TagId((std::uint16_t)pTagId.groupId, (std::uint32_t)pTagId.groupOrder, (std::uint16_t)pTagId.tagId), bufferId, (imebra::tagVR_t)tagVR)) ];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraMutableDataSet*) appendSequenceItem:(ImebraTagId*)pTagId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraMutableDataSet alloc] initWithImebraDataSet:
        new imebra::MutableDataSet(
            ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->appendSequenceItem(imebra::TagId((std::uint16_t)pTagId.groupId, (std::uint32_t)pTagId.groupOrder, (std::uint16_t)pTagId.tagId))) ];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraWritingDataHandler*) getWritingDataHandler:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraWritingDataHandler alloc] initWithImebraWritingDataHandler:
            new imebra::WritingDataHandler(((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->getWritingDataHandler(*get_other_imebra_object_holder(tagId, TagId), bufferId, (imebra::tagVR_t)tagVR))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraWritingDataHandler*) getWritingDataHandler:(ImebraTagId*)tagId bufferId:(unsigned int)bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraWritingDataHandler alloc] initWithImebraWritingDataHandler:
            new imebra::WritingDataHandler(((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->getWritingDataHandler(*get_other_imebra_object_holder(tagId, TagId), bufferId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraWritingDataHandlerNumeric*) getWritingDataHandlerNumeric:(ImebraTagId*)tagId bufferId:(unsigned long)bufferId tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraWritingDataHandlerNumeric alloc] initWithImebraWritingDataHandler:
            new imebra::WritingDataHandlerNumeric(((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->getWritingDataHandlerNumeric(*get_other_imebra_object_holder(tagId, TagId), bufferId, (imebra::tagVR_t)tagVR))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraWritingDataHandlerNumeric*) getWritingDataHandlerNumeric:(ImebraTagId*)tagId bufferId:(unsigned long)bufferId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraWritingDataHandlerNumeric alloc] initWithImebraWritingDataHandler:
            new imebra::WritingDataHandlerNumeric(((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->getWritingDataHandlerNumeric(*get_other_imebra_object_holder(tagId, TagId), bufferId))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(void)setInt64:(ImebraTagId*)tagId newValue:(signed long long)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setInt64(*get_other_imebra_object_holder(tagId, TagId), newValue, (imebra::tagVR_t)tagVR);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setInt32:(ImebraTagId*)tagId newValue:(signed int)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setInt32(*get_other_imebra_object_holder(tagId, TagId), newValue, (imebra::tagVR_t)tagVR);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setSignedLong:(ImebraTagId*)tagId newValue:(signed int)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setInt32(*get_other_imebra_object_holder(tagId, TagId), newValue, (imebra::tagVR_t)tagVR);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setInt16:(ImebraTagId*)tagId newValue:(signed short)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setInt16(*get_other_imebra_object_holder(tagId, TagId), newValue, (imebra::tagVR_t)tagVR);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setInt8:(ImebraTagId*)tagId newValue:(signed char)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setInt8(*get_other_imebra_object_holder(tagId, TagId), newValue, (imebra::tagVR_t)tagVR);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setInt64:(ImebraTagId*)tagId newValue:(signed long long)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setInt64(*get_other_imebra_object_holder(tagId, TagId), newValue);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setInt32:(ImebraTagId*)tagId newValue:(signed int)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setInt32(*get_other_imebra_object_holder(tagId, TagId), newValue);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setSignedLong:(ImebraTagId*)tagId newValue:(signed int)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setInt32(*get_other_imebra_object_holder(tagId, TagId), newValue);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setInt16:(ImebraTagId*)tagId newValue:(signed short)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setInt16(*get_other_imebra_object_holder(tagId, TagId), newValue);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setInt8:(ImebraTagId*)tagId newValue:(signed char)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setInt8(*get_other_imebra_object_holder(tagId, TagId), newValue);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setUint64:(ImebraTagId*)tagId newValue:(unsigned long long)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setUint64(*get_other_imebra_object_holder(tagId, TagId), newValue, (imebra::tagVR_t)tagVR);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setUint32:(ImebraTagId*)tagId newValue:(unsigned int)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setUint32(*get_other_imebra_object_holder(tagId, TagId), newValue, (imebra::tagVR_t)tagVR);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setUnsignedLong:(ImebraTagId*)tagId newValue:(unsigned int)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setUint32(*get_other_imebra_object_holder(tagId, TagId), newValue, (imebra::tagVR_t)tagVR);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setUint16:(ImebraTagId*)tagId newValue:(unsigned short)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setUint16(*get_other_imebra_object_holder(tagId, TagId), newValue, (imebra::tagVR_t)tagVR);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setUint8:(ImebraTagId*)tagId newValue:(unsigned char)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setUint8(*get_other_imebra_object_holder(tagId, TagId), newValue, (imebra::tagVR_t)tagVR);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setUint64:(ImebraTagId*)tagId newValue:(unsigned long long)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setUint64(*get_other_imebra_object_holder(tagId, TagId), newValue);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setUint32:(ImebraTagId*)tagId newValue:(unsigned int)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setUint32(*get_other_imebra_object_holder(tagId, TagId), newValue);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setUnsignedLong:(ImebraTagId*)tagId newValue:(unsigned int)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setUint32(*get_other_imebra_object_holder(tagId, TagId), newValue);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setUint16:(ImebraTagId*)tagId newValue:(unsigned short)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setUint16(*get_other_imebra_object_holder(tagId, TagId), newValue);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setUint8:(ImebraTagId*)tagId newValue:(unsigned char)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setUint8(*get_other_imebra_object_holder(tagId, TagId), newValue);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setDouble:(ImebraTagId*)tagId newValue:(double)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setDouble(*get_other_imebra_object_holder(tagId, TagId), newValue, (imebra::tagVR_t)tagVR);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setFloat:(ImebraTagId*)tagId newValue:(float)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setFloat(*get_other_imebra_object_holder(tagId, TagId), newValue, (imebra::tagVR_t)tagVR);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setDouble:(ImebraTagId*)tagId newValue:(double)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setDouble(*get_other_imebra_object_holder(tagId, TagId), newValue);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setFloat:(ImebraTagId*)tagId newValue:(float)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setFloat(*get_other_imebra_object_holder(tagId, TagId), newValue);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setString:(ImebraTagId*)tagId newValue:(NSString*)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setString(*get_other_imebra_object_holder(tagId, TagId), imebra::NSStringToString(newValue), (imebra::tagVR_t)tagVR);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setString:(ImebraTagId*)tagId newValue:(NSString*)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setString(*get_other_imebra_object_holder(tagId, TagId), imebra::NSStringToString(newValue));

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setAge:(ImebraTagId*)tagId newValue:(ImebraAge*)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setAge(*get_other_imebra_object_holder(tagId, TagId), *get_other_imebra_object_holder(newValue, Age));

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setDate:(ImebraTagId*)tagId newValue:(ImebraDate*)newValue tagVR:(ImebraTagType)tagVR error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setDate(*get_other_imebra_object_holder(tagId, TagId), *get_other_imebra_object_holder(newValue, Date), (imebra::tagVR_t)tagVR);

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setDate:(ImebraTagId*)tagId newValue:(ImebraDate*)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setDate(*get_other_imebra_object_holder(tagId, TagId), *get_other_imebra_object_holder(newValue, Date));

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)setPatientName:(ImebraTagId*)tagId newValue:(ImebraPatientName*)newValue error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableDataSet*)get_imebra_object_holder(DataSet))->setPatientName(*get_other_imebra_object_holder(tagId, TagId), *get_other_imebra_object_holder(newValue, PatientName));

    OBJC_IMEBRA_FUNCTION_END();
}

@end
