/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "../include/imebraobjc/imebra_dimse.h"
#include <imebra/dimse.h>
#include <imebra/dataSet.h>
#include "imebra_implementation_macros.h"
#include "imebra_nserror.h"
#include "imebra_strings.h"

#import "../include/imebraobjc/imebra_dataset.h"
#import "../include/imebraobjc/imebra_tagId.h"
#import "../include/imebraobjc/imebra_acse.h"

@implementation ImebraDimseCommandBase

-(id)initWithImebraCommand:define_imebra_parameter(DimseCommandBase)
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, get_imebra_parameter(DimseCommandBase));
    }
    else
    {
        get_imebra_parameter(DimseCommandBase);
    }
    return self;

}


-(void)dealloc
{
    delete_imebra_object_holder(DimseCommandBase);
}

-(ImebraDataSet*)getCommandDataSet:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraDataSet alloc] initWithImebraDataSet:new imebra::DataSet(get_imebra_object_holder(DimseCommandBase)->getCommandDataSet())];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraDataSet*)getPayloadDataSet:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraDataSet alloc] initWithImebraDataSet:new imebra::DataSet(get_imebra_object_holder(DimseCommandBase)->getPayloadDataSet())];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(NSString*)getAbstractSyntax
{
    return imebra::stringToNSString(get_imebra_object_holder(DimseCommandBase)->getAbstractSyntax());
}

-(NSString*)getAffectedSopInstanceUid:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return imebra::stringToNSString(get_imebra_object_holder(DimseCommandBase)->getAffectedSopInstanceUid());

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(NSString*)getAffectedSopClassUid:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return imebra::stringToNSString(get_imebra_object_holder(DimseCommandBase)->getAffectedSopClassUid());

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(NSString*)getRequestedSopInstanceUid:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return imebra::stringToNSString(get_imebra_object_holder(DimseCommandBase)->getRequestedSopInstanceUid());

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(NSString*)getRequestedSopClassUid:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return imebra::stringToNSString(get_imebra_object_holder(DimseCommandBase)->getRequestedSopClassUid());

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}


@end


@implementation ImebraDimseCommand

-(unsigned short) ID
{
    return (unsigned short)((imebra::DimseCommand*)get_imebra_object_holder(DimseCommandBase))->getID();
}

-(ImebraDimseCommandType) commandType
{
    return (ImebraDimseCommandType)((imebra::DimseCommand*)get_imebra_object_holder(DimseCommandBase))->getCommandType();
}

@end


@implementation ImebraDimseResponse

-(ImebraDimseStatus) status
{
    return (ImebraDimseStatus)((imebra::DimseResponse*)get_imebra_object_holder(DimseCommandBase))->getStatus();
}

-(unsigned short) statusCode
{
    return (unsigned short)((imebra::DimseResponse*)get_imebra_object_holder(DimseCommandBase))->getStatusCode();
}

@end


@implementation ImebraCPartialResponse

-(unsigned int)getRemainingSubOperations:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return (unsigned int)((imebra::CPartialResponse*)get_imebra_object_holder(DimseCommandBase))->getRemainingSubOperations();

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned int)getCompletedSubOperations:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return (unsigned int)((imebra::CPartialResponse*)get_imebra_object_holder(DimseCommandBase))->getCompletedSubOperations();

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

-(unsigned int)getFailedSubOperations:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return (unsigned int)((imebra::CPartialResponse*)get_imebra_object_holder(DimseCommandBase))->getFailedSubOperations();

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}


-(unsigned int)getWarningSubOperations:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return (unsigned int)((imebra::CPartialResponse*)get_imebra_object_holder(DimseCommandBase))->getWarningSubOperations();

    OBJC_IMEBRA_FUNCTION_END_RETURN(0);
}

@end


@implementation ImebraCStoreCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    priority:(ImebraDimseCommandPriority)priority
    affectedSopClassUid:(NSString*)affectedSopClassUid
    affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
    originatorAET:(NSString*)originatorAET
    originatorMessageID:(unsigned short)originatorMessageID
    payload:(ImebraDataSet*)pPayload
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::CStoreCommand(
                                     imebra::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     (imebra::dimseCommandPriority_t)priority,
                                     imebra::NSStringToString(affectedSopClassUid),
                                     imebra::NSStringToString(affectedSopInstanceUid),
                                     imebra::NSStringToString(originatorAET),
                                     (std::uint16_t)originatorMessageID,
                                     *get_other_imebra_object_holder(pPayload, DataSet)));
    }
    return self;

}


-(NSString*) originatorAET
{
    return imebra::stringToNSString(((imebra::CStoreCommand*)get_imebra_object_holder(DimseCommandBase))->getOriginatorAET());
}

-(unsigned short) originatorMessageID
{
    return (unsigned short)((imebra::CStoreCommand*)get_imebra_object_holder(DimseCommandBase))->getOriginatorMessageID();
}

@end


@implementation ImebraCStoreResponse

-(id)initWithcommand:(ImebraCStoreCommand*) pCommand
    responseCode:(ImebraDimseStatusCode)responseCode
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::CStoreResponse(
                                     *(imebra::CStoreCommand*)get_other_imebra_object_holder(pCommand, DimseCommandBase),
                                     (imebra::dimseStatusCode_t)responseCode));
    }
    return self;

}

@end


@implementation ImebraCGetCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    priority:(ImebraDimseCommandPriority)priority
    affectedSopClassUid:(NSString*)affectedSopClassUid
    identifier:(ImebraDataSet*)pIdentifier
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::CGetCommand(
                                     imebra::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     (imebra::dimseCommandPriority_t)priority,
                                     imebra::NSStringToString(affectedSopClassUid),
                                     *get_other_imebra_object_holder(pIdentifier, DataSet)));
    }
    return self;
}

@end


@implementation ImebraCGetResponse

-(id)initWithCommand:(ImebraCGetCommand*)pReceivedCommand
    responseCode:(ImebraDimseStatusCode)responseCode
    remainingSubOperations:(unsigned int)remainingSubOperations
    completedSubOperations:(unsigned int)completedSubOperations
    failedSubOperations:(unsigned int)failedSubOperations
    warningSubOperations:(unsigned int)warningSubOperations
    identifier:(ImebraDataSet*)pIdentifier
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::CGetResponse(
                                     *(imebra::CGetCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     (imebra::dimseStatusCode_t)responseCode,
                                     (std::uint32_t)remainingSubOperations,
                                     (std::uint32_t)completedSubOperations,
                                     (std::uint32_t)failedSubOperations,
                                     (std::uint32_t)warningSubOperations,
                                     *get_other_imebra_object_holder(pIdentifier, DataSet)));
    }
    return self;
}

-(id)initWithcommand:(ImebraCGetCommand*)pReceivedCommand
    responseCode:(ImebraDimseStatusCode)responseCode
    remainingSubOperations:(unsigned int)remainingSubOperations
    completedSubOperations:(unsigned int)completedSubOperations
    failedSubOperations:(unsigned int)failedSubOperations
    warningSubOperations:(unsigned int)warningSubOperations
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::CGetResponse(
                                     *(imebra::CGetCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     (imebra::dimseStatusCode_t)responseCode,
                                     (std::uint32_t)remainingSubOperations,
                                     (std::uint32_t)completedSubOperations,
                                     (std::uint32_t)failedSubOperations,
                                     (std::uint32_t)warningSubOperations));
    }
    return self;
}


@end


@implementation ImebraCFindCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    priority:(ImebraDimseCommandPriority)priority
    affectedSopClassUid:(NSString*)affectedSopClassUid
    identifier:(ImebraDataSet*)pIdentifier
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::CFindCommand(
                                     imebra::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     (imebra::dimseCommandPriority_t)priority,
                                     imebra::NSStringToString(affectedSopClassUid),
                                     *get_other_imebra_object_holder(pIdentifier, DataSet)));
    }
    return self;
}

@end


@implementation ImebraCFindResponse

-(id)initWithCommand:(ImebraCFindCommand*)pReceivedCommand
    identifier:(ImebraDataSet*)pIdentifier
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::CFindResponse(
                                     *(imebra::CFindCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     *get_other_imebra_object_holder(pIdentifier, DataSet)));
    }
    return self;
}

-(id)initWithcommand:(ImebraCFindCommand*)pReceivedCommand
    responseCode:(ImebraDimseStatusCode)responseCode
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::CFindResponse(
                                     *(imebra::CFindCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     (imebra::dimseStatusCode_t)responseCode));
    }
    return self;
}

@end


@implementation ImebraCMoveCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    priority:(ImebraDimseCommandPriority)priority
    affectedSopClassUid:(NSString*)affectedSopClassUid
    destinationAET:(NSString*)destinationAET
    identifier:(ImebraDataSet*)pIdentifier
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::CMoveCommand(
                                     imebra::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     (imebra::dimseCommandPriority_t)priority,
                                     imebra::NSStringToString(affectedSopClassUid),
                                     imebra::NSStringToString(destinationAET),
                                     *get_other_imebra_object_holder(pIdentifier, DataSet)));
    }
    return self;
}

-(NSString*)getDestinationAET:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return imebra::stringToNSString(((imebra::CMoveCommand*)get_imebra_object_holder(DimseCommandBase))->getDestinationAET());

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

@end


@implementation ImebraCMoveResponse

-(id)initWithCommand:(ImebraCMoveCommand*)pReceivedCommand
    responseCode:(ImebraDimseStatusCode)responseCode
    remainingSubOperations:(unsigned int)remainingSubOperations
    completedSubOperations:(unsigned int)completedSubOperations
    failedSubOperations:(unsigned int)failedSubOperations
    warningSubOperations:(unsigned int)warningSubOperations
    identifier:(ImebraDataSet*)pIdentifier
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::CMoveResponse(
                                     *(imebra::CMoveCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     (imebra::dimseStatusCode_t)responseCode,
                                     (std::uint32_t)remainingSubOperations,
                                     (std::uint32_t)completedSubOperations,
                                     (std::uint32_t)failedSubOperations,
                                     (std::uint32_t)warningSubOperations,
                                     *get_other_imebra_object_holder(pIdentifier, DataSet)));
    }
    return self;

}

-(id)initWithcommand:(ImebraCMoveCommand*)pReceivedCommand
    responseCode:(ImebraDimseStatusCode)responseCode
    remainingSubOperations:(unsigned int)remainingSubOperations
    completedSubOperations:(unsigned int)completedSubOperations
    failedSubOperations:(unsigned int)failedSubOperations
    warningSubOperations:(unsigned int)warningSubOperations
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::CMoveResponse(
                                     *(imebra::CMoveCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     (imebra::dimseStatusCode_t)responseCode,
                                     (std::uint32_t)remainingSubOperations,
                                     (std::uint32_t)completedSubOperations,
                                     (std::uint32_t)failedSubOperations,
                                     (std::uint32_t)warningSubOperations));
    }
    return self;

}


@end


@implementation ImebraCEchoCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    priority:(ImebraDimseCommandPriority)priority
    affectedSopClassUid:(NSString*)affectedSopClassUid
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::CEchoCommand(
                                     imebra::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     (imebra::dimseCommandPriority_t)priority,
                                     imebra::NSStringToString(affectedSopClassUid)));
    }
    return self;

}

@end


@implementation ImebraCEchoResponse

-(id)initWithcommand:(ImebraCEchoCommand*)pReceivedCommand
    responseCode:(ImebraDimseStatusCode)responseCode
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::CEchoResponse(
                                     *(imebra::CEchoCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     (imebra::dimseStatusCode_t)responseCode));
    }
    return self;

}

@end


@implementation ImebraCCancelCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    priority:(ImebraDimseCommandPriority)priority
    cancelMessageID:(unsigned short)cancelMessageID
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::CCancelCommand(
                                     imebra::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     (imebra::dimseCommandPriority_t)priority,
                                     (std::uint16_t)cancelMessageID));
    }
    return self;
}

-(unsigned short)cancelMessageID
{
    return (unsigned short)((imebra::CCancelCommand*)get_imebra_object_holder(DimseCommandBase))->getCancelMessageID();
}

@end


@implementation ImebraNEventReportCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    affectedSopClassUid:(NSString*)affectedSopClassUid
    affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
    eventID:(unsigned short)eventID
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NEventReportCommand(
                                     imebra::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     imebra::NSStringToString(affectedSopClassUid),
                                     imebra::NSStringToString(affectedSopInstanceUid),
                                     (std::uint16_t)eventID));
    }
    return self;
}

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    affectedSopClassUid:(NSString*)affectedSopClassUid
    affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
    eventID:(unsigned short)eventID
    eventInformation:(ImebraDataSet*)pEventInformation
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NEventReportCommand(
                                     imebra::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     imebra::NSStringToString(affectedSopClassUid),
                                     imebra::NSStringToString(affectedSopInstanceUid),
                                     (std::uint16_t)eventID,
                                     *get_other_imebra_object_holder(pEventInformation, DataSet)));
    }
    return self;
}

-(unsigned short) eventID
{
    return (unsigned short)((imebra::NEventReportCommand*)get_imebra_object_holder(DimseCommandBase))->getEventID();
}

@end


@implementation ImebraNEventReportResponse

-(id)initWithCommand:(ImebraNEventReportCommand*)pReceivedCommand
    eventReply:(ImebraDataSet*)pEventReply
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NEventReportResponse(
                                     *(imebra::NEventReportCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     *get_other_imebra_object_holder(pEventReply, DataSet)));
    }
    return self;

}

-(id)initWithcommand:(ImebraNEventReportCommand*)pReceivedCommand
    responseCode:(ImebraDimseStatusCode)responseCode
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NEventReportResponse(
                                     *(imebra::NEventReportCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     (imebra::dimseStatusCode_t)responseCode));
    }
    return self;

}

-(unsigned short) eventID
{
    return (unsigned short)((imebra::NEventReportResponse*)get_imebra_object_holder(DimseCommandBase))->getEventID();
}

@end


@implementation ImebraNGetCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    requestedSopClassUid:(NSString*)requestedSopClassUid
    requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
    attributeIdentifierList:(NSArray*)pAttributeIdentifierList
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        imebra::attributeIdentifierList_t identifierList;
        size_t identifiersCount = [pAttributeIdentifierList count];
        for(unsigned int scanIdentifiers(0); scanIdentifiers != identifiersCount; ++scanIdentifiers)
        {
            unsigned int group = ((ImebraTagId*)[pAttributeIdentifierList objectAtIndex:scanIdentifiers]).groupId;
            unsigned int tag = ((ImebraTagId*)[pAttributeIdentifierList objectAtIndex:scanIdentifiers]).tagId;
            identifierList.push_back((imebra::tagId_t)((group << 16) | tag));
        }

        set_imebra_object_holder(DimseCommandBase, new imebra::NGetCommand(
                    imebra::NSStringToString(abstractSyntax),
                    (std::uint16_t)messageID,
                    imebra::NSStringToString(requestedSopClassUid),
                    imebra::NSStringToString(requestedSopInstanceUid),
                    identifierList));
    }
    return self;

}

-(NSArray*) attributeList
{
    imebra::attributeIdentifierList_t identifiersList(((imebra::NGetCommand*)get_imebra_object_holder(DimseCommandBase))->getAttributeList());

    NSMutableArray* pIdentifiers = [[NSMutableArray alloc] init];

    for(const imebra::tagId_t tagId: identifiersList)
    {
        [pIdentifiers addObject: [[ImebraTagId alloc] initWithGroup:(unsigned short)((std::uint32_t)tagId >> 16) tag:(unsigned short)((std::uint32_t)tagId & 0xffff)]];
    }

    return pIdentifiers;
}

@end


@implementation ImebraNGetResponse

-(id)initWithCommand:(ImebraNGetCommand*)pReceivedCommand
    responseCode:(ImebraDimseStatusCode)responseCode
    attributeList:(ImebraDataSet*)pAttributeList
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NGetResponse(
                                     *(imebra::NGetCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     (imebra::dimseStatusCode_t)responseCode,
                                     *get_other_imebra_object_holder(pAttributeList, DataSet)));
    }
    return self;

}

-(id)initWithcommand:(ImebraNGetCommand*)pReceivedCommand
    responseCode:(ImebraDimseStatusCode)responseCode
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NGetResponse(
                                     *(imebra::NGetCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     (imebra::dimseStatusCode_t)responseCode));
    }
    return self;
}

@end


@implementation ImebraNSetCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    requestedSopClassUid:(NSString*)requestedSopClassUid
    requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
    modificationList:(ImebraDataSet*)pModificationList
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NSetCommand(
                                     imebra::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     imebra::NSStringToString(requestedSopClassUid),
                                     imebra::NSStringToString(requestedSopInstanceUid),
                                     *get_other_imebra_object_holder(pModificationList, DataSet)));
    }
    return self;

}

@end


@implementation ImebraNSetResponse

-(id)initWithCommand:(ImebraNSetCommand*)pReceivedCommand
    modifiedAttributes:(NSArray*)pModifiedAttributes
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        imebra::attributeIdentifierList_t identifierList;
        size_t identifiersCount = [pModifiedAttributes count];
        for(unsigned int scanIdentifiers(0); scanIdentifiers != identifiersCount; ++scanIdentifiers)
        {
            unsigned int group = ((ImebraTagId*)[pModifiedAttributes objectAtIndex:scanIdentifiers]).groupId;
            unsigned int tag = ((ImebraTagId*)[pModifiedAttributes objectAtIndex:scanIdentifiers]).tagId;
            identifierList.push_back((imebra::tagId_t)((group << 16) | tag));
        }

        set_imebra_object_holder(DimseCommandBase, new imebra::NSetResponse(
                                     *(imebra::NSetCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     identifierList));
    }
    return self;
}

-(id)initWithcommand:(ImebraNSetCommand*)pReceivedCommand
    responseCode:(ImebraDimseStatusCode)responseCode
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NSetResponse(
                                     *(imebra::NSetCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     (imebra::dimseStatusCode_t)responseCode));
    }
    return self;
}

-(NSArray*) modifiedAttributes
{
    imebra::attributeIdentifierList_t identifiersList(((imebra::NSetResponse*)get_imebra_object_holder(DimseCommandBase))->getModifiedAttributes());

    NSMutableArray* pIdentifiers = [[NSMutableArray alloc] init];

    for(const imebra::tagId_t tagId: identifiersList)
    {
        [pIdentifiers addObject: [[ImebraTagId alloc] initWithGroup:(unsigned short)((std::uint32_t)tagId >> 16) tag:(unsigned short)((std::uint32_t)tagId & 0xffff)]];
    }

    return pIdentifiers;

}

@end



@implementation ImebraNActionCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    requestedSopClassUid:(NSString*)requestedSopClassUid
    requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
    actionID:(unsigned short)actionID
    actionInformation:(ImebraDataSet*)pActionInformation
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NActionCommand(
                                     imebra::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     imebra::NSStringToString(requestedSopClassUid),
                                     imebra::NSStringToString(requestedSopInstanceUid),
                                     (std::uint16_t)actionID,
                                     *get_other_imebra_object_holder(pActionInformation, DataSet)));
    }
    return self;

}

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    requestedSopClassUid:(NSString*)requestedSopClassUid
    requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
    actionID:(unsigned short)actionID
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NActionCommand(
                                     imebra::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     imebra::NSStringToString(requestedSopClassUid),
                                     imebra::NSStringToString(requestedSopInstanceUid),
                                     (std::uint16_t)actionID));
    }
    return self;

}

-(unsigned short) actionID
{
    return (unsigned short)((imebra::NActionCommand*)get_imebra_object_holder(DimseCommandBase))->getActionID();
}

@end


@implementation ImebraNActionResponse

-(id)initWithCommand:(ImebraNActionCommand*)pReceivedCommand
    actionReply:(ImebraDataSet*)pActionReply
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NActionResponse(
                                     *(imebra::NActionCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     *get_other_imebra_object_holder(pActionReply, DataSet)));
    }
    return self;

}

-(id)initWithcommand:(ImebraNActionCommand*)pReceivedCommand
    responseCode:(ImebraDimseStatusCode)responseCode
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NActionResponse(
                                     *(imebra::NActionCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     (imebra::dimseStatusCode_t)responseCode));
    }
    return self;

}

-(unsigned short) actionID
{
    return (unsigned short)((imebra::NActionResponse*)get_imebra_object_holder(DimseCommandBase))->getActionID();
}

@end


@implementation ImebraNCreateCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    affectedSopClassUid:(NSString*)affectedSopClassUid
    affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
    attributeList:(ImebraDataSet*)pAttributeList
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NCreateCommand(
                                     imebra::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     imebra::NSStringToString(affectedSopClassUid),
                                     imebra::NSStringToString(affectedSopInstanceUid),
                                     *get_other_imebra_object_holder(pAttributeList, DataSet)));
    }
    return self;
}

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    affectedSopClassUid:(NSString*)affectedSopClassUid
    affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NCreateCommand(
                                     imebra::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     imebra::NSStringToString(affectedSopClassUid),
                                     imebra::NSStringToString(affectedSopInstanceUid)));
    }
    return self;
}

@end


@implementation ImebraNCreateResponse

-(id)initWithCommand:(ImebraNCreateCommand*)pReceivedCommand
    attributeList:(ImebraDataSet*)pAttributeList
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NCreateResponse(
                                     *(imebra::NCreateCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     *get_other_imebra_object_holder(pAttributeList, DataSet)));
    }
    return self;

}

-(id)initWithCommand:(ImebraNCreateCommand*)pReceivedCommand
    affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
    attributeList:(ImebraDataSet*)pAttributeList
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NCreateResponse(
                                     *(imebra::NCreateCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     imebra::NSStringToString(affectedSopInstanceUid),
                                     *get_other_imebra_object_holder(pAttributeList, DataSet)));
    }
    return self;

}

-(id)initWithCommand:(ImebraNCreateCommand*)pReceivedCommand
    affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NCreateResponse(
                                     *(imebra::NCreateCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     imebra::NSStringToString(affectedSopInstanceUid)));
    }
    return self;

}

-(id)initWithcommand:(ImebraNCreateCommand*)pReceivedCommand
    responseCode:(ImebraDimseStatusCode)responseCode
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NCreateResponse(
                                     *(imebra::NCreateCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     (imebra::dimseStatusCode_t)responseCode));
    }
    return self;

}

@end


@implementation ImebraNDeleteCommand

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
    messageID:(unsigned short)messageID
    requestedSopClassUid:(NSString*)requestedSopClassUid
    requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NDeleteCommand(
                                     imebra::NSStringToString(abstractSyntax),
                                     (std::uint16_t)messageID,
                                     imebra::NSStringToString(requestedSopClassUid),
                                     imebra::NSStringToString(requestedSopInstanceUid)));
    }
    return self;

}

@end


@implementation ImebraNDeleteResponse

-(id)initWithcommand:(ImebraNDeleteCommand*)pReceivedCommand
    responseCode:(ImebraDimseStatusCode)responseCode
{
    reset_imebra_object_holder(DimseCommandBase);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseCommandBase, new imebra::NDeleteResponse(
                                     *(imebra::NDeleteCommand*)get_other_imebra_object_holder(pReceivedCommand, DimseCommandBase),
                                     (imebra::dimseStatusCode_t)responseCode));
    }
    return self;
}

@end


@implementation ImebraDimseService

-(id)initWithAssociation:(ImebraAssociationBase*)pAssociation
{
    reset_imebra_object_holder(DimseService);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(DimseService, new imebra::DimseService(*get_other_imebra_object_holder(pAssociation, AssociationBase)));
    }
    return self;
}

-(void)dealloc
{
    delete_imebra_object_holder(DimseService);
}

-(NSString*)getTransferSyntax:(NSString*)abstractSyntax error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return imebra::stringToNSString(get_imebra_object_holder(DimseService)->getTransferSyntax(imebra::NSStringToString(abstractSyntax)));

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(unsigned short)getNextCommandID
{
    return (unsigned short)get_imebra_object_holder(DimseService)->getNextCommandID();
}

-(ImebraDimseCommand*)getCommand:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    std::unique_ptr<imebra::DimseCommand> pCommand(new imebra::DimseCommand(get_imebra_object_holder(DimseService)->getCommand()));

    switch(pCommand->getCommandType())
    {
    case imebra::dimseCommandType_t::cStore:
        return [[ImebraCStoreCommand alloc] initWithImebraCommand:pCommand.release()];
    case imebra::dimseCommandType_t::cGet:
        return [[ImebraCGetCommand alloc] initWithImebraCommand:pCommand.release()];
    case imebra::dimseCommandType_t::cMove:
        return [[ImebraCMoveCommand alloc] initWithImebraCommand:pCommand.release()];
    case imebra::dimseCommandType_t::cFind:
        return [[ImebraCFindCommand alloc] initWithImebraCommand:pCommand.release()];
    case imebra::dimseCommandType_t::cEcho:
        return [[ImebraCEchoCommand alloc] initWithImebraCommand:pCommand.release()];
    case imebra::dimseCommandType_t::cCancel:
        return [[ImebraCCancelCommand alloc] initWithImebraCommand:pCommand.release()];
    case imebra::dimseCommandType_t::nEventReport:
        return [[ImebraNEventReportCommand alloc] initWithImebraCommand:pCommand.release()];
    case imebra::dimseCommandType_t::nGet:
        return [[ImebraNGetCommand alloc] initWithImebraCommand:pCommand.release()];
    case imebra::dimseCommandType_t::nSet:
        return [[ImebraNSetCommand alloc] initWithImebraCommand:pCommand.release()];
    case imebra::dimseCommandType_t::nAction:
        return [[ImebraNActionCommand alloc] initWithImebraCommand:pCommand.release()];
    case imebra::dimseCommandType_t::nCreate:
        return [[ImebraNCreateCommand alloc] initWithImebraCommand:pCommand.release()];
    case imebra::dimseCommandType_t::nDelete:
        return [[ImebraNDeleteCommand alloc] initWithImebraCommand:pCommand.release()];
    default:
        break;
    }

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(void)sendCommandOrResponse:(ImebraDimseCommandBase*)pCommand error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    get_imebra_object_holder(DimseService)->sendCommandOrResponse(*get_other_imebra_object_holder(pCommand, DimseCommandBase));

    OBJC_IMEBRA_FUNCTION_END();
}

-(ImebraCStoreResponse*)getCStoreResponse:(ImebraCStoreCommand*)pCommand error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraCStoreResponse alloc] initWithImebraCommand:
            new imebra::CStoreResponse(get_imebra_object_holder(DimseService)->getCStoreResponse(*(imebra::CStoreCommand*)get_other_imebra_object_holder(pCommand, DimseCommandBase)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraCGetResponse*)getCGetResponse:(ImebraCGetCommand*)pCommand error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraCGetResponse alloc] initWithImebraCommand:
            new imebra::CGetResponse(get_imebra_object_holder(DimseService)->getCGetResponse(*(imebra::CGetCommand*)get_other_imebra_object_holder(pCommand, DimseCommandBase)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraCFindResponse*)getCFindResponse:(ImebraCFindCommand*)pCommand error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraCFindResponse alloc] initWithImebraCommand:
            new imebra::CFindResponse(get_imebra_object_holder(DimseService)->getCFindResponse(*(imebra::CFindCommand*)get_other_imebra_object_holder(pCommand, DimseCommandBase)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraCMoveResponse*)getCMoveResponse:(ImebraCMoveCommand*)pCommand error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraCMoveResponse alloc] initWithImebraCommand:
            new imebra::CMoveResponse(get_imebra_object_holder(DimseService)->getCMoveResponse(*(imebra::CMoveCommand*)get_other_imebra_object_holder(pCommand, DimseCommandBase)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraCEchoResponse*)getCEchoResponse:(ImebraCEchoCommand*)pCommand error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraCEchoResponse alloc] initWithImebraCommand:
            new imebra::CEchoResponse(get_imebra_object_holder(DimseService)->getCEchoResponse(*(imebra::CEchoCommand*)get_other_imebra_object_holder(pCommand, DimseCommandBase)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraNEventReportResponse*)getNEventReportResponse:(ImebraNEventReportCommand*)pCommand error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraNEventReportResponse alloc] initWithImebraCommand:
            new imebra::NEventReportResponse(get_imebra_object_holder(DimseService)->getNEventReportResponse(*(imebra::NEventReportCommand*)get_other_imebra_object_holder(pCommand, DimseCommandBase)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraNGetResponse*)getNGetResponse:(ImebraNGetCommand*)pCommand error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraNGetResponse alloc] initWithImebraCommand:
            new imebra::NGetResponse(get_imebra_object_holder(DimseService)->getNGetResponse(*(imebra::NGetCommand*)get_other_imebra_object_holder(pCommand, DimseCommandBase)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraNSetResponse*)getNSetResponse:(ImebraNSetCommand*)pCommand error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraNSetResponse alloc] initWithImebraCommand:
            new imebra::NSetResponse(get_imebra_object_holder(DimseService)->getNSetResponse(*(imebra::NSetCommand*)get_other_imebra_object_holder(pCommand, DimseCommandBase)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraNActionResponse*)getNActionResponse:(ImebraNActionCommand*)pCommand error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraNActionResponse alloc] initWithImebraCommand:
            new imebra::NActionResponse(get_imebra_object_holder(DimseService)->getNActionResponse(*(imebra::NActionCommand*)get_other_imebra_object_holder(pCommand, DimseCommandBase)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraNCreateResponse*)getNCreateResponse:(ImebraNCreateCommand*)pCommand error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraNCreateResponse alloc] initWithImebraCommand:
            new imebra::NCreateResponse(get_imebra_object_holder(DimseService)->getNCreateResponse(*(imebra::NCreateCommand*)get_other_imebra_object_holder(pCommand, DimseCommandBase)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraNDeleteResponse*)getNDeleteResponse:(ImebraNDeleteCommand*)pCommand error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraNDeleteResponse alloc] initWithImebraCommand:
            new imebra::NDeleteResponse(get_imebra_object_holder(DimseService)->getNDeleteResponse(*(imebra::NDeleteCommand*)get_other_imebra_object_holder(pCommand, DimseCommandBase)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

@end

