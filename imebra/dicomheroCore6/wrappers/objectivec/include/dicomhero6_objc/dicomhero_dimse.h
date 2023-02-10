/*
Copyright 2005 - 2021 by Paolo Brandoli/Binarno s.p.

DICOMHero/Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for DICOMHero/Imebra from the DICOMHero’s website (https://dicomhero.com).
*/

#if !defined(dicomheroObjcDimse__INCLUDED_)
#define dicomheroObjcDimse__INCLUDED_

#import <Foundation/Foundation.h>
#import <Foundation/NSArray.h>
#import <Foundation/NSString.h>
#include "dicomhero_macros.h"

/// \enum DicomheroDimseCommandType
/// \brief DIMSE command types.
///
///////////////////////////////////////////////////////////////////////////////
typedef NS_ENUM(unsigned short, DicomheroDimseCommandType)
{
    DicomheroDimseCommandTypeCStore = 0x1,         ///< C-STORE
    DicomheroDimseCommandTypeCGet = 0x10,          ///< C-GET
    DicomheroDimseCommandTypeCFind = 0x20,         ///< C-FIND
    DicomheroDimseCommandTypeCMove = 0x21,         ///< C-MOVE
    DicomheroDimseCommandTypeCCancel = 0xfff,      ///< C-CANCEL
    DicomheroDimseCommandTypeCEcho = 0x30,         ///< C-ECHO
    DicomheroDimseCommandTypeNEventReport = 0x100, ///< N-EVENT_REPORT
    DicomheroDimseCommandTypeNGet = 0x110,         ///< N-GET
    DicomheroDimseCommandTypeNSet = 0x120,         ///< N-SET
    DicomheroDimseCommandTypeNAction = 0x130,      ///< N-ACTION
    DicomheroDimseCommandTypeNCreate = 0x140,      ///< N-CREATE
    DicomheroDimseCommandTypeNDelete = 0x150       ///< N-DELETE
};


typedef NS_ENUM(unsigned short, DicomheroDimseCommandPriority)
{
    DicomheroDimseCommandPriorityLow = 0x2,  ///< Low priority
    DicomheroDimseCommandPriorityMedium = 0, ///< Medium priority
    DicomheroDimseCommandPriorityHigh = 0x1  ///< High priority

};



/// \enum DicomheroDimseStatusCode
/// \brief The DICOM response status code.
///
//////////////////////////////////////////////////////////////////
typedef NS_ENUM(unsigned short, DicomheroDimseStatusCode)
{
    DicomheroDimseStatusCodeSuccess = 0,                                           ///< Success
    DicomheroDimseStatusCodeUnsupportedOptionalAttributes = 0x0001,                ///< Requested optional Attributes are not supported
    DicomheroDimseStatusCodeCannotUpdateperformedProcedureStepObject = 0x0110,     ///< Performed Procedure Step Object may no longer be updated
    DicomheroDimseStatusCodeUnsupportedSOPClass = 0x0122,                          ///< SOP Class not Supported
    DicomheroDimseStatusCodeOutOfResources = 0xa700,                               ///< Refused: Out of resources
    DicomheroDimseStatusCodeOutOfResourcesCannotCalculateNumberOfMatches = 0xa701, ///< Refused: Out of Resources - Unable to calculate number of matches
    DicomheroDimseStatusCodeOutOfResourcesCannotPerformSubOperations = 0xa702,     ///< Refused: Out of Resources - Unable to perform sub-operations
    DicomheroDimseStatusCodeMoveDestinationUnknown = 0xa801,                       ///< Refused: Move Destination unknown
    DicomheroDimseStatusCodeIdentifierDoesNotMatchSOPClass = 0xa900,               ///< Identifier does not match SOP Class
    DicomheroDimseStatusCodeSubOperationCompletedWithErrors = 0xb000,              ///< Sub-operations Complete - One or more Failures
    DicomheroDimseStatusCodeElementDiscarded = 0xb006,                             ///< Element discarded
    DicomheroDimseStatusCodeDatasetDoesNotMatchSOPClass = 0xb007,                  ///< Data Set does not match SOP Class
    DicomheroDimseStatusCodeUPSAlreadyCanceled = 0xb304,                           ///< The UPS is already in the requested state of CANCELED
    DicomheroDimseStatusCodeCoercedInvalidValuesToValidValues = 0xb305,            ///< Coerced invalid values to valid values
    DicomheroDimseStatusCodeUPSStateAlreadyCompleted = 0xb306,                     ///< The UPS is already in the requested state of COMPLETED
    DicomheroDimseStatusCodeUnableToProcess = 0xc000,                              ///< Unable to process
    DicomheroDimseStatusCodeMoreThanOneMatchFound = 0xc100,                        ///< More than one match found,
    DicomheroDimseStatusCodeCannotSupportRequestedTemplate = 0xc200,               ///< Unable to support requested template
    DicomheroDimseStatusCodeUPSNotUpdated = 0xc300,                                ///< Refused: The UPS may no longer be updated
    DicomheroDimseStatusCodeTransactionUIDNotProvided = 0xc301,                    ///< Refused: The correct Transaction UID was not provided
    DicomheroDimseStatusCodeUPSAlreadyInProgress = 0xc302,                         ///< Refused: The UPS is already IN PROGRESS
    DicomheroDimseStatusCodeCanScheduleOnlyWithNCreate = 0xc303,                   ///< Refused: The UPS may only become SCHEDULED via N-CREATE, not N-SET or N-ACTION
    DicomheroDimseStatusCodeUPSCannotChangeState = 0xc304,                         ///< Refused: The UPS has not met final state requirements for the requested state change
    DicomheroDimseStatusCodeInstanceUIDDoesNotExist = 0xc307,                      ///< Specified SOP Instance UID does not exist or is not a UPS Instance managed by this SCP
    DicomheroDimseStatusCodeUnknownAETitle = 0xc308,                               ///< Receiving AE-TITLE is Unknown to this SCP
    DicomheroDimseStatusCodeUPSNotSchedule = 0xc309,                               ///< Refused: The provided value of UPS State was not SCHEDULED
    DicomheroDimseStatusCodeUPSNotInProgress = 0xc310,                             ///< Refused: The UPS is not yet in the "IN PROGRESS" state
    DicomheroDimseStatusCodeUPSAlreadyCompleted = 0xc311,                          ///< Refused: The UPS is already COMPLETED
    DicomheroDimseStatusCodePerformerCannotBeContacted = 0xc312,                   ///< Refused: The performer cannot be contacted
    DicomheroDimseStatusCodePerformerDoesNotCancel = 0xc313,                       ///< Refused: Performer chooses not to cancel
    DicomheroDimseStatusCodeUnappropriateActionForInstance = 0xc314,               ///< Refused: Specified action not appropriate for specified instance
    DicomheroDimseStatusCodeSCPDoesNotSupportEventReports = 0xc315,                ///< Refused: SCP does not support Event Reports
    DicomheroDimseStatusCodeCanceled = 0xfe00,                                     ///< Terminated due to Cancel request
    DicomheroDimseStatusCodePending = 0xff00,                                      ///< Pending
    DicomheroDimseStatusCodePendingWithWarnings = 0xff01                           ///< Pending with warnings
};


/// \enum DicomheroDimseStatus
/// \brief Simplified DIMSE response status code, derived from
///        dimseStatusCode_t.
///
//////////////////////////////////////////////////////////////////
typedef NS_ENUM(unsigned short, DicomheroDimseStatus)
{
    DicomheroDimseStatusSuccess = 0, ///< The operation was completed succesfully
    DicomheroDimseStatusWarning = 1, ///< The operation was completed with warnings
    DicomheroDimseStatusFailure = 2, ///< The operation failed
    DicomheroDimseStatusCancel  = 3, ///< The operation was canceled
    DicomheroDimseStatusPending = 4  ///< The operation is still running

};


@class DicomheroDataSet;
@class DicomheroTagId;
@class DicomheroAssociationBase;


///
/// \brief Base class for the DICOM commands and responses.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroDimseCommandBase: NSObject
{
   @public
   define_dicomhero_object_holder(DimseCommandBase);
}
    -(id)initWithDicomheroCommand:define_dicomhero_parameter(DimseCommandBase);

    -(void)dealloc;

    ///
    /// \brief Returns the DicomheroDataSet containing the command data.
    ///
    /// \param pError set to a NSError derived class in case of error
    /// \return the DicomheroDataSet containing the command data
    ///
    //////////////////////////////////////////////////////////////////
    -(DicomheroDataSet*)getCommandDataSet:(NSError**)pError;

    ///
    /// \brief Returns the DicomheroDataSet containing the payload data.
    ///
    /// \param pError set to a NSError derived class in case of error
    /// \return the DicomheroDataSet containing the payload data
    ///
    //////////////////////////////////////////////////////////////////
    -(DicomheroDataSet*)getPayloadDataSet:(NSError**)pError;

    ///
    /// \brief Returns the message abstract syntax.
    ///
    /// \return the message abstract syntax
    ///
    //////////////////////////////////////////////////////////////////
    -(NSString*)getAbstractSyntax;

    ///
    /// \brief Returns the affected SOP instance UID.
    ///
    /// \param pError set to a NSError derived class in case of error
    /// \return the affected SOP instance UID
    ///
    //////////////////////////////////////////////////////////////////
    -(NSString*)getAffectedSopInstanceUid:(NSError**)pError;

    ///
    /// \brief Returns the affected SOP Class UID.
    ///
    /// \param pError set to a NSError derived class in case of error
    /// \return the affected SOP Class UID
    ///
    //////////////////////////////////////////////////////////////////
    -(NSString*)getAffectedSopClassUid:(NSError**)pError;

    ///
    /// \brief Returns the requested SOP instance UID.
    ///
    /// \param pError set to a NSError derived class in case of error
    /// \return requested SOP instance UID
    ///
    //////////////////////////////////////////////////////////////////
    -(NSString*)getRequestedSopInstanceUid:(NSError**)pError;

    ///
    /// \brief Returns the requested SOP class UID.
    ///
    /// \param pError set to a NSError derived class in case of error
    /// \return requested SOP class UID
    ///
    //////////////////////////////////////////////////////////////////
    -(NSString*)getRequestedSopClassUid:(NSError**)pError;

@end


///
/// \brief Base class for the DICOM commands.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroDimseCommand: DicomheroDimseCommandBase

    ///
    /// \brief Returns the command ID.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) unsigned short ID;

    ///
    /// \brief Returns the command type.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) DicomheroDimseCommandType commandType;

@end


///
/// \brief Base class for the DICOM responses.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroDimseResponse: DicomheroDimseCommandBase

    ///
    /// \brief Returns the response status.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) DicomheroDimseStatus status;

    ///
    /// \brief Returns the response status code.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) unsigned short statusCode;

@end


///
/// \brief Base class for all the partial responses
///        (responses to C-GET, C-MOVE and C-FIND).
///
//////////////////////////////////////////////////////////////////
@interface DicomheroCPartialResponse: DicomheroDimseResponse

    ///
    /// \brief Returns the number of remaining C-STORE sub operations.
    ///
    /// \param pError set to DicomheroMissingDataElementError if the
    ///               data is missing
    /// \return number of remaining C-STORE sub operations
    ///
    //////////////////////////////////////////////////////////////////
    -(unsigned int)getRemainingSubOperations:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    ///
    /// \brief Returns the number of completed C-STORE sub operations.
    ///
    /// \param pError set to DicomheroMissingDataElementError if the
    ///               data is missing
    /// \return number of completed C-STORE sub operations
    ///
    //////////////////////////////////////////////////////////////////
    -(unsigned int)getCompletedSubOperations:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    ///
    /// \brief Returns the number of failed C-STORE sub operations.
    ///
    /// \param pError set to DicomheroMissingDataElementError if the
    ///               data is missing
    /// \return number of failed C-STORE sub operations
    ///
    //////////////////////////////////////////////////////////////////
    -(unsigned int)getFailedSubOperations:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    ///
    /// \brief Returns the number of C-STORE sub operations completed
    ///        with warnings
    ///
    /// \param pError set to DicomheroMissingDataElementError if the
    ///               data is missing
    /// \return number of C-STORE sub operations completed with
    ///         warnings
    ///
    //////////////////////////////////////////////////////////////////
    -(unsigned int)getWarningSubOperations:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

@end


///
/// \brief Represents a C-STORE request.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroCStoreCommand: DicomheroDimseCommand

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID              message ID (can be retrieved
    ///                               with
    ///                               DicomheroDimseService::getNextCommandID()
    /// \param priority               message priority
    /// \param affectedSopClassUid    affected SOP instance UID
    /// \param affectedSopInstanceUid affected SOP instance UID
    /// \param originatorAET          originator AET (issuer of the
    ///                               C-MOVE or C-GET command)
    /// \param originatorMessageID    message ID of the C-MOVE or
    ///                               C-GET that triggered the C-STORE
    /// \param pPayload               C-STORE payload
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        priority:(DicomheroDimseCommandPriority)priority
        affectedSopClassUid:(NSString*)affectedSopClassUid
        affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
        originatorAET:(NSString*)originatorAET
        originatorMessageID:(unsigned short)originatorMessageID
        payload:(DicomheroDataSet*)pPayload;

    ///
    /// \brief Returns the AET of the entity that triggered this
    ///        C-STORE request either via a C-MOVE or a C-GET
    ///        request.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) NSString* originatorAET;

    ///
    /// \brief Returns the message ID of the C-MOVE or C-GET request
    ///        that triggered this C-STORE request.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) unsigned short originatorMessageID;

@end


///
/// \brief Represents a C-STORE response.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroCStoreResponse: DicomheroDimseResponse

    ///
    /// \brief Initializer.
    ///
    /// \param pReceivedCommand the C-STORE command for which this
    ///                          response is being constructed
    /// \param responseCode     the response code.
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithcommand:(DicomheroCStoreCommand*)pReceivedCommand
        responseCode:(DicomheroDimseStatusCode)responseCode;

@end


///
/// \brief Represents a C-GET command.
///
/// C-GET triggers a C-STORE command that is issued through
/// the same association used for the C-GET, therefore the
/// SCU must have negotiated the SCP role for the abstract
/// syntax (see DicomheroPresentationContexts and
/// DicomheroAssociationSCU).
///
//////////////////////////////////////////////////////////////////
@interface DicomheroCGetCommand: DicomheroDimseCommand

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID              message ID (can be retrieved
    ///                               with
    ///                               DicomheroDimseService::getNextCommandID()
    /// \param priority               message priority
    /// \param affectedSopClassUid    the affected SOP class UID
    /// \param pIdentifier            the keys to use for the
    ///                               C-GET query
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        priority:(DicomheroDimseCommandPriority)priority
        affectedSopClassUid:(NSString*)affectedSopClassUid
        identifier:(DicomheroDataSet*)pIdentifier;

@end


///
/// \brief Represents a C-GET response.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroCGetResponse: DicomheroCPartialResponse

    ///
    /// \brief Initializer to use when failed C-STORE operations
    ///        are present.
    ///
    /// This constructor should be used when the response code
    /// identifies a canceled operation, a failure, a refused
    /// operation or a warning.
    ///
    /// \param pReceivedCommand       the C-GET command for which
    ///                               this response is being
    ///                               constructed
    /// \param responseCode           the response code.
    /// \param remainingSubOperations number of remaining C-STORE
    ///                               operations
    /// \param completedSubOperations number of completed C-STORE
    ///                               operations
    /// \param failedSubOperations    number of failed C-STORE
    ///                               operations
    /// \param warningSubOperations   number of C-STORE operations
    ///                               completed with warnings
    /// \param pIdentifier            DataSet with the list of failed
    ///                               instance UIDs in the tag
    ///                               FailedSOPInstanceUIDList
    ///                               (0008,0058)
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithCommand:(DicomheroCGetCommand*)pReceivedCommand
        responseCode:(DicomheroDimseStatusCode)responseCode
        remainingSubOperations:(unsigned int)remainingSubOperations
        completedSubOperations:(unsigned int)completedSubOperations
        failedSubOperations:(unsigned int)failedSubOperations
        warningSubOperations:(unsigned int)warningSubOperations
        identifier:(DicomheroDataSet*)pIdentifier;

    ///
    /// \brief Initializer.
    ///
    /// \param pReceivedCommand       the C-GET command for which
    ///                               this response is being
    ///                               constructed
    /// \param responseCode           the response code.
    /// \param remainingSubOperations number of remaining C-STORE
    ///                               operations
    /// \param completedSubOperations number of completed C-STORE
    ///                               operations
    /// \param failedSubOperations    number of failed C-STORE
    ///                               operations
    /// \param warningSubOperations   number of C-STORE operations
    ///                               completed with warnings
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithcommand:(DicomheroCGetCommand*)pReceivedCommand
        responseCode:(DicomheroDimseStatusCode)responseCode
        remainingSubOperations:(unsigned int)remainingSubOperations
        completedSubOperations:(unsigned int)completedSubOperations
        failedSubOperations:(unsigned int)failedSubOperations
        warningSubOperations:(unsigned int)warningSubOperations;

@end


///
/// \brief Represents a C-FIND command.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroCFindCommand: DicomheroDimseCommand

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID           message ID (can be retrieved
    ///                            with
    ///                            DicomheroDimseService::getNextCommandID()
    /// \param priority            the message priority
    /// \param affectedSopClassUid the affected SOP class UID
    /// \param pIdentifier         the dataset with the identifier
    ///                            (list of tags to match and their
    ///                            requested values)
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        priority:(DicomheroDimseCommandPriority)priority
        affectedSopClassUid:(NSString*)affectedSopClassUid
        identifier:(DicomheroDataSet*)pIdentifier;

@end


///
/// \brief Represents a C-FIND response.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroCFindResponse: DicomheroDimseResponse

    ///
    /// \brief Initializer for responses with pending status.
    ///
    /// Responses with pending status carry a DicomheroDataSet with a
    /// single item from the C-FIND query results.
    ///
    /// \param receivedCommand command for which the reponse is being
    ///                        constructed
    /// \param identifier      one item from the C-FIND query results
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithCommand:(DicomheroCFindCommand*)pReceivedCommand
        identifier:(DicomheroDataSet*)pIdentifier;

    ///
    /// \brief Initializer for final C-FIND response (success or
    ///        failure).
    ///
    /// \param pReceivedCommand command for which the response is
    ///                         being constructed
    /// \param responseCode    response code
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithcommand:(DicomheroCFindCommand*)pReceivedCommand
        responseCode:(DicomheroDimseStatusCode)responseCode;
@end


///
/// \brief Represents a C-MOVE command.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroCMoveCommand: DicomheroDimseCommand

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID           message ID (can be retrieved
    ///                            with
    ///                            DicomheroDimseService::getNextCommandID()
    /// \param priority            the message priority
    /// \param affectedSopClassUid affected SOP class UID
    /// \param destinationAET      destination AET
    /// \param identifier          the dataset with the identifier
    ///                            (list of tags to match and their
    ///                            requested values)
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        priority:(DicomheroDimseCommandPriority)priority
        affectedSopClassUid:(NSString*)affectedSopClassUid
        destinationAET:(NSString*)destinationAET
        identifier:(DicomheroDataSet*)pIdentifier;

    ///
    /// \brief Returns the destination AET
    ///
    /// \param pError set to DicomheroMissingDataElementError if the
    ///               data is missing
    /// \return the destination AET
    ///
    //////////////////////////////////////////////////////////////////
    -(NSString*)getDestinationAET:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

@end


///
/// \brief Represents the C-MOVE response.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroCMoveResponse: DicomheroCPartialResponse

    ///
    /// \brief Initializer for failed C-STORE operations.
    ///
    /// This constructor should be used when the response code
    /// identifies a canceled operation, a failure, a refused
    /// operation or a warning.
    ///
    /// \param pReceivedCommand       the C-GET command for which
    ///                               this response is being
    ///                               constructed
    /// \param responseCode           the response code.
    /// \param remainingSubOperations number of remaining C-STORE
    ///                               operations
    /// \param completedSubOperations number of completed C-STORE
    ///                               operations
    /// \param failedSubOperations    number of failed C-STORE
    ///                               operations
    /// \param warningSubOperations   number of C-STORE operations
    ///                               completed with warnings
    /// \param identifier             DicomheroDataSet with the list of
    ///                               failed instance UIDs in the tag
    ///                               FailedSOPInstanceUIDList
    ///                               (0008,0058)
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithCommand:(DicomheroCMoveCommand*)pReceivedCommand
        responseCode:(DicomheroDimseStatusCode)responseCode
        remainingSubOperations:(unsigned int)remainingSubOperations
        completedSubOperations:(unsigned int)completedSubOperations
        failedSubOperations:(unsigned int)failedSubOperations
        warningSubOperations:(unsigned int)warningSubOperations
        identifier:(DicomheroDataSet*)pIdentifier;

    ///
    /// \brief Initializer.
    ///
    /// \param pReceivedCommand       the C-GET command for which
    ///                               this response is being
    ///                               constructed
    /// \param responseCode           the response code.
    /// \param remainingSubOperations number of remaining C-STORE
    ///                               operations
    /// \param completedSubOperations number of completed C-STORE
    ///                               operations
    /// \param failedSubOperations    number of failed C-STORE
    ///                               operations
    /// \param warningSubOperations   number of C-STORE operations
    ///                               completed with warnings
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithcommand:(DicomheroCMoveCommand*)pReceivedCommand
        responseCode:(DicomheroDimseStatusCode)responseCode
        remainingSubOperations:(unsigned int)remainingSubOperations
        completedSubOperations:(unsigned int)completedSubOperations
        failedSubOperations:(unsigned int)failedSubOperations
        warningSubOperations:(unsigned int)warningSubOperations;

@end


///
/// \brief Represents a C-ECHO command.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroCEchoCommand: DicomheroDimseCommand

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID           message ID (can be retrieved
    ///                            with
    ///                            DicomheroDimseService::getNextCommandID()
    /// \param priority            the priority
    /// \param affectedSopClassUid the affected SOP class UID
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        priority:(DicomheroDimseCommandPriority)priority
        affectedSopClassUid:(NSString*)affectedSopClassUid;

@end


///
/// \brief Represents a C-ECHO response.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroCEchoResponse: DicomheroDimseResponse

    ///
    /// \brief Initializer.
    ///
    /// \param pReceivedCommand command for which the response is being
    ///                        constructed
    /// \param responseCode    the response code
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithcommand:(DicomheroCEchoCommand*)pReceivedCommand
        responseCode:(DicomheroDimseStatusCode)responseCode;

@end


///
/// \brief Represents the C-CANCEL command.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroCCancelCommand: DicomheroDimseCommand

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID              message ID (can be retrieved
    ///                               with
    ///                               DicomheroDimseService::getNextCommandID()
    /// \param priority               the message priority
    /// \param cancelMessageID        the ID of the message to cancel
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        priority:(DicomheroDimseCommandPriority)priority
        cancelMessageID:(unsigned short)cancelMessageID;


    ///
    /// \brief Returns the ID of the message to cancel.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) unsigned short cancelMessageID;

@end


///
/// \brief Represents a N-EVENT-REPORT command.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroNEventReportCommand: DicomheroDimseCommand

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID              message ID (can be retrieved
    ///                               with
    ///                               DicomheroDimseService::getNextCommandID()
    /// \param affectedSopClassUid    the affected SOP class UID
    /// \param affectedSopInstanceUid the affected SOP instance UID
    /// \param eventID                the event ID
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        affectedSopClassUid:(NSString*)affectedSopClassUid
        affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
        eventID:(unsigned short)eventID;

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID              message ID (can be retrieved
    ///                               with
    ///                               DimseService::getNextCommandID()
    /// \param affectedSopClassUid    the affected SOP class UID
    /// \param affectedSopInstanceUid the affected SOP instance UID
    /// \param eventID                the event ID
    /// \param pEventInformation      the dataset with event
    ///                               information
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        affectedSopClassUid:(NSString*)affectedSopClassUid
        affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
        eventID:(unsigned short)eventID
        eventInformation:(DicomheroDataSet*)pEventInformation;

    ///
    /// \brief Returns the event ID.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) unsigned short eventID;

@end


///
/// \brief N-EVENT-REPORT response.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroNEventReportResponse: DicomheroDimseResponse

    ///
    /// \brief Initializer which includes a payload.
    ///        This implies a successful operation.
    ///
    /// \param pReceivedCommand the N-EVENT request command for which
    ///                         the response is being constructed
    /// \param pEventReply      the response payload
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithCommand:(DicomheroNEventReportCommand*)pReceivedCommand
        eventReply:(DicomheroDataSet*)pEventReply;

    ///
    /// \brief Initializer.
    ///
    /// \param pReceivedCommand the N-EVENT request command for which
    ///                         the response is being constructed
    /// \param responseCode     the response code
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithcommand:(DicomheroNEventReportCommand*)pReceivedCommand
        responseCode:(DicomheroDimseStatusCode)responseCode;

    ///
    /// \brief Get the event ID. The response may omit this
    ///        information.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) unsigned short eventID;

@end


///
/// \brief Represents a N-GET command.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroNGetCommand: DicomheroDimseCommand

    ///
    /// \brief Initializes the N-GET command.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID              message ID (can be retrieved
    ///                               with
    ///                               DicomheroDimseService::getNextCommandID()
    /// \param requestedSopClassUid    the requested SOP class UID
    /// \param requestedSopInstanceUid the requested SOP instance
    ///                                UID
    /// \param attributeIdentifierList A NSArray of DicomheroTagId
    ///                                objects, representing the tags
    ///                                to retrieve.
    ///                                An empty list means "all the
    ///                                tags".
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        requestedSopClassUid:(NSString*)requestedSopClassUid
        requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
        attributeIdentifierList:(NSArray*)attributeIdentifierList;

    ///
    /// \brief Return the list of tags to retrieve. an empty
    ///        list means all the tags.
    ///
    /// The returned NSArray object is filled with DicomheroTagId
    /// objects.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) NSArray* attributeList;

@end


///
/// \brief Represents a N-GET response.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroNGetResponse: DicomheroDimseResponse

    ///
    /// \brief Initializer.
    ///
    /// \param pReceivedCommand command for which the response is
    ///                        being constructed
    /// \param responseCode    response code
    /// \param pAttributeList  dataset containing the list of
    ///                        attribute identifiers
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithCommand:(DicomheroNGetCommand*)pReceivedCommand
        responseCode:(DicomheroDimseStatusCode)responseCode
        attributeList:(DicomheroDataSet*)pAttributeList;

    ///
    /// \brief Initializer.
    ///
    /// \param pReceivedCommand command for which the response is being
    ///                        constructed
    /// \param responseCode    response code
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithcommand:(DicomheroNGetCommand*)pReceivedCommand
        responseCode:(DicomheroDimseStatusCode)responseCode;

@end


///
/// \brief Represents the N-SET command
///
//////////////////////////////////////////////////////////////////
@interface DicomheroNSetCommand: DicomheroDimseCommand

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID              message ID (can be retrieved
    ///                               with
    ///                               DicomheroDimseService::getNextCommandID()
    /// \param requestedSopClassUid    the requested SOP class UID
    /// \param requestedSopInstanceUid the requested SOP instance
    ///                                UID
    /// \param pModificationList       dataset containing the new
    ///                                attributes values
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        requestedSopClassUid:(NSString*)requestedSopClassUid
        requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
        modificationList:(DicomheroDataSet*)pModificationList;

@end


///
/// \brief Represents the N-SET response.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroNSetResponse: DicomheroDimseResponse

    ///
    /// \brief Initializer of a successful response.
    ///
    /// \param pReceivedCommand    the command for which this response
    ///                            is being constructed
    /// \param pModifiedAttributes list of modified attributes. A
    ///                            NSArray of DicomheroTagId objects
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithCommand:(DicomheroNSetCommand*)pReceivedCommand
        modifiedAttributes:(NSArray*)pModifiedAttributes;

    ///
    /// \brief Initializer.
    ///
    /// \param pReceivedCommand    the command for which this response
    ///                            is being constructed
    /// \param responseCode        response code
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithcommand:(DicomheroNSetCommand*)pReceivedCommand
        responseCode:(DicomheroDimseStatusCode)responseCode;

    ///
    /// \brief Returns the list of modified attributes.
    ///        A NSArray of DicomheroTagId objects.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) NSArray* modifiedAttributes;

@end


///
/// \brief Represents the N-ACTION command.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroNActionCommand: DicomheroDimseCommand

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID              message ID (can be retrieved
    ///                               with
    ///                               DicomheroDimseService::getNextCommandID()
    /// \param requestedSopClassUid    the requested SOP class UID
    /// \param requestedSopInstanceUid the requested SOP instance
    ///                                UID
    /// \param actionID                action ID
    /// \param pActionInformation      dataset containing information
    ///                                about the action
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        requestedSopClassUid:(NSString*)requestedSopClassUid
        requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
        actionID:(unsigned short)actionID
        actionInformation:(DicomheroDataSet*)pActionInformation;

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID              message ID (can be retrieved
    ///                               with
    ///                               DicomheroDimseService::getNextCommandID()
    /// \param requestedSopClassUid    the requested SOP class UID
    /// \param requestedSopInstanceUid the requested SOP instance
    ///                                UID
    /// \param actionID                action ID
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        requestedSopClassUid:(NSString*)requestedSopClassUid
        requestedSopInstanceUid:(NSString*)requestedSopInstanceUid
        actionID:(unsigned short)actionID;

    ///
    /// \brief Returns the action's ID.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) unsigned short actionID;

@end


///
/// \brief Represents the N-ACTION response.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroNActionResponse: DicomheroDimseResponse

    ///
    /// \brief Initializer for a successful reply.
    ///
    /// \param pReceivedCommand the command for which this response is
    ///                         being constructed
    /// \param pActionReply     dataSet with information about the
    ///                         action reply
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithCommand:(DicomheroNActionCommand*)pReceivedCommand
        actionReply:(DicomheroDataSet*)pActionReply;

    ///
    /// \brief Initializer.
    ///
    /// \param pReceivedCommand the command for which this response is
    ///                         being constructed
    /// \param responseCode     the response code
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithcommand:(DicomheroNActionCommand*)pReceivedCommand
        responseCode:(DicomheroDimseStatusCode)responseCode;

    ///
    /// \brief Returns the action's ID.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) unsigned short actionID;

@end


///
/// \brief The N-CREATE command.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroNCreateCommand: DicomheroDimseCommand

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID              message ID (can be retrieved
    ///                               with
    ///                               DicomheroDimseService::getNextCommandID()
    /// \param affectedSopClassUid    the affected SOP class UID
    /// \param affectedSopInstanceUid the affected SOP instance UID
    /// \param pAttributeList         the dataset containing the
    ///                               attributes and values
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        affectedSopClassUid:(NSString*)affectedSopClassUid
        affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
        attributeList:(DicomheroDataSet*)pAttributeList;

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID              message ID (can be retrieved
    ///                               with
    ///                               DicomheroDimseService::getNextCommandID()
    /// \param affectedSopClassUid    the affected SOP class UID
    /// \param affectedSopInstanceUid the affected SOP instance UID
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        affectedSopClassUid:(NSString*)affectedSopClassUid
        affectedSopInstanceUid:(NSString*)affectedSopInstanceUid;

@end


///
/// \brief Represents the N-CREATE response.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroNCreateResponse: DicomheroDimseResponse

    ///
    /// \brief Initializer.
    ///
    /// \param pReceivedCommand command for which the response is
    ///                        being constructed
    /// \param pAttributeList   dataset containing the attributes list
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithCommand:(DicomheroNCreateCommand*)pReceivedCommand
        attributeList:(DicomheroDataSet*)pAttributeList;

    ///
    /// \brief Initializer.
    ///
    /// \param pReceivedCommand command for which the response is
    ///                         being constructed
    /// \param affectedSopInstanceUid affected SOP instance UID
    /// \param pAttributeList   dataset containing the attributes list
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithCommand:(DicomheroNCreateCommand*)pReceivedCommand
        affectedSopInstanceUid:(NSString*)affectedSopInstanceUid
        attributeList:(DicomheroDataSet*)pAttributeList;

    ///
    /// \brief Constructor.
    ///
    /// \param pReceivedCommand       command for which the response is
    ///                               being constructed
    /// \param affectedSopInstanceUid created SOP instance UID
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithCommand:(DicomheroNCreateCommand*)pReceivedCommand
        affectedSopInstanceUid:(NSString*)affectedSopInstanceUid;

    ///
    /// \brief Constructor.
    ///
    /// \param pReceivedCommand command for which the response is
    ///                        being constructed
    /// \param responseCode the response code
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithcommand:(DicomheroNCreateCommand*)pReceivedCommand
        responseCode:(DicomheroDimseStatusCode)responseCode;

@end


///
/// \brief The N-DELETE command.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroNDeleteCommand: DicomheroDimseCommand

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax      the message's abstract syntax
    ///                            (previously negotiated via the
    ///                            DicomheroPresentationContexts
    ///                            parameter of the
    ///                            DicomheroAssociationSCP or
    ///                            DicomheroAssociationSCU initializers)
    /// \param messageID              message ID (can be retrieved
    ///                               with
    ///                               DicomheroDimseService::getNextCommandID()
    /// \param requestedSopClassUid    the requested SOP class UID
    /// \param requestedSopInstanceUid the requested SOP instance UID
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax
        messageID:(unsigned short)messageID
        requestedSopClassUid:(NSString*)requestedSopClassUid
        requestedSopInstanceUid:(NSString*)requestedSopInstanceUid;

@end


///
/// \brief The N-DELETE response.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroNDeleteResponse: DicomheroDimseResponse

    ///
    /// \brief Initializer.
    ///
    /// \param pReceivedCommand command for which the response is
    ///                         being constructed
    /// \param responseCode     response code
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithcommand:(DicomheroNDeleteCommand*)pReceivedCommand
        responseCode:(DicomheroDimseStatusCode)responseCode;

@end


///
/// \brief Sends and receives DICOM commands and responses through
///        an DicomheroAssociationSCU or an DicomheroAssociationSCP.
///
/// DicomheroDimseService supplies getNextCommandID() in order to
/// obtain the ID for the commands sent through the
/// DicomheroDimseService object.
///
//////////////////////////////////////////////////////////////////
@interface DicomheroDimseService: NSObject
{
   @public
   define_dicomhero_object_holder(DimseService);
}

    ///
    /// \brief Initializer.
    ///
    /// \param pAssociation the AssociationBase derived class through
    ///                     which the DICOM commands and responses are
    ///                     sent and received
    ///
    //////////////////////////////////////////////////////////////////
    -(id)initWithAssociation:(DicomheroAssociationBase*)pAssociation;

    -(void)dealloc;

    ///
    /// \brief Returns the negotiated transfer syntax for a specific
    ///        abstract syntax.
    ///
    /// This method is multithread safe.
    ///
    /// \param abstractSyntax the abstract syntax for which the
    ///                       transfer syntax is needed
    /// \return the negotiated transfer syntax for the specified
    ///         abstract syntax
    ///
    //////////////////////////////////////////////////////////////////
    -(NSString*)getTransferSyntax:(NSString*)abstractSyntax error:(NSError**)pError;

    ///
    /// \brief Retrieves an ID that can be used on the next command
    ///        sent through this DimseService object.
    ///
    /// This method is multithread safe.
    ///
    /// \return an ID that can be used as command ID on a command sent
    ///         through this DimseService object
    ///
    //////////////////////////////////////////////////////////////////
    -(unsigned short)getNextCommandID;

    ///
    /// \brief Retrieves the next incoming DICOM command.
    ///
    /// The method blocks until the command is available or until
    /// the association is closed, either by the connected peer or
    /// by other means (e.g because of the DIMSE timeout), in which
    /// case the exception DicomheroStreamEOFError is set in pError.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// This method can be called by several threads at once:
    /// each thread will receive a DIMSE command and can reply
    /// to the command via sendCommandOrResponse().
    ///
    /// The underlying AssociationBase object will take care of
    /// limiting the number of incoming command according to the
    /// maximum number of performed operation negotiated for
    /// the association.
    ///
    /// Set pError to StreamEOFError if the association is closed
    /// while the method is waiting for an incoming command or
    /// response.
    ///
    /// \param pError set to a NSError derived class in case of error
    /// \return the next incoming DICOM command
    ///
    //////////////////////////////////////////////////////////////////
    -(DicomheroDimseCommand*)getCommand:(NSError**)pError;

    ///
    /// \brief Sends a DICOM command or response through the
    ///        association.
    ///
    /// This method is multithread safe.
    ///
    /// \param pCommand the command or response to send
    /// \param pError set to a NSError derived class in case of error
    ///
    //////////////////////////////////////////////////////////////////
    -(void)sendCommandOrResponse:(DicomheroDimseCommandBase*)pCommand error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    ///
    /// \brief Wait for the response for the specified C-STORE
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// Set pError to StreamEOFError if the association is closed
    /// while the method is waiting for an incoming command or
    /// response.
    ///
    /// \param pCommand the sent C-CSTORE command for which to
    ///                wait for a response
    /// \param pError set to a NSError derived class in case of error
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(DicomheroCStoreResponse*)getCStoreResponse:(DicomheroCStoreCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified C-GET
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// Set pError to StreamEOFError if the association is closed
    /// while the method is waiting for an incoming command or
    /// response.
    ///
    /// \param pCommand the sent C-GET command for which to
    ///                wait for a response
    /// \param pError set to a NSError derived class in case of error
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(DicomheroCGetResponse*)getCGetResponse:(DicomheroCGetCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified C-FIND
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// Set pError to StreamEOFError if the association is closed
    /// while the method is waiting for an incoming command or
    /// response.
    ///
    /// \param pCommand the sent C-FIND command for which to
    ///                wait for a response
    /// \param pError set to a NSError derived class in case of error
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(DicomheroCFindResponse*)getCFindResponse:(DicomheroCFindCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified C-MOVE
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// Set pError to StreamEOFError if the association is closed
    /// while the method is waiting for an incoming command or
    /// response.
    ///
    /// \param pCommand the sent C-MOVE command for which to
    ///                wait for a response
    /// \param pError set to a NSError derived class in case of error
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(DicomheroCMoveResponse*)getCMoveResponse:(DicomheroCMoveCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified C-ECHO
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// Set pError to StreamEOFError if the association is closed
    /// while the method is waiting for an incoming command or
    /// response.
    ///
    /// \param pCommand the sent C-ECHO command for which to
    ///                wait for a response
    /// \param pError set to a NSError derived class in case of error
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(DicomheroCEchoResponse*)getCEchoResponse:(DicomheroCEchoCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified N-EVENT-REPORT
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// Set pError to StreamEOFError if the association is closed
    /// while the method is waiting for an incoming command or
    /// response.
    ///
    /// \param pCommand the sent N-EVENT-REPORT command for which to
    ///                wait for a response
    /// \param pError set to a NSError derived class in case of error
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(DicomheroNEventReportResponse*)getNEventReportResponse:(DicomheroNEventReportCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified N-GET
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// Set pError to StreamEOFError if the association is closed
    /// while the method is waiting for an incoming command or
    /// response.
    ///
    /// \param pCommand the sent N-GET command for which to
    ///                wait for a response
    /// \param pError set to a NSError derived class in case of error
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(DicomheroNGetResponse*)getNGetResponse:(DicomheroNGetCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified N-SET
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// Set pError to StreamEOFError if the association is closed
    /// while the method is waiting for an incoming command or
    /// response.
    ///
    /// \param pCommand the sent N-SET command for which to
    ///                wait for a response
    /// \param pError set to a NSError derived class in case of error
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(DicomheroNSetResponse*)getNSetResponse:(DicomheroNSetCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified N-ACTION
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// Set pError to StreamEOFError if the association is closed
    /// while the method is waiting for an incoming command or
    /// response.
    ///
    /// \param pCommand the sent N-ACTION command for which to
    ///                wait for a response
    /// \param pError set to a NSError derived class in case of error
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(DicomheroNActionResponse*)getNActionResponse:(DicomheroNActionCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified N-CREATE
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// Set pError to StreamEOFError if the association is closed
    /// while the method is waiting for an incoming command or
    /// response.
    ///
    /// \param pCommand the sent N-CREATE command for which to
    ///                wait for a response
    /// \param pError set to a NSError derived class in case of error
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(DicomheroNCreateResponse*)getNCreateResponse:(DicomheroNCreateCommand*)pCommand error:(NSError**)pError;

    ///
    /// \brief Wait for the response for the specified N-DELETE
    ///        command and returns it.
    ///
    /// Other threads can wait for other commands or responses from
    /// the same DIMSE service. All the commands and responses are
    /// received by a secondary thread and distributed to all the
    /// listener waiting for a command or a response.
    ///
    /// Set pError to StreamEOFError if the association is closed
    /// while the method is waiting for an incoming command or
    /// response.
    ///
    /// \param pCommand the sent N-DELETE command for which to
    ///                wait for a response
    /// \param pError set to a NSError derived class in case of error
    /// \return the response for the specified command
    ///
    //////////////////////////////////////////////////////////////////
    -(DicomheroNDeleteResponse*)getNDeleteResponse:(DicomheroNDeleteCommand*)pCommand error:(NSError**)pError;

@end

#endif // dicomheroObjcDimse__INCLUDED_
