/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#if !defined(imebraObjcAcse__INCLUDED_)
#define imebraObjcAcse__INCLUDED_

#import <Foundation/Foundation.h>

#import "imebra_macros.h"
#import "imebra_dataset.h"
#import "imebra_streamReader.h"
#import "imebra_streamWriter.h"


///
/// \brief A presentation context defines which transfer syntaxes are supported
///        for a specific abstract syntax.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraPresentationContext: NSObject
{
    @public
    define_imebra_object_holder(PresentationContext);
}

    ///
    /// \brief Initializer.
    ///
    /// The SCU will act as SCU and the SCP will act as SCP when using this
    /// presentation context. To specify the roles of the SCU and the SCP
    /// use the initializer which includes the roles parameters.
    ///
    /// \param abstractSyntax the abstract syntax described by this presentation
    ///                       context
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax;

    ///
    /// \brief Initializer that specifies the SCU/SCP roles.
    ///
    /// \param abstractSyntax the abstract syntax described by this presentation
    ///                       context
    /// \param bSCURole       if true then the SCU will act as an SCU.
    ///                       The SCU and SCP can be both an SCU and an SCP for
    ///                       the same abstract syntax
    /// \param bSCPRole       if true then the SCU will act as an SCP
    ///                       The SCU and SCP can be both an SCU and an SCP for
    ///                       the same abstract syntax
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax scuRole:(BOOL)bSCURole scpRole:(BOOL)bSCPRole;

    -(void)dealloc;

    ///
    /// \brief Add a supported transfer syntax to the presentation context.
    ///
    /// \param transferSyntax the transfer syntax to add
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)addTransferSyntax:(NSString*)transferSyntax;

@end


///
/// \brief A collection of presentation contexts.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraPresentationContexts: NSObject
{
    @public
    define_imebra_object_holder(PresentationContexts);
}

    ///
    /// \brief Initializer.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)init;

    -(void)dealloc;

    ///
    /// \brief Add a presentation context to the collection.
    ///
    /// \param pPresentationContext the presentation context to add to the
    ///                             collection
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)addPresentationContext:(ImebraPresentationContext*)pPresentationContext;

@end


///
/// \brief A message composed by one or two datasets.
///
/// When sending a message through an ImebraAssociationBase derived object
/// then up to two dataset can be included into the message: the first
/// dataset is the command dataset, while the optional second one is the
/// command's payload.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraAssociationMessage: NSObject
{
    @public
    define_imebra_object_holder(AssociationMessage);
}

    -(id)initWithImebraAssociationMessage:define_imebra_parameter(AssociationMessage);

    -(void)dealloc;

    ///
    /// \brief Return the command stored in the message.
    ///
    /// \return the command ImebraDataSet
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraDataSet*)getCommand:(NSError**)pError;

    ///
    /// \brief Return the payload stored in the message.
    ///
    /// \return the payload ImebraDataSet
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraDataSet*)getPayload:(NSError**)pError;

    ///
    /// \brief Return true if the message has a payload.
    ///
    /// \return true if the message has a payload, false otherwise
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(BOOL)hasPayload;

    ///
    /// \brief The message's abstract syntax
    ///
    ///////////////////////////////////////////////////////////////////////////////
    @property (readonly) NSString* abstractSyntax;

@end






///
/// \brief A message composed by one or two datasets.
///
/// When sending a message through an ImebraAssociationBase derived object
/// then up to two dataset can be included into the message: the first
/// dataset is the command dataset, while the optional second one is the
/// command's payload.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraMutableAssociationMessage: ImebraAssociationMessage

    ///
    /// \brief Initializer.
    ///
    /// \param abstractSyntax the abstract syntax of the message.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithAbstractSyntax:(NSString*)abstractSyntax;

    ///
    /// \brief Add a command ImebraDataSet to the message.
    ///
    /// Two datasets can be transmitted at once: the first data set is the
    /// DICOM command, while the second optional one is the command payload.
    ///
    /// \param dataSet a ImebraDataSet to add to the message
    /// \param pError  set in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)addDataSet:(ImebraDataSet*)pDataSet error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

@end








///
/// \brief The association base class.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraAssociationBase: NSObject
{
    @public
    define_imebra_object_holder(AssociationBase);
}

    -(void)dealloc;

    ///
    /// \brief Read a command dataset and its payload (if any).
    ///
    /// \param pError set to ImebraStreamClosedError if the association has been
    ///               released or aborted.
    ///
    ///
    /// \return an ImebraAssociationMessage containing a command and its payload.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraAssociationMessage*)getCommand:(NSError**)pError;

    ///
    /// \brief Read a response dataset and its payload (if any).
    ///
    /// \param messageId the message ID for which the response is expected
    /// \param pError    set to ImebraStreamClosedError if the association has been
    ///                   released or aborted.
    ///
    /// \return an AssociationDataSet containing a response and its payload.
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(ImebraAssociationMessage*)getResponse:(unsigned int)messageId error:(NSError**)pError;

    ///
    /// \brief Send a DICOM message to the connected peer.
    ///
    /// \param pMessage the DICOM message to send
    /// \param pError   set to a subclass of NSError in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)sendMessage:(ImebraAssociationMessage*)pMessage error:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    ///
    /// \brief Releases the association.
    ///
    /// The method blocks until the other party acknowledges the release command
    /// or until the ACSE timout expires.
    ///
    /// \param pError set to a subclass of NSError in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)release:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    ///
    /// \brief Aborts the association.
    ///
    /// The association will be aborted as soon as possible. The other party
    /// will not acknowledge the abort command.
    ///
    /// \param pError set to a subclass of NSError in case of error
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(void)abort:(NSError**)pError
        __attribute__((swift_error(nonnull_error)));

    ///
    /// \brief Returns the transfer syntax negotiated for a specific
    ///        abstract syntax.
    ///
    /// \param abstractSyntax the abstract syntax for which the
    ///                       transfer syntax is requested
    /// \param pError         set to ImebraAcseNoTransferSyntaxError
    ///                       if no transfer syntax is available or
    ///                ImebraAcsePresentationContextNotRequestedError
    ///                       if the abstract syntax was not
    ///                       negotiated at all
    /// \return the negotiated transfer syntax for the specified
    ///         abstract syntax
    ///
    //////////////////////////////////////////////////////////////////
    -(NSString*)getTransferSyntax:(NSString*)abstractSyntax error:(NSError**)pError;

    ///
    /// \brief Returns our AET.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) NSString* thisAET;

    ///
    /// \brief Returns the other party's AET.
    ///
    //////////////////////////////////////////////////////////////////
    @property (readonly) NSString* otherAET;

@end


///
/// \brief Represents the SCU part of an association.
///
/// The initializer tries to create an association with an SCP via the
/// ImebraStreamReader and the ImebraStreamWriter passed as parameter;
/// when communicating through the ImebraTCPStream then the same object is
/// used as reader and writer.
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraAssociationSCU: ImebraAssociationBase

    ///
    /// \brief Initiates an association request.
    ///
    /// Blocks until the association has been negotiated successfully or an
    /// error occurs (pError is set).
    ///
    /// \param thisAET              the AET of the SCU
    /// \param otherAET             the AET of the SCP with wich the association
    ///                             is negotiated
    /// \param invokedOperations    maximum number of parallel operations we
    ///                             intend to invoke when acting as a SCU
    /// \param performedOperations  maximum number of parallel operations we can
    ///                             perform when acting as a SCP
    /// \param presentationContexts list of proposed presentation contexts
    /// \param pInput               input stream from which the SCP receives
    ///                             data. When using a TCPStream the same object
    ///                             can act as both input and output
    /// \param pOutput              output stream into which the SCP writes
    ///                             data. When using a TCPStream the same object
    ///                             can act as both input and output
    /// \param dimseTimeoutSeconds  DIMSE timeout, in seconds. 0 means infinite
    /// \param pError               may be set to one of the following errors:
    ///                             - ImebraCorruptedAcseMessageError
    ///                             - ImebraAcseSCUApplicationContextNameNotSupportedError
    ///                             - ImebraAcseSCUCalledAETNotRecognizedError
    ///                             - ImebraCodecWrongFormatError
    ///                             - ImebraDicomCodecDepthLimitReachedError
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithThisAET:(NSString*)thisAET otherAET:(NSString*)otherAET
                                    maxInvokedOperations:(unsigned int)invokedOperations
                                    maxPerformedOperations:(unsigned int)performedOperations
                                    presentationContexts:(ImebraPresentationContexts*)presentationContexts
                                    reader:(ImebraStreamReader*)pInput
                                    writer:(ImebraStreamWriter*)pOutput
                                    dimseTimeoutSeconds:(unsigned int)dimseTimeoutSeconds error:(NSError**)pError;
@end


///
/// \brief Represents the SCP part of an association.
///
/// The initializer waits for an incoming DICOM association request
/// (a-request-rq) and then returns once the association has been established,
/// or set pError to ImebraCorruptedAcseMessageError if the SCU sends a
/// wrong message type.
///
/// <b>ImebraAssociationSCP lifecycle</b>
///
/// Only create an ImebraAssociationSCP object AFTER the ImebraStreamReader
/// and ImebraStreamWriter parameters have been successfully connected to
/// their peer, then keep it alive and poll the data via readCommand() and
/// readPayload() until pError is set to ImebraStreamClosedError or
/// ImebraCorruptedAcseMessageError.
///
/// pError set to ImebraStreamClosedError means that the association has
/// been released or aborted.
///
/// If you call the abort() method on the ImebraAssociationSCP you should still
/// wait for pError set to ImebraStreamClosedError by getCommand().
///
///////////////////////////////////////////////////////////////////////////////
@interface ImebraAssociationSCP: ImebraAssociationBase

    ///
    /// \brief Listens for an association request.
    ///
    /// Blocks until the association has been negotiated successfully or an
    /// error occurs (pError is set).
    ///
    /// \param thisAET              the AET of the SCP. If empty then the SCP
    ///                             will accept associations for any called AET,
    ///                             otherwise it will reject the association
    ///                             when the called AET does not match this one
    /// \param invokedOperations    maximum number of parallel operations we
    ///                             intend to invoke when acting as a SCU
    /// \param performedOperations  maximum number of parallel operations we can
    ///                             perform when acting as a SCP
    /// \param presentationContexts list of accepted presentation contexts
    /// \param pInput               input stream from which the SCP receives
    ///                             data. When using a TCPStream the same object
    ///                             can act as both input and output
    /// \param pOutput              output stream into which the SCP writes
    ///                             data. When using a TCPStream the same object
    ///                             can act as both input and output
    /// \param dimseTimeoutSeconds  DIMSE timeout, in seconds. 0 means infinite
    /// \param artimTimeoutSeconds  ARTIM timeout, in seconds. Amount of time that
    ///                             is allowed to pass before an association
    ///                             request arrives
    /// \param pError               may be set to one of the following errors:
    ///                             - ImebraCorruptedAcseMessageError
    ///                             - ImebraAcseSCUApplicationContextNameNotSupportedError
    ///                             - ImebraAcseSCUCalledAETNotRecognizedError
    ///                             - ImebraCodecWrongFormatError
    ///                             - ImebraDicomCodecDepthLimitReachedError
    ///
    ///////////////////////////////////////////////////////////////////////////////
    -(id)initWithThisAET:(NSString*)thisAET
                                    maxInvokedOperations:(unsigned int)invokedOperations
                                    maxPerformedOperations:(unsigned int)performedOperations
                                    presentationContexts:(ImebraPresentationContexts*)presentationContexts
                                    reader:(ImebraStreamReader*)pInput
                                    writer:(ImebraStreamWriter*)pOutput
                                    dimseTimeoutSeconds:(unsigned int)dimseTimeoutSeconds
                                    artimTimeoutSeconds:(unsigned int)artimTimeoutSeconds error:(NSError**)pError;
@end


#endif // imebraObjcAcse__INCLUDED_
