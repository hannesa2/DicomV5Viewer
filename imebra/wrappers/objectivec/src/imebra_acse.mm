/*
Copyright 2005 - 2017 by Paolo Brandoli/Binarno s.p.

Imebra is available for free under the GNU General Public License.

The full text of the license is available in the file license.rst
 in the project root folder.

If you do not want to be bound by the GPL terms (such as the requirement
 that your application must also be GPL), you may purchase a commercial
 license for Imebra from the Imebra’s website (http://imebra.com).
*/

#include "imebra_implementation_macros.h"

#import <Foundation/Foundation.h>
#import "../include/imebraobjc/imebra_acse.h"
#include "imebra_nserror.h"
#include <imebra/acse.h>
#include <imebra/dataSet.h>
#include <imebra/streamReader.h>
#include <imebra/streamWriter.h>
#include "imebra_strings.h"

////////////////////////////////////////////////////////
//
// ImebraPresentationContext
//
////////////////////////////////////////////////////////

@implementation ImebraPresentationContext

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
{
    reset_imebra_object_holder(PresentationContext);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(PresentationContext, new imebra::PresentationContext(imebra::NSStringToString(abstractSyntax)));
    }
    return self;
}

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax scuRole:(BOOL)bSCURole scpRole:(BOOL)bSCPRole
{
    reset_imebra_object_holder(PresentationContext);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(PresentationContext, new imebra::PresentationContext(imebra::NSStringToString(abstractSyntax), bSCURole != 0, bSCPRole != 0));
    }
    return self;
}

-(void)dealloc
{
    delete_imebra_object_holder(PresentationContext);
}

-(void)addTransferSyntax:(NSString*)transferSyntax
{
    get_imebra_object_holder(PresentationContext)->addTransferSyntax(imebra::NSStringToString(transferSyntax));
}

@end


@implementation ImebraPresentationContexts

-(id)init
{
    reset_imebra_object_holder(PresentationContexts);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(PresentationContexts, new imebra::PresentationContexts());
    }
    return self;

}

-(void)dealloc
{
    delete_imebra_object_holder(PresentationContexts);
}

-(void)addPresentationContext:(ImebraPresentationContext*)pPresentationContext
{
    get_imebra_object_holder(PresentationContexts)->addPresentationContext(*get_other_imebra_object_holder(pPresentationContext, PresentationContext));
}

@end


@implementation ImebraAssociationMessage: NSObject

-(id)initWithImebraAssociationMessage:define_imebra_parameter(AssociationMessage)
{
    reset_imebra_object_holder(AssociationMessage);
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(AssociationMessage, new imebra::AssociationMessage(*get_imebra_parameter(AssociationMessage)));
    }
    else
    {
        delete get_imebra_parameter(AssociationMessage);
    }
    return self;
}


-(void)dealloc
{
    delete_imebra_object_holder(AssociationMessage);
}

-(NSString*)abstractSyntax
{
    return imebra::stringToNSString(get_imebra_object_holder(AssociationMessage)->getAbstractSyntax());
}

-(ImebraDataSet*)getCommand:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraDataSet alloc] initWithImebraDataSet:(new imebra::DataSet(get_imebra_object_holder(AssociationMessage)->getCommand()))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraDataSet*)getPayload:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraDataSet alloc] initWithImebraDataSet:(new imebra::DataSet(get_imebra_object_holder(AssociationMessage)->getPayload()))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(BOOL)hasPayload
{
    return get_imebra_object_holder(AssociationMessage)->hasPayload();
}

@end


@implementation ImebraMutableAssociationMessage

-(id)initWithAbstractSyntax:(NSString*)abstractSyntax
{
    self = [super init];
    if(self)
    {
        set_imebra_object_holder(AssociationMessage, new imebra::MutableAssociationMessage(imebra::NSStringToString(abstractSyntax)));
    }
    return self;
}

-(void)addDataSet:(ImebraDataSet*)pDataSet error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    ((imebra::MutableAssociationMessage*)get_imebra_object_holder(AssociationMessage))->addDataSet(*get_other_imebra_object_holder(pDataSet, DataSet));

    OBJC_IMEBRA_FUNCTION_END();
}

@end


@implementation ImebraAssociationBase

-(void)dealloc
{
    delete_imebra_object_holder(AssociationBase);
}

-(ImebraAssociationMessage*)getCommand:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return [[ImebraAssociationMessage alloc] initWithImebraAssociationMessage:(new imebra::AssociationMessage(get_imebra_object_holder( AssociationBase)->getCommand()))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(ImebraAssociationMessage*)getResponse:(unsigned int) messageId error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();
    return [[ImebraAssociationMessage alloc] initWithImebraAssociationMessage:(new imebra::AssociationMessage(get_imebra_object_holder(AssociationBase)->getResponse((std::uint16_t)messageId)))];

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(void)sendMessage:(ImebraAssociationMessage*)pMessage error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    get_imebra_object_holder(AssociationBase)->sendMessage(*(get_other_imebra_object_holder(pMessage, AssociationMessage)));

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)release:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    get_imebra_object_holder(AssociationBase)->release();

    OBJC_IMEBRA_FUNCTION_END();
}

-(void)abort:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    get_imebra_object_holder(AssociationBase)->abort();

    OBJC_IMEBRA_FUNCTION_END();
}

-(NSString*)getTransferSyntax:(NSString*)abstractSyntax error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    return imebra::stringToNSString(get_imebra_object_holder(AssociationBase)->getTransferSyntax(imebra::NSStringToString(abstractSyntax)));

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

-(NSString*)thisAET
{
    return imebra::stringToNSString(get_imebra_object_holder(AssociationBase)->getThisAET());
}

-(NSString*)otherAET
{
    return imebra::stringToNSString(get_imebra_object_holder(AssociationBase)->getOtherAET());
}

@end


@implementation ImebraAssociationSCU

-(id)initWithThisAET:(NSString*)thisAET otherAET:(NSString*)otherAET
    maxInvokedOperations:(unsigned int)invokedOperations
    maxPerformedOperations:(unsigned int)performedOperations
    presentationContexts:(ImebraPresentationContexts*)presentationContexts
    reader:(ImebraStreamReader*)pInput
    writer:(ImebraStreamWriter*)pOutput
    dimseTimeoutSeconds:(unsigned int)dimseTimeoutSeconds error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    reset_imebra_object_holder(AssociationBase);

    self = [super init];
    if(self)
    {
        set_imebra_object_holder(AssociationBase,
                    new imebra::AssociationSCU(
                                     imebra::NSStringToString(thisAET),
                                     imebra::NSStringToString(otherAET),
                                     invokedOperations,
                                     performedOperations,
                                     *get_other_imebra_object_holder(presentationContexts, PresentationContexts),
                                     *get_other_imebra_object_holder(pInput, StreamReader),
                                     *get_other_imebra_object_holder(pOutput, StreamWriter),
                                     dimseTimeoutSeconds));
    }
    return self;

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

@end


@implementation ImebraAssociationSCP

-(id)initWithThisAET:(NSString*)thisAET
    maxInvokedOperations:(unsigned int)invokedOperations
    maxPerformedOperations:(unsigned int)performedOperations
    presentationContexts:(ImebraPresentationContexts*)presentationContexts
    reader:(ImebraStreamReader*)pInput
    writer:(ImebraStreamWriter*)pOutput
    dimseTimeoutSeconds:(unsigned int)dimseTimeoutSeconds
    artimTimeoutSeconds:(unsigned int)artimTimeoutSeconds error:(NSError**)pError
{
    OBJC_IMEBRA_FUNCTION_START();

    reset_imebra_object_holder(AssociationBase);

    self = [super init];
    if(self)
    {
        set_imebra_object_holder(AssociationBase,
                    new imebra::AssociationSCP(
                                     imebra::NSStringToString(thisAET),
                                     invokedOperations,
                                     performedOperations,
                                     *get_other_imebra_object_holder(presentationContexts, PresentationContexts),
                                     *get_other_imebra_object_holder(pInput, StreamReader),
                                     *get_other_imebra_object_holder(pOutput, StreamWriter),
                                     dimseTimeoutSeconds,
                                     artimTimeoutSeconds));
    }
    return self;

    OBJC_IMEBRA_FUNCTION_END_RETURN(nil);
}

@end


