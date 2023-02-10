/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "../include/dicomhero6_objc/dicomhero_dimse.h"
#include <dicomhero6/dimse.h>
#include <dicomhero6/dataSet.h>
#include "dicomhero_implementation_macros.h"
#include "dicomhero_nserror.h"
#include "dicomhero_strings.h"

#import "../include/dicomhero6_objc/dicomhero_dataset.h"
#import "../include/dicomhero6_objc/dicomhero_tagId.h"
#import "../include/dicomhero6_objc/dicomhero_acse.h"

@implementation DicomheroDimseCommandBase

-(id)initWithDicomheroCommand:define_dicomhero_parameter(DimseCommandBase)
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, get_dicomhero_parameter(DimseCommandBase));
    }
    else
    {
        get_dicomhero_parameter(DimseCommandBase);
    }
    return self;

}


-(void)dealloc
{
    delete_dicomhero_object_holder(DimseCommandBase);
}

-(DicomheroDataSet*)getCommandDataSet:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:new dicomhero::DataSet(get_dicomhero_object_holder(DimseCommandBase)->getCommandDataSet())];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroDataSet*)getPayloadDataSet:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroDataSet alloc] initWithDicomheroDataSet:new dicomhero::DataSet(get_dicomhero_object_holder(DimseCommandBase)->getPayloadDataSet())];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(NSString*)getAbstractSyntax
{
    return dicomhero::stringToNSString(get_dicomhero_object_holder(DimseCommandBase)->getAbstractSyntax());
}

-(NSString*)getAffectedSopInstanceUid:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return dicomhero::stringToNSString(get_dicomhero_object_holder(DimseCommandBase)->getAffectedSopInstanceUid());

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(NSString*)getAffectedSopClassUid:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return dicomhero::stringToNSString(get_dicomhero_object_holder(DimseCommandBase)->getAffectedSopClassUid());

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(NSString*)getRequestedSopInstanceUid:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return dicomhero::stringToNSString(get_dicomhero_object_holder(DimseCommandBase)->getRequestedSopInstanceUid());

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(NSString*)getRequestedSopClassUid:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return dicomhero::stringToNSString(get_dicomhero_object_holder(DimseCommandBase)->getRequestedSopClassUid());

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}


@end


@implementation DicomheroDimseCommand

-(unsigned short) ID
{
    return (unsigned short)((dicomhero::DimseCommand*)get_dicomhero_object_holder(DimseCommandBase))->getID();
}

-(DicomheroDimseCommandType) commandType
{
    return (DicomheroDimseCommandType)((dicomhero::DimseCommand*)get_dicomhero_object_holder(DimseCommandBase))->getCommandType();
}

@end


@implementation DicomheroDimseResponse

-(DicomheroDimseStatus) status
{
    return (DicomheroDimseStatus)((dicomhero::DimseResponse*)get_dicomhero_object_holder(DimseCommandBase))->getStatus();
}

-(unsigned short) statusCode
{
    return (unsigned short)((dicomhero::DimseResponse*)get_dicomhero_object_holder(DimseCommandBase))->getStatusCode();
}

@end


@implementation DicomheroCPartialResponse

-(unsigned int)getRemainingSubOperations:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return (unsigned int)((dicomhero::CPartialResponse*)get_dicomhero_object_holder(DimseCommandBase))->getRemainingSubOperations();

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned int)getCompletedSubOperations:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return (unsigned int)((dicomhero::CPartialResponse*)get_dicomhero_object_holder(DimseCommandBase))->getCompletedSubOperations();

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

-(unsigned int)getFailedSubOperations:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return (unsigned int)((dicomhero::CPartialResponse*)get_dicomhero_object_holder(DimseCommandBase))->getFailedSubOperations();

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}


-(unsigned int)getWarningSubOperations:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return (unsigned int)((dicomhero::CPartialResponse*)get_dicomhero_object_holder(DimseCommandBase))->getWarningSubOperations();

    OBJC_DICOMHERO_FUNCTION_END_RETURN(0);
}

@end


@implementation DicomheroCStoreCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    priority:(DicomheroDimseCommandPriority)priority
    affectedSopClassUid:(NSString*)affectedSopClassUid
    affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
    originatorAET:(NSString*)originatorAET
    originatorMessageID:(unsigned short)originatorMessageID
    payload:(DicomheroDataSet*)pPayload
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::CStoreCommand(
                                     dicomhero::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     (dicomhero::dimseCommandPriority_t)priority,
                                     dicomhero::NSStringToString(affectedSopClassUid),
                                     dicomhero::NSStringToString(affectedSopInstanceUid),
                                     dicomhero::NSStringToString(originatorAET),
                                     (std::uint16_t)originatorMessageID,
                                     *get_other_dicomhero_object_holder(pPayload, DataSet)));
    }
    return self;

}


-(NSString*) originatorAET
{
    return dicomhero::stringToNSString(((dicomhero::CStoreCommand*)get_dicomhero_object_holder(DimseCommandBase))->getOriginatorAET());
}

-(unsigned short) originatorMessageID
{
    return (unsigned short)((dicomhero::CStoreCommand*)get_dicomhero_object_holder(DimseCommandBase))->getOriginatorMessageID();
}

@end


@implementation DicomheroCStoreResponse

-(id)initWithcommand:(DicomheroCStoreCommand*) pCommand
    responseCode:(DicomheroDimseStatusCode)responseCode
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::CStoreResponse(
                                     *(dicomhero::CStoreCommand*)get_other_dicomhero_object_holder(pCommand, DimseCommandBase),
                                     (dicomhero::dimseStatusCode_t)responseCode));
    }
    return self;

}

@end


@implementation DicomheroCGetCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    priority:(DicomheroDimseCommandPriority)priority
    affectedSopClassUid:(NSString*)affectedSopClassUid
    identifier:(DicomheroDataSet*)pIdentifier
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::CGetCommand(
                                     dicomhero::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     (dicomhero::dimseCommandPriority_t)priority,
                                     dicomhero::NSStringToString(affectedSopClassUid),
                                     *get_other_dicomhero_object_holder(pIdentifier, DataSet)));
    }
    return self;
}

@end


@implementation DicomheroCGetResponse

-(id)initWithCommand:(DicomheroCGetCommand*)pReceivedCommand
    responseCode:(DicomheroDimseStatusCode)responseCode
    remainingSubOperations:(unsigned int)remainingSubOperations
    completedSubOperations:(unsigned int)completedSubOperations
    failedSubOperations:(unsigned int)failedSubOperations
    warningSubOperations:(unsigned int)warningSubOperations
    identifier:(DicomheroDataSet*)pIdentifier
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::CGetResponse(
                                     *(dicomhero::CGetCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     (dicomhero::dimseStatusCode_t)responseCode,
                                     (std::uint32_t)remainingSubOperations,
                                     (std::uint32_t)completedSubOperations,
                                     (std::uint32_t)failedSubOperations,
                                     (std::uint32_t)warningSubOperations,
                                     *get_other_dicomhero_object_holder(pIdentifier, DataSet)));
    }
    return self;
}

-(id)initWithcommand:(DicomheroCGetCommand*)pReceivedCommand
    responseCode:(DicomheroDimseStatusCode)responseCode
    remainingSubOperations:(unsigned int)remainingSubOperations
    completedSubOperations:(unsigned int)completedSubOperations
    failedSubOperations:(unsigned int)failedSubOperations
    warningSubOperations:(unsigned int)warningSubOperations
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::CGetResponse(
                                     *(dicomhero::CGetCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     (dicomhero::dimseStatusCode_t)responseCode,
                                     (std::uint32_t)remainingSubOperations,
                                     (std::uint32_t)completedSubOperations,
                                     (std::uint32_t)failedSubOperations,
                                     (std::uint32_t)warningSubOperations));
    }
    return self;
}


@end


@implementation DicomheroCFindCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    priority:(DicomheroDimseCommandPriority)priority
    affectedSopClassUid:(NSString*)affectedSopClassUid
    identifier:(DicomheroDataSet*)pIdentifier
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::CFindCommand(
                                     dicomhero::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     (dicomhero::dimseCommandPriority_t)priority,
                                     dicomhero::NSStringToString(affectedSopClassUid),
                                     *get_other_dicomhero_object_holder(pIdentifier, DataSet)));
    }
    return self;
}

@end


@implementation DicomheroCFindResponse

-(id)initWithCommand:(DicomheroCFindCommand*)pReceivedCommand
    identifier:(DicomheroDataSet*)pIdentifier
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::CFindResponse(
                                     *(dicomhero::CFindCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     *get_other_dicomhero_object_holder(pIdentifier, DataSet)));
    }
    return self;
}

-(id)initWithcommand:(DicomheroCFindCommand*)pReceivedCommand
    responseCode:(DicomheroDimseStatusCode)responseCode
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::CFindResponse(
                                     *(dicomhero::CFindCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     (dicomhero::dimseStatusCode_t)responseCode));
    }
    return self;
}

@end


@implementation DicomheroCMoveCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    priority:(DicomheroDimseCommandPriority)priority
    affectedSopClassUid:(NSString*)affectedSopClassUid
    destinationAET:(NSString*)destinationAET
    identifier:(DicomheroDataSet*)pIdentifier
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::CMoveCommand(
                                     dicomhero::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     (dicomhero::dimseCommandPriority_t)priority,
                                     dicomhero::NSStringToString(affectedSopClassUid),
                                     dicomhero::NSStringToString(destinationAET),
                                     *get_other_dicomhero_object_holder(pIdentifier, DataSet)));
    }
    return self;
}

-(NSString*)getDestinationAET:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return dicomhero::stringToNSString(((dicomhero::CMoveCommand*)get_dicomhero_object_holder(DimseCommandBase))->getDestinationAET());

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

@end


@implementation DicomheroCMoveResponse

-(id)initWithCommand:(DicomheroCMoveCommand*)pReceivedCommand
    responseCode:(DicomheroDimseStatusCode)responseCode
    remainingSubOperations:(unsigned int)remainingSubOperations
    completedSubOperations:(unsigned int)completedSubOperations
    failedSubOperations:(unsigned int)failedSubOperations
    warningSubOperations:(unsigned int)warningSubOperations
    identifier:(DicomheroDataSet*)pIdentifier
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::CMoveResponse(
                                     *(dicomhero::CMoveCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     (dicomhero::dimseStatusCode_t)responseCode,
                                     (std::uint32_t)remainingSubOperations,
                                     (std::uint32_t)completedSubOperations,
                                     (std::uint32_t)failedSubOperations,
                                     (std::uint32_t)warningSubOperations,
                                     *get_other_dicomhero_object_holder(pIdentifier, DataSet)));
    }
    return self;

}

-(id)initWithcommand:(DicomheroCMoveCommand*)pReceivedCommand
    responseCode:(DicomheroDimseStatusCode)responseCode
    remainingSubOperations:(unsigned int)remainingSubOperations
    completedSubOperations:(unsigned int)completedSubOperations
    failedSubOperations:(unsigned int)failedSubOperations
    warningSubOperations:(unsigned int)warningSubOperations
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::CMoveResponse(
                                     *(dicomhero::CMoveCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     (dicomhero::dimseStatusCode_t)responseCode,
                                     (std::uint32_t)remainingSubOperations,
                                     (std::uint32_t)completedSubOperations,
                                     (std::uint32_t)failedSubOperations,
                                     (std::uint32_t)warningSubOperations));
    }
    return self;

}


@end


@implementation DicomheroCEchoCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    priority:(DicomheroDimseCommandPriority)priority
    affectedSopClassUid:(NSString*)affectedSopClassUid
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::CEchoCommand(
                                     dicomhero::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     (dicomhero::dimseCommandPriority_t)priority,
                                     dicomhero::NSStringToString(affectedSopClassUid)));
    }
    return self;

}

@end


@implementation DicomheroCEchoResponse

-(id)initWithcommand:(DicomheroCEchoCommand*)pReceivedCommand
    responseCode:(DicomheroDimseStatusCode)responseCode
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::CEchoResponse(
                                     *(dicomhero::CEchoCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     (dicomhero::dimseStatusCode_t)responseCode));
    }
    return self;

}

@end


@implementation DicomheroCCancelCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    priority:(DicomheroDimseCommandPriority)priority
    cancelMessageID:(unsigned short)cancelMessageID
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::CCancelCommand(
                                     dicomhero::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     (dicomhero::dimseCommandPriority_t)priority,
                                     (std::uint16_t)cancelMessageID));
    }
    return self;
}

-(unsigned short)cancelMessageID
{
    return (unsigned short)((dicomhero::CCancelCommand*)get_dicomhero_object_holder(DimseCommandBase))->getCancelMessageID();
}

@end


@implementation DicomheroNEventReportCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    affectedSopClassUid:(NSString*)affectedSopClassUid
    affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
    eventID:(unsigned short)eventID
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NEventReportCommand(
                                     dicomhero::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     dicomhero::NSStringToString(affectedSopClassUid),
                                     dicomhero::NSStringToString(affectedSopInstanceUid),
                                     (std::uint16_t)eventID));
    }
    return self;
}

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    affectedSopClassUid:(NSString*)affectedSopClassUid
    affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
    eventID:(unsigned short)eventID
    eventInformation:(DicomheroDataSet*)pEventInformation
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NEventReportCommand(
                                     dicomhero::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     dicomhero::NSStringToString(affectedSopClassUid),
                                     dicomhero::NSStringToString(affectedSopInstanceUid),
                                     (std::uint16_t)eventID,
                                     *get_other_dicomhero_object_holder(pEventInformation, DataSet)));
    }
    return self;
}

-(unsigned short) eventID
{
    return (unsigned short)((dicomhero::NEventReportCommand*)get_dicomhero_object_holder(DimseCommandBase))->getEventID();
}

@end


@implementation DicomheroNEventReportResponse

-(id)initWithCommand:(DicomheroNEventReportCommand*)pReceivedCommand
    eventReply:(DicomheroDataSet*)pEventReply
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NEventReportResponse(
                                     *(dicomhero::NEventReportCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     *get_other_dicomhero_object_holder(pEventReply, DataSet)));
    }
    return self;

}

-(id)initWithcommand:(DicomheroNEventReportCommand*)pReceivedCommand
    responseCode:(DicomheroDimseStatusCode)responseCode
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NEventReportResponse(
                                     *(dicomhero::NEventReportCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     (dicomhero::dimseStatusCode_t)responseCode));
    }
    return self;

}

-(unsigned short) eventID
{
    return (unsigned short)((dicomhero::NEventReportResponse*)get_dicomhero_object_holder(DimseCommandBase))->getEventID();
}

@end


@implementation DicomheroNGetCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    requestedSopClassUid:(NSString*)requestedSopClassUid
    requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
    attributeIdentifierList:(NSArray*)pAttributeIdentifierList
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        dicomhero::attributeIdentifierList_t identifierList;
        size_t identifiersCount = [pAttributeIdentifierList count];
        for(unsigned int scanIdentifiers(0); scanIdentifiers != identifiersCount; ++scanIdentifiers)
        {
            unsigned int group = ((DicomheroTagId*)[pAttributeIdentifierList objectAtIndex:scanIdentifiers]).groupId;
            unsigned int tag = ((DicomheroTagId*)[pAttributeIdentifierList objectAtIndex:scanIdentifiers]).tagId;
            identifierList.push_back((dicomhero::tagId_t)((group << 16) | tag));
        }

        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NGetCommand(
                    dicomhero::NSStringToString(abstractSyntax),
                    (std::uint16_t)messageID,
                    dicomhero::NSStringToString(requestedSopClassUid),
                    dicomhero::NSStringToString(requestedSopInstanceUid),
                    identifierList));
    }
    return self;

}

-(NSArray*) attributeList
{
    dicomhero::attributeIdentifierList_t identifiersList(((dicomhero::NGetCommand*)get_dicomhero_object_holder(DimseCommandBase))->getAttributeList());

    NSMutableArray* pIdentifiers = [[NSMutableArray alloc] init];

    for(const dicomhero::tagId_t tagId: identifiersList)
    {
        [pIdentifiers addObject: [[DicomheroTagId alloc] initWithGroup:(unsigned short)((std::uint32_t)tagId >> 16) tag:(unsigned short)((std::uint32_t)tagId & 0xffff)]];
    }

    return pIdentifiers;
}

@end


@implementation DicomheroNGetResponse

-(id)initWithCommand:(DicomheroNGetCommand*)pReceivedCommand
    responseCode:(DicomheroDimseStatusCode)responseCode
    attributeList:(DicomheroDataSet*)pAttributeList
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NGetResponse(
                                     *(dicomhero::NGetCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     (dicomhero::dimseStatusCode_t)responseCode,
                                     *get_other_dicomhero_object_holder(pAttributeList, DataSet)));
    }
    return self;

}

-(id)initWithcommand:(DicomheroNGetCommand*)pReceivedCommand
    responseCode:(DicomheroDimseStatusCode)responseCode
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NGetResponse(
                                     *(dicomhero::NGetCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     (dicomhero::dimseStatusCode_t)responseCode));
    }
    return self;
}

@end


@implementation DicomheroNSetCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    requestedSopClassUid:(NSString*)requestedSopClassUid
    requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
    modificationList:(DicomheroDataSet*)pModificationList
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NSetCommand(
                                     dicomhero::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     dicomhero::NSStringToString(requestedSopClassUid),
                                     dicomhero::NSStringToString(requestedSopInstanceUid),
                                     *get_other_dicomhero_object_holder(pModificationList, DataSet)));
    }
    return self;

}

@end


@implementation DicomheroNSetResponse

-(id)initWithCommand:(DicomheroNSetCommand*)pReceivedCommand
    modifiedAttributes:(NSArray*)pModifiedAttributes
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        dicomhero::attributeIdentifierList_t identifierList;
        size_t identifiersCount = [pModifiedAttributes count];
        for(unsigned int scanIdentifiers(0); scanIdentifiers != identifiersCount; ++scanIdentifiers)
        {
            unsigned int group = ((DicomheroTagId*)[pModifiedAttributes objectAtIndex:scanIdentifiers]).groupId;
            unsigned int tag = ((DicomheroTagId*)[pModifiedAttributes objectAtIndex:scanIdentifiers]).tagId;
            identifierList.push_back((dicomhero::tagId_t)((group << 16) | tag));
        }

        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NSetResponse(
                                     *(dicomhero::NSetCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     identifierList));
    }
    return self;
}

-(id)initWithcommand:(DicomheroNSetCommand*)pReceivedCommand
    responseCode:(DicomheroDimseStatusCode)responseCode
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NSetResponse(
                                     *(dicomhero::NSetCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     (dicomhero::dimseStatusCode_t)responseCode));
    }
    return self;
}

-(NSArray*) modifiedAttributes
{
    dicomhero::attributeIdentifierList_t identifiersList(((dicomhero::NSetResponse*)get_dicomhero_object_holder(DimseCommandBase))->getModifiedAttributes());

    NSMutableArray* pIdentifiers = [[NSMutableArray alloc] init];

    for(const dicomhero::tagId_t tagId: identifiersList)
    {
        [pIdentifiers addObject: [[DicomheroTagId alloc] initWithGroup:(unsigned short)((std::uint32_t)tagId >> 16) tag:(unsigned short)((std::uint32_t)tagId & 0xffff)]];
    }

    return pIdentifiers;

}

@end



@implementation DicomheroNActionCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    requestedSopClassUid:(NSString*)requestedSopClassUid
    requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
    actionID:(unsigned short)actionID
    actionInformation:(DicomheroDataSet*)pActionInformation
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NActionCommand(
                                     dicomhero::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     dicomhero::NSStringToString(requestedSopClassUid),
                                     dicomhero::NSStringToString(requestedSopInstanceUid),
                                     (std::uint16_t)actionID,
                                     *get_other_dicomhero_object_holder(pActionInformation, DataSet)));
    }
    return self;

}

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    requestedSopClassUid:(NSString*)requestedSopClassUid
    requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
    actionID:(unsigned short)actionID
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NActionCommand(
                                     dicomhero::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     dicomhero::NSStringToString(requestedSopClassUid),
                                     dicomhero::NSStringToString(requestedSopInstanceUid),
                                     (std::uint16_t)actionID));
    }
    return self;

}

-(unsigned short) actionID
{
    return (unsigned short)((dicomhero::NActionCommand*)get_dicomhero_object_holder(DimseCommandBase))->getActionID();
}

@end


@implementation DicomheroNActionResponse

-(id)initWithCommand:(DicomheroNActionCommand*)pReceivedCommand
    actionReply:(DicomheroDataSet*)pActionReply
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NActionResponse(
                                     *(dicomhero::NActionCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     *get_other_dicomhero_object_holder(pActionReply, DataSet)));
    }
    return self;

}

-(id)initWithcommand:(DicomheroNActionCommand*)pReceivedCommand
    responseCode:(DicomheroDimseStatusCode)responseCode
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NActionResponse(
                                     *(dicomhero::NActionCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     (dicomhero::dimseStatusCode_t)responseCode));
    }
    return self;

}

-(unsigned short) actionID
{
    return (unsigned short)((dicomhero::NActionResponse*)get_dicomhero_object_holder(DimseCommandBase))->getActionID();
}

@end


@implementation DicomheroNCreateCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    affectedSopClassUid:(NSString*)affectedSopClassUid
    affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
    attributeList:(DicomheroDataSet*)pAttributeList
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NCreateCommand(
                                     dicomhero::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     dicomhero::NSStringToString(affectedSopClassUid),
                                     dicomhero::NSStringToString(affectedSopInstanceUid),
                                     *get_other_dicomhero_object_holder(pAttributeList, DataSet)));
    }
    return self;
}

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    affectedSopClassUid:(NSString*)affectedSopClassUid
    affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NCreateCommand(
                                     dicomhero::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     dicomhero::NSStringToString(affectedSopClassUid),
                                     dicomhero::NSStringToString(affectedSopInstanceUid)));
    }
    return self;
}

@end


@implementation DicomheroNCreateResponse

-(id)initWithCommand:(DicomheroNCreateCommand*)pReceivedCommand
    attributeList:(DicomheroDataSet*)pAttributeList
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NCreateResponse(
                                     *(dicomhero::NCreateCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     *get_other_dicomhero_object_holder(pAttributeList, DataSet)));
    }
    return self;

}

-(id)initWithCommand:(DicomheroNCreateCommand*)pReceivedCommand
    affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
    attributeList:(DicomheroDataSet*)pAttributeList
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NCreateResponse(
                                     *(dicomhero::NCreateCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     dicomhero::NSStringToString(affectedSopInstanceUid),
                                     *get_other_dicomhero_object_holder(pAttributeList, DataSet)));
    }
    return self;

}

-(id)initWithCommand:(DicomheroNCreateCommand*)pReceivedCommand
    affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NCreateResponse(
                                     *(dicomhero::NCreateCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     dicomhero::NSStringToString(affectedSopInstanceUid)));
    }
    return self;

}

-(id)initWithcommand:(DicomheroNCreateCommand*)pReceivedCommand
    responseCode:(DicomheroDimseStatusCode)responseCode
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NCreateResponse(
                                     *(dicomhero::NCreateCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     (dicomhero::dimseStatusCode_t)responseCode));
    }
    return self;

}

@end


@implementation DicomheroNDeleteCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    requestedSopClassUid:(NSString*)requestedSopClassUid
    requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NDeleteCommand(
                                     dicomhero::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     dicomhero::NSStringToString(requestedSopClassUid),
                                     dicomhero::NSStringToString(requestedSopInstanceUid)));
    }
    return self;

}

@end


@implementation DicomheroNDeleteResponse

-(id)initWithcommand:(DicomheroNDeleteCommand*)pReceivedCommand
    responseCode:(DicomheroDimseStatusCode)responseCode
{
    reset_dicomhero_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseCommandBase, new dicomhero::NDeleteResponse(
                                     *(dicomhero::NDeleteCommand*)get_other_dicomhero_object_holder(pReceivedCommand, DimseCommandBase),
                                     (dicomhero::dimseStatusCode_t)responseCode));
    }
    return self;
}

@end


@implementation DicomheroDimseService

-(id)initWithAssociation:(DicomheroAssociationBase*)pAssociation
{
    reset_dicomhero_object_holder(DimseService);
    self = [super init];
    if(self)
    {
        set_dicomhero_object_holder(DimseService, new dicomhero::DimseService(*get_other_dicomhero_object_holder(pAssociation, AssociationBase)));
    }
    return self;
}

-(void)dealloc
{
    delete_dicomhero_object_holder(DimseService);
}

-(NSString*)getTransferSyntax:(NSString*)abstractSyntax error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return dicomhero::stringToNSString(get_dicomhero_object_holder(DimseService)->getTransferSyntax(dicomhero::NSStringToString(abstractSyntax)));

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(unsigned short)getNextCommandID
{
    return (unsigned short)get_dicomhero_object_holder(DimseService)->getNextCommandID();
}

-(DicomheroDimseCommand*)getCommand:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    std::unique_ptr<dicomhero::DimseCommand> pCommand(new dicomhero::DimseCommand(get_dicomhero_object_holder(DimseService)->getCommand()));

    switch(pCommand->getCommandType())
    {
    case dicomhero::dimseCommandType_t::cStore:
        return [[DicomheroCStoreCommand alloc] initWithDicomheroCommand:pCommand.release()];
    case dicomhero::dimseCommandType_t::cGet:
        return [[DicomheroCGetCommand alloc] initWithDicomheroCommand:pCommand.release()];
    case dicomhero::dimseCommandType_t::cMove:
        return [[DicomheroCMoveCommand alloc] initWithDicomheroCommand:pCommand.release()];
    case dicomhero::dimseCommandType_t::cFind:
        return [[DicomheroCFindCommand alloc] initWithDicomheroCommand:pCommand.release()];
    case dicomhero::dimseCommandType_t::cEcho:
        return [[DicomheroCEchoCommand alloc] initWithDicomheroCommand:pCommand.release()];
    case dicomhero::dimseCommandType_t::cCancel:
        return [[DicomheroCCancelCommand alloc] initWithDicomheroCommand:pCommand.release()];
    case dicomhero::dimseCommandType_t::nEventReport:
        return [[DicomheroNEventReportCommand alloc] initWithDicomheroCommand:pCommand.release()];
    case dicomhero::dimseCommandType_t::nGet:
        return [[DicomheroNGetCommand alloc] initWithDicomheroCommand:pCommand.release()];
    case dicomhero::dimseCommandType_t::nSet:
        return [[DicomheroNSetCommand alloc] initWithDicomheroCommand:pCommand.release()];
    case dicomhero::dimseCommandType_t::nAction:
        return [[DicomheroNActionCommand alloc] initWithDicomheroCommand:pCommand.release()];
    case dicomhero::dimseCommandType_t::nCreate:
        return [[DicomheroNCreateCommand alloc] initWithDicomheroCommand:pCommand.release()];
    case dicomhero::dimseCommandType_t::nDelete:
        return [[DicomheroNDeleteCommand alloc] initWithDicomheroCommand:pCommand.release()];
    default:
        break;
    }

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(void)sendCommandOrResponse:(DicomheroDimseCommandBase*)pCommand error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    get_dicomhero_object_holder(DimseService)->sendCommandOrResponse(*get_other_dicomhero_object_holder(pCommand, DimseCommandBase));

    OBJC_DICOMHERO_FUNCTION_END();
}

-(DicomheroCStoreResponse*)getCStoreResponse:(DicomheroCStoreCommand*)pCommand error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroCStoreResponse alloc] initWithDicomheroCommand:
            new dicomhero::CStoreResponse(get_dicomhero_object_holder(DimseService)->getCStoreResponse(*(dicomhero::CStoreCommand*)get_other_dicomhero_object_holder(pCommand, DimseCommandBase)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroCGetResponse*)getCGetResponse:(DicomheroCGetCommand*)pCommand error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroCGetResponse alloc] initWithDicomheroCommand:
            new dicomhero::CGetResponse(get_dicomhero_object_holder(DimseService)->getCGetResponse(*(dicomhero::CGetCommand*)get_other_dicomhero_object_holder(pCommand, DimseCommandBase)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroCFindResponse*)getCFindResponse:(DicomheroCFindCommand*)pCommand error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroCFindResponse alloc] initWithDicomheroCommand:
            new dicomhero::CFindResponse(get_dicomhero_object_holder(DimseService)->getCFindResponse(*(dicomhero::CFindCommand*)get_other_dicomhero_object_holder(pCommand, DimseCommandBase)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroCMoveResponse*)getCMoveResponse:(DicomheroCMoveCommand*)pCommand error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroCMoveResponse alloc] initWithDicomheroCommand:
            new dicomhero::CMoveResponse(get_dicomhero_object_holder(DimseService)->getCMoveResponse(*(dicomhero::CMoveCommand*)get_other_dicomhero_object_holder(pCommand, DimseCommandBase)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroCEchoResponse*)getCEchoResponse:(DicomheroCEchoCommand*)pCommand error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroCEchoResponse alloc] initWithDicomheroCommand:
            new dicomhero::CEchoResponse(get_dicomhero_object_holder(DimseService)->getCEchoResponse(*(dicomhero::CEchoCommand*)get_other_dicomhero_object_holder(pCommand, DimseCommandBase)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroNEventReportResponse*)getNEventReportResponse:(DicomheroNEventReportCommand*)pCommand error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroNEventReportResponse alloc] initWithDicomheroCommand:
            new dicomhero::NEventReportResponse(get_dicomhero_object_holder(DimseService)->getNEventReportResponse(*(dicomhero::NEventReportCommand*)get_other_dicomhero_object_holder(pCommand, DimseCommandBase)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroNGetResponse*)getNGetResponse:(DicomheroNGetCommand*)pCommand error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroNGetResponse alloc] initWithDicomheroCommand:
            new dicomhero::NGetResponse(get_dicomhero_object_holder(DimseService)->getNGetResponse(*(dicomhero::NGetCommand*)get_other_dicomhero_object_holder(pCommand, DimseCommandBase)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroNSetResponse*)getNSetResponse:(DicomheroNSetCommand*)pCommand error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroNSetResponse alloc] initWithDicomheroCommand:
            new dicomhero::NSetResponse(get_dicomhero_object_holder(DimseService)->getNSetResponse(*(dicomhero::NSetCommand*)get_other_dicomhero_object_holder(pCommand, DimseCommandBase)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroNActionResponse*)getNActionResponse:(DicomheroNActionCommand*)pCommand error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroNActionResponse alloc] initWithDicomheroCommand:
            new dicomhero::NActionResponse(get_dicomhero_object_holder(DimseService)->getNActionResponse(*(dicomhero::NActionCommand*)get_other_dicomhero_object_holder(pCommand, DimseCommandBase)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroNCreateResponse*)getNCreateResponse:(DicomheroNCreateCommand*)pCommand error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroNCreateResponse alloc] initWithDicomheroCommand:
            new dicomhero::NCreateResponse(get_dicomhero_object_holder(DimseService)->getNCreateResponse(*(dicomhero::NCreateCommand*)get_other_dicomhero_object_holder(pCommand, DimseCommandBase)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

-(DicomheroNDeleteResponse*)getNDeleteResponse:(DicomheroNDeleteCommand*)pCommand error:(NSError**)pError
{
    OBJC_DICOMHERO_FUNCTION_START();

    return [[DicomheroNDeleteResponse alloc] initWithDicomheroCommand:
            new dicomhero::NDeleteResponse(get_dicomhero_object_holder(DimseService)->getNDeleteResponse(*(dicomhero::NDeleteCommand*)get_other_dicomhero_object_holder(pCommand, DimseCommandBase)))];

    OBJC_DICOMHERO_FUNCTION_END_RETURN(nil);
}

@end

